#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib> 
#include <cstring>
//function：（-p） or （not -p）
using namespace std;
/*
注意加命名空间
for循环括号里定义的变量，只存在再该for循环里，
出了for循环，该循环变量释放
argc：程序参数个数（默认为1,也就是程序名字）
argv[0]: 是程序名字
argv[1]：你输入的参数
*/
int main(int argc, char** argv)
{
	
	cout << argc <<endl;
	//用系统时间初始化随机种子
    	srand ((unsigned int) time (NULL));
	
	pcl::PointCloud<pcl::PointXYZ>  cloud_a,cloud_b,cloud_c;//存储连接xyz的cloud_c
	pcl::PointCloud<pcl::Normal>  n_cloud_b;
	pcl::PointCloud<pcl::PointNormal>  p_n_cloud_c;//存储连接xyz与normal后的点云
	
	size_t i=0;

	//设置a点云大小：3
	cloud_a.width = 3;
	cloud_a.height = 1;
	cloud_a.points.resize(cloud_a.width * cloud_a.height);//points.resize设置点云大小
	//strcmp等于，返回0
	if(strcmp(argv[1], "-p" ) == 0)//将a，b点云连接为c点云（纵向扩展数据）
	{
		cloud_b.width = 2;
		cloud_b.height = 1;
		cloud_b.points.resize( cloud_b.width * cloud_b.height );
	}
	else//字段连接（数据个数必须相同，横向扩展数据）
	{
		n_cloud_b.width = 3;
		n_cloud_b.height = 1;
		//如果是连接XYZ与normal 则生成3个
		n_cloud_b.points.resize(n_cloud_b.width * n_cloud_b.height);
	}
	//以下循环生成无序点云,填充上面定义的两种类型点云对象
	for(i= 0;i<cloud_a.points.size();++i)
	{	//cloud_a始终产生3个点
		cloud_a.points[i].x= 1024 * rand()/(RAND_MAX + 1.0f);
		cloud_a.points[i].y= 1024 * rand()/(RAND_MAX + 1.0f);
		cloud_a.points[i].z= 1024 * rand()/(RAND_MAX + 1.0f);
	}
	
	if(strcmp(argv[1],"-p") == 0)
	{
		for(i=0; i<cloud_b.points.size(); ++i)
		{//如果连接a+b=c则cloud_b用2个点作为xyz数据
			cloud_b.points[i].x= 1024 * rand()/(RAND_MAX+1.0f);
			cloud_b.points[i].y= 1024 * rand()/(RAND_MAX+1.0f);
			cloud_b.points[i].z= 1024 * rand()/(RAND_MAX+1.0f);
		}
	}
	else
	{
		for(i=0; i<n_cloud_b.points.size(); ++i)
		{
			//如果连接xyz + normal = xyznormal 则n_cloud_b用3个点作为normal数据
			n_cloud_b.points[i].normal[0] = 1024 * rand()/(RAND_MAX+ 1.0f);
			n_cloud_b.points[i].normal[1] = 1024 * rand()/(RAND_MAX+ 1.0f);
			n_cloud_b.points[i].normal[2] = 1024 * rand()/(RAND_MAX+ 1.0f);
		}
		
	}
	//打印数据cloud_a
	cout << "cloud_a: " <<endl;
	for(i=0; i<cloud_a.points.size(); ++i)
	{
		cout << cloud_a.points[i].x << " " 
			<< cloud_a.points[i].y << " " << cloud_a.points[i].z << endl; 
	}
	//根据功能打印
	cout << "cloud_b: " <<endl;
	if(strcmp(argv[1],"-p") == 0)
	{
		for(i=0; i< cloud_b.points.size(); ++i)
		{
			cout  << cloud_b.points[i].x << " " << 
					cloud_b.points[i].y << " " << cloud_b.points[i].z << endl; 
		}
	}
	else
	{
		for(i=0; i< n_cloud_b.points.size(); ++i)
		{
			cout << n_cloud_b.points[i].normal[0] << " " 
				<< n_cloud_b.points[i].normal[1] << " " << n_cloud_b.points[i].normal[2] << endl; 
		}		
		
	}
	//连接
	cout << "cloud_c: " <<endl;
	if(strcmp(argv[1],"-p") == 0)
	{
		//设置c点云大小
		int c_size = (cloud_a.height + cloud_b.height) * \
					(cloud_a.width + cloud_b.width);
		cloud_c.height = 1;
		cloud_c.points.resize(c_size);
		
		//连接点云
		cloud_c = cloud_a + cloud_b;
		
		//打印数据c点云
	
		for(i=0; i<cloud_c.points.size(); ++i)
		{
			cout << cloud_c.points[i].x << " " 
				<< cloud_c.points[i].y << " " << cloud_c.points[i].z << endl; 
			
		}
		
		
	}
	else
	{  	//设置c点云大小
		p_n_cloud_c.height = 1;
		p_n_cloud_c.points.resize(cloud_a.height * cloud_a.width);
		//连接字段 cloud_a n_cloud_b 
		pcl::concatenateFields(cloud_a, n_cloud_b, p_n_cloud_c);
		
		//打印数据c点云

		for(i=0; i< p_n_cloud_c.points.size(); ++i)
		{
			cout << p_n_cloud_c.points[i].x << " " 
				<< p_n_cloud_c.points[i].y << " " << p_n_cloud_c.points[i].z 
						<< p_n_cloud_c.points[i].normal[0] << " " << p_n_cloud_c.points[i].normal[1]
								<< " " << p_n_cloud_c.points[i].normal[2] << endl; 
			
		}
	}
	

	
	
	
	return 0;


}


