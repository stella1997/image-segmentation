#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "SLIC.h"
#include "ComputeTime.h"

using namespace std;
using namespace cv;
typedef unsigned int UINT;

int main()
{
	int spNumMax = 200;
	double compactness = 10;
	int spNum = 0;

	Mat img = imread("test.jpg");
	int width = img.cols;
	int height = img.rows;
	int sz = width*height;
	UINT *reimg = new UINT[sz * 3];
	for (int c = 0; c<3; c++)
	{
		for (int i = 0; i<width; i++)
		{
			for (int j = 0; j<height; j++)

				reimg[c*(width*height) + i*height + j] = saturate_cast<unsigned int>(img.at<Vec3b>(j, i)[2 - c]);
		}
	}
	int* label = new int[sz];
	SLIC slic;
	ComputeTime ct;
	ct.Begin();
	slic.DoSuperpixelSegmentation_ForGivenNumberOfSuperpixels(reimg, height, width, label, spNum, spNumMax, compactness);
	cout << "slictimes" << ct.End() << "ms" << endl;
	Mat superpixels(img.size(), CV_16U);


	// 重新用一张Mat图来保存每个像素对应的标签，之后就能用opencv处理了
	for (int i = 0; i<superpixels.rows; i++)
	{
		for (int j = 0; j<superpixels.cols; j++)
		{
			superpixels.at<ushort>(i, j) = label[i + j*superpixels.rows];
		}
	}
	

	
	/*Mat Contoursimg;
	Contoursimg = img.clone();*/
	const int dx8[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	/*int sz = width*height;*/
	vector<bool> istaken(sz, false);
	vector<int> contourx(sz); vector<int> contoury(sz);
	int mainindex(0); int cind(0);
	for (int k = 0; k < width; k++)
	{
		for (int j = 0; j < height; j++)
		{
			int np(0);
			for (int i = 0; i < 8; i++)
			{
				int x = k + dx8[i];
				int y = j + dy8[i];

				if ((x >= 0 && x < width) && (y >= 0 && y < height))
				{
					/*int index = y*width + x;*/
					int index = x*height + y;
					//if( false == istaken[index] )//comment this to obtain internal contours
					{
						if (label[mainindex] != label[index]) np++;
						/*if (label[mainindex] != superpixels.at<ushort>(y, x)) np++;*/
					}
				}
			}
			if (np > 1)
			{
				contourx[cind] = k;
				contoury[cind] = j;
				istaken[mainindex] = true;
				//img[mainindex] = color;
				cind++;
			}
			mainindex++;
		}
	}
	//cout << mainindex << "," << cind << endl; 
	int numboundpix = cind;//int(contourx.size());
	for (int j = 0; j < numboundpix; j++)
	{
		/*int ii = contoury[j] * width + contourx[j];*/
		/*ubuff[ii] = 0xffffff;*/
		img.at<Vec3b>(contoury[j], contourx[j])[0] = 0xffffff;
		img.at<Vec3b>(contoury[j], contourx[j])[1] = 0xffffff;
		img.at<Vec3b>(contoury[j], contourx[j])[2] = 0xffffff;

		for (int n = 0; n < 8; n++)
		{
			int x = contourx[j] + dx8[n];
			int y = contoury[j] + dy8[n];
			if ((x >= 0 && x < width) && (y >= 0 && y < height))
			{
				/*int ind = y*width + x;*/
				int ind = x*height + y;
				if (!istaken[ind]) /*ubuff[ind] = 0;*/
				{
					img.at<Vec3b>(y, x)[0] = 0;
					img.at<Vec3b>(y, x)[1] = 0;
					img.at<Vec3b>(y, x)[2] = 0;
				}
			}
		}
	}
	imshow("supimg", img);
	imwrite("result.jpg", img);
	waitKey();
	return 0;
}