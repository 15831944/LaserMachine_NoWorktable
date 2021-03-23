// ObjectProtyDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "ObjectProtyDlg1.h"
#include "afxdialogex.h"


// CObjectProtyDlg1 对话框

IMPLEMENT_DYNAMIC(CObjectProtyDlg1, CDialog)

CObjectProtyDlg1::CObjectProtyDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectProtyDlg1::IDD, pParent)
{
	m_Duplicate = gDupNumber * 2 + 1;
	m_GapDistance = gGapDistance;
}

CObjectProtyDlg1::~CObjectProtyDlg1()
{
}

void CObjectProtyDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLG1_EDIT1, m_Duplicate);
	DDV_MinMaxUInt(pDX, m_Duplicate, 1, 1000);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLG1_EDIT2, m_GapDistance);
	DDV_MinMaxFloat(pDX, m_GapDistance, (float)0.0001, 1);
}


BEGIN_MESSAGE_MAP(CObjectProtyDlg1, CDialog)
END_MESSAGE_MAP()



void CObjectProtyDlg1::OnOK()
{
	UpdateData(TRUE);
	if ((m_Duplicate & 1) == 0)
	{
		MessageBox(_T("线数必须为奇数"));
		return;
	}
	gDupNumber = m_Duplicate / 2;
	gGapDistance = m_GapDistance;
	CDialog::OnOK();
}


