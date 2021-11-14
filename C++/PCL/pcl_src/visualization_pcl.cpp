#include <iostream>
#include <ctime>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

//函数声明
void viewerOneOff(pcl::visualization::PCLVisualizer& viewer);
void viewerPsycho(pcl::visualization::PCLVisualizer& viewer);

/**CloudViewer类不能在多线程应用程序中使用
pcl::visualization::CloudViewer
pcl::visualization::PCLVisualizer
*/
int main(int argc, char** argv)
{
//声明一个点云 指针
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    //从PCD 中 读取点云
    pcl::io::loadPCDFile ("../maize.pcd", *cloud);


    /* 创建显示 类 实例 */
    pcl::visualization::CloudViewer viewer("Cloud Viewer"); 
 
    /* 显示点云 */
    viewer.showCloud(cloud);

	/* 回调函数执行一次   */
    viewer.runOnVisualizationThreadOnce (viewerOneOff);
    
	/* 回调函数 显示每刷新一帧 执行一次 */
    viewer.runOnVisualizationThread (viewerPsycho);

    /*持续显示*/
    while (!viewer.wasStopped ())
    {
    }

	return 0;
}


//回调函数
//仅执行一次的回调函数，在一个点添加一个球体
void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
{
     /* 设置背景颜色 */
    viewer.setBackgroundColor (1.0, 0.5, 1.0);
 
    /*生成一个点 设置为球体 */
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
 
    /*在一个点上添加 一个 球体*/
    viewer.addSphere (o, 0.25, "sphere", 0);
 
    /* 终端打印  仅显示一次  */
    std::cout << "i only run once" << std::endl;
 
}
//回调函数，显示每刷新一帧执行一次。添加一个数值 一直增加的字符串。
void viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
{
    /*记录 刷新 次数*/
    static unsigned count = 0;
 
    //生成 刷新 次数 语句的字符串
    std::stringstream ss;
    ss << "Once per viewer loop: " << count++;
 
     //除去 text 的id  否则会重复  打印 不出来
    viewer.removeShape ("text", 0);
 
    // 将变换的字符添加上去
    viewer.addText (ss.str(), 200, 300, "text", 0);
 
}



