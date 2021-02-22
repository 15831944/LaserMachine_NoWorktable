// DevCfgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "DevCfgDlg.h"
#include "afxdialogex.h"


// CDevCfgDlg �Ի���

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


// CDevCfgDlg ��Ϣ�������


BOOL CDevCfgDlg::PreTranslateMessage(MSG* pMsg)
{
	// ��ֹ"Enter"��"ESC"�����˳�����
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
	//��ӱ�������
	//GetParentFrame()->SendMessage(WM_MainWindows_Resume, NULL, NULL);
	CDialogEx::OnOK();
}




BOOL CDevCfgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//ΪTab Control����4��ҳ��
	m_tab.InsertItem(0, _T("������"));
	m_tab.InsertItem(1, _T("��"));
	m_tab.InsertItem(2, _T("����̨"));
	m_tab.InsertItem(3, _T("���"));

	//����4���Ի���
	m_dlgDevCfgTabLASER.Create(IDD_DEVICE_CONFIG_TAB_LASER, &m_tab);
	m_dlgDevCfgTabScanner.Create(IDD_DEVICE_CONFIG_TAB_SCANNER, &m_tab);
	m_dlgDevCfgTabWorktable.Create(IDD_DEVICE_CONFIG_TAB_WORKTABLE, &m_tab);
	m_dlgDevCfgTabCamera.Create(IDD_DEVICE_CONFIG_TAB_CAMERA, &m_tab);

	//�趨��Tab����ʾ�ķ�Χ
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

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &m_dlgDevCfgTabLASER;
	pDialog[1] = &m_dlgDevCfgTabScanner;
	pDialog[2] = &m_dlgDevCfgTabWorktable;
	pDialog[3] = &m_dlgDevCfgTabCamera;
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDevCfgDlg::OnTcnSelchangeTabDeviceConfig(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ѵ�ǰ��ҳ����������
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = m_tab.GetCurSel();
	//���µ�ҳ����ʾ����
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);


	*pResult = 0;
}
