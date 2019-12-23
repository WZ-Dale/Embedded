// 20191221
// ѧϰ��ע�� by wangze

#pragma once

#if !defined ICOMPARATOR
#define ICOMPARATOR

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "E:\Projects\Opencv3_Demo\4_histogram_finder__imageComparator_integral\colorhistogram.h"

// �Ƚ�ֱ��ͼ��������ͼ��
class ImageComparator {

  private:

	cv::Mat refH;       // reference histogram// ��׼ͼ��
	cv::Mat inputH;     // histogram of input image// ����ͼ���ֱ��ͼ

	ColorHistogram hist; // ����ֱ��ͼ
	int nBins; // number of bins used in each color channel// ÿ����ɫͨ��ʹ�õ���������

  public:

	ImageComparator() :nBins(8) {

	}

	// Set number of bins used when comparing the histograms
	void setNumberOfBins( int bins) {

		nBins= bins;
	}

	int getNumberOfBins() {

		return nBins;
	}
	// ���ò������׼ͼ���ֱ��ͼ
	// set and compute histogram of reference image
	void setReferenceImage(const cv::Mat& image) {

		hist.setSize(nBins);
		refH= hist.getHistogram(image);
	}
	// ��BGRֱ��ͼ�Ƚ�ͼ��
	// compare the image using their BGR histograms
	double compare(const cv::Mat& image) {

		inputH= hist.getHistogram(image);
		// �ý��淨�Ƚ�ֱ��ͼ
		// histogram comparison using intersection
		return cv::compareHist(refH,inputH, cv::HISTCMP_INTERSECT);
	}
};


#endif
