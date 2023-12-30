import sys
import os
from PyQt5.uic import loadUi
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QFileDialog
import sqlite3
from PyQt5.QtWidgets import QWidget
from PyQt5.QtGui import QIcon, QPixmap
from PyQt5.QtCore import QDateTime, Qt, QDate, QTime
from AddRecordWindow import *
from GlobalPath import GlobalPath
class ChangeRecordWindow(QWidget):
    def __init__(self, main):
        super(ChangeRecordWindow, self).__init__()
        loadUi("ui/addrecord.ui",self)
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))
        self.setWindowIcon(icon)
        self.main = main
        self.setWindowTitle("Change")
        self.pushButton.clicked.connect(self.close)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton.clicked.connect(self.ChangeRecordSlot)
        self.pushButton_3.clicked.connect(self.OpenContract)

    def OpenContract(self):
        file , check = QFileDialog.getOpenFileName(None, "QFileDialog.getOpenFileName()","", "Text files (*.pdf *.txt *docx)")
        self.label_10.setText(file)

    def LoadData(self,id):
        self.id_order = id
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        results = now_cursor.execute('SELECT * FROM maintable where id ='+id+';')
        for row in results:
            self.lineEdit.setText(str(row[1]))
            self.lineEdit_2.setText(str(row[2]))
            date = QDate.fromString(row[3], "dd.MM.yyyy")
            self.dateEdit.setDate(date)
            self.lineEdit_5.setText(str(row[4]))
            self.spinBox_3.setValue(row[5])
            self.lineEdit_6.setText(str(row[8]))
            self.label_10.setText(str(row[11]))

    def ChangeRecordSlot(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 

        element_order = self.lineEdit.text()
        element_agreementstatus = self.lineEdit_2.text()
        element_date = self.dateEdit.text()
        element_client = self.lineEdit_5.text()
        element_price = self.spinBox_3.text()
        element_warehouse = self.lineEdit_6.text()
        element_path = self.label_10.text()

        update = """UPDATE maintable SET [order] = ?, agreementstatus = ?, date = ?, client = ?, price = ?, warehouse = ?, path = ? WHERE id = ?"""
        data = (element_order, element_agreementstatus, element_date, element_client, element_price, element_warehouse, element_path,self.id_order)
        now_cursor.execute(update, data)
        connection.commit()
        connection.close()
        self.main.LoadData(self.main.lineEdit.text())

class AddRecordWindow(QWidget):
    def __init__(self, main):
        super(AddRecordWindow, self).__init__()
        loadUi("ui/addrecord.ui",self)

        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))

        self.setWindowIcon(icon)
        self.main = main
        self.setWindowTitle("Add")

        self.pushButton.clicked.connect(self.close)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton.clicked.connect(self.AddRecordSlot)
        self.pushButton_3.clicked.connect(self.OpenContract)

    def OpenContract(self):
        file , check = QFileDialog.getOpenFileName(None, "QFileDialog.getOpenFileName()", "", "Text files (*.pdf *.txt *docx)")
        self.label_10.setText(file)

    def AddRecordSlot(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 

        result = now_cursor.execute('SELECT max(id) FROM maintable')
        n = result.fetchone()[0]
        if n is None:
            element_id = 1
        else:
            element_id = n + 1
        
        element_order = self.lineEdit.text()
        element_agreementstatus = self.lineEdit_2.text()
        element_date = self.dateEdit.text()
        element_client = self.lineEdit_5.text()

        element_price = self.spinBox_3.text()

        element_warehouse = self.lineEdit_6.text()
        element_status = 0
        element_report = 0
        element_path = self.label_10.text()
        now_cursor = connection.cursor() 
        result = now_cursor.execute("""INSERT INTO maintable VALUES 
        (?,?,?,?,?,?,?,?,?,?,?,?,?,?);""",
        (element_id,element_order,element_agreementstatus,element_date,element_client,element_price,0,0,element_warehouse,element_status,element_report,element_path,"",""))

        connection.commit()
        connection.close()

        self.main.RefreshMainTable()

class ChangeUnitWindow(QWidget):
    def __init__(self, main):
        super(ChangeUnitWindow, self).__init__()
        loadUi("ui/addunit.ui",self)
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))
        self.setWindowIcon(icon)
        self.main = main
        self.setWindowTitle("Change")
        
        self.pushButton.clicked.connect(self.close)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton.clicked.connect(self.ChangeRecordSlot)

    def LoadData(self,id):
        self.id_order = id
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        results = now_cursor.execute('SELECT * FROM unittable where id ='+id+';')
        for row in results:
            self.lineEdit.setText(str(row[2]))

    def ChangeRecordSlot(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 

        element_title = self.lineEdit.text()

        update = """UPDATE unittable SET title = ? WHERE id = ?"""
        data = (element_title,self.id_order)
        now_cursor.execute(update, data)
        connection.commit()
        connection.close()
        self.main.RefreshUnitTable()

class AddUnitWindow(QWidget):
    def __init__(self, main):
        super(AddUnitWindow, self).__init__()
        loadUi("ui/addunit.ui",self)

        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))

        self.setWindowIcon(icon)
        self.main = main
        self.setWindowTitle("Add")

        self.pushButton.clicked.connect(self.close)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton.clicked.connect(self.AddRecordSlot)

    def AddRecordSlot(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 

        result = now_cursor.execute('SELECT max(id) FROM unittable')
        n = result.fetchone()[0]
        if n is None:
            element_id = 1
        else:
            element_id = n + 1
        
        element_order_id = self.main.id_order
        element_title = self.lineEdit.text()
        element_status = 0
  

        now_cursor = connection.cursor() 
        result = now_cursor.execute("""INSERT INTO unittable VALUES 
        (?,?,?,?);""",
        (int(element_order_id),element_id,element_title,element_status))

        connection.commit()
        connection.close()

        self.main.RefreshUnitTable()