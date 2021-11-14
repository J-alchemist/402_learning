import torch
import torch.nn as nn   #类式接口
import torch.nn.functional as F #函数式接口
import cv2
import torchvision.datasets
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter


#1-卷积层
dataset = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)

dataloader = DataLoader(dataset, batch_size=64)

class Mynn_Model(nn.Module):

    def __init__(self):
        super(Mynn_Model, self).__init__()
        #in_channels输入图像的通道数
        #out_channels卷积产生的通道数（卷积核的种类数）
        self.conv1 = nn.Conv2d(in_channels=3, out_channels=6, kernel_size=3,
                                stride=1, padding=0)

    def forward(self, x):
        x = self.conv1(x)
        return x

nnobj1 = Mynn_Model()
print(nnobj1)

writer = SummaryWriter("./logs")
step = 0
for data in dataloader:
    img, idx = data
    output = nnobj1(img)
    print(img.shape)
    print(output.shape)         # 卷积一次变为： 32-3+1
    writer.add_image("nn1", img, step, dataformats='NCHW')

    output = torch.reshape(output, (-1, 3, 30, 30)) #将6通道转换为3通道
    writer.add_image("nn2", output, step, dataformats='NCHW')
    step += 1

'''
#2-conv2d用法
img_src = cv2.imread("E:\\PyTorch\\torchpro1\\hymenoptera_data\\train\\ants\\150801171_cd86f17ed8.jpg")
# cv2.imshow("img_src", img_src)
# cv2.waitKey(0)
# cv2.destroyAllWindows()
input = torch.tensor([[1, 2, 0, 3, 1],
                      [0, 1, 2, 3, 1],
                      [1, 2, 1, 0, 0],
                      [5, 2, 3, 1, 1],
                      [2, 1, 0, 1, 1]])
kernel = torch.tensor([[1, 2, 1],
                       [0, 1, 0],
                       [2, 1, 0]])
print(input.shape)
print(kernel.shape) #此尺寸不满足
#需要进行尺寸变换
input = torch.reshape(input, [1, 1, 5, 5])
kernel = torch.reshape(kernel, [1, 1, 3, 3])
print(input.shape)
print(kernel.shape)

output1 = F.conv2d(input, kernel, stride=1)  #stride步进
print(output1)

output2 = F.conv2d(input, kernel, stride=1, padding=1)  #padding图形四周添加一圈像素，像素值为0
print(output2)
'''


'''
w = torch.rand(16, 3, 5, 5)  # 16种3通道的5乘5卷积核
b = torch.rand(16)  # 和卷积核种类数保持一致(不同通道共用一个bias)
x = torch.randn(1, 3, 28, 28)  # 1张3通道的28乘28的图像
out = F.conv2d(x, w, b, stride=1, padding=1)  # 步长为1,外加1圈padding
print(out.shape)
'''