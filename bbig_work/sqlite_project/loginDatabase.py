import sqlite3


def check_username(username):
    sql = sqlite3.connect('balance_car.db')
    data = sql.execute("select * from user where name='%s'" % username).fetchone()
    sql.close()
    return data


def user_login(name, password):
    data = check_username(name)  # 获取用户名对应的数据库资料
    if data:
        if data[2] == password:
            # print("登录成功")
            flag = 1
        else:
            # print("密码错误")
            flag = 2
    else:
        # print("用户名不存在")
        flag = 3
    return flag

