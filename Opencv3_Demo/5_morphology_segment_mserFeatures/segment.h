// 20200104
// ѧϰ��ע�� by wangze

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "E:\Projects\Opencv3_Demo\5_morphology_segment_mserFeatures\watershedSegmentation.h"


int segment_Test() {

	// Read input image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\group.jpg");
	if (!image.data)
		return 0; 

    // Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image",image);

	// Get the binary map
	cv::Mat binary;
	binary= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\binary.bmp",0);

    // Display the binary image
	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image",binary);

	// ����������ϸС����
	// Eliminate noise and smaller objects
	cv::Mat fg;
	cv::erode(binary,fg,cv::Mat(),cv::Point(-1,-1),4);

    // Display the foreground image
	cv::namedWindow("Foreground Image");
	cv::imshow("Foreground Image",fg);

	// ��ʶ���������ͼ������
	// Identify image pixels without objects
	cv::Mat bg;
	cv::dilate(binary,bg,cv::Mat(),cv::Point(-1,-1),4);
	cv::threshold(bg,bg,1,128,cv::THRESH_BINARY_INV);

    // Display the background image
	cv::namedWindow("Background Image");
	cv::imshow("Background Image",bg);

	// �ϲ�����ͼ���õ����ͼ��
	// Show markers image
	cv::Mat markers(binary.size(),CV_8U,cv::Scalar(0));
	markers= fg+bg;
	cv::namedWindow("Markers");
	cv::imshow("Markers",markers);

	// ������ˮ��ָ���Ķ���
	// Create watershed segmentation object
	WatershedSegmenter segmenter;

	// ���ñ��ͼ��Ȼ��ִ�зָ����
	// Set markers and process
	segmenter.setMarkers(markers);
    segmenter.process(image);

    // Display segmentation result
	cv::namedWindow("Segmentation");
	cv::imshow("Segmentation",segmenter.getSegmentation());

    // Display watersheds
	cv::namedWindow("Watersheds");
	cv::imshow("Watersheds",segmenter.getWatersheds());

    // Open another image
	image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\tower.jpg");

	// ��Ǳ�������
	// Identify background pixels
	cv::Mat imageMask(image.size(),CV_8U,cv::Scalar(0));
	cv::rectangle(imageMask,cv::Point(5,5),cv::Point(image.cols-5,image.rows-5),cv::Scalar(255),3);
	// ���ǰ�����أ���ͼ������ģ�
	// Identify foreground pixels (in the middle of the image)
	cv::rectangle(imageMask,cv::Point(image.cols/2-10,image.rows/2-10),
						    cv::Point(image.cols/2+10,image.rows/2+10),cv::Scalar(1),10);

	// Set markers and process
	segmenter.setMarkers(imageMask);
	segmenter.process(image);

    // Display the image with markers
	cv::rectangle(image,cv::Point(5,5),cv::Point(image.cols-5,image.rows-5),cv::Scalar(255,255,255),3);
	cv::rectangle(image,cv::Point(image.cols/2-10,image.rows/2-10),
						 cv::Point(image.cols/2+10,image.rows/2+10),cv::Scalar(1,1,1),10);
	cv::namedWindow("Image with marker");
	cv::imshow("Image with marker",image);

	// Display watersheds
	cv::namedWindow("Watershed");
	cv::imshow("Watershed",segmenter.getWatersheds());

	cv::waitKey();
	return 0;
}
