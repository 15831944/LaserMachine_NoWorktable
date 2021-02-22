// MainControlDlg.cpp : ʵ���ļ�
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


// ���MessageBoxTimeout֧��
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


// CMainControlDlg ���

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


// CMainControlDlg ��Ϣ�������


void CMainControlDlg::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	//��ͼ�������ش��ڳߴ磬�����ϼ�������Ϣ�������������Ի���ߴ�
	GetParentFrame()->SendMessage(WM_CtrlWindows_Size, NULL, NULL);
}


void CMainControlDlg::OnBnClickedButtonStartMark()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (NULL == pDevCardMark)
	{
		AfxMessageBox(_T("��꿨δ��ʼ��"));
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
	MessageBoxTimeout(NULL, _T("������"), _T("��ʾ"), MB_OK, 0, 1000);

}


void CMainControlDlg::OnBnClickedButtonStopMark()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (NULL == pDevCardMark)
	{
		//AfxMessageBox(_T("��꿨δ��ʼ��"));
		return;
	}

	pDevCardMark->StopMarkCardMark();

}

void CMainControlDlg::OnBnClickedButtonWorktableMoveHome()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardWorktable)
		return;
	pDevCardWorktable->HomeMoveXY(-1, -1);
}

BOOL CMainControlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		strCoordinate.Format(_T("ƽ̨����: %.3f, %.3f, %.3f"), fCurAbsPosX, fCurAbsPosY, fCurAbsPosZ);
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
		strTime.Format(_T("��ʱ: %02d:%02d:%02d"), lTimeHrs, lTimeMins, lTimeSnds);
		pFrame->m_wndStatusBar.SetPaneText(3, strTime);
		break;
	default:
		break;
	}

	CFormView::OnTimer(nIDEvent);
}

void CMainControlDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardWorktable)
		return;

	UpdateData(TRUE);
	if (0 == m_nPosMoveWorktableMode)	
	{
		//�������
		pDevCardWorktable->PosMoveXYHand(m_fPosMoveWorktableX, m_fPosMoveWorktableY);
	}
	else
	{
		//��������
		double fAbsCurPosX, fAbsCurPosY;
		pDevCardWorktable->GetAbsPosXY(&fAbsCurPosX, &fAbsCurPosY);
		pDevCardWorktable->PosMoveXYHand(m_fPosMoveWorktableX - fAbsCurPosX, m_fPosMoveWorktableY - fAbsCurPosY);
	}
}


void CMainControlDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	
	//��ʼ������
	((CComboBox*)GetDlgItem(IDC_COMBO_POS_MOVE_WORKTABLE_MODE))->InsertString(0, (_T("�������")));
	((CComboBox*)GetDlgItem(IDC_COMBO_POS_MOVE_WORKTABLE_MODE))->InsertString(1, (_T("��������")));

	//��ʼ����ֵ
	m_nPosMoveWorktableMode = 0;
	m_fPosMoveWorktableX = 0;
	m_fPosMoveWorktableY = 0;
	UpdateData(FALSE);

	//��ʼ������̨����
	if (pDevCardWorktable)
		SetTimer(ID_TIMEER_WORKTABLE_COORD, 300, NULL);

	//�ӹ��߳����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardWorktable)
		return;

	double fPosCameraX, fPosCameraY;
	fPosCameraX = ReadDevCameraPosX();
	fPosCameraY = ReadDevCameraPosY();
	pDevCardWorktable->PosMoveXYHand(-fPosCameraX, -fPosCameraY);
}


void CMainControlDlg::OnBnClickedButtonPosMoveFromScannerToCamera()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardWorktable)
		return;

	double fPosCameraX, fPosCameraY;
	fPosCameraX = ReadDevCameraPosX();
	fPosCameraY = ReadDevCameraPosY();
	pDevCardWorktable->PosMoveXYHand(fPosCameraX, fPosCameraY);
}


