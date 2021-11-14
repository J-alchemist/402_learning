#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

int main(int argc,char** argv)
{
    /*创建一个点云变量 的共享指针  并实例化*/
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
 
      /*从 pcd文件  读取 点云*/   //若写相对路径的话，相对于可执行文件而言
    if(pcl::io::loadPCDFile<pcl::PointXYZ>("/home/gj/pcl_pro/t1/pcd/test_pcd.pcd",*cloud)==-1)
    {    
        //  返回值是 -1  代表 没有读到
        PCL_ERROR("Couldn't read file test_pcd.pcd \n");
        return  (-1);
    }
 
      //计算点云数量   打印相关信息
    std::cout<<"Loaded "<<cloud->width*cloud->height<<" data points from test_pcd.pcd with the following fields: "<<std::endl;
 
    /*遍历输出 各点云的内容*/
    for(size_t i=0;i<cloud->points.size();++i)
    {
        std::cout<<"    "<<cloud->points[i].x
        <<" "<<cloud->points[i].y
        <<" "<<cloud->points[i].z<<std::endl;
    }

    return 0;


}
