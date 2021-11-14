#include <iostream>
#include <fstream>
using namespace std;
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Geometry>
#include <boost/format.hpp> // for formating strings
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/pcl_visualizer.h>
 
 
 
int main( int argc, char** argv )
{
    vector<cv::Mat> colorImgs,depthImgs;//彩色图和深度图
    vector<Eigen::Isometry3d> poses;//相机位姿
 
    ifstream fin("../pose.txt");//文件读入 相机位置 文件
 
    if(!fin)//相机位姿读入失败
    {
        cerr<<"请在有pose.txt的目录下运行此程序"<<endl;
        return 1;
    }
 
    for(int i=0;i<5;i++)
    {
        boost::format fmt("../%s/%d.%s");//图像文件格式  
        colorImgs.push_back(cv::imread((fmt%"color"%(i+1)%"png").str()));  // 读取彩色图像
        depthImgs.push_back( cv::imread( (fmt%"depth"%(i+1)%"pgm").str(), -1 )); // 使用 -1 读取原始图像
 
 
         //读取相机位姿
        double data[7]={0};
        for(auto& d:data)
               fin>>d;
            Eigen::Quaterniond q( data[6], data[3], data[4], data[5] );
            Eigen::Isometry3d T(q);
            T.pretranslate( Eigen::Vector3d( data[0], data[1], data[2] ));
            poses.push_back( T );
    }
 
     //相机内参
    double cx=325.5;
    double cy=253.5;
    double fx=518.0;
    double fy=519.0;
    double depthScale = 1000.0;
 
 
    cout<<"正在将图像转换为点云..."<<endl;
 
    //定义点云使用的格式  用XYZRGB
    typedef pcl::PointXYZRGB PointT;
    typedef pcl::PointCloud<PointT> PointCloud;
 
    //新建一个点云
    PointCloud::Ptr pointCloud( new PointCloud );
 
    for(int i=0;i<5;i++)
    {
        cout<<"转换图像中："<<i+1<<endl;
        cv::Mat color = colorImgs[i];//获得 要处理的彩色图像
        cv::Mat depth = depthImgs[i];//获得 要处理的深度图像
        Eigen::Isometry3d T = poses[i];//获得 对应的pose
        for(int v=0 ; v<color.rows;v++)//处理每个像素
        {
            for(int u=0 ; u<color.cols;u++)
            {
                unsigned int d = depth.ptr<unsigned short>(v)[u];//深度值
                if(d==0) continue;//为0 表示没有测量到
 
                Eigen::Vector3d point;//相机坐标系下的点
                //计算相机坐标系下的点的坐标
                point[2] = double(d)/depthScale;
                point[0] = (u-cx)*point[2]/fx;
                point[1] = (v-cy)*point[2]/fy;
 
 
                Eigen::Vector3d pointWorld = T*point;//转换到世界坐标系下
 
 
                PointT p;//声明点云
                p.x = pointWorld[0];//赋值点云位置
                p.y = pointWorld[1]; 
                p.z = pointWorld[2]; 
                p.b = color.data[ v*color.step+u*color.channels() ];//赋值点云对应RGB颜色
                p.g = color.data[ v*color.step+u*color.channels()+1 ];
                p.r = color.data[ v*color.step+u*color.channels()+2 ];
 
                pointCloud->points.push_back( p );
            }
        }
    }
 
 
        pointCloud->is_dense = false; 
        cout<<"点云共有"<<pointCloud->size()<<"个点."<<endl;
 
        pcl::io::savePCDFileBinary("map.pcd", *pointCloud );//保存点云文件
 
 
    return 0;
}



