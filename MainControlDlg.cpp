// MainControlDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "LaserMachine.h"
#include "MainControlDlg.h"
#include "MainFrm.h"
#include "DeviceCardMark.h"
#include "DeviceCardMarkBSL.h"

#include "DeviceCardWorktable.h"
#include "CDlgDevCfgTabCamera.h"
#include "PreProcess.h"
#include "XSleep.h"
#include "CameraPosition.h"
#include "math.h"
#include "CameraView.h"
#include "CDlgSetParaGrid.h"


// 添加MessageBoxTimeout支持
extern "C"
{
	int WINAPI MessageBoxTimeoutA(IN HWND hWnd, IN LPCSTR lpText, IN LPCSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
	int WINAPI MessageBoxTimeoutW(IN HWND hWnd, IN LPCWSTR lpText, IN LPCWSTR lpCaption, IN UINT uType, IN WORD wLanguageId, IN DWORD dwMilliseconds);
};
#ifdef UNICODE
#define MessageBoxTimeout MessageBoxTimeoutW
#else
#define MessageBoxTimeout MessageBoxTimeoutA
#endif



// CMainControlDlg

IMPLEMENT_DYNCREATE(CMainControlDlg, CFormView)

CMainControlDlg::CMainControlDlg()
	: CFormView(CMainControlDlg::IDD)
	, m_fPosMoveWorktableX(0)
	, m_fPosMoveWorktableY(0)
	, m_fPosMoveWorktableZ(0)
{
	
}

CMainControlDlg::~CMainControlDlg()
{

}

void CMainControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_CBIndex(pDX, IDC_COMBO_POS_MOVE_WORKTABLE_MODE, m_nPosMoveWorktableMode);
	DDX_Text(pDX, IDC_EDIT_POS_MOVE_WORKTABLE_X, m_fPosMoveWorktableX);
	DDX_Text(pDX, IDC_EDIT_POS_MOVE_WORKTABLE_Y, m_fPosMoveWorktableY);
	DDX_Text(pDX, IDC_EDIT_POS_MOVE_WORKTABLE_Z_UNIT, m_fPosMoveWorktableZ);
}

BEGIN_MESSAGE_MAP(CMainControlDlg, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_START_MARK, &CMainControlDlg::OnBnClickedButtonStartMark)
	ON_BN_CLICKED(IDC_BUTTON_STOP_MARK, &CMainControlDlg::OnBnClickedButtonStopMark)
	ON_BN_CLICKED(IDC_BUTTON_START_MARK, &CMainControlDlg::OnBnClickedButtonStartMark)
	ON_BN_CLICKED(IDC_BUTTON_WORKTABLE_MOVE_HOME, &CMainControlDlg::OnBnClickedButtonWorktableMoveHome)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_POS_MOVE_WORKTABLE_BEGIN, &CMainControlDlg::OnBnClickedButtonPosMoveWorktableBegin)
	ON_BN_CLICKED(IDC_BUTTON_POS_MOVE_FROM_CAMERA_TO_SCANNER, &CMainControlDlg::OnBnClickedButtonPosMoveFromCameraToScanner)
	ON_BN_CLICKED(IDC_BUTTON_POS_MOVE_FROM_SCANNER_TO_CAMERA, &CMainControlDlg::OnBnClickedButtonPosMoveFromScannerToCamera)
	ON_BN_CLICKED(IDC_BUTTON_LASER_ON, &CMainControlDlg::OnBnClickedButtonLaserOn)
	ON_BN_CLICKED(IDC_BUTTON_LASER_OFF, &CMainControlDlg::OnBnClickedButtonLaserOff)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_START_PROCESS, &CMainControlDlg::OnBnClickedButtonMainStartProcess)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_STOP_PROCESS, &CMainControlDlg::OnBnClickedButtonMainStopProcess)
	ON_BN_CLICKED(IDC_BUTTON_POS__RESET, &CMainControlDlg::OnBnClickedButtonPos)
	ON_BN_CLICKED(IDC_BUTTONT_POS_MOVE_WORKTABLE_Z_UP, &CMainControlDlg::OnBnClickedButtontPosMoveWorktableZUp)
	ON_BN_CLICKED(IDC_BUTTONT_POS_MOVE_WORKTABLE_Z_DOWN, &CMainControlDlg::OnBnClickedButtontPosMoveWorktableZDown)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS_TEST_DXF, &CMainControlDlg::OnBnClickedButtonProcessTestDxf)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMainControlDlg 诊断

