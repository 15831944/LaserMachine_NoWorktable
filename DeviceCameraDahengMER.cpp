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
	// ����豸�Ѿ�����رգ���֤����ڳ�ʼ��������������ٴδ�
	if (m_bDevCamOpened)
	{
		CloseDevice();
		m_bDevCamOpened = FALSE;
	}

	if (FALSE == OpenDevice())
		return m_bDevCamOpened = FALSE;

	if (FALSE == InitDeviceParam())
	{
		AfxMessageBox(_T("����豸������ʼ��ʧ�ܣ�"));
		return FALSE;
	}

	return TRUE;
}

BOOL CDeviceCameraDahengMER::CloseDevCamera()
{
	// TODO: Add your control notification handler code here
	if (m_bDevCamOpened)
	{
		AfxMessageBox(_T("���δ�򿪣�"));
		return FALSE;
	}

	// ���δͣ������ֹͣ�ɼ�
	if (m_bIsAcqImg)
	{
		if (FALSE == StopAcqImg())
		{
			AfxMessageBox(_T("ֹͣ����ɼ�ʧ�ܣ�"));
			return FALSE;
		}
		m_bIsAcqImg = FALSE;
	}

	//�ر����
	if (FALSE == CloseDevice())
	{
		AfxMessageBox(_T("�ر�����豸ʧ�ܣ�"));
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
		//��������ͨ��
		m_objStreamPtr->StartGrab();
		//���Ϳ�������
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
		//����ͣ������
		m_objFeatureControlPtr->GetCommandFeature("AcquisitionStop")->Execute();
		//�ر�����ͨ��
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
		objImageDataPtr = m_objStreamPtr->GetImage(2000);//��ʱʱ��ʹ��500ms���û����������趨

		if (objImageDataPtr->GetStatus() == GX_FRAME_STATUS_SUCCESS)

		{
			//��ͼ�ɹ�����������֡�����Խ���ͼ����...
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

//ͼ�������д
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


// �����
BOOL CDeviceCameraDahengMER::OpenDevice()
{
	bool bIsDeviceOpen = false;         ///< �豸�Ƿ�򿪱�־
	bool bIsStreamOpen = false;         ///< �豸���Ƿ�򿪱�־

	try
	{
		// ��ʼ���豸��
		IGXFactory::GetInstance().Init();	
		// ö���豸
		GxIAPICPP::gxdeviceinfo_vector vectorDeviceInfo;
		IGXFactory::GetInstance().UpdateDeviceList(1000, vectorDeviceInfo);
		//�ж�ö�ٵ����豸�Ƿ�����㣬��������򵯿���ʾ
		if (vectorDeviceInfo.size() <= 0)
		{
			AfxMessageBox(_T("δ��������豸!"));
			return FALSE;
		}

		//// ����豸�Ѿ�����رգ���֤����ڳ�ʼ��������������ٴδ�
		//if (m_bDevCamOpened)
		//{
		//	m_objStreamPtr->Close();			//�ر�������
		//	m_objDevicePtr->Close();			//�ر��豸
		//	m_bDevCamOpened = false;
		//}

		//���豸
		m_objDevicePtr = IGXFactory::GetInstance().OpenDeviceBySN(vectorDeviceInfo[0].GetSN(), GX_ACCESS_EXCLUSIVE);
		bIsDeviceOpen = true;
		m_objFeatureControlPtr = m_objDevicePtr->GetRemoteFeatureControl();

		//�ж��豸���Ƿ�����㣬��������������
		int nStreamCount = m_objDevicePtr->GetStreamCount();
		if (nStreamCount > 0)
		{
			m_objStreamPtr = m_objDevicePtr->OpenStream(0);
			bIsStreamOpen = true;
		}
		else
		{
			AfxMessageBox(_T("δ�����豸��!"));
			m_objDevicePtr->Close();
			return FALSE;
		}
	}
	catch (CGalaxyException& e)
	{
		//�ж��豸���Ƿ��Ѵ�
		if (bIsStreamOpen)
		{
			m_objStreamPtr->Close();
		}
		//�ж��豸�Ƿ��Ѵ�
		if (bIsDeviceOpen)
		{
			m_objDevicePtr->Close();
		}

		AfxMessageBox((CString)e.what());
		return FALSE;
	}
	return TRUE;
}


// �ر����
BOOL CDeviceCameraDahengMER::CloseDevice()
{
	try
	{
		//�ر�����ɼ�
		m_objStreamPtr->StopGrab();
		//�ر�������
		m_objStreamPtr->Close();
		//�ر��豸
		m_objDevicePtr->Close();
		//����ʼ���ͷ���Դ
		IGXFactory::GetInstance().Uninit();
	}
	catch (CGalaxyException& e)
	{
		AfxMessageBox((CString)e.what());
		return FALSE;
	}

	return TRUE;
}

// ��ʼ���豸��Ĭ�ϲ���
BOOL CDeviceCameraDahengMER::InitDeviceParam()
{
	try
	{
		//��ȡͼ���С�ߴ�
		m_nImgWidth = (int)m_objFeatureControlPtr->GetIntFeature("Width")->GetValue();
		m_nImgHeight = (int)m_objFeatureControlPtr->GetIntFeature("Height")->GetValue();


		//���òɼ�ģʽΪ�����ɼ�ģʽ
		m_objFeatureControlPtr->GetEnumFeature("AcquisitionMode")->SetValue("Continuous");

		//�Ƿ�֧�ִ���ģʽѡ��
		m_bTriggerMode = m_objFeatureControlPtr->IsImplemented("TriggerMode");
		if (m_bTriggerMode)
		{
			//���ô���ģʽ��
			m_objFeatureControlPtr->GetEnumFeature("TriggerMode")->SetValue("Off");
		}

		//�Ƿ�֧�ִ���Դѡ��
		m_bTriggerSource = m_objFeatureControlPtr->IsImplemented("TriggerSource");
		if (m_bTriggerMode)
		{
			//���ô���Դ
			//m_objFeatureControlPtr->GetEnumFeature("TriggerSource")->SetValue("Software");
		}

		//�Ƿ�֧��Bayer��ʽ
		m_bColorFilter = m_objFeatureControlPtr->IsImplemented("PixelColorFilter");

		//�Ƿ�֧�ִ�������ѡ��
		m_bTriggerActive = m_objFeatureControlPtr->IsImplemented("TriggerActivation");

		//�Ƿ�֧���Զ���ƽ��
		m_bBalanceWhiteAuto = m_objFeatureControlPtr->IsImplemented("BalanceWhiteAuto");

		//��ƽ���Ƿ�ɶ�
		bool bBalanceWhiteAutoRead = false;     
		bBalanceWhiteAutoRead = m_objFeatureControlPtr->IsReadable("BalanceWhiteAuto");
		//���֧���ҿɶ������ȡ�豸��ǰ��ƽ��ģʽ
		if (m_bBalanceWhiteAuto)
		{
			if (bBalanceWhiteAutoRead)
			{
				m_strBalanceWhiteAutoMode = m_objFeatureControlPtr->GetEnumFeature("BalanceWhiteAuto")
					->GetValue();
			}
		}

		//�Ƿ�֧���Զ���ƽ��ͨ��ѡ��
		m_bBalanceWhiteRatioSelect = m_objFeatureControlPtr->IsImplemented("BalanceRatioSelector");

		//��ȡ�ع�ʱ�䡢���漰�Զ���ƽ��ϵ�������ֵ����Сֵ
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

