import torchvision, torch
from torch import nn
#train_data = torchvision.datasets.ImageNet("./ImageNetdata", train=False,
#                                        transform=torchvision.transforms.ToTensor(), download=True)

#现有网络模型加载
vgg16_false = torchvision.models.vgg16(pretrained=False)
vgg16_true = torchvision.models.vgg16(pretrained=True)  # True已训练好的参数

print(vgg16_true)

#网络修改，应用于CIFAR10
#vgg16网络输出1000类，但是CIFAR10只是10类
train_data = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)
#1   增加一层
vgg16_true.classifier.add_module('add_linear', nn.linear(1000, 10))  # 1000--->10
print(vgg16_true)
#2   修改某层
vgg16_false.classifier[6] = nn.Linear(4096, 10)
print(vgg16_false)

#模型保存
#方式1: 保存了模型及参数
torch.save(vgg16_false, "./vgg16_false1.pth")
# 加载1(若是加载自定义模型，需要再加载文件import导入该网络)
vgg16_false1_mode = torch.load("./vgg16_false1.pth")
print(vgg16_false1_mode)

#方式2： 只保存参数(官方推荐)
torch.save(vgg16_false.state_dict(), "./vgg16_false2.pth")
# 加载2（要加载模型）
vgg16_false2_mode = torchvision.models.vgg16(pretrained=False)  #定义一个网络对象
vgg16_false2_mode.load_state_dict( torch.load("./vgg16_false2.pth") ) #再加载数据
print(vgg16_false2_mode)
