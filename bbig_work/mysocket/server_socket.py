import socket
from threading import Thread
import time
import struct

from sqlite_project.loginDatabase import user_login
from sqlite_project.UserData import saveCarData, gainCarData

Send_Head = 0xaa
Send_Tail = 0xbb


class Server:

    # 初始方法
    def __init__(self):
        # 参数初始化
        self.con_info = ""
        self.con_disinfo = ""
        self.rece_info = ""
        self.param_dic = {'login': 0x00, 'forward': 0x41, 'back': 0x45, 'left': 0x46, 'right': 0x42, 'stop': 0x5a,
                          'pitch': 0x06, 'sql_query': 0x0b}

        # 创建socket对象
        self.server = socket.socket()
        self.server.bind(("192.168.77.115", 8989))
        self.server.listen(7)

        # 所有的客户端
        self.clients = []
        # 用户名字与ip的绑定信息
        self.clients_name_ip = {}
        # 小车客户端
        self.car_client = None

        Thread(target=self.get_conn).start()

    # 监听客户端连接
    def get_conn(self):
        while True:
            client, address = self.server.accept()
            print(address)
            if address[0] == "192.168.77.89":  # 小车ip
                self.car_client = client
                Thread(target=self.get_msg_car).start()
            else:
                self.clients.append(client)
                Thread(target=self.get_msg_client, args=(client, self.clients, self.clients_name_ip, address)).start()

    # 进行用户客户端信息处理
    def get_msg_client(self, client, clients, clients_name_ip, address):
        # 接收客户端发来的名称与密码，与数据库信息匹配
        while True:
            user_name, user_password = client.recv(1024).decode().split("+")
            print(user_name, user_password)
            # 与数据库信息匹配
            flag_login = user_login(user_name, user_password)
            user_pack = struct.pack("<BBBB", Send_Head, self.param_dic['login'], int(flag_login), Send_Tail)
            client.send(user_pack)
            if flag_login == 1:
                # 昵称与 ip 绑定
                clients_name_ip[address] = user_name
                self.con_info = user_name
                break

        # 循环监听客户端信息
        while True:
            # 获取所有客户发送的消息
            try:
                recv_data = client.recv(1024)
                # print(len(recv_data))
                top_msg = struct.unpack("<BB", recv_data[:2])
                if top_msg == (49, 48):
                    recv_data = recv_data[2:].decode()
                    self.rece_info = recv_data
                else:
                    recv_data = struct.unpack("<" + str(len(recv_data)) + 'B', recv_data)
                    self.parse_user_data(recv_data)

                print(recv_data)

            except Exception as e:
                self.close_client(client, address)
                print(e)
                break
            # 如果用户退出，输入Q
            # if recv_data.upper() == "Q":
            #     self.close_client(client, address)
            #     break
            # for c in clients:
            #     c.send((clients_name_ip[address] + "" +
            #             time.strftime("%x") + "\n" + recv_data).encode())

    # 关闭资源
    def close_client(self, client, address):
        self.con_disinfo = self.clients_name_ip[address]
        self.clients.remove(client)
        client.close()

        print(self.clients_name_ip[address] + "断开连接")

    # 解析用户数据
    def parse_user_data(self, param_data):
        if self.param_dic['forward'] <= param_data[1] <= self.param_dic['stop']:
            send_data = struct.pack("<8B", param_data[1], param_data[1], param_data[1], param_data[1], param_data[1],
                                    param_data[1], param_data[1], param_data[1])
            self.send_msg_car(send_data)
            # saveCarData(param_data[1])
        elif param_data[1] == self.param_dic['sql_query']:
            check_data = str(10) + "最后一次pitch值为：\t" + str(gainCarData())
            self.send_msg_client(check_data)

    # 接收小车信息
    def get_msg_car(self):
        self.con_info = "car"
        state = 0
        recv_pack = []
        while True:
            try:
                # recv_data = self.car_client.recv(5)
                # recv_data = struct.unpack("<" + str(len(recv_data)) + "B", recv_data)
                # if recv_data[0] == 0xaa and recv_data[-1] == 0xbb:
                #     if recv_data[1] == self.param_dic['pitch']:
                #         pitch = recv_data[3]
                #         send_pitch = struct.pack("<BBBBB", Send_Head, self.param_dic['pitch'], recv_data[2], pitch,
                #                                  Send_Tail)
                #         if recv_data[2] == 0x02:  # 1正2负，复原
                #             pitch = -pitch
                #         print('pitch', pitch)
                #         saveCarData(pitch)
                #         self.send_msg_client_bin(send_pitch)  # 将 pitch 值发给客户端，客户端画图

                recv_data = self.car_client.recv(1)
                recv_data = struct.unpack("<B", recv_data)

                # print('server收', recv_data)
                recv_data = recv_data[0]
                # print('状态', state)
                if recv_data:
                    if recv_data == 0xaa and state == 0:
                        state = 1
                        recv_pack.append(recv_data)
                    elif state == 1:
                        state = 2
                        recv_pack.append(recv_data)
                    elif state == 2:
                        state = 3
                        recv_pack.append(recv_data)
                    elif state == 3:
                        recv_pack.append(recv_data)
                        state = 4
                    elif state == 4 and recv_data == 0xbb:
                        recv_pack.append(recv_data)
                        state = 5
                    else:
                        state = 0
                        recv_pack = []

                    if state == 5:
                        pitch = recv_pack[3]
                        send_pitch = struct.pack("<BBBBB", Send_Head, self.param_dic['pitch'], recv_pack[2], pitch,
                                                 Send_Tail)
                        if recv_pack[2] == 0x02:  # 1正2负，复原
                            pitch = -pitch
                        print('pitch', pitch)
                        saveCarData(pitch)
                        self.send_msg_client_bin(send_pitch)  # 将 pitch 值发给客户端，客户端画图
                        state = 0
                        recv_pack = []

            except Exception as e:
                print(e)
                self.car_client.close()
                self.con_disinfo = "car"
                break

    # 发送信息给用户客户端
    def send_msg_client(self, msg):
        for c in self.clients:
            c.send(msg.encode())

    # 发送二进制信息给用户客户端
    def send_msg_client_bin(self, msg):
        for c in self.clients:
            c.send(msg)

    # 发送信息给小车
    def send_msg_car(self, msg):
        self.car_client.send(msg)


if __name__ == "__main__":
    Server()
