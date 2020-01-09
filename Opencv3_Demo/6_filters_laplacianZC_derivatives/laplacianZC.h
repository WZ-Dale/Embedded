// 20200107
// ѧϰ��ע�� by wangze

#if !defined LAPLACEZC
#define LAPLACEZC

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class LaplacianZC {

  private:
	  // laplacian��������˹���ӣ�
	  cv::Mat laplace;

	  // Aperture size of the laplacian kernel��������˹�ں˵Ŀ׾���С��
	  int aperture;

  public:

	  LaplacianZC() : aperture(3) {}

	  // Set the aperture size of the kernel�������ں˵Ŀ׾���С��
	  void setAperture(int a) {

		  aperture= a;
	  }

	  // Get the aperture size of the kernel
	  int getAperture() const {

		  return aperture;
	  }

	  // Compute the floating point Laplacian�����㸡�������͵�������˹���ӣ�
	  cv::Mat computeLaplacian(const cv::Mat& image) {

		  // Compute Laplacian������������˹���ӣ�
		  cv::Laplacian(image,laplace,CV_32F,aperture);

		  return laplace;
	  }

	  // Get the Laplacian result in 8-bit image �����������˹���������8λͼ���У�
	  // zero corresponds to gray level 128��0��ʾ�Ҷȼ�128��
	  // if no scale is provided, then the max value will be�������ָ�����ű�������ô���ֵ��Ŵ�255��
	  // scaled to intensity 255
	  // You must call computeLaplacian before calling this method���ڵ����������֮ǰ�������ȵ���computeLaplacian��
	  cv::Mat getLaplacianImage(double scale=-1.0) {

		  if (scale<0) {
	
			  double lapmin, lapmax;
			  // ȡ����С�����������˹ֵ
			  cv::minMaxLoc(laplace,&lapmin,&lapmax);
			  // ����������˹���ӵ�127
			  scale= 127/ std::max(-lapmin,lapmax);
		  }
		  // ���ɻҶ�ͼ��
		  cv::Mat laplaceImage;
		  laplace.convertTo(laplaceImage,CV_8U,scale,128);

		  return laplaceImage;
	  }

	  // Get a binary image of the zero-crossings����ù����Ķ�ֵͼ��
	  // laplacian image should be CV_32F��������˹ͼ������ͱ�����CV_32F��
	  cv::Mat getZeroCrossings(cv::Mat laplace) {

		  // threshold at 0����ֵΪ0��
		  // negative values in black�������ú�ɫ��
		  // positive values in white�������ð�ɫ��
		  cv::Mat signImage;
		  cv::threshold(laplace,signImage,0,255,cv::THRESH_BINARY);

		  // convert the +/- image into CV_8U����+/-ͼ��ת����CV_8U��
		  cv::Mat binary;
		  signImage.convertTo(binary,CV_8U);

		  // dilate the binary image of +/- regions������+/-����Ķ�ֵͼ��
		  cv::Mat dilated;
		  cv::dilate(binary,dilated,cv::Mat());
	
		  // return the zero-crossing contours�����ع�����������
		  return dilated-binary;
	  }
};


#endif
