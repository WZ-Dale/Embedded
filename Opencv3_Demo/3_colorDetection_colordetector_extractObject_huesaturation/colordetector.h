// 20191210
// ѧϰ��ע�� by wangze

#pragma once

#if !defined COLORDETECT
#define COLORDETECT

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/imgproc/types_c.h>

class ColorDetector {

  private:
	  // �������С����
	  // minimum acceptable distance
	  int maxDist; 
	  // Ŀ����ɫ
	  // target color
	  cv::Vec3b target; 
	  // ������ɫת��ͼ���ͼ��
	  // image containing color converted image
	  cv::Mat converted;
	  bool useLab;
	  // �������ɵĶ�����ӳ���ͼ��
	  // image containing resulting binary map
	  cv::Mat result;

  public:
	  // �չ��캯��
	  // empty constructor
	  // �ڴ˳�ʼ��Ĭ�ϲ���
	  // default parameter initialization here
	  ColorDetector() : maxDist(100), target(0,0,0), useLab(false) {}

	  // extra constructor for Lab color space example
	  ColorDetector(bool useLab) : maxDist(100), target(0,0,0), useLab(useLab) {}
	  
	  // ��һ�ֹ��캯����ʹ���û������Ŀ����ɫ����ɫ������Ϊ����
	  // full constructor
	  ColorDetector(uchar blue, uchar green, uchar red, int mxDist=100, bool useLab=false): maxDist(mxDist), useLab(useLab) { 

		  // target color
		  setTargetColor(blue, green, red);
	  }

	  // ������Ŀ����ɫ�Ĳ��
	  // Computes the distance from target color.
	  int getDistanceToTargetColor(const cv::Vec3b& color) const {
		  return getColorDistance(color, target);
	  }
	  // ����������ɫ֮��ĳ�������
	  // Computes the city-block distance between two colors.
	  int getColorDistance(const cv::Vec3b& color1, const cv::Vec3b& color2) const {

		  return abs(color1[0]-color2[0])+
					abs(color1[1]-color2[1])+
					abs(color1[2]-color2[2]);

	 	  // Or:
		  // return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0]-color2[0],color[1]-color2[1],color[2]-color2[2])));
		  
		  // Or:
		  // cv::Vec3b dist;
		  // cv::absdiff(color,color2,dist);
		  // return cv::sum(dist)[0];
	  }

	  // Processes the image. Returns a 1-channel binary image.
	  cv::Mat process(const cv::Mat &image) {
			  // ��Ҫʱ���·����ֵӳ��
			  // ������ͼ��ĳߴ���ͬ�������ǵ�ͨ��
			  // re-allocate binary map if necessary
			  // same size as input image, but 1-channel
			  result.create(image.size(), CV_8U);

			  // ת����Lab��ɫ�ռ�
			  // Converting to Lab color space 
			  if (useLab)
				  cv::cvtColor(image, converted, CV_BGR2Lab);

			  // ȡ�õ�����
			  // get the iterators
			  cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
			  cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
			  cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

			  // ��ȡת����ͼ��ĵ�����
			  // get the iterators of the converted image 
			  if (useLab) {
				  it = converted.begin<cv::Vec3b>();
				  itend = converted.end<cv::Vec3b>();
			  }

			  // �Ա�ÿ������
			  // for each pixel
			  for (; it != itend; ++it, ++itout) {
				  // process each pixel --------------------- ����ÿһ������
					  // �Ƚ���Ŀ����ɫ�Ĳ��
					  // compute distance from target color
				  if (getDistanceToTargetColor(*it) < maxDist) {
					  *itout = 255;
				  }
				  else {
					  *itout = 0;
				  }
				  // end of pixel processing ---------------- ���ش������
			  }

			  return result;
	  }

	  // ����operator()Ŀ��->�º���
	  cv::Mat operator()(const cv::Mat &image) {
	  
		  cv::Mat input;
		  
		  // ת����Lab��ɫ�ռ�
		  if (useLab) { // Lab conversion
			  cv::cvtColor(image, input, CV_BGR2Lab);
		  }
		  else {
			  input = image;
		  }

		  cv::Mat output;
		  // compute absolute difference with target color
		  cv::absdiff(input,cv::Scalar(target),output);
	      // split the channels into 3 images
	      std::vector<cv::Mat> images;
	      cv::split(output,images);
		  // add the 3 channels (saturation might occurs here)
	      output= images[0]+images[1]+images[2];
		  // apply threshold
          cv::threshold(output,  // input image
                      output,  // output image
                      maxDist, // threshold (must be < 256)
                      255,     // max value
                 cv::THRESH_BINARY_INV); // thresholding type
	
	      return output;
	  }


	  // ������ɫ������ֵ
	  // ��ֵ���������������������Ϊ0
	  // Getters and setters
	  // Sets the color distance threshold.
	  // Threshold must be positive, otherwise distance threshold
	  // is set to 0.
	  void setColorDistanceThreshold(int distance) {

		  if (distance<0)
			  distance=0;
		  maxDist= distance;
	  }
	  // ȡ����ɫ������ֵ
	  // Gets the color distance threshold
	  int getColorDistanceThreshold() const {

		  return maxDist;
	  }

	  // ������Ҫ������ɫ
	  // Sets the color to be detected
	  // given in BGR color space
	  void setTargetColor(uchar blue, uchar green, uchar red) {

		  // ����ΪBGR
		  // BGR order
		  target = cv::Vec3b(blue, green, red);

		  if (useLab) {
			  // ��ʱ�ĵ�����ͼ��
			  // Temporary 1-pixel image
			  cv::Mat tmp(1, 1, CV_8UC3);
			  tmp.at<cv::Vec3b>(0, 0) = cv::Vec3b(blue, green, red);

			  // ��Ŀ����ɫת����Lab��ɫ�ռ�
			  // Converting the target to Lab color space 
			  cv::cvtColor(tmp, tmp, CV_BGR2Lab);

			  target = tmp.at<cv::Vec3b>(0, 0);
		  }
	  }
	  // ������Ҫ������ɫ
	  // Sets the color to be detected
	  void setTargetColor(cv::Vec3b color) {

		  target= color;
	  }
	  // ȡ����Ҫ������ɫ
	  // Gets the color to be detected
	  cv::Vec3b getTargetColor() const {

		  return target;
	  }
};

#endif
