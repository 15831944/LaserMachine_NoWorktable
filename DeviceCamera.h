#pragma once
#include <afx.h>
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
using namespace HalconCpp;



//�����࣬����豸����
class CDeviceCamera :
	public CObject
{
// ����
public:
	CDeviceCamera();
	virtual ~CDeviceCamera();

// ����
protected:


// ʵ��
public:

	virtual BOOL OpenDevCamera() = 0;					//��������豸��ʼ��
	virtual BOOL CloseDevCamera() = 0;				//�ر����
	virtual BOOL StartAcqImg() = 0;					//��ʼ�ɼ�����
	virtual BOOL StopAcqImg() = 0;					//ֹͣ�ɼ�����
	virtual HObject GrabImgBySoftCommand() = 0;	//������ͼ

	//ͼ�������д
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



	BOOL m_bDevCamOpened = FALSE;			//�Ƿ��
	BOOL m_bIsAcqImg = FALSE;				//�Ƿ�ɼ�

	int m_nImgWidth;        ///< ԭʼͼ���
	int m_nImgHeight;       ///< ԭʼͼ���
	//int m_nImgExposure;	//�ع�ʱ��
	//int m_nImgGain;		//����
	//int imgBrightness;	//����
	//int imgContrast;	//�Աȶ�

};


