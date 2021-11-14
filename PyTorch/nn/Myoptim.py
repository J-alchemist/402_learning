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

nnobj1 = Mynn_Model()
print(nnobj1)
nnloss1 = nn.CrossEntropyLoss()     #损失函数
nnoptim1 = torch.optim.SGD(nnobj1.parameters(), lr=0.01)      #优化器


for data in dataloader: #一轮训练，需要多轮训练，外嵌for
    img, idx = data
    output = nnobj1(img)
    result_loss = nnloss1(output, idx)
    nnoptim1.zero_grad()    #清除梯度
    result_loss.backward()      #反向传播，产生梯度信息可以进行优化
    nnoptim1.step()     #优化