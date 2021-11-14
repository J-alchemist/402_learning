from torch.utils.tensorboard import SummaryWriter
from torchvision import transforms
import torch
import cv2
import numpy as np
from PIL import Image



img_path = "hymenoptera_data/train/ants/24335309_c5ea483bb8.jpg"
img = Image.open(img_path)
print(type(img))
print(img)

tensor_trans = transforms.ToTensor()  #创建ToTensor对象，类似的ToPILImage类
tensor_img = tensor_trans(img)  #转换为torch.Tensor类型
print(type(tensor_img))
print(tensor_img)

#归一化:Normalize()
print(tensor_img[0][0][0])  #归一化之前的像素值
trans_norm = transforms.Normalize([0.5,0.5,0.5], [0.5,0.5,0.5])
img_norm = trans_norm(tensor_img)
print(img_norm[0][0][0])   #归一化之后的像素值

writer = SummaryWriter("logs")
writer.add_image("tensor_img", tensor_img)
writer.add_image("img_norm", img_norm)


#resize()，并没有发生裁切！！
print(img.size)
trans_resize = transforms.Resize((300, 400))    #指定缩放的长宽
img_resize = trans_resize(img)
print(img_resize)
img_resize_tensor = tensor_trans(img_resize)
writer.add_image("img_resize", img_resize_tensor)

#compose()整合步骤: 先重置大小，再转换类型
trans_resize2 = transforms.Resize(400)  #将图片短边缩放至x，长宽比保持不变
trans_compose = transforms.Compose([trans_resize2, tensor_trans])
conpose_img = trans_compose(img)
writer.add_image("img_resizeandconpose", conpose_img)

writer.close()