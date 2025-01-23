# -*- coding: utf-8 -*-

import sys
import sqlite3

from PyQt5.QtWidgets import *
from PyQt5.QtCore import pyqtSlot
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

from Pyqt_Mainwindows.ui_FirstPageMainWindow import Ui_MainWindow
from myDialog_interview import QmyDialog as QmyDialog_interview
from myDialog_picturePorjection import QmyDialog as QmyDialog_pictureProjection
from myDialog_situationalEvaluation import QmyDialog as QmyDialog_situationalEvaluation
from Sqlite_Projects.gain_userinfo import gain_userInformation
from Sqlite_Projects.gain_id_interview import gainIdInterview
from Sqlite_Projects.gain_id_picpro import gainIdPicpro
from Sqlite_Projects.gain_id_siteva import gainIdSitEva
from DrawProjects.interview_draw_projection import fig_output_A
from DrawProjects.picpro_draw_projection import fig_output_B
from DrawProjects.siteva_draw_projection import fig_output_C


class QmyMainWindow(QMainWindow):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_MainWindow()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面

    ##  ==============自定义功能函数========================

    ##  ==============event处理函数==========================

    ##  ==========由connectSlotsByName()自动连接的槽函数============

    ##  =============自定义槽函数===============================
    @pyqtSlot()
    def on_pushButton_interview_clicked(self):
        self._form = QmyDialog_interview()  # 创建窗体
        self._form.ui.stackedWidget.setCurrentIndex(0)
        self._form.show()

    @pyqtSlot()
    def on_pushButton_interview_out_clicked(self):
        if gainIdInterview():
            if gainIdInterview()[0] == gain_userInformation()[0]:
                self._form = QmyDialog_interview()  # 创建窗体
                # 绘制结果报告
                _scene = QGraphicsScene()
                self._form.ui.graphicsView_interview_picout.setScene(_scene)
                _canvas = FigureCanvas(fig_output_A())
                _proxy_widget = QGraphicsProxyWidget()
                _proxy_widget.setWidget(_canvas)
                _scene.addItem(_proxy_widget)

                self._form.ui.stackedWidget.setCurrentIndex(21)
                self._form.show()
            else:
                self._msb = QMessageBox().information(self, "提示", "您尚未完成结构化面试环节，无法查看报告。")
        else:
            self._msb = QMessageBox().information(self, "提示", "您尚未完成结构化面试环节，无法查看报告。")

    @pyqtSlot()
    def on_pushButton_projection_clicked(self):
        self._form = QmyDialog_pictureProjection()  # 创建窗体
        self._form.ui.stackedWidget.setCurrentIndex(0)
        self._form.show()

    @pyqtSlot()
    def on_pushButton_projection_out_clicked(self):
        if gainIdPicpro():
            if gainIdPicpro()[0] == gain_userInformation()[0]:
                self._form = QmyDialog_pictureProjection()  # 创建窗体

                # 绘制结果报告
                _scene = QGraphicsScene()
                self._form.ui.graphicsView_picpro_picout.setScene(_scene)
                _canvas = FigureCanvas(fig_output_B())
                _proxy_widget = QGraphicsProxyWidget()
                _proxy_widget.setWidget(_canvas)
                _scene.addItem(_proxy_widget)

                self._form.ui.stackedWidget.setCurrentIndex(44)
                self._form.show()
            else:
                self._msb = QMessageBox().information(self, "提示", "您尚未完成图片投射测评环节，无法查看报告。")
        else:
            self._msb = QMessageBox().information(self, "提示", "您尚未完成图片投射测评环节，无法查看报告。")

    @pyqtSlot()
    def on_pushButton_evaluation_clicked(self):
        self._form = QmyDialog_situationalEvaluation()
        self._form.ui.stackedWidget.setCurrentIndex(0)
        self._form.show()

    @pyqtSlot()
    def on_pushButton_evaluation_out_clicked(self):
        if gainIdSitEva():
            if gainIdSitEva()[0] == gain_userInformation()[0]:
                self._form = QmyDialog_situationalEvaluation()  # 创建窗体

                # 绘制结果报告
                _scene = QGraphicsScene()
                self._form.ui.graphicsView_evaluation_picout.setScene(_scene)
                _canvas = FigureCanvas(fig_output_C())
                _proxy_widget = QGraphicsProxyWidget()
                _proxy_widget.setWidget(_canvas)
                _scene.addItem(_proxy_widget)

                self._form.ui.stackedWidget.setCurrentIndex(6)
                self._form.show()
            else:
                self._msb = QMessageBox().information(self, "提示", "您尚未完成情境评价测试环节，无法查看报告。")
        else:
            self._msb = QMessageBox().information(self, "提示", "您尚未完成情境评价测试环节，无法查看报告。")

##  ============窗体测试程序 ================================


if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序
    form = QmyMainWindow()  # 创建窗体
    form.show()
    sys.exit(app.exec_())
