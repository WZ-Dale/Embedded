// 20191210
// ѧϰ��ע�� by wangze

#pragma once

#include "E:\Projects\Opencv3_Demo\3_colorDetection_colordetector_extractObject_huesaturation\colordetector.h"
#include <vector>
	
cv::Mat ColorDetector::process(const cv::Mat &image) {
	  // ��Ҫʱ���·����ֵӳ��
	  // ������ͼ��ĳߴ���ͬ�������ǵ�ͨ��
	  // re-allocate binary map if necessary
	  // same size as input image, but 1-channel
	  result.create(image.size(),CV_8U);

	  // ת����Lab��ɫ�ռ�
	  // Converting to Lab color space 
	  if (useLab)
		  cv::cvtColor(image, converted, CV_BGR2Lab);

	  // ȡ�õ�����
	  // get the iterators
	  cv::Mat_<cv::Vec3b>::const_iterator it= image.begin<cv::Vec3b>();
	  cv::Mat_<cv::Vec3b>::const_iterator itend= image.end<cv::Vec3b>();
	  cv::Mat_<uchar>::iterator itout= result.begin<uchar>();

	  // ��ȡת����ͼ��ĵ�����
	  // get the iterators of the converted image 
	  if (useLab) {
		  it = converted.begin<cv::Vec3b>();
		  itend = converted.end<cv::Vec3b>();
	  }

	  // �Ա�ÿ������
	  // for each pixel
	  for ( ; it!= itend; ++it, ++itout) {
	  // process each pixel --------------------- ����ÿһ������
		  // �Ƚ���Ŀ����ɫ�Ĳ��
		  // compute distance from target color
		  if (getDistanceToTargetColor(*it)<maxDist) {
			  *itout= 255;
		  } else {
			  *itout= 0;
		  }
      // end of pixel processing ---------------- ���ش������
	  }

	  return result;
}

