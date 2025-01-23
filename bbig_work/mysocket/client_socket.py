import socket
from threading import Thread
import struct

Send_Head = 0xaa
Send_Tail = 0xbb


class Client:
    # 初始方法
    def __init__(self):
        self.client = socket.socket()
        self.client.connect(("192.168.77.115", 8989))
        self.work_thread()

        # 自定义参数
        self.rece_info = ""
        self.flag_login = 0
        self.param_dic = {'login': 0x00, 'forward': 0x41, 'back': 0x45, 'left': 0x46, 'right': 0x42, 'stop': 0x5a,
                          'pitch': 0x06, 'sql_query': 0x0b}
        self.pitch = 0
        self.pitch_new = 0

    # 发送文本消息
    def send_msg_text(self, msg):
        self.client.send(msg.encode())
        # if msg.upper() == "Q":
        #     self.client.close()
        # self.destroy()
        # self.message.clear()

    # 发送16进制信息
    def send_msg_hex(self, msg):
        self.client.send(msg)

    # 接收消息
    def recv_msg(self):
        while True:
            try:
                data = self.client.recv(1024)
                top_msg = struct.unpack("<BB", data[:2])
                if top_msg == (49, 48):
                    data = data[2:].decode()
                    self.rece_info = data
                else:
                    data = struct.unpack("<" + str(len(data)) + "B", data)  # 不定长B接收
                    if data[0] == Send_Head and data[len(data) - 1] == Send_Tail:
                        if data[1] == self.param_dic['login']:
                            self.flag_login = data[2]
                        elif data[1] == self.param_dic['pitch']:
                            self.pitch = data[3]

                            if data[2] == 0x02:  # 1正2负，复原
                                self.pitch = -self.pitch

                            self.pitch_new = 1

                print('client收', data)
                # data = data + "\n"
                # self.content.append(data)
            except:
                exit()

    # 线程处理
    def work_thread(self):
        # Thread(target=self.send_msg).start()
        Thread(target=self.recv_msg).start()

    # 小车控制
    def car_forward(self):
        pack = struct.pack("<BBB", Send_Head, self.param_dic['forward'], Send_Tail)
        self.send_msg_hex(pack)

    def car_back(self):
        pack = struct.pack("<BBB", Send_Head, self.param_dic['back'], Send_Tail)
        self.send_msg_hex(pack)

    def car_left(self):
        pack = struct.pack("<BBB", Send_Head, self.param_dic['left'], Send_Tail)
        self.send_msg_hex(pack)

    def car_right(self):
        pack = struct.pack("<BBB", Send_Head, self.param_dic['right'], Send_Tail)
        self.send_msg_hex(pack)

    def car_stop(self):
        pack = struct.pack("<BBB", Send_Head, self.param_dic['stop'], Send_Tail)
        self.send_msg_hex(pack)

    # 请求查询数据库最后一条记录
    def sql_query(self):
        pack = struct.pack("<BBB", Send_Head, self.param_dic['sql_query'], Send_Tail)
        self.send_msg_hex(pack)
