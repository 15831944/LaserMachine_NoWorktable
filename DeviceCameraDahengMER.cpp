#include "stdafx.h"
#include "DeviceCameraDahengMER.h"

CDeviceCameraDahengMER::CDeviceCameraDahengMER()

{
	//m_pSampleCaptureEventHandle = NULL;
	//m_pBitmap(NULL)
	m_bDevCamOpened = FALSE;
	m_bIsAcqImg = FALSE;
	m_bColorFilter = false;
	m_bTriggerMode = false;
	m_bTriggerSource = false;
	m_bTriggerActive = false;
	m_bBalanceWhiteAuto = false;
	m_bBalanceWhiteRatioSelect = false;
	m_nTriggerModeOld = 0;
	m_nTriggerSourceOld = 0;
	m_nTriggerActiveOld = 0;
	m_nBalanceWhiteAutoOld = 0;
	m_nBanlanceWhiteRatioOld = 0;
	m_dShutterValueMax = 0;
	m_dShutterValueMin = 0;
	m_dGainValueMax = 0;
	m_dGainValueMin = 0;
	m_dBalanceWhiteRatioMax = 0;
	m_dBalanceWhiteRatioMin = 0;
	m_strBalanceWhiteAutoMode = "Off";
}

//CDeviceCameraDahengMER:: ~CDeviceCameraDahengMER()
//{
//
//}


BOOL CDeviceCameraDahengMER::OpenDevCamera()
{
	// 如果设备已经打开则关闭，保证相机在初始化出错情况下能再次打开
	if (m_bDevCamOpened)
	{
		CloseDevice();
		m_bDevCamOpened = FALSE;
	}

	if (FALSE == OpenDevice())
		return m_bDevCamOpened = FALSE;

	if (FALSE == InitDeviceParam())
	{
		AfxMessageBox(_T("相机设备参数初始化失败！"));
		return FALSE;
	}

	return TRUE;
}

BOOL CDeviceCameraDahengMER::CloseDevCamera()
{
	// TODO: Add your control notification handler code here
	if (m_bDevCamOpened)
	{
		AfxMessageBox(_T("相机未打开！"));
		return FALSE;
	}

	// 如果未停采则先停止采集
	if (m_bIsAcqImg)
	{
		if (FALSE == StopAcqImg())
		{
			AfxMessageBox(_T("停止相机采集失败！"));
			return FALSE;
		}
		m_bIsAcqImg = FALSE;
	}

	//关闭相机
	if (FALSE == CloseDevice())
	{
		AfxMessageBox(_T("关闭相机设备失败！"));
		return FALSE;
	}

	m_bDevCamOpened = FALSE;
	m_bIsAcqImg = FALSE;
	return TRUE;
}

BOOL CDeviceCameraDahengMER::StartAcqImg()
{
	// TODO: Add your control notification handler code here
	try
	{
		//开启流层通道
		m_objStreamPtr->StartGrab();
		//发送开采命令
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStart")->Execute();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
		return FALSE;
	}

	m_bIsAcqImg = TRUE;
	return TRUE;
}

BOOL CDeviceCameraDahengMER::StopAcqImg()
{
	// TODO: Add your control notification handler code here
	try
	{
		//发送停采命令
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
		//关闭流层通道
		m_objStreamPtr->StopGrab();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
		return FALSE;
	}
	m_bIsAcqImg = FALSE;
	return TRUE;
}

HObject CDeviceCameraDahengMER::GrabImgBySoftCommand()
{
	// TODO: Add your control notification handler code here
	HObject hoImg;

	try
	{
		CImageDataPointer objImageDataPtr;
		objImageDataPtr = m_objStreamPtr->GetImage(2000);//超时时间使用500ms，用户可以自行设定

		if (objImageDataPtr->GetStatus() == GX_FRAME_STATUS_SUCCESS)

		{
			//采图成功而且是完整帧，可以进行图像处理...
			GenImage1(&hoImg, "byte", (HTuple)(int)objImageDataPtr->GetWidth(), (HTuple)(int)objImageDataPtr->GetHeight(), (Hlong)objImageDataPtr->GetBuffer());
		}
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
		return HObject();
	}
	return hoImg;
}

