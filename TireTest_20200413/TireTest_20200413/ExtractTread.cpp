#include "ExtractTread.h"

cv::Mat srcImage;
cv::Mat dstImage;

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
	//std::cout << "This image is " << image.rows << " x " << image.cols << std::endl;
	//std::cout << "This image has " << image.channels() << " channel(s)" << std::endl;
	// ���崰�ڣ�choice������ʾͼ��
	cv::namedWindow(str, cv::WINDOW_AUTOSIZE);
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
	int n_comps = cv::connectedComponents(temp, labels, 4, CV_16U);
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

// ��������ֵ��
int binarization = 170; // bar �ĳ�ֵ��Ҳ����ֵ�ĳ�ֵ
int binarization_max_vale = 255; // ��ֵ�����ֵ
int binarization_bar_max_value = 255; // bar�����ֵ
void ChangeBinarizationValue(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::threshold(srcImage, dstImage, binarization, binarization_max_vale, cv::THRESH_BINARY); // ��ֵ��
	cv::imshow("BinarizationWin", dstImage);
	//cv::Mat image_connect;
	//LargestConnectedComponent(dstImage, image_connect);
	//cv::imshow("BinarizationWin", image_connect);
}
void ChangeBinarization(int, void*)
{
	ChangeBinarizationValue(srcImage, dstImage);
}
void BarbinarizationFun(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::namedWindow("BinarizationWin", cv::WINDOW_NORMAL);
	cv::createTrackbar("binarization bar", "BinarizationWin", &binarization, binarization_bar_max_value, ChangeBinarization);
	ChangeBinarization(binarization, 0);
}

// ��������Ե���
int threshold1 = 100; // bar �ĳ�ֵ��Ҳ����ֵ�ĳ�ֵ
int threshold_bar_max_value = 1000; // bar�����ֵ
void ChangeThresholdValue(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::Canny(srcImage, dstImage, threshold1, 2 * threshold1, 3, false); // ��Ե���
	cv::imshow("ThresholdWin", dstImage);
	//cv::Mat image_connect;
	//LargestConnectedComponent(dstImage, image_connect);
	//cv::imshow("ThresholdWin", image_connect);
}
void ChangeThreshold(int, void*)
{
	ChangeThresholdValue(srcImage, dstImage);
}
void ThresholdFun(cv::Mat inputImage, cv::Mat outputImage)
{
	cv::namedWindow("ThresholdWin", cv::WINDOW_NORMAL);
	cv::createTrackbar("threshold1 bar", "ThresholdWin", &threshold1, threshold_bar_max_value, ChangeThreshold);
	ChangeThreshold(threshold1, 0);
}


void Test1() {
// ԭͼ
	cv::Mat image = cv::imread("22.jpg", cv::IMREAD_GRAYSCALE);
	// �����ͼ�����������ʾδ����ͼ��������
	if (image.empty()) {
		std::cout << "Error reading image..." << std::endl;
		return;
	}
	//ShowImage("image", image);
	// 3024 x 3024

// ��ȡͼƬ
	// ��ȡָ������1512
	int x = 0, y = image.rows / 4;
	cv::Rect rect(x, y, image.cols, 2 * y);
	cv::Mat image_roi = image(rect);
	//ShowImage("image_roi", image_roi);

// ��СͼƬ
	cv::Mat image_min;
	cv::resize(image_roi, image_min, cv::Size(), 0.2, 0.2);
	//ShowImage("image_min", image_min);

// ֱ��ͼ���⻯
	cv::Mat equal_hist;
	cv::equalizeHist(image_min, equal_hist); //ֱ��ͼ���⻯
	//ShowImage("equal_hist", equal_hist);

	srcImage = equal_hist;
	//srcImage = image_min;


	//cv::findContours(srcImage, );


// ��ֵ��
	//cv::threshold(srcImage, dstImage, binarization, binarization_max_vale, cv::THRESH_BINARY);
	//ShowImage("BinarizationWin", dstImage);
	// ��������ֵ��
	BarbinarizationFun(srcImage, dstImage);

// ��Ե���
	//cv::Canny(dstImage, dstImage, threshold1, threshold2, 7);
	//ShowImage("ThresholdWin", dstImage);
	// ��������Ե���
	ThresholdFun(srcImage, dstImage);


/*
// ���Ͳ���
	cv::Mat input = dstImage;
	cv::Mat output;
	//��ȡ�Զ����
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)); //��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�


// ��ʴ����
	//��ʴ����
	cv::erode(input, output, element);
	ShowImage("Erode", output);
	
	
	cv::dilate(input, output, element);
	ShowImage("Dilate", output);

// �߼���̬ѧ����
	//cv::morphologyEx(input, output, cv::MORPH_ERODE, element); // ��ʴ
	//ShowImage("MorphologyEx", output);
	//cv::morphologyEx(input, output, cv::MORPH_DILATE, element); // ����
	//ShowImage("MorphologyEx", output);
	//cv::morphologyEx(input, output, cv::MORPH_OPEN, element); // ������
	//ShowImage("MorphologyEx", output);
	cv::morphologyEx(input, output, cv::MORPH_CLOSE, element); // ������
	ShowImage("MorphologyEx", output);
	//cv::morphologyEx(input, output, cv::MORPH_GRADIENT, element); // ��̬ѧ�ݶ�
	//ShowImage("MorphologyEx", output);
	//cv::morphologyEx(input, output, cv::MORPH_TOPHAT, element); // ��ñ
	//ShowImage("MorphologyEx", output);
	//cv::morphologyEx(input, output, cv::MORPH_BLACKHAT, element); // ��ñ
	//ShowImage("MorphologyEx", output);

// �����ͨ��
	cv::Mat image_connect;
	LargestConnectedComponent(dstImage, image_connect);
	ShowImage("image_connect", image_connect);

// ��ȡ̥��


*/


}


