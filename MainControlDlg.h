#pragma once

#define ID_TIMEER_WORKTABLE_COORD WM_USER+100
#define ID_TIMEER_PROCESS_TIME WM_USER+101

#include "LaserMachineDoc.h"


// CMainControlDlg 窗体视图

class CMainControlDlg : public CFormView
{
	DECLARE_DYNCREATE(CMainControlDlg)

protected:
	CMainControlDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CMainControlDlg();

public:
	enum { IDD = IDD_MAIN_CONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonStartMark();
	afx_msg void OnBnClickedButtonStopMark();
	afx_msg void OnBnClickedButtonWorktableMoveHome();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();

protected:
	int m_nPosMoveWorktableMode;
	double m_fPosMoveWorktableX, m_fPosMoveWorktableY, m_fPosMoveWorktableZ;
public:
	afx_msg void OnBnClickedButtonPosMoveWorktableBegin();
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButtonPosMoveFromCameraToScanner();
	afx_msg void OnBnClickedButtonPosMoveFromScannerToCamera();
	afx_msg void OnBnClickedButtonLaserOn();
	afx_msg void OnBnClickedButtonLaserOff();
	afx_msg void OnBnClickedButtonMainStartProcess();
	afx_msg void OnBnClickedButtonMainStopProcess();

	//加工进程控制**************************加工进程控制
public:
	BOOL m_bMarkThreadIsRunning;
	void StartMarkThreads();
	void StopMarkThread(CWinThread* pThred);
	void WaitForMarkThreadEnded();
	//ThreadFunc
	static UINT MarkProcRun(LPVOID lpParam);
	//shared data
	CMachineListContainer* m_pListContainer;
	// event handles to synchronize threads
	HANDLE  MarkProcStopEvent;
	// mutexes to guarantee mutual access to shared objects
	CRITICAL_SECTION    ProcObjListMutex;
private:
	CWinThread* m_pThMarkProc;				//线程指针
	//DWORD m_dwThMarkProc;					//线程ID
	long m_lTimeStartProcess;
	HWND m_hwndCameraView;
	//加工进程控制**************************加工进程控制

public:
	afx_msg void OnBnClickedButtonPos();
	afx_msg void OnBnClickedButtontPosMoveWorktableZUp();
	afx_msg void OnBnClickedButtontPosMoveWorktableZDown();
	afx_msg void OnBnClickedButtonProcessTestDxf();
	afx_msg void OnDestroy();
};


