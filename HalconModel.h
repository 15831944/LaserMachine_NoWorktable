#pragma once

#include <cstring>
#include <vector>
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
using namespace HalconCpp;


class HalconModel
{
public:
	HalconModel()
	{
		strModelType = CString();
		hoImg = HObject();
		hoXldModel = HObject();
		hoXldModelContourAffine = HObject();
		hvModelOriginRow = 0;
		hvModelOriginColumn = 0;
		hvModelScaleMin = 0.9;
		hvModelScaleMax = 1.1;
		hvModelMinScore = 0.7;
	};
	HalconModel(CString strCircle, double fRadius, double fPixelSize, double fScaleMin, double fScaleMax, double fMinScore)
	{
		strModelType = strCircle;
		hoImg = HObject();
		//GenCircleContourXld(&hoXldModel, 0, 0, fRadius / fPixelSize, 0, 6.28318, "positive", 1);
		hoXldModelContourAffine = HObject();
		hvModelOriginRow = 0;
		hvModelOriginColumn = 0;
		hvModelScaleMin = fScaleMin;
		hvModelScaleMax = fScaleMax;
		hvModelMinScore = fMinScore;

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
			ReduceDomain(ho_ContCircleModelImage, ho_ContCircleModelRegionDilation, &hoXldModel);
		}

	}

	CString strModelType;
	HObject hoImg;							//抓标时的相机图片
	HObject hoXldModel;						//抓标模板，可能是Image或contour
	HObject hoXldModelContourAffine;		//抓标结果contour
	HTuple hvModelOriginRow;
	HTuple hvModelOriginColumn;
	HTuple hvModelScaleMin;
	HTuple hvModelScaleMax;
	HTuple hvModelMinScore;

};

