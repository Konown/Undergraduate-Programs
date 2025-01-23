# -*- coding: utf-8 -*-

import sys
import sqlite3

from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QUrl, pyqtSlot
from PyQt5.QtGui import QDesktopServices

from ui_py.ui_Widget_login import Ui_Widget
from myWidget_1st_page import QmyWidget as QmyWidget_1st_page


class QmyWidget(QWidget):

    def __init__(self, parent=None):
        super().__init__(parent)  # 调用父类构造函数，创建窗体
        self.ui = Ui_Widget()  # 创建UI对象
        self.ui.setupUi(self)  # 构造UI界面

##  =============自定义槽函数===============================


##  ============窗体测试程序 ================================
if __name__ == "__main__":  # 用于当前窗体测试
    app = QApplication(sys.argv)  # 创建GUI应用程序
    # app.setWindowIcon(QIcon('QtProjects/images/Login/WzuModellogo.bmp'))
    form = QmyWidget()  # 创建窗体
    form.show()

    sys.exit(app.exec_())
