// 20200108
// ѧϰ��ע�� by wangze

#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int blobs_Test() {

	// Read input binary image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\binaryGroup.bmp",0);
	if (!image.data)
		return 0; 

	cv::namedWindow("Binary Image");
	cv::imshow("Binary Image",image);

	// findContours������ȡͼ�����������������
	// Get the contours of the connected components�����ڴ洢������������
    std::vector<std::vector<cv::Point> > contours;
	cv::findContours(image, 
		contours, // a vector of contours ���洢������������
		cv::RETR_EXTERNAL,      // retrieve the external contours�������ⲿ������
		cv::CHAIN_APPROX_NONE); // retrieve all pixels of each contours��ÿ��������ȫ�����أ�

	// Print contours' length
	std::cout << "Contours: " << contours.size() << std::endl;
    std::vector<std::vector<cv::Point> >::const_iterator itContours= contours.begin();
	for ( ; itContours!=contours.end(); ++itContours) {

		std::cout << "Size: " << itContours->size() << std::endl;
	}

	// drawContours�����ڰ�ɫͼ���ϻ�����Щ���������
	// draw black contours on white image���ڰ�ɫͼ���ϻ���ɫ������
	cv::Mat result(image.size(),CV_8U,cv::Scalar(255));
	cv::drawContours(result,contours,
		-1, // draw all contours����ȫ��������
		cv::Scalar(0), // in black���ú�ɫ����
		2); // with a thickness of 2�����Ϊ2��

	cv::namedWindow("Contours");
	cv::imshow("Contours",result);

	// Eliminate too short or too long contours��ɾ��̫�̻�̫����������
	int cmin= 50;  // minimum contour length����С�������ȣ�
	int cmax= 500; // maximum contour length����������ȣ�
    std::vector<std::vector<cv::Point> >::iterator itc= contours.begin();
	// �����������
	while (itc!=contours.end()) {
		// ��֤������С
		if (itc->size() < cmin || itc->size() > cmax)
			itc= contours.erase(itc);
		else 
			++itc;
	}

	// draw contours on the original image
	cv::Mat original= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\group.jpg");

	cv::drawContours(original,contours,
		-1, // draw all contours
		cv::Scalar(255,255,255), // in white
		2); // with a thickness of 2

	cv::namedWindow("Contours on Animals");
	cv::imshow("Contours on Animals",original);

	// Let's now draw black contours on white image
	result.setTo(cv::Scalar(255));
	cv::drawContours(result,contours,
		-1, // draw all contours
		 0, // in black
		 1); // with a thickness of 1

	image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\binaryGroup.bmp",0);

	// testing the bounding box �����Ա߽��
	cv::Rect r0= cv::boundingRect(contours[0]);
	// draw the rectangle�������Σ�
	cv::rectangle(result,r0, 0, 2);

	// testing the enclosing circle �����Ը���Բ��
	float radius;
	cv::Point2f center;
	cv::minEnclosingCircle(contours[1],center,radius);
	// draw the cricle����Բ�Σ�
    cv::circle(result,center,static_cast<int>(radius), 0, 2);

	// testing the approximate polygon�����Զ���αƽ���
	std::vector<cv::Point> poly;
	cv::approxPolyDP(contours[2],poly,5,true);
	// draw the polygon��������Σ�
	cv::polylines(result, poly, true, 0, 2);

	std::cout << "Polygon size: " << poly.size() << std::endl;

	// testing the convex hull������͹����
	std::vector<cv::Point> hull;
	cv::convexHull(contours[3],hull);
	// draw the polygon��������Σ�
	cv::polylines(result, hull, true, 0, 2);
	
	std::vector<cv::Vec4i> defects;
	// cv::convexityDefects(contours[3], hull, defects);

	// testing the moments

	// iterate over all contours�����������أ�������������������
	itc= contours.begin();
	while (itc!=contours.end()) {

		// compute all moments���������������أ�
		cv::Moments mom= cv::moments(*itc++);

		// draw mass center�������ģ�
		cv::circle(result,
			// position of mass center converted to integer��������λ��ת����������
			cv::Point(mom.m10/mom.m00,mom.m01/mom.m00),
			2,cv::Scalar(0),2); // draw black dot�����ڵ㣩
	}

	cv::namedWindow("Some Shape descriptors");
	cv::imshow("Some Shape descriptors",result);

	// New call to findContours but with RETR_LIST flag
	image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\binaryGroup.bmp",0);

	// Get the contours of the connected components
	cv::findContours(image, 
		contours, // a vector of contours �����������������
		cv::RETR_LIST, // retrieve the external and internal contours������ȫ��������
		cv::CHAIN_APPROX_NONE); // retrieve all pixels of each contours��ȫ�����أ�

	// draw black contours on white image
	result.setTo(255);
	cv::drawContours(result,contours,
	   -1,  // draw all contours
		0,  // in black
		2); // with a thickness of 2
	cv::namedWindow("All Contours");
	cv::imshow("All Contours",result);

	// get a MSER image
	cv::Mat components;
	components= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\mser.bmp",0);

	// create a binary version��������ֵͼ��
	components= components==255;
	// open the image (white background)����ͼ�񣬰���������
	cv::morphologyEx(components,components,cv::MORPH_OPEN,cv::Mat(),cv::Point(-1,-1),3);

	cv::namedWindow("MSER image");
	cv::imshow("MSER image",components);

	contours.clear();
	//invert image (background must be black)����תͼ�񣨱��������Ǻ�ɫ�ģ���
	cv::Mat componentsInv= 255-components;
	// Get the contours of the connected components���õ����������������
	cv::findContours(componentsInv, 
		contours, // a vector of contours ��������������
		cv::RETR_EXTERNAL, // retrieve the external contours�������ⲿ������
		cv::CHAIN_APPROX_NONE); // retrieve all pixels of each contours

	// white image����ɫͼ��
	cv::Mat quadri(components.size(),CV_8U,255);

	// for all contours�����ȫ��������
    std::vector<std::vector<cv::Point> >::iterator it= contours.begin();
	while (it!= contours.end()) {
		poly.clear();
		// approximate contour by polygon���ö���αƽ�������
		cv::approxPolyDP(*it,poly,5,true);
	
		// do we have a quadrilateral?���Ƿ�Ϊ�ı��Σ�
		if (poly.size()==4) {
	        // draw it����������
			cv::polylines(quadri, poly, true, 0, 2);
		}
	
		++it;
	}

	cv::namedWindow("MSER quadrilateral");
	cv::imshow("MSER quadrilateral",quadri);

	cv::waitKey();
	return 0;
}
