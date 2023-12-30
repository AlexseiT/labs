# -*- coding: utf-8 -*-
import sys
import os
import time
import shutil
import pathlib
from PyQt5.uic import loadUi
from PyQt5.QtWebChannel import QWebChannel
from PyQt5.QtWebEngineWidgets import *
from PyQt5 import QtCore
from PyQt5.QtWidgets import QDialog, QApplication, QMainWindow, QFileDialog, QProgressBar, QSplashScreen
import sqlite3
from PyQt5.QtWidgets import QMessageBox, QWidget, QTableWidgetItem, QVBoxLayout, QHBoxLayout, QPushButton, QCheckBox, QHeaderView, QDesktopWidget
from PyQt5.QtGui import QHideEvent, QIcon, QMovie, QPaintEvent, QPainter, QPixmap, QShowEvent, QColor
from PyQt5.QtCore import Qt, QSize, QObject, pyqtSlot, QUrl, QPoint
from AddRecordWindow import *
from GlobalPath import GlobalPath
#from MainTableView import *
class UnitTableView(QDialog):
    def __init__(self,main):
        super(UnitTableView, self).__init__()
        loadUi("ui/unittable.ui",self)
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))
        self.main = main
        self.setWindowIcon(icon)
        self.tableWidget.setHorizontalHeaderLabels(["Номер","Название","Статус"]) 
        self.tableWidget.setColumnHidden(0,True)
        #self.tableWidget.verticalHeader().setVisible(False)
        self.tableWidget.horizontalHeader().setStyleSheet("background-color:#E3E3E3;")
        self.tableWidget.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)
        self.tableWidget.setShowGrid(False)
        self.addrecord = AddUnitWindow(self)
        self.pushButton.clicked.connect(self.OpenAddUnitWindowSlot)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton_3.clicked.connect(self.DeleteSelectOrders)
        self.pushButton_4.clicked.connect(self.OpenChangeWindow)
        self.changeunitwindow = ChangeUnitWindow(self)

        self.pushButton.setIcon(QIcon("Assets/Add.png"))
        self.pushButton.setIconSize(QSize(30,30))
        self.pushButton.setFixedSize(40, 40)

        self.pushButton_3.setIcon(QIcon("Assets/deleteOrder.png"))
        self.pushButton_3.setIconSize(QSize(30,30))
        self.pushButton_3.setFixedSize(40, 40)

        self.pushButton_4.setIcon(QIcon("Assets/change.png"))
        self.pushButton_4.setIconSize(QSize(30,30))
        self.pushButton_4.setFixedSize(40, 40)

    def OpenChangeWindow(self):
        if self.tableWidget.selectionModel().hasSelection():
            row = self.tableWidget.currentRow()
            id = self.tableWidget.item(row,0).text()
            self.changeunitwindow.LoadData(id)
            self.changeunitwindow.show()

    def ChangeStatusUnit(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 
        sender = self.sender()
        status = 0
        results = now_cursor.execute('SELECT * FROM unittable where id = '+sender.objectName()+';')
        for row in results:
            if row[3] == 1:
                status = 0
            else:
                status = 1
        update = """UPDATE unittable SET status = ? WHERE id = ?"""
        data = (status, sender.objectName())
        now_cursor.execute(update, data)
        connection.commit()
        connection.close()
        self.RefreshUnitTable()

    def DeleteSelectOrders(self):
        if self.tableWidget.selectionModel().hasSelection():
            message = QMessageBox
            reply = message.question(self, 'ВНИМАНИЕ !!!',"Вы точно хотите удалить юнит ?", message.Yes | message.No)
            if reply == message.Yes:   
                row = self.tableWidget.currentRow()
                id = self.tableWidget.item(row,0).text()
                connection = sqlite3.connect(GlobalPath.path_data_base)
                now_cursor = connection.cursor()
                delete_record = """DELETE from unittable where id = """ + id
                now_cursor.execute(delete_record)
                connection.commit()
                now_cursor.close()
                self.RefreshUnitTable()

    def DeleteOrders(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        delete_record = """DELETE from unittable where idorder = """ + self.id_order
        now_cursor.execute(delete_record)
        connection.commit()
        now_cursor.close()

    def LoadData(self,id):
        self.id_order = id

        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        results = now_cursor.execute('SELECT * FROM unittable where idorder ='+id+';')
        count_item = len(results.fetchall())
        results = now_cursor.execute('SELECT * FROM unittable where idorder ='+id+';')

        self.tableWidget.setRowCount(count_item)
        tablerow=0
        ready=0
        for row in results:

 
            element_id = QTableWidgetItem()
            element_title = QTableWidgetItem()
            element_status = QTableWidgetItem()


            element_id.setData(Qt.ItemDataRole.DisplayRole, row[1])
            element_title.setData(Qt.ItemDataRole.DisplayRole, row[2]) 
            element_status.setData(Qt.ItemDataRole.DisplayRole, row[3])      
            

            element_id.setFlags(Qt.ItemFlag.ItemIsEditable)
            element_title.setFlags(Qt.ItemFlag.ItemIsEditable)

            checkbox = QCheckBox(objectName = str(row[1]))

            if (row[3] == 1):
                checkbox.setChecked(True)
                ready+=1

            checkbox.clicked.connect(self.ChangeStatusUnit)
            layout = QVBoxLayout()
            layout.addWidget(checkbox)
            cell_widget_ready = QWidget()
            cell_widget_ready.setLayout(layout)

            self.tableWidget.setItem(tablerow, 0, element_id)
            self.tableWidget.setItem(tablerow, 1, element_title)
            self.tableWidget.setItem(tablerow, 2, element_status)
            self.tableWidget.setCellWidget(tablerow, 2, cell_widget_ready)

            tablerow+=1
        self.label_4.setText(str(tablerow))
        self.label_5.setText(str(ready))

    def RefreshUnitTable(self):
        self.LoadData(self.id_order)
        self.main.LoadData(self.main.lineEdit.text())

    def OpenAddUnitWindowSlot(self):
        self.addrecord.show()

class NoteWindow(QWidget):
    def __init__(self):
        super(NoteWindow, self).__init__()
        loadUi("ui/notes.ui",self)

        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))

        self.setWindowIcon(icon)
        self.setWindowTitle("Note")
        self.pushButton.clicked.connect(self.AcceptNote)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton_6.clicked.connect(self.EditNote)
        self.ReadOnly()
        self.pushButton_7.clicked.connect(self.CancelNote)
        self.pushButton_4.clicked.connect(self.DeleteNote)
        self.pushButton_5.clicked.connect(self.OpenNote)
        self.pushButton_3.clicked.connect(self.SaveNote)
        self.pushButton_8.clicked.connect(self.SaveAsNote)
        
    def SaveNote(self):
        text = self.textEdit.toPlainText()
        print(self.file)
        with open(self.file, 'w') as file_write:
            file_write.write(text)

    def SaveAsNote(self):
        file = QFileDialog.getSaveFileName(None,"SaveTextFile","", "Text Files (*.txt)")
        text = self.textEdit.toPlainText()
        if file[0]: 
            with open(file[0], 'w') as file_write:
                file_write.write(text)

    def OpenNote(self):
        file , check = QFileDialog.getOpenFileName(None, "QFileDialog.getOpenFileName()","", "Text files (*.txt)")
        if file != "":
            self.file = file
            text=open(file).read()
            self.textEdit.setPlainText(text)
            self.pushButton_3.setEnabled(True)

    def DeleteNote(self):
        self.textEdit.setText("")

    def CancelNote(self):
        self.ReadOnly()
        self.LoadData(self.id_order)

    def ReadOnly(self):
        self.textEdit.setReadOnly(True)
        self.pushButton_5.setEnabled(False)
        self.pushButton_4.setEnabled(False)
        self.pushButton_7.setEnabled(False)
        self.pushButton_3.setEnabled(False)
        self.textEdit.setStyleSheet("background-color:#E3E3E3;")

    def LoadData(self,id):
        self.id_order = id
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        results = now_cursor.execute('SELECT * FROM maintable where id ='+id+';')
        for row in results:
            self.textEdit.setText(str(row[12]))

    def EditNote(self):
        self.textEdit.setReadOnly(False)
        self.pushButton_5.setEnabled(True)
        self.pushButton_4.setEnabled(True)
        self.pushButton_7.setEnabled(True)
        self.textEdit.setStyleSheet("background-color:white;")

    def AcceptNote(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 
        element_note = self.textEdit.toPlainText()
        update = """UPDATE maintable SET note = ? WHERE id = ?"""
        data = (element_note, self.id_order)
        now_cursor.execute(update, data)
        connection.commit()
        connection.close()
        self.ReadOnly()

class CreateDataBaseWindow(QWidget):
    def __init__(self,main):
        super(CreateDataBaseWindow, self).__init__()
        loadUi("ui/createdatabase.ui",self)
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))
        self.setWindowIcon(icon)
        self.setWindowTitle("Create")
        self.main = main
        self.pushButton.clicked.connect(self.close)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton.clicked.connect(self.CreateDataBase)

    def CreateDataBase(self):
        name = self.lineEdit.text() + '.db'
        shutil.copyfile('__systemdatabase.db', name)
        GlobalPath.path_data_base = name
        self.main.LoadData(self.main.lineEdit.text())
        self.main.BlockButton(True)

