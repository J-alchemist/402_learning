#include "InorderMat.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*
//空间创建方法
Mat img(640, 480, CV_8UC3);//空间申请方式1
 //img.create(rows, cols, CV_8UC1);//空间申请方式2
int es = img.elemSize();//elemSize()获取像素点大小（每个像素点多少字节）

//空间释放
img.release();//或者析构
*/
void means1(void)
{
//连续空间访问 data[]
	Mat img(640, 480, CV_8UC3);
	int es = img.elemSize();
	int size = img.rows*img.cols*es;

	for (int i = 0; i<size; i += es)
	{
		//设置一个像素点的颜色
		//mat空间像素为BGR顺序，
		img.data[i] = 50;
		img.data[i + 1] = 50;
		img.data[i + 2] = 50;
	}
	namedWindow("Mat1", CV_WINDOW_AUTOSIZE);//CV_WINDOW_AUTOSIZE=自动大小
	imshow("Mat1", img);
}

void means2(void)
{
	//ptr接口遍历 val[]返回值是指针类型
	Mat img(640, 480, CV_8UC3);
	for (int r = 0; r<img.rows; r++)
	{
		for (int l = 0; l<img.cols; l++)
		{
			Vec3b *p = img.ptr<Vec3b>(r, l);
			//  Vec3b *p = img.ptr<Vec3b>(r);//只访问某一行
			p->val[0] = 0;
			p->val[1] = 255;
			p->val[2] = 0;
		}

	}
	namedWindow("Mat2", CV_WINDOW_AUTOSIZE);
	imshow("Mat2", img);
}

void means3(void)
{
	//at接口遍历 at[]返回值是引用类型  try catch异常捕获
	Mat img(640, 480, CV_8UC3);
	try
	{
		for (int r = 0; r<img.rows; r++)
		{
			for (int c = 0; c<img.cols; c++)
			{
				Vec3b &p = img.at<Vec3b>(r, c);//引用类型
				//  Vec3b *p = img.ptr<Vec3b>(r);//只访问某一行
				p[0] = 0;
				p[1] = 255;
				p[2] = 200;
			}

		}
	}
	catch (Exception &ex)
	{
		cout << ex.what() << endl;

	}

	namedWindow("Mat3", CV_WINDOW_AUTOSIZE);
	imshow("Mat3", img);
}

void means4(void)
{
	//通过迭代器遍历 val[]
	Mat img(640, 480, CV_8UC3);

	auto it_ing = img.begin<Vec3b>();
	auto it_end = img.end<Vec3b>();
	for (; it_ing != it_end; ++it_ing)
	{
		(*it_ing).val[0] = 2;
		(*it_ing).val[1] = 103;
		(*it_ing).val[2] = 2;
	}

	namedWindow("Mat4", CV_WINDOW_AUTOSIZE);
	imshow("Mat4", img);
}


//图像遍历并修改
void imagedeal(void)
{
	Mat src, togray;

	src = imread("F:\\OpenCV\\Resources\\10.jpg");
	if (!src.data){

		printf("couldn't open !!!");
		return;
	}
	namedWindow("src", CV_WINDOW_AUTOSIZE);
	imshow("src", src);

//	cvtColor(src, togray, CV_BGR2GRAY);//改变色域

	Mat rgbimg;
	rgbimg.create(src.size(), src.type());

	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {

			if (src.elemSize() == 1) { //灰度图   //测试时将src.elemSize()改为togray.elemSize(),并打开cvtColor();
				uchar &p = togray.at<uchar>(r, c);
				//修改像素
				p = 255 - p;//p为引用类型时，可以这个赋值，p若为普通变量，则必须 togray.at<uchar>(r, c) = 255 - p;
			}
			else if (src.elemSize() == 3) {//rgb
					Vec3b pre = src.at<Vec3b>(r, c);
					//修改像素
					rgbimg.at<Vec3b>(r, c)[0] = 255 - pre[0];
					rgbimg.at<Vec3b>(r, c)[1] = 255 - pre[1];
					rgbimg.at<Vec3b>(r, c)[2] = 255 - pre[2];
					}

		}
	}
	//opencv直接像素取反
//	bitwise_not(src, dst);

	namedWindow("demo", CV_WINDOW_AUTOSIZE);
//	imshow("demo", togray);
	imshow("demo", rgbimg);
}


