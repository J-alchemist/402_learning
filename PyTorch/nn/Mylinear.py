import torch
import torchvision
from torch import nn
from torch.nn import Linear
from torch.utils.data import DataLoader


#线性层
dataset = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)

dataloader = DataLoader(dataset, batch_size=64)

class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        self.linear1 = Linear(196608, 10)

    def forward(self, input):
        output = self.linear1(input)
        return output

nnlinear1 = Mynn_Model()

for data in dataloader:
    img ,idx = data
    print(img.shape)
    #output = torch.reshape(img, (1, 1, 1, -1))  #变为1堆，1通道，1*x的格式
    output = torch.flatten(img)     #变为一行
    print(output.shape)
    output2 = nnlinear1(output)
    print(output2.shape)