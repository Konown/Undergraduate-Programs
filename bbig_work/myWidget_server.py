# -*- coding: utf-8 -*-

import sys
import sqlite3
import socket
import time

from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QUrl, pyqtSlot, QTimer
from PyQt5.QtGui import QDesktopServices

from ui_py.ui_server import Ui_Widget
from mysocket.server_socket import Server


class QmyWidget(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Widget()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面
        self.setWindowTitle("Server")
        self.ui.lineEdit_send.setPlaceholderText(u"输入发送内容")

        self.timer = QTimer()
        self.timer.timeout.connect(self.update)
        self.timer.start(50)

        self.server = Server()

    ## =============自定义函数==================================
    def update(self):
        # 网络连接框
        if self.server.con_info:
            self.ui.textBrowser_connect.append(self.server.con_info + "已登录")
            self.server.con_info = ""
        if self.server.con_disinfo:
            self.ui.textBrowser_connect.append(self.server.con_disinfo + "已退出")
            self.server.con_disinfo = ""

        # 消息发送框
        if self.server.rece_info:
            self.ui.textBrowser_Rece.append(self.server.rece_info)
            self.server.rece_info = ""


##  =============自定义槽函数===============================
    @pyqtSlot()
    def on_pushButton_send_clicked(self):
        self.server.send_msg_client(str(10) + time.strftime("%x\t%X") + "\n" + self.ui.lineEdit_send.text())
        self.ui.lineEdit_send.clear()

##  ============窗体测试程序 ================================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序

    form = QmyWidget()  # 创建窗体
    form.show()

    sys.exit(app.exec_())
