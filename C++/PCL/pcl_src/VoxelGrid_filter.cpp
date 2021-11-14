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

/* 声明 体素滤波 后 的点云 */
/*
采样，即减少点的数量，并同时保持点云的特征
*/
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_VoxelGrid_filtered (new pcl::PointCloud<pcl::PointXYZ>);
 
    /* 声明体素滤波 的 类实例 */
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    /* 设置输入点云 */
    sor.setInputCloud (cloud);
    /* 设置体素滤波的参数 */  //10.1 米的立方体
    sor.setLeafSize (10.1f, 10.1f, 10.1f);
    /* 执行滤波 返回 滤波后 的 点云 */
    sor.filter (*cloud_VoxelGrid_filtered);
 
        // 显示体素滤波后的点云
    /* 创建显示 类 实例 */
    pcl::visualization::CloudViewer viewer1("Cloud Viewer VoxelGrid"); 
 
    /* 显示点云 */
    viewer1.showCloud(cloud_VoxelGrid_filtered);
 
        /*持续显示*/
    while (!viewer1.wasStopped ())
    {
    }

	return 0;
}
