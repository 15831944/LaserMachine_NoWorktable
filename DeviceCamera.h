#pragma once
#include <afx.h>
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
using namespace HalconCpp;



//纯虚类，相机设备父类
class CDeviceCamera :
	public CObject
{
// 构造
public:
	CDeviceCamera();
	virtual ~CDeviceCamera();

// 特性
protected:


// 实现
public:

	virtual BOOL OpenDevCamera() = 0;					//打开相机，设备初始化
	virtual BOOL CloseDevCamera() = 0;				//关闭相机
	virtual BOOL StartAcqImg() = 0;					//开始采集进程
	virtual BOOL StopAcqImg() = 0;					//停止采集进程
	virtual HObject GrabImgBySoftCommand() = 0;	//软触发采图

	//图像参数读写
	virtual void SetImgSize(int nImgWidth, int nImgHeight) = 0;					//
	virtual int GetImgWidth() = 0;					//
	virtual int GetImgHeight() = 0;					//
	virtual void SetImgMirrorX(int nImgMirrorX) = 0;					//
	virtual int GetImgMirrorX() = 0;					//
	virtual void SetImgMirrorY(int nImgMirrorY) = 0;					//
	virtual int GetImgMirrorY() = 0;					//
	virtual void SetImgExposure(int nImgExposure) = 0;					//
	virtual int GetImgExposure() = 0;					//
	virtual void SetImgGain(int nImgGain) = 0;					//
	virtual int GetImgGain() = 0;					//
	virtual void SetImgContrast(int nImgContrast) = 0;					//
	virtual int GetImgContrast() = 0;					//



	BOOL m_bDevCamOpened = FALSE;			//是否打开
	BOOL m_bIsAcqImg = FALSE;				//是否采集

	int m_nImgWidth;        ///< 原始图像宽
	int m_nImgHeight;       ///< 原始图像高
	//int m_nImgExposure;	//曝光时间
	//int m_nImgGain;		//增益
	//int imgBrightness;	//亮度
	//int imgContrast;	//对比度

};


