// 20191208
// ѧϰ��ע�� by wangze

#pragma once

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int addImages_Test() {
	cv::Mat image1;
	cv::Mat image2;

	// open images
	image1= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg");
	image2= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\rain.jpg");
	if (!image1.data)
		return 0; 
	if (!image2.data)
		return 0; 

	cv::namedWindow("Image 1");
	cv::imshow("Image 1",image1);
	cv::namedWindow("Image 2");
	cv::imshow("Image 2",image2);

	cv::Mat result;

	// ��ͼ��Ȩ��
	// add two images
	cv::addWeighted(image1,0.7,image2,0.9,0.,result);
	cv::namedWindow("result");
	cv::imshow("result",result);

	// ʹ����������أ�ִ������ͬ���Ĳ���
	// using overloaded operator
	result= 0.7*image1+0.9*image2;
	cv::namedWindow("result with operators");
	cv::imshow("result with operators",result);

	image2= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\rain.jpg",0);

	// ��������ͼ�������
	// create vector of 3 images
	std::vector<cv::Mat> planes;
	// ��һ����ͨ��ͼ��ָ�Ϊ������ͨ��ͼ��
	// split 1 3-channel image into 3 1-channel images
	cv::split(image1,planes);
	// �ӵ���ɫͨ����
	// add to blue channel
	planes[0]+= image2;
	// ��������ͨ��ͼ��ϲ�Ϊһ����ͨ��ͼ��
	// merge the 3 1-channel images into 1 3-channel image
	cv::merge(planes,result);

	cv::namedWindow("Result on blue channel");
	cv::imshow("Result on blue channel",result);

	cv::waitKey();

	return 0;
}
