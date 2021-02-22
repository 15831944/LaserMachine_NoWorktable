
// MainFrm.cpp : CMainFrame 类的实现
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
	//系统消息
	ON_WM_CREATE()
	ON_WM_SIZE()
	//用户消息
	ON_MESSAGE(WM_CtrlWindows_Size, &CMainFrame::OnCtrlwindowsSize)
	ON_MESSAGE(WM_ObPrtyWindows_Size, &CMainFrame::OnObprtywindowsSize)
	ON_MESSAGE(WM_CamPosWindows_Size, &CMainFrame::OnCamPoswindowsSize)
	ON_MESSAGE(WM_MainWindows_Resume, &CMainFrame::OnMainwindowsResume)
	//命令
	ON_COMMAND(IDM_OBJPRTY_PANEL_DISP, &CMainFrame::OnObjPrtyPanelDisp)
	ON_COMMAND(IDM_CAMPOS_PANEL_DISP, &CMainFrame::OnCamPosPanelDisp)
	ON_COMMAND(IDM_GRAPH_TO_VIDEO, &CMainFrame::OnDrawToVideo)
	ON_COMMAND(IDM_DEVICE_CONFIG, &CMainFrame::OnDeviceConfig)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	//修改状态栏,具体内容待定
	//****2019.5 By Cao****
	ID_INDICATOR_DEVICE_COORD,
	ID_INDICATOR_VIEW_COORD,
	ID_INDICATOR_USED_TIME,
	ID_INDICATOR_MACHINE_STATUS,
	//ID_INDICATOR_CAPS,
	//ID_INDICATOR_NUM,
	//ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
	m_bAutoMenuEnable = FALSE; //使能调用EnableMenuItem
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
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndToolBar1.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar1.LoadToolBar(IDR_TOOLBAR_MODIFY))
	{
		TRACE0("未能创建自定义工具栏\n");
		return -1;      // 未能创建
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));


	// TODO:  如果不需要可停靠工具栏，则删除这三行
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_bSplitter_Flag = false;	//窗口创建完成标志置位
	
	//设置窗口拆分,并为各子窗口设置大小等
	//****2019.5 By Cao****
	//if (!m_wndSplitter.CreateStatic(this, 1, 3))
	//****2020.7 增加一个子窗口 用于相机定位****
	if (!m_wndSplitter.CreateStatic(this, 1, 4))
		return FALSE;
	//设备控制窗口,位于主窗口左侧,固定宽度,不可关闭
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CMainControlDlg),
		CSize(ControlWindowsWidth, 0), pContext))
		return FALSE;

	//中间窗口用于显示加工对象和相机图像,默认宽度为窗体总宽减去设备控制窗口后的剩余
	m_wndSplitter.SetColumnInfo(1, MainWindowsWidth - ControlWindowsWidth, 10);

	//加工对象属性窗口,位于主窗口右侧,固定宽度,可关闭和打开.默认关闭
	if (!m_wndSplitter.CreateView(0, 2, RUNTIME_CLASS(CObjectProperty),
		CSize(0, 0), pContext))
		return FALSE;
	m_bObPrtyWindows_Hide = true;

	//相机定位设置窗口,位于主窗口右侧,固定宽度,可关闭和打开.默认关闭
	if (!m_wndSplitter.CreateView(0, 3, RUNTIME_CLASS(CCameraPosition),
		CSize(0, 0), pContext))
		return FALSE;
	m_bCamPosWindows_Hide = true;

	//中间窗口继续拆分为上下两个子窗口
	if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 2, 1, WS_CHILD | WS_VISIBLE,
		m_wndSplitter.IdFromRowCol(0, 1)))
		return FALSE;

	//上面窗口用于显示加工对象,尺寸可变
	if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CLaserMachineView),
		CSize(0, MainWindowsHight - 20), pContext))
		return FALSE;
	//下面窗口用于相机图像显示,尺寸可变
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
	//  CREATESTRUCT cs 来修改窗口类或样式
	//修改标题栏,设置主窗口大小
	//****2019.5 By Cao****
	cs.style &= ~FWS_ADDTOTITLE;
//	cs.lpszName = _T("XXXX激光加工软件");
	cs.cx = MainWindowsWidth;
	cs.cy = MainWindowsHight;
//	cs.style &= ~WS_SIZEBOX;
//	cs.style &= ~WS_MAXIMIZEBOX;
	return TRUE;
}

// CMainFrame 诊断
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

// CMainFrame 消息处理程序
afx_msg LRESULT CMainFrame::OnCtrlwindowsSize(WPARAM wParam, LPARAM lParam)
{
	//若调整尺寸,则重置主控对话框尺寸
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
	//若调整尺寸,则重置加工对象属性对话框尺寸
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
	//若调整尺寸,则重置相机定位设置对话框尺寸
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
	//若拆分窗口已经完成,则锁定加工对象属性对话框尺寸
	if (m_bSplitter_Flag)
	{
		GetClientRect(rc);
		//******注意:主窗口最小化时不调整拆分窗口尺寸
		if (rc.right == 0 && rc.bottom == 0)
			return;
		//***********否则会出现异常中断
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
	//刷新理论坐标
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
	dlg.m_strCheckTitle = _T("请输入系统管理员密码");
	dlg.DoModal();
	if (dlg.m_strPassword != m_strSysPassword)
	{
		MessageBox(_T("输入密码错误!\n"));
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pDevCardMark)
	{
		pDevCardMark->StopMarkCardMark();
	}

	CFrameWnd::OnClose();
}
