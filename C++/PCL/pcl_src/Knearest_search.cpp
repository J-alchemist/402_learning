#include <pcl/point_cloud.h>
#include <pcl/octree/octree.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib> 
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/octree/octree_container.h>
#include <pcl/octree/octree_pointcloud_changedetector.h>

int main(int argc,char**argv)
{

	//用系统时间初始化随机种子
    srand((unsigned int)time(NULL));
 
    //声明一个点云指针 并分配空间
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
 
    //定义点云大小  点云个数1000个，无序
    cloud->width = 1000;
    cloud->height = 1;
    cloud->points.resize (cloud->width * cloud->height);
 
    //循环给点云赋值 通过 随机数  点云的坐标 0-1024
    for(size_t i=0;i<cloud->points.size(); ++i)
    {
        cloud->points[i].x =1024.0f* rand () / (RAND_MAX +1.0f);
        cloud->points[i].y =1024.0f* rand () / (RAND_MAX +1.0f);
        cloud->points[i].z =1024.0f* rand () / (RAND_MAX +1.0f);            
    }
//---------------------------------
//构建一个  搜索点
    pcl::PointXYZ searchPoint;
    searchPoint.x=1024.0f* rand () / (RAND_MAX +1.0f);
    searchPoint.y=1024.0f* rand () / (RAND_MAX +1.0f);
    searchPoint.z=1024.0f* rand () / (RAND_MAX +1.0f);
   //设置K的个数
    int K = 10;
    // 创建一个 搜索后 保存 的 点的索引值 的 向量
    std::vector<int> pointIdxNKNSearch;
    // 创建一个 搜索后 保存 的 点的距离平方值 的 向量
    std::vector<float> pointNKNSquaredDistance;
 
    //打印 K近邻 搜索 的点  和 K个数
    std::cout<<"K nearest neighbor search at ("<<searchPoint.x
    <<" "<<searchPoint.y
    <<" "<<searchPoint.z
    <<") with K="<< K <<std::endl;
 
    /*执行 K近邻 搜索  函数 参数 搜索点K个  搜索结果的点索引值存放向量  搜索结果点距离平方存放向量*/
    float resolution = 128.0f;//分辨率

    pcl::octree::OctreePointCloudSearch<pcl::PointXYZ> octree(resolution);

    octree.setInputCloud (cloud);
    octree.addPointsFromInputCloud ();


    if (octree.nearestKSearch (searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) >0)
    {
         //打印搜索到的点 的 位置 和距离
        for (size_t i=0; i<pointIdxNKNSearch.size (); ++i)
        {
            std::cout<<"    "<<   cloud->points[ pointIdxNKNSearch[i] ].x 
            <<" "<< cloud->points[pointIdxNKNSearch[i] ].y 
            <<" "<< cloud->points[pointIdxNKNSearch[i] ].z 
            <<" (squared distance: "<<pointNKNSquaredDistance[i] <<")"<<std::endl;
        }
    }

	return 0;
}

