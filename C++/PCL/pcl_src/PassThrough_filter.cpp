#include <iostream>
#include <ctime>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/passthrough.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>

int main(int argc, char** argv)
{

//声明一个点云 指针
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
 
    //从PCD 中 读取点云
    pcl::io::loadPCDFile ("../wolf.pcd", *cloud);

/* 声明 直通滤波 后 的点云 */
/*
对指定的某一纬度实行一个简单的滤波，即去掉指定范围内部或者外部的点
*/
//cloud_PassThrough_filtered为Ptr指针类型
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_PassThrough_filtered (new  pcl::PointCloud<pcl::PointXYZ>);
 
    /* 声明直通滤波 的 类实例 */
    pcl::PassThrough< pcl::PointXYZ >  pass;
    /* 设置输入点云 */
    pass.setInputCloud (cloud);
    /* 设置滤波的维度 */
    pass.setFilterFieldName ("z");
    /* 设置滤波的范围 */
    pass.setFilterLimits (-50.0,50.0);
    /* 设置去掉的 是 范围内（true） 还是 范围外（false）   */
    pass.setFilterLimitsNegative (1);
    //pass.setFilterLimitsNegative (0);
    /* 执行滤波 返回 滤波后 的 点云 */
    pass.filter (*cloud_PassThrough_filtered);
 
 
    // 显示直通滤波后的点云
    /* 创建显示 类 实例 */
    pcl::visualization::CloudViewer viewer1("Cloud Viewer PassThrough"); 
 
    /* 显示点云 */
    viewer1.showCloud(cloud_PassThrough_filtered);
 
        /*持续显示*/
    while (!viewer1.wasStopped ())
    {
    }

	return 0;
}
