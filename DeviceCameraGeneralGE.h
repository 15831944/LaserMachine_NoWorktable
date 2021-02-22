#pragma once
#include "DeviceCamera.h"
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
using namespace HalconCpp;


class CDeviceCameraGeneralGE :
	public CDeviceCamera
{
	// ����
public:
	CDeviceCameraGeneralGE();
		//virtual ~CDeviceCameraGeneralGE();

	// ����
protected:
	// Local iconic variables
	HObject  ho_Image;

	// Local control variables
	HTuple  hv_GeneralInfo, hv_GeneralInfoValues;
	HTuple  hv_BoardInfo, hv_BoardInfoValues, hv_CameraTypeInfo;
	HTuple  hv_CameraTypeInfoValues, hv_DefaultInfo, hv_DefaultInfoValues;
	HTuple  hv_ParameterInfo, hv_ParameterInfoValues, hv_RevisionInfo;
	HTuple  hv_RevisionValues, hv_MyColorSpace, hv_MyCameraType;
	HTuple  hv_MyDevice, hv_AcqHandle, hv_Width, hv_Height;
	HTuple  hv_WindowID, hv_Seconds1, hv_i, hv_Seconds2, hv_Seconds3;
	HTuple  hv_Seconds4, hv_TimeGrab, hv_TimeSobel, hv_TimeAll;
	HTuple  hv_Overhead;

	
	// ʵ��
public:
	virtual BOOL OpenDevCamera();				//��������豸��ʼ��
	virtual BOOL CloseDevCamera();				//�ر����
	virtual BOOL StartAcqImg();					//��ʼ�ɼ�
	virtual BOOL StopAcqImg();					//ֹͣ�ɼ�
	virtual HObject GrabImgBySoftCommand();			//������ͼ

	//ͼ�������д
	virtual void SetImgSize(int nImgWidth, int nImgHeight);					
	virtual int GetImgWidth();					
	virtual int GetImgHeight();					
	virtual void SetImgMirrorX(int nImgMirrorX);
	virtual int GetImgMirrorX();
	virtual void SetImgMirrorY(int nImgMirrorY);
	virtual int GetImgMirrorY();
	virtual void SetImgExposure(int nImgExposure);				
	virtual int GetImgExposure();					
	virtual void SetImgGain(int nImgGain);				
	virtual int GetImgGain();				
	virtual void SetImgContrast(int nImgContrast);
	virtual int GetImgContrast();

protected:
	BOOL InitHalconCamera();


};

