# -*- coding: utf-8 -*-

import sys
import sqlite3
import socket
from threading import Thread

from PyQt5.QtWidgets import QApplication, QWidget, QMessageBox
from PyQt5.QtCore import QUrl, pyqtSlot
from PyQt5.QtGui import QDesktopServices

from ui_py.ui_client1 import Ui_Widget
from myWidget_client2 import QmyWidget as QmyWWidget_Client2
from mysocket.client_socket import Client
import globalvar as gl
from sqlite_project.buildDatebase import clearDatabase_car

class QmyWidget(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Widget()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面
        self.setWindowTitle("Client_Login")

        gl.client = Client()
        self.client = gl.client

    ##  =============自定义槽函数===============================

    ##  =============自定义槽函数===============================

    @pyqtSlot()
    def on_pushButto_login_close_clicked(self):
        self.close()

    @pyqtSlot()
    def on_pushButton_login_enter_clicked(self):
        user_name = self.ui.lineEdit_users.text()
        user_password = self.ui.lineEdit_login_password.text()
        self.client.send_msg_text(user_name + "+" + user_password)
        while self.client.flag_login == 0:
            pass

        if self.client.flag_login == 1:
            QMessageBox.information(self, "很悲伤", "输入正确")
        elif self.client.flag_login == 2:
            QMessageBox.warning(self, "恭喜你", "密码错误")
        elif self.client.flag_login == 3:
            QMessageBox.critical(self, "祝贺你", "用户名不存在")

        if self.client.flag_login == 1:
            self._ui = QmyWWidget_Client2()
            clearDatabase_car()
            self._ui.show()
            self.close()

        self.client.flag_login = 0


##  ============窗体测试程序 ================================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序
    # app.setWindowIcon(QIcon('QtProjects/images/Login/WzuModellogo.bmp'))
    form = QmyWidget()  # 创建窗体
    form.show()

    sys.exit(app.exec_())
