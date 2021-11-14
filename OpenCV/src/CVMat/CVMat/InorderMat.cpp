#include "InorderMat.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/*
//�ռ䴴������
Mat img(640, 480, CV_8UC3);//�ռ����뷽ʽ1
 //img.create(rows, cols, CV_8UC1);//�ռ����뷽ʽ2
int es = img.elemSize();//elemSize()��ȡ���ص��С��ÿ�����ص�����ֽڣ�

//�ռ��ͷ�
img.release();//��������
*/
void means1(void)
{
//�����ռ���� data[]
	Mat img(640, 480, CV_8UC3);
	int es = img.elemSize();
	int size = img.rows*img.cols*es;

	for (int i = 0; i<size; i += es)
	{
		//����һ�����ص����ɫ
		//mat�ռ�����ΪBGR˳��
		img.data[i] = 50;
		img.data[i + 1] = 50;
		img.data[i + 2] = 50;
	}
	namedWindow("Mat1", CV_WINDOW_AUTOSIZE);//CV_WINDOW_AUTOSIZE=�Զ���С
	imshow("Mat1", img);
}

void means2(void)
{
	//ptr�ӿڱ��� val[]����ֵ��ָ������
	Mat img(640, 480, CV_8UC3);
	for (int r = 0; r<img.rows; r++)
	{
		for (int l = 0; l<img.cols; l++)
		{
			Vec3b *p = img.ptr<Vec3b>(r, l);
			//  Vec3b *p = img.ptr<Vec3b>(r);//ֻ����ĳһ��
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
	//at�ӿڱ��� at[]����ֵ����������  try catch�쳣����
	Mat img(640, 480, CV_8UC3);
	try
	{
		for (int r = 0; r<img.rows; r++)
		{
			for (int c = 0; c<img.cols; c++)
			{
				Vec3b &p = img.at<Vec3b>(r, c);//��������
				//  Vec3b *p = img.ptr<Vec3b>(r);//ֻ����ĳһ��
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
	//ͨ������������ val[]
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


//ͼ��������޸�
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

//	cvtColor(src, togray, CV_BGR2GRAY);//�ı�ɫ��

	Mat rgbimg;
	rgbimg.create(src.size(), src.type());

	for (int r = 0; r < src.rows; r++) {
		for (int c = 0; c < src.cols; c++) {

			if (src.elemSize() == 1) { //�Ҷ�ͼ   //����ʱ��src.elemSize()��Ϊtogray.elemSize(),����cvtColor();
				uchar &p = togray.at<uchar>(r, c);
				//�޸�����
				p = 255 - p;//pΪ��������ʱ�����������ֵ��p��Ϊ��ͨ����������� togray.at<uchar>(r, c) = 255 - p;
			}
			else if (src.elemSize() == 3) {//rgb
					Vec3b pre = src.at<Vec3b>(r, c);
					//�޸�����
					rgbimg.at<Vec3b>(r, c)[0] = 255 - pre[0];
					rgbimg.at<Vec3b>(r, c)[1] = 255 - pre[1];
					rgbimg.at<Vec3b>(r, c)[2] = 255 - pre[2];
					}

		}
	}
	//opencvֱ������ȡ��
//	bitwise_not(src, dst);

	namedWindow("demo", CV_WINDOW_AUTOSIZE);
//	imshow("demo", togray);
	imshow("demo", rgbimg);
}


