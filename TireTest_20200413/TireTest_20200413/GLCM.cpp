#include "GLCM.h"
#include <string>

GLCM::GLCM() : m_grayLevel(16)
{

}

GLCM::~GLCM()
{

}

//==============================================================================
// ��������: initGLCM
// ����˵��: vecGLCM,Ҫ���г�ʼ���Ĺ�������,Ϊ��ά����
//          size, ��ά����Ĵ�С,������ͼ�񻮷ֵĻҶȵȼ����
// ��������: ��ʼ����ά����
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
// ��������: getHorisonGLCM
// ����˵��: src,Ҫ���д���ľ���,Դ����
//          dst,�������,�����ľ��󣬼�Ҫ��ĻҶȹ�������
//          imgWidth, ͼ����
//          imgHeight, ͼ��߶�
// ��������: ����ˮƽ����ĻҶȹ�������
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
// ��������: getVertialGLCM
// ����˵��: src,Ҫ���д���ľ���,Դ����
//          dst,�������,�����ľ��󣬼�Ҫ��ĻҶȹ�������
//          imgWidth, ͼ����
//          imgHeight, ͼ��߶�
// ��������: ���㴹ֱ����ĻҶȹ�������
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
// ��������: getGLCM45
// ����˵��: src,Ҫ���д���ľ���,Դ����
//          dst,�������,�����ľ��󣬼�Ҫ��ĻҶȹ�������
//          imgWidth, ͼ����
//          imgHeight, ͼ��߶�
// ��������: ����45�ȵĻҶȹ�������
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
// ��������: getGLCM135
// ����˵��: src,Ҫ���д���ľ���,Դ����
//          dst,�������,�����ľ��󣬼�Ҫ��ĻҶȹ�������
//          imgWidth, ͼ����
//          imgHeight, ͼ��߶�
// ��������: ���� 135 �ȵĻҶȹ�������
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
// ��������: calGLCM
// ����˵��: inputImg,Ҫ�����������������ͼ��,Ϊ�Ҷ�ͼ��
//          vecGLCM, �������,���ݻҶ�ͼ�������ĻҶȹ�����
//          angle,�Ҷȹ�������ķ���,��ˮƽ����ֱ��45�ȡ�135���ĸ�����
// ��������: ����Ҷȹ�������
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
	// Ѱ��������ػҶ����ֵ
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
	// ��ʼ����̬����
	tempVec.resize(height);
	for (int i = 0; i < height; ++i)
	{
		tempVec[i].resize(width);
	}

	if (maxGrayLevel > 16)//���Ҷȼ�������16����ͼ��ĻҶȼ���С��16������С�Ҷȹ�������Ĵ�С��
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

		if (angle == GLCM_HORIZATION)  // ˮƽ����
			getHorisonGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_VERTICAL)    // ��ֱ����
			getVertialGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE45)     // 45 �ȻҶȹ�����
			getGLCM45(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE135)    // 135 �ȻҶȹ�����
			getGLCM135(tempVec, vecGLCM, width, height);
	}
	else//���Ҷȼ���С��16����������Ӧ�ĻҶȹ�������
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 1; j < width; ++j)
			{
				int tmpVal = cvGetReal2D(src, i, j);
				tempVec[i][j] = tmpVal;
			}
		}

		if (angle == GLCM_HORIZATION)  // ˮƽ����
			getHorisonGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_VERTICAL)    // ��ֱ����
			getVertialGLCM(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE45)     // 45 �ȻҶȹ�����
			getGLCM45(tempVec, vecGLCM, width, height);
		if (angle == GLCM_ANGLE135)    // 135 �ȻҶȹ�����
			getGLCM135(tempVec, vecGLCM, width, height);
	}

	cvReleaseImage(&src);
}

//==============================================================================
// ��������: getGLCMFeatures
// ����˵��: vecGLCM, �������,�Ҷȹ�����
//          features,�Ҷȹ���������������ֵ,��Ҫ�������������ء��Աȶȡ����־�
// ��������: ���ݻҶȹ���������������ֵ
//==============================================================================

void GLCM::getGLCMFeatures(VecGLCM& vecGLCM, GLCMFeatures& features)
{
	int total = 0;

	for (int i = 0; i < m_grayLevel; ++i)
	{
		for (int j = 0; j < m_grayLevel; ++j)
		{
			total += vecGLCM[i][j];     // ������ͼ��ĻҶ�ֵ�ĺ�
		}
	}

	vector<vector<double> > temp;
	temp.resize(m_grayLevel);
	for (int i = 0; i < m_grayLevel; ++i)
	{
		temp[i].resize(m_grayLevel);
	}

	// ��һ��
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
				features.entropy -= temp[i][j] * log(temp[i][j]);               //��     

			features.contrast += (double)(i - j)*(double)(i - j)*temp[i][j];        //�Աȶ�
			features.idMoment += temp[i][j] / (1 + (double)(i - j)*(double)(i - j));//����
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
		//�Ҷȹ�������
		IplImage* img = cvLoadImage(ch, 0);
		//cvSetImageROI(img, cvRect(1453, 1149, 557, 557));
		//cvNamedWindow("ShowSRC");
		//cvShowImage("ShowSRC",img);
		//cvWaitKey(0);

		GLCM glcm;
		VecGLCM vec;
		GLCMFeatures features;
		glcm.initGLCM(vec);
		// ˮƽ
		glcm.calGLCM(img, vec, GLCM::GLCM_HORIZATION);
		glcm.getGLCMFeatures(vec, features);
		double energy_hor = features.energy;
		double entropy_hor = features.entropy;
		double contrast_hor = features.contrast;
		double idMoment_hor = features.idMoment;

		// ��ֱ
		glcm.calGLCM(img, vec, GLCM::GLCM_VERTICAL);
		glcm.getGLCMFeatures(vec, features);
		double energy_vetical = features.energy;
		double entropy_vetical = features.entropy;
		double contrast_vetical = features.contrast;
		double idMoment_vetical = features.idMoment;


		// 45 ��
		glcm.calGLCM(img, vec, GLCM::GLCM_ANGLE45);
		glcm.getGLCMFeatures(vec, features);
		double energy_45 = features.energy;
		double entropy_45 = features.entropy;
		double contrast_45 = features.contrast;
		double idMoment_45 = features.idMoment;


		// 135 ��
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
		
		static int i = 1;

		if (i == 1)
			cout << "Num" << "\t" << "energy" << "\t\t" << "entropy" << "\t\t" << "contrast" << "\t" << "idMoment" << endl;
		//cout << "energy_average" << "\t" << "entropy_average" << "\t" << "contrast_average" << "\t" << "idMoment_average" << endl;
		cout << i << "\t" << energy_average << "\t" << entropy_average << "\t\t" << contrast_average << "\t\t" << idMoment_average << endl;

		if (i == 1)
			finout1 << "Num" << "\t" << "energy" << "\t\t" << "entropy" << "\t\t" << "contrast" << "\t" << "idMoment" << endl;
		//finout1 << "energy_average" << "\t" << "entropy_average" << "\t" << "contrast_average" << "\t" << "idMoment_average" << endl;
		finout1  << i << "\t" << energy_average << "\t" << entropy_average << "\t\t" << contrast_average << "\t\t" << idMoment_average << endl;

		++i;

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