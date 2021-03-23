#pragma once

#include <vector>
#include <cstring>
#include "PointF.h"
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
using namespace HalconCpp;

#ifndef DEFAULT_MODEL_PARAM
#define DEFAULT_SCALE_MIN 0.95
#define DEFAULT_SCALE_MAX 1.05
#define DEFAULT_MIN_SCORE 0.8
#endif

enum class ModelType { MT_Circle, MT_Cross, MT_ClosedPolyline };

class ModelBase
{
public:
	ModelBase();
    virtual ~ModelBase() {}

	//�Ƿ���ʾ��ת�Ƕ�
	//�Ƿ���ʾץ��������������BOOL bShowContour = TRUE, BOOL bShowText = TRUE
	//�Ƿ��ץ�����������������Զ�У��BOOL bSort = FALSE, int const nSortRow = 0, int const nSortColumn = 0
	int LocateModel(std::vector <CPointF>& vPtPos, std::vector <double>& vFAngle,  BOOL bShowContour = TRUE, BOOL bShowText = TRUE,
					BOOL bSort = FALSE, int const nSortRow = 0, int const nSortColumn = 0);

	void SetImage(HObject const hoImg);
	void SetImage();

	void SetScale(double fScaleMin, double fScaleMax);
	void SetMinScore(double fMinScore);
	void SetMatchDomain(CPointF const ptPos, double fSizeFactor);
	void GetMatchDomain(CPointF& ptPos, double& fSizeFactor);
	void SetMatchedPos(std::vector <CPointF> const vPtPos);
	void GetMatchedPos(std::vector <CPointF>& vPtPos);

protected:
	HWND GetHwndShow();
	void TransLogicToCamera(HTuple *hvRow, HTuple *hvCol, double const fX, double const fY);
	void TransCameraToLogic(double *fX, double *fY, HTuple const hvRow, HTuple const hvCol);
	void TransCameraToLogic(HTuple* hvX, HTuple* hvY, HTuple const hvRow, HTuple const hvCol);
	void SortMtatchResult(HTuple* hvRow, HTuple* hvCol, HTuple* hvAngle, HTuple* hvScale, HTuple* hvScore, int const nCountRow, int const cCountCol);

protected:
	ModelType m_eModelType;					//ģ������

	//��Ƭ + ģ��
	HObject m_hoImg;						//ץ����Ƭ
	HObject m_hoModel;						//ץ��ģ�壬������Image��contour
	HObject m_hoContourAffine;				//ץ����contour

	//ץ�����
	double m_fPixelSize;					//���سߴ� mm/p
	double m_fModelOriginRow;					//ץ��ê��
	double m_fModelOriginColumn;
	double m_fModelScaleMin;				//ץ�������ݲ�
	double m_fModelScaleMax;
	double m_fModelMinScore;				//ץ����С�÷�
	CPointF m_ptMatchDomainPos;				//������ֲ��Ӵ���ƥ��ʱ���ֲ��Ӵ��������������ĵ���������
	double m_fMatchDomainSizeFactor;		//������ֲ��Ӵ���ƥ��ʱ������ = �ֲ��Ӵ��ߴ�/ģ�����ߴ�

	//ץ����
	std::vector<CPointF> m_vPtPos;			//ģ������������ƫ������/mm
};



class ModelCircle :public ModelBase
{
public:
	ModelCircle(double fPixelSize, double fRadius);

protected:
	double m_fRadius;
};

class ModelCross :public ModelBase
{
public:
	ModelCross(double fPixelSize, double fLength, double fWidth);

protected:
	double 	m_fLength;
	double 	m_fWidth;
};

class ModelClosedPolyline :public ModelBase
{
public:
	ModelClosedPolyline(double fPixelSize, std::vector<CPointF> const vecPt);

protected:
	std::vector<CPointF> m_vecPt;
};



class ModelFactory
{
public:
	//static ModelBase* creatModel(ModelType type)
	//{
	//	switch (type)
	//	{
	//	case ModelType::MT_Circle:
	//		return new ModelCircle();
	//		break;
	//	case ModelType::MT_Cross:
	//		return new ModelCross();
	//		break;
	//	default:
	//		return NULL;
	//		break;
	//	}
	//}

	static ModelBase* creatModel(ModelType typeCircle, double fPixelSize, double fRadius)
	{
		if (ModelType::MT_Circle != typeCircle)
			return NULL;

		return new ModelCircle(fPixelSize, fRadius);
	}

	static ModelBase* creatModel(ModelType typeCross, double fPixelSize, double fLength, double fWidth)
	{
		if (ModelType::MT_Cross != typeCross)
			return NULL;

		return new ModelCross(fPixelSize, fLength, fWidth);
	}

	static ModelBase* creatModel(ModelType typeCross, double fPixelSize, std::vector<CPointF> const vecPt)
	{
		if (ModelType::MT_ClosedPolyline != typeCross)
			return NULL;

		return new ModelClosedPolyline(fPixelSize, vecPt);
	}


};






