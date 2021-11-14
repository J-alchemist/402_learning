#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/compression/compression_profiles.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/cloud_viewer.h>

int main(int argc, char** argv)
{
 /* 
//构建多个点云数据，通过代码生成
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr(new  pcl::PointCloud<pcl::PointXYZRGB>());;
 
  uint8_t r(255), g(15), b(15);
  for (float z(-1.0); z <= 1.0; z += 0.1)//z轴点云层数
  {
    for (float angle(0.0); angle <= 360.0; angle += 60.0)
    {
		//基点
      pcl::PointXYZ basic_point;
      basic_point.x = 0.5 * cosf(float(angle/180*M_PI));//float cos(xx);
      basic_point.y = sinf(float(angle/180*M_PI));
      basic_point.z = z;
		//给到最后数据
      pcl::PointXYZRGB point;
      point.x = basic_point.x;
      point.y = basic_point.y;
      point.z = basic_point.z;
		//给到颜色数据
      uint32_t rgb = (static_cast<uint32_t>(r) << 16 |
              static_cast<uint32_t>(g) << 8 | static_cast<uint32_t>(b));
      point.rgb = *reinterpret_cast<float*>(&rgb);//将引用rgb转化为float*类型指针，再用*取出值给 point.rgb，此point.rgb的rgb非你自己定义的rgb
      point_cloud_ptr->points.push_back (point);
    }
	//颜色变化
    if (z < 0.0)
    {
      r -= 12;
      g += 12;
    }
    else
    {
      g -= 12;
      b += 12;
    }
  }
   point_cloud_ptr->width = (int) point_cloud_ptr->points.size ();
   point_cloud_ptr->height = 1;   
 
   pcl::io::savePCDFile("creat_xyzrgb.pcd",*point_cloud_ptr);*/
//-------------------------------------------------
/*以下与conpressXYZ一样的压缩操作*/
    /*创建一个点云变量 的共享指针  并实例化*/
    pcl::PointCloud<pcl::PointXYZ> cloud;
          /*从 pcd文件  读取 点云*/
    if(pcl::io::loadPCDFile<pcl::PointXYZ>("/home/gj/pcl_pro/t3/build/src/bin/creat_xyzrgb.pcd",cloud)==-1)
    {    
        //  返回值是 -1  代表 没有读到
        PCL_ERROR("Couldn't read file test_pcd.pcd \n");
        return  (-1);
    }
//打印压缩前从文件中读取的点云
 /*   std::cout <<"before: "<< std::endl;
    for(size_t i;i<cloud.points.size();++i)
    {
        std::cout<<"x="<<cloud.points[i].x<<"\t"<<"y="<<cloud.points[i].y<<"\t"<<"z="<<cloud.points[i].z<<std::endl;
	
    }
    */
    /* 压缩选项  可以参考 usr/include/pcl/compression/compression_profiles.h   */    
    pcl::io::compression_Profiles_e compressionProfile = pcl::io::MANUAL_CONFIGURATION;//设定为允许为高级参数化进行手工配置
    
    /*声明八叉树的压缩 变量  指针*/
    pcl::io::OctreePointCloudCompression<pcl::PointXYZ>* PointCloudEncoder;
    /* 设置压缩 和解压 时 的结果信息是否打印显示出来  */
    //bool showStatistics = true ;
    bool showStatistics = false;
        /*  进行 八叉树 的 压缩 配置  */
    PointCloudEncoder=new pcl::io::OctreePointCloudCompression<pcl::PointXYZ>(compressionProfile,showStatistics,0.001,0.01,true,100,true,8);//输入6个参数
    
    //压缩的字节流
    std::stringstream compressedData;
 
        /* 实现压缩的函数   第一个参数要求时只能指针，  .makeShared()即将cloud转成了 ptr */
    PointCloudEncoder->encodePointCloud(cloud.makeShared(),compressedData);
    
   //声明 解压 缩 后的 点云 指针
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloudOut(new pcl::PointCloud<pcl::PointXYZ>());
 
    /* 实现 解压缩 的 地方 第一个参数字节流 第二个参数 点云指针*/
    PointCloudEncoder->decodePointCloud(compressedData, cloudOut);
    
    
//打印解压缩后的点云坐标
/*
    std::cout<<"after: "<<std::endl;
    for(size_t i;i<cloudOut->points.size();++i)
    {
 
        std::cout<<"x="<<cloudOut->points[i].x<<"\t"<<"y="<<cloudOut->points[i].y<<"\t"<<"z="<<cloudOut->points[i].z<<std::endl;
    } 
*/
    pcl::visualization::CloudViewer viewer("Viewer");
    viewer.showCloud(cloudOut);//gui show
	while (!viewer.wasStopped ())
	{
	}

    return 0;

}



