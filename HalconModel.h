#pragma once

#include <cstring>
#include <vector>
#include "PointF.h"
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>

#ifndef DEFAULT_VALUE
#define DEFAULT_SCALE_MIN 0.9
#define DEFAULT_SCALE_MAX 1.1
#define DEFAULT_MIN_SCORE 0.7
#endif

using namespace HalconCpp;

class HalconModel
{
public:
	//~HalconModel() {};
	HalconModel();
	HalconModel(CString strCircle, double fRadius, double fPixelSize);
	HalconModel(CString strCross, double fLength, double fWidth, double fPixelSize);

	void SetScale(double fScaleMin, double fScaleMax);
	void SetMinScore(double fMinScore);
	void SetMatchDomain(double fPosX, double fPosY, double fPixelSize, double fSizeFactor = 2);

public:
	CString m_strModelType;
	HObject m_hoImg;							//ץ��ʱ�����ͼƬ
	HObject m_hoXldModel;						//ץ��ģ�壬������Image��contour
	HObject m_hoXldModelContourAffine;		//ץ����contour

	HTuple m_hvModelOriginRow;				//ץ��ê��
	HTuple m_hvModelOriginColumn;
	HTuple m_hvModelScaleMin;				//ץ��ߴ��ݲ�
	HTuple m_hvModelScaleMax;
	HTuple m_hvModelMinScore;				//ץ����С�÷�
	CPointF m_ptMatchDomainPos;				//������ֲ��Ӵ���ƥ��ʱ���ֲ��Ӵ��������������ĵ���������
	double m_fMatchDomainSizeFactor;		//������ֲ��Ӵ���ƥ��ʱ������ = �ֲ��Ӵ��ߴ�/ģ�����ߴ�
	std::vector<CPointF> m_vPtPosFindedModels;

};

