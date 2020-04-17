#include "TireTest.h"

void onMouse(int event, int x, int y, int flags, void* param) {
	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);
	// �����¼�
	switch (event) {	// dispatch the event
		// �����������¼�
	case cv::EVENT_LBUTTONDOWN: // mouse button down event
		// ��ʾ����ֵ
		// display pixel value at (x,y)
		std::cout << "at (" << x << "," << y << ") value is: " << static_cast<int>(im->at<uchar>(cv::Point(x, y))) << std::endl;
		break;
	}
}
void ShowImage(const cv::String &str, cv::Mat &image) {
	// ������ͼ���������ʾͼƬ�ֱ��ʺ�ͨ����
	std::cout << "This image is " << image.rows << " x " << image.cols << std::endl;
	std::cout << "This image has " << image.channels() << " channel(s)" << std::endl;
	// ���崰�ڣ�choice������ʾͼ��
	cv::namedWindow(str);
	cv::imshow(str, image);
	// ע��ص�����������¼�
	cv::setMouseCallback(str, onMouse, reinterpret_cast<void*>(&image));
	cv::waitKey(0);
}
void LargestConnectedComponent(cv::Mat srcImage, cv::Mat &dstImage)
{
	cv::Mat temp;
	cv::Mat labels;
	srcImage.copyTo(temp);

	//1. �����ͨ��
	int n_comps = connectedComponents(temp, labels, 4, CV_16U);
	std::vector<int> histogram_of_labels;
	for (int i = 0; i < n_comps; i++)//��ʼ��labels�ĸ���Ϊ0
	{
		histogram_of_labels.push_back(0);
	}

	int rows = labels.rows;
	int cols = labels.cols;
	for (int row = 0; row < rows; row++) //����ÿ��labels�ĸ���
	{
		for (int col = 0; col < cols; col++)
		{
			histogram_of_labels.at(labels.at<unsigned short>(row, col)) += 1;
		}
	}
	histogram_of_labels.at(0) = 0; //��������labels��������Ϊ0

	//2. ����������ͨ��labels����
	int maximum = 0;
	int max_idx = 0;
	for (int i = 0; i < n_comps; i++)
	{
		if (histogram_of_labels.at(i) > maximum)
		{
			maximum = histogram_of_labels.at(i);
			max_idx = i;
		}
	}

	//3. �������ͨ����Ϊ1
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if (labels.at<unsigned short>(row, col) == max_idx)
			{
				labels.at<unsigned short>(row, col) = 255;
			}
			else
			{
				labels.at<unsigned short>(row, col) = 0;
			}
		}
	}

	//4. ��ͼ�����ΪCV_8U��ʽ
	labels.convertTo(dstImage, CV_8U);
}

cv::Mat srcImage;
cv::Mat dstImage;

int threshold1 = 100; // bar �ĳ�ֵ��Ҳ����ֵ�ĳ�ֵ
int threshold2 = 150; // bar �ĳ�ֵ��Ҳ����ֵ�ĳ�ֵ
int threshold_bar_max_value = 255; // bar�����ֵ
void ChangeThresholdValue(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::Canny(srcImage, dstImage, threshold1, threshold2); // ��Ե���
	cv::imshow("ThresholdWin", dstImage);
}
void ChangeThreshold1(int, void*)
{
	ChangeThresholdValue(srcImage, dstImage);
}
void ChangeThreshold2(int, void*)
{
	ChangeThresholdValue(srcImage, dstImage);
}
void ThresholdFun(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::namedWindow("ThresholdWin");
	cv::createTrackbar("threshold1 bar", "ThresholdWin", &threshold1, threshold_bar_max_value, ChangeThreshold1);
	ChangeThreshold1(threshold1, 0);
	cv::createTrackbar("threshold2 bar", "ThresholdWin", &threshold2, threshold_bar_max_value, ChangeThreshold2);
	ChangeThreshold2(threshold2, 0);
}

int binarization = 100; // bar �ĳ�ֵ��Ҳ����ֵ�ĳ�ֵ
int binarization_max_vale = 255; // ��ֵ�����ֵ
int binarization_bar_max_value = 255; // bar�����ֵ
void ChangeBinarizationValue(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::threshold(srcImage, dstImage, binarization, binarization_max_vale, cv::THRESH_BINARY); // ��ֵ��
	cv::imshow("BinarizationWin", dstImage);
}
void ChangeBinarization(int, void*)
{
	ChangeBinarizationValue(srcImage, dstImage);
}
void BarbinarizationFun(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::namedWindow("BinarizationWin");
	cv::createTrackbar("binarization bar", "BinarizationWin", &binarization, binarization_bar_max_value, ChangeBinarization);
	ChangeBinarization(binarization, 0);
}


void Test1() {
// ԭͼ
	cv::Mat image = cv::imread("11.jpg", cv::IMREAD_GRAYSCALE);
	//cv::Mat image = cv::imread("11.jpg", cv::IMREAD_COLOR);

	// �����ͼ�����������ʾδ����ͼ��������
	if (image.empty()) {
		std::cout << "Error reading image..." << std::endl;
		return;
	}
	//ShowImage("image", image);
	// 3024 x 3024

// ��ȡͼƬ
	// ��ȡָ������1512
	int x = 256, y = 1512;
	cv::Rect rect(x, y, 3024 - 2 * x + 150, 3024 - y);
	cv::Mat image_roi = image(rect);
	//ShowImage("image_roi", image_roi);

// ��СͼƬ
	cv::Mat image_min;
	cv::resize(image_roi, image_min, cv::Size(), 0.2, 0.2);
	//ShowImage("image_min", image_min);

// ֱ��ͼ���⻯
	cv::Mat equal_hist;
	equalizeHist(image_min, equal_hist); //ֱ��ͼ���⻯
	//ShowImage("equal_hist", equal_hist);

	srcImage = equal_hist;
// ��Ե���
	cv::Canny(srcImage, dstImage, threshold1, threshold2);
	//ShowImage("ThresholdWin", dstImage);
	// ��������Ե���
	//ThresholdFun(srcImage, dstImage);

// ��ֵ��
	//cv::threshold(srcImage, dstImage, binarization, binarization_max_vale, cv::THRESH_BINARY);
	//ShowImage("BinarizationWin", dstImage);
	// ��������ֵ��
	//BarbinarizationFun(srcImage, dstImage);

// ���Ͳ���
	cv::Mat input = dstImage;
	cv::Mat output;
	//��ȡ�Զ����
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)); //��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
	cv::dilate(input, output, element);
	ShowImage("Dilate", output);

// ��ʴ����
	//��ʴ����
	cv::erode(input, output, element);
	ShowImage("Erode", output);

// �߼���̬ѧ����
	cv::morphologyEx(input, output, cv::MORPH_ERODE, element); // ��ʴ
	ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_DILATE, element); // ����
	ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_OPEN, element); // ������
	ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_CLOSE, element); // ������
	ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_GRADIENT, element); // ��̬ѧ�ݶ�
	ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_TOPHAT, element); // ��ñ
	ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_BLACKHAT, element); // ��ñ
	ShowImage("MorphologyEx", output);

	//cv::Mat image_connect;
	//LargestConnectedComponent(image_min, image_connect);
	//ShowImage("image_connect", image_connect);

	//int initial_value = 50;
	//int max_value = 255;
	//createTrackbar("threshold", "Sliding bar", &initial_value, max_value, Changethreshold1);
	//Changethreshold1(initial_value, 0);
	//createTrackbar("threshold", "Sliding bar", &initial_value, max_value, Changethreshold2);
	//Changethreshold2(initial_value, 0);

}
