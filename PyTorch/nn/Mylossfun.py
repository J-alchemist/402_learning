import torch
from torch import nn
from torch.nn import L1Loss, MSELoss

input = torch.tensor([1, 2, 3], dtype=torch.float32)
target = torch.tensor([1, 2, 5], dtype=torch.float32)

input = torch.reshape(input, (1,1,1,3))
target = torch.reshape(target, (1,1,1,3))

#L1Loss函数
#loss1 = L1Loss(reduction="mean")    #（0+0+2）/3
loss1 = L1Loss(reduction="sum")
result1 = loss1(input, target)
print(result1)

#MSELoss函数
loss2 = MSELoss()     # （5-3）平方/3
result2 = loss2(input, target)
print(result2)


#CrossEntropyLoss()分类常用的损失函数
x = torch.tensor([0.1, 0.2, 0.3])
y = torch.tensor([1])
x = torch.reshape(x, (1, 3))
loss_cross = nn.CrossEntropyLoss()
resultx = loss_cross(x, y)
print(resultx)

