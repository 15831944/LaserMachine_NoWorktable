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
	HObject m_hoImg;							//抓标时的相机图片
	HObject m_hoXldModel;						//抓标模板，可能是Image或contour
	HObject m_hoXldModelContourAffine;		//抓标结果contour

	HTuple m_hvModelOriginRow;				//抓标锚点
	HTuple m_hvModelOriginColumn;
	HTuple m_hvModelScaleMin;				//抓标尺寸容差
	HTuple m_hvModelScaleMax;
	HTuple m_hvModelMinScore;				//抓标最小得分
	CPointF m_ptMatchDomainPos;				//在相机局部视窗中匹配时，局部视窗中心相对相机中心的像素坐标
	double m_fMatchDomainSizeFactor;		//在相机局部视窗中匹配时，因子 = 局部视窗尺寸/模板外框尺寸
	std::vector<CPointF> m_vPtPosFindedModels;

};