#ifdef _DEBUG
void CMainControlDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainControlDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainControlDlg 消息处理程序


void CMainControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	//试图调整主控窗口尺寸，则向上级发送消息，用于锁定本对话框尺寸
	GetParentFrame()->SendMessage(WM_CtrlWindows_Size, NULL, NULL);
}


void CMainControlDlg::OnBnClickedButtonStartMark()
{
	// TODO: 在此添加控件通知处理程序代码

	if (NULL == pDevCardMark)
	{
		AfxMessageBox(_T("打标卡未初始化"));
		return;
	}
	
	CLaserMachineDoc* pDoc = (CLaserMachineDoc*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CMachineListContainer* pListContainerTmp = pDoc->m_pLaserObjList;
	pDevCardMark->LoadMachineObjList(pListContainerTmp);

	//double ptPos[][2] = { {50,0}, {-50, 0}, {0, 50}, {50,0} };
	//theApp.pDevCardMark->AddEntityCircle(ptCenter, 50, 0, 0);
	//double ptCenter[2] = { 0, 0 };
	//theApp.pDevCardMark->AddEntityLines(4, ptPos);
	//theApp.pDevCardMark->AddEntityLines(2, ptPos);

	pDevCardMark->StartMarkCardMark();
	pDevCardMark->WaitForThreadsEnded();
	MessageBoxTimeout(NULL, _T("标刻完成"), _T("提示"), MB_OK, 0, 1000);

}


void CMainControlDlg::OnBnClickedButtonStopMark()
{
	// TODO: 在此添加控件通知处理程序代码

	if (NULL == pDevCardMark)
	{
		//AfxMessageBox(_T("打标卡未初始化"));
		return;
	}

	pDevCardMark->StopMarkCardMark();

}

void CMainControlDlg::OnBnClickedButtonWorktableMoveHome()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardWorktable)
		return;
	pDevCardWorktable->HomeMoveXY(-1, -1);
}

BOOL CMainControlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (NULL == pDevCardWorktable)
		return CFormView::PreTranslateMessage(pMsg);

	static WPARAM wparamLastKey = -1;
	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_LEFT)->m_hWnd)
		{
			pDevCardWorktable->JogMoveX(1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_RIGHT)->m_hWnd)
		{
			pDevCardWorktable->JogMoveX(-1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_DOWN)->m_hWnd)
		{
			pDevCardWorktable->JogMoveY(1);
		}
		else if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_UP)->m_hWnd)
		{
			pDevCardWorktable->JogMoveY(-1);
		}
		break;
	case WM_LBUTTONUP:
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_LEFT)->m_hWnd
			|| pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_RIGHT)->m_hWnd
			|| pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_DOWN)->m_hWnd
			|| pMsg->hwnd == GetDlgItem(IDC_BUTTON_WORKTABLE_MOVE_UP)->m_hWnd)
		{
			pDevCardWorktable->StopMoveXY(TRUE);
		}
		break;
	case WM_KEYDOWN:
		if (pMsg->wParam == wparamLastKey)
			break;
		wparamLastKey = pMsg->wParam;
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			pDevCardWorktable->JogMoveX(1);
			break;
		case VK_RIGHT:
			pDevCardWorktable->JogMoveX(-1);
			break;
		case VK_DOWN:
			pDevCardWorktable->JogMoveY(1);
			break;
		case VK_UP:
			pDevCardWorktable->JogMoveY(-1);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		wparamLastKey = -1;
		if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
		{
			pDevCardWorktable->StopMoveX(TRUE);
		}
		else if (pMsg->wParam == VK_DOWN || pMsg->wParam == VK_UP)
		{
			pDevCardWorktable->StopMoveY(TRUE);
		}
		break;
	default:
		break;
	}

	return CFormView::PreTranslateMessage(pMsg);
}

void CMainControlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMainFrame* pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CString strCoordinate, strTime;
	switch (nIDEvent)
	{
	case ID_TIMEER_WORKTABLE_COORD:
		if (NULL == pDevCardWorktable)
			break;

		double fCurAbsPosX, fCurAbsPosY, fCurAbsPosZ;
		pDevCardWorktable->GetAbsPosXY(&fCurAbsPosX, &fCurAbsPosY);
		pDevCardWorktable->GetAbsPosZ(&fCurAbsPosZ);
		strCoordinate.Format(_T("平台坐标: %.3f, %.3f, %.3f"), fCurAbsPosX, fCurAbsPosY, fCurAbsPosZ);
		pFrame->m_wndStatusBar.SetPaneText(1, strCoordinate);
		break;
	case ID_TIMEER_PROCESS_TIME:
		long lTimeCount, lTimeHrs, lTimeMins, lTimeSnds;
		lTimeCount = GetTickCount();
		lTimeSnds = (lTimeCount - m_lTimeStartProcess) / 1000;
		lTimeMins = lTimeSnds / 60;
		lTimeHrs = lTimeMins / 60;
		lTimeSnds = lTimeSnds - lTimeMins * 60;
		lTimeMins = lTimeMins - lTimeHrs * 60;
		strTime.Format(_T("耗时: %02d:%02d:%02d"), lTimeHrs, lTimeMins, lTimeSnds);
		pFrame->m_wndStatusBar.SetPaneText(3, strTime);
		break;
	default:
		break;
	}

	CFormView::OnTimer(nIDEvent);
}

void CMainControlDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (pDevCardWorktable)
	//{
	//	KillTimer(ID_TIMEER_WORKTABLE_COORD);
	//	pDevCardWorktable->StopMoveXY(TRUE, TRUE);
	//	pDevCardWorktable->StopMoveZ(TRUE, TRUE);
	//}

	//DeleteCriticalSection(&ProcObjListMutex);


	CFormView::OnClose();
}



void CMainControlDlg::OnBnClickedButtonPosMoveWorktableBegin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardWorktable)
		return;

	UpdateData(TRUE);
	if (0 == m_nPosMoveWorktableMode)	
	{
		//相对坐标
		pDevCardWorktable->PosMoveXYHand(m_fPosMoveWorktableX, m_fPosMoveWorktableY);
	}
	else
	{
		//绝对坐标
		double fAbsCurPosX, fAbsCurPosY;
		pDevCardWorktable->GetAbsPosXY(&fAbsCurPosX, &fAbsCurPosY);
		pDevCardWorktable->PosMoveXYHand(m_fPosMoveWorktableX - fAbsCurPosX, m_fPosMoveWorktableY - fAbsCurPosY);
	}
}


void CMainControlDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	
	//初始化界面
	((CComboBox*)GetDlgItem(IDC_COMBO_POS_MOVE_WORKTABLE_MODE))->InsertString(0, (_T("相对坐标")));
	((CComboBox*)GetDlgItem(IDC_COMBO_POS_MOVE_WORKTABLE_MODE))->InsertString(1, (_T("绝对坐标")));

	//初始化数值
	m_nPosMoveWorktableMode = 0;
	m_fPosMoveWorktableX = 0;
	m_fPosMoveWorktableY = 0;
	UpdateData(FALSE);

	//开始读工作台坐标
	if (pDevCardWorktable)
		SetTimer(ID_TIMEER_WORKTABLE_COORD, 300, NULL);

	//加工线程相关
#if defined(_UNICODE) || defined(__UNICODE)
	MarkProcStopEvent = CreateEventW(NULL, TRUE, FALSE, NULL);
#else
	MarkProcStopEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
#endif
	ResetEvent(MarkProcStopEvent);
	m_pListContainer = NULL;
	m_bMarkThreadIsRunning = FALSE;
	m_pThMarkProc = NULL;
	InitializeCriticalSection(&ProcObjListMutex);

	CCameraView* pCameraView = (CCameraView*)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter1.GetPane(1, 0);
	m_hwndCameraView = pCameraView->GetSafeHwnd();
}


void CMainControlDlg::OnBnClickedButtonPosMoveFromCameraToScanner()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardWorktable)
		return;

	double fPosCameraX, fPosCameraY;
	fPosCameraX = ReadDevCameraPosX();
	fPosCameraY = ReadDevCameraPosY();
	pDevCardWorktable->PosMoveXYHand(-fPosCameraX, -fPosCameraY);
}


void CMainControlDlg::OnBnClickedButtonPosMoveFromScannerToCamera()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardWorktable)
		return;

	double fPosCameraX, fPosCameraY;
	fPosCameraX = ReadDevCameraPosX();
	fPosCameraY = ReadDevCameraPosY();
	pDevCardWorktable->PosMoveXYHand(fPosCameraX, fPosCameraY);
}