//图像参数读写
void CDeviceCameraDahengMER::SetImgSize(int nImgWidth, int nImgHeight)
{

}
int CDeviceCameraDahengMER::GetImgWidth()
{
	return m_nImgWidth;
}
int CDeviceCameraDahengMER::GetImgHeight()
{
	return m_nImgHeight;
}
void CDeviceCameraDahengMER::SetImgExposure(int nImgExposure)
{
	if (nImgExposure < (int)m_dShutterValueMin)
		nImgExposure = (int)m_dShutterValueMin;
	if (nImgExposure > (int)m_dShutterValueMax)
		nImgExposure = (int)m_dShutterValueMax;

	try
	{
		m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->SetValue((double)nImgExposure);
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}
}
int CDeviceCameraDahengMER::GetImgExposure()
{
	int nImgExposure = 0;
	try
	{
		nImgExposure = (int)m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetValue();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}

	return nImgExposure;
}
void CDeviceCameraDahengMER::SetImgGain(int nImgGain)
{
	try
	{
		m_objFeatureControlPtr->GetFloatFeature("Gain")->SetValue((double)nImgGain);
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}
}
int CDeviceCameraDahengMER::GetImgGain()
{
	int nImgGain = 0;
	try
	{
		nImgGain = (int)m_objFeatureControlPtr->GetFloatFeature("Gain")->GetValue();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}

	return nImgGain;
}
void CDeviceCameraDahengMER::SetImgMirrorX(int nImgMirrorX)
{
	try
	{
		m_objFeatureControlPtr->GetBoolFeature("ReverseX")->SetValue((bool)nImgMirrorX);
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}
}
int CDeviceCameraDahengMER::GetImgMirrorX()
{
	BOOL bImgReverseX = 0;
	try
	{
		bImgReverseX = m_objFeatureControlPtr->GetBoolFeature("ReverseX")->GetValue();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}

	if (bImgReverseX)
		return 1;
	else
		return 0;
}
void CDeviceCameraDahengMER::SetImgMirrorY(int nImgMirrorY)
{
	try
	{
		m_objFeatureControlPtr->GetBoolFeature("ReverseY")->SetValue((bool)nImgMirrorY);
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}
}
int CDeviceCameraDahengMER::GetImgMirrorY()
{
	BOOL bImgReverseY = 0;
	try
	{
		bImgReverseY = m_objFeatureControlPtr->GetBoolFeature("ReverseY")->GetValue();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
	}

	if (bImgReverseY)
		return 1;
	else
		return 0;
}
void CDeviceCameraDahengMER::SetImgContrast(int nImgContrast)
{

}
int CDeviceCameraDahengMER::GetImgContrast()
{
	return 0;
}


// 打开相机
BOOL CDeviceCameraDahengMER::OpenDevice()
{
	bool bIsDeviceOpen = false;         ///< 设备是否打开标志
	bool bIsStreamOpen = false;         ///< 设备流是否打开标志

	try
	{
		// 初始化设备库
		IGXFactory::GetInstance().Init();	
		// 枚举设备
		GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;
		IGXFactory::GetInstance().UpdateDeviceList(1000, vectorDeviceInfo);
		//判断枚举到的设备是否大于零，如果不是则弹框提示
		if (vectorDeviceInfo.size() <= 0)
		{
			AfxMessageBox(_T("未发现相机设备!"));
			return FALSE;
		}

		//// 如果设备已经打开则关闭，保证相机在初始化出错情况下能再次打开
		//if (m_bDevCamOpened)
		//{
		//	m_objStreamPtr->Close();			//关闭流对象
		//	m_objDevicePtr->Close();			//关闭设备
		//	m_bDevCamOpened = false;
		//}

		//打开设备
		m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(vectorDeviceInfo[0].GetSN(), GX_ACCESS_EXCLUSIVE);
		bIsDeviceOpen = true;
		m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

		//判断设备流是否大于零，如果大于零则打开流
		int nStreamCount = m_objDevicePtr->GetStreamCount();
		if (nStreamCount > 0)
		{
			m_objStreamPtr = m_objDevicePtr->OpenStream(0);
			bIsStreamOpen = true;
		}
		else
		{
			AfxMessageBox(_T("未发现设备流!"));
			m_objDevicePtr->Close();
			return FALSE;
		}
	}
	catch (CGalaxyException& e)
	{
		//判断设备流是否已打开
		if (bIsStreamOpen)
		{
			m_objStreamPtr->Close();
		}
		//判断设备是否已打开
		if (bIsDeviceOpen)
		{
			m_objDevicePtr->Close();
		}

		AfxMessageBox((CString)e.what());
		return FALSE;
	}
	return TRUE;
}


