#include "GLCM.h"
#include <string>

GLCM::GLCM() : m_grayLevel(16)
{

}

GLCM::~GLCM()
{

}

//==============================================================================
// 函数名称: initGLCM
// 参数说明: vecGLCM,要进行初始化的共生矩阵,为二维方阵
//          size, 二维矩阵的大小,必须与图像划分的灰度等级相等
// 函数功能: 初始化二维矩阵
//==============================================================================

void GLCM::initGLCM(VecGLCM& vecGLCM, int size)
{
	assert(size == m_grayLevel);
	vecGLCM.resize(size);
	for (int i = 0; i < size; ++i)
	{
		vecGLCM[i].resize(size);
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			vecGLCM[i][j] = 0;
		}
	}
}

//==============================================================================
// 函数名称: getHorisonGLCM
// 参数说明: src,要进行处理的矩阵,源数据
//          dst,输出矩阵,计算后的矩阵，即要求的灰度共生矩阵
//          imgWidth, 图像宽度
//          imgHeight, 图像高度
// 函数功能: 计算水平方向的灰度共生矩阵
//==============================================================================

void GLCM::getHorisonGLCM(VecGLCM &src, VecGLCM &dst, int imgWidth, int imgHeight)
{
	int height = imgHeight;
	int width = imgWidth;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width - 1; ++j)
		{
			int rows = src[i][j];
			int cols = src[i][j + 1];
			dst[rows][cols]++;
		}
	}


}

//==============================================================================
// 函数名称: getVertialGLCM
// 参数说明: src,要进行处理的矩阵,源数据
//          dst,输出矩阵,计算后的矩阵，即要求的灰度共生矩阵
//          imgWidth, 图像宽度
//          imgHeight, 图像高度
// 函数功能: 计算垂直方向的灰度共生矩阵
//==============================================================================

void GLCM::getVertialGLCM(VecGLCM &src, VecGLCM &dst, int imgWidth, int imgHeight)
{
	int height = imgHeight;
	int width = imgWidth;
	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int rows = src[i][j];
			int cols = src[i + 1][j];
			dst[rows][cols]++;
		}
	}
}

//==============================================================================
// 函数名称: getGLCM45
// 参数说明: src,要进行处理的矩阵,源数据
//          dst,输出矩阵,计算后的矩阵，即要求的灰度共生矩阵
//          imgWidth, 图像宽度
//          imgHeight, 图像高度
// 函数功能: 计算45度的灰度共生矩阵
//==============================================================================

void GLCM::getGLCM45(VecGLCM &src, VecGLCM &dst, int imgWidth, int imgHeight)
{
	int height = imgHeight;
	int width = imgWidth;
	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 0; j < width - 1; ++j)
		{
			int rows = src[i][j];
			int cols = src[i + 1][j + 1];
			dst[rows][cols]++;
		}
	}
}


//==============================================================================
// 函数名称: getGLCM135
// 参数说明: src,要进行处理的矩阵,源数据
//          dst,输出矩阵,计算后的矩阵，即要求的灰度共生矩阵
//          imgWidth, 图像宽度
//          imgHeight, 图像高度
// 函数功能: 计算 135 度的灰度共生矩阵
//==============================================================================

void GLCM::getGLCM135(VecGLCM& src, VecGLCM& dst, int imgWidth, int imgHeight)
{
	int height = imgHeight;
	int width = imgWidth;
	for (int i = 0; i < height - 1; ++i)
	{
		for (int j = 1; j < width; ++j)
		{
			int rows = src[i][j];
			int cols = src[i + 1][j - 1];
			dst[rows][cols]++;
		}
	}
}

//==============================================================================
// 函数名称: calGLCM
// 参数说明: inputImg,要进行纹理特征计算的图像,为灰度图像
//          vecGLCM, 输出矩阵,根据灰度图像计算出的灰度共生阵
//          angle,灰度共生矩阵的方向,有水平、垂直、45度、135度四个方向
// 函数功能: 计算灰度共生矩阵
//==============================================================================

