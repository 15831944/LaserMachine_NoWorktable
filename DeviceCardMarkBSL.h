#pragma once
#include "DeviceCardMark.h"
#include "afxwin.h"
#include <vector>
#include "MarkAPI.h"



class CDeviceCardMarkBSL :
	public CDeviceCardMark
{


	// ����
public:
	CDeviceCardMarkBSL();
	virtual ~CDeviceCardMarkBSL();

	// ����
public:
	HINSTANCE m_hMarkDll;
	HINSTANCE m_hCalDll;

	CString m_strFileName;	//�ļ���
	CString m_strDevId;		//�豸ID	
	CString m_strCaliName;	//У���ļ���	

	CWinThread* m_pThMarkCard;					//�ӹ��߳�ָ��
	CWinThread* m_pThRedLgtCard;				//����߳�ָ��
	CWinThread* m_pThLaserOn;					//�ӹ��߳�ָ��
	BSL_MarkByDeviceId m_funcMarkByDeviceId; //�߳��е��õ�BSL��̺���

	class penPara
	{
	public:
		unsigned int  nPenNo;							//Ҫ���õıʺ�(0-255)					 
		int      nMarkLoop;								//�ӹ�����
		double   dMarkSpeed;							//��̴���mm/s
		double   dPowerRatio;							//���ʰٷֱ�(0-100%)	
		double   dCurrent = 1;							//����A
		int      nFreq;									//Ƶ��HZ
		int      nQPulseWidth;							//Q������us	
		int      nStartTC;								//��ʼ��ʱus
		int      nLaserOffTC;							//����ر���ʱus 
		int      nEndTC;								//������ʱus
		int      nPolyTC;								//�ս���ʱus
		
		//��ת����
		double   dJumpSpeed = 4000;						//��ת�ٶ�mm/s
		int      nJumpPosTC;							//��תλ����ʱus
		int      nJumpDistTC = 100;						//��ת������ʱus/mm	

		//������
		double   dEndComp = 100;						//ĩ�㲹��mm
		//double   dAccDist,//���پ���mm	
		// double   dPointTime,//�����ʱ ms

		//ʸ��������
		bool     bPulsePointMode = false;						//�����ģʽ 
		int      nPulseNum = 1;
		float    POINTTIME = 0;
	};

	// ʵ��
public:
	virtual BOOL InitialCardMark();
	virtual BOOL StartMarkCardMark();
	virtual BOOL StopMarkCardMark();
	virtual BOOL WaitForThreadsEnded();
	virtual BOOL LaserOn();
	virtual BOOL LaserOff();
	virtual BOOL ShowDlgCali();
	virtual BOOL SetLenRegion(double fWorksize);	//����
	virtual BOOL SetScannerXYFlipFlag(int nXYFlip, int nInvertX, int nInvertY);


	//���üӹ�����
	virtual BOOL SetPensFromAllLayers(CMachineListContainer* pObjList);
	virtual BOOL SetPenFromDefaultProcParm(UINT nPenNo);

	//ͼԪ��������ϸ����е�LoadMachineObjList��ȡ�ӹ�����
	virtual BOOL DeleteALLEntities();
	virtual BOOL SaveEntityToFile();
	virtual BOOL AddEntityLines(int nCount, double ptPos[][2], int nPenNo);
	virtual BOOL AddEntityCircle(double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo);
	virtual BOOL AddEntityArc(double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo);


protected:
	//BSLCard
	//����߳�
	BOOL ApplyCaliFile(BOOL bFlagCaliFile);
	void StartMarkThread();
	void StopMarkThread(CWinThread* pThred);
	static UINT ThreadMarkCard(LPVOID lpParam);

	//���⿪��ع�
	void StartLaserOn();
	static UINT ThreadLaserOn(LPVOID lpParam);
	BSL_LarseOnPoint m_funcLaserOnPoint;

	BOOL InitialDataFile();	//��ȡ.orzx�ļ������.orzx�ļ��е�ͼԪ��д�ļ�����m_strFileName
	BOOL GetFreshDevlist();	// ��ȡ�豸���ݲ�ˢ���б�д�豸ID��m_strDevId
	BOOL AppendFileToDevice(); //�����ļ����豸��������m_strFileName��m_strDevId
	BOOL InitialBSLFuncCalledInThread(); //��ʼ�����߳�������Ҫ�õ���BSL����

};

