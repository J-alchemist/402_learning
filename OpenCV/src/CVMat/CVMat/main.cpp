#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "InorderMat.h"

/* 迭代器效率最低，ptr和at效率差不多，
 * 直接地址访问效率差不多
 */
using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{

	imagedeal();

	waitKey(0);



	return 0;
}


