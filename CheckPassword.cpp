// CheckSysPasswd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "CheckPassword.h"
#include "afxdialogex.h"


// CCheckPassword �Ի���

IMPLEMENT_DYNAMIC(CCheckPassword, CDialog)

CCheckPassword::CCheckPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CCheckPassword::IDD, pParent)
	, m_strPassword(_T(""))
{
}

CCheckPassword::~CCheckPassword()
{
}

void CCheckPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}

BEGIN_MESSAGE_MAP(CCheckPassword, CDialog)
	ON_BN_CLICKED(IDOK, &CCheckPassword::OnBnClickedOk)
END_MESSAGE_MAP()

// CCheckPassword ��Ϣ�������
void CCheckPassword::OnBnClickedOk()
{ 
	UpdateData(TRUE);
	CDialog::OnOK();
}

BOOL CCheckPassword::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_STATIC_CHECKTITLE)->SetWindowText(m_strCheckTitle);
	GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
	return FALSE;  //Set the focus to a control, so return false
}
