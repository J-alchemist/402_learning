#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/QR>
#include <Eigen/Cholesky>

#define MATRIX_SIZE 2
using namespace std;

int main(int argc, char** argv) {
	
	double mat_determinant = 0.0;
	
    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrix_100;//100*100的动态矩阵
    matrix_100 = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);//随机产生
    matrix_100 = matrix_100.transpose() * matrix_100;//产生对称矩阵  A*A转置为 对称矩阵
    mat_determinant = matrix_100.determinant();
    cout << "Matrix determination:" << mat_determinant << endl;//计算行列式
    
    Eigen::Matrix<double,Eigen::Dynamic,1> vnd;	//列向量 vectorXd 
    vnd = Eigen::MatrixXd::Random(MATRIX_SIZE,1);
    Eigen::Matrix<double,Eigen::Dynamic,1> x;
    
    //AX=B
    cout << "QR result: "  << endl;
    x = matrix_100.colPivHouseholderQr().solve(vnd);//QR分解的结果
	cout << x << endl;
	
	
  
	cout<<"LLT result:" << endl;
	x = matrix_100.llt().solve(vnd);//LL分解的结果（Cholesky） 
	cout << x << endl;		



    return 0;
}