void CMainControlDlg::OnBnClickedButtonLaserOn()
{

	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardMark)
		return;

	if (!m_bMarkThreadIsRunning)
	{
		pDevCardMark->LaserOn();
		m_bMarkThreadIsRunning = TRUE;
		pDevCardMark->WaitForThreadsEnded();
		MessageBoxTimeout(NULL, _T("出光完成"), _T("提示"), MB_OK, 0, 1000);
		m_bMarkThreadIsRunning = FALSE;
	}

}


void CMainControlDlg::OnBnClickedButtonLaserOff()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardMark)
		return;
	if (m_bMarkThreadIsRunning)
	{
		pDevCardMark->LaserOff();
		m_bMarkThreadIsRunning = FALSE;
	}

}


void CMainControlDlg::OnBnClickedButtonMainStartProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	CLaserMachineDoc* pDoc = (CLaserMachineDoc*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//CMachineListContainer* pListContainerTmp = pDoc->m_pLaserObjList;
	m_pListContainer = pDoc->m_pLaserObjList;


	//开始加工进程
	//if (NULL == pDevCardMark)
	//{
	//	AfxMessageBox(_T("打标卡未初始化"));
	//	return;
	//}
	//if (NULL == pDevCardWorktable)
	//{
	//	AfxMessageBox(_T("运动控制卡未初始化"));
	//	return;
	//}
	if (!m_bMarkThreadIsRunning)
	{
		m_lTimeStartProcess = GetTickCount();
		SetTimer(ID_TIMEER_PROCESS_TIME, 200, NULL);
		StartMarkThreads();
		m_bMarkThreadIsRunning = TRUE;
		WaitForMarkThreadEnded();
		KillTimer(ID_TIMEER_PROCESS_TIME);
		MessageBoxTimeout(NULL, _T("加工完成"), _T("提示"), MB_OK, 0, 1000);
		m_bMarkThreadIsRunning = FALSE;
	}
}

void CMainControlDlg::OnBnClickedButtonMainStopProcess()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardMark)
	{
		//AfxMessageBox(_T("打标卡未初始化"));
		return;
	}
	if (m_bMarkThreadIsRunning)
	{
		SetEvent(MarkProcStopEvent);
		pDevCardMark->StopMarkCardMark();
		m_bMarkThreadIsRunning = FALSE;
	}


}

void CMainControlDlg::WaitForMarkThreadEnded()
{
	//退出加工线程
	if (m_pThMarkProc)
	{
		BOOL bQuit = FALSE;
		DWORD dRet;
		MSG msg;
		int nCt = 0;
		while (!bQuit)
		{
			if (FALSE == m_bMarkThreadIsRunning)
				break;

			dRet = MsgWaitForMultipleObjects(1, &m_pThMarkProc->m_hThread, FALSE, INFINITE, QS_ALLINPUT);
			if (dRet == WAIT_OBJECT_0 + 1)
			{
				//收到消息
				TRACE("加工线程消息,函数返回值为%d \n", dRet);
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TRACE("PeekMessage_Count = %d \n", ++nCt);
					if (msg.message == WM_QUIT)
					{
						bQuit = TRUE;
						break;
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}

				//收到消息
				//TRACE("加工线程消息,函数返回值为%d \n", dRet);
				//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				//{
				//	TRACE("PeekMessage_Count = %d \n", ++nCt);
				//	TranslateMessage(&msg);
				//	DispatchMessage(&msg);
				//}
				//else
				//	Sleep(1);
			}
			else if (WAIT_OBJECT_0 == dRet)
			{
				//线程退出
				TRACE("加工线程已退出，函数返回值: %d \n", dRet);
				delete m_pThMarkProc;
				m_pThMarkProc = NULL;
				break;
			}
			else
			{
				//线程非正常退出
				TRACE("加工线程非正常退出，函数返回值: %d \n", dRet);
				delete m_pThMarkProc;
				m_pThMarkProc = NULL;
				break;
			}
		}
	}

	m_bMarkThreadIsRunning = FALSE;
}

