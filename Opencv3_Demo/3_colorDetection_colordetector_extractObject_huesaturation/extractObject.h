// 20191216
// ѧϰ��ע�� by wangze

#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


int extractObject_Test() {

	// Read input image
	cv::Mat image= cv::imread("E:\\Projects\\Opencv3_Demo\\images\\boldt.jpg");
	if (!image.data)
		return 0; 

    // Display the image
	cv::namedWindow("Original Image");
	cv::imshow("Original Image",image);

	// ����һ�����߿�ľ���
	// �����ⲿ�����ػᱻ���Ϊ����
	// define bounding rectangle 
	cv::Rect rectangle(50,25,210,180);

	// ģ�ͣ��ڲ�ʹ�ã�
	// the models (internally used)
	cv::Mat bgModel,fgModel; 
	// �ָ��������ֿ��ܵ�ֵ��
	// segmentation result
	cv::Mat result; // segmentation (4 possible values)

	// GrabCut�ָ��㷨���������󣬵�����ܾ�ȷ
	// GrabCut segmentation
	cv::grabCut(image,    // input image					// ����ͼ��
		result,   // segmentation result					// �ָ���
		rectangle,// rectangle containing foreground		// ����ǰ���ľ���
		bgModel, fgModel, // models							// ģ��
		5,        // number of iterations					// ��������
		cv::GC_INIT_WITH_RECT); // use rectangle			// ʹ�þ��Σ���ʾ��ʹ�ô��߿�ľ���ģ��

	// ȡ�ñ��Ϊ����������ǰ����������
	// Get the pixels marked as likely foreground
	cv::compare(result,cv::GC_PR_FGD,result,cv::CMP_EQ);
	// or: ʹ�ð�λ����������һλ�������ǰ��ɫ���Ϊ1
    //	result= result&1;
	
	// �������ͼ��
	// create a white image
	cv::Mat foreground(image.size(), CV_8UC3,
	          	       cv::Scalar(255, 255, 255));
	// �����Ʊ�������
	image.copyTo(foreground,result); // bg pixels not copied

	// draw rectangle on original image
	cv::rectangle(image, rectangle, cv::Scalar(255,255,255),1);
	cv::namedWindow("Image with rectangle");
	cv::imshow("Image with rectangle",image);

	// display result
	cv::namedWindow("Foreground object");
	cv::imshow("Foreground object",foreground);

	cv::waitKey();
	return 0;
}
