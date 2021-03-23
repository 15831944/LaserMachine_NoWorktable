#include "stdafx.h"
#include "HalconModel.h"


HalconModel::HalconModel()
{
	m_strModelType = CString();
	m_hoImg = HObject();
	m_hoXldModel = HObject();
	m_hoXldModelContourAffine = HObject();
	m_hvModelOriginRow = 0;
	m_hvModelOriginColumn = 0;
	m_hvModelScaleMin = DEFAULT_SCALE_MIN;
	m_hvModelScaleMax = DEFAULT_SCALE_MAX;
	m_hvModelMinScore = DEFAULT_MIN_SCORE;

	m_ptMatchDomainPos = CPointF(0, 0);
	m_fMatchDomainSizeFactor = 0;

	m_vPtPosFindedModels.resize(0);
}

HalconModel::HalconModel(CString strCircle, double fRadius, double fPixelSize)
{
	m_strModelType = strCircle;
	m_hoImg = HObject();
	//GenCircleContourXld(&hoXldModel, 0, 0, fRadius / fPixelSize, 0, 6.28318, "positive", 1);
	m_hoXldModelContourAffine = HObject();
	m_hvModelOriginRow = 0;
	m_hvModelOriginColumn = 0;
	m_hvModelScaleMin = DEFAULT_SCALE_MIN;
	m_hvModelScaleMax = DEFAULT_SCALE_MAX;
	m_hvModelMinScore = DEFAULT_MIN_SCORE;
	m_ptMatchDomainPos = CPointF(0, 0);
	m_fMatchDomainSizeFactor = 0;
	m_vPtPosFindedModels.resize(0);


	{
		//生成模板圆图片，如果尺寸不变，就用原图
		HObject ho_ContCircleModel, ho_ContCircleModelCentered, ho_ContCircleModelImage, ho_ContCircleModelRegion, ho_ContCircleModelRegionDilation;
		HTuple hv_CircleRadiusPixel, hv_CircleImageHeight, hv_CircleImageWidth, hv_Hom2d;

		hv_CircleRadiusPixel = fRadius / fPixelSize;
		hv_CircleImageHeight = hv_CircleRadiusPixel * 2 + 10;
		hv_CircleImageWidth = hv_CircleRadiusPixel * 2 + 10;
		GenCircleContourXld(&ho_ContCircleModel, 0, 0, hv_CircleRadiusPixel, 0, 6.28318, "positive", 1);
		HomMat2dIdentity(&hv_Hom2d);
		HomMat2dTranslate(hv_Hom2d, hv_CircleImageHeight / 2, hv_CircleImageWidth / 2, &hv_Hom2d);
		AffineTransContourXld(ho_ContCircleModel, &ho_ContCircleModelCentered, hv_Hom2d);
		GenImageConst(&ho_ContCircleModelImage, "byte", hv_CircleImageWidth, hv_CircleImageHeight);
		PaintXld(ho_ContCircleModelCentered, ho_ContCircleModelImage, &ho_ContCircleModelImage, 255);
		Threshold(ho_ContCircleModelImage, &ho_ContCircleModelRegion, 10, 255);
		DilationRectangle1(ho_ContCircleModelRegion, &ho_ContCircleModelRegionDilation, 3, 3);
		ReduceDomain(ho_ContCircleModelImage, ho_ContCircleModelRegionDilation, &m_hoXldModel);
	}

}

HalconModel::HalconModel(CString strCross, double fLength, double fWidth, double fPixelSize)
{
	m_strModelType = strCross;
	m_hoImg = HObject();
	//m_hoXldModel赋值
	m_hoXldModelContourAffine = HObject();
	m_hvModelOriginRow = 0;
	m_hvModelOriginColumn = 0;
	m_hvModelScaleMin = DEFAULT_SCALE_MIN;
	m_hvModelScaleMax = DEFAULT_SCALE_MAX;
	m_hvModelMinScore = DEFAULT_MIN_SCORE;
	m_ptMatchDomainPos = CPointF(0, 0);
	m_fMatchDomainSizeFactor = 0;
	m_vPtPosFindedModels.resize(0);

	{
		HObject	ho_Rectangle1, ho_Rectangle2, ho_CrossUnion, ho_CrossUnionCentered;
		HObject	ho_CrossImage, ho_CrossRegion, ho_CrossRegionDilation;
		HTuple hv_CrossImageSideLength, hv_Hom2d;
		HTuple  hv_crossLengthPixel, hv_crossWidthPixel;

		//画cross并生成Contour
		hv_crossLengthPixel = fLength / fPixelSize;
		hv_crossWidthPixel = fWidth / fPixelSize;
		hv_CrossImageSideLength = 10 + (hv_crossLengthPixel > hv_crossWidthPixel) ? hv_crossLengthPixel : hv_crossWidthPixel;

		GenRectangle2ContourXld(&ho_Rectangle1, 0, 0, 0, hv_crossWidthPixel / 2, hv_crossLengthPixel / 2);
		GenRectangle2ContourXld(&ho_Rectangle2, 0, 0, 0, hv_crossLengthPixel / 2, hv_crossWidthPixel / 2);
		Union2ClosedContoursXld(ho_Rectangle1, ho_Rectangle2, &ho_CrossUnion);

		HomMat2dIdentity(&hv_Hom2d);
		HomMat2dTranslate(hv_Hom2d, hv_CrossImageSideLength / 2, hv_CrossImageSideLength / 2, &hv_Hom2d);
		AffineTransContourXld(ho_CrossUnion, &ho_CrossUnionCentered, hv_Hom2d);
		GenImageConst(&ho_CrossImage, "byte", hv_CrossImageSideLength, hv_CrossImageSideLength);
		PaintXld(ho_CrossUnionCentered, ho_CrossImage, &ho_CrossImage, 255);
		Threshold(ho_CrossImage, &ho_CrossRegion, 10, 255);
		DilationRectangle1(ho_CrossRegion, &ho_CrossRegionDilation, 3, 3);
		ReduceDomain(ho_CrossImage, ho_CrossRegionDilation, &m_hoXldModel);

	}
}


void HalconModel::SetScale(double fScaleMin, double fScaleMax)
{
	if (0 >= fScaleMin)
		fScaleMin = 0.1;
	if (0 >= fScaleMax)
		fScaleMin = 0.1;

	if (fScaleMin >= fScaleMax)
	{
		fScaleMin = 1;
		fScaleMax = 1;
	}

	m_hvModelScaleMin = fScaleMin;
	m_hvModelScaleMax = fScaleMax;
}
void HalconModel::SetMinScore(double fMinScore)
{
	if (0 >= fMinScore)
		fMinScore = 0.1;
	else if (1 < fMinScore)
		fMinScore = 1;

	m_hvModelMinScore = fMinScore;
}
void HalconModel::SetMatchDomain(double fPosX, double fPosY, double fPixelSize, double fSizeFactor)
{
	m_ptMatchDomainPos = CPointF(fPosX / fPixelSize, fPosY);

	if (fSizeFactor < 1)
		fSizeFactor = 1;
	m_fMatchDomainSizeFactor = fSizeFactor;

}
