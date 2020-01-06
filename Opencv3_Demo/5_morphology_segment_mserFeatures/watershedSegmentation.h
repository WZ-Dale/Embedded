// 20200104
// ѧϰ��ע�� by wangze

#if !defined WATERSHS
#define WATERSHS

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class WatershedSegmenter {

  private:

	  cv::Mat markers;

  public:

	  void setMarkers(const cv::Mat& markerImage) {
		  // ת����������ͼ��
		// Convert to image of ints
		markerImage.convertTo(markers,CV_32S);
	  }

	  cv::Mat process(const cv::Mat &image) {
		  // Ӧ�÷�ˮ��
		// Apply watershed
		cv::watershed(image,markers);

		return markers;
	  }

	  // ��ͼ�����ʽ���ؽ��
	  // Return result in the form of an image
	  cv::Mat getSegmentation() {
		  
		cv::Mat tmp;
		// ���б�ǩ����255�����ζ���ֵ255
		// all segment with label higher than 255
		// will be assigned value 255
		markers.convertTo(tmp,CV_8U);

		return tmp;
	  }

	  // ��ͼ�����ʽ���ط�ˮ��
	  // Return watershed in the form of an image
	  cv::Mat getWatersheds() {
	
		cv::Mat tmp;
		// �ڱ任ǰ��ÿ������pת��Ϊ255p+255
		markers.convertTo(tmp,CV_8U,255,255);

		return tmp;
	  }
};


#endif
