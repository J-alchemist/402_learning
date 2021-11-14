import torch
from torch import nn
from torch.nn import Sequential, Conv2d, MaxPool2d, Linear
from torch.nn.modules.flatten import Flatten

#搭建神经网络
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

#网络正确性测试
if __name__ == '__main__':
    cifar10obj = Model_Cifar10()
    input = torch.ones((64, 3, 32, 32))
    output = cifar10obj(input)
    print(output.shape)



