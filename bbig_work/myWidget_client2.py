# -*- coding: utf-8 -*-

import sys
import random
import time

from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QUrl, pyqtSlot, QTimer
from PyQt5.QtGui import QDesktopServices

import pyqtgraph as pg

import globalvar
from ui_py.ui_client2 import Ui_Widget
from sqlite_project.UserData import gainCarData
import globalvar as gl

class QmyWidget(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Widget()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面
        self.setWindowTitle("Client")
        self.ui.lineEdit_Send.setPlaceholderText(u"请输入发送内容")

        self.client = gl.client

        # 定时器
        self.timer = QTimer()
        self.timer.timeout.connect(self.update)
        self.flag_timer = 0

        self.timer_msg = QTimer()
        self.timer_msg.timeout.connect(self.update_msg)
        self.timer_msg.start(20)

        # 画图
        self.line_pitch = []
        self.axis_x = []
        self.line_pos = -0.2

        self.ui.graphicsView_2.setXRange(0, 30, padding=0.02)
        self.ui.graphicsView_2.enableAutoRange(axis='x')
        self.ui.graphicsView_2.setYRange(-10, 10, padding=0.1)
        self.ui.graphicsView_2.enableAutoRange(axis='y')
        self.ui.graphicsView_2.setAutoPan(x=True, y=True)
        self.curve1 = self.ui.graphicsView_2.plot()
        self.curve1.setPen((255, 0, 0), width=2)
        self.ui.graphicsView_2.plotItem.showGrid(True, True)
        self.ui.graphicsView_2.plotItem.setLabel('left', text='Pitch', units='%')
        self.ui.graphicsView_2.plotItem.setLabel('bottom', text='Time', units='s')

    pg.setConfigOption('background', 'w')
    pg.setConfigOption('foreground', 'k')

    ##  =============自定义槽函数==============================
    # 请求数据库查找
    @pyqtSlot()
    def on_pushButton_check_clicked(self):
        # _url = QUrl('https://www.bing.com')
        # QDesktopServices.openUrl(_url)
        self.client.sql_query()


    # 绘图
    @pyqtSlot()
    def on_pushButton_draw_2_clicked(self):
        if self.flag_timer == 0:
            self.timer.start(50)
            self.ui.pushButton_draw_2.setText("停止绘制")
            self.flag_timer = 1
        elif self.flag_timer == 1:
            self.timer.stop()
            self.ui.pushButton_draw_2.setText("继续绘制")
            self.flag_timer = 0


    # 页面切换
    @pyqtSlot()
    def on_pushButton_next_clicked(self):
        self.ui.stackedWidget.setCurrentIndex(0)

    @pyqtSlot()
    def on_pushButton_previous_clicked(self):
        self.ui.stackedWidget.setCurrentIndex(2)


    # 控制小车运动
    @pyqtSlot()
    def on_pushButton_forward_clicked(self):
        self.client.car_forward()

    @pyqtSlot()
    def on_pushButton_back_clicked(self):
        self.client.car_back()

    @pyqtSlot()
    def on_pushButton_left_clicked(self):
        self.client.car_left()

    @pyqtSlot()
    def on_pushButton_right_clicked(self):
        self.client.car_right()

    @pyqtSlot()
    def on_pushButton_stop_clicked(self):
        self.client.car_stop()


    # 文本流信息传输
    @pyqtSlot()
    def on_pushButton_sendMs_clicked(self):
        pack_str = str(10) + time.strftime("%x\t%X") + "\n" + self.ui.lineEdit_Send.text()
        self.client.send_msg_text(pack_str)
        self.ui.lineEdit_Send.clear()

    ## =============自定义函数==================================
    def update(self):
        # num = random.randint(0, 100)
        if self.client.pitch_new == 1:
            self.client.pitch_new = 0
            self.line_pitch.append(self.client.pitch)
            self.line_pos += 0.2
            self.axis_x.append(self.line_pos)
            self.curve1.setData(y=self.line_pitch, x=self.axis_x)

    def update_msg(self):
        if self.client.rece_info:
            self.ui.textBrowser_Receive.append(self.client.rece_info)
            self.client.rece_info = ""

##  ============窗体测试程序 ================================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序
    # app.setWindowIcon(QIcon('QtProjects/images/Login/cjluModellogo.bmp'))
    form = QmyWidget()  # 创建窗体
    form.show()

    sys.exit(app.exec_())