class ShippedWindow(QWidget):
    def __init__(self,main):
        super(ShippedWindow, self).__init__()
        loadUi("ui/shipped.ui",self)
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))
        self.setWindowIcon(icon)
        self.setWindowTitle("Shipped")
        self.main = main
        self.pushButton.clicked.connect(self.close)
        self.pushButton.clicked.connect(self.AcceptShipped)
        self.pushButton_2.clicked.connect(self.close)
        self.pushButton_3.clicked.connect(self.close)
        self.pushButton_3.clicked.connect(self.DeleteShipped)

    def DeleteShipped(self):     
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 
        element_shipped = ""
        update = """UPDATE maintable SET shipped = ?, status = ? WHERE id = ?"""
        data = (element_shipped,0,self.id_order)
        now_cursor.execute(update, data)
        connection.commit()
        connection.close()
        self.main.LoadData(self.main.lineEdit.text())
        
    def AcceptShipped(self):
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor() 
        element_shipped = self.lineEdit.text()
        update = """UPDATE maintable SET shipped = ?, status = ? WHERE id = ?"""
        data = (element_shipped,1,self.id_order)
        now_cursor.execute(update, data)
        connection.commit()
        connection.close()
        self.main.LoadData(self.main.lineEdit.text())

    def LoadData(self,id):
        self.id_order = id
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        results = now_cursor.execute('SELECT * FROM maintable where id ='+id+';')
        for row in results:
            self.label_3.setText(str(row[8]))
            self.lineEdit.setText(str(row[13]))

