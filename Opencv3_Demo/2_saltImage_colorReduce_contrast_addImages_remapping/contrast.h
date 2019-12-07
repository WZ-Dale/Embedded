// 20191207
// ѧϰ��ע�� by wangze

#pragma once

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// �񻯺���
void sharpen(const cv::Mat &image, cv::Mat &result) {
	
	// �ж��Ƿ���Ҫ����ͼ�����ݣ�����Ҫ�ͷ���
	result.create(image.size(), image.type()); // allocate if necessary
	int nchannels= image.channels();

	// ���������У����˵�һ�к����һ��
	for (int j= 1; j<image.rows-1; j++) { // for all rows (except first and last)

		const uchar* previous= image.ptr<const uchar>(j-1); // previous row		// ��һ��
		const uchar* current= image.ptr<const uchar>(j);	// current row		// ��ǰ��
		const uchar* next= image.ptr<const uchar>(j+1);		// next row			// ��һ��

		uchar* output= result.ptr<uchar>(j);	// output row			// �����

		// ����ǰ�е����ͼ��
		for (int i=nchannels; i<(image.cols-1)*nchannels; i++) {

			// Ӧ��������
			// apply sharpening operator
			*output++= cv::saturate_cast<uchar>(5*current[i]-current[i-nchannels]-current[i+nchannels]-previous[i]-next[i]); 
			// saturate_cast<uchar>ģ�庯���������ǽ����������0-255��Χ��
		}
	}

	// ��δ�������������Ϊ0����������Ȧ��������Ϊ��ɫ
	// Set the unprocess pixels to 0
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols-1).setTo(cv::Scalar(0));
	// row��col�᷵��һ������ROI��һ������ROI
	// setTo()�������ԶԾ����е�����Ԫ�ظ�ֵ
	// �������������ͨ���Ĳ�ͼ����Ҫʹ��cv::Scalar(a,b,c)ָ��������ֵ���ֱ��ÿ��ͨ�����и�ֵ
}

// �񻯺������������汾
// same function but using iterator
// this one works only for gray-level image
void sharpenIterator(const cv::Mat &image, cv::Mat &result) {

	// ����
	// must be a gray-level image
	CV_Assert(image.type() == CV_8UC1);

	// initialize iterators at row 1
	cv::Mat_<uchar>::const_iterator it= image.begin<uchar>()+image.cols;
	cv::Mat_<uchar>::const_iterator itend= image.end<uchar>()-image.cols;
	cv::Mat_<uchar>::const_iterator itup= image.begin<uchar>();
	cv::Mat_<uchar>::const_iterator itdown= image.begin<uchar>()+2*image.cols;

	// setup output image and iterator
	result.create(image.size(), image.type()); // allocate if necessary
	cv::Mat_<uchar>::iterator itout= result.begin<uchar>()+result.cols;

	for ( ; it!= itend; ++it, ++itout, ++itup, ++itdown) {

			*itout= cv::saturate_cast<uchar>(*it *5 - *(it-1)- *(it+1)- *itup - *itdown); 
	}

	// Set the unprocessed pixels to 0
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols-1).setTo(cv::Scalar(0));
}

// ʹ�þ�����ģ��˲�����
// using kernel
void sharpen2D(const cv::Mat &image, cv::Mat &result) {

	// Construct kernel (all entries initialized to 0)
	cv::Mat kernel(3,3,CV_32F,cv::Scalar(0));
	// assigns kernel values
	kernel.at<float>(1,1)= 5.0;
	kernel.at<float>(0,1)= -1.0;
	kernel.at<float>(2,1)= -1.0;
	kernel.at<float>(1,0)= -1.0;
	kernel.at<float>(1,2)= -1.0;

	//filter the image
	cv::filter2D(image,result,image.depth(),kernel);
}

int contrast_Test() {
	// test sharpen function

	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg");
	if (!image.data)
		return 0; 

	cv::Mat result;

	double time= static_cast<double>(cv::getTickCount());
	sharpen(image, result);
	time= (static_cast<double>(cv::getTickCount())-time)/cv::getTickFrequency();
	std::cout << "time= " << time << std::endl;

	cv::namedWindow("Image");
	cv::imshow("Image",result);

	// test sharpenIterator

    // open the image in gray-level
	image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg",0);

	time = static_cast<double>(cv::getTickCount());
	sharpenIterator(image, result);
	time= (static_cast<double>(cv::getTickCount())-time)/cv::getTickFrequency();
	std::cout << "time 3= " << time << std::endl;

	cv::namedWindow("Sharpened Image");
	cv::imshow("Sharpened Image",result);

	// test sharpen2D

	image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg");

	time = static_cast<double>(cv::getTickCount());
	sharpen2D(image, result);
	time= (static_cast<double>(cv::getTickCount())-time)/cv::getTickFrequency();
	std::cout << "time 2D= " << time << std::endl;

	cv::namedWindow("Image 2D");
	cv::imshow("Image 2D",result);

	cv::waitKey();

	return 0;
}


