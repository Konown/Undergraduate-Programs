# -*- coding: utf-8 -*-

import sys

from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QUrl, pyqtSlot
from PyQt5.QtGui import QDesktopServices

from Pyqt_Login.ui_HomeWidget import Ui_Widget as Ui_Widget_home
from myDialog_meta import QmyDialog as Ui_Dialog_login
from Sqlite_Projects.build_database import buildDatabase


class QmyWidget(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Widget_home()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面

    ##  ==============自定义功能函数========================

    ##  ==============event处理函数==========================

    ##  ==========由connectSlotsByName()自动连接的槽函数============

    @pyqtSlot()
    def on_personalLoginButton_clicked(self):
        self.hide()
        buildDatabase()
        self._loginPage = Ui_Dialog_login()
        self._loginPage.show()
        # self._loginPage.exec_()
        # self.show()

    @pyqtSlot()
    def on_contactButton_clicked(self):
        _url = QUrl('https://www.wenzhoumodel.com')
        QDesktopServices.openUrl(_url)

    @pyqtSlot()
    def on_homeQuitButton_clicked(self):
        self.close()


##  =============自定义槽函数===============================


##  ============窗体测试程序 ================================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序
    # app.setWindowIcon(QIcon('QtProjects/images/Login/WzuModellogo.bmp'))
    form = QmyWidget()  # 创建窗体
    form.show()

    sys.exit(app.exec_())
