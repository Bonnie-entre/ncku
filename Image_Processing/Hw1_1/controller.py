from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QDialog, QFileDialog, QGridLayout, QLabel, QPushButton
from PyQt5.QtGui import QImage, QPixmap
import cv2
import numpy as np
from ui import Ui_Form

class MainWindow_controller(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.setup_control()


    def setup_control(self):
        # TODO
        self.ui.pushButton.clicked.connect(self.clickBtn_loadImage)
        self.ui.pushButton_2.clicked.connect(self.clickBtn_loadImage2)
        self.ui.Button11_1.clicked.connect(self.clickBtn_colorSeperate)
        self.ui.Button11_2.clicked.connect(self.clickBtn_colorTransform)
        self.ui.Button11_3.clicked.connect(self.color_detection)
        self.ui.Button11_4.clicked.connect(self.blending)
        self.alpha_slider_max = 255
        self.ui.Button2_1.clicked.connect(self.Gaussian)
        self.ui.Button2_2.clicked.connect(self.Bilateral)
        self.ui.Button2_3.clicked.connect(self.Median)


    def clickBtn_loadImage(self):
        # clear last image
        self.ui.label_image.clear()

        # import image
        filename, _ = QFileDialog.getOpenFileName(self, 'Open Image', 'Image', '*.png *.jpg *.bmp')
        if filename == '':
            return
        self.img = cv2.imread(filename, -1)
        if self.img.size == 1:
            return
        self.showImage()
    
    def showImage(self):
        height, width, channel = self.img.shape
        bytesPerline = 3 * width
        self.qImg = QImage(self.img.data, width, height, bytesPerline, QImage.Format_RGB888).rgbSwapped()
        self.ui.label_image.setPixmap(QPixmap.fromImage(self.qImg))
        self.ui.label_image.setScaledContents(True)
 
    def clickBtn_loadImage2(self):
        # clear last image
        self.ui.label_image2.clear()

        # import image
        filename, _ = QFileDialog.getOpenFileName(self, 'Open Image', 'Image', '*.png *.jpg *.bmp')
        if filename == '':
            return
        self.img2 = cv2.imread(filename, -1)
        if self.img2.size == 1:
            return
        self.showImage2()
    
    def showImage2(self):
        height, width, channel = self.img2.shape
        bytesPerline = 3 * width
        self.qImg2 = QImage(self.img2.data, width, height, bytesPerline, QImage.Format_RGB888).rgbSwapped()
        self.ui.label_image2.setPixmap(QPixmap.fromImage(self.qImg2))
        self.ui.label_image2.setScaledContents(True)
 
    def clickBtn_colorSeperate(self):
        b, g, r = cv2.split(self.img)
        zeros = np.zeros(self.img.shape[:2], dtype="uint8")
        cv2.namedWindow("rImg", cv2.WINDOW_NORMAL)
        cv2.namedWindow("gImg", cv2.WINDOW_NORMAL)
        cv2.namedWindow("bImg", cv2.WINDOW_NORMAL)
        cv2.moveWindow("gImg", 0, 300)
        cv2.moveWindow("bImg", 0, 600)
        cv2.imshow("rImg", cv2.merge([zeros, zeros, r]))
        cv2.imshow("gImg", cv2.merge([zeros, g, zeros]))
        cv2.imshow("bImg", cv2.merge([b, zeros, zeros]))
        cv2.resizeWindow("rImg", 400, 300)
        cv2.resizeWindow("gImg", 400, 300)
        cv2.resizeWindow("bImg", 400, 300)
        cv2.waitKey(0)

    def clickBtn_colorTransform(self):
        img = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
        cv2.namedWindow("Img", cv2.WINDOW_NORMAL)
        cv2.imshow("Img", img)

        img2 = self.img
        (row, col) = img2.shape[0:2]
        for i in range(row):
            for j in range(col):
                img2[i, j] = sum(img2[i, j]) * 0.33
        
        cv2.imshow("Img 1/3", img2)
        cv2.waitKey(0)

    def color_detection(self):
        hsv = cv2.cvtColor(self.img, cv2.COLOR_BGR2HSV)
        lower_green = np.array([35, 43, 46])
        upper_green = np.array([77, 255, 255])
        mask_green = cv2.inRange(hsv, lower_green, upper_green)
        res1 = cv2.bitwise_and(self.img, self.img, mask=mask_green)

        sensitivity = 15
        lower_white = np.array([0,0,255-sensitivity])
        upper_white = np.array([255,sensitivity,255])
        mask_white = cv2.inRange(hsv, lower_white, upper_white)
        res2 = cv2.bitwise_and(self.img, self.img, mask=mask_white)
        cv2.namedWindow("green", cv2.WINDOW_NORMAL)
        cv2.namedWindow("white", cv2.WINDOW_NORMAL)
        cv2.imshow("green", res1)
        cv2.imshow("white", res2)
        cv2.waitKey(0)

    def on_trackbar(self, val):
        alpha = val / self.alpha_slider_max
        beta = ( 1.0 - alpha )
        dst = cv2.addWeighted(self.img, alpha, self.img2, beta, 0.0)
        cv2.imshow('result',dst)
        
    def blending(self):
        cv2.namedWindow('result',cv2.WINDOW_NORMAL)
        cv2.resizeWindow("result", 400, 300)
        cv2.createTrackbar('Blend', 'result' , 0, self.alpha_slider_max, self.on_trackbar)
        self.on_trackbar(0)

    def on_trackbar_Gaussian(self, val):
        k = 2 * val + 1
        Gaussian = cv2.GaussianBlur(self.img, (k, k), 0)
        cv2.imshow('Gaussian Blurring', Gaussian)

    def Gaussian(self):
        cv2.namedWindow('Gaussian Blurring',cv2.WINDOW_NORMAL)
        cv2.resizeWindow("Gaussian Blurring", 300, 400)
        cv2.createTrackbar('magnitude', 'Gaussian Blurring' , 0, 10, self.on_trackbar_Gaussian)
        self.on_trackbar_Gaussian(0)

    def on_trackbar_Bilateral(self, val):
        k = 2 * val + 1
        Bilateral = cv2.bilateralFilter(self.img, k, 90, 90)
        cv2.imshow('Bilateral Filtering', Bilateral)

    def Bilateral(self):
        cv2.namedWindow('Bilateral Filtering',cv2.WINDOW_NORMAL)
        cv2.resizeWindow("Bilateral Filtering", 300, 400)
        cv2.createTrackbar('magnitude', 'Bilateral Filtering' , 0, 10, self.on_trackbar_Bilateral)
        self.on_trackbar_Bilateral(0)

    def on_trackbar_Median(self, val):
        k = 2 * val + 1
        Median = cv2.medianBlur(self.img2, k)
        cv2.imshow('Median Filtering', Median)

    def Median(self):
        cv2.namedWindow('Median Filtering',cv2.WINDOW_NORMAL)
        cv2.resizeWindow("Median Filtering", 300, 400)
        cv2.createTrackbar('magnitude', 'Median Filtering' , 0, 10, self.on_trackbar_Median)
        self.on_trackbar_Median(0)