class HtmlWindow(QMainWindow):
    def __init__(self):
        super(HtmlWindow, self).__init__()
        self.setWindowTitle('Справка')
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/info.png"))
        self.setWindowIcon(icon)
        self.setGeometry(5,30,900,730)
        self.browser=QWebEngineView()
        self.browser.load(QUrl('file:///' + os.path.abspath("HTML/index.html").replace("\\","/")))
        self.setCentralWidget(self.browser)
        self.button = QPushButton('Выйти из справки', self)
        self.button.setFixedSize(100,50)
        self.button.move(800, 680) 
        self.button.clicked.connect(self.close)
     
class MainTableView(QDialog):
    def __init__(self):
        super(MainTableView, self).__init__()
        loadUi("ui/table.ui",self)
        self.tableWidget.setHorizontalHeaderLabels(["Номер","Заказ","Договор","Дата","Заказчик","Цена","Всего","Готово","Склад","Статус","Заметки","Ссылка"])
        self.tableWidget.setColumnHidden(0,True)
        self.tableWidget.setColumnHidden(11,True)
        #self.tableWidget.verticalHeader().setVisible(False)
        self.tableWidget.horizontalHeader().setStyleSheet("background-color:#B9EC87;")
        self.tableWidget.verticalHeader().setStyleSheet("background-color:#B9EC87;")
        self.tableWidget.setStyleSheet("selection-background-color:#B9EC87; selection-color:black;") 
        self.tableWidget.setShowGrid(False)
        self.tableWidget.verticalHeader().setDefaultSectionSize(45)  
        self.tableWidget.horizontalHeader().setSectionResizeMode(1, QHeaderView.ResizeMode.Stretch)
        self.pushButton_7.clicked.connect(self.ButtonDelete)
        self.pushButton_8.clicked.connect(self.ButtonOpenUnits)
        self.pushButton.clicked.connect(self.SearchClient)
        self.pushButton_9.clicked.connect(self.ButtonOpenContract)
        self.pushButton_10.clicked.connect(self.ButtonOpenChangeRecord)
        self.pushButton_11.clicked.connect(self.ButtonOpenShipped)
        self.pushButton_2.clicked.connect(self.SearchClear)
        self.pushButton_5.clicked.connect(self.OpenDataBase)
        self.pushButton_12.clicked.connect(self.CreateDataBase)
        self.pushButton_5.clicked.connect(self.CheckDataBaseDefault)
        self.pushButton_12.clicked.connect(self.CheckDataBaseDefault)
        self.pushButton_4.clicked.connect(self.OpenHtmlWindow)

        self.radioButton.clicked.connect(self.SearchClient)
        self.radioButton_2.clicked.connect(self.SearchClient)
        self.radioButton_3.clicked.connect(self.SearchClient)
        self.radioButton_4.clicked.connect(self.SearchClient)

        self.pushButton_7.setIcon(QIcon("Assets/deleteOrder.png"))
        self.pushButton_7.setIconSize(QSize(30,30))
        self.pushButton_7.setFixedSize(40, 40)

        self.pushButton_6.setIcon(QIcon("Assets/Add.png"))
        self.pushButton_6.setIconSize(QSize(30,30))
        self.pushButton_6.setFixedSize(40, 40)

        self.pushButton_11.setIcon(QIcon("Assets/shippedStart.png"))
        self.pushButton_11.setIconSize(QSize(30,30))
        self.pushButton_11.setFixedSize(40, 40)

        self.pushButton_10.setIcon(QIcon("Assets/change.png"))
        self.pushButton_10.setIconSize(QSize(30,30))
        self.pushButton_10.setFixedSize(40, 40)

        self.pushButton_8.setIcon(QIcon("Assets/openunit.png"))
        self.pushButton_8.setIconSize(QSize(30,30))
        self.pushButton_8.setFixedSize(40, 40)

        self.pushButton_9.setIcon(QIcon("Assets/agreement.png"))
        self.pushButton_9.setIconSize(QSize(30,30))
        self.pushButton_9.setFixedSize(40, 40)

        self.BlockButton(False)

        self.pushButton_4.setIcon(QIcon("Assets/info.png"))
        self.pushButton_4.setIconSize(QSize(30,30))
        self.pushButton_4.setFixedSize(40, 40)

        self.unittable = UnitTableView(self)
        self.changewindow = ChangeRecordWindow(self)
        self.notewindow = NoteWindow()
        self.shippedwindow = ShippedWindow(self)
        self.createdatabase = CreateDataBaseWindow(self)
        self.htmlwindow = HtmlWindow()

    def OpenHtmlWindow(self):
        self.htmlwindow.show()

    def BlockButton(self,check):
        self.pushButton_7.setEnabled(check)
        self.pushButton_6.setEnabled(check)
        self.pushButton_11.setEnabled(check)
        self.pushButton_10.setEnabled(check)
        self.pushButton_8.setEnabled(check)
        self.pushButton_9.setEnabled(check)

    def CheckDataBaseDefault(self):
        path = pathlib.PurePath(GlobalPath.path_data_base)
        if path.name != '__systemdatabase.db' and path.name != "":
            self.BlockButton(True)
        else:
            self.BlockButton(False)

    def CreateDataBase(self):
        self.createdatabase.show()

    def OpenDataBase(self):
        file , check = QFileDialog.getOpenFileName(None, "QFileDialog.getOpenFileName()","", "All Files (*.db)")
        if file != '':
            GlobalPath.path_data_base = file
            self.LoadData(self.lineEdit.text())

    def SearchClear(self):
        self.lineEdit.setText('')
        self.LoadData('')

    def ButtonResultShipped(self,button):
        sender = self.sender()
        id = sender.objectName()
        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()
        results = now_cursor.execute('SELECT * FROM maintable where id ='+id+';')
        for row in results:
            QMessageBox.information(self, "Shipped", "Отгружено: " + str(row[13]))

    def ButtonOpenShipped(self,button):
        if self.tableWidget.selectionModel().hasSelection():
            row = self.tableWidget.currentRow()
            id = self.tableWidget.item(row,0).text()
            self.shippedwindow.LoadData(id)
            self.shippedwindow.show()

    def ButtonOpenNote(self,button):
        sender = self.sender()
        id = sender.objectName()
        self.notewindow.LoadData(id)
        self.notewindow.show()

    def ButtonOpenChangeRecord(self):
        if self.tableWidget.selectionModel().hasSelection():
            row = self.tableWidget.currentRow()
            id = self.tableWidget.item(row,0).text()
            self.changewindow.LoadData(id)
            self.changewindow.show()

    def ButtonOpenContract(self):
        if self.tableWidget.selectionModel().hasSelection():
            row = self.tableWidget.currentRow()
            path = self.tableWidget.item(row,11).text()
            if path != "":
                os.startfile(path)

    def SearchClient(self):
        self.LoadData(self.lineEdit.text())

    def ButtonDelete(self):
        if self.tableWidget.selectionModel().hasSelection():
            message = QMessageBox
            reply = message.question(self, 'ВНИМАНИЕ !!!',"Вы точно хотите удалить запись ?", message.Yes | message.No) #Исправить для остальных!!!
            #choice = reply.value
            if reply == message.Yes:
                row = self.tableWidget.currentRow()
                id = self.tableWidget.item(row,0).text()
                connection = sqlite3.connect(GlobalPath.path_data_base)
                now_cursor = connection.cursor()
                delete_record = """DELETE from maintable where id = """ + id
                now_cursor.execute(delete_record)
                connection.commit()
                delete_record = """DELETE from unittable where idorder = """ + id
                now_cursor.execute(delete_record)
                connection.commit()
                now_cursor.close()
                self.LoadData(self.lineEdit.text())

    def ButtonOpenUnits(self):
        if self.tableWidget.selectionModel().hasSelection():
            row = self.tableWidget.currentRow()
            id = self.tableWidget.item(row,0).text()
            self.unittable.LoadData(id)
            self.unittable.show()
            self.LoadData(self.lineEdit.text())


    def ButtonDeleteClickedSlot(self):
        reply = QMessageBox.question(self, 'Внимание',"Вы точно хотите удалить запись ?", QMessageBox.Yes, QMessageBox.No)
        if reply == QMessageBox.Yes:
            sender = self.sender()
            connection = sqlite3.connect(GlobalPath.path_data_base)
            now_cursor = connection.cursor()
            delete_record = """DELETE from maintable where id = """ + sender.text()
            now_cursor.execute(delete_record)
            connection.commit()
            delete_record = """DELETE from unittable where idorder = """ + sender.text()
            now_cursor.execute(delete_record)
            connection.commit()
            now_cursor.close()
            self.LoadData(self.lineEdit.text())

    def LoadData(self,values):
        self.tableWidget.setRowCount(0);

        connection = sqlite3.connect(GlobalPath.path_data_base)
        now_cursor = connection.cursor()

        results = now_cursor.execute("SELECT * FROM maintable where id = -1")
        count_item = len(results.fetchall())
        results = now_cursor.execute("SELECT * FROM maintable where id = -1")

        if values == '':
            results = now_cursor.execute('SELECT * FROM maintable ;')
            count_item = len(results.fetchall())
            results = now_cursor.execute('SELECT * FROM maintable ;')
        else:
            results = now_cursor.execute("SELECT * FROM maintable where client = '%s'" % values)
            count_item = len(results.fetchall())
            results = now_cursor.execute("SELECT * FROM maintable where client = '%s'" % values)

        self.tableWidget.setRowCount(count_item)
        tablerow=0
        tableeditrow=0
        for row in results:

            new_connection = sqlite3.connect(GlobalPath.path_data_base)
            new_now_cursor = new_connection.cursor()
            result_unit = new_now_cursor.execute('SELECT * FROM unittable where idorder ='+str(row[0])+';')
            count_unit = len(result_unit.fetchall())

            result_unit = new_now_cursor.execute('SELECT * FROM unittable where idorder ='+str(row[0])+' and status = 1;')
            count_ready = len(result_unit.fetchall())

            checker = True

            if (self.radioButton.isChecked() == True and count_ready == count_unit):
                checker = False
                if (count_ready == 0 and count_unit == 0):
                    checker = True
            if (self.radioButton_2.isChecked() == True and (count_ready != count_unit or count_ready == 0 and count_unit == 0)):
                checker = False
            if (self.radioButton_3.isChecked() == True and row[9] != 1):
                checker = False

            if checker == True:
                element_id = QTableWidgetItem()
                element_order = QTableWidgetItem()
                element_agreementstatus = QTableWidgetItem()
                element_date = QTableWidgetItem()
                element_client = QTableWidgetItem()
                element_price = QTableWidgetItem()
                element_all = QTableWidgetItem()
                element_ready = QTableWidgetItem()
                element_warehouse = QTableWidgetItem()
                element_status = QTableWidgetItem()
                element_report = QTableWidgetItem()
                element_path = QTableWidgetItem()

                element_order.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_agreementstatus.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_date.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_client.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_price.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_all.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_ready.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_warehouse.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_status.setFlags(Qt.ItemFlag.ItemIsEditable)
                element_report.setFlags(Qt.ItemFlag.ItemIsEditable)

                element_id.setData(Qt.ItemDataRole.DisplayRole, row[0]) 
                element_order.setData(Qt.ItemDataRole.DisplayRole, row[1])
                element_agreementstatus.setData(Qt.ItemDataRole.DisplayRole, row[2]) 
                element_date.setData(Qt.ItemDataRole.DisplayRole, row[3])
                element_client.setData(Qt.ItemDataRole.DisplayRole, row[4]) 
                element_price.setData(Qt.ItemDataRole.DisplayRole, row[5])
                element_all.setData(Qt.ItemDataRole.DisplayRole, count_unit)
                element_ready.setData(Qt.ItemDataRole.DisplayRole, count_ready) 
                element_warehouse.setData(Qt.ItemDataRole.DisplayRole, row[8])
                element_status.setData(Qt.ItemDataRole.DisplayRole, row[9]) 
                element_report.setData(Qt.ItemDataRole.DisplayRole, row[10])
                element_path.setData(Qt.ItemDataRole.DisplayRole, row[11]) 
                #
                element_id.setForeground(QColor(0, 0, 0))
                element_order.setForeground(QColor(0, 0, 0))
                element_agreementstatus.setForeground(QColor(0, 0, 0)) 
                element_date.setForeground(QColor(0, 0, 0))
                element_client.setForeground(QColor(0, 0, 0)) 
                element_price.setForeground(QColor(0, 0, 0))
                element_all.setForeground(QColor(0, 0, 0))
                element_ready.setForeground(QColor(0, 0, 0)) 
                element_warehouse.setForeground(QColor(0, 0, 0))
                element_status.setForeground(QColor(0, 0, 0)) 
                element_report.setForeground(QColor(0, 0, 0))
                element_path.setForeground(QColor(0, 0, 0)) 

                color_ready = QtWidgets.QLabel()
                if count_unit == count_ready:
                    color_ready.setStyleSheet("background-color:#B9EC87;")
                    color_ready.setFixedSize(80,5)
                if count_unit > count_ready:
                    color_ready.setStyleSheet("background-color:#FADE97;")
                    color_ready.setFixedSize(count_ready*80/count_unit,5)
                if count_ready == 0:
                    color_ready.setStyleSheet("background-color:#F58686;")
                    color_ready.setFixedSize(10,5)
                if count_unit == 0:
                    color_ready.setFixedSize(0,0)

                text_id = QtWidgets.QLabel(str(row[0]))
                layout = QHBoxLayout()
                cell_widget_ready = QWidget()

                self.tableWidget.setItem(tablerow, 0, element_id)
                self.tableWidget.setItem(tablerow, 1, element_order)
                self.tableWidget.setItem(tablerow, 2, element_agreementstatus)
                self.tableWidget.setItem(tablerow, 3, element_date)
                self.tableWidget.setItem(tablerow, 4, element_client)
                self.tableWidget.setItem(tablerow, 5, element_price)
                self.tableWidget.setItem(tablerow, 6, element_all)

                text_ready = QtWidgets.QLabel(str(count_ready))
                layout = QVBoxLayout()
                layout.addWidget(text_ready)
                layout.addWidget(color_ready)
                cell_widget_ready = QWidget()
                cell_widget_ready.setLayout(layout)

                self.tableWidget.setItem(tablerow, 7, element_ready)
                self.tableWidget.setCellWidget(tablerow, 7, cell_widget_ready)

                self.tableWidget.setItem(tablerow, 8, element_warehouse)

                if (row[9] == 1):
                    button = QPushButton(objectName = str(row[0]))
                    button.clicked.connect(lambda: self.ButtonResultShipped(button))
                    button.setIcon(QIcon("Assets/shipped.png"))
                    button.setIconSize(QSize(25,25))
                    button.setFixedSize(35, 35)
                    layout = QHBoxLayout()
                    text = QtWidgets.QLabel("")
                    layout.addWidget(text)
                    layout.addWidget(button)
                    cell_widget_ready = QWidget()
                    cell_widget_ready.setLayout(layout)
                    self.tableWidget.setCellWidget(tablerow, 9, cell_widget_ready)
                else:
                    layout = QHBoxLayout()
                    text = QtWidgets.QLabel("")
                    layout.addWidget(text)
                    cell_widget_ready = QWidget()
                    cell_widget_ready.setLayout(layout)
                    self.tableWidget.setCellWidget(tablerow, 9, cell_widget_ready)

                button = QPushButton(objectName = str(row[0]))
                button.clicked.connect(lambda: self.ButtonOpenNote(button))
                button.setIcon(QIcon("Assets/note.png"))
                button.setIconSize(QSize(35,35))
                button.setFixedSize(35, 35)

                layout = QHBoxLayout()
                text = QtWidgets.QLabel("")
                layout.addWidget(text)
                layout.addWidget(button)
                cell_widget_ready = QWidget()
                cell_widget_ready.setLayout(layout)

                self.tableWidget.setItem(tablerow, 10, element_report)
                self.tableWidget.setCellWidget(tablerow, 10, cell_widget_ready)

                self.tableWidget.setItem(tablerow, 11, element_path)

                tableeditrow+=1
            else:
                self.tableWidget.hideRow(tablerow)
            header = QTableWidgetItem()
            header.setData(Qt.ItemDataRole.DisplayRole, tableeditrow) 
            self.tableWidget.setVerticalHeaderItem(tablerow,header)
            tablerow+=1

