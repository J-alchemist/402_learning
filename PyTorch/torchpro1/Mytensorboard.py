from torch.utils.tensorboard import SummaryWriter
import torch
import cv2
from PIL import Image
import numpy as np
from torchvision import transforms

writer = SummaryWriter("logs")

# tensorboard --logdir=logs --port=6007
# 1-函数
for x in range(100):
    # 记录标量，三个参数分别为曲线的名称、曲线的y值、曲线的x值
    writer.add_scalar('y=3x', x * 3, x)

# 2-图像
img_src = cv2.imread("hymenoptera_data/train/ants/188552436_605cc9b36b.jpg")
print(type(img_src))
# cv2.imshow("Myimage", img)
# cv2.waitKey(0)
# cv2.destroyAllWindows()

img_des = torch.from_numpy(img_src)   #转换为torch.Tensor类型  只是与下面转换方式的通道有所不同
print(type(img_des))
print(img_des.shape)   #size
print(img_des.dtype)   #数据类型
print(img_des.device)  #设备类型
#print(img_des)
writer.add_image("Myimage2", img_des, 1, dataformats='HWC')

'''
tensor_trans = transforms.ToTensor()  #创建ToTensor对象
tensor_img = tensor_trans(img_src)  #转换为torch.Tensor类型   为chw模式
print(type(tensor_img))
print(tensor_img.shape)   #size
print(tensor_img.dtype)   #数据类型
print(tensor_img.device)  #设备类型
#print(tensor_img)
writer.add_image("Myimage1", tensor_img, 1, dataformats='CHW')
'''

writer.close()



