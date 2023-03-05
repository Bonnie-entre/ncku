## Use conda activat imageAI/ imageAI_2

from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QDialog, QFileDialog, QGridLayout, QLabel, QPushButton
from PyQt5.QtGui import QImage, QPixmap
import cv2
import numpy as np
from ui import Ui_Form
import os
from matplotlib import pyplot as plt

class MainWindow_controller(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.setup_control()


    def setup_control(self):
        self.ui.pushButton_0.clicked.connect(self.LoadFolder)
        self.ui.pushButton.clicked.connect(self.clickBtn_loadImage)
        self.ui.pushButton_2.clicked.connect(self.clickBtn_loadImage2)
        self.ui.Button11_1.clicked.connect(self.DrawContour)
        self.ui.Button11_2.clicked.connect(self.CountRings)
        self.ui.Button2_1.clicked.connect(self.FindCorners)
        self.ui.Button2_2.clicked.connect(self.IntrinsicMatrix)
        self.ui.Button2_3.clicked.connect(self.ExtrinsicMatrix)
        self.ui.Button2_4.clicked.connect(self.DistortionMatrix)
        self.ui.Button2_5.clicked.connect(self.ShowResult)
        self.ui.Button3_1.clicked.connect(self.ShowWords_onBoard)
        self.ui.Button3_2.clicked.connect(self.ShowWords_Vertically)
        self.ui.Button4_1.clicked.connect(self.DisparityMap)
        self.ui.Button4_2.clicked.connect(self.CheckDisparity)


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

        # show image
        self.img = cv2.resize(self.img, (self.img.shape[1]//3, self.img.shape[0]//3), interpolation=cv2.INTER_AREA)
            
        cv2.imshow("Img1", self.img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
 

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

        # show image
        self.img2 = cv2.resize(self.img2, (self.img2.shape[1]//3, self.img2.shape[0]//3), interpolation=cv2.INTER_AREA)
        
        cv2.imshow("Img2", self.img2)
        cv2.waitKey(0)
        cv2.destroyAllWindows()


    def DrawContour(self):
        image = cv2.resize(self.img, (self.img.shape[1]*3, self.img.shape[0]*3), interpolation=cv2.INTER_AREA)
        imgray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        ret, thresh = cv2.threshold(imgray, 127, 255, 0)
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)        
        im_output = image.copy()        
        cv2.drawContours(im_output, contours, -1, (0, 255, 0), 2)     
        im_output = cv2.GaussianBlur(im_output, (5, 5), 0) 
        cv2.imshow("Contours", im_output)
        cv2.waitKey(0)
        cv2.destroyAllWindows()


    def CountRings(self):
        imgray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
        ret, thresh = cv2.threshold(imgray, 127, 255, 0)
        contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
        imgray2 = cv2.cvtColor(self.img2, cv2.COLOR_BGR2GRAY)
        ret, thresh2 = cv2.threshold(imgray2, 127, 255, 0)
        contours2, hierarchy = cv2.findContours(thresh2, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

        self.ui.load1_2_1.setText( "There are "+ str(int(len(contours)/2)) +" rings in img1.jpg")
        self.ui.load1_2_2.setText("There are "+ str(int(len(contours2)/2)) +" rings in img2.jpg")


    def LoadFolder(self):
        self.imFolder = []
        folder_path = QFileDialog.getExistingDirectory(self, "Open folder", "./")
        if folder_path == '':
            return

        scale_percent = 30 # percent of original size
        for filename in os.listdir(folder_path):
            img = cv2.imread(os.path.join(folder_path,filename), -1)
            if img is not None:
                # resize image
                width = int(img.shape[1] * scale_percent / 100)
                height = int(img.shape[0] * scale_percent / 100)
                dim = (width, height)
                resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)
                self.imFolder.append(resized)
               

    def FindCorners(self):
        criteria=(cv2.TermCriteria_EPS + cv2.TermCriteria_MAX_ITER, 30, 0.001)
        w1,h1=(11,8)
        objp = np.zeros((w1 * h1, 3), np.float32)
        objp[:, :2] = np.mgrid[0:w1, 0:h1].T.reshape(-1, 2)

        # Arrays to store object points and image points from all the images.
        self.objpoints = []  # 3d point in real world space
        self.imgpoints = []  # 2d points in image plane
        self.grayFolder = []
        
        for i in range(len(self.imFolder)):
            img = self.imFolder[i].copy()
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            self.grayFolder.append(gray)
            ret, corners = cv2.findChessboardCorners(gray, (11,8) ,None)
            if ret == True:
                self.objpoints.append(objp)
                corners2 = cv2.cornerSubPix(gray, corners, (11,11), (-1, -1), criteria)
                self.imgpoints.append(corners2)
                cv2.drawChessboardCorners(img, (11,8), corners2, ret)
                cv2.imshow("img", img)
                key = cv2.waitKey(500)  # 0.5 second

            if key == 27:   #if ESC is pressed, exit loop
                cv2.destroyAllWindows()
                break
        ret, self.mat_inter, self.coff_dis, v_rot, v_trans = cv2.calibrateCamera(self.objpoints, self.imgpoints, self.grayFolder[0].shape[::-1], None, None)


    def IntrinsicMatrix(self):  # should click FindCorner first to get parameters
        print("Intrinsic:")
        print(self.mat_inter)


    def ExtrinsicMatrix(self):  # should click FindCorner first to get parameters
        pick_index = int(self.ui.box.currentText())-1
        print("Extrinsic:")
        gray_img = self.grayFolder[pick_index]
        ret, mat_inter, coff_dis, v_rot, v_trans = cv2.calibrateCamera(self.objpoints, self.imgpoints, gray_img.shape[::-1], None, None)
        print(len(v_rot))
        R = cv2.Rodrigues(v_rot[pick_index-1])     #R = cv2.Rodrigues(rvecs[num-1])
        ext = np.hstack((R[0], v_trans[pick_index-1]))   #ext = np.hstack((R[0], tvecs[num-1]))
        print(ext)


    def DistortionMatrix(self): # should click FindCorner first to get parameters
        print("Distortion:")
        print(self.coff_dis)


    def ShowResult(self):       # should click FindCorner first to get parameters
        cv2.namedWindow('Undistorted Img', cv2.WINDOW_AUTOSIZE)
        cv2.moveWindow('Undistorted Img', 1000, 300)
        cv2.namedWindow('Distorted Img', cv2.WINDOW_AUTOSIZE)
        cv2.moveWindow('Distorted Img', 350, 300)
        
        for i in range(len(self.grayFolder)):    
            cv2.imshow("Distorted Img", self.grayFolder[i])        
            undist = cv2.undistort(self.grayFolder[i], self.mat_inter, self.coff_dis, None, self.mat_inter)
            cv2.imshow("Undistorted Img", undist)
            key = cv2.waitKey(500)  # 0.5 second
            if key == 27:   #if ESC is pressed, exit loop
                cv2.destroyAllWindows()
                break
    

    def ShowWords(self, filename_dir):
        # get alphabet library
        fs = cv2.FileStorage(filename_dir, cv2.FILE_STORAGE_READ)

        # get text from textbox
        t = self.ui.textbox.text()

        # interate 5 images
        # Camera Calibration
        criteria=(cv2.TermCriteria_EPS + cv2.TermCriteria_MAX_ITER, 30, 0.001)
        w1,h1=(11,8)
        objp = np.zeros((w1 * h1, 3), np.float32)
        objp[:, :2] = np.mgrid[0:w1, 0:h1].T.reshape(-1, 2)

        # Arrays to store object points and image points from all the images.
        objpoints = []  # 3d point in real world space
        imgpoints = []  # 2d points in image plane
        
        for i in range(len(self.imFolder)):
            img = self.imFolder[i].copy()
            gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            ret, corners = cv2.findChessboardCorners(gray, (11,8) ,None)
            if ret == True:
                objpoints.append(objp)
                corners2 = cv2.cornerSubPix(gray, corners, (11,11), (-1, -1), criteria)
                imgpoints.append(corners2)
                ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
            
            # draw
                count_ch = 0
                for a in t:
                    # get alphabet array
                    ch = fs.getNode(a).mat() 
                    ch = ch.astype(np.float32)

                    # modify x
                    if(count_ch%3==0):  # x+9
                        x_m = 7
                    elif(count_ch%3 == 1):
                        x_m = 4
                    else:
                        x_m = 1

                    # modify y  
                    if(int(count_ch/3)==0):  # x+9
                        y_m = 5
                    else:
                        y_m = 1   

                    for a1 in ch:
                        for a2 in a1:
                            a2[0] += x_m
                            a2[1] += y_m
                    count_ch+=1
                    for c in range(len(ch)):
                        # project 3D points to image plane
                        imgpts, jac = cv2.projectPoints(ch[c], rvecs[i], tvecs[i], mtx, dist)
                        # imgpts, jac = cv2.projectPoints(axis, rvecs[i], tvecs[i], mtx, dist)

                        def draw(image, imgpts):
                            image = cv2.line(image, tuple(imgpts[0].ravel().astype(int)), tuple(imgpts[1].ravel().astype(int)), (0, 0, 255), 3)
                            return image

                        img = draw(img, imgpts)
            cv2.imshow("img", img)
            cv2.waitKey(1000)
        cv2.destroyAllWindows()
       
    def ShowWords_onBoard(self):        
        self.ShowWords('./Q2_lib/alphabet_lib_onboard.txt')

    def ShowWords_Vertically(self):
        self.ShowWords('./Q2_lib/alphabet_lib_vertical.txt')


    def DisparityMap(self):
        imageL = cv2.resize(self.img, (self.img.shape[1]*3, self.img.shape[0]*3), interpolation=cv2.INTER_AREA)
        imageR = cv2.resize(self.img2, (self.img2.shape[1]*3, self.img2.shape[0]*3), interpolation=cv2.INTER_AREA)
        imgL = cv2.cvtColor(imageL, cv2.COLOR_BGR2GRAY)
        imgR = cv2.cvtColor(imageR, cv2.COLOR_BGR2GRAY)
        stereo = cv2.StereoBM_create(numDisparities=256, blockSize=25)
        disparity = stereo.compute(imgL, imgR)
        plt.imshow(disparity,'gray')
        plt.show()

    
    def CheckDisparity(self):
        imgL = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
        imgR = cv2.cvtColor(self.img2, cv2.COLOR_BGR2GRAY)
        stereo = cv2.StereoBM_create(numDisparities=256, blockSize=25)
        disparity = stereo.compute(imgL, imgR).astype(np.float32) / 16.0
        # disparity = cv2.resize(disparity, (1400, 950), interpolation=cv2.INTER_AREA)

        # mouse callback function
        def draw_circle(event, x, y, flags, param):
            
            if event == cv2.EVENT_LBUTTONDOWN:
                imgR = self.img2.copy()
                x -= int(disparity[y][x])
                cv2.circle(imgR, (x,y), 3, (0, 255, 0), -1)
                cv2.imshow('imageR_dot', imgR)
                cv2.waitKey(500)

        while(1):
            cv2.namedWindow('imageL')
            cv2.setMouseCallback('imageL', draw_circle)
            cv2.imshow('imageL', self.img)
            if cv2.waitKey(20) & 0xFF == 27:
                break

        cv2.waitKey(0)
        cv2.destroyAllWindows()
        
