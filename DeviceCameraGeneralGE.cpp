#include "stdafx.h"
#include "DeviceCameraGeneralGE.h"


CDeviceCameraGeneralGE::CDeviceCameraGeneralGE()
{

}

BOOL CDeviceCameraGeneralGE::OpenDevCamera()
{
	if (m_bDevCamOpened)
	{
		//AfxMessageBox(_T("相机已经打开"));
		return TRUE;
	}

	if (!InitHalconCamera())
	{
		AfxMessageBox(_T("相机初始化失败"));
		return FALSE;
	}

	return m_bDevCamOpened = TRUE;
}
BOOL CDeviceCameraGeneralGE::CloseDevCamera()
{
	if (!m_bDevCamOpened)
	{
		//AfxMessageBox(_T("相机已经关闭"));
		return TRUE;
	}

	if (m_bIsAcqImg)
		StopAcqImg();

	try
	{
		CloseFramegrabber(hv_AcqHandle);
	}
	catch (HException & exception)
	{
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		return FALSE;
	}

	m_bDevCamOpened = FALSE;
	return TRUE;

}
BOOL CDeviceCameraGeneralGE::StartAcqImg()
{
	if (!m_bDevCamOpened)
	{
		AfxMessageBox(_T("相机未初始化，无法开始采集"));
		return FALSE;
	}

	//开始采集
	if (!m_bIsAcqImg)
	{
		try
		{
			SetFramegrabberParam(hv_AcqHandle, "grab_timeout", 100);
			GrabImageStart(hv_AcqHandle, -1);
		}
		catch (HException & exception)
		{
			AfxMessageBox((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
			CString strTmp;
			strTmp.Format((HString)exception.ProcName() + (CString)_T("\n") + (HString)exception.ErrorMessage());
			TRACE(strTmp);
			if ((int)exception.ErrorCode() < 0)
				throw exception;
			return FALSE;
		}
		m_bIsAcqImg = TRUE;
		return TRUE;
	}

	return FALSE;
}
BOOL CDeviceCameraGeneralGE::StopAcqImg()
{
	if (!m_bDevCamOpened)
	{
		AfxMessageBox(_T("相机未初始化，无法停止采集"));
		return FALSE;
	}

	//停止采集
	if (m_bIsAcqImg)
	{
		m_bIsAcqImg = FALSE;
		return TRUE;
	}

	return FALSE;
}

HObject CDeviceCameraGeneralGE::GrabImgBySoftCommand()
{
	while (TRUE)
	{
		try
		{
			GrabImageAsync(&ho_Image, hv_AcqHandle, -1);
			return ho_Image;
		}
		catch (HException& exception)
		{
			if ((int)exception.ErrorCode() < 0)
				throw exception;
			continue;
		}
	}

	//try
	//{
	//	//SetCheck("~give error");
	//	GrabImageAsync(&ho_Image, hv_AcqHandle, -1);
	//	//SetCheck("give error");
	//}
	//catch (HException & exception)
	//{
	//	AfxMessageBox(exception.ErrorMessage());
	//	if ((int)exception.ErrorCode() < 0)
	//		throw exception;
	//	return HObject();
	//}

	//return ho_Image;
}


//初始化Halcon图像来源
BOOL CDeviceCameraGeneralGE::InitHalconCamera()
{
	try
	{
		InfoFramegrabber("GigEVision2", "general", &hv_GeneralInfo, &hv_GeneralInfoValues);
		InfoFramegrabber("GigEVision2", "info_boards", &hv_BoardInfo, &hv_BoardInfoValues);
		InfoFramegrabber("GigEVision2", "camera_types", &hv_CameraTypeInfo, &hv_CameraTypeInfoValues);
		InfoFramegrabber("GigEVision2", "defaults", &hv_DefaultInfo, &hv_DefaultInfoValues);
		InfoFramegrabber("GigEVision2", "parameters", &hv_ParameterInfo, &hv_ParameterInfoValues);
		InfoFramegrabber("GigEVision2", "revision", &hv_RevisionInfo, &hv_RevisionValues);
		hv_MyColorSpace = "default";
		hv_MyCameraType = "default";
		hv_MyDevice = "default";
		OpenFramegrabber("GigEVision2", 1, 1, 0, 0, 0, 0, "default", -1, hv_MyColorSpace,
			-1, "false", hv_MyCameraType, hv_MyDevice, -1, -1, &hv_AcqHandle);
		//
		//InfoFramegrabber("GenICamTL", "general", &hv_GeneralInfo, &hv_GeneralInfoValues);
		//InfoFramegrabber("GenICamTL", "info_boards", &hv_BoardInfo, &hv_BoardInfoValues);
		//InfoFramegrabber("GenICamTL", "camera_types", &hv_CameraTypeInfo, &hv_CameraTypeInfoValues);
		//InfoFramegrabber("GenICamTL", "defaults", &hv_DefaultInfo, &hv_DefaultInfoValues);
		//InfoFramegrabber("GenICamTL", "parameters", &hv_ParameterInfo, &hv_ParameterInfoValues);
		//InfoFramegrabber("GenICamTL", "revision", &hv_RevisionInfo, &hv_RevisionValues);
		//OpenFramegrabber("GenICamTL", 0, 0, 0, 0, 0, 0, "progressive", -1, "default", -1,
		//	"false", "default", "MER-500-14GM(00-21-49-00-FC-7E)", 0, -1, &hv_AcqHandle);


		//SetFramegrabberParam(hv_AcqHandle, "grab_timeout", 5000);

		//设置图像显示大小
		//GrabImageStart(hv_AcqHandle, -1);
		//GrabImage(&ho_Image, hv_AcqHandle);
		////GrabImageAsync(&ho_Image, hv_AcqHandle, -1);
		//GetImagePointer1(ho_Image, NULL, NULL, &hv_Width, &hv_Width);//和加载静态图像相同

		//HDevWindowStack::Push(hv_WindowID);
		//SetPart(hv_WindowID, -1, -1, -1, -1);
		//SetPart(hv_WindowID, 0, 0, hv_Width - 1, hv_Width - 1);
	}
	catch (HException & exception)
	{
		//AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		return FALSE;
	}

	return TRUE;
}


//图像参数读写
void CDeviceCameraGeneralGE::SetImgSize(int nImgWidth, int nImgHeight)
{
	SetFramegrabberParam(hv_AcqHandle, "image_width", nImgWidth);
	SetFramegrabberParam(hv_AcqHandle, "image_height", nImgHeight);
}
int CDeviceCameraGeneralGE::GetImgWidth()
{
	HTuple hvImgWidth;
	GetFramegrabberParam(hv_AcqHandle, "image_width", &hvImgWidth);
	return m_nImgWidth = hvImgWidth.I();
}
int CDeviceCameraGeneralGE::GetImgHeight()
{
	HTuple hvImgHeight;
	GetFramegrabberParam(hv_AcqHandle, "image_height", &hvImgHeight);
	return m_nImgHeight = hvImgHeight.I();
}
void CDeviceCameraGeneralGE::SetImgExposure(int nImgExposure)
{
	SetFramegrabberParam(hv_AcqHandle, "ExposureTime", nImgExposure);
}
int CDeviceCameraGeneralGE::GetImgExposure()
{
	HTuple hvImgExposure;
	GetFramegrabberParam(hv_AcqHandle, "ExposureTime", &hvImgExposure);
	return hvImgExposure.I();
}
void CDeviceCameraGeneralGE::SetImgGain(int nImgGain)
{
	SetFramegrabberParam(hv_AcqHandle, "Gain", nImgGain);
}
int CDeviceCameraGeneralGE::GetImgGain()
{
	HTuple hvImgGain;
	GetFramegrabberParam(hv_AcqHandle, "Gain", &hvImgGain);
	return hvImgGain.I();
}
void CDeviceCameraGeneralGE::SetImgMirrorX(int nImgMirrorX)
{
	SetFramegrabberParam(hv_AcqHandle, "ReverseX", nImgMirrorX);
}
int CDeviceCameraGeneralGE::GetImgMirrorX()
{
	HTuple hvImgMirrorX;
	GetFramegrabberParam(hv_AcqHandle, "ReverseX", &hvImgMirrorX);
	return hvImgMirrorX.I();
}
void CDeviceCameraGeneralGE::SetImgMirrorY(int nImgMirrorY)
{
	SetFramegrabberParam(hv_AcqHandle, "ReverseY", nImgMirrorY);
}
int CDeviceCameraGeneralGE::GetImgMirrorY()
{
	HTuple hvImgMirrorY;
	GetFramegrabberParam(hv_AcqHandle, "ReverseY", &hvImgMirrorY);
	return hvImgMirrorY.I();
}
void CDeviceCameraGeneralGE::SetImgContrast(int nImgContrast)
{
	SetFramegrabberParam(hv_AcqHandle, "ExpectedGrayValue", nImgContrast);
}
int CDeviceCameraGeneralGE::GetImgContrast()
{
	HTuple hvImgContrast;
	GetFramegrabberParam(hv_AcqHandle, "ExpectedGrayValue", &hvImgContrast);
	return hvImgContrast.I();
}
