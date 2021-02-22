#pragma once
#include "DeviceCamera.h"
//#include "GxIAPI.h"
//#include "DxImageProc.h"
#include "GalaxyIncludes.h"
//#include "GXBitmap.h"
#include <vector>


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CDeviceCameraDahengMER :
	public CDeviceCamera
{
// 构造
public:
	CDeviceCameraDahengMER();
	//virtual ~CDeviceCameraDahengMER();

// 特性
protected:


// 实现
public:
	virtual BOOL OpenDevCamera();				//打开相机，设备初始化
	virtual BOOL CloseDevCamera();				//关闭相机
	virtual BOOL StartAcqImg();					//开始采集
	virtual BOOL StopAcqImg();					//停止采集
	virtual HObject GrabImgBySoftCommand();		//软触发采图

	//图像参数读写
	virtual void SetImgSize(int nImgWidth, int nImgHeight);					//
	virtual int GetImgWidth();					//
	virtual int GetImgHeight();					//
	virtual void SetImgExposure(int nImgExposure);					//
	virtual int GetImgExposure();					//
	virtual void SetImgGain(int nImgGain);					//
	virtual int GetImgGain();					//
	virtual void SetImgMirrorX(int nImgMirrorX);
	virtual int GetImgMirrorX();
	virtual void SetImgMirrorY(int nImgMirrorY);
	virtual int GetImgMirrorY();
	virtual void SetImgContrast(int nImgContrast);
	virtual int GetImgContrast();


	//Daheng
protected:
	// 打开相机
	BOOL OpenDevice();

	// 关闭相机
	BOOL CloseDevice();

	// 初始化设备的默认参数
	BOOL InitDeviceParam();

protected:
	//CGXBitmap* m_pBitmap;                  ///< 保存图像指针

	CGXDevicePointer                  m_objDevicePtr;             ///< 设备句柄
	CGXStreamPointer                  m_objStreamPtr;             ///< 设备流
	CGXFeatureControlPointer          m_objFeatureControlPtr;     ///< 属性控制器
	//CSampleCaptureEventHandler* m_pSampleCaptureEventHandle;///< 回调函数指针

	//BOOL                              m_bIsOpen;                  ///< 设备打开标识
	//BOOL                              m_bIsSnap;                  ///< 设备采集标识
	bool                              m_bColorFilter;             ///< 是否支持彩色相机
	bool                              m_bTriggerMode;             ///< 是否支持触发模式
	bool                              m_bTriggerSource;           ///< 是否支持触发源
	bool                              m_bTriggerActive;           ///< 是否支持触发极性
	bool                              m_bBalanceWhiteAuto;        ///< 是否支持自动白平衡
	bool                              m_bBalanceWhiteRatioSelect; ///< 是否支持白平衡通道选择
	double                            m_dShutterValueMax;         ///< 曝光时间最大值      
	double                            m_dShutterValueMin;         ///< 曝光时间最小值     
	double                            m_dGainValueMax;            ///< 增益最大值
	double                            m_dGainValueMin;            ///< 增益最小值
	double                            m_dBalanceWhiteRatioMax;    ///< 自动白平衡系数最大值
	double                            m_dBalanceWhiteRatioMin;    ///< 自动白平衡系数最小值
	int                               m_nTriggerModeOld;          ///< 记录触发模式
	int                               m_nTriggerSourceOld;        ///< 记录触发源
	int                               m_nTriggerActiveOld;        ///< 记录触发极性
	int                               m_nBalanceWhiteAutoOld;     ///< 记录自动白平衡
	int                               m_nBanlanceWhiteRatioOld;   ///< 记录自动白平衡系数
	gxstring                          m_strBalanceWhiteAutoMode;  ///< 记录自动白平衡方式

};

////---------------------------------------------------------------------------------
///**
//\brief   用户继承采集事件处理类
//*/
////----------------------------------------------------------------------------------
//class CSampleCaptureEventHandler :public ICaptureEventHandler
//{
//	//---------------------------------------------------------------------------------
//	/**
//	\brief   采集回调函数
//	\param   objImageDataPointer      图像处理参数
//	\param   pFrame                   用户参数
//
//	\return  无
//	*/
//	//----------------------------------------------------------------------------------
//	void DoOnImageCaptured(CImageDataPointer& objImageDataPointer, void* pUserParam)
//	{
//		try
//		{
//			CDeviceCameraDahengMER* pDevCameDahengMER = (CDeviceCameraDahengMER*)pUserParam;
//
//			GX_PIXEL_FORMAT_ENTRY emPixelFormat = objImageDataPointer->GetPixelFormat();
//			void* pImgBuffer = objImageDataPointer->GetBuffer();
//			pDevCameDahengMER->m_nImageWidth = objImageDataPointer->GetWidth();
//			pDevCameDahengMER->m_nImageHeight = objImageDataPointer->GetHeight();
//
//			//GenImage1(&pDevCameDahengMER->m_hoImg, "byte", pDevCameDahengMER->m_nImageWidth, pDevCameDahengMER->m_nImageHeight, (Hlong)pImgBuffer);
//
//			//GenImage1Extern(&ho_Img, "byte", (HTuple)m_stFrameData.nWidth, (HTuple)m_stFrameData.nHeight, (Hlong)m_stFrameData.pImgBuf, 0);
//
//			////显示图像
//			//pDevCameDahengMER->m_pBitmap->Show(objImageDataPointer);
//
//			////判断是否需要保存图像
//			//if (pSingleCamDlg->m_bCheckSaveBmp == TRUE)
//			//{
//			//	pSingleCamDlg->SavePicture(objImageDataPointer);
//			//}
//		}
//		catch (CGalaxyException)
//		{
//			//do nothing
//
//		}
//		catch (std::exception)
//		{
//			//do nothing
//
//		}
//	}
//};