void CMainControlDlg::StartMarkThreads()
{
	// reset all event handles to initial states 
	ResetEvent(MarkProcStopEvent);

	// stop threads if still running ...
	if ((*this).m_pThMarkProc)
	{
		WaitForSingleObject(m_pThMarkProc->m_hThread, INFINITE);
		StopMarkThread(m_pThMarkProc);
	}

	m_pThMarkProc = AfxBeginThread(MarkProcRun, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, 0);
	m_pThMarkProc->m_bAutoDelete = FALSE;
	m_pThMarkProc->ResumeThread();

}
void CMainControlDlg::StopMarkThread(CWinThread* pThred)
{
	//停止加工
	DWORD dwExit = 0;
	MSG msg;
	do
	{
		Sleep(1);
		GetExitCodeThread(pThred->m_hThread, &dwExit);
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	} while (dwExit == STILL_ACTIVE);

	//删除线程指针
	delete pThred;

}
//ThreadFunc
UINT CMainControlDlg::MarkProcRun(LPVOID lpParam)
{

	CMainControlDlg* pMainContorlDlg = (CMainControlDlg*)lpParam;
	//const HWND hPostDlg = pMainContorlDlg->GetSafeHwnd();

	//读对象链表
	EnterCriticalSection(&pMainContorlDlg->ProcObjListMutex);        // CriticalSect
	CMachineListContainer* pListContainerTmp = pMainContorlDlg->m_pListContainer;
	LeaveCriticalSection(&pMainContorlDlg->ProcObjListMutex);        // CriticalSect
	
	//CString strTime;
	//long t1 = GetTickCount();//程序段开始前取得系统运行时间(ms)            
	//分格
	CPreProcess preProcess;
	std::vector<ObjRect> vecGridRect;
	if(0 < vecGridX.size())
		preProcess.CalculateGrid(vecGridRect, pListContainerTmp, vecGridX, vecGridY);
	else
		preProcess.CalculateGrid(vecGridRect, pListContainerTmp);
	preProcess.DoGrid(vecGridRect, pListContainerTmp);
	////测试
	//long t2 = GetTickCount();//程序段结束后取得系统运行时间(ms) 
	//long nCtSize = 0;
	//double ptOrg1[2], ptScale1[2], fRotateDegree1, ptReal1[2];
	//ptOrg1[0] = 0;
	//ptOrg1[1] = 0;
	//ptScale1[0] = 1;
	//ptScale1[1] = 1;
	//fRotateDegree1 = 0;
	//ptReal1[0] = 0;
	//ptReal1[1] = 0;
	//preProcess.DoTrans(ptOrg1, ptScale1, fRotateDegree1, ptReal1);

	//pMainContorlDlg->m_bMarkThreadIsRunning = FALSE;
	//for (auto val1 : preProcess.m_vecProcEntPerGrid)
	//{
	//	for (auto val2 : val1.vecEntitiesPerGrid)
	//	{
	//		for (auto val3 : val2.mlineObj)
	//		{
	//			nCtSize += val3.size();
	//		}
	//	}
	//}
	//strTime.Format(_T("Size: %d\ntime:%dms"), nCtSize, t2 - t1);//前后之差即程序运行时间        
	//AfxMessageBox(strTime);
	//return 0;
	////测试


	//暂存当前工作台位置
	double fPosSavedX, fPosSavedY;
	pDevCardWorktable->GetAbsPosXY(&fPosSavedX, &fPosSavedY);

	//抓标
	//暂存手动抓标结果
	int nCountMarkPoints = g_nCountMarkPoints;
	std::vector <CPointF> vPtPosDestinedMark(g_vPtPosDestinedMark);
	std::vector <CPointF> vPtPosRealMark(g_vPtPosRealMark);
	std::vector <HalconModel> vMarkPointModel(g_vMarkPointModel);
	//准备自动抓标结果
	if (0 != nCountMarkPoints)
	{
		//抓图计算
		for (int i = 0; i < nCountMarkPoints; i++)
		{
			double fPosTmpX, fPosTmpY;
			pDevCardWorktable->GetAbsPosXY(&fPosTmpX, &fPosTmpY);
			pDevCardWorktable->PosMoveXY(vPtPosRealMark[i].x - fPosTmpX, vPtPosRealMark[i].y - fPosTmpY, TRUE);

			XSleep(1000);

			std::vector <CPointF> vPtPosFinded;
			::SendMessage(pMainContorlDlg->m_hwndCameraView, WM_LOCATE, (WPARAM)&(vMarkPointModel[i]), (LPARAM)&vPtPosFinded);
			//int nFindedMark = pCameraView->m_pHalconWnd->LocateModel(vMarkPointModel[i], &vPtPosFinded);
			int nFindedMark = vPtPosFinded.size();
			if (0 >= nFindedMark)
			{
				//如果没抓到圆
				XSleep(1);
				AfxMessageBox(_T("没有抓到mark点"));
				return 1;
			}
			else if (1 < nFindedMark)
			{
				//如果抓到多个圆
				XSleep(1);
				AfxMessageBox(_T("抓到多个mark点"));
				return 1;
			}
			else
			{
				XSleep(1000);
				//如果抓到一个
				//AfxMessageBox(_T("抓到1个mark点"));
				vPtPosRealMark[i] += vPtPosFinded[0];
			}
		}
	}

	//平移旋转拉伸
	double ptOrg[2], ptScale[2], fRotateDegree, ptReal[2];
	preProcess.CalculateTrans(nCountMarkPoints, vPtPosDestinedMark, vPtPosRealMark, vecGridRect, fPosSavedX, fPosSavedY,
		ptOrg, ptScale, &fRotateDegree, ptReal);
	preProcess.DoTrans(ptOrg, ptScale, fRotateDegree, ptReal);

	CString strTmp;
	strTmp.Format(_T("ptOrg= %.3f, %.3f\nptScale= %.3f, %.3f\nRotate= %.3f\nptReal= %.3f, %.3f\norg-minGrid= %.3f, %.3f"), ptOrg[0], ptOrg[1],
		ptScale[0], ptScale[1], fRotateDegree,
		ptReal[0], ptReal[1],
		ptOrg[0] - vecGridRect[0].min_x, ptOrg[1] - vecGridRect[0].min_y);
	pMainContorlDlg->SetDlgItemText(IDC_STATIC_TEST_LOCATE, strTmp);

	//开始加工
	//写加工参数
	pDevCardMark->SetPensFromAllLayers(pListContainerTmp);

	//循环遍历每个分格
	double fGridCenterX, fGridCenterY;
	double fAbsCurPosX, fAbsCurPosY;
	for (int nGridIndex = 0; nGridIndex < vecGridRect.size(); nGridIndex++)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject((pMainContorlDlg->MarkProcStopEvent), 0))
			break;

		//工作平台运动到分格中心
		preProcess.GetGridCenter(nGridIndex, &fGridCenterX, &fGridCenterY);
		pDevCardWorktable->GetAbsPosXY(&fAbsCurPosX, &fAbsCurPosY);
		pDevCardWorktable->PosMoveXY(fGridCenterX - fAbsCurPosX, fGridCenterY - fAbsCurPosY, TRUE);
		//运动过程中写打标卡缓冲区
		preProcess.WriteEntitiesPerGridToBuffer(nGridIndex, pDevCardMark, pListContainerTmp);
		//等待工作台运动完成
		pDevCardWorktable->WaitForMoveEndedXY();
		XSleep(1);
		//出光
		pDevCardMark->StartMarkCardMark();
		pDevCardMark->WaitForThreadsEnded();
	}

	//工作台回原位置
	pDevCardWorktable->GetAbsPosXY(&fAbsCurPosX, &fAbsCurPosY);
	pDevCardWorktable->PosMoveXY(fPosSavedX - fAbsCurPosX, fPosSavedY - fAbsCurPosY, TRUE);
	pDevCardWorktable->WaitForMoveEndedXY();

	pMainContorlDlg->m_bMarkThreadIsRunning = FALSE;

	//AfxMessageBox(_T("加工完成"));
	return 0;
}


