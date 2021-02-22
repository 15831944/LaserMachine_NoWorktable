
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "MainFrm.h"
#include "LaserMachineView.h"
#include "LaserMachineDoc.h"
#include "MainControlDlg.h"
#include "ObjectProperty.h"
#include "CameraPosition.h"
#include "CameraView.h"
#include "DevCfgDlg.h"
#include "CheckPassword.h"
#include "DeviceCardWorktable.h"
#include "DeviceCardMark.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//ϵͳ��Ϣ
	ON_WM_CREATE()
	ON_WM_SIZE()
	//�û���Ϣ
	ON_MESSAGE(WM_CtrlWindows_Size, &CMainFrame::OnCtrlwindowsSize)
	ON_MESSAGE(WM_ObPrtyWindows_Size, &CMainFrame::OnObprtywindowsSize)
	ON_MESSAGE(WM_CamPosWindows_Size, &CMainFrame::OnCamPoswindowsSize)
	ON_MESSAGE(WM_MainWindows_Resume, &CMainFrame::OnMainwindowsResume)
	//����
	ON_COMMAND(IDM_OBJPRTY_PANEL_DISP, &CMainFrame::OnObjPrtyPanelDisp)
	ON_COMMAND(IDM_CAMPOS_PANEL_DISP, &CMainFrame::OnCamPosPanelDisp)
	ON_COMMAND(IDM_GRAPH_TO_VIDEO, &CMainFrame::OnDrawToVideo)
	ON_COMMAND(IDM_DEVICE_CONFIG, &CMainFrame::OnDeviceConfig)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	//�޸�״̬��,�������ݴ���
	//****2019.5 By Cao****
	ID_INDICATOR_DEVICE_COORD,
	ID_INDICATOR_VIEW_COORD,
	ID_INDICATOR_USED_TIME,
	ID_INDICATOR_MACHINE_STATUS,
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
	m_bAutoMenuEnable = FALSE; //ʹ�ܵ���EnableMenuItem
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_bToolBar_Flag = false;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP |
		CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndToolBar1.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar1.LoadToolBar(IDR_TOOLBAR_MODIFY))
	{
		TRACE0("δ�ܴ����Զ��幤����\n");
		return -1;      // δ�ܴ���
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));


	// TODO:  �������Ҫ��ͣ������������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_bSplitter_Flag = false;	//���ڴ�����ɱ�־��λ
	
	//���ô��ڲ��,��Ϊ���Ӵ������ô�С��
	//****2019.5 By Cao****
	//if (!m_wndSplitter.CreateStatic(this, 1, 3))
	//****2020.7 ����һ���Ӵ��� ���������λ****
	if (!m_wndSplitter.CreateStatic(this, 1, 4))
		return FALSE;
	//�豸���ƴ���,λ�����������,�̶����,���ɹر�
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMainControlDlg),
		CSize(ControlWindowsWidth, 0), pContext))
		return FALSE;

	//�м䴰��������ʾ�ӹ���������ͼ��,Ĭ�Ͽ��Ϊ�����ܿ��ȥ�豸���ƴ��ں��ʣ��
	m_wndSplitter.SetColumnInfo(1, MainWindowsWidth - ControlWindowsWidth, 10);

	//�ӹ��������Դ���,λ���������Ҳ�,�̶����,�ɹرպʹ�.Ĭ�Ϲر�
	if (!m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(CObjectProperty),
		CSize(0, 0), pContext))
		return FALSE;
	m_bObPrtyWindows_Hide = true;

	//�����λ���ô���,λ���������Ҳ�,�̶����,�ɹرպʹ�.Ĭ�Ϲر�
	if (!m_wndSplitter.CreateView(0, 3, RUNTIME_CLASS(CCameraPosition),
		CSize(0, 0), pContext))
		return FALSE;
	m_bCamPosWindows_Hide = true;

	//�м䴰�ڼ������Ϊ���������Ӵ���
	if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0, 1)))
		return FALSE;

	//���洰��������ʾ�ӹ�����,�ߴ�ɱ�
	if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CLaserMachineView),
		CSize(0, MainWindowsHight - 20), pContext))
		return FALSE;
	//���洰���������ͼ����ʾ,�ߴ�ɱ�
	if (!m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CCameraView),
		CSize(0, 0), pContext))
		return FALSE;

	m_bSplitter_Flag = true;
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//�޸ı�����,���������ڴ�С
	//****2019.5 By Cao****
	cs.style &= ~FWS_ADDTOTITLE;
