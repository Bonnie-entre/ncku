from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QDialog, QFileDialog, QGridLayout, QLabel, QPushButton
from PyQt5.QtGui import QImage, QPixmap
import cv2
import numpy as np
from ui import Ui_Form
import matplotlib.pyplot as plt
from scipy import signal

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
        self.ui.Button11_1.clicked.connect(self.GaussianBlur)
        self.ui.Button11_2.clicked.connect(self.Sobel_X)
        self.ui.Button11_3.clicked.connect(self.Sobel_Y)
        self.ui.Button11_4.clicked.connect(self.Magnitude)
        # self.alpha_slider_max = 255
        self.ui.Button2_1.clicked.connect(self.Resize)
        self.ui.Button2_2.clicked.connect(self.Translation)
        self.ui.Button2_3.clicked.connect(self.Rotate)
        self.ui.Button2_4.clicked.connect(self.Shearing)


    def clickBtn_loadImage(self):
        # clear last image
        self.ui.label_image.clear()

        # import image
        filename, _ = QFileDialog.getOpenFileName(self, 'Open Image', 'Image', '*.png *.jpg *.bmp')
        if filename == '':
            return
        self.img = cv2.imread(filename)
        self.showImage()
        print(self.img.shape)
    
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
 
    def convolve2D(self, image, kernel, average=False):
        if len(image.shape) == 3:
            image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
        image_row, image_col = image.shape
        kernel_row, kernel_col = kernel.shape
    
        output = np.zeros(image.shape)
    
        pad_height = int((kernel_row - 1) / 2)
        pad_width = int((kernel_col - 1) / 2)
    
        padded_image = np.zeros((image_row + (2 * pad_height), image_col + (2 * pad_width)))
    
        padded_image[pad_height:padded_image.shape[0] - pad_height, pad_width:padded_image.shape[1] - pad_width] = image

    
        for row in range(image_row):
            for col in range(image_col):
                output[row, col] = np.sum(kernel * padded_image[row:row + kernel_row, col:col + kernel_col])
                if average:
                    output[row, col] /= kernel.shape[0] * kernel.shape[1]
    
    
        return output

    def GaussianBlur(self):
        #3*3 Gassian filter
        x, y = np.mgrid[-1:2, -1:2]
        gaussian_kernel = np.exp(-(x**2+y**2))

        #Normalization
        gaussian_kernel = gaussian_kernel / gaussian_kernel.sum()
        # print(gaussian_kernel.shape)
        # print(gaussian_kernel)

        #Convo
        self.GaussianBlur_Img = self.convolve2D(image = self.img,kernel= gaussian_kernel, average =True) #卷積

        plt.imshow(self.GaussianBlur_Img, cmap=plt.get_cmap('gist_gray'))
        plt.show()


    def Sobel_X(self):
        kernal_vertical = np.float64([[-1, 0, 1],
                                        [-2, 0, 2],
                                        [-1, 0, 1]])
        self.Sobel_X_Img = self.convolve2D(self.GaussianBlur_Img, kernal_vertical, False)
        self.Sobel_X_Img = np.sqrt(self.Sobel_X_Img**2)
        
        cv2.namedWindow("Sobel_X_Img", cv2.WINDOW_NORMAL)
        cv2.imshow("Sobel_X_Img", self.Sobel_X_Img)
        cv2.waitKey(0)

    def Sobel_Y(self):
        kernal_horizontal = np.float64([[1, 2, 1],
                                        [0, 0, 0],
                                        [-1, -2, -1]])
        self.Sobel_Y_Img = self.convolve2D(self.GaussianBlur_Img, kernal_horizontal, False)
        self.Sobel_Y_Img = np.sqrt(self.Sobel_Y_Img**2)
        cv2.namedWindow("Sobel_Y_Img", cv2.WINDOW_NORMAL)
        cv2.imshow("Sobel_Y_Img", self.Sobel_Y_Img)
        cv2.waitKey(0)

    def Magnitude(self):
        mergeImg = np.sqrt(self.Sobel_X_Img**2 + self.Sobel_Y_Img**2)
        cv2.namedWindow("Magnitude", cv2.WINDOW_NORMAL)
        cv2.imshow("Magnitude", mergeImg)
        cv2.waitKey(0)

    def Resize(self):
        cv2.namedWindow("Resize", cv2.WINDOW_NORMAL)

        self.img2 = cv2.resize(self.img2, (215, 215))
        H = np.float32([[1, 0, 0], [0, 1, 0]])
        self.img2 = cv2.warpAffine(self.img2, H, (430, 430))

        cv2.resizeWindow("Resize", 430, 430)
        cv2.imshow("Resize", self.img2)
        cv2.waitKey(0)

    def Translation(self):
        cv2.namedWindow("Translation", cv2.WINDOW_NORMAL)

        resize_cp = self.img2
        H = np.float32([[1, 0, 0], [0, 1, 0]])
        H_cp = np.float32([[1, 0, 215], [0, 1, 215]])
        self.img2 = cv2.warpAffine(self.img2, H, (430, 430))
        resize_cp = cv2.warpAffine(resize_cp, H_cp, (430, 430))
        self.Translation_Img = cv2.addWeighted(src1 = self.img2, alpha= 1, src2 = resize_cp, beta= 1, gamma = 1)

        cv2.resizeWindow("Translation", 430, 430)
        cv2.imshow("Translation", self.Translation_Img)
        cv2.waitKey(0)

    def Rotate(self):
        cv2.namedWindow("Rotate", cv2.WINDOW_NORMAL)

        M = cv2.getRotationMatrix2D((215, 215), 45, 0.5)    #(center_coordinate，angle，resize)
        self.Rotate_Img = cv2.warpAffine(self.Translation_Img, M, (430, 430))
            
        cv2.resizeWindow("Rotate", 430, 430)
        cv2.imshow("Rotate", self.Rotate_Img)
        cv2.waitKey(0)

    def Shearing(self):
        cv2.namedWindow("Shearing", cv2.WINDOW_NORMAL)

        src = np.float32([[50,50],[200,50],[50,200]])
        dst = np.float32([[10,100],[100,50],[100,250]]) 
        M = cv2.getAffineTransform(src, dst)
        Shearing_Img = cv2.warpAffine(self.Rotate_Img, M, (430, 430))
            
        cv2.resizeWindow("Shearing", 430, 430)
        cv2.imshow("Shearing", Shearing_Img)
        cv2.waitKey(0)


