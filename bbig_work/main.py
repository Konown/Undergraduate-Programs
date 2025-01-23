import sys
from PyQt5.QtWidgets import QApplication
from myWidget_client1 import QmyWidget as QmyWidget_Client1
from myWidget_server import QmyWidget as QmyWidget_Server


app = QApplication(sys.argv)
mainform_server = QmyWidget_Server()
mainform_server.show()
mainform_client1 = QmyWidget_Client1()
mainform_client1.show()
sys.exit(app.exec_())

