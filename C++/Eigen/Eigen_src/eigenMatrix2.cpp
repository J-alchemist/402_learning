#include <iostream>
#include <Eigen/Dense>
 /*
 �ο��� https://blog.csdn.net/yxpandjay/article/details/80587916
 */ 
template <typename T>
static void matrix_mul_matrix(T* p1, int iRow1, int iCol1, T* p2, int iRow2, int iCol2, T* p3)
{
    if (iRow1 != iRow2) return;//�������˷��ĺϷ��� 
 
    //������
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map1(p1, iRow1, iCol1);
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map2(p2, iRow2, iCol2);
    //Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> > map3(p3, iCol1, iCol2);
 
    //������   map���� Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ���� 
    // Eigen::Matrix�������������ͣ�����Dynamic����չ������Dynamic����չ������/�д洢 ��Ĭ�ϰ��У� 
    //Matrix��������ģ����������õ�ֻ��ǰ��������ǰ���������ֱ��ʾ����Ԫ�ص����͡�������������С���������Ȼ�����
   // Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map1(p1, iRow1, iCol1);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map1(p1, iRow1, iCol1);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map2(p2, iRow2, iCol2);
    Eigen::Map< Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >  map3(p3, iCol1, iCol2);
 
    map3 = map1 * map2;
}
 
int main(int argc, char* argv[])
{
    //1. ����Ķ���
    std::cout << "�����壺"<< std::endl;    
    Eigen::MatrixXd m(2, 2);
    Eigen::Vector3d vec3d; //typedef  Matrix< double , 3 , 1>  Vector3d 
    Eigen::Vector4d vec4d(1.0, 2.0, 3.0, 4.0);
 	std::cout << vec4d << std::endl << std::endl;//�о��� 4x1  ������ 
 	
    //2. ��̬���󡢾�̬����
    Eigen::MatrixXd matrixXd;
    Eigen::Matrix3d matrix3d;
 
    //3. ����Ԫ�صķ���
    std::cout << "����Ԫ�ط��ʣ�"<< std::endl;
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = m(0, 0) + 3; 
    m(1, 1) = m(0, 0) * m(0, 1);
    std::cout << m << std::endl << std::endl;
 
    //4. ���þ����Ԫ��
    std::cout << "��ʼ��Ԫ�أ�"<< std::endl;    
    m << -1.5, 2.4,
          6.7, 2.0;  
    std::cout << m << std::endl << std::endl; 
    int row = 4;
    int col = 5;
    Eigen::MatrixXf matrixXf(row, col);
    matrixXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20;
    std::cout << matrixXf << std::endl << std::endl;
    matrixXf << Eigen::MatrixXf::Identity(row, col);//��rowXcol�еĵ�λ�����x���������˳�ʼ�� 
    std::cout << matrixXf << std::endl << std::endl;
 
    //5. ���þ����С
    std::cout << "���ô�С��"<< std::endl;
    Eigen::MatrixXd matrixXd1(3, 3);
    //ʹ�á�=��������������̬����ʱ������������ߵľ����С���ȣ�����ߵĶ�̬����Ĵ�С�ᱻ�޸�Ϊ�ұߵĴ�С 
    m = matrixXd1;//mԭ��Ϊ2x2 ��������չ 
    std::cout << m.rows() << "  " << m.cols() << std::endl << std::endl;// rows()�� cols() 

    //6. ��������
    std::cout << "�ӷ����˷���"<< std::endl;
    m << 1, 2, 7,
        3, 4, 8,
        5, 6, 9;
    std::cout << m << std::endl;
    matrixXd1 = Eigen::Matrix3d::Random();	// ��� ����3x3����  ���ֵ���� -1 �� 1 ֮��
    m += matrixXd1;		//�ӷ� 
    std::cout << m << std::endl << std::endl;
    m *= 2;		//�˷� 
    std::cout << m << std::endl << std::endl;
    std::cout << -m << std::endl << std::endl;//ȡ��������m��Ȼ��m���������-m����m 
 
    //7. ������ת�á�������󡢰������
    std::cout << "ת�á�������棺"<< std::endl;
    std::cout << m << std::endl << std::endl;
    std::cout << m.transpose() << std::endl << std::endl;
    /*
	���ʵ����ͬ���鲿�෴��
	������� ÿ��Ԫ��ȡ����õ��ľ��� 	
	����ת�þ��󣺾�������ת���ٰѾ�����ÿ��Ԫ��ȡ����õ��ľ��� 		
	�Թ���ת�þ���ת�á�ȡ������ڱ��� 
	ע��˵������ 
	*/ 
    std::cout << m.conjugate() << std::endl << std::endl;
    std::cout << m.adjoint() << std::endl << std::endl;
    std::cout << m << std::endl << std::endl;
    //m.transposeInPlace();//��m��ת�þ������m����  //ͬ��  conjugateInPlace()Ҳ��
	m = m.transpose();
    std::cout << m << std::endl << std::endl;
 
    //8. ������ˡ������������
    std::cout << "������ˡ�����������ˣ�"<< std::endl;
    std::cout << m*m << std::endl << std::endl;
    vec3d = Eigen::Vector3d(1, 2, 3);
    std::cout << m * vec3d << std::endl << std::endl;
    std::cout << vec3d.transpose()* m << std::endl << std::endl;//transposeת�ã����������Լ� 
 
    //9. ����Ŀ����
    std::cout << "����Ŀ������"<< std::endl;    
    std::cout << m << std::endl << std::endl;
    std::cout << m.block(1, 1, 2, 2) << std::endl << std::endl;//���m(1,1)��ʼ��2x2�Ӿ��� 
    std::cout << m.block<1, 2>(0, 0) << std::endl << std::endl;//��m(0,0)��ʼ��1x2���Ӿ��� 
    std::cout << m.col(1) << std::endl << std::endl;//���1�� 
    std::cout << m.row(0) << std::endl << std::endl;//���0�� 
 
    //10. �����Ŀ����
    std::cout << "�����Ŀ������"<< std::endl; 
    Eigen::ArrayXf arrayXf(10);//������ 
    arrayXf << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10;
    std::cout << vec3d << std::endl << std::endl;
    std::cout << arrayXf << std::endl << std::endl;
    std::cout << arrayXf.head(5) << std::endl << std::endl;//ǰ5�� 
    std::cout << arrayXf.tail(4) * 2 << std::endl << std::endl;//��4�� 
 
    //11. �����������ֵ����������
    std::cout << "����ֵ������������"<< std::endl; 
    Eigen::Matrix2f matrix2f;
    matrix2f << 1, 2, 3, 4;
    	//��ģ�� ����Eigen::Matrix2f�������͵ı��� eigenSolver�����������matrix2f 
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix2f>  eigenSolver(matrix2f);
    if (eigenSolver.info() == Eigen::Success) {
        std::cout << eigenSolver.eigenvalues() << std::endl << std::endl;// ����ֵ
        std::cout << eigenSolver.eigenvectors() << std::endl << std::endl;// ��������
    }
 
    //12. ��Map����̬�����ʹ��
    std::cout << "��Map����̬�����ʹ�ã�"<< std::endl;     
    int array1[4] = { 1, 2, 3, 4 };
    int array2[4] = { 5, 6, 7, 8 };
    int array3[4] = {0};
    matrix_mul_matrix(array1, 2, 2, array2, 2, 2, array3);
    for (int i = 0; i < 4; i++)
        std::cout << array3[i] << std::endl;
  
	return 0;
}
