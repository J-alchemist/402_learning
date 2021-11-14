from torch.utils.data import DataLoader
import torchvision
from torch.utils.tensorboard import SummaryWriter

test_set = torchvision.datasets.CIFAR10("./dataset", train=False,
                transform=torchvision.transforms.ToTensor(), download=True)

'''
【args：】
batch_size：每次从数据集取多少个打包
drop_last：最后一次数据不足batch_size个时，是否舍去（False不舍去）
'''
test_loader = DataLoader(test_set, batch_size=64, shuffle=True,
                                num_workers=0,  drop_last=False)

img, idx = test_set[0]
print(img.shape)
print(idx)


writer = SummaryWriter("logs")
step = 0
for data in test_loader:
    imgs, idxs = data
   # print(imgs.shape)
   # print(idxs)
    writer.add_image("DataLoader_img", imgs, step, dataformats='NCHW')
    step = step + 1

writer.close()

