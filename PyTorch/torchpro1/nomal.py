import torch
import numpy as np

#张量定义
data = [[1, 2], [3, 4]]
x_data = torch.tensor(data)
print(x_data)

np_array = np.array(data)
print(type(np_array))
x_np = torch.from_numpy(np_array)
print(x_np)

x_ones = torch.ones_like(x_data)        #创建x_data大小的1张量
print(x_ones)

x_rand = torch.rand_like(x_data, dtype=torch.float)     #创建x_data大小的随机张量
print(x_rand)


shape = (2,3)		#元组类型, 描述张量的维数
rand_tensor = torch.rand(shape)  # 等价于 rand_tensor = torch.rand(2,3)
ones_tensor = torch.ones(shape,  dtype=torch.int32)
zeros_tensor = torch.zeros(shape, dtype=torch.int32)
print(rand_tensor)
print(ones_tensor)
print(ones_tensor)

print(zeros_tensor.shape)   #size
print(zeros_tensor.dtype)   #数据类型
print(zeros_tensor.device)  #设备类型

#张量操作
print("------------")
zeros_tensor[ : , 2] = 1       # 切片  第2列所有值1
print(zeros_tensor)

t1 = torch.cat([zeros_tensor, zeros_tensor, zeros_tensor], dim=1)   # 连接 dim（1/0）：按行/列 拼接
print(t1)

zeros_tensor1 = zeros_tensor * zeros_tensor  #对应元素相乘
print(zeros_tensor1)

zeros_tensor2 = zeros_tensor @ zeros_tensor.T  #矩阵乘法
print(zeros_tensor2)

#np与tensor的转换
t1 = torch.ones(2,2)
print(t1)
n1 = t1.numpy()
print(n1)
t1 = torch.from_numpy(n1)
print(t1)


