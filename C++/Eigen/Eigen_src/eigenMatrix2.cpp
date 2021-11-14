#include <iostream>
#include <Eigen/Dense>
 /*
 参考： https://blog.csdn.net/yxpandjay/article/details/80587916
 */ 
template <typename T>
static void matrix_mul_matrix(T* p1, int iRow1, int iCol1, T* p2, int iRow2, int iCol2, T* p3)
{
    if (iRow1 != iRow2) return;//检验矩阵乘法的合法性 
 
    //列优先
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map1(p1, iRow1, iCol1);
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map2(p2, iRow2, iCol2);
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map3(p3, iCol1, iCol2);
 
    //行优先   map容器 Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> 类型 
    // Eigen::Matrix：矩阵数据类型，行数Dynamic可扩展，列数Dynamic可扩展，按列/行存储 （默认按列） 
    //Matrix共有六个模板参数，常用的只有前三个。其前三个参数分别表示矩阵元素的类型、行数和列数大小。、行优先还是列
   // Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map1(p1, iRow1, iCol1);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map1(p1, iRow1, iCol1);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map2(p2, iRow2, iCol2);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map3(p3, iCol1, iCol2);
 
    map3 = map1 * map2;
}
 
int main(int argc, char* argv[])
{
    //1. 矩阵的定义
    std::cout << "矩阵定义："<< std::endl;    
    Eigen::MatrixXd m(2, 2);
    Eigen::Vector3d vec3d; //typedef  Matrix< double , 3 , 1>  Vector3d 
    Eigen::Vector4d vec4d(1.0, 2.0, 3.0, 4.0);
 	std::cout << vec4d << std::endl << std::endl;//列矩阵 4x1  列向量 
 	
    //2. 动态矩阵、静态矩阵
    Eigen::MatrixXd matrixXd;
    Eigen::Matrix3d matrix3d;
 
    //3. 矩阵元素的访问
    std::cout << "矩阵元素访问："<< std::endl;
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = m(0, 0) + 3; 
    m(1, 1) = m(0, 0) * m(0, 1);
    std::cout << m << std::endl << std::endl;
 
    //4. 设置矩阵的元素
    std::cout << "初始化元素："<< std::endl;    
    m << -1.5, 2.4,
          6.7, 2.0;  
    std::cout << m << std::endl << std::endl; 
    int row = 4;
    int col = 5;
    Eigen::MatrixXf matrixXf(row, col);
    matrixXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    std::cout << matrixXf << std::endl << std::endl;
    matrixXf << Eigen::MatrixXf::Identity(row, col);//用rowXcol列的单位矩阵对x变量进行了初始化 
    std::cout << matrixXf << std::endl << std::endl;
 
    //5. 重置矩阵大小
    std::cout << "重置大小："<< std::endl;
    Eigen::MatrixXd matrixXd1(3, 3);
    //使用”=”操作符操作动态矩阵时，如果左右两边的矩阵大小不等，则左边的动态矩阵的大小会被修改为右边的大小 
    m = matrixXd1;//m原来为2x2 ，任意扩展 
    std::cout << m.rows() << "  " << m.cols() << std::endl << std::endl;// rows()， cols() 

    //6. 矩阵运算
    std::cout << "加法、乘法："<< std::endl;
    m << 1, 2, 7,
        3, 4, 8,
        5, 6, 9;
    std::cout << m << std::endl;
    matrixXd1 = Eigen::Matrix3d::Random();	// 随机 生成3x3矩阵  随机值介于 -1 和 1 之间
    m += matrixXd1;		//加法 
    std::cout << m << std::endl << std::endl;
    m *= 2;		//乘法 
    std::cout << m << std::endl << std::endl;
    std::cout << -m << std::endl << std::endl;//取反，但是m仍然是m，并不会吧-m赋予m 
 
    //7. 求矩阵的转置、共轭矩阵、伴随矩阵
    std::cout << "转置、共轭、伴随："<< std::endl;
    std::cout << m << std::endl << std::endl;
    std::cout << m.transpose() << std::endl << std::endl;
    /*
	共轭：实部相同，虚部相反数
	共轭矩阵： 每个元素取共轭得到的矩阵 	
	共轭转置矩阵：矩阵本身先转置再把矩阵中每个元素取共轭得到的矩阵 		
	自共轭转置矩阵：转置、取共轭等于本身 
	注意说法！！ 
	*/ 
    std::cout << m.conjugate() << std::endl << std::endl;
    std::cout << m.adjoint() << std::endl << std::endl;
    std::cout << m << std::endl << std::endl;
    //m.transposeInPlace();//用m的转置矩阵代替m矩阵  //同理  conjugateInPlace()也是
	m = m.transpose();
    std::cout << m << std::endl << std::endl;
 
    //8. 矩阵相乘、矩阵向量相乘
    std::cout << "矩阵相乘、矩阵向量相乘："<< std::endl;
    std::cout << m*m << std::endl << std::endl;
    vec3d = Eigen::Vector3d(1, 2, 3);
    std::cout << m * vec3d << std::endl << std::endl;
    std::cout << vec3d.transpose()* m << std::endl << std::endl;//transpose转置，但不代替自己 
 
    //9. 矩阵的块操作
    std::cout << "矩阵的块操作："<< std::endl;    
    std::cout << m << std::endl << std::endl;
    std::cout << m.block(1, 1, 2, 2) << std::endl << std::endl;//输出m(1,1)开始的2x2子矩阵 
    std::cout << m.block<1, 2>(0, 0) << std::endl << std::endl;//从m(0,0)开始的1x2的子矩阵 
    std::cout << m.col(1) << std::endl << std::endl;//输出1列 
    std::cout << m.row(0) << std::endl << std::endl;//输出0行 
 
    //10. 向量的块操作
    std::cout << "向量的块操作："<< std::endl; 
    Eigen::ArrayXf arrayXf(10);//列向量 
    arrayXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    std::cout << vec3d << std::endl << std::endl;
    std::cout << arrayXf << std::endl << std::endl;
    std::cout << arrayXf.head(5) << std::endl << std::endl;//前5个 
    std::cout << arrayXf.tail(4) * 2 << std::endl << std::endl;//后4个 
 
    //11. 求解矩阵的特征值和特征向量
    std::cout << "特征值和特征向量："<< std::endl; 
    Eigen::Matrix2f matrix2f;
    matrix2f << 1, 2, 3, 4;
    	//类模板 定义Eigen::Matrix2f数据类型的变量 eigenSolver，并传入参数matrix2f 
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix2f>  eigenSolver(matrix2f);
    if (eigenSolver.info() == Eigen::Success) {
        std::cout << eigenSolver.eigenvalues() << std::endl << std::endl;// 特征值
        std::cout << eigenSolver.eigenvectors() << std::endl << std::endl;// 特征向量
    }
 
    //12. 类Map及动态矩阵的使用
    std::cout << "类Map及动态矩阵的使用："<< std::endl;     
    int array1[4] = { 1, 2, 3, 4 };
    int array2[4] = { 5, 6, 7, 8 };
    int array3[4] = {0};
    matrix_mul_matrix(array1, 2, 2, array2, 2, 2, array3);
    for (int i = 0; i < 4; i++)
        std::cout << array3[i] << std::endl;
  
	return 0;
}
