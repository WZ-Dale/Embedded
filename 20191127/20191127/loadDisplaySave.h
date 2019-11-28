// 20191128
// ѧϰ��ע�� by wangze
#pragma once

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


void onMouse(int event, int x, int y, int flags, void* param) {

	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);

	switch (event) {	// dispatch the event

	case cv::EVENT_LBUTTONDOWN: // mouse button down event

		// display pixel value at (x,y)
		std::cout << "at (" << x << "," << y << ") value is: "
			<< static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl;
		break;
	}
}

int loadDisplaySave_Test() {
	// ������ͼ
	cv::Mat image; // create an empty image
	// ��ʾ�ֱ���
	std::cout << "This image is " << image.rows << " x " << image.cols << std::endl;

	// ����һ��ͼ��ֻ��һ��ͨ�����Ҷ�ͼ
	// read the input image as a gray-scale image
	image = cv::imread("E:\\��OpenCV3Cookbook-master��\\src\\images\\puppy.bmp", cv::IMREAD_GRAYSCALE);
	//image = cv::imread("E:\\��OpenCV3Cookbook-master��\\src\\Chapter01\\output.bmp", cv::IMREAD_COLOR);

	// �����ͼ�����������ʾδ����ͼ��������0
	if (image.empty()) {  // error handling
		// no image has been created...
		// possibly display an error message
		// and quit the application 
		std::cout << "Error reading image..." << std::endl;
		return 0;
	}

	// ������ͼ���������ʾͼƬ�ֱ��ʺ�ͨ����
	std::cout << "This image is " << image.rows << " x " << image.cols << std::endl;
	std::cout << "This image has " << image.channels() << " channel(s)" << std::endl;

	// ���崰�ڣ�choice��
	// create image window named "My Image"
	cv::namedWindow("Original Image"); // define the window (optional)
	// ��ʾͼ��
	cv::imshow("Original Image", image); // show the image

	// 
	// set the mouse callback for this image
	cv::setMouseCallback("Original Image", onMouse, reinterpret_cast<void*>(&image));

	// ������һ����ͼ
	cv::Mat result; // we create another empty image
	// ͼ����ת������������������0��ʾˮƽ��0��ʾ��ֱ��С��0��ʾˮƽ�ʹ�ֱ
	cv::flip(image, result, 1); // positive for horizontal
						  // 0 for vertical,                     
						  // negative for both
	cv::namedWindow("Output Image"); // the output window
	cv::imshow("Output Image", result);

	// 0��ʾ��Զ�ȴ�������������ʾ������
	cv::waitKey(1000); // 0 to indefinitely wait for a key pressed
				// specifying a positive value will wait for
				// the given amount of msec
	// д����̣�������ͼƬ
	cv::imwrite("E:\\��OpenCV3Cookbook-master��\\src\\Chapter01\\output.bmp", result); // save result
	cv::Mat result3;
	result3 = cv::imread("E:\\��OpenCV3Cookbook-master��\\src\\Chapter01\\output.bmp", cv::IMREAD_COLOR);
	cv::imshow("Output Image3", result3);
	std::cout << "This image has " << result3.channels() << " channel(s)" << std::endl;
	// create another image window named
	cv::namedWindow("Drawing on an Image"); // define the window

	//
	cv::circle(image,              // destination image 
		cv::Point(155, 110), // center coordinate
		65,                 // radius  
		0,                  // color (here black)
		3);                 // thickness

	cv::putText(image,                   // destination image
		"This is a dog.",        // text
		cv::Point(40, 200),       // text position
		cv::FONT_HERSHEY_PLAIN,  // font type
		2.0,                     // font scale
		255,                     // text color (here white)
		2);                      // text thickness

	cv::imshow("Drawing on an Image", image); // show the image

	cv::waitKey(0); // 0 to indefinitely wait for a key pressed

	return 0;
}