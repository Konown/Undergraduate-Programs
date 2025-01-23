
copy QtProjects/MainWindow/FirstPage/MainWindow.ui FirstPageMainWindow.ui

pyuic5 -o ui_py/ui_client1.py client1/widget.ui

pyrcc5 -o img_rc.py client1/img.qrc