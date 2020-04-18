#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>


// ����¼�
void onMouse(int event, int x, int y, int flags, void* param);
// չʾͼƬ���ɵ��
void ShowImage(const cv::String &str, cv::Mat &image);
// ��ֵ��
void ChangeBinarizationValue(cv::Mat inputImage, cv::Mat outputImage);
void ChangeBinarization(int, void*);
void BarbinarizationFun(cv::Mat inputImage, cv::Mat outputImage);
// ��Ե���
void ChangeThresholdValue(cv::Mat inputImage, cv::Mat outputImage);
void ChangeThreshold1(int, void*);
void ChangeThreshold2(int, void*);
void ThresholdFun(cv::Mat inputImage, cv::Mat outputImage);

// ������

// �����ͨ����
void LargestConnectedComponent(cv::Mat srcImage, cv::Mat &dstImage);


void Test1();



