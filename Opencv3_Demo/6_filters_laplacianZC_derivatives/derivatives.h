// 20200107
// 学习并注释 by wangze

#include <iostream>
#include <iomanip>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "E:\Projects\Opencv3_Demo\6_filters_laplacianZC_derivatives\laplacianZC.h"

int derivatives_Test() {

	// Read input image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg",0);
	if (!image.data)
		return 0; 

    // Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image",image);

	// Compute Sobel X derivative
	cv::Mat sobelX;
	cv::Sobel(image,  // input
		sobelX,    // output
		CV_8U,     // image type
		1, 0,      // kernel specification(内核规格)
		3,         // size of the square kernel （正方形内核的尺寸）
		0.4, 128); // scale and offset（比例和偏移量）

    // Display the image
	cv::namedWindow("Sobel X Image");
	cv::imshow("Sobel X Image",sobelX);

	// Compute Sobel Y derivative
	cv::Mat sobelY;
	cv::Sobel(image,  // input
		sobelY,    // output
		CV_8U,     // image type
		0, 1,      // kernel specification
		3,         // size of the square kernel 
		0.4, 128); // scale and offset

    // Display the image
	cv::namedWindow("Sobel Y Image");
	cv::imshow("Sobel Y Image",sobelY);

	// 计算Sobel滤波器的范数
	// Compute norm of Sobel
	cv::Sobel(image,sobelX,CV_16S,1,0);
	cv::Sobel(image,sobelY,CV_16S,0,1);
	cv::Mat sobel;
	// 计算L1范数
	//compute the L1 norm
	sobel= abs(sobelX)+abs(sobelY);

	// 找到Sobel最小值和最大值
	double sobmin, sobmax;
	cv::minMaxLoc(sobel,&sobmin,&sobmax);
	std::cout << "sobel value range: " << sobmin << "  " << sobmax << std::endl;

	// Compute Sobel X derivative (7x7)
	cv::Sobel(image,sobelX,CV_8U,1,0,7,0.001,128);

    // Display the image
	cv::namedWindow("Sobel X Image (7x7)");
	cv::imshow("Sobel X Image (7x7)",sobelX);

	// Print window pixel values
	for (int i=0; i<12; i++) {
		for (int j=0; j<12; j++)
			std::cout << std::setw(5) << static_cast<int>(sobel.at<short>(i+79,j+215)) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	// 转换成8位图像
	// Conversion to 8-bit image
	// sobelImage = -alpha*sobel + 255
	cv::Mat sobelImage;
	sobel.convertTo(sobelImage,CV_8U,-255./sobmax,255);

    // Display the image
	cv::namedWindow("Sobel Image");
	cv::imshow("Sobel Image",sobelImage);

	// 阈值化
	// Apply threshold to Sobel norm (low threshold value)
	cv::Mat sobelThresholded;
	cv::threshold(sobelImage, sobelThresholded, 225, 255, cv::THRESH_BINARY);

    // Display the image
	cv::namedWindow("Binary Sobel Image (low)");
	cv::imshow("Binary Sobel Image (low)",sobelThresholded);

	// Apply threshold to Sobel norm (high threshold value)
	cv::threshold(sobelImage, sobelThresholded, 190, 255, cv::THRESH_BINARY);

    // Display the image
	cv::namedWindow("Binary Sobel Image (high)");
	cv::imshow("Binary Sobel Image (high)",sobelThresholded);


	// Compute Laplacian 3x3
	cv::Mat laplace;
	cv::Laplacian(image,laplace,CV_8U,1,1,128);

    // Display the image
	cv::namedWindow("Laplacian Image");
	cv::imshow("Laplacian Image",laplace);

	int cx(238), cy(90);
	int dx(12), dy(12);
	
    // Extract small window
	cv::Mat window(image,cv::Rect(cx,cy,dx,dy));
	cv::namedWindow("Image window");
	cv::imshow("Image window",window);
	cv::imwrite("E:\\Projects\\Opencv3_Demo\\6_filters_laplacianZC_derivatives\\window.bmp",window);

	// Compute Laplacian using LaplacianZC class（用LaplacianZC类计算拉普拉斯算子）
	LaplacianZC laplacian;
	laplacian.setAperture(7);// 7x7的拉普拉斯算子
	cv::Mat flap= laplacian.computeLaplacian(image);

	// display min max values of the lapalcian
	double lapmin, lapmax;
	cv::minMaxLoc(flap,&lapmin,&lapmax);

	// display laplacian image
	laplace= laplacian.getLaplacianImage();
	cv::namedWindow("Laplacian Image (7x7)");
	cv::imshow("Laplacian Image (7x7)",laplace);

	// Print image values
	std::cout << std::endl;
	std::cout << "Image values:\n\n";
	for (int i = 0; i<dx; i++) {
		for (int j = 0; j<dy; j++)
			std::cout << std::setw(5) << static_cast<int>(image.at<uchar>(i + cy, j + cx)) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Print Laplacian values
	std::cout << "Laplacian value range=[" << lapmin << "," << lapmax << "]\n";
	std::cout << std::endl;
	for (int i=0; i<dx; i++) {
		for (int j=0; j<dy; j++)
			std::cout << std::setw(5) << static_cast<int>(flap.at<float>(i + cy, j + cx) / 100) << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// Compute and display the zero-crossing points
	cv::Mat zeros;
	zeros= laplacian.getZeroCrossings(flap);
	cv::namedWindow("Zero-crossings");
	cv::imshow("Zero-crossings",255-zeros);

	// Print window pixel values
	std::cout << "Zero values:\n\n";
	for (int i=0; i<dx; i++) {
		for (int j=0; j<dy; j++)
			std::cout << std::setw(2) << static_cast<int>(zeros.at<uchar>(i + cy, j + cx))/255 << " ";
		std::cout << std::endl;
	}
	
	// down-sample and up-sample the image
	cv::Mat reduced, rescaled;
	cv::pyrDown(image, reduced);
	cv::pyrUp(reduced, rescaled);

    // Display the rescaled image
	cv::namedWindow("Rescaled Image");
	cv::imshow("Rescaled Image",rescaled);

	// compute a difference of Gaussians pyramid
	cv::Mat dog;
	cv::subtract(rescaled, image, dog, cv::Mat(), CV_16S);
	cv::Mat dogImage;
	dog.convertTo(dogImage,CV_8U,1.0,128);

    // Display the DoG image
	cv::namedWindow("DoG Image (from pyrdown/pyrup)");
	cv::imshow("DoG Image (from pyrdown/pyrup)",dogImage);

	// Apply two Gaussian filters
	cv::Mat gauss05;
	cv::Mat gauss15;
	cv::GaussianBlur(image,gauss05,cv::Size(),0.5);
	cv::GaussianBlur(image,gauss15,cv::Size(),1.5);

	// compute a difference of Gaussians （计算高斯差分）
	cv::subtract(gauss15, gauss05, dog, cv::Mat(), CV_16S);
	dog.convertTo(dogImage,CV_8U,2.0,128);

    // Display the DoG image
	cv::namedWindow("DoG Image");
	cv::imshow("DoG Image",dogImage);

	// Apply two Gaussian filters
	cv::Mat gauss20;
	cv::GaussianBlur(image,gauss20,cv::Size(),2.0);
	cv::Mat gauss22;
	cv::GaussianBlur(image,gauss22,cv::Size(),2.2);

	// compute a difference of Gaussians 
	cv::subtract(gauss22, gauss20, dog, cv::Mat(), CV_32F);
	dog.convertTo(dogImage,CV_8U,10.0,128);

    // Display the DoG image
	cv::namedWindow("DoG Image (2)");
	cv::imshow("DoG Image (2)",dogImage);

    // Display the zero-crossings of DoG （计算DoG的过零点）
	zeros= laplacian.getZeroCrossings(dog);
	cv::namedWindow("Zero-crossings of DoG");
	cv::imshow("Zero-crossings of DoG",255-zeros);

    // Display the image with window
	cv::rectangle(image,cv::Rect(cx,cy,dx,dy),cv::Scalar(255,255,255));
	cv::namedWindow("Original Image with window");
	cv::imshow("Original Image with window",image);

	cv::waitKey();
	return 0;
}