void GLCM::calGLCM(IplImage* inputImg, VecGLCM& vecGLCM, int angle)
{
	assert(inputImg->nChannels == 1);
	IplImage* src = NULL;
	src = cvCreateImage(cvGetSize(inputImg), IPL_DEPTH_32S, inputImg->nChannels);
	cvConvert(inputImg, src);

	int height = src->height;
	int width = src->width;
	int maxGrayLevel = 0;
	// 寻找最大像素灰度最大值
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int grayVal = cvGetReal2D(src, i, j);
			if (grayVal > maxGrayLevel)
			{
				maxGrayLevel = grayVal;
			}

		}
	}// end for i

	++maxGrayLevel;
	VecGLCM tempVec;
	// 初始化动态数组
	tempVec.resize(height);
	for (int i = 0; i < height; ++i)
	{
		tempVec[i].resize(width);
	}

	if (maxGrayLevel > 16)//若灰度级数大于16，则将图像的灰度级缩小至16级，减小灰度共生矩阵的大小。
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				int tmpVal = cvGetReal2D(src, i, j);
				tmpVal /= m_grayLevel;
				tempVec[i][j] = tmpVal;
			}
		}

		if (angle == GLCM_HORIZATION)  // 水平方向
			getHorisonGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_VERTICAL)    // 垂直方向
			getVertialGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE45)     // 45 度灰度共生阵
			getGLCM45(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE135)    // 135 度灰度共生阵
			getGLCM135(tempVec, vecGLCM, width, height);
	}
	else//若灰度级数小于16，则生成相应的灰度共生矩阵
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 1; j < width; ++j)
			{
				int tmpVal = cvGetReal2D(src, i, j);
				tempVec[i][j] = tmpVal;
			}
		}

		if (angle == GLCM_HORIZATION)  // 水平方向
			getHorisonGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_VERTICAL)    // 垂直方向
			getVertialGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE45)     // 45 度灰度共生阵
			getGLCM45(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE135)    // 135 度灰度共生阵
			getGLCM135(tempVec, vecGLCM, width, height);
	}

	cvReleaseImage(&src);
}

//==============================================================================
// 函数名称: getGLCMFeatures
// 参数说明: vecGLCM, 输入矩阵,灰度共生阵
//          features,灰度共生矩阵计算的特征值,主要包含了能量、熵、对比度、逆差分矩
// 函数功能: 根据灰度共生矩阵计算的特征值
//==============================================================================

void GLCM::getGLCMFeatures(VecGLCM& vecGLCM, GLCMFeatures& features)
{
	int total = 0;

	for (int i = 0; i < m_grayLevel; ++i)
	{
		for (int j = 0; j < m_grayLevel; ++j)
		{
			total += vecGLCM[i][j];     // 求所有图像的灰度值的和
		}
	}

	vector<vector<double> > temp;
	temp.resize(m_grayLevel);
	for (int i = 0; i < m_grayLevel; ++i)
	{
		temp[i].resize(m_grayLevel);
	}

	// 归一化
	for (int i = 0; i < m_grayLevel; ++i)
	{
		for (int j = 0; j < m_grayLevel; ++j)
		{
			temp[i][j] = (double)vecGLCM[i][j] / (double)total;
		}
	}

	for (int i = 0; i < m_grayLevel; ++i)
	{
		for (int j = 0; j < m_grayLevel; ++j)
		{
			features.energy += temp[i][j] * temp[i][j];

			if (temp[i][j] > 0)
				features.entropy -= temp[i][j] * log(temp[i][j]);               //熵     

			features.contrast += (double)(i - j)*(double)(i - j)*temp[i][j];        //对比度
			features.idMoment += temp[i][j] / (1 + (double)(i - j)*(double)(i - j));//逆差矩
		}
	}
}

//void getFileName();
//string names[2000];
//char data[20];
//const string filename = "T2.jpg";

