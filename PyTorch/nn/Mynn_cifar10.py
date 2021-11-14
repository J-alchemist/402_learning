import torchvision
from torch import nn
import torch
from torch.nn import MaxPool2d, Conv2d, Linear, Sequential
from torch.nn.modules.flatten import Flatten
from torch.utils.data import DataLoader

dataset = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)

dataloader = DataLoader(dataset, batch_size=64)

#常用写法  Sequential
class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.model1 = Sequential(
            Conv2d(3, 32, 5, stride=1, padding=2),
            MaxPool2d(2),
            Conv2d(32, 32, 5, stride=1, padding=2),
            MaxPool2d(2),
            Conv2d(32, 64, 5, stride=1, padding=2),
            MaxPool2d(2),
            Flatten(),
            Linear(1024, 64),
            Linear(64, 10)
        )

    def forward(self, x):
        x = self.model1(x)
        return x

# nnobj1 = Mynn_Model()
# print(nnobj1)
# input = torch.ones((64, 3, 32, 32))     #产生数据
# output = nnobj1(input)
# print(output.shape)

'''
writer = SummaryWriter("logs")
writer.add_graph(nnobj1, input)
writer.close()
'''
nnloss1 = nn.CrossEntropyLoss()     #损失函数
nnobj1 = Mynn_Model()
print(nnobj1)
for data in dataloader:
    img, idx = data
    output = nnobj1(img)
    result_loss = nnloss1(output, idx)
    print(result_loss)
    result_loss.backward()      #反向传播，产生梯度信息可以进行优化


'''
#正常写法
class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.conv1 = Conv2d(3, 32, 5, stride=1, padding=2) #后两个参数需要计算
        self.maxpool1 = MaxPool2d(2)
        self.conv2 = Conv2d(32, 32, 5, stride=1, padding=2)
        self.maxpool2 = MaxPool2d(2)
        self.conv3 = Conv2d(32, 64, 5, stride=1, padding=2)
        self.maxpool3 = MaxPool2d(2)
        self.flatten = Flatten()
        self.linear1 = Linear(1024, 64)     # 64 x 4 x 4 = 1024
        self.linear2 = Linear(64, 10)

    def forward(self, x):
        x = self.conv1(x)
        x = self.maxpool1(x)
        x = self.conv2(x)
        x = self.maxpool2(x)
        x = self.conv3(x)
        x = self.maxpool3(x)
        x = self.flatten(x)
        x = self.linear1(x)
        x = self.linear2(x)   
        return x
'''