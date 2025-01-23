import sqlite3


# 增加用户数据
def add_user_data():
    input_name = input("请输入您的用户名：")
    input_password = input("请输入您的密码：")

    sql = sqlite3.connect("../balance_car.db")
    sql.execute("insert into user(name, passworld) values(?,?)",
                (input_name, input_password))
    sql.commit()
    print("添加成功")
    sql.close()

# 显示用户数据
def showall_userdata():
    sql = sqlite3.connect("../balance_car.db")
    data = sql.execute("select * from user").fetchall()
    sql.close()
    return data
# "select * from user"为查询user对应的表的所有资料的指令


# 删除用户数据
def drop_userdata():
    print('指定id删除')
    sql = sqlite3.connect("../balance_car.db")
    data = sql.execute("select * from user").fetchall()
    print('所有数据:' + str(data))
    while 1:
        id = input('请输入你要删除的数据的id:')
        sql.execute("DELETE FROM user WHERE id = %s" % id)
        sql.commit()
        print('删除完成')
        data = sql.execute("select * from user")
        print(data.fetchall())
        sql.close()
        break


# 获取小车数据
def gainCarData():
    conn =sqlite3.connect('balance_car.db')
    cur = conn.cursor()

    cur.execute('''
        SELECT pitch FROM car
        WHERE user_id = (SELECT max(user_id) FROM car);''')
    # cur.execute('''
    #     SELECT pitch FROM car
    #     ORDER BY user_id DESC LIMIT 5;''')

    carData = cur.fetchone()[0]
    print(carData)

    conn.close()

    return carData


# 保存小车数据
def saveCarData(msg):
    conn = sqlite3.connect('balance_car.db')
    cur = conn.cursor()

    cur.execute('''SELECT COUNT(*) FROM car;''')
    row_count = cur.fetchone()[0]

    userinfo = [row_count + 10001, msg]

    cur.execute('''INSERT INTO car(
                user_id, pitch)
                VALUES(?, ?);''', userinfo)

    conn.commit()
    conn.close()



if __name__ == "__main__":
    print("""
    user数据表
    1:增加数据
    2:查询数据
    3.删除数据
    q:退出
    """)
    while 1:
        option = None
        cho = input('选择您想要的进行的操作:')
        if cho == '1':
            add_user_data()
        elif cho == '2':
            data = showall_userdata()
            print(data)
        elif cho == '3':
            drop_userdata()
        elif cho == 'q':
            break
        else:
            "输入错误"
