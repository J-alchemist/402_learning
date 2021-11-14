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

/* 声明 离群点滤波 后 的点云 */
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_OutRemove_filtered (new pcl::PointCloud<pcl::PointXYZ>);
 
    /* 声明 离群点滤波 的 类实例 */
    pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor_OutRemove;
    /* 设置输入点云 */
    sor_OutRemove.setInputCloud (cloud);
    /* 设置在进行统计时考虑查询点邻近点数 */
    sor_OutRemove.setMeanK (30);
    /* 设置判断是否为离群点 的 阈值  设置为1的 话 表示为：如果一个点的距离超过平均距离一个标准差以上则为离群点 */
    sor_OutRemove.setStddevMulThresh(1.0);
    //返回被滤掉的离群点
    //sor_OutRemove.setFilterLimitsNegative (0);
     /* 执行滤波 返回 滤波后 的 点云 */
    sor_OutRemove.filter (*cloud_OutRemove_filtered);
 
 
    /* 打印滤波前后的点数 */
    std::cout<<"size of clound :"<<cloud->points.size()<<"   size of  outremove "<<cloud_OutRemove_filtered->points.size()<<endl;
        // 显示体素滤波后的点云
    /* 创建显示 类 实例 */
    pcl::visualization::CloudViewer viewer1("Cloud Viewer VoxelGrid"); 
 
    /* 显示点云 */
    viewer1.showCloud(cloud_OutRemove_filtered);
 
        /*持续显示*/
    while (!viewer1.wasStopped ())
    {
    }

	return 0;
}