//	cs.lpszName = _T("XXXX����ӹ����");
	cs.cx = MainWindowsWidth;
	cs.cy = MainWindowsHight;
//	cs.style &= ~WS_SIZEBOX;
//	cs.style &= ~WS_MAXIMIZEBOX;
	return TRUE;
}

// CMainFrame ���
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame ��Ϣ�������
afx_msg LRESULT CMainFrame::OnCtrlwindowsSize(WPARAM wParam, LPARAM lParam)
{
	//�������ߴ�,���������ضԻ���ߴ�
	if (m_bSplitter_Flag)
	{
		m_wndSplitter.SetColumnInfo(0, ControlWindowsWidth, 10);
		m_wndSplitter.RecalcLayout();
	}
	return 0;
}

afx_msg LRESULT CMainFrame::OnObprtywindowsSize(WPARAM wParam, LPARAM lParam)
{
	CRect rc;
	//�������ߴ�,�����üӹ��������ԶԻ���ߴ�
	if (m_bSplitter_Flag)
	{
		GetClientRect(rc);
		if (m_bObPrtyWindows_Hide && m_bCamPosWindows_Hide)
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth, 0);
		else if (!m_bObPrtyWindows_Hide)
		{
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - ObPrtyWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(2, ObPrtyWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(3, 0, 0);
		}
		else if (!m_bCamPosWindows_Hide)
		{
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - CamPosWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(2, 0, 0);
			m_wndSplitter.SetColumnInfo(3, CamPosWindowsWidth, 0);
		}
		m_wndSplitter.RecalcLayout();
	}
	return 0;
}

afx_msg LRESULT CMainFrame::OnCamPoswindowsSize(WPARAM wParam, LPARAM lParam)
{
	CRect rc;
	//�������ߴ�,�����������λ���öԻ���ߴ�
	if (m_bSplitter_Flag)
	{
		GetClientRect(rc);
		if (m_bObPrtyWindows_Hide && m_bCamPosWindows_Hide)
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth, 0);
		else if (!m_bObPrtyWindows_Hide)
		{
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - ObPrtyWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(2, ObPrtyWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(3, 0, 0);
		}
		else if (!m_bCamPosWindows_Hide)
		{
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - CamPosWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(2, 0, 0);
			m_wndSplitter.SetColumnInfo(3, CamPosWindowsWidth, 0);
		}
		m_wndSplitter.RecalcLayout();
	}
	return 0;
}

afx_msg LRESULT CMainFrame::OnMainwindowsResume(WPARAM wParam, LPARAM lParam)
{
	CRect rc;
	GetClientRect(rc);
	m_wndSplitter.SetColumnInfo(0, ControlWindowsWidth, 10);
	m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth, 0);
	m_wndSplitter1.SetRowInfo(0, MainWindowsHight - 20, 0);
	m_wndSplitter.RecalcLayout();
	m_wndSplitter1.RecalcLayout();
	m_bSplitter_Flag = true;
	return 0;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CRect rc;
	//����ִ����Ѿ����,�������ӹ��������ԶԻ���ߴ�
	if (m_bSplitter_Flag)
	{
		GetClientRect(rc);
		//******ע��:��������С��ʱ��������ִ��ڳߴ�
		if (rc.right == 0 && rc.bottom == 0)
			return;
		//***********���������쳣�ж�
		if (m_bObPrtyWindows_Hide && m_bCamPosWindows_Hide)
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth, 0);
		else if(!m_bObPrtyWindows_Hide)
		{
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - ObPrtyWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(2, ObPrtyWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(3, 0, 0);
		}
		else if(!m_bCamPosWindows_Hide)
		{
			m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - CamPosWindowsWidth, 0);
			m_wndSplitter.SetColumnInfo(2, 0, 0);
			m_wndSplitter.SetColumnInfo(3, CamPosWindowsWidth, 0);
		}
		m_wndSplitter.RecalcLayout();
	}
	CFrameWnd::OnSize(nType, cx, cy);
}

