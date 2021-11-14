#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/octree/octree.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <vector>
#include <ctime>
 
using namespace std; 
using namespace pcl; 
int main(int argc, char** argv)
{
	
//用系统时间初始化随机种子
    srand ((unsigned int) time (NULL));//rand产生seed-RAND_MAX的数
 
    //声明一个点云指针 并分配空间
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	//pcl::PointCloud<pcl::PointXYZ>* cloudx;

    //定义点云大小  点云个数1000个，无序
    cloud->width =1000;
    cloud->height =1;
    cloud->points.resize (cloud->width * cloud->height);
 
    //循环给点云赋值 通过 随机数  点云的坐标 0-1024
    for(size_t i=0; i < cloud->points.size(); ++i)
    {
        cloud->points[i].x = 1024.0f* rand () / (RAND_MAX +1.0f);
        cloud->points[i].y = 1024.0f* rand () / (RAND_MAX +1.0f);
        cloud->points[i].z = 1024.0f* rand () / (RAND_MAX +1.0f);            
    }
	//--------------------
	//构建一个  搜索点 构建一个搜索点x、y、z，取值0-1024随机
    pcl::PointXYZ searchPoint;

    searchPoint.x = 1024.0f * rand () / (RAND_MAX +1.0f);
    searchPoint.y = 1024.0f * rand () / (RAND_MAX +1.0f);
    searchPoint.z = 1024.0f * rand () / (RAND_MAX +1.0f);
	
    // 创建一个 搜索后 保存 的 点的索引值 的 向量
    std::vector<int> pointIdxVec;
    //体素近邻参数，分辨率参数，就是该八叉树分为多少份
    float resolution = 128.0f;

    pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree(resolution);

    octree.setInputCloud(cloud);
    octree.addPointsFromInputCloud();
    /*执行体素近邻搜索  函数很简单  参数 就是 搜索的点  和返回的索引值 向量*/
    if (octree.voxelSearch(searchPoint, pointIdxVec))
    {
        // 打印 搜索 的 点 的位置
        std::cout<<"Neighbors within voxel search at ("<<searchPoint.x
        <<" "<<searchPoint.y
        <<" "<<searchPoint.z<<")"
        <<std::endl;
 
            //打印搜索到的点 的 位置
        for (size_t i=0; i<pointIdxVec.size (); ++i)
        {
            std::cout<<"    "<< cloud->points[pointIdxVec[i]].x 
            <<" "<< cloud->points[pointIdxVec[i]].y 
            <<" "<< cloud->points[pointIdxVec[i]].z << std::endl;
        }
    }
	
/*	//可视化
	pcl::visualization::CloudViewer viewer("Cloud Viewer");
	viewer.showCloud(cloud);
    while (!viewer.wasStopped ())
        {
 
        }
*/	
	return 0;

}