class SplashScreen(QSplashScreen):
    
    def __init__(self, path: str):
        self.size = QSize(600,600)
        self.path = "Assets/spinner.gif" 
        self.movie = QMovie(path)
        self.movie.jumpToFrame(0)
        pixmap = QPixmap(self.size)
        QSplashScreen.__init__(self, pixmap)
        self.movie.frameChanged.connect(self.repaint)

    def showEvent(self, event: QShowEvent) -> None:
        self.movie.start()

    def hideEvent(self, event: QHideEvent) -> None:
        self.movie.stop()

    def paintEvent(self, event: QPaintEvent) -> None:
        painter = QPainter(self)
        pixmap = self.movie.currentPixmap()
        pixmap = pixmap.scaled(self.size)
        painter.drawPixmap(0,0,pixmap)

class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        loadUi("ui/mainwindow.ui",self)

        self.setWindowTitle("WStatus")
        icon = QIcon()
        icon.addPixmap(QPixmap("Assets/icon.png"))
        self.setWindowIcon(icon)

        self.maintable = MainTableView()
        self.maintable.LoadData('')

        self.widget = QtWidgets.QStackedWidget()
        self.widget.addWidget(self.maintable)
        self.widget.addWidget(self.maintable)
        self.widget.setFixedHeight(540)
        self.widget.setFixedWidth(1103)
        self.setCentralWidget(self.widget)

        self.addrecord = AddRecordWindow(self)
        self.maintable.pushButton_6.clicked.connect(self.OpenAddRecordWindowSlot)
        self.maintable.pushButton_3.clicked.connect(self.close)

    def OpenAddRecordWindowSlot(self):
        self.addrecord.show()
        self.RefreshMainTable()

    def RefreshMainTable(self):
        self.maintable.LoadData(self.maintable.lineEdit.text())
        self.widget.addWidget(self.maintable)
        self.widget.addWidget(self.maintable)
        self.setCentralWidget(self.widget)


def main(): 

    app = QApplication(sys.argv)

    splash = SplashScreen('Assets/icon.png')
    progressbar = QProgressBar(splash)
    progressbar.setMaximum(10)
    progressbar.setTextVisible(False)
    progressbar.setGeometry(40, splash.size.height() - 50, splash.size.width()-80, 20)
    progressbar.setStyleSheet("QProgressBar::chunk "
                        "{"
                        "background-color: #B9EC87;"
                        "}")
    splash.show()
    for i in range(10):
        progressbar.setValue(i)
        t = time.time()
        while time.time() < t + 0.1:
            app.processEvents()
    time.sleep(1)
    window = MainWindow()
    window.show()
    splash.finish(window)
    try:
        sys.exit(app.exec())
    except:
        print("Exit")

if __name__ == "__main__": 
    main() 