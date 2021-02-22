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
// ����
public:
	CDeviceCameraDahengMER();
	//virtual ~CDeviceCameraDahengMER();

// ����
protected:


// ʵ��
public:
	virtual BOOL OpenDevCamera();				//��������豸��ʼ��
	virtual BOOL CloseDevCamera();				//�ر����
	virtual BOOL StartAcqImg();					//��ʼ�ɼ�
	virtual BOOL StopAcqImg();					//ֹͣ�ɼ�
	virtual HObject GrabImgBySoftCommand();		//������ͼ

	//ͼ�������д
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
	// �����
	BOOL OpenDevice();

	// �ر����
	BOOL CloseDevice();

	// ��ʼ���豸��Ĭ�ϲ���
	BOOL InitDeviceParam();

protected:
	//CGXBitmap* m_pBitmap;                  ///< ����ͼ��ָ��

	CGXDevicePointer                  m_objDevicePtr;             ///< �豸���
	CGXStreamPointer                  m_objStreamPtr;             ///< �豸��
	CGXFeatureControlPointer          m_objFeatureControlPtr;     ///< ���Կ�����
	//CSampleCaptureEventHandler* m_pSampleCaptureEventHandle;///< �ص�����ָ��

	//BOOL                              m_bIsOpen;                  ///< �豸�򿪱�ʶ
	//BOOL                              m_bIsSnap;                  ///< �豸�ɼ���ʶ
	bool                              m_bColorFilter;             ///< �Ƿ�֧�ֲ�ɫ���
	bool                              m_bTriggerMode;             ///< �Ƿ�֧�ִ���ģʽ
	bool                              m_bTriggerSource;           ///< �Ƿ�֧�ִ���Դ
	bool                              m_bTriggerActive;           ///< �Ƿ�֧�ִ�������
	bool                              m_bBalanceWhiteAuto;        ///< �Ƿ�֧���Զ���ƽ��
	bool                              m_bBalanceWhiteRatioSelect; ///< �Ƿ�֧�ְ�ƽ��ͨ��ѡ��
	double                            m_dShutterValueMax;         ///< �ع�ʱ�����ֵ      
	double                            m_dShutterValueMin;         ///< �ع�ʱ����Сֵ     
	double                            m_dGainValueMax;            ///< �������ֵ
	double                            m_dGainValueMin;            ///< ������Сֵ
	double                            m_dBalanceWhiteRatioMax;    ///< �Զ���ƽ��ϵ�����ֵ
	double                            m_dBalanceWhiteRatioMin;    ///< �Զ���ƽ��ϵ����Сֵ
	int                               m_nTriggerModeOld;          ///< ��¼����ģʽ
	int                               m_nTriggerSourceOld;        ///< ��¼����Դ
	int                               m_nTriggerActiveOld;        ///< ��¼��������
	int                               m_nBalanceWhiteAutoOld;     ///< ��¼�Զ���ƽ��
	int                               m_nBanlanceWhiteRatioOld;   ///< ��¼�Զ���ƽ��ϵ��
	gxstring                          m_strBalanceWhiteAutoMode;  ///< ��¼�Զ���ƽ�ⷽʽ

};

////---------------------------------------------------------------------------------
///**
//\brief   �û��̳вɼ��¼�������
//*/
////----------------------------------------------------------------------------------
//class CSampleCaptureEventHandler :public ICaptureEventHandler
//{
//	//---------------------------------------------------------------------------------
//	/**
//	\brief   �ɼ��ص�����
//	\param   objImageDataPointer      ͼ�������
//	\param   pFrame                   �û�����
//
//	\return  ��
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
//			////��ʾͼ��
//			//pDevCameDahengMER->m_pBitmap->Show(objImageDataPointer);
//
//			////�ж��Ƿ���Ҫ����ͼ��
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