void CMainControlDlg::OnBnClickedButtonLaserOn()
{

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardMark)
		return;

	if (!m_bMarkThreadIsRunning)
	{
		pDevCardMark->LaserOn();
		m_bMarkThreadIsRunning = TRUE;
		pDevCardMark->WaitForThreadsEnded();
		MessageBoxTimeout(NULL, _T("�������"), _T("��ʾ"), MB_OK, 0, 1000);
		m_bMarkThreadIsRunning = FALSE;
	}

}


void CMainControlDlg::OnBnClickedButtonLaserOff()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CLaserMachineDoc* pDoc = (CLaserMachineDoc*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//CMachineListContainer* pListContainerTmp = pDoc->m_pLaserObjList;
	m_pListContainer = pDoc->m_pLaserObjList;


	//��ʼ�ӹ�����
	//if (NULL == pDevCardMark)
	//{
	//	AfxMessageBox(_T("��꿨δ��ʼ��"));
	//	return;
	//}
	//if (NULL == pDevCardWorktable)
	//{
	//	AfxMessageBox(_T("�˶����ƿ�δ��ʼ��"));
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
		MessageBoxTimeout(NULL, _T("�ӹ����"), _T("��ʾ"), MB_OK, 0, 1000);
		m_bMarkThreadIsRunning = FALSE;
	}
}