void CMainFrame::OnObjPrtyPanelDisp()
{
	CRect rc;
	GetClientRect(rc);
	m_bObPrtyWindows_Hide = !m_bObPrtyWindows_Hide;
	if (m_bObPrtyWindows_Hide)
	{
		m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth, 0);
		GetMenu()->CheckMenuItem(IDM_OBJPRTY_PANEL_DISP, MF_UNCHECKED);
	}
	else
	{
		m_bCamPosWindows_Hide = true;
		m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - ObPrtyWindowsWidth, 0);
		m_wndSplitter.SetColumnInfo(2, ObPrtyWindowsWidth, 0);
		m_wndSplitter.SetColumnInfo(3, 0, 0);
		GetMenu()->CheckMenuItem(IDM_OBJPRTY_PANEL_DISP, MF_CHECKED);
	}
	m_wndSplitter.RecalcLayout();
}

void CMainFrame::OnCamPosPanelDisp()
{
	//ˢ����������
	CCameraPosition* pCameraPosition = (CCameraPosition*)m_wndSplitter.GetPane(0, 3);
	pCameraPosition->RefreshMarkPoints();

	CRect rc;
	GetClientRect(rc);
	m_bCamPosWindows_Hide = !m_bCamPosWindows_Hide;
	if (m_bCamPosWindows_Hide)
	{
		m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth, 0);
		GetMenu()->CheckMenuItem(IDM_CAMPOS_PANEL_DISP, MF_UNCHECKED);
	}
	else
	{
		m_bObPrtyWindows_Hide = true;
		m_wndSplitter.SetColumnInfo(1, rc.Width() - ControlWindowsWidth - CamPosWindowsWidth, 0);
		m_wndSplitter.SetColumnInfo(2, 0, 0);
		m_wndSplitter.SetColumnInfo(3, CamPosWindowsWidth, 0);
		GetMenu()->CheckMenuItem(IDM_CAMPOS_PANEL_DISP, MF_CHECKED);
	}
	m_wndSplitter.RecalcLayout();
}

void CMainFrame::OnDrawToVideo()
{
	m_bToolBar_Flag = !m_bToolBar_Flag;
	if (!m_bToolBar_Flag)
	{
		m_wndSplitter1.SetRowInfo(0, MainWindowsHight - 20, 0);
		GetMenu()->CheckMenuItem(IDM_GRAPH_TO_VIDEO, MF_UNCHECKED);
	}
	else
	{
		m_wndSplitter1.SetRowInfo(0, 0, 0);
		GetMenu()->CheckMenuItem(IDM_GRAPH_TO_VIDEO, MF_CHECKED);
	}
	m_wndSplitter1.RecalcLayout();
}

void CMainFrame::OnDeviceConfig()
{
	m_strSysPassword = _T("");
	CCheckPassword dlg;
	dlg.m_strCheckTitle = _T("������ϵͳ����Ա����");
	dlg.DoModal();
	if (dlg.m_strPassword != m_strSysPassword)
	{
		MessageBox(_T("�����������!\n"));
		return;
	}
	//CRect rc;
	//GetClientRect(rc);
	//m_bSplitter_Flag = false;
	//m_wndSplitter.SetColumnInfo(0, 0, 0);
	//m_wndSplitter.SetColumnInfo(1, rc.Width(), 0);
	//m_wndSplitter1.SetRowInfo(0, rc.Height(), 0);
	//m_wndSplitter.RecalcLayout();
	//m_wndSplitter1.RecalcLayout();

	CDevCfgDlg dlg1;
	dlg1.DoModal();
}



void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (pDevCardMark)
	{
		pDevCardMark->StopMarkCardMark();
	}

	CFrameWnd::OnClose();
}
