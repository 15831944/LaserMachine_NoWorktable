// DevCfgDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "DevCfgDlg.h"
#include "afxdialogex.h"


// CDevCfgDlg 对话框

IMPLEMENT_DYNAMIC(CDevCfgDlg, CDialogEx)

CDevCfgDlg::CDevCfgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevCfgDlg::IDD, pParent)
{

}

CDevCfgDlg::~CDevCfgDlg()
{
}

void CDevCfgDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TAB_DEVICE_CONFIG, m_tab);
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDevCfgDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDevCfgDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CDevCfgDlg::OnBnClickedBtnSave)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_DEVICE_CONFIG, &CDevCfgDlg::OnTcnSelchangeTabDeviceConfig)
END_MESSAGE_MAP()


// CDevCfgDlg 消息处理程序


BOOL CDevCfgDlg::PreTranslateMessage(MSG* pMsg)
{
	// 禁止"Enter"、"ESC"按键退出窗口
	if (((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
		|| ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE)))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDevCfgDlg::OnBnClickedCancel()
{
	//GetParentFrame()->SendMessage(WM_MainWindows_Resume, NULL, NULL);
	CDialogEx::OnCancel();
}

void CDevCfgDlg::OnBnClickedBtnSave()
{
	//添加保存数据
	//GetParentFrame()->SendMessage(WM_MainWindows_Resume, NULL, NULL);
	CDialogEx::OnOK();
}




BOOL CDevCfgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//为Tab Control增加4个页面
	m_tab.InsertItem(0, _T("激光器"));
	m_tab.InsertItem(1, _T("振镜"));
	m_tab.InsertItem(2, _T("工作台"));
	m_tab.InsertItem(3, _T("相机"));

	//创建4个对话框
	m_dlgDevCfgTabLASER.Create(IDD_DEVICE_CONFIG_TAB_LASER, &m_tab);
	m_dlgDevCfgTabScanner.Create(IDD_DEVICE_CONFIG_TAB_SCANNER, &m_tab);
	m_dlgDevCfgTabWorktable.Create(IDD_DEVICE_CONFIG_TAB_WORKTABLE, &m_tab);
	m_dlgDevCfgTabCamera.Create(IDD_DEVICE_CONFIG_TAB_CAMERA, &m_tab);

	//设定在Tab内显示的范围
	CRect rc;
	m_tab.GetClientRect(&rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_dlgDevCfgTabLASER.MoveWindow(&rc);
	m_dlgDevCfgTabScanner.MoveWindow(&rc);
	m_dlgDevCfgTabWorktable.MoveWindow(&rc);
	m_dlgDevCfgTabCamera.MoveWindow(&rc);

	//把对话框对象指针保存起来
	pDialog[0] = &m_dlgDevCfgTabLASER;
	pDialog[1] = &m_dlgDevCfgTabScanner;
	pDialog[2] = &m_dlgDevCfgTabWorktable;
	pDialog[3] = &m_dlgDevCfgTabCamera;
	//显示初始页面
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	//保存当前选择
	m_CurSelTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDevCfgDlg::OnTcnSelchangeTabDeviceConfig(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	//把当前的页面隐藏起来
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//得到新的页面索引
	m_CurSelTab = m_tab.GetCurSel();
	//把新的页面显示出来
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);


	*pResult = 0;
}
