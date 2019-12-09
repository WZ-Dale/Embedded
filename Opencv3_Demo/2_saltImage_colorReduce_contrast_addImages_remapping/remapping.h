// 20191209
// ѧϰ��ע�� by wangze

#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <math.h>

// ��ӳ��ͼ�񣬴�������Ч��
// remapping an image by creating wave effects
void wave(const cv::Mat &image, cv::Mat &result) {
	// ӳ�����
	// the map functions
	cv::Mat srcX(image.rows,image.cols,CV_32F); // x-map
	cv::Mat srcY(image.rows,image.cols,CV_32F); // y-map
	// ����ӳ�����
	// creating the mapping
	for (int i=0; i<image.rows; i++) {
		for (int j=0; j<image.cols; j++) {
			// ��i��j�����ص���λ��
			srcX.at<float>(i,j)= j;					// ������ͬһ��
			srcY.at<float>(i,j)= i+3*sin(j/6.0);	// ԭ���ڵ�i�е����أ����ڸ���һ�����������ƶ�
			
			// ˮƽ��ת
			// horizontal flipping
			// srcX.at<float>(i,j)= image.cols-j-1;
			// srcY.at<float>(i,j)= i;
		}
	}
	// Ӧ��ӳ�����
	// applying the mapping
	cv::remap(image,  // source image
		      result, // destination image
			  srcX,   // x map
			  srcY,   // y map
			  cv::INTER_LINEAR); // interpolation method	// ���������ֵ��
}

int remapping_Test() {
	// open image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg",0);

	cv::namedWindow("Image");
	cv::imshow("Image",image);

	// remap image
	cv::Mat result, result1, result2, result3, result4;
	wave(image,result);
	wave(result, result1);
	wave(result1, result2);
	wave(result2, result3);
	wave(result3, result4);

	cv::namedWindow("Remapped image");
	cv::imshow("Remapped image",result4);

	cv::waitKey();
	return 0;
}


