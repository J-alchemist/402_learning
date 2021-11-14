import torchvision
from torch.utils.tensorboard import SummaryWriter

dataset_transform = torchvision.transforms.Compose([
    torchvision.transforms.ToTensor(),
    #...
])
train_set = torchvision.datasets.CIFAR10("./dataset", train=True, transform=dataset_transform, download=True)
test_set = torchvision.datasets.CIFAR10("./dataset", train=False, transform=dataset_transform, download=True)

# print(test_set[0])
# img, idx = test_set[0]
# print(test_set.classes[idx])
# img.show()

# tensorboard --logdir=logs --port=6007
writer = SummaryWriter("logs")

for i in range(10):
    img, idx = train_set[i]
    writer.add_image("test_set", img, i)

writer.close()