void CMainControlDlg::OnBnClickedButtonMainStopProcess()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardMark)
	{
		//AfxMessageBox(_T("��꿨δ��ʼ��"));
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
	//�˳��ӹ��߳�
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
				//�յ���Ϣ
				TRACE("�ӹ��߳���Ϣ,��������ֵΪ%d \n", dRet);
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

				//�յ���Ϣ
				//TRACE("�ӹ��߳���Ϣ,��������ֵΪ%d \n", dRet);
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
				//�߳��˳�
				TRACE("�ӹ��߳����˳�����������ֵ: %d \n", dRet);
				delete m_pThMarkProc;
				m_pThMarkProc = NULL;
				break;
			}
			else
			{
				//�̷߳������˳�
				TRACE("�ӹ��̷߳������˳�����������ֵ: %d \n", dRet);
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
	//ֹͣ�ӹ�
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

	//ɾ���߳�ָ��
	delete pThred;

}
//ThreadFunc
UINT CMainControlDlg::MarkProcRun(LPVOID lpParam)
{

	CMainControlDlg* pMainContorlDlg = (CMainControlDlg*)lpParam;
	//const HWND hPostDlg = pMainContorlDlg->GetSafeHwnd();

	//����������
	EnterCriticalSection(&pMainContorlDlg->ProcObjListMutex);        // CriticalSect
	CMachineListContainer* pListContainerTmp = pMainContorlDlg->m_pListContainer;
	LeaveCriticalSection(&pMainContorlDlg->ProcObjListMutex);        // CriticalSect
	
	//CString strTime;
	//long t1 = GetTickCount();//����ο�ʼǰȡ��ϵͳ����ʱ��(ms)            
	//�ָ�
	CPreProcess preProcess;
	std::vector<ObjRect> vecGridRect;
	if(0 < vecGridX.size())
		preProcess.CalculateGrid(vecGridRect, pListContainerTmp, vecGridX, vecGridY);
	else
		preProcess.CalculateGrid(vecGridRect, pListContainerTmp);
	preProcess.DoGrid(vecGridRect, pListContainerTmp);
	////����
	//long t2 = GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms) 
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
	//strTime.Format(_T("Size: %d\ntime:%dms"), nCtSize, t2 - t1);//ǰ��֮���������ʱ��        
	//AfxMessageBox(strTime);
	//return 0;
	////����


	//�ݴ浱ǰ����̨λ��
	double fPosSavedX, fPosSavedY;
	pDevCardWorktable->GetAbsPosXY(&fPosSavedX, &fPosSavedY);

	//ץ��
	//�ݴ��ֶ�ץ����
	int nCountMarkPoints = g_nCountMarkPoints;
	std::vector <CPointF> vPtPosDestinedMark(g_vPtPosDestinedMark);
	std::vector <CPointF> vPtPosRealMark(g_vPtPosRealMark);
	std::vector <HalconModel> vMarkPointModel(g_vMarkPointModel);
	//׼���Զ�ץ����
	if (0 != nCountMarkPoints)
	{
		//ץͼ����
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
				//���ûץ��Բ
				XSleep(1);
				AfxMessageBox(_T("û��ץ��mark��"));
				return 1;
			}
			else if (1 < nFindedMark)
			{
				//���ץ�����Բ
				XSleep(1);
				AfxMessageBox(_T("ץ�����mark��"));
				return 1;
			}
			else
			{
				XSleep(1000);
				//���ץ��һ��
				//AfxMessageBox(_T("ץ��1��mark��"));
				vPtPosRealMark[i] += vPtPosFinded[0];
			}
		}
	}

	//ƽ����ת����
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

	//��ʼ�ӹ�
	//д�ӹ�����
	pDevCardMark->SetPensFromAllLayers(pListContainerTmp);

	//ѭ������ÿ���ָ�
	double fGridCenterX, fGridCenterY;
	double fAbsCurPosX, fAbsCurPosY;
	for (int nGridIndex = 0; nGridIndex < vecGridRect.size(); nGridIndex++)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject((pMainContorlDlg->MarkProcStopEvent), 0))
			break;

		//����ƽ̨�˶����ָ�����
		preProcess.GetGridCenter(nGridIndex, &fGridCenterX, &fGridCenterY);
		pDevCardWorktable->GetAbsPosXY(&fAbsCurPosX, &fAbsCurPosY);
		pDevCardWorktable->PosMoveXY(fGridCenterX - fAbsCurPosX, fGridCenterY - fAbsCurPosY, TRUE);
		//�˶�������д��꿨������
		preProcess.WriteEntitiesPerGridToBuffer(nGridIndex, pDevCardMark, pListContainerTmp);
		//�ȴ�����̨�˶����
		pDevCardWorktable->WaitForMoveEndedXY();
		XSleep(1);
		//����
		pDevCardMark->StartMarkCardMark();
		pDevCardMark->WaitForThreadsEnded();
	}

	//����̨��ԭλ��
	pDevCardWorktable->GetAbsPosXY(&fAbsCurPosX, &fAbsCurPosY);
	pDevCardWorktable->PosMoveXY(fPosSavedX - fAbsCurPosX, fPosSavedY - fAbsCurPosY, TRUE);
	pDevCardWorktable->WaitForMoveEndedXY();

	pMainContorlDlg->m_bMarkThreadIsRunning = FALSE;

	//AfxMessageBox(_T("�ӹ����"));
	return 0;
}


void CMainControlDlg::OnBnClickedButtonPos()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (NULL == pDevCardWorktable)
		return;

	pDevCardWorktable->ResetZeroWorktable();
}


void CMainControlDlg::OnBnClickedButtontPosMoveWorktableZUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardWorktable)
		return;

	UpdateData(TRUE);
	pDevCardWorktable->PosMoveZHand(m_fPosMoveWorktableZ);
}


void CMainControlDlg::OnBnClickedButtontPosMoveWorktableZDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == pDevCardWorktable)
		return;

	UpdateData(TRUE);
	pDevCardWorktable->PosMoveZHand(-m_fPosMoveWorktableZ);

}




void CMainControlDlg::OnBnClickedButtonProcessTestDxf()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	//����մ�꿨������
	if (!pDevCardMark->DeleteALLEntities())
		return;
	if (0 >= vecEntities.size())
		return;
	if (FALSE == pDevCardMark->SetPensFromAllLayers(m_pListContainer))
		return;

	//��ƫ����ת������
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

			//������д��忨������
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

	//��ʼ�ӹ�
	pDevCardMark->StartMarkCardMark();
	pDevCardMark->WaitForThreadsEnded();


}


void CMainControlDlg::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

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


