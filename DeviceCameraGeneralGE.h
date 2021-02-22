#pragma once
#include "DeviceCamera.h"
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
using namespace HalconCpp;


class CDeviceCameraGeneralGE :
	public CDeviceCamera
{
	// 构造
public:
	CDeviceCameraGeneralGE();
		//virtual ~CDeviceCameraGeneralGE();

	// 特性
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

	
	// 实现
public:
	virtual BOOL OpenDevCamera();				//打开相机，设备初始化
	virtual BOOL CloseDevCamera();				//关闭相机
	virtual BOOL StartAcqImg();					//开始采集
	virtual BOOL StopAcqImg();					//停止采集
	virtual HObject GrabImgBySoftCommand();			//软触发采图

	//图像参数读写
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