void Test3(const char* ch)
{
	fstream finout1("data.txt", ios::in | ios::out | ios::app);
	//getFileName();
	//int i = 0;
	//char data1[20];
	//while (names[i].length() > 5) {
	//	strcpy_s(data1, names[i].c_str());
	//	string imagename = data1;
		//灰度共生矩阵
		IplImage* img = cvLoadImage(ch, 0);
		//cvSetImageROI(img, cvRect(1453, 1149, 557, 557));
		//cvNamedWindow("ShowSRC");
		//cvShowImage("ShowSRC",img);
		//cvWaitKey(0);

		GLCM glcm;
		VecGLCM vec;
		GLCMFeatures features;
		glcm.initGLCM(vec);
		// 水平
		glcm.calGLCM(img, vec, GLCM::GLCM_HORIZATION);
		glcm.getGLCMFeatures(vec, features);
		double energy_hor = features.energy;
		double entropy_hor = features.entropy;
		double contrast_hor = features.contrast;
		double idMoment_hor = features.idMoment;

		// 垂直
		glcm.calGLCM(img, vec, GLCM::GLCM_VERTICAL);
		glcm.getGLCMFeatures(vec, features);
		double energy_vetical = features.energy;
		double entropy_vetical = features.entropy;
		double contrast_vetical = features.contrast;
		double idMoment_vetical = features.idMoment;


		// 45 度
		glcm.calGLCM(img, vec, GLCM::GLCM_ANGLE45);
		glcm.getGLCMFeatures(vec, features);
		double energy_45 = features.energy;
		double entropy_45 = features.entropy;
		double contrast_45 = features.contrast;
		double idMoment_45 = features.idMoment;


		// 135 度
		glcm.calGLCM(img, vec, GLCM::GLCM_ANGLE135);
		glcm.getGLCMFeatures(vec, features);
		double energy_135 = features.energy;
		double entropy_135 = features.entropy;
		double contrast_135 = features.contrast;
		double idMoment_135 = features.idMoment;

		double energy_average = (energy_135 + energy_45 + energy_hor + energy_vetical) / 4;
		double entropy_average = (entropy_135 + entropy_45 + entropy_hor + entropy_vetical) / 4;
		double contrast_average = (contrast_135 + contrast_45 + contrast_hor + contrast_vetical) / 4;
		double idMoment_average = (idMoment_135 + idMoment_45 + idMoment_hor + idMoment_vetical) / 4;
		
		//static int i = 1;
		//
		//if (i == 1)
		//	cout << "Num" << "\t" << "energy" << "\t\t" << "entropy" << "\t\t" << "contrast" << "\t" << "idMoment" << endl;
		////cout << "energy_average" << "\t" << "entropy_average" << "\t" << "contrast_average" << "\t" << "idMoment_average" << endl;
		//cout << i << "\t" << energy_average << "\t" << entropy_average << "\t\t" << contrast_average << "\t\t" << idMoment_average << endl;

		//if (i == 1)
		//	finout1 << "Num" << "\t" << "energy" << "\t\t" << "entropy" << "\t\t" << "contrast" << "\t" << "idMoment" << endl;
		////finout1 << "energy_average" << "\t" << "entropy_average" << "\t" << "contrast_average" << "\t" << "idMoment_average" << endl;
		//finout1  << i << "\t" << energy_average << "\t" << entropy_average << "\t\t" << contrast_average << "\t\t" << idMoment_average << endl;


		//++i;


		int sum = 0;
		if (energy_average <= 0.3) {
			sum += 1;		
		}
		else { sum -= 1; }
		if (entropy_average >= 7.3) {
			sum += 1;
		}
		else { sum -= 1; }
		if (contrast_average >= 2.2) {
			sum += 2;
		}
		else { sum -= 2; }
		if (idMoment_average <= 2.11) {
			sum += 1;
		}
		else { sum -= 1; }
		cout << sum << endl;

			

		//i++;
	//}
}

//void getFileName() {
//	fstream finout("FILENAME.TXT", ios::in | ios::out);
//	ostringstream outstr;
//	if (finout.is_open()) {
//		finout.seekg(0);
//		int i = 0;
//		while (finout.getline(data, 19)) {
//			outstr << data;
//
//			names[i] = outstr.str();
//			//cout <<setw(30)<<i<<setw(30)<<names[i]<<'\n';
//			i++;
//			outstr.str("");
//
//		}
//	}
//	else
//		cout << "failed" << endl;
//}