import torch
import torchvision
from torch import nn
from torch.nn import Sequential, Conv2d, MaxPool2d, Linear
from torch.nn.modules.flatten import Flatten
from torch.utils.data import DataLoader
from torch.utils.tensorboard import SummaryWriter
import time

from model import *     #   model.py必须与本文件再同一目录下！！！

#定义训练的设备
train_device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

#数据集
train_dataset = torchvision.datasets.CIFAR10("./data", train=True,
                                        transform=torchvision.transforms.ToTensor(), download=True)
test_dataset = torchvision.datasets.CIFAR10("./data", train=False,
                                        transform=torchvision.transforms.ToTensor(), download=True)
#大小
train_size = len(train_dataset)
test_size = len(test_dataset)
print("训练集长度：{0}, 测试集长度：{1}".format(train_size, test_size))

#加载数据集
train_dataloader = DataLoader(train_dataset, batch_size=64)
test_dataloader = DataLoader(test_dataset, batch_size=64)

#神经网络
cifar10obj = Model_Cifar10()
cifar10obj.to(train_device)

#损失函数
loss_fn = nn.CrossEntropyLoss()
loss_fn.to(train_device)

#优化器
learning_rate = 0.01    #学习效率
optimizer = torch.optim.SGD(cifar10obj.parameters(), lr = learning_rate)

#添加tensorboard图形化查看训练过程
writer = SummaryWriter("./logs")

#设置网络参数及训练
total_train_step = 0 #记录训练次数
total_test_step = 0  #记录测试次数
epoch = 30  #训练轮数

for i in range(epoch):
    print("------第{}/{}轮训练开始------".format(i+1, epoch))
    start_t = time.time()  # 开始时间

    cifar10obj.train()      #训练模式
    for datax in train_dataloader:
        imgx, targetx = datax

        imgx = imgx.to(train_device)    #cuda
        targetx = targetx.to(train_device)

        outputx = cifar10obj(imgx)      #过网络

        lossx = loss_fn(outputx, targetx)       #损失
        optimizer.zero_grad()       #优化器（反向传播）
        lossx.backward()
        optimizer.step()

        total_train_step = total_train_step + 1
        if total_train_step%100 == 0:
            print("-训练次数：{}， Loss：{}".format(total_train_step, lossx.item()))   #item()将tensor数据据转换为真实的数字，便于观看
            writer.add_scalar("train_loss", lossx.item(), total_train_step)

    end_t = time.time()  # 结束时间
    print("第{}轮训练时长：{}".format(i+1, end_t-start_t))

    #测试当前网络训练程度
    cifar10obj.eval()   #测试模式
    total_test_loss = 0     #总体损失
    total_accuracy = 0
    with torch.no_grad():
        for datax in test_dataloader:
            imgx, targetx = datax
            imgx = imgx.to(train_device)
            targetx = targetx.to(train_device)

            outputx = cifar10obj(imgx)  # 过网络
            lossx = loss_fn(outputx, targetx)  # 损失
            total_test_loss = total_test_loss + lossx.item()

            accuracy = (outputx.argmax(1) == targetx).sum()   #输出argmax(1)横向解锁，argmax(0)纵向
            total_accuracy = total_accuracy + accuracy
            total_accuracy = total_accuracy.item()  #!!!
    print("整体测试集的Loss：{}".format( total_test_loss ))
    print("整体测试集的正确率：{}".format( total_accuracy/test_size ))
    writer.add_scalar("test_loss", total_test_loss, total_test_step)
    writer.add_scalar("test_accuracy", total_accuracy/test_size, total_test_step)
    total_test_step = total_test_step + 1

    #保存每一轮的训练模型
    if total_accuracy/test_size > 0.62:
        torch.save(cifar10obj.state_dict(), "./models/cifar10_{}.pth".format(i+1))

writer.close()

'''
output = torch.tensor([
    [0.1, 0.3],
    [0.8, 0.5]
])
print(output.argmax(1))

preds = output.argmax(1)
target = torch.tensor([0,1])

print((preds==target).sum())
'''










