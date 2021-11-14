import torch
import torch.nn as nn   #类式接口
import torchvision
import torchvision.datasets
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter


#最大池化
#1
'''
input = torch.tensor([[1, 2, 0, 3, 1],
                      [0, 1, 2, 3, 1],
                      [1, 2, 1, 0, 0],
                      [5, 2, 3, 1, 1],
                      [2, 1, 0, 1, 1]], dtype=torch.float32)
print(input.shape)
input = torch.reshape(input, (-1, 1, 5, 5))  #尺寸变化来满足函数要求
print(input.shape)

class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.maxpool1 = nn.MaxPool2d(kernel_size=3, ceil_mode=True)

    def forward(self, input):
        output = self.maxpool1(input)
        return output

nnpool1 = Mynn_Model()
output = nnpool1(input)
print(output)
'''
#2
dataset = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)

dataloader = DataLoader(dataset, batch_size=64)

class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.maxpool1 = nn.MaxPool2d(kernel_size=3, ceil_mode=True)

    def forward(self, input):
        output = self.maxpool1(input, inplace=False) #inplace=False 保留原始数据input，结果赋给ouput
        return output

nnpool2 = Mynn_Model()

writer = SummaryWriter("./logs")
step = 0
for data in dataloader:
    img ,idx = data
    writer.add_image("input_pool", img, step, dataformats='NCHW')
    output = nnpool2(img)
    writer.add_image("output_pool", output, step, dataformats='NCHW')
    step = step + 1

writer.close()

