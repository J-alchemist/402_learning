import torch
import torch.nn as nn   #类式接口
from torch.nn import ReLU, Sigmoid
import torchvision
import torchvision.datasets
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter

#非线性化
'''
#1
input = torch.tensor([[1, -0.5],
                      [-1,   3]])

input = torch.reshape(input, (-1, 1, 2, 2))
print(input.shape)

class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.relu1 = ReLU(inplace=False)

    def forward(self, input):
        output = self.relu1(input)
        return output

nnrelu1 = Mynn_Model()
nnoutput = nnrelu1(input)
print(nnoutput)
'''
#2
dataset = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)

dataloader = DataLoader(dataset, batch_size=64)

class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.relu1 = ReLU(inplace=False)
        self.sigmoid1 = Sigmoid()

    def forward(self, input):
        output = self.sigmoid1(input)
        return output

nnrelu2 = Mynn_Model()
writer = SummaryWriter("./logs")
step = 0
for data in dataloader:
    img ,idx = data
    writer.add_image("input_relu", img, step, dataformats='NCHW')
    output = nnrelu2(img)
    writer.add_image("output_relu", output, step, dataformats='NCHW')
    step = step + 1

writer.close()


















