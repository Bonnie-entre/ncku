# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'hw1.ui'
#
# Created by: PyQt5 UI code generator 5.15.7
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(400, 600)
        self.groupBox = QtWidgets.QGroupBox(Form)
        self.groupBox.setGeometry(QtCore.QRect(20, 40, 260, 460))
        self.groupBox.setObjectName("groupBox")        
        self.Button11_1 = QtWidgets.QPushButton(Form)
        self.Button11_1.setGeometry(QtCore.QRect(40, 160, 222, 34))
        self.Button11_1.setObjectName("Button11_1")
        self.Button11_2 = QtWidgets.QPushButton(Form)
        self.Button11_2.setGeometry(QtCore.QRect(40, 240, 222, 34))
        self.Button11_2.setObjectName("Button11_2")
        self.Button11_3 = QtWidgets.QPushButton(Form)
        self.Button11_3.setGeometry(QtCore.QRect(40, 320, 222, 34))
        self.Button11_3.setObjectName("Button11_3")
        self.Button11_4 = QtWidgets.QPushButton(Form)
        self.Button11_4.setGeometry(QtCore.QRect(40, 400, 222, 34))
        self.Button11_4.setObjectName("Button11_4")
        self.Button11_5 = QtWidgets.QPushButton(Form)
        self.Button11_5.setGeometry(QtCore.QRect(40, 480, 222, 34))
        self.Button11_5.setObjectName("Button11_5")        
        self.pushButton_0 = QtWidgets.QPushButton(Form)
        self.pushButton_0.setGeometry(QtCore.QRect(40, 80, 222, 40))
        self.pushButton_0.setObjectName("pushButton_0")      
        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.Button11_1.setText(_translate("Form", "1. Show Images"))
        self.Button11_2.setText(_translate("Form", "2. Show Distribution"))
        self.Button11_3.setText(_translate("Form", "3. Show Model Structure"))
        self.Button11_4.setText(_translate("Form", "4. Show Comparison"))
        self.Button11_5.setText(_translate("Form", "5. Inference"))
        self.pushButton_0.setText(_translate("Form", "Load Image"))
        self.groupBox.setTitle(_translate("Form", "5. ResNet50"))