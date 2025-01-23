# -*- coding: utf-8 -*-

import sys
import sqlite3

from PyQt5.QtWidgets import QApplication, QDialog, QWidget, QMainWindow
from PyQt5.QtCore import pyqtSlot

from Pyqt_Login.ui_LoginDialog import Ui_Dialog as Ui_Dialog_login
from myDialog_1st_page import QmyDialog as Ui_Dialog_1st_page


# from myWidget_home import QmyWidget as Ui_Widget_homepage

class QmyDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Dialog_login()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面

    ##  ============自定义功能函数========================

    ##  ===========event处理函数==========================

    ##  ========由connectSlotsByName()自动连接的槽函数=========

    @pyqtSlot()
    def on_pushButton_submit_clicked(self):

        # conn = sqlite3.connect('date.db')
        # cur = conn.cursor()
        #
        # cur.execute('''SELECT COUNT(*) FROM Users;''')
        # row_count = int(cur.fetchone()[0])
        #
        # userinfo = [row_count + 100001,
        #             self.ui.lineEdit_name.text(),
        #             self.ui.lineEdit_email.text(),
        #             self.ui.comboBox_sex.currentText(),
        #             self.ui.lineEdit_location.text(),
        #             self.ui.lineEdit_age.text(),
        #             self.ui.lineEdit_workunit.text(),
        #             self.ui.lineEdit_phone.text(),
        #             self.ui.lineEdit_post.text()
        #             ]
        #
        # cur.execute('''INSERT INTO Users(
        #     user_id, user_name, user_email,
        #     user_sex, user_area, user_age,
        #     user_unit, user_phone, user_post)
        #     VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);''', userinfo)
        #
        # conn.commit()
        # conn.close()

        self.close()
        self._firstPage = Ui_Dialog_1st_page()
        self._firstPage.show()

    @pyqtSlot()
    def on_pushButton_back_clicked(self):
        self.close()
        #
        # self._homePage = Ui_Widget_homepage()
        # self._homePage.show()
        # return 0


##  ==========自定义槽函数===============================


##  ============窗体测试程序 ============================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序
    form = QmyDialog()  # 创建窗体
    form.show()
    sys.exit(app.exec_())
