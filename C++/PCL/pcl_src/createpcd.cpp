#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcdpointtype.hpp>

int main(int argc,char** argv)
{
//声明自己定义的点云变量
    pcl::PointCloud<MyPointType> cloud;
//设置点云大小 
    cloud.points.resize(2);//2个点
    cloud.width = 2;
    cloud.height = 1;
//赋值点里面的变量 
    cloud.points[0].x = cloud.points[0].y = cloud.points[0].z=1;
    cloud.points[1].x = cloud.points[1].y = cloud.points[1].z=3;

    cloud.points[0].JoneAdd = 1.2;
    cloud.points[1].JoneAdd = 3.4;
//保存 
    pcl::io::savePCDFile("test2.pcd", cloud);
 
    return 0;


}
