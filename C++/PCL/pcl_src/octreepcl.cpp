#include <pcl/point_cloud.h>
#include <pcl/octree/octree.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib> 
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
/*
A创建一个八叉树并添加，然后转换内存，在添加B，此时多出来的就是不同的点云
A\B共享一个八叉树，实现空间点的检测
*/
int main(int argc, char** argv)
{
    //创建时间随机种子  取随机数用的
    srand((unsigned int)time(NULL));
 
    //声明一个点云 A  指针 并分配空间
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudA(new pcl::PointCloud<pcl::PointXYZ> );
 
    //定义点云大小  点云个数128个，无序
    cloudA->width = 128;
    cloudA->height = 1;
    cloudA->points.resize (cloudA->width * cloudA->height);
    //循环给点云赋值 通过 随机数  点云的坐标 0-64
    for (size_t i=0; i<cloudA->points.size (); ++i)
    {
        cloudA->points[i].x =64.0f* rand () / (RAND_MAX +1.0f);//RAND_MAX=32767   rand ()在（0-32767）
        cloudA->points[i].y =64.0f* rand () / (RAND_MAX +1.0f);
        cloudA->points[i].z =64.0f* rand () / (RAND_MAX +1.0f);
    }

 /* 设置分辨率 描述的是最低一级 八叉树 的 最小体素 的 尺寸
 https://www.cnblogs.com/icmzn/articles/4902691.html
 */
    float resolution =32.0f;
 
    /* 构建 八叉树 变化 检测 的 类 并设置 分辨率 */
    pcl::octree::OctreePointCloudChangeDetector<pcl::PointXYZ> octree(resolution);
	
	/* 赋值八叉树的 点云 */
    octree.setInputCloud(cloudA);//设置输入的点云
    octree.addPointsFromInputCloud();//将输入的点云添加到八叉树

 /*交换八叉树缓存，但是cloudA对应的八叉树仍在内存中
 点云cloudA 是参考点云，用其建立的八叉树对象描述它的空间分布。*/ 
    octree.switchBuffers();
    
     //声明一个点云 B  指针 并分配空间
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudB(new pcl::PointCloud<pcl::PointXYZ> );
 
    //定义点云大小  点云个数128个，无序
    cloudB->width =128;
    cloudB->height =1;
    cloudB->points.resize (cloudB->width *cloudB->height);
    //循环给点云赋值 通过 随机数  点云的坐标 0-64
    for (size_t i=0; i<cloudB->points.size (); ++i)
    {
        cloudB->points[i].x = 90.0f* rand () / (RAND_MAX +1.0f);
        cloudB->points[i].y = 90.0f* rand () / (RAND_MAX +1.0f);
        cloudB->points[i].z = 90.0f* rand () / (RAND_MAX +1.0f);
    }
	/* 赋值八叉树的 点云 */
    octree.setInputCloud(cloudB);//设置输入的点云
    octree.addPointsFromInputCloud();//将输入的点云添加到八叉树
	/*声明 B 比 A 多 出 的点云 的索引值 保存 向量*/
    std::vector<int> newPointIdxVector;
 
    /* 得到B比A 多出来的 索引值  注意 B 比 A  少的  不会得到  */
    octree.getPointIndicesFromNewVoxels(newPointIdxVector);

	// 终端打印 B 比 A 多出 来的  点云
    std::cout<<"Output from getPointIndicesFromNewVoxels:"<<std::endl;
    for (size_t i=0; i< newPointIdxVector.size (); ++i)
		std::cout<<i<<"# Index:"<<newPointIdxVector[i]
		<<"  Point:"<<cloudB->points[newPointIdxVector[i]].x <<" "
		<<cloudB->points[newPointIdxVector[i]].y <<" "
		<<cloudB->points[newPointIdxVector[i]].z <<std::endl;

 //声明一个点云 C  指针 并分配空间
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudC(new pcl::PointCloud<pcl::PointXYZ> );
    //定义点云大小  点云个数上面计算的 B 比 A 多出的 个，无序
    cloudC->width = newPointIdxVector.size ();
    cloudC->height = 1;
    cloudC->points.resize(cloudC->width *cloudC->height);
 
    for(size_t i=0;i<newPointIdxVector.size();++i)
    {
        cloudC->points[i]=cloudB->points[newPointIdxVector[i]];
 
    }
    //--------------------------------------
    //可视化模块  新建一个点云C来保存B比A多出来的点。
    pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("3D Viewwe"));//创建指针viewer
    viewer->initCameraParameters();//初始化相机参数
    //------------  
    int v1(0);//第一个窗口的参数
    viewer->createViewPort(0.0,0.0,0.33,1,v1); //设置第一个窗口的大小，位于屏幕左侧
    viewer->setBackgroundColor(0,0,0,v1);//background of first port
    viewer->addText("cloudA",10,10,"cloudA",v1);//好像是一个便签
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ>  single_color1(cloudA,255,0,0);//设置第一个点云的颜色
   // viewer->addPointCloud<pcl::PointXYZ>(cloudA,single_color1,"cloudA",v1);//显示第一个点云
    //------------
    int v2(0);//第一个窗口的参数//点云B显示为绿色
    viewer->createViewPort(0.33,0,0.66,1,v2);//设置第二个窗口的大小，位于屏幕右侧
    viewer->setBackgroundColor(0,0,0,v2);//background of second port
    viewer->addText("cloudB",10,9,"cloudB",v2);//输出一行文字
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color2(cloudB,0,255,0);//设置第二个点云的颜色
   // viewer->addPointCloud<pcl::PointXYZ>(cloudB,single_color2,"simple_cloud2",v2);//显示第二个点云
    //第三个点云窗口 //第三个窗口将点云A、B、C显示在一起
    int v3(0);//第三个窗口的参数//蓝色
    viewer->createViewPort(0.66,0,1,1,v3);//窗口大小
    viewer->setBackgroundColor(0,0,0,v3);//背景颜色
    viewer->addText("cloud_result",10,8,"cloud_result",v3);//好像是一个便签
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color3(cloudC,255,255,255);//点云颜色
 
    viewer->addPointCloud<pcl::PointXYZ>(cloudA,single_color1,"cloud1",v3);//显示点云
    viewer->addPointCloud<pcl::PointXYZ>(cloudB,single_color2,"cloud2",v3);//显示点云
    viewer->addPointCloud<pcl::PointXYZ>(cloudC,single_color3,"cloud3",v3);//显示点云
    viewer->addCoordinateSystem(2);//为所有窗口添加坐标系  2为坐标系的放大系数
    viewer->spin();
    

    return 0;


}
