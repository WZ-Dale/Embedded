// 20200106
// ѧϰ��ע�� by wangze

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

int mserFeatures_Test() {

	// Read input image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\building.jpg",0);
	if (!image.data)
		return 0; 

    // Display the image
	cv::namedWindow("Image");
	cv::imshow("Image",image);
	
	// ������MSER�����
	// basic MSER detector
	cv::Ptr<cv::MSER> ptrMSER= cv::MSER::create(5,     // delta value for local minima detection���ֲ������ʹ�õ�����ֵ��
		                                        200,   // min acceptable area���������С�����
				                                2000); // max acceptable area���������������
	// �㼯������
    // vector of point sets
	std::vector<std::vector<cv::Point> > points;
	// ���ε�����
	// vector of rectangles
	std::vector<cv::Rect> rects;
	// ���MSER����
	// detect MSER features
	ptrMSER->detectRegions(image, points, rects);

	std::cout << points.size() << " MSERs detected" << std::endl;

	// ������ɫͼ��
	// create white image
	cv::Mat output(image.size(),CV_8UC3);
	output= cv::Scalar(255,255,255);
	
	// OpenCV�����������
	// OpenCV random number generator
	cv::RNG rng;

	// ���ÿ����⵽�����������ڲ�ɫ������ʾMSER
	// ������������ʾ�ϴ��MSER
	// Display the MSERs in color areas
	// for each detected feature
	// reverse order to display the larger MSER first
    for (std::vector<std::vector<cv::Point> >::reverse_iterator it= points.rbegin();
			   it!= points.rend(); ++it) {
		// ���������ɫ
		// generate a random color
		cv::Vec3b c(rng.uniform(0,254),
			        rng.uniform(0,254),
					rng.uniform(0,254));

		std::cout << "MSER size= " << it->size() << std::endl;
		// ���MSER�����е�ÿ����
		// for each point in MSER set
		for (std::vector<cv::Point>::iterator itPts= it->begin();
			                                  itPts!= it->end(); ++itPts) {
			// ������дMSER������
			//do not overwrite MSER pixels
			if (output.at<cv::Vec3b>(*itPts)[0]==255) {

				output.at<cv::Vec3b>(*itPts)= c;
			}
		}
	}
	
	cv::namedWindow("MSER point sets");
	cv::imshow("MSER point sets",output);
	cv::imwrite("E:\\Projects\\Opencv3_Demo\\5_morphology_segment_mserFeatures\\mser.bmp", output);

	// ��ȡ����ʾ���ε�MSER
	// Extract and display the rectangular MSERs
	std::vector<cv::Rect>::iterator itr = rects.begin();
	std::vector<std::vector<cv::Point> >::iterator itp = points.begin();
	for (; itr != rects.end(); ++itr, ++itp) {
		// ������߱���
		// ratio test
		if (static_cast<double>(itp->size())/itr->area() > 0.6)
			cv::rectangle(image, *itr, cv::Scalar(255), 2);
	}

	// Display the resulting image
	cv::namedWindow("Rectangular MSERs");
	cv::imshow("Rectangular MSERs", image);
	
	// Reload the input image
	image = cv::imread("E:\\Projects\\Opencv3_Demo\\images\\building.jpg", 0);
	if (!image.data)
		return 0;
	// ��ȡ����ʾ��Բ�ε�MSER
	// Extract and display the elliptic MSERs
	for (std::vector<std::vector<cv::Point> >::iterator it = points.begin();
	                                                    it != points.end(); ++it) {
		// ����MSER�����е�ÿ����
		// for each point in MSER set
		for (std::vector<cv::Point>::iterator itPts = it->begin();
		                                      itPts != it->end(); ++itPts) {
			// ��ȡ��յľ���
			// Extract bouding rectangles
			cv::RotatedRect rr = cv::minAreaRect(*it);
			// �����Բ�ĳ����
            // check ellipse elongation
			if (rr.size.height / rr.size.height > 0.6 || rr.size.height / rr.size.height < 1.6)
				cv::ellipse(image, rr, cv::Scalar(255), 2);
		} 
		// ����û����ѭ����ֻ�Ƕ��ѭ������������
	}

	// Display the image
	cv::namedWindow("MSER ellipses");
	cv::imshow("MSER ellipses", image);

	/*
	// detection using mserFeatures class

	// create MSER feature detector instance
	MSERFeatures mserF(200,  // min area 
		               1500, // max area
					   0.5); // ratio area threshold
	                         // default delta is used

	// the vector of bounding rotated rectangles
	std::vector<cv::RotatedRect> rects;

	// detect and get the image
	cv::Mat result= mserF.getImageOfEllipses(image,rects);

	// display detected MSER
	cv::namedWindow("MSER regions");
	cv::imshow("MSER regions",result);
	*/
	cv::waitKey();
}
