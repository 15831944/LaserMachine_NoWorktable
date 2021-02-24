#pragma once

#include <cstring>
#include <vector>
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
	HalconModel(CString strCircle, double fRadius, double fPixelSize, double fScaleMin = DEFAULT_SCALE_MIN, double fScaleMax = DEFAULT_SCALE_MAX, double fMinScore = DEFAULT_MIN_SCORE,
		int nRgnRowMin = 0, int nRgnRowMax = 0, int nRgnColMin = 0, int nRgnColMax = 0);
	HalconModel(CString strCross, double fLength, double fWidth, double fPixelSize, double fScaleMin = DEFAULT_SCALE_MIN, double fScaleMax = DEFAULT_SCALE_MAX, double fMinScore = DEFAULT_MIN_SCORE,
		int nRgnRowMin = 0, int nRgnRowMax = 0, int nRgnColMin = 0, int nRgnColMax = 0);


public:
	CString m_strModelType;
	HObject m_hoImg;							//抓标时的相机图片
	HObject m_hoXldModel;						//抓标模板，可能是Image或contour
	HObject m_hoXldModelContourAffine;		//抓标结果contour
	HTuple m_hvModelOriginRow;
	HTuple m_hvModelOriginColumn;
	HTuple m_hvModelScaleMin;
	HTuple m_hvModelScaleMax;
	HTuple m_hvModelMinScore;
	int m_nRgnRowMin;
	int m_nRgnRowMax;
	int m_nRgnColMin;
	int m_nRgnColMax;

};

