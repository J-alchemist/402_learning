#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <cmath>
using namespace std;
 
int main(int argc, char** argv) {
	
    Eigen::Quaterniond q1(0.55,0.3,0.2,0.2);
    q1.normalize();//归一化 ，当前向量是不改变的并且返回一个新的规范化的向量 
	//单位化 
	//double a = sqrt(0.55*0.55 + 0.3*0.3 + 0.2*0.2 + 0.2*0.2);
	// Eigen::Quaterniond q1(0.55/a, 0.3/a, 0.2/a, 0.2/a); 
 
    Eigen::Quaterniond q2(-0.1,0.3,-0.7,0.2);
    q2 = q2.normalized();

    Eigen::Matrix<double,3,1> t1;
    t1<<0.7,1.1,0.2;
    Eigen::Matrix<double,3,1> t2;
    t2<<-0.1,0.4,0.8;
    Eigen::Matrix<double,3,1> p1;
    p1<<0.5,-0.1,0.2;
    Eigen::Matrix<double,3,1> p12;
    
    //欧氏变换矩阵T1（旋转矩阵 +平移向量 ） 
    Eigen::Isometry3d T1 = Eigen::Isometry3d::Identity(); //构造由Identity初始化(单位)的变换矩阵 4x4 
    cout << "T1 = \n" << T1.matrix() <<endl;	
    T1.rotate(q1.toRotationMatrix());//添加旋转矩阵   prerotate也可以 
    T1.pretranslate(t1);//添加平移向量 
  
    p1 = T1.inverse() * p1;//p1 = T*X ---> X = T^(-1)*p1  
    //构造变换矩阵T2   
    Eigen::Isometry3d T2 = Eigen::Isometry3d::Identity();
    T2.rotate(q2.toRotationMatrix());//四元素-->旋转矩阵  
    T2.pretranslate(t2);
    //用T2旋转p1 
    p12 = T2 * p1;

    cout<< "p12 = \n" << p12 <<endl; 
   
    return 0;
}