void Test2() {
// ԭͼ
	cv::Mat image = cv::imread("221.jpg", cv::IMREAD_GRAYSCALE);
	if (image.empty()) {
		std::cout << "Error reading image..." << std::endl;
		return;
	}
	//ShowImage("image", image);

// ��ȡͼƬ
	int x = 0, y = image.rows / 4;
	cv::Rect rect(x, y, image.cols, 2 * y);
	cv::Mat image_roi = image(rect);
	//ShowImage("image_roi", image_roi);

// ��СͼƬ
	cv::Mat image_min;
	cv::resize(image_roi, image_min, cv::Size(), 0.2, 0.2);
	ShowImage("image_min", image_min);


// ֱ��ͼ���⻯
	//cv::Mat equal_hist;
	//cv::equalizeHist(image_min, equal_hist); //ֱ��ͼ���⻯
	//ShowImage("equal_hist", equal_hist);

	srcImage = image_min;
	//srcImage = equal_hist;
// ��ֵ��
	cv::threshold(srcImage, dstImage, binarization, binarization_max_vale, cv::THRESH_BINARY);
	ShowImage("BinarizationWin", dstImage);

	cv::Mat input = dstImage;
	cv::Mat output;

	//��ȡ�Զ����
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)); //��һ������MORPH_RECT��ʾ���εľ���ˣ���Ȼ������ѡ����Բ�εġ������͵�
// ���Ͳ���
	for (int i = 0; i < 12; ++i) {
		cv::dilate(input, output, element);
		input = output;
	}
	ShowImage("Dilate", output);
// ��ʴ����
	for (int i = 0; i < 20; ++i) {
		cv::erode(output, output, element);
	}
	ShowImage("Erode", output);

// ��Ե���
	cv::Canny(output, dstImage, threshold1, 2 * threshold1, 7, true);
	for (int i = 0; i < dstImage.cols; ++i) {
		dstImage.at<uchar>(0, i) = 255;
		dstImage.at<uchar>(dstImage.rows - 1, i) = 255;
	}
	ShowImage("ThresholdWin", dstImage);
	
// ��ɫ
	cv::bitwise_not(dstImage, dstImage);

	ShowImage("bitwise_not", dstImage);
// �����ͨ��
	cv::Mat image_connect;
	LargestConnectedComponent(dstImage, image_connect);
	ShowImage("image_connect", image_connect);

// ���Ͳ���
	input = image_connect;
	for (int i = 0; i < 5; ++i) {
		cv::dilate(input, output, element);
		input = output;
	}
	ShowImage("Dilate", output);

// ��ʴ����
	for (int i = 0; i < 15; ++i) {
		cv::erode(output, output, element);
	}
	ShowImage("Erode", output);


// �����
	for (int i = 0; i < output.rows; ++i) {
		for (int j = 0; j < output.cols; ++j) {
			if (output.at<uchar>(i, j) == 0) {
				image_min.at<uchar>(i, j) = 0;
			}
		}
	
	}
	ShowImage("yu", image_min);

// ����̥��ͼƬ
	//cv::imwrite("T2.jpg", image_min);



// ��ֵ��
	srcImage = image_min;
	BarbinarizationFun(srcImage, dstImage);
}
