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
        Form.resize(1800, 470)
        self.groupBox = QtWidgets.QGroupBox(Form)
        self.groupBox.setGeometry(QtCore.QRect(150, 40, 260, 400))
        self.groupBox.setObjectName("groupBox")        
        self.Button11_1 = QtWidgets.QPushButton(Form)
        self.Button11_1.setGeometry(QtCore.QRect(170, 160, 222, 34))
        self.Button11_1.setObjectName("Button11_1")
        self.Button11_2 = QtWidgets.QPushButton(Form)
        self.Button11_2.setGeometry(QtCore.QRect(170, 240, 222, 34))
        self.Button11_2.setObjectName("Button11_2")
        # 2 text lines
        self.load1_2_1 = QtWidgets.QLabel(Form)
        self.load1_2_1.setGeometry(QtCore.QRect(170, 290, 250, 20))
        self.load1_2_1.setObjectName("load1_2_1")
        self.load1_2_2 = QtWidgets.QLabel(Form)
        self.load1_2_2.setGeometry(QtCore.QRect(170, 315, 250, 20))
        self.load1_2_2.setObjectName("load1_2_1")

        self.groupBox_2 = QtWidgets.QGroupBox(Form)
        self.groupBox_2.setGeometry(QtCore.QRect(440, 40, 260, 400))
        self.groupBox_2.setObjectName("groupBox_2")
        self.Button2_1 = QtWidgets.QPushButton(Form)
        self.Button2_1.setGeometry(QtCore.QRect(460, 80, 222, 34))
        self.Button2_1.setObjectName("Button2_1")
        self.Button2_2 = QtWidgets.QPushButton(Form)
        self.Button2_2.setGeometry(QtCore.QRect(460, 160, 222, 34))
        self.Button2_2.setObjectName("Button2_2")
        self.groupBox_3 = QtWidgets.QGroupBox(Form)
        self.groupBox_3.setGeometry(QtCore.QRect(450, 220, 240, 100))
        self.groupBox_3.setObjectName("groupBox_3")
        self.Button2_3 = QtWidgets.QPushButton(Form)
        self.Button2_3.setGeometry(QtCore.QRect(460, 278, 222, 34))
        self.Button2_3.setObjectName("Button2_3")
        self.box = QtWidgets.QComboBox(Form)   # 加入下拉選單
        self.box.addItems(['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15'])   # 加入四個選項
        self.box.setGeometry(460,245,222,30)
        self.Button2_4 = QtWidgets.QPushButton(Form)
        self.Button2_4.setGeometry(QtCore.QRect(460, 340, 222, 34))
        self.Button2_4.setObjectName("Button2_4")
        self.Button2_5 = QtWidgets.QPushButton(Form)
        self.Button2_5.setGeometry(QtCore.QRect(460, 390, 222, 34))
        self.Button2_5.setObjectName("Button2_5")

        self.groupBox_4 = QtWidgets.QGroupBox(Form)
        self.groupBox_4.setGeometry(QtCore.QRect(730, 40, 260, 400))
        self.groupBox_4.setObjectName("groupBox_4")
        self.textbox = QtWidgets.QLineEdit(Form)
        self.textbox.setGeometry(QtCore.QRect(750, 120, 222, 34))
        self.textbox.setObjectName("textbox")
        self.Button3_1 = QtWidgets.QPushButton(Form)
        self.Button3_1.setGeometry(QtCore.QRect(750, 240, 222, 34))
        self.Button3_1.setObjectName("Button3_1")
        self.Button3_2 = QtWidgets.QPushButton(Form)
        self.Button3_2.setGeometry(QtCore.QRect(750, 340, 222, 34))
        self.Button3_2.setObjectName("Button3_2")

        self.groupBox_5 = QtWidgets.QGroupBox(Form)
        self.groupBox_5.setGeometry(QtCore.QRect(1020, 40, 260, 400))
        self.groupBox_5.setObjectName("groupBox_5")
        self.Button4_1 = QtWidgets.QPushButton(Form)
        self.Button4_1.setGeometry(QtCore.QRect(1040, 240, 222, 34))
        self.Button4_1.setObjectName("Button4_1")
        self.Button4_2 = QtWidgets.QPushButton(Form)
        self.Button4_2.setGeometry(QtCore.QRect(1040, 320, 222, 34))
        self.Button4_2.setObjectName("Button4_2")
        
        self.pushButton_0 = QtWidgets.QPushButton(Form)
        self.pushButton_0.setGeometry(QtCore.QRect(20, 80, 120, 40))
        self.pushButton_0.setObjectName("pushButton_0")
        self.pushButton = QtWidgets.QPushButton(Form)
        self.pushButton.setGeometry(QtCore.QRect(20, 160, 120, 40))
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(Form)
        self.pushButton_2.setGeometry(QtCore.QRect(20, 240, 120, 40))
        self.pushButton_2.setObjectName("pushButton_2")
        self.load1 = QtWidgets.QLabel(Form)
        self.load1.setGeometry(QtCore.QRect(40, 210, 70, 20))
        self.load1.setObjectName("load1")
        self.load2 = QtWidgets.QLabel(Form)
        self.load2.setGeometry(QtCore.QRect(40, 290, 70, 20))
        self.load2.setObjectName("load2")
        self.label_image = QtWidgets.QLabel(Form)
        self.label_image.setGeometry(QtCore.QRect(830, 40, 400, 300))
        self.label_image.setObjectName("image")
        self.label_image2 = QtWidgets.QLabel(Form)
        self.label_image2.setGeometry(QtCore.QRect(1300, 40, 400, 300))
        self.label_image2.setObjectName("image2")
        

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.Button11_1.setText(_translate("Form", "1.1 Draw Contour"))
        self.Button11_2.setText(_translate("Form", "1.2 Count Rings"))
        self.load1_2_1.setText(_translate("Form", "There are ___ rings in img1.jpg"))
        self.load1_2_2.setText(_translate("Form", "There are ___ rings in img2.jpg"))
        
        self.Button2_1.setText(_translate("Form", "2.1 Find Corners"))
        self.Button2_2.setText(_translate("Form", "2.2 Find Intrinsic"))
        self.Button2_3.setText(_translate("Form", "2.3 Find Extrinsic"))
        self.Button2_4.setText(_translate("Form", "2.4 Find Distortion"))
        self.Button2_5.setText(_translate("Form", "2.5 Show Result"))
        self.Button3_1.setText(_translate("Form", "3.1 Show Words on Board"))
        self.Button3_2.setText(_translate("Form", "3.2 Show Words Vertically"))
        self.Button4_1.setText(_translate("Form", "4.1 Stereo Disparity Map"))
        self.Button4_2.setText(_translate("Form", "4.2 Check Disparity Value"))
        self.pushButton_0.setText(_translate("Form", "Load Folder"))
        self.pushButton.setText(_translate("Form", "Load Image_L"))
        self.pushButton_2.setText(_translate("Form", "Load Image_R"))
        self.load1.setText(_translate("Form", "image1"))
        self.load2.setText(_translate("Form", "image2"))
        self.groupBox.setTitle(_translate("Form", "1. Find Contour"))
        self.groupBox_2.setTitle(_translate("Form", "2. Calibration"))
        self.groupBox_3.setTitle(_translate("Form", "2.3 Find Extrinsic"))
        self.groupBox_4.setTitle(_translate("Form", "3. Augmented Reality"))
        self.groupBox_5.setTitle(_translate("Form", "4. Stereo Disparity Map"))
        self.box.setCurrentIndex(0) # 下拉選單 deafult '1'
