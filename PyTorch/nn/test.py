#自定义数据集合 imgs，准备图片进行测试
from PIL import Image
import torch
import torchvision
from torch import nn
from torch.nn import Conv2d, Sequential, MaxPool2d, Linear
from torch.nn.modules.flatten import Flatten

'''
#在test_dataset打断点仿真参数classes下就可看到以下数据
['airplane', 'automobile', 'bird', 'cat', 'deer', 'dog', 'frog', 'horse', 'ship', 'truck']
[0,           1,            2,      3,      4,      5,      6,      7,      8,      9    ]
'''

img1 = Image.open("imgs/frog.png")
print(img1)
img1 = img1.convert("RGB")          #PNG的4通道转3通道
print(img1)

transform = torchvision.transforms.Compose( [torchvision.transforms.Resize((32,32)),
                                             torchvision.transforms.ToTensor()] )

img1 = transform(img1)
print(img1.shape)

class Model_Cifar10(nn.Module):

    def __init__(self):
        super(Model_Cifar10, self).__init__()
        self.model1 = Sequential(
            Conv2d(3, 32, 5, stride=1, padding=2),
            MaxPool2d(2),
            Conv2d(32, 32, 5, stride=1, padding=2),
            MaxPool2d(2),
            Conv2d(32, 64, 5, stride=1, padding=2),
            MaxPool2d(2),
            Flatten(),
            Linear(64*4*4, 64),
            Linear(64, 10)
        )

    def forward(self, x):
        x = self.model1(x)
        return x

cifar10obj = Model_Cifar10()
cifar10obj.load_state_dict( torch.load("models/cifar10_26.pth"))
print(cifar10obj)
img1 = torch.reshape(img1, (1, 3, 32, 32))  #格式需要带batch

cifar10obj.eval()
with torch.no_grad():
    output = cifar10obj(img1)
print(output)
print(output.argmax(1))




