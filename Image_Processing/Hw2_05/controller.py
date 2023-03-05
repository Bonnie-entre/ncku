## Use conda activat imageAI_2

from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import QApplication, QDialog, QFileDialog, QGridLayout, QLabel, QPushButton
from PyQt5.QtGui import QImage, QPixmap
import numpy as np
from ui import Ui_Form
from matplotlib import pyplot as plt
import matplotlib.image as img
from PIL import Image
import torch
from torch.nn import functional as F
from torchsummary import summary
from torchvision import datasets, models, transforms

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
normalize = transforms.Normalize(mean=[0.485, 0.456, 0.406],
                                 std=[0.229, 0.224, 0.225])
data_transforms = {
                        'train':
                        transforms.Compose([
                            transforms.Resize((224,224)),
                            transforms.RandomAffine(0, shear=10, scale=(0.8,1.2)),
                            transforms.RandomHorizontalFlip(),
                            transforms.ToTensor(),
                            normalize
                        ]),
                        'validation':
                        transforms.Compose([
                            transforms.Resize((224,224)),
                            transforms.ToTensor(),
                            normalize
                        ]),
                    }

class MainWindow_controller(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__() # in python3, super(Class, self).xxx = super().xxx
        self.ui = Ui_Form()
        self.ui.setupUi(self)
        self.setup_control()
        self.model_test = torch.load('./model/model_resnet50_CrossEntropy.pt', map_location='cpu')
        self.model_test.eval()     


    def setup_control(self):
        self.ui.pushButton_0.clicked.connect(self.LoadImage)
        self.ui.Button11_1.clicked.connect(self.ShowImg)
        self.ui.Button11_2.clicked.connect(self.ShowDistribution)
        self.ui.Button11_3.clicked.connect(self.ModelStructure)
        self.ui.Button11_4.clicked.connect(self.Comparison)
        self.ui.Button11_5.clicked.connect(self.Inference)


    def LoadImage(self):
        # import image
        filename, _ = QFileDialog.getOpenFileName(self, 'Open Image', 'Image', '*.png *.jpg *.bmp')
        if filename == '':
            return
        self.img = Image.open(filename)
        self.img.show()


    def ShowImg(self):
        cat = Image.open('./inference_dataset/Cat/8048.jpg')
        cat = cat.resize((224,224))
        dog = Image.open('./inference_dataset/Dog/a86fbbe4e09de8ad59e8a9175d10d478.jpg')
        dog = dog.resize((224,224))

        plt.figure(figsize=(6,4)) 
        plt.subplot(121)
        plt.imshow(cat)
        plt.title("Cat")
        plt.axis('off')
        plt.subplot(122)
        plt.imshow(dog)
        plt.title("Dog")
        plt.axis('off')
        plt.show()


    def ShowDistribution(self):
        # COLAB
        # from glob import glob 
        # cat_pic = glob('/content/data/Dataset_OpenCvDl_Hw2_Q5/training_dataset/Cat/*') #dont forget the /*
        # catNum = len(cat_pic)
        # print(catNum)
        plt.figure(figsize=(6,5)) 
        x = ["Cat", "Dog"]        # 水平資料點
        h = [5412, 10788]   # 高度
        for i in range(len(h)):
            plt.text(i, h[i], h[i])
        plt.bar(x,h)
        plt.ylabel("Number of images")
        plt.title("Class Distribution")
        plt.show()


    def ModelStructure(self):
        print(summary(self.model_test, (3, 224, 224)))


    #TODO set right accuracy
    def Comparison(self):
        plt.figure(figsize=(6,5)) 
        x = ["Binary Cross Entropy", "Focal Loss"]        # 水平資料點
        h = [97.7, 95.5]   # 高度
        for i in range(len(h)):
            plt.text(i, h[i], h[i])
        plt.bar(x,h)
        plt.ylabel("Accuracy(%)")
        plt.title("Accuracy Comparison")
        plt.show()


    def Inference(self):
        validation_batch = torch.stack([data_transforms['validation'](self.img).to(device)])
        pred_logits_tensor = self.model_test(validation_batch)
        pred_probs = F.softmax(pred_logits_tensor, dim=1).cpu().data.numpy()
        plt.figure(figsize=(6,5)) 
        plt.title("{:.0f}% Cat, {:.0f}% Dog".format(100*pred_probs[0,0],
                                                    100*pred_probs[0,1]))
        plt.imshow(self.img)
        plt.axis('off')
        plt.show()