// 关闭相机
BOOL CDeviceCameraDahengMER::CloseDevice()
{
	try
	{
		//关闭流层采集
		m_objStreamPtr->StopGrab();
		//关闭流对象
		m_objStreamPtr->Close();
		//关闭设备
		m_objDevicePtr->Close();
		//反初始化释放资源
		IGXFactory::GetInstance().Uninit();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
		return FALSE;
	}

	return TRUE;
}

// 初始化设备的默认参数
BOOL CDeviceCameraDahengMER::InitDeviceParam()
{
	try
	{
		//获取图像大小尺寸
		m_nImgWidth = (int)m_objFeatureControlPtr->GetIntFeature("Width")->GetValue();
		m_nImgHeight = (int)m_objFeatureControlPtr->GetIntFeature("Height")->GetValue();


		//设置采集模式为连续采集模式
		m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");

		//是否支持触发模式选择
		m_bTriggerMode = m_objFeatureControlPtr->IsImplemented("TriggerMode");
		if (m_bTriggerMode)
		{
			//设置触发模式开
			m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");
		}

		//是否支持触发源选择
		m_bTriggerSource = m_objFeatureControlPtr->IsImplemented("TriggerSource");
		if (m_bTriggerMode)
		{
			//设置触发源
			//m_objFeatureControlPtr->GetEnumFeature("TriggerSource")->SetValue("Software");
		}

		//是否支持Bayer格式
		m_bColorFilter = m_objFeatureControlPtr->IsImplemented("PixelColorFilter");

		//是否支持触发极性选择
		m_bTriggerActive = m_objFeatureControlPtr->IsImplemented("TriggerActivation");

		//是否支持自动白平衡
		m_bBalanceWhiteAuto = m_objFeatureControlPtr->IsImplemented("BalanceWhiteAuto");

		//白平衡是否可读
		bool bBalanceWhiteAutoRead = false;     
		bBalanceWhiteAutoRead = m_objFeatureControlPtr->IsReadable("BalanceWhiteAuto");
		//如果支持且可读，则获取设备当前白平衡模式
		if (m_bBalanceWhiteAuto)
		{
			if (bBalanceWhiteAutoRead)
			{
				m_strBalanceWhiteAutoMode = m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")
					->GetValue();
			}
		}

		//是否支持自动白平衡通道选择
		m_bBalanceWhiteRatioSelect = m_objFeatureControlPtr->IsImplemented("BalanceRatioSelector");

		//获取曝光时间、增益及自动白平衡系数的最大值和最小值
		m_dShutterValueMax = m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetMax();
		m_dShutterValueMin = m_objFeatureControlPtr->GetFloatFeature("ExposureTime")->GetMin();
		m_dGainValueMax = m_objFeatureControlPtr->GetFloatFeature("Gain")->GetMax();
		m_dGainValueMin = m_objFeatureControlPtr->GetFloatFeature("Gain")->GetMin();
		m_dBalanceWhiteRatioMax = m_objFeatureControlPtr->GetFloatFeature("BalanceRatio")->GetMax();
		m_dBalanceWhiteRatioMin = m_objFeatureControlPtr->GetFloatFeature("BalanceRatio")->GetMin();

	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
		return FALSE;
	}
	return TRUE;
}

