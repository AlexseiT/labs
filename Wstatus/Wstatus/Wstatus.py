# -*- coding: utf-8 -*-

import sys
import sqlite3
from sqlite3 import Error
from PyQt6.QtWidgets import QApplication, QMessageBox, QLabel, QTableWidget, QWidget, QTableWidgetItem, QVBoxLayout, QWidgetAction
from PyQt6.QtGui import QIcon
from PyQt6.QtCore import pyqtSlot

data = {'col1':['1','2','3','4'],
        'col2':['1','2','1','3'],
        'col3':['1','1','2','1']}

class TableView(QTableWidget):
    def __init__(self, data, *args):
        QTableWidget.__init__(self, *args)
        self.data = data
        self.setData()
        self.resizeColumnsToContents()
        self.resizeRowsToContents()
 
    def setData(self): 
        horHeaders = []
        for n, key in enumerate(sorted(self.data.keys())):
            horHeaders.append(key)
            for m, item in enumerate(self.data[key]):
                newitem = QTableWidgetItem(item)
                self.setItem(m, n, newitem)
        self.setHorizontalHeaderLabels(horHeaders)

def main(): 
    conn = sqlite3.connect('DataBase.db')
    cur = conn.cursor()

    #user = ('2', '500')
    #cur.execute("INSERT INTO main VALUES(?, ?);", user)
    #conn.commit()

    cur.execute("SELECT * FROM main;")
    all_results = cur.fetchall()
    print(all_results)
    print(len(all_results))
    print(data)
    app = QApplication(sys.argv)
    table = TableView(data, 4, 3)
    table.show()
    sys.exit(app.exec())



if __name__ == "__main__": 
    main() 
