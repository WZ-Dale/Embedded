// 20191221
// ѧϰ��ע�� by wangze

#pragma once

#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

#include "E:\Projects\Opencv3_Demo\4_histogram_finder__imageComparator_integral\contentFinder.h"
#include "E:\Projects\Opencv3_Demo\4_histogram_finder__imageComparator_integral\colorhistogram.h"

int finder_Test() {
	// Read reference image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\baboon01.jpg");
	if (!image.data)
		return 0; 

	// initial window position
	cv::Rect rect(110, 45, 35, 45);
	cv::rectangle(image, rect, cv::Scalar(0, 0, 255));
	// ����������ROI
	// Baboon's face ROI
	cv::Mat imageROI = image(rect);

	cv::namedWindow("Image 1");
	cv::imshow("Image 1",image);

	// �õ�����������ֱ��ͼ
	// Get the Hue histogram of the Baboon's face
	int minSat=65;
	ColorHistogram hc;
	cv::Mat colorhist= hc.getHueHistogram(imageROI,minSat);

	ContentFinder finder;
	finder.setHistogram(colorhist);
	finder.setThreshold(0.2f);

	// Convert to HSV space (just for display)
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);

	// Split the image
	vector<cv::Mat> v;
	cv::split(hsv,v);

	// Eliminate pixels with low saturation
	cv::threshold(v[1],v[1],minSat,255,cv::THRESH_BINARY);
	cv::namedWindow("Saturation mask");
	cv::imshow("Saturation mask",v[1]);

	//--------------
	// Second image
	image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\baboon02.jpg");

	cv::namedWindow("Image 2");
	cv::imshow("Image 2",image);
	// ת��ΪHSV
	// Convert to HSV space
	cv::cvtColor(image, hsv, CV_BGR2HSV);
	// �õ�ɫ��ֱ��ͼ�ķ���ͶӰ
	// Get back-projection of hue histogram
	int ch[1]={0};
	finder.setThreshold(-1.0f); // no thresholding// ������ֵ����
	cv::Mat result= finder.find(hsv,0.0f,180.0f,ch);

	// Display back projection result
	cv::namedWindow("Backprojection on second image");
	cv::imshow("Backprojection on second image",result);

	// initial window position
	cv::rectangle(image, rect, cv::Scalar(0,0,255));
	// �þ�ֵƫ�Ʒ���������
	// search objet with mean shift
	cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
		10,     // iterate max 10 times// ������10��
		1);     // or until the change in centroid position is less than 1px// �������ƶ�����С��1������
	cout << "meanshift= " << cv::meanShift(result,rect,criteria) << endl;

	// draw output window
	cv::rectangle(image, rect, cv::Scalar(0,255,0));

	// Display image
	cv::namedWindow("Image 2 result");
	cv::imshow("Image 2 result",image);

	cv::waitKey();
	return 0;
}	