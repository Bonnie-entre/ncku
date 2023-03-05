from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QDialog, QFileDialog, QGridLayout, QLabel, QPushButton
from PyQt5.QtGui import QImage, QPixmap
import cv2
import numpy as np
import random
from matplotlib import pyplot as plt
from keras.datasets import cifar10
import torch
import torch.nn as nn
import torchvision.models as models
from torchsummary import summary
import torchvision
from torchvision import transforms
import torchvision.transforms as TF
#import functional
from PIL import Image

from ui import Ui_Form

VGG_types = {
    'VGG11': [64, 'M', 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M'],
    'VGG13': [64, 64, 'M', 128, 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M'],
    'VGG16': [64, 64, 'M', 128, 128, 'M', 256, 256, 256, 'M', 512, 512, 512, 'M', 512, 512, 512, 'M'],
    'VGG19': [64, 64, 'M', 128, 128, 'M', 256, 256, 256, 256, 'M', 512, 512, 512, 512, 'M', 512, 512, 512, 512, 'M']
}

class VGG_net(nn.Module):
    def __init__(self, in_channels, num_classes):
        super(VGG_net, self).__init__()
        self.in_channels = in_channels
        self.conv_layers = self.create_conv_layer(VGG_types['VGG19'])
                
        self.fcs = nn.Sequential(
            nn.Linear(512, 4096),  
            nn.ReLU(),
            nn.Dropout(p=0.5),
            nn.Linear(4096, 4096),
            nn.ReLU(),
            nn.Dropout(p=0.5),
            nn.Linear(4096, num_classes)
        )
        
    def forward(self, x):
        x = self.conv_layers(x)
        x = x.reshape(x.shape[0], -1)
        x = self.fcs(x)
        return x
    
    def create_conv_layer(self, architecture):
        layers = []
        in_channels = self.in_channels
        
        for x in architecture:
            if type(x) == int:
                out_channels = x
                layers += [nn.Conv2d(in_channels = in_channels, out_channels = out_channels,
                                    kernel_size=(3,3), stride=(1,1), padding=(1,1)),
                           nn.BatchNorm2d(x), nn.ReLU()]
                in_channels = x
            elif x == 'M':
                layers += [nn.MaxPool2d(kernel_size=(2,2), stride = (2,2))]
        
        return nn.Sequential(*layers)


class MainWindow_controller(QtWidgets.QMainWindow):


    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.setup_control()


        # load dataset
        (self.trainX, self.trainy), (self.testX, self.testy)=cifar10.load_data()# summarize loaded dataset
        print('Train: X=%s, y=%s' % (self.trainX.shape, self.trainy.shape))
        print('Test: X=%s, y=%s' % (self.testX.shape, self.testy.shape))
        # Label 
        self.label_dict={
            0:"airplain",1:"automobile",2:"bird",3:"cat",4:"deer", 5:"dog", 
            6:"frog",7:"horse",8:"ship",9:"truck"}

        # load model
        self.model = VGG_net(in_channels=3, num_classes = 10)
        self.model.load_state_dict(torch.load('./model_cifar_vgg19_dict.pt',map_location='cpu'))
        self.model.eval()


    def setup_control(self):
        # TODO
        self.ui.pushButton.clicked.connect(self.clickBtn_loadImage)
        self.ui.Button11_1.clicked.connect(self.TrainImg)
        self.ui.Button11_2.clicked.connect(self.Model_Structure)
        self.ui.Button11_3.clicked.connect(self.Augmentation)
        self.ui.Button11_4.clicked.connect(self.Accuracy_Loss)
        self.ui.Button11_5.clicked.connect(self.Inference)


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
 
    def TrainImg(self):
        fig=plt.gcf()                            #取得 pyplot 物件參考
        fig.set_size_inches(12, 14)                    #設定畫布大小為 12 吋*14吋
        for i in range(0, 9):                     #依序顯示 num 個子圖
            idx =  random.randint(1, 50000)   #self.trainX.shape
            ax = plt.subplot(3, 3, i+1)               #建立 5*5 個子圖中的第 i+1 個
            ax.imshow(self.trainX[idx], cmap='binary')           #顯示子圖
            title = self.label_dict[int(self.trainy[idx])]
            ax.set_title(title, fontsize=10)             #設定標題
            ax.set_xticks([]);                     #不顯示 x 軸刻度
            ax.set_yticks([]);                     #不顯示 y 軸刻度
        plt.show()

    def Model_Structure(self):
        vgg19_pretrained = models.vgg19().to(device = torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
        print(summary(vgg19_pretrained, (3, 224, 224)))

    def Augmentation(self):
        transform = transforms.Compose([
            transforms.ToPILImage(),
            transforms.RandomRotation(30, resample=Image.BICUBIC, expand=False, center=(55, 5)),
        ])
        
        transform2 = transforms.Compose([
            transforms.ToPILImage(),
            transforms.RandomResizedCrop((100, 200)),
        ])

        transform3 = transforms.Compose([
            transforms.ToPILImage(),
            transforms.RandomHorizontalFlip(p=0.9),
        ])

        aug_Img = [transform(self.img), transform2(self.img), transform3(self.img)]
        
        fig=plt.gcf()                          
        fig.set_size_inches(8, 4)
        for i in range(3):
            ax = plt.subplot(1, 3, i+1)              
            ax.set_xticks([]);                  
            ax.set_yticks([]);   
            ax.imshow(aug_Img[i])
        plt.show()

    def Accuracy_Loss(self):
        Img = cv2.imread('lo_acc.png')
        plt.imshow(Img, cmap=plt.get_cmap('gist_gray'))
        plt.show()

    def Inference(self):
        # process
        # torch_img = torch.from_numpy(self.img)
        # torch_img = torch_img.view(torch_img.shape[2], torch_img.shape[0], torch_img.shape[1])
        # print(torch_img.shape)

        # preprocess = transforms.Compose([
        #     transforms.Resize(256),
        #     transforms.CenterCrop(224),
        #     transforms.ToTensor(),
        #     transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
        # ])
        # images = transforms.ToPILImage()(self.img)
        # images = preprocess(images)
        
        images = self.testX[0]
        transforms.ToPILImage()(images).show()

        images = torch.from_numpy(images)
        images = images.view(1, images.shape[2], images.shape[0], images.shape[1])
        print(images.size())

        # predict
        images = images.to(device = torch.device('cuda' if torch.cuda.is_available() else 'cpu'))
        output = self.model(images) #.unsqueeze(0)
        print(output)
        _, predicted = torch.max(output, 1)
        print(predicted)
        # print(self.label_dict[predicted])
