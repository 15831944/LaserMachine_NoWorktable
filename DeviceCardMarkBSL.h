#pragma once
#include "DeviceCardMark.h"
#include "afxwin.h"
#include <vector>
#include "MarkAPI.h"



class CDeviceCardMarkBSL :
	public CDeviceCardMark
{


	// 构造
public:
	CDeviceCardMarkBSL();
	virtual ~CDeviceCardMarkBSL();

	// 特性
public:
	HINSTANCE m_hMarkDll;
	HINSTANCE m_hCalDll;

	CString m_strFileName;	//文件名
	CString m_strDevId;		//设备ID	
	CString m_strCaliName;	//校正文件名	

	CWinThread* m_pThMarkCard;					//加工线程指针
	CWinThread* m_pThRedLgtCard;				//红光线程指针
	CWinThread* m_pThLaserOn;					//加工线程指针
	BSL_MarkByDeviceId m_funcMarkByDeviceId; //线程中调用的BSL标刻函数

	class penPara
	{
	public:
		unsigned int  nPenNo;							//要设置的笔号(0-255)					 
		int      nMarkLoop;								//加工次数
		double   dMarkSpeed;							//标刻次数mm/s
		double   dPowerRatio;							//功率百分比(0-100%)	
		double   dCurrent = 1;							//电流A
		int      nFreq;									//频率HZ
		int      nQPulseWidth;							//Q脉冲宽度us	
		int      nStartTC;								//开始延时us
		int      nLaserOffTC;							//激光关闭延时us 
		int      nEndTC;								//结束延时us
		int      nPolyTC;								//拐角延时us
		
		//跳转参数
		double   dJumpSpeed = 4000;						//跳转速度mm/s
		int      nJumpPosTC;							//跳转位置延时us
		int      nJumpDistTC = 100;						//跳转距离延时us/mm	

		//打点参数
		double   dEndComp = 100;						//末点补偿mm
		//double   dAccDist,//加速距离mm	
		// double   dPointTime,//打点延时 ms

		//矢量打点参数
		bool     bPulsePointMode = false;						//脉冲点模式 
		int      nPulseNum = 1;
		float    POINTTIME = 0;
	};

	// 实现
public:
	virtual BOOL InitialCardMark();
	virtual BOOL StartMarkCardMark();
	virtual BOOL StopMarkCardMark();
	virtual BOOL WaitForThreadsEnded();
	virtual BOOL LaserOn();
	virtual BOOL LaserOff();
	virtual BOOL ShowDlgCali();
	virtual BOOL SetLenRegion(double fWorksize);	//暂用
	virtual BOOL SetScannerXYFlipFlag(int nXYFlip, int nInvertX, int nInvertY);


	//设置加工参数
	virtual BOOL SetPensFromAllLayers(CMachineListContainer* pObjList);
	virtual BOOL SetPenFromDefaultProcParm(UINT nPenNo);

	//图元对象处理，配合父类中的LoadMachineObjList读取加工对象
	virtual BOOL DeleteALLEntities();
	virtual BOOL SaveEntityToFile();
	virtual BOOL AddEntityLines(int nCount, double ptPos[][2], int nPenNo);
	virtual BOOL AddEntityCircle(double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo);
	virtual BOOL AddEntityArc(double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo);


protected:
	//BSLCard
	//标刻线程
	BOOL ApplyCaliFile(BOOL bFlagCaliFile);
	void StartMarkThread();
	void StopMarkThread(CWinThread* pThred);
	static UINT ThreadMarkCard(LPVOID lpParam);

	//激光开光关光
	void StartLaserOn();
	static UINT ThreadLaserOn(LPVOID lpParam);
	BSL_LarseOnPoint m_funcLaserOnPoint;

	BOOL InitialDataFile();	//读取.orzx文件，清空.orzx文件中的图元，写文件名：m_strFileName
	BOOL GetFreshDevlist();	// 获取设备数据并刷新列表，写设备ID：m_strDevId
	BOOL AppendFileToDevice(); //关联文件到设备，即关联m_strFileName到m_strDevId
	BOOL InitialBSLFuncCalledInThread(); //初始化多线程中所需要用到的BSL函数

};