void CMainControlDlg::OnBnClickedButtonPos()
{
	// TODO: 在此添加控件通知处理程序代码

	if (NULL == pDevCardWorktable)
		return;

	pDevCardWorktable->ResetZeroWorktable();
}


void CMainControlDlg::OnBnClickedButtontPosMoveWorktableZUp()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardWorktable)
		return;

	UpdateData(TRUE);
	pDevCardWorktable->PosMoveZHand(m_fPosMoveWorktableZ);
}


void CMainControlDlg::OnBnClickedButtontPosMoveWorktableZDown()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == pDevCardWorktable)
		return;

	UpdateData(TRUE);
	pDevCardWorktable->PosMoveZHand(-m_fPosMoveWorktableZ);

}




void CMainControlDlg::OnBnClickedButtonProcessTestDxf()
{
	// TODO: 在此添加控件通知处理程序代码
	CLaserMachineDoc* pDoc = (CLaserMachineDoc*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pListContainer = pDoc->m_pLaserObjList;
	CPreProcess preProcess;
	VecEntities vecEntities, vecEntitiesTrans;
	ObjRect objrect;

	objrect = m_pListContainer->GetObjBound();
	double centerX, centerY;
	centerX = (objrect.max_x + objrect.min_x) / 2;
	centerY = (objrect.max_y + objrect.min_y) / 2;

	preProcess.LoadMachineObjList(vecEntities, m_pListContainer);

	if (NULL == pDevCardMark)
		return;
	//先清空打标卡缓冲区
	if (!pDevCardMark->DeleteALLEntities())
		return;
	if (0 >= vecEntities.size())
		return;
	if (FALSE == pDevCardMark->SetPensFromAllLayers(m_pListContainer))
		return;

	//带偏移旋转的阵列
	for (auto valVecDouble : g_vecTestDXF)
	{
		CString strTmp;
		strTmp.Format(_T("ptOrg= %.3f, %.3f\nRotate= %.3f\nptReal= %.3f, %.3f"), centerX, centerY, 
			-valVecDouble[2], valVecDouble[0], valVecDouble[1]);
		this->SetDlgItemText(IDC_STATIC_TEST_LOCATE, strTmp);


		for (auto valEnt : vecEntities)
		{
			PreProcessEntity myEntity;
			MLine_T mlineTmp;
			MLine_T mlineTranslateOrg, mlineTranslate, mlineRotate;

			mlineTmp = valEnt.mlineObj;
			bgt::translate_transformer<double, 2, 2> translateOrg(-centerX, -centerY);
			bg::transform(mlineTmp, mlineTranslateOrg, translateOrg);
			bgt::rotate_transformer<boost::geometry::radian, double, 2, 2> rotate(-valVecDouble[2]);
			//bgt::rotate_transformer<boost::geometry::degree, double, 2, 2> rotate(-valVecDouble[2]);
			bg::transform(mlineTranslateOrg, mlineRotate, rotate);
			bgt::translate_transformer<double, 2, 2> translate(valVecDouble[0], valVecDouble[1]);
			bg::transform(mlineRotate, mlineTranslate, translate);
			myEntity.mlineObj = mlineTranslate;
			myEntity.nPenNo = valEnt.nPenNo;
			vecEntitiesTrans.push_back(myEntity);
		}
	}

	for (auto valEnt : vecEntitiesTrans)
	{
		int nPenNo = valEnt.nPenNo;

		MLine_T mlineTmp;
		mlineTmp = valEnt.mlineObj;
		//bgt::translate_transformer<double, 2, 2> translate(-ptCenter.x(), -ptCenter.y());
		//bg::transform(mlineTmp, mlineTrans, translate);

		BOOST_FOREACH(Line_T const& line, mlineTmp)
		{
			int nCountPt;
			double(*ptBuf)[2];
			nCountPt = (int)line.size();
			ptBuf = new double[nCountPt][2];

			for (int i = 0; i < nCountPt; i++)
			{
				ptBuf[i][0] = line[i].x();
				ptBuf[i][1] = line[i].y();
			}

			//将对象写入板卡缓冲区
			if (FALSE == pDevCardMark->AddEntityLines(nCountPt, ptBuf, nPenNo))
			{
				delete[] ptBuf;
				return;
			}
		}
	}

	if (NULL == pDevCardWorktable)
		return;
	double fPosCameraX, fPosCameraY;
	fPosCameraX = ReadDevCameraPosX();
	fPosCameraY = ReadDevCameraPosY();
	pDevCardWorktable->PosMoveXY(-fPosCameraX, -fPosCameraY, TRUE);
	pDevCardWorktable->WaitForMoveEndedXY();

	//开始加工
	pDevCardMark->StartMarkCardMark();
	pDevCardMark->WaitForThreadsEnded();


}


void CMainControlDlg::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	if (pDevCardWorktable)
	{
		KillTimer(ID_TIMEER_WORKTABLE_COORD);
		pDevCardWorktable->StopMoveXY(TRUE, TRUE);
		pDevCardWorktable->StopMoveZ(TRUE, TRUE);
	}
	OnBnClickedButtonMainStopProcess();
	OnBnClickedButtonStopMark();
	DeleteCriticalSection(&ProcObjListMutex);
}


