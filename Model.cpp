#include "stdafx.h"
#include "Model.h"
#include "CameraView.h"
#include "MainFrm.h"

ModelBase::ModelBase()
{
	m_hoImg = HObject();
	//m_hoModel = HObject();
	m_hoContourAffine = HObject();

	m_nModelOriginRow = 0;
	m_nModelOriginColumn = 0;
	m_fModelScaleMin = DEFAULT_SCALE_MIN;
	m_fModelScaleMax = DEFAULT_SCALE_MAX;
	m_fModelMinScore = DEFAULT_MIN_SCORE;
	m_ptMatchDomainPos = CPointF(0, 0);
	m_fMatchDomainSizeFactor = 0;
	m_vPtPos.resize(0);

}

int ModelBase::LocateModel(std::vector <CPointF>& vPtPos, BOOL bShowContour, BOOL bShowText)
{
	HObject	hoImageDisplay, hoModel, hoModelContour, hoModelContourAffine, hoMatchRegion;

	HTuple hv_Class, hv_ModelID;
	HTuple hv_ScaleMin, hv_ScaleMax, hv_ModelOriginRow, hv_ModelOriginColumn, hv_MinScore;
	HTuple hv_Row, hv_Column, hv_Angle, hv_Scale, hv_Score, hv_Length;
	HTuple HomMat2D;
	HTuple hv_PosX, hv_PosY, hv_String;
	HTuple hv_ImgWidth, hv_ImgHeight;

	try
	{
		//清空显示
		::SendMessage(GetHwndShow(), WM_SHOW_TEXT, FALSE, NULL);
		::SendMessage(GetHwndShow(), WM_SHOW_CONTOUR, FALSE, NULL);

		//HObject hoReadImg;
		//ReadImage(&hoReadImg, "D://YuanLu//4. Halcon//CCD Sample//xxx.png");
		//SetImage(hoReadImg);
		SetImage();

		hoImageDisplay = m_hoImg;
		hoModel = m_hoModel;
		hv_ScaleMin = m_fModelScaleMin;
		hv_ScaleMax = m_fModelScaleMax;
		hv_MinScore = m_fModelMinScore;
		hv_ModelOriginRow = m_nModelOriginRow;
		hv_ModelOriginColumn = m_nModelOriginColumn;

		GetImageSize(hoImageDisplay, &hv_ImgWidth, &hv_ImgHeight);

		//抓标
		GetObjClass(hoModel, &hv_Class);
		if (hv_Class == HTuple("image"))
		{
			//设置局部抓图参数
			if (CPointF(0, 0) != m_ptMatchDomainPos && 0 != m_fMatchDomainSizeFactor)
			{			
				HTuple hv_RgnRow, hv_RgnCol, hv_RgnWidth, hv_RgnHeight;

				GetImageSize(hoModel, &hv_RgnWidth, &hv_RgnHeight);
				hv_RgnWidth *= m_fMatchDomainSizeFactor;
				hv_RgnHeight *= m_fMatchDomainSizeFactor;
				TransLogicToCamera(&hv_RgnRow, &hv_RgnCol, m_ptMatchDomainPos.x, m_ptMatchDomainPos.y);
				GenRectangle2(&hoMatchRegion, hv_RgnRow, hv_RgnCol, 0, hv_RgnWidth / 2, hv_RgnHeight / 2);
				ReduceDomain(hoImageDisplay, hoMatchRegion, &hoImageDisplay);
			}
			CreateScaledShapeModel(hoModel, "auto", -0.39, 0.79, "auto", hv_ScaleMin, hv_ScaleMax,
				"auto", "auto", "ignore_local_polarity", "auto", "auto", &hv_ModelID);

		}
		else
		{
			if (CPointF(0, 0) != m_ptMatchDomainPos && 0 != m_fMatchDomainSizeFactor)
			{
				HTuple hv_RgnRow, hv_RgnCol, hv_RgnWidth, hv_RgnHeight;
				HTuple hv_RgnRow1, hv_RgnCol1, hv_RgnRow2, hv_RgnCol2;

				//GetImageSize(hoModel, &hv_RgnWidth, &hv_RgnHeight);
				//SmallestRectangle2Xld(hoModel, &hv_RgnRow, &hv_RgnCol, &hv_RgnPhi, &hv_RgnWidth, &hv_RgnHeight);
				SmallestRectangle1Xld(hoModel, &hv_RgnRow1, &hv_RgnCol1, &hv_RgnRow2, &hv_RgnCol2);
				hv_RgnWidth = hv_RgnCol2 - hv_RgnCol1;
				hv_RgnHeight = hv_RgnRow2 - hv_RgnRow1;
				hv_RgnWidth *= m_fMatchDomainSizeFactor;
				hv_RgnHeight *= m_fMatchDomainSizeFactor;
				TransLogicToCamera(&hv_RgnRow, &hv_RgnCol, m_ptMatchDomainPos.x, m_ptMatchDomainPos.y);
				GenRectangle2(&hoMatchRegion, hv_RgnRow, hv_RgnCol, 0, hv_RgnWidth / 2, hv_RgnHeight / 2);
				ReduceDomain(hoImageDisplay, hoMatchRegion, &hoImageDisplay);
			}

			CreateScaledShapeModelXld(hoModel, "auto", -0.39, 0.79, "auto", hv_ScaleMin, hv_ScaleMax,
				"auto", "auto", "ignore_local_polarity", 5, &hv_ModelID);
		}
		SetShapeModelOrigin(hv_ModelID, hv_ModelOriginRow, hv_ModelOriginColumn);
		GetShapeModelContours(&hoModelContour, hv_ModelID, 1);
		FindScaledShapeModel(hoImageDisplay, hv_ModelID, -0.39, 0.79, hv_ScaleMin, hv_ScaleMax, hv_MinScore, 0, 0.1,
			"least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Scale, &hv_Score);
		ClearShapeModel(hv_ModelID);

		//如果没有找到
		TupleLength(hv_Row, &hv_Length);
		if (0 == hv_Length.I())
		{
			vPtPos.clear();
			SetMatchedPos(vPtPos);
			return 0;
		}

		//如果找到一个或多个
		vPtPos.clear();
		GenEmptyObj(&m_hoContourAffine);
		hv_String = HTuple();
		for (HTuple hv_i = 0; hv_i.Continue(hv_Length - 1, 1); hv_i += 1)
		{
			//计算坐标
			TransCameraToLogic(&hv_PosX, &hv_PosY, hv_Row[hv_i], hv_Column[hv_i]);
			//hv_PosX = (hv_Column[hv_i] - hv_ImgWidth / 2) * (HTuple)m_fPixelSize;
			//hv_PosY = (hv_Row[hv_i] - hv_ImgHeight / 2) * (HTuple)m_fPixelSize;
			//hv_PosY = -hv_PosY;

			vPtPos.push_back(CPointF(hv_PosX.D(), hv_PosY.D()));

			//显示信息
			if (bShowText)
			{
				TupleConcat(hv_String, ("X: " + hv_PosX).TupleConcat("Y: " + hv_PosY), &hv_String);
			}
			//显示轮廓图案
			if (bShowContour)
			{
				HomMat2dIdentity(&HomMat2D);
				HomMat2dScale(HomMat2D, hv_Scale[hv_i], hv_Scale[hv_i], 0, 0, &HomMat2D);
				HomMat2dRotate(HomMat2D, hv_Angle[hv_i], 0, 0, &HomMat2D);
				HomMat2dTranslate(HomMat2D, hv_Row[hv_i], hv_Column[hv_i], &HomMat2D);
				AffineTransContourXld(hoModelContour, &hoModelContourAffine, HomMat2D);
				ConcatObj(m_hoContourAffine, hoModelContourAffine, &m_hoContourAffine);
			}
		}


		if (bShowText)
			::SendMessage(GetHwndShow(), WM_SHOW_TEXT, TRUE, (LPARAM)&((hv_String.TupleConcat(hv_Row)).TupleConcat(hv_Column)));

		if (bShowContour)
			::SendMessage(GetHwndShow(), WM_SHOW_CONTOUR, TRUE, (LPARAM)&m_hoContourAffine);

		SetMatchedPos(vPtPos);
		return hv_Length.I();

	}
	catch (HException& exception)
	{
		AfxMessageBox((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		//TRACE((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
	}

	return -1;

}


void ModelBase::SetMatchDomain(CPointF const ptPos, double const fSizeFactor)
{
	m_ptMatchDomainPos = ptPos;
	m_fMatchDomainSizeFactor = fSizeFactor;
}
void ModelBase::GetMatchDomain(CPointF& ptPos, double& fSizeFactor)
{
	ptPos = m_ptMatchDomainPos;
	fSizeFactor = m_fMatchDomainSizeFactor;
}
void ModelBase::SetMatchedPos(std::vector <CPointF> const vPtPos)
{
	m_vPtPos = vPtPos;
}
void ModelBase::GetMatchedPos(std::vector <CPointF>& vPtPos)
{
	vPtPos = m_vPtPos;
}

void  ModelBase::SetImage(HObject const hoImg)
{
	m_hoImg = hoImg;
}

void  ModelBase::SetImage()
{
	HObject hoImg;
	::SendMessage(GetHwndShow(), WM_GET_IMAGE, (WPARAM)&hoImg, NULL);
	m_hoImg = hoImg;
}


HWND ModelBase::GetHwndShow()
{
	CCameraView* pCameraView = (CCameraView*)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter1.GetPane(1, 0);
	return pCameraView->m_pHalconWnd->GetSafeHwnd();
}
void ModelBase::TransLogicToCamera(HTuple* hvRow, HTuple* hvCol, double const fX, double const fY)
{
	HObject hoImg;
	HTuple hv_ImgWidth, hv_ImgHeight, hv_CenterRow, hv_CenterCol;
	HTuple hv_X, hv_Y, hv_Pixel;

	try
	{
		hoImg = m_hoImg;
		hv_Pixel = m_fPixelSize;
		GetImageSize(hoImg, &hv_ImgWidth, &hv_ImgHeight);
		hv_CenterRow = hv_ImgHeight / 2;
		hv_CenterCol = hv_ImgWidth / 2;

		hv_X = fX / hv_Pixel;
		hv_Y = fY / hv_Pixel;
		hv_Y = -hv_Y;

		*hvRow = hv_CenterRow + hv_Y;
		*hvCol = hv_CenterCol + hv_X;
	}
	catch (HException& exception)
	{
		AfxMessageBox((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		//TRACE((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
	}
}
void ModelBase::TransCameraToLogic(double* fX, double* fY, HTuple const hvRow, HTuple const hvCol)
{
	HObject hoImg;
	HTuple hv_ImgWidth, hv_ImgHeight, hv_CenterRow, hv_CenterCol;
	HTuple hv_X, hv_Y, hv_Pixel;

	try
	{
		hoImg = m_hoImg;
		hv_Pixel = m_fPixelSize;
		GetImageSize(hoImg, &hv_ImgWidth, &hv_ImgHeight);
		hv_CenterRow = hv_ImgHeight / 2;
		hv_CenterCol = hv_ImgWidth / 2;

		hv_X = hv_Pixel * (hvCol - hv_CenterCol);
		hv_Y = hv_Pixel * (hvRow - hv_CenterRow);
		hv_Y = -hv_Y;

		*fX = hv_X.D();
		*fY = hv_Y.D();
	}
	catch (HException& exception)
	{
		AfxMessageBox((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		//TRACE((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
	}
}
void ModelBase::TransCameraToLogic(HTuple* hvX, HTuple* hvY, HTuple const hvRow, HTuple const hvCol)
{
	HObject hoImg;
	HTuple hv_ImgWidth, hv_ImgHeight, hv_CenterRow, hv_CenterCol;
	HTuple hv_X, hv_Y, hv_Pixel;

	try
	{
		hoImg = m_hoImg;
		hv_Pixel = m_fPixelSize;
		GetImageSize(hoImg, &hv_ImgWidth, &hv_ImgHeight);
		hv_CenterRow = hv_ImgHeight / 2;
		hv_CenterCol = hv_ImgWidth / 2;

		hv_X = hv_Pixel * (hvCol - hv_CenterCol);
		hv_Y = hv_Pixel * (hvRow - hv_CenterRow);
		hv_Y = -hv_Y;

		*hvX = hv_X;
		*hvY = hv_Y;
	}
	catch (HException& exception)
	{
		AfxMessageBox((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		//TRACE((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
	}
}



/// <summary>
/// ModelCircle类构造函数
/// </summary>
/// <param name="fPixelSize"></param>
/// <param name="fRadius"></param>
/// <returns></returns>
ModelCircle::ModelCircle(double fPixelSize, double fRadius)
{
	m_eModelType = ModelType::MT_Circle;
	m_fPixelSize = fPixelSize;
	m_fRadius = fRadius;

	{
		//生成模板圆图片，如果尺寸不变，就用原图
		HObject ho_ContCircleModel, ho_ContCircleModelCentered, ho_ContCircleModelImage, ho_ContCircleModelRegion, ho_ContCircleModelRegionDilation;
		HTuple hv_CircleRadiusPixel, hv_CircleImageHeight, hv_CircleImageWidth, hv_Hom2d;

		hv_CircleRadiusPixel = m_fRadius / m_fPixelSize;
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
		ReduceDomain(ho_ContCircleModelImage, ho_ContCircleModelRegionDilation, &m_hoModel);
	}

}

/// <summary>
/// ModelCross类构造函数
/// </summary>
/// <param name="fPixelSize"></param>
/// <param name="fLength"></param>
/// <param name="fWidth"></param>
/// <returns></returns>
ModelCross::ModelCross(double fPixelSize, double fLength, double fWidth)
{
	m_eModelType = ModelType::MT_Cross;
	m_fPixelSize = fPixelSize;
	m_fLength = fLength;
	m_fWidth = fWidth;


	{
		HObject	ho_Rectangle1, ho_Rectangle2, ho_CrossUnion, ho_CrossUnionCentered;
		HObject	ho_CrossImage, ho_CrossRegion, ho_CrossRegionDilation;
		HTuple hv_CrossImageSideLength, hv_Hom2d;
		HTuple  hv_crossLengthPixel, hv_crossWidthPixel;

		//画cross并生成Contour
		hv_crossLengthPixel = m_fLength / m_fPixelSize;
		hv_crossWidthPixel = m_fWidth / m_fPixelSize;
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
		ReduceDomain(ho_CrossImage, ho_CrossRegionDilation, &m_hoModel);

	}
}
