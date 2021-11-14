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

/* 声明 投影 滤波 后 的点云 */
/*
将点投影到参数化模型上
*/
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_projected (new pcl::PointCloud<pcl::PointXYZ>);
 
    /*定义模型的系数对象，并填充 对应 的数据  如果是平面方程： ax+by+cz+d = 0  ，若投影到z平面 即 a、b、d 为0  c为1 */
    pcl::ModelCoefficients::Ptr  coefficients(new pcl::ModelCoefficients());
	//系数填充//若为其他曲面，需要更改下面适配参数个数，及增添必要参数
    coefficients->values.resize(4);
    coefficients->values[0] = 0;
    coefficients->values[1] = 0;
    coefficients->values[2] = 1;
    coefficients->values[3] = 0;
 
    /* 声明 投影滤波 的 类实例  */
    pcl::ProjectInliers<pcl::PointXYZ> proj;
    /* 设置参数化模型的类型 */
    proj.setModelType (pcl::SACMODEL_PLANE);
    /* 设置输入点云 */
    proj.setInputCloud (cloud);
    /* 设置上面填充完的模型 */
    proj.setModelCoefficients (coefficients);
    /*  执行滤波 返回 滤波后 的 点云 */
    proj.filter (*cloud_projected);
	
	
    /* 创建显示 类 实例 */
    pcl::visualization::CloudViewer viewer1("Cloud Viewer VoxelGrid"); 
    /* 显示点云 */
    viewer1.showCloud(cloud_projected);
        /*持续显示*/
    while (!viewer1.wasStopped ())
    {
    }

	return 0;
}
