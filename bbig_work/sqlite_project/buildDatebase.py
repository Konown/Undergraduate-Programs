import sqlite3

# 用户数据表建立
def buildDatabase_user():
    conn = sqlite3.connect('../balance_car.db')
    cur = conn.cursor()

    cur.execute("""create table if not exists
            %s(
            %s integer primary key autoincrement,
            %s varchar(128),
            %s varchar(128))"""
                % ('user',
                   'id',
                   'name',
                   'password',
                   ))

    conn.commit()
    conn.close()


# 小车数据表建立
def buildDatabase_car():
    conn = sqlite3.connect('../balance_car.db')
    cur = conn.cursor()

    cur.execute("""
        CREATE TABLE IF NOT EXISTS car(
        user_id INT    not null,
        pitch   INT    not null,
        PRIMARY KEY (user_id));""")

    conn.commit()
    conn.close()

# 清空小车数据表中的内容
def clearDatabase_car():
    conn = sqlite3.connect('balance_car.db')
    cur = conn.cursor()

    cur.execute("""DELETE FROM car;""")
    conn.commit()
    conn.close()


if __name__ == "__main__":
    buildDatabase_user()
    buildDatabase_car()