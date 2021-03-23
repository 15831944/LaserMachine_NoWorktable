// ObjectProtyDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "ObjectProtyDlg2.h"
#include "afxdialogex.h"


// CObjectProtyDlg2 对话框

IMPLEMENT_DYNAMIC(CObjectProtyDlg2, CDialog)

CObjectProtyDlg2::CObjectProtyDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectProtyDlg2::IDD, pParent)
{
	m_nSelGroup = 0;
	m_nSel_Old = 0;
	m_FillAngle = gFillAngle0;
	m_FillGap = gFillGap0;
	m_FillCurtail = gCurtail0;
	m_OutlinePrior = gFillOutlinePrior;
	m_GapMode = gGapMode0;
	m_FillMode = gFillMode0;
	m_FillEnable = gFillEnable0;
	m_Angle[0] = gFillAngle0;
	m_Gap[0] = gFillGap0;
	m_Curtail[0] = gCurtail0;
	m_GMode[0] = gGapMode0;
	m_FMode[0] = gFillMode0;
	m_Enable[0] = gFillEnable0;
	m_Angle[1] = gFillAngle1;
	m_Gap[1] = gFillGap1;
	m_Curtail[1] = gCurtail1;
	m_GMode[1] = gGapMode1;
	m_FMode[1] = gFillMode1;
	m_Enable[1] = gFillEnable1;
	m_Angle[2] = gFillAngle2;
	m_Gap[2] = gFillGap2;
	m_Curtail[2] = gCurtail2;
	m_GMode[2] = gGapMode2;
	m_FMode[2] = gFillMode2;
	m_Enable[2] = gFillEnable2;
	m_Angle[3] = gFillAngle3;
	m_Gap[3] = gFillGap3;
	m_Curtail[3] = gCurtail3;
	m_GMode[3] = gGapMode3;
	m_FMode[3] = gFillMode3;
	m_Enable[3] = gFillEnable3;
}

CObjectProtyDlg2::~CObjectProtyDlg2()
{
}

void CObjectProtyDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_OBJECT_PROPERTY_DLG2_RADIO4, m_nSelGroup);
	DDV_MinMaxInt(pDX, m_nSelGroup, 0, 3);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_DLG2_EDIT1, m_FillAngle);
	DDV_MinMaxDouble(pDX, m_FillAngle, -360, 360);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_DLG2_EDIT2, m_FillGap);
	DDV_MinMaxDouble(pDX, m_FillGap, 0, 1000);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_DLG2_EDIT3, m_FillCurtail);
	DDV_MinMaxDouble(pDX, m_FillCurtail, 0, 100);
	DDX_Radio(pDX, IDC_OBJECT_PROPERTY_DLG2_RADIO1, m_OutlinePrior);
	DDV_MinMaxInt(pDX, m_OutlinePrior, 0, 2);
	DDX_Radio(pDX, IDC_OBJECT_PROPERTY_DLG2_RADIO8, m_GapMode);
	DDV_MinMaxInt(pDX, m_GapMode, 0, 1);
	DDX_Radio(pDX, IDC_OBJECT_PROPERTY_DLG2_RADIO10, m_FillMode);
	DDV_MinMaxInt(pDX, m_FillMode, 0, 1);
	DDX_Check(pDX, IDC_OBJECT_PROPERTY_DLG2_CHECK1, m_FillEnable);
}


BEGIN_MESSAGE_MAP(CObjectProtyDlg2, CDialog)
	ON_BN_CLICKED(IDC_OBJECT_PROPERTY_DLG2_RADIO4, &CObjectProtyDlg2::OnClickedObjectPropertyDlg2Radio4)
	ON_COMMAND(IDC_OBJECT_PROPERTY_DLG2_RADIO5, &CObjectProtyDlg2::OnClickedObjectPropertyDlg2Radio4)
	ON_COMMAND(IDC_OBJECT_PROPERTY_DLG2_RADIO6, &CObjectProtyDlg2::OnClickedObjectPropertyDlg2Radio4)
	ON_COMMAND(IDC_OBJECT_PROPERTY_DLG2_RADIO7, &CObjectProtyDlg2::OnClickedObjectPropertyDlg2Radio4)
	ON_BN_CLICKED(IDC_OBJECT_PROPERTY_DLG2_CHECK1, &CObjectProtyDlg2::OnClickedObjectPropertyDlg2Check1)
	ON_BN_CLICKED(IDC_OBJECT_PROPERTY_DLG2_BTN1, &CObjectProtyDlg2::OnClickedObjectPropertyDlg2Save)
END_MESSAGE_MAP()


// ObjectProtyDlg2 消息处理程序


BOOL CObjectProtyDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	if (m_FillEnable)
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO8)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO9)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO11)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1))->SetCheck(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO8)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO9)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1))->SetCheck(FALSE);
	}
	return TRUE;
}

void CObjectProtyDlg2::OnClickedObjectPropertyDlg2Radio4()
{
	UpdateData(TRUE);
	if (m_nSel_Old == m_nSelGroup)
		return;
	if (m_nSel_Old > 3 || m_nSelGroup > 3)
		return;
	m_Angle[m_nSel_Old] = m_FillAngle;
	m_Gap[m_nSel_Old] = m_FillGap;
	m_Curtail[m_nSel_Old] = m_FillCurtail;
	m_GMode[m_nSel_Old] = m_GapMode;
	m_FMode[m_nSel_Old] = m_FillMode;
	if (m_FillEnable)
		m_Enable[m_nSel_Old] = true;
	else
		m_Enable[m_nSel_Old] = false;
	m_nSel_Old = m_nSelGroup;
	m_FillAngle = m_Angle[m_nSelGroup];
	m_FillGap = m_Gap[m_nSelGroup];
	m_FillCurtail = m_Curtail[m_nSelGroup];
	m_GapMode = m_GMode[m_nSelGroup];
	m_FillMode = m_FMode[m_nSelGroup];
	m_FillEnable = m_Enable[m_nSelGroup];
	if (m_FillEnable)
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO8)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO9)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1))->SetCheck(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO8)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO9)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1))->SetCheck(FALSE);
	}
	UpdateData(FALSE);
}

void CObjectProtyDlg2::OnClickedObjectPropertyDlg2Check1()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1);
	if (pBtn->GetCheck())
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT2)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO8)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO9)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_CHECK1)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT2)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO8)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO9)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJECT_PROPERTY_DLG2_RADIO11)->EnableWindow(FALSE);
	}
}

void CObjectProtyDlg2::OnClickedObjectPropertyDlg2Save()
{
	if (!UpdateData(TRUE))
		return;
	m_Angle[m_nSelGroup] = m_FillAngle;
	m_Gap[m_nSelGroup] = m_FillGap;
	m_Curtail[m_nSelGroup] = m_FillCurtail;
	m_GMode[m_nSelGroup] = m_GapMode;
	m_FMode[m_nSelGroup] = m_FillMode;
	if (m_FillEnable)
		m_Enable[m_nSelGroup] = true;
	else
		m_Enable[m_nSelGroup] = false;
	gFillOutlinePrior = m_OutlinePrior;
	gFillAngle0 = m_Angle[0];
	gFillGap0 = m_Gap[0];
	gCurtail0 = m_Curtail[0];
	gGapMode0 = m_GMode[0];
	gFillMode0 = m_FMode[0];
	gFillEnable0 = m_Enable[0];
	gFillAngle1 = m_Angle[1];
	gFillGap1 = m_Gap[1];
	gCurtail1 = m_Curtail[1];
	gGapMode1 = m_GMode[1];
	gFillMode1 = m_FMode[1];
	gFillEnable1 = m_Enable[1];
	gFillAngle2 = m_Angle[2];
	gFillGap2 = m_Gap[2];
	gCurtail2 = m_Curtail[2];
	gGapMode2 = m_GMode[2];
	gFillMode2 = m_FMode[2];
	gFillEnable2 = m_Enable[2];
	gFillAngle3 = m_Angle[3];
	gFillGap3 = m_Gap[3];
	gCurtail3 = m_Curtail[3];
	gGapMode3 = m_GMode[3];
	gFillMode3 = m_FMode[3];
	gFillEnable3 = m_Enable[3];
	CDialog::OnOK();
}
