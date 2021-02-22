// CObjPropertyDlgEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "ObjPropertyDlgEdit.h"
#include "afxdialogex.h"


// CObjPropertyDlgEdit 对话框

IMPLEMENT_DYNAMIC(CObjPropertyDlgEdit, CDialogEx)

CObjPropertyDlgEdit::CObjPropertyDlgEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CObjPropertyDlgEdit::IDD, pParent)
	, m_RotateAngle(0)
{
	m_bSizeChanged;
	m_pObjProty = NULL;
	m_ProcessSpeed = 0;
	m_ProcessTimes = 0;
	m_ProcessMode = 0;
	m_ProcessPower = 0;
	m_ProcessFrequncy = 0;
	m_ProcessPulseWidth = 0;
	m_ProcessWaitTime = 0;
	m_Rise_Lenth_Step = 0;
	m_Start_X = 0;
	m_Start_Y = 0;
	m_End_X = 0;
	m_End_Y = 0;
	m_Center_X = 0;
	m_Center_Y = 0;
	m_Radius = 0;
	m_Ratio = 1;
	m_Start_Angle = 0;
	m_End_Angle = 0;
	m_RotateAngle = 0;
}

CObjPropertyDlgEdit::~CObjPropertyDlgEdit()
{
}

void CObjPropertyDlgEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT, m_ObjType);
	DDX_Control(pDX, IDC_OBJ_PROTY_DLGEDIT_COMBOX1, m_LayerList1);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT1, m_ProcessSpeed);
	DDV_MinMaxFloat(pDX, m_ProcessSpeed, 0, 999999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT2, m_ProcessTimes);
	DDV_MinMaxByte(pDX, m_ProcessTimes, 0, 255);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT3, m_ProcessMode);
	DDV_MinMaxByte(pDX, m_ProcessMode, 0, 255);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT4, m_ProcessPower);
	DDV_MinMaxFloat(pDX, m_ProcessPower, 0, 100);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT5, m_ProcessFrequncy);
	DDV_MinMaxFloat(pDX, m_ProcessFrequncy, 0, 99999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT6, m_ProcessPulseWidth);
	DDV_MinMaxFloat(pDX, m_ProcessPulseWidth, 0, 999999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT7, m_ProcessWaitTime);
	DDV_MinMaxFloat(pDX, m_ProcessWaitTime, 0, 999999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT8, m_Rise_Lenth_Step);
	DDV_MinMaxFloat(pDX, m_Rise_Lenth_Step, 0, 99);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT9, m_Start_X);
	DDV_MinMaxDouble(pDX, m_Start_X, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT10, m_Start_Y);
	DDV_MinMaxDouble(pDX, m_Start_Y, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT11, m_End_X);
	DDV_MinMaxDouble(pDX, m_End_X, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT12, m_End_Y);
	DDV_MinMaxDouble(pDX, m_End_Y, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT13, m_Center_X);
	DDV_MinMaxDouble(pDX, m_Center_X, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT14, m_Center_Y);
	DDV_MinMaxDouble(pDX, m_Center_Y, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT15, m_Radius);
	DDV_MinMaxDouble(pDX, m_Radius, -9999, 9999);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT16, m_Ratio);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT17, m_Start_Angle);
	DDV_MinMaxDouble(pDX, m_Start_Angle, -360, 360);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT18, m_End_Angle);
	DDV_MinMaxDouble(pDX, m_End_Angle, -360, 360);
	DDX_Text(pDX, IDC_OBJ_PROTY_DLGEDIT_EDIT19, m_RotateAngle);
	DDV_MinMaxDouble(pDX, m_RotateAngle, 0, 360);
}

// 重写
BOOL CObjPropertyDlgEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	POSITION pos;
	CString str;
	BOOL bSLayer, bSType, bSDot;
	CMachineObj_Comm* pObj;
	ObjPoint point;
	int SelectCount, LayerCount;
	int nIndex, nObjType, nObjLayer;
	SelectCount = m_pObjProty->m_PropertyList.GetSelectedCount();
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_COMBOX1)->ShowWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT1)->ShowWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT3)->ShowWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT4)->ShowWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT5)->ShowWindow(TRUE);
	if (gLaserType == IPG_Fiber_Laser)
	{
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT6)->ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC5)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC12)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC13)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC14)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC16)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC18)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC20)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC21)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC22)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC23)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC24)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC25)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC26)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC27)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT7)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT8)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT11)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT12)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT13)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT14)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT15)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT16)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT17)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT18)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT19)->ShowWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN2)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN3)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN4)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN5)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN6)->EnableWindow(TRUE);
	if (SelectCount > 1)
	{
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN7)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN8)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN9)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN11)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN7)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN8)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN9)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN11)->EnableWindow(FALSE);
	}
	if (!m_pObjProty || SelectCount < 1)
		return FALSE;
	LayerCount = m_pObjProty->m_pObjList->GetLayerCount();
	for (int i = 0; i < LayerCount; i++)
	{
		str = m_pObjProty->m_pObjList->GetLayerOfNumber(i)->m_LayerName;
		m_LayerList1.InsertString(i, str);
	}
	bSLayer = TRUE;
	bSType = TRUE;
	bSDot = TRUE;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	nIndex = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
	pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
	nObjType = pObj->GetObjType();
	nObjLayer =pObj->m_ObjByLayer;
	if (nObjType == MachineObj_Type_Point)
	{
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT7)->ShowWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC4)->ShowWindow(SW_SHOW);
		bSDot = FALSE;
		m_ProcessWaitTime = ((CMachineObjPoint*)pObj)->m_MachineWaitTime;
	}
	for (int i = 1; i < SelectCount; i++)
	{
		nIndex = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
		if (nObjType != pObj->GetObjType())
			bSType = FALSE;
		if (nObjLayer != pObj->m_ObjByLayer)
			bSLayer = FALSE;
		if (pObj->GetObjType() == MachineObj_Type_Point)
		{
			GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT7)->ShowWindow(TRUE);
			GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC4)->ShowWindow(SW_SHOW);
			if (bSDot)
			{
				bSDot = FALSE;
				m_ProcessWaitTime = ((CMachineObjPoint*)pObj)->m_MachineWaitTime;
			}
			else if (m_ProcessWaitTime != ((CMachineObjPoint*)pObj)->m_MachineWaitTime)
				m_ProcessWaitTime = -9999;
		}
	}
	str.Format(_T("(%d)"), SelectCount);
	
	if (bSType)
	{
		switch (nObjType)
		{
		case MachineObj_Type_Point:
			str = _T("点") + str;
			GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC3)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT7)->ShowWindow(TRUE);
			GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC4)->ShowWindow(SW_SHOW);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_Line:
			str = _T("直线") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC12)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC13)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC14)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = pObj->GetObjEnd(pObj);
				m_End_X = point.x;
				m_End_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT11)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT12)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_Circle:
			str = _T("园") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC16)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC18)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->SetWindowText(_T("半径"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC20)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = ((CMachineObjCircle*)pObj)->GetCircleCenter();
				m_Center_X = point.x;
				m_Center_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT13)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT14)->ShowWindow(TRUE);
				m_Radius = ((CMachineObjCircle*)pObj)->GetCircleRadius();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT15)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_Arc:
			str = _T("圆弧") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC12)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC13)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC14)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC16)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC18)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->SetWindowText(_T("半径"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC20)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC22)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC24)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC25)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = pObj->GetObjEnd(pObj);
				m_End_X = point.x;
				m_End_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT11)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT12)->ShowWindow(TRUE);
				point = ((CMachineObjArc*)pObj)->GetArcCenter();
				m_Center_X = point.x;
				m_Center_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT13)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT14)->ShowWindow(TRUE);
				m_Radius = ((CMachineObjArc*)pObj)->GetArcRadius();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT15)->ShowWindow(TRUE);
				m_Start_Angle = ((CMachineObjArc*)pObj)->GetStartAngle();
				m_End_Angle = ((CMachineObjArc*)pObj)->GetEndAngle();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT17)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT18)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_Ellipse:
			str = _T("椭圆") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->SetWindowText(_T("中心X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC16)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->SetWindowText(_T("中心Y坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC18)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->SetWindowText(_T("长轴长度"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC20)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC21)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = ((CMachineObjEllipse*)pObj)->GetEllipseCenter();
				m_Center_X = point.x;
				m_Center_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT13)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT14)->ShowWindow(TRUE);
				m_Radius = ((CMachineObjEllipse*)pObj)->GetEllipseXRadius();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT15)->ShowWindow(TRUE);
				m_Ratio = ((CMachineObjEllipse*)pObj)->GetEllipseRatio();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT16)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_ArcEll:
			str = _T("椭圆弧") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC12)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC13)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC14)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->SetWindowText(_T("中心X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC16)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->SetWindowText(_T("中心Y坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC18)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->SetWindowText(_T("长轴长度"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC20)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC21)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC22)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC24)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC25)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = pObj->GetObjEnd(pObj);
				m_End_X = point.x;
				m_End_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT11)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT12)->ShowWindow(TRUE);
				point = ((CMachineObjArcEll*)pObj)->GetEllipseCenter();
				m_Center_X = point.x;
				m_Center_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT13)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT14)->ShowWindow(TRUE);
				m_Radius = ((CMachineObjArcEll*)pObj)->GetEllipseXRadius();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT15)->ShowWindow(TRUE);
				m_Ratio = ((CMachineObjArcEll*)pObj)->GetEllipseRatio();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT16)->ShowWindow(TRUE);
				m_Start_Angle = ((CMachineObjArcEll*)pObj)->GetStartRadian() * 180 / M_PI;
				m_End_Angle = ((CMachineObjArcEll*)pObj)->GetEndRadian() * 180 / M_PI;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT17)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT18)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_TiltEllipse:
			str = _T("斜椭圆") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC12)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC13)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC14)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->SetWindowText(_T("中心X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC15)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC16)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->SetWindowText(_T("中心Y坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC17)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC18)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->SetWindowText(_T("长轴长度"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC19)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC20)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC21)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC22)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC23)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC24)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC25)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC26)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC27)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = pObj->GetObjEnd(pObj);
				m_End_X = point.x;
				m_End_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT11)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT12)->ShowWindow(TRUE);
				point = ((CMachineObjTiltEllipse*)pObj)->GetTiltEllipseCenter();
				m_Center_X = point.x;
				m_Center_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT13)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT14)->ShowWindow(TRUE);
				m_Radius = ((CMachineObjTiltEllipse*)pObj)->GetTiltEllipseXRadius();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT15)->ShowWindow(TRUE);
				m_Ratio = ((CMachineObjTiltEllipse*)pObj)->GetTiltEllipseRatio();
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT16)->ShowWindow(TRUE);
				m_Start_Angle = ((CMachineObjTiltEllipse*)pObj)->GetStartRadian() * 180 / M_PI;
				m_End_Angle = ((CMachineObjTiltEllipse*)pObj)->GetEndRadian() * 180 / M_PI;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT17)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT18)->ShowWindow(TRUE);
				m_RotateAngle = ((CMachineObjTiltEllipse*)pObj)->GetRotateRadian() * 180 / M_PI;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT19)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_Polyline:
			str = _T("多段线") + str;
			pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
			if (SelectCount == 1)
			{
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->SetWindowTextW(_T("起点X坐标"));
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC7)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC8)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC9)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC10)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC12)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC13)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_STATIC14)->ShowWindow(SW_SHOW);
				point = pObj->GetObjStart(pObj);
				m_Start_X = point.x;
				m_Start_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT9)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT10)->ShowWindow(TRUE);
				point = pObj->GetObjEnd(pObj);
				m_End_X = point.x;
				m_End_Y = point.y;
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT11)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_EDIT12)->ShowWindow(TRUE);
				GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN1)->EnableWindow(TRUE);
			}
			break;
		case MachineObj_Type_Group:
			str = _T("群组") + str;
			break;
		default:
			str = "";
			break;
		}
	}
	else
		str = _T("多类型") + str;
	m_ObjType = str;
	if (bSLayer)
	{
		CMachinePara_Layer* pLayer = m_pObjProty->m_pObjList->GetLayerOfNumber(nObjLayer);
		m_ProcessSpeed = pLayer->m_MachinePara.Speed;
		m_ProcessPower = pLayer->m_MachinePara.Power;
		m_ProcessFrequncy = float(pLayer->m_MachinePara.Frequncy) / 1000;
		m_ProcessPulseWidth = pLayer->m_MachinePara.PulseWidth;
		m_ProcessTimes = pLayer->m_MachinePara.Times;
		m_ProcessMode = pLayer->m_MachineMode;
		m_LayerList1.SetCurSel(nObjLayer);
	}
	if (m_LayerList1.GetCurSel() > 0)
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN2)->EnableWindow(TRUE);
	if (m_LayerList1.GetCurSel() > LayerNum_Reserve2)
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN4)->EnableWindow(TRUE);
	UpdateData(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(CObjPropertyDlgEdit, CDialogEx)
	ON_CBN_SELCHANGE(IDC_OBJ_PROTY_DLGEDIT_COMBOX1, &CObjPropertyDlgEdit::OnSelchangeObjProtyDlgeditCombox1)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN2, &CObjPropertyDlgEdit::OnBnClickedChangeObjLayer)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN3, &CObjPropertyDlgEdit::OnBnClickedChangeObjProty)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN4, &CObjPropertyDlgEdit::OnBnClickedChangeLayerProty)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN5, &CObjPropertyDlgEdit::OnBnClickedClearRedundLayer)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN6, &CObjPropertyDlgEdit::OnBnClickedAddNewLayer)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN1, &CObjPropertyDlgEdit::OnBnClickedModifyObj)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN7, &CObjPropertyDlgEdit::OnBnClickedObjPathSort1)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN8, &CObjPropertyDlgEdit::OnBnClickedObjPathSort2)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN9, &CObjPropertyDlgEdit::OnBnClickedObjPathSort3)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN10, &CObjPropertyDlgEdit::OnBnClickedObjPathSort4)
	ON_BN_CLICKED(IDC_OBJ_PROTY_DLGEDIT_BTN11, &CObjPropertyDlgEdit::OnBnClickedObjPathSort5)
END_MESSAGE_MAP()


// CObjPropertyDlgEdit 消息处理程序

void CObjPropertyDlgEdit::OnSelchangeObjProtyDlgeditCombox1()
{
	int nSel = m_LayerList1.GetCurSel();
	if (nSel > LayerNum_Reserve2)
	{
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN2)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN4)->EnableWindow(TRUE);
		if (nSel < m_pObjProty->m_pObjList->GetLayerCount())
		{
			CMachinePara_Layer* pLayer = m_pObjProty->m_pObjList->GetLayerOfNumber(nSel);
			m_ProcessSpeed = pLayer->m_MachinePara.Speed;
			m_ProcessPower = pLayer->m_MachinePara.Power;
			m_ProcessFrequncy = float(pLayer->m_MachinePara.Frequncy) / 1000;
			m_ProcessPulseWidth = pLayer->m_MachinePara.PulseWidth;
			m_ProcessTimes = pLayer->m_MachinePara.Times;
			m_ProcessMode = pLayer->m_MachineMode;
		}
	}
	else if (nSel >= 0)
	{
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN2)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN4)->EnableWindow(FALSE);
		CMachinePara_Layer* pLayer = m_pObjProty->m_pObjList->GetLayerOfNumber(0);
		m_ProcessSpeed = pLayer->m_MachinePara.Speed;
		m_ProcessPower = pLayer->m_MachinePara.Power;
		m_ProcessFrequncy = float(pLayer->m_MachinePara.Frequncy) / 1000;
		m_ProcessPulseWidth = pLayer->m_MachinePara.PulseWidth;
		m_ProcessTimes = pLayer->m_MachinePara.Times;
		m_ProcessMode = pLayer->m_MachineMode;
	}
	UpdateData(FALSE);
}

void CObjPropertyDlgEdit::OnBnClickedChangeObjLayer()
{
	int nSel = m_LayerList1.GetCurSel();
	if (nSel > LayerNum_Mark && nSel < LayerNum_Default)
	{
		MessageBox(_T("无效的图层!"));
		return;
	}
	POSITION pos;
	CMachineObj_Comm* pObj;
	int SelectCount, nIndex, nIndex_rev1, nIndex_rev2;
	int nBorderCount, nMarkCount, nBorderCount1, nMarkCount1, Old_Layer, nType;
	nBorderCount = 0;
	nMarkCount = 0;
	nIndex_rev1 = 0;
	nIndex_rev2 = 0;
	pos = m_pObjProty->m_pObjList->GetObjHeadPosition();
	while (pos)
	{
		pObj = m_pObjProty->m_pObjList->GetObjNext(pos);
		if (pObj->m_ObjByLayer == LayerNum_Border)
		{
			nBorderCount++;
			nMarkCount++;
		}
		else if (pObj->m_ObjByLayer == LayerNum_Mark)
		{
			nMarkCount++;
		}
		else
			break;
	}
	nBorderCount1 = nBorderCount;
	nMarkCount1 = nMarkCount;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	SelectCount = m_pObjProty->m_PropertyList.GetSelectedCount();
	for (int i = 0; i < SelectCount; i++)
	{
		nIndex = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		if (nIndex < nBorderCount1)
			nIndex = nIndex - nIndex_rev1;
		else if (nIndex < nMarkCount1)
			nIndex = nIndex - nIndex_rev1 - nIndex_rev2;

		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(nIndex);
		Old_Layer = pObj->m_ObjByLayer;
		nType = pObj->GetObjType();
		if (nSel == LayerNum_Border && (Old_Layer == LayerNum_Mark || Old_Layer >= LayerNum_Default))
		{
			if (nType != MachineObj_Type_Point && nType != MachineObj_Type_Group)
			{
				pObj->m_ObjByLayer = nSel;
				m_pObjProty->m_pObjList->RemoveObjAtIndex(nIndex);
				m_pObjProty->m_pObjList->InsertObjAtIndex(nBorderCount, pObj);
				nBorderCount++;
				nMarkCount++;
			}
		}
		else if (nSel == LayerNum_Mark && (Old_Layer == LayerNum_Border || Old_Layer >= LayerNum_Default))
		{
			if (nType != MachineObj_Type_Point && nType != MachineObj_Type_Group)
			{
				pObj->m_ObjByLayer = nSel;
				if (Old_Layer == LayerNum_Border)
				{
					m_pObjProty->m_pObjList->InsertObjAtIndex(nMarkCount, pObj);
					m_pObjProty->m_pObjList->RemoveObjAtIndex(nIndex);
					nBorderCount--;
					nIndex_rev1++;
				}
				else
				{
					m_pObjProty->m_pObjList->RemoveObjAtIndex(nIndex);
					m_pObjProty->m_pObjList->InsertObjAtIndex(nMarkCount, pObj);
					nMarkCount++;
				}
			}
		}
		else if (nSel >= LayerNum_Default)
		{
			if (nType != MachineObj_Type_Group)
			{
				pObj->m_ObjByLayer = nSel;
				if (Old_Layer == LayerNum_Border)
				{
					m_pObjProty->m_pObjList->InsertObjAtIndex(nMarkCount + nIndex_rev1, pObj);
					m_pObjProty->m_pObjList->RemoveObjAtIndex(nIndex);
					nBorderCount--;
					nMarkCount--;
					nIndex_rev1++;
				}
				else if (Old_Layer == LayerNum_Mark)
				{
					m_pObjProty->m_pObjList->InsertObjAtIndex(nMarkCount + nIndex_rev1 + nIndex_rev2, pObj);
					m_pObjProty->m_pObjList->RemoveObjAtIndex(nIndex);
					nMarkCount--;
					nIndex_rev2++;
				}
			}
		}
	}
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN7)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN8)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN9)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN10)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJ_PROTY_DLGEDIT_BTN11)->EnableWindow(FALSE);
	return;
}

void CObjPropertyDlgEdit::OnBnClickedChangeObjProty()
{
	ProcessPara para1;
	int nLayer;
	if (!UpdateData(TRUE))
		return;
	para1.Frequncy = UINT(m_ProcessFrequncy * 1000);
	para1.Power = m_ProcessPower;
	para1.PulseWidth = m_ProcessPulseWidth;
	para1.Speed = m_ProcessSpeed;
	para1.Times = m_ProcessTimes;
	if (!m_pObjProty->m_pDoc->Check_Process_Para1(para1, m_ProcessMode))
	{
		MessageBox(_T("加工参数超出限定范围!"));
		return;
	}
	if (!m_pObjProty->m_pDoc->Check_Process_Para2(m_ProcessWaitTime))
	{
		MessageBox(_T("加工参数超出限定范围!"));
		return;
	}
	nLayer = m_pObjProty->m_pObjList->FindLayerByPara(para1, m_ProcessMode);
	if (nLayer > 0 && nLayer < LayerNum_Default)
		return;
	else if (nLayer < 0)
	{
		CString str;
		nLayer = m_pObjProty->m_pObjList->GetLayerCount();
		str.Format(_T("Para%d"), nLayer - LayerNum_Default + 1);
		CMachinePara_Layer* pLayer = new CMachinePara_Layer(str, m_ProcessMode, para1);
		m_pObjProty->m_pObjList->AddLayer(pLayer);
		m_LayerList1.InsertString(nLayer, str);
	}
	m_LayerList1.SetCurSel(nLayer);
	POSITION pos;
	int Index;
	CMachineObj_Comm* pObj;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(Index);
		if (pObj->m_ObjByLayer >= LayerNum_Default && pObj->GetObjType() != MachineObj_Type_Group)
			pObj->m_ObjByLayer = nLayer;
		if (pObj->GetObjType() == MachineObj_Type_Point)
			((CMachineObjPoint*)pObj)->m_MachineWaitTime = m_ProcessWaitTime;
	}
}

void CObjPropertyDlgEdit::OnBnClickedChangeLayerProty()
{
	ProcessPara para1;
	if (!UpdateData(TRUE))
		return;
	para1.Frequncy = UINT(m_ProcessFrequncy * 1000);
	para1.Power = m_ProcessPower;
	para1.PulseWidth = m_ProcessPulseWidth;
	para1.Speed = m_ProcessSpeed;
	para1.Times = m_ProcessTimes;
	if (!m_pObjProty->m_pDoc->Check_Process_Para1(para1, m_ProcessMode)
		|| !m_pObjProty->m_pDoc->Check_Process_Para2(m_ProcessWaitTime))
	{
		MessageBox(_T("加工参数超出限定范围!"));
		return;
	}
	int nSel = m_LayerList1.GetCurSel();
	if (nSel < LayerNum_Default)
	{
		MessageBox(_T("该层属性不可修改!"));
		return;
	}
	CMachinePara_Layer* pLayer;
	pLayer = m_pObjProty->m_pObjList->GetLayerOfNumber(nSel);
	pLayer->m_MachinePara = para1;
	pLayer->m_MachineMode = m_ProcessMode;
	return;
}

void CObjPropertyDlgEdit::OnBnClickedClearRedundLayer()
{
	int nSel, mode;
	ProcessPara para;
	nSel = m_LayerList1.GetCurSel();
	if (nSel >= LayerNum_Default)
	{
		para = m_pObjProty->m_pObjList->GetLayerOfNumber(nSel)->m_MachinePara;
		mode = m_pObjProty->m_pObjList->GetLayerOfNumber(nSel)->m_MachineMode;
	}
	m_pObjProty->m_pObjList->ClearRedundLayer();
	CString str;
	int LayerCount = m_pObjProty->m_pObjList->GetLayerCount();
	m_LayerList1.ResetContent();
	for (int i = 0; i < LayerCount; i++)
	{
		str = m_pObjProty->m_pObjList->GetLayerOfNumber(i)->m_LayerName;
		m_LayerList1.InsertString(i, str);
	}
	if (nSel >= 0)
	{
		if (nSel >= LayerNum_Default)
			nSel = m_pObjProty->m_pObjList->FindLayerByPara(para, mode);
		m_LayerList1.SetCurSel(nSel);
	}
}

void CObjPropertyDlgEdit::OnBnClickedAddNewLayer()
{
	ProcessPara para;
	if (!UpdateData(TRUE))
		return;
	para.Frequncy = UINT(m_ProcessFrequncy * 1000);
	para.Power = m_ProcessPower;
	para.PulseWidth = m_ProcessPulseWidth;
	para.Speed = m_ProcessSpeed;
	para.Times = m_ProcessTimes;
	if (!m_pObjProty->m_pDoc->Check_Process_Para1(para, m_ProcessMode)
		|| !m_pObjProty->m_pDoc->Check_Process_Para2(m_ProcessWaitTime))
	{
		MessageBox(_T("加工参数超出限定范围!"));
		return;
	}
	CString str;
	CMachinePara_Layer* pLayer;
	int nLayer = m_LayerList1.GetCount();
	str.Format(_T("Para%d"), nLayer - LayerNum_Default + 1);
	pLayer = new CMachinePara_Layer(str, m_ProcessMode, para);
	m_pObjProty->m_pObjList->AddLayer(pLayer);
	m_LayerList1.ResetContent();
	for (int i = 0; i < nLayer + 1; i++)
	{
		str = m_pObjProty->m_pObjList->GetLayerOfNumber(i)->m_LayerName;
		m_LayerList1.InsertString(i, str);
	}
	MessageBox(_T("成功添加新层") + str);
	m_LayerList1.SetCurSel(nLayer);
}

void CObjPropertyDlgEdit::OnBnClickedModifyObj()
{
	if (m_pObjProty->m_PropertyList.GetSelectedCount() != 1)
		return;
	ObjPoint point;
	ObjVPoint vpoint;
	double old_Start_X = m_Start_X;
	double old_Start_Y = m_Start_Y;
	double old_End_X = m_End_X;
	double old_End_Y = m_End_Y;
	double old_Center_X = m_Center_X;
	double old_Center_Y = m_Center_Y;
	double old_Radius = m_Radius;
	double old_Start_Angle = m_Start_Angle;
	double old_End_Angle = m_End_Angle;
	double old_Ratio = m_Ratio;
	double old_RotateAngle = m_RotateAngle;
	if (!UpdateData(TRUE))
		return;
	POSITION pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	int sel = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
	CMachineObj_Comm* pObj = m_pObjProty->m_pObjList->GetObjAtIndex(sel);
	ObjRect new_rect, old_rect;

	switch (pObj->GetObjType())
	{
	case MachineObj_Type_Point:
		CMachineObjPoint* pPoint;
		pPoint = (CMachineObjPoint*)pObj;
		if (abs(m_Start_X - old_Start_X) > Zero
			|| abs(m_Start_Y - old_Start_Y) > Zero)
		{
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pPoint->SetPoint(ObjPoint(m_Start_X, m_Start_Y));
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		break;
	case MachineObj_Type_Line:
		CMachineObjLine* pLine;
		pLine = (CMachineObjLine*)pObj;
		if (abs(m_Start_X - old_Start_X) > Zero
			|| abs(m_Start_Y - old_Start_Y) > Zero
			|| abs(m_End_X - old_End_X) > Zero
			|| abs(m_End_Y - old_End_Y) > Zero)
		{
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pLine->SetLine(ObjPoint(m_Start_X, m_Start_Y), ObjPoint(m_End_X, m_End_Y));
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		break;
	case MachineObj_Type_Circle:
		CMachineObjCircle* pCircle;
		pCircle = (CMachineObjCircle*)pObj;
		if ((abs(m_Center_X - old_Center_X) > Zero || abs(m_Center_Y - old_Center_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero)
		{
			//中心修改,起点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pCircle->SetCircleRadius(m_Radius);
			pCircle->MoveCircleCenter(ObjPoint(m_Center_X, m_Center_Y));
			point = pCircle->GetCircleStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero)
		{
			//起点修改,中心未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pCircle->SetCircleRadius(m_Radius);
			pCircle->MoveCircleStart(ObjPoint(m_Start_X, m_Start_Y));
			point = pCircle->GetCircleCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if (abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Radius - old_Radius) > Zero)
		{
			//起点和中心均未修改,半径修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pCircle->SetCircleRadius(m_Radius);
			point = pCircle->GetCircleStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Center_X -old_Center_X) > Zero || abs(m_Center_Y -old_Center_Y) > Zero)
			&& (abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero))
		{
			//起点和中心均修改,无效
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			MessageBox(_T("不可同时改变圆心和起点坐标!"));
			point = pCircle->GetCircleStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pCircle->GetCircleCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Radius = pCircle->GetCircleRadius();
			UpdateData(FALSE);
			new_rect = old_rect;
		}
		else
		{
			//无修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			new_rect = old_rect;
		}
		break;
	case MachineObj_Type_Arc:
		CMachineObjArc* pArc;
		pArc = (CMachineObjArc*)pObj;
		if ((abs(m_Center_X - old_Center_X) > Zero || abs(m_Center_Y - old_Center_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//中心修改,起点终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArc->MoveArcCenter(ObjPoint(m_Center_X, m_Center_Y));
			pArc->SetArcRadius(m_Radius);
			pArc->SetStartAndEndAngle(m_Start_Angle, m_End_Angle);
			point = pArc->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArc->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			m_Start_Angle = pArc->GetStartAngle();
			m_End_Angle = pArc->GetEndAngle();
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//起点修改,中心终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArc->SetArcRadius(m_Radius);
			pArc->SetStartAndEndAngle(m_Start_Angle, m_End_Angle);
			pArc->MoveArcStart(ObjPoint(m_Start_X, m_Start_Y));
			point = pArc->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			point = pArc->GetArcCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Start_Angle = pArc->GetStartAngle();
			m_End_Angle = pArc->GetEndAngle();
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_End_X - old_End_X) > Zero || abs(m_End_Y - old_End_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero)
		{
			//终点修改,起点中心未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArc->SetArcRadius(m_Radius);
			pArc->SetStartAndEndAngle(m_Start_Angle, m_End_Angle);
			pArc->MoveArcEnd(ObjPoint(m_End_X, m_End_Y));
			point = pArc->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArc->GetArcCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Start_Angle = pArc->GetStartAngle();
			m_End_Angle = pArc->GetEndAngle();
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Radius - old_Radius) > Zero || abs(m_Start_Angle - old_Start_Angle) > Zero || abs(m_End_Angle - old_End_Angle) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//中心起点终点均未修改,但其他修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArc->SetArcRadius(m_Radius);
			pArc->SetStartAndEndAngle(m_Start_Angle, m_End_Angle);
			point = pArc->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArc->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			m_Start_Angle = pArc->GetStartAngle();
			m_End_Angle = pArc->GetEndAngle();
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if (abs(m_Radius - old_Radius) < Zero && abs(m_Start_Angle - old_Start_Angle) < Zero && abs(m_End_Angle - old_End_Angle) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//所有无修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			new_rect = old_rect;
		}
		else
		{
			//无效的修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			MessageBox(_T("不可同时改变圆心,起点,终点坐标!"));
			point = pArc->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArc->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			point = pArc->GetArcCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Radius = pArc->GetArcRadius();
			m_Start_Angle = pArc->GetStartAngle();
			m_End_Angle = pArc->GetEndAngle();
			UpdateData(FALSE);
			new_rect = old_rect;
		}
		break;
	case MachineObj_Type_Ellipse:
		CMachineObjEllipse* pEllipse;
		pEllipse = (CMachineObjEllipse*)pObj;
		if ((abs(m_Center_X - old_Center_X) > Zero || abs(m_Center_Y - old_Center_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero)
		{
			//中心修改,起点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pEllipse->SetEllipseXradius(m_Radius);
			pEllipse->SetEllipseRatio(m_Ratio);
			pEllipse->MoveEllipseCenter(ObjPoint(m_Center_X, m_Center_Y));
			point = pEllipse->GetEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero)
		{
			//起点修改,中心未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pEllipse->SetEllipseXradius(m_Radius);
			pEllipse->SetEllipseRatio(m_Ratio);
			pEllipse->MoveEllipseStart(ObjPoint(m_Start_X, m_Start_Y));
			point = pEllipse->GetEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if (abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& (abs(m_Radius - old_Radius) > Zero) || (abs(m_Ratio - old_Ratio) > Zero))
		{
			//起点和中心均未修改,半径或比率修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pEllipse->SetEllipseXradius(m_Radius);
			pEllipse->SetEllipseRatio(m_Ratio);
			point = pEllipse->GetEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Center_X - old_Center_X) > Zero || abs(m_Center_Y - old_Center_Y) > Zero)
			&& (abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero))
		{
			//起点和中心均修改,无效
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			MessageBox(_T("不可同时改变中心和起点坐标!"));
			point = pEllipse->GetEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pEllipse->GetEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Radius = pEllipse->GetEllipseXRadius();
			m_Ratio = pEllipse->GetEllipseRatio();
			UpdateData(FALSE);
			new_rect = old_rect;
		}
		else
		{
			//无修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			new_rect = old_rect;
		}
		break;
	case MachineObj_Type_ArcEll:
		CMachineObjArcEll* pArcEll;
		pArcEll = (CMachineObjArcEll*)pObj;
		if ((abs(m_Center_X - old_Center_X) > Zero || abs(m_Center_Y - old_Center_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//中心修改,起点终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArcEll->MovetEllipseCenter(ObjPoint(m_Center_X, m_Center_Y));
			pArcEll->SetEllipseXradius(m_Radius);
			pArcEll->SetEllipseRatio(m_Ratio);
			pArcEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			point = pArcEll->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArcEll->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			m_Start_Angle = pArcEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pArcEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//起点修改,中心终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArcEll->SetEllipseXradius(m_Radius);
			pArcEll->SetEllipseRatio(m_Ratio);
			pArcEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			pArcEll->MoveArcStart(ObjPoint(m_Start_X, m_Start_Y));
			point = pArcEll->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			point = pArcEll->GetEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Start_Angle = pArcEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pArcEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_End_X - old_End_X) > Zero || abs(m_End_Y - old_End_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero)
		{
			//终点修改,起点中心未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArcEll->SetEllipseXradius(m_Radius);
			pArcEll->SetEllipseRatio(m_Ratio);
			pArcEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			pArcEll->MoveArcEnd(ObjPoint(m_End_X, m_End_Y));
			point = pArcEll->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArcEll->GetEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Start_Angle = pArcEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pArcEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Radius - old_Radius) > Zero || abs(m_Ratio - old_Ratio) > Zero
			|| abs(m_Start_Angle - old_Start_Angle) > Zero || abs(m_End_Angle - old_End_Angle) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//中心起点终点均未修改,但其他修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pArcEll->SetEllipseXradius(m_Radius);
			pArcEll->SetEllipseRatio(m_Ratio);
			pArcEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			point = pArcEll->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArcEll->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			m_Start_Angle = pArcEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pArcEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if (abs(m_Radius - old_Radius) < Zero &&abs(m_Ratio - old_Ratio) < Zero
			&& abs(m_Start_Angle - old_Start_Angle) < Zero && abs(m_End_Angle - old_End_Angle) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//所有无修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			new_rect = old_rect;
		}
		else
		{
			//无效的修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			MessageBox(_T("不可同时改变圆心,起点,终点坐标!"));
			point = pArcEll->GetArcStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pArcEll->GetArcEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			point = pArcEll->GetEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Radius = pArcEll->GetEllipseXRadius();
			m_Ratio = pArcEll->GetEllipseRatio();
			m_Start_Angle = pArcEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pArcEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = old_rect;
		}
		break;
	case MachineObj_Type_TiltEllipse:
		CMachineObjTiltEllipse* pTiltEll;
		pTiltEll = (CMachineObjTiltEllipse*)pObj;
		if ((abs(m_Center_X - old_Center_X) > Zero || abs(m_Center_Y - old_Center_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//中心修改,起点终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pTiltEll->MoveTiltEllipseCenter(ObjPoint(m_Center_X, m_Center_Y));
			pTiltEll->SetTiltEllipseXRadius(m_Radius);
			pTiltEll->SetTiltEllipseRatio(m_Ratio);
			pTiltEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			pTiltEll->SetRotateRadian(m_RotateAngle / 180 * M_PI);
			point = pTiltEll->GetTiltEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pTiltEll->GetTiltEllipseEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			m_Start_Angle = pTiltEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pTiltEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//起点修改,中心终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pTiltEll->SetTiltEllipseXRadius(m_Radius);
			pTiltEll->SetTiltEllipseRatio(m_Ratio);
			pTiltEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			pTiltEll->SetRotateRadian(m_RotateAngle / 180 * M_PI);
			pTiltEll->MoveTiltEllipseStart(ObjPoint(m_Start_X, m_Start_Y));
			point = pTiltEll->GetTiltEllipseEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			point = pTiltEll->GetTiltEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Start_Angle = pTiltEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pTiltEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_End_X - old_End_X) > Zero || abs(m_End_Y - old_End_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero)
		{
			//终点修改,起点中心未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pTiltEll->SetTiltEllipseXRadius(m_Radius);
			pTiltEll->SetTiltEllipseRatio(m_Ratio);
			pTiltEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			pTiltEll->SetRotateRadian(m_RotateAngle / 180 * M_PI);
			pTiltEll->MoveTiltEllipseEnd(ObjPoint(m_Start_X, m_Start_Y));
			point = pTiltEll->GetTiltEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pTiltEll->GetTiltEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Start_Angle = pTiltEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pTiltEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if ((abs(m_Radius - old_Radius) > Zero || abs(m_Ratio - old_Ratio) > Zero || abs(m_RotateAngle - old_RotateAngle) > Zero
			|| abs(m_Start_Angle - old_Start_Angle) > Zero || abs(m_End_Angle - old_End_Angle) > Zero)
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//中心起点终点均未修改,但其他修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pTiltEll->SetTiltEllipseXRadius(m_Radius);
			pTiltEll->SetTiltEllipseRatio(m_Ratio);
			pTiltEll->SetStartAndEndRadian(m_Start_Angle / 180 * M_PI, m_End_Angle / 180 * M_PI);
			pTiltEll->SetRotateRadian(m_RotateAngle / 180 * M_PI);
			point = pTiltEll->GetTiltEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pTiltEll->GetTiltEllipseEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			m_Start_Angle = pTiltEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pTiltEll->GetEndRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound(TRUE);
		}
		else if (abs(m_Radius - old_Radius) < Zero &&abs(m_Ratio - old_Ratio) < Zero && abs(m_RotateAngle - old_RotateAngle) < Zero
			&& abs(m_Start_Angle - old_Start_Angle) < Zero && abs(m_End_Angle - old_End_Angle) < Zero
			&& abs(m_Center_X - old_Center_X) < Zero && abs(m_Center_Y - old_Center_Y) < Zero
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//所有无修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			new_rect = old_rect;
		}
		else
		{
			//无效的修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			MessageBox(_T("不可同时改变中心,起点,终点坐标!"));
			pTiltEll->SetRotateRadian(m_RotateAngle / 180 * M_PI);
			point = pTiltEll->GetTiltEllipseStart();
			m_Start_X = point.x;
			m_Start_Y = point.y;
			point = pTiltEll->GetTiltEllipseEnd();
			m_End_X = point.x;
			m_End_Y = point.y;
			point = pTiltEll->GetTiltEllipseCenter();
			m_Center_X = point.x;
			m_Center_Y = point.y;
			m_Radius = pTiltEll->GetTiltEllipseXRadius();
			m_Ratio = pTiltEll->GetTiltEllipseRatio();
			m_Start_Angle = pTiltEll->GetStartRadian() / M_PI * 180;
			m_End_Angle = pTiltEll->GetEndRadian() / M_PI * 180;
			m_RotateAngle = pTiltEll->GetRotateRadian() / M_PI * 180;
			UpdateData(FALSE);
			new_rect = old_rect;
		}
		break;
	case MachineObj_Type_Polyline:
		CMachineObjPolyline* pPolyline;
		pPolyline = (CMachineObjPolyline*)pObj;
		if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& abs(m_End_X - old_End_X) < Zero && abs(m_End_Y - old_End_Y) < Zero)
		{
			//起点修改,终点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pPolyline->MovePolylineStart(ObjPoint(m_Start_X, m_Start_Y));
			vpoint = pPolyline->GetPolylineEnd();
			m_End_X = vpoint.x;
			m_End_Y = vpoint.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound();
			break;
		}
		else if ((abs(m_End_X - old_End_X) > Zero || abs(m_End_Y - old_End_Y) > Zero)
			&& abs(m_Start_X - old_Start_X) < Zero && abs(m_Start_Y - old_Start_Y) < Zero)
		{
			//终点修改,起点未修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			pPolyline->MovePolylineEnd(ObjPoint(m_End_X, m_End_Y));
			vpoint = pPolyline->GetPolylineStart();
			m_Start_X = vpoint.x;
			m_Start_Y = vpoint.y;
			UpdateData(FALSE);
			new_rect = m_pObjProty->m_pObjList->GetObjBound();
			break;
		}
		else if ((abs(m_Start_X - old_Start_X) > Zero || abs(m_Start_Y - old_Start_Y) > Zero)
			&& (abs(m_End_X - old_End_X) > Zero || abs(m_End_Y - old_End_Y) > Zero))
		{
			//起点终点均修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			MessageBox(_T("不可同时改变起点和终点坐标!"));
			vpoint = pPolyline->GetPolylineStart();
			m_Start_X = vpoint.x;
			m_Start_Y = vpoint.y;
			vpoint = pPolyline->GetPolylineEnd();
			m_End_X = vpoint.x;
			m_End_Y = vpoint.y;
			UpdateData(FALSE);
			new_rect = old_rect;
			break;
		}
		else
		{
			//无修改
			old_rect = m_pObjProty->m_pObjList->GetObjBound();
			new_rect = old_rect;
		}
		break;
	default:
		old_rect = m_pObjProty->m_pObjList->GetObjBound();
		new_rect = old_rect;
		break;
	}

	if (old_rect.max_x != new_rect.max_x || old_rect.max_y != new_rect.max_y
		|| old_rect.min_x != new_rect.min_x || old_rect.min_y != new_rect.min_y)
		m_bSizeChanged = TRUE;
	return;
}

void CObjPropertyDlgEdit::OnBnClickedObjPathSort1()
{
	int Index, Index1, Count, nType;
	CMachineObjList* pObjList;
	CMachineObj_Comm* pObj;
	BOOL bFirstIndex = FALSE;
	POSITION pos, pos1, pos2;
	ObjPoint point, point1, point2;
	pObjList = new CMachineObjList;
	Count = 0;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(Index - Count);
		if (pObj->m_ObjByLayer >= LayerNum_Default && pObj->GetObjType() != MachineObj_Type_Group)
		{
			if (!bFirstIndex)
			{
				bFirstIndex = TRUE;
				Index1 = Index;
			}
			m_pObjProty->m_pObjList->RemoveObjAtIndex(Index - Count);
			pObjList->AddTail(pObj);
			Count++;
		}
	}
	Count = pObjList->GetCount();
	for (int i = 0; i < Count; i++)
	{
		pos = pObjList->GetHeadPosition();
		pos2 = pos;
		point = ObjPoint(100000, 100000);
		while (pos)
		{
			pos1 = pos;
			pObj = pObjList->GetNext(pos);
			nType = pObj->GetObjType();
			if (nType == MachineObj_Type_Point
				|| nType == MachineObj_Type_Circle
				|| nType == MachineObj_Type_Ellipse)
			{
				point1 = pObj->GetObjStart(pObj);
				if (point1.y < point.y)
				{
					point = point1;
					pos2 = pos1;
				}
				else if (abs(point1.y - point.y) < Zero)
				{
					if (point1.x < point.x)
					{
						point = point1;
						pos2 = pos1;
					}
				}
			}
			else
			{
				point1 = pObj->GetObjStart(pObj);
				point2 = pObj->GetObjEnd(pObj);
				if ((point1.y < point.y) && (point2.x > point1.x))
				{
					point = point1;
					pos2 = pos1;
				}
				else if (abs(point1.y - point.y) < Zero && (point2.x > point1.x))
				{
					if (point1.x < point.x)
					{
						point = point1;
						pos2 = pos1;
					}
				}
				if ((point2.y < point.y) && (point1.x > point2.x))
				{
					pObj = pObj->ExchangeStartAndEnd(pObj);
					point = point2;
					pos2 = pos1;
				}
				else if (abs(point2.y - point.y) < Zero && (point1.x > point2.x))
				{
					if (point2.x < point.x)
					{
						pObj = pObj->ExchangeStartAndEnd(pObj);
						point = point2;
						pos2 = pos1;
					}
				}
			}
		}
		pObj = pObjList->GetAt(pos2);
		pObjList->RemoveAt(pos2);
		m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
		Index1++;
	}
	delete pObjList;
	pObjList = NULL;
	MessageBox(_T("排序完成!"));
	OnOK();
}

void CObjPropertyDlgEdit::OnBnClickedObjPathSort2()
{
	int Index, Index1, Count, nType;
	CMachineObjList* pObjList;
	CMachineObj_Comm* pObj;
	BOOL bFirstIndex = FALSE, bFwd, bFlag;
	POSITION pos, pos1, pos2;
	ObjPoint point, point1, point2, point3;
	pObjList = new CMachineObjList;
	Count = 0;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(Index - Count);
		if (pObj->m_ObjByLayer >= LayerNum_Default && pObj->GetObjType() != MachineObj_Type_Group)
		{
			if (!bFirstIndex)
			{
				bFirstIndex = TRUE;
				Index1 = Index;
			}
			m_pObjProty->m_pObjList->RemoveObjAtIndex(Index - Count);
			pObjList->AddTail(pObj);
			Count++;
		}
	}
	Count = pObjList->GetCount();
	bFwd = TRUE;
	bFlag = FALSE;
	point3 = ObjPoint(0, 0);
	for (int i = 0; i < Count; i++)
	{
		pos = pObjList->GetHeadPosition();
		pos2 = pos;
		if (bFwd)
			point = ObjPoint(100000, 100000);
		else
			point = ObjPoint(-100000, 100000);
		while (pos)
		{
			pos1 = pos;
			pObj = pObjList->GetNext(pos);
			nType = pObj->GetObjType();
			if (bFwd)
			{
				//顺向
				if (nType == MachineObj_Type_Point
					|| nType == MachineObj_Type_Circle
					|| nType == MachineObj_Type_Ellipse)
				{
					point1 = pObj->GetObjStart(pObj);
					if (point1.y < point.y)
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.y - point.y) < Zero)
					{
						if (point1.x < point.x)
						{
							point = point1;
							pos2 = pos1;
						}
					}
				}
				else
				{
					point1 = pObj->GetObjStart(pObj);
					point2 = pObj->GetObjEnd(pObj);
					if ((point1.y < point.y) && (point2.x > point1.x))
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.y - point.y) < Zero && (point2.x > point1.x))
					{
						if (point1.x < point.x)
						{
							point = point1;
							pos2 = pos1;
						}
					}
					if ((point2.y < point.y) && (point1.x > point2.x))
					{
						pObj = pObj->ExchangeStartAndEnd(pObj);
						point = point2;
						pos2 = pos1;
					}
					else if (abs(point2.y - point.y) < Zero && (point1.x > point2.x))
					{
						if (point2.x < point.x)
						{
							pObj = pObj->ExchangeStartAndEnd(pObj);
							point = point2;
							pos2 = pos1;
						}
					}
				}
			}
			else
			{
				//反向
				if (nType == MachineObj_Type_Point
					|| nType == MachineObj_Type_Circle
					|| nType == MachineObj_Type_Ellipse)
				{
					point1 = pObj->GetObjStart(pObj);
					if (point1.y < point.y)
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.y - point.y) < Zero)
					{
						if (point1.x > point.x)
						{
							point = point1;
							pos2 = pos1;
						}
					}
				}
				else
				{
					point1 = pObj->GetObjStart(pObj);
					point2 = pObj->GetObjEnd(pObj);
					if ((point1.y < point.y) && (point2.x < point1.x))
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.y - point.y) < Zero && (point2.x < point1.x))
					{
						if (point1.x > point.x)
						{
							point = point1;
							pos2 = pos1;
						}
					}
					if ((point2.y < point.y) && (point1.x < point2.x))
					{
						pObj = pObj->ExchangeStartAndEnd(pObj);
						point = point2;
						pos2 = pos1;
					}
					else if (abs(point2.y - point.y) < Zero && (point1.x < point2.x))
					{
						if (point2.x > point.x)
						{
							pObj = pObj->ExchangeStartAndEnd(pObj);
							point = point2;
							pos2 = pos1;
						}
					}
				}
			}
		}
		if (!bFlag)
		{
			pObj = pObjList->GetAt(pos2);
			pObjList->RemoveAt(pos2);
			m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
			Index1++;
			point3 = pObj->GetObjStart(pObj);			
			bFlag = TRUE;
		}
		else
		{
			pObj = pObjList->GetAt(pos2);
			point1 = pObj->GetObjStart(pObj);
			if (abs(point1.y - point3.y) < Zero)
			{
				pObjList->RemoveAt(pos2);
				m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
				Index1++;
			}
			else
			{
				bFwd = !bFwd;
				bFlag = FALSE;
				i--;
			}
		}
	}
	delete pObjList;
	pObjList = NULL;
	MessageBox(_T("排序完成!"));
	OnOK();
}

void CObjPropertyDlgEdit::OnBnClickedObjPathSort3()
{
	int Index, Index1, Count, nType;
	CMachineObjList* pObjList;
	CMachineObj_Comm* pObj;
	BOOL bFirstIndex = FALSE;
	POSITION pos, pos1, pos2;
	ObjPoint point, point1, point2;
	pObjList = new CMachineObjList;
	Count = 0;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(Index - Count);
		if (pObj->m_ObjByLayer >= LayerNum_Default && pObj->GetObjType() != MachineObj_Type_Group)
		{
			if (!bFirstIndex)
			{
				bFirstIndex = TRUE;
				Index1 = Index;
			}
			m_pObjProty->m_pObjList->RemoveObjAtIndex(Index - Count);
			pObjList->AddTail(pObj);
			Count++;
		}
	}
	Count = pObjList->GetCount();
	for (int i = 0; i < Count; i++)
	{
		pos = pObjList->GetHeadPosition();
		pos2 = pos;
		point = ObjPoint(100000, 100000);
		while (pos)
		{
			pos1 = pos;
			pObj = pObjList->GetNext(pos);
			nType = pObj->GetObjType();
			if (nType == MachineObj_Type_Point
				|| nType == MachineObj_Type_Circle
				|| nType == MachineObj_Type_Ellipse)
			{
				point1 = pObj->GetObjStart(pObj);
				if (point1.x < point.x)
				{
					point = point1;
					pos2 = pos1;
				}
				else if (abs(point1.x - point.x) < Zero)
				{
					if (point1.y < point.y)
					{
						point = point1;
						pos2 = pos1;
					}
				}
			}
			else
			{
				point1 = pObj->GetObjStart(pObj);
				point2 = pObj->GetObjEnd(pObj);
				if ((point1.x < point.x) && (point2.y > point1.y))
				{
					point = point1;
					pos2 = pos1;
				}
				else if (abs(point1.x - point.x) < Zero && (point2.y > point1.y))
				{
					if (point1.y < point.y)
					{
						point = point1;
						pos2 = pos1;
					}
				}
				if ((point2.x < point.x) && (point1.y > point2.y))
				{
					pObj = pObj->ExchangeStartAndEnd(pObj);
					point = point2;
					pos2 = pos1;
				}
				else if (abs(point2.x - point.x) < Zero && (point1.y > point2.y))
				{
					if (point2.y < point.y)
					{
						pObj = pObj->ExchangeStartAndEnd(pObj);
						point = point2;
						pos2 = pos1;
					}
				}
			}
		}
		pObj = pObjList->GetAt(pos2);
		pObjList->RemoveAt(pos2);
		m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
		Index1++;
	}
	delete pObjList;
	pObjList = NULL;
	MessageBox(_T("排序完成!"));
	OnOK();
}

void CObjPropertyDlgEdit::OnBnClickedObjPathSort4()
{
	int Index, Index1, Count, nType;
	CMachineObjList* pObjList;
	CMachineObj_Comm* pObj;
	BOOL bFirstIndex = FALSE, bFwd, bFlag;
	POSITION pos, pos1, pos2;
	ObjPoint point, point1, point2, point3;
	pObjList = new CMachineObjList;
	Count = 0;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(Index - Count);
		if (pObj->m_ObjByLayer >= LayerNum_Default && pObj->GetObjType() != MachineObj_Type_Group)
		{
			if (!bFirstIndex)
			{
				bFirstIndex = TRUE;
				Index1 = Index;
			}
			m_pObjProty->m_pObjList->RemoveObjAtIndex(Index - Count);
			pObjList->AddTail(pObj);
			Count++;
		}
	}
	Count = pObjList->GetCount();
	bFwd = TRUE;
	bFlag = FALSE;
	point3 = ObjPoint(0, 0);
	for (int i = 0; i < Count; i++)
	{
		pos = pObjList->GetHeadPosition();
		pos2 = pos;
		if (bFwd)
			point = ObjPoint(100000, 100000);
		else
			point = ObjPoint(100000, -100000);
		while (pos)
		{
			pos1 = pos;
			pObj = pObjList->GetNext(pos);
			nType = pObj->GetObjType();
			if (bFwd)
			{
				//顺向
				if (nType == MachineObj_Type_Point
					|| nType == MachineObj_Type_Circle
					|| nType == MachineObj_Type_Ellipse)
				{
					point1 = pObj->GetObjStart(pObj);
					if (point1.x < point.x)
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.x - point.x) < Zero)
					{
						if (point1.y < point.y)
						{
							point = point1;
							pos2 = pos1;
						}
					}
				}
				else
				{
					point1 = pObj->GetObjStart(pObj);
					point2 = pObj->GetObjEnd(pObj);
					if ((point1.x < point.x) && (point2.y > point1.y))
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.x - point.x) < Zero && (point2.y > point1.y))
					{
						if (point1.y < point.y)
						{
							point = point1;
							pos2 = pos1;
						}
					}
					if ((point2.x < point.x) && (point1.y > point2.y))
					{
						pObj = pObj->ExchangeStartAndEnd(pObj);
						point = point2;
						pos2 = pos1;
					}
					else if (abs(point2.x - point.x) < Zero && (point1.y > point2.y))
					{
						if (point2.y < point.y)
						{
							pObj = pObj->ExchangeStartAndEnd(pObj);
							point = point2;
							pos2 = pos1;
						}
					}
				}
			}
			else
			{
				//反向
				if (nType == MachineObj_Type_Point
					|| nType == MachineObj_Type_Circle
					|| nType == MachineObj_Type_Ellipse)
				{
					point1 = pObj->GetObjStart(pObj);
					if (point1.x < point.x)
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.x - point.x) < Zero)
					{
						if (point1.y > point.y)
						{
							point = point1;
							pos2 = pos1;
						}
					}
				}
				else
				{
					point1 = pObj->GetObjStart(pObj);
					point2 = pObj->GetObjEnd(pObj);
					if ((point1.x < point.x) && (point2.y < point1.y))
					{
						point = point1;
						pos2 = pos1;
					}
					else if (abs(point1.x - point.x) < Zero && (point2.y < point1.y))
					{
						if (point1.y > point.y)
						{
							point = point1;
							pos2 = pos1;
						}
					}
					if ((point2.x < point.x) && (point1.y < point2.y))
					{
						pObj = pObj->ExchangeStartAndEnd(pObj);
						point = point2;
						pos2 = pos1;
					}
					else if (abs(point2.x - point.x) < Zero && (point1.y < point2.y))
					{
						if (point2.y > point.y)
						{
							pObj = pObj->ExchangeStartAndEnd(pObj);
							point = point2;
							pos2 = pos1;
						}
					}
				}
			}
		}
		if (!bFlag)
		{
			pObj = pObjList->GetAt(pos2);
			pObjList->RemoveAt(pos2);
			m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
			Index1++;
			point3 = pObj->GetObjStart(pObj);
			bFlag = TRUE;
		}
		else
		{
			pObj = pObjList->GetAt(pos2);
			point1 = pObj->GetObjStart(pObj);
			if (abs(point1.x - point3.x) < Zero)
			{
				pObjList->RemoveAt(pos2);
				m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
				Index1++;
			}
			else
			{
				bFwd = !bFwd;
				bFlag = FALSE;
				i--;
			}
		}
	}
	delete pObjList;
	pObjList = NULL;
	MessageBox(_T("排序完成!"));
	OnOK();
}

void CObjPropertyDlgEdit::OnBnClickedObjPathSort5()
{
	int Index, Index1, Count, nType;
	CMachineObjList* pObjList;
	CMachineObj_Comm* pObj;
	BOOL bFirstIndex = FALSE;
	POSITION pos, pos1, pos2;
	ObjPoint point, point1, point2;
	double distance, distance1;
	pObjList = new CMachineObjList;
	Count = 0;
	pos = m_pObjProty->m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_pObjProty->m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjProty->m_pObjList->GetObjAtIndex(Index - Count);
		if (pObj->m_ObjByLayer >= LayerNum_Default && pObj->GetObjType() != MachineObj_Type_Group)
		{
			if (!bFirstIndex)
			{
				bFirstIndex = TRUE;
				Index1 = Index;
			}
			m_pObjProty->m_pObjList->RemoveObjAtIndex(Index - Count);
			pObjList->AddTail(pObj);
			Count++;
		}
	}
	Count = pObjList->GetCount();
	pos = pObjList->GetHeadPosition();
	pos2 = pos;
	point = ObjPoint(1000, 1000);
	while (pos)
	{
		pos1 = pos;
		pObj = pObjList->GetNext(pos);
		nType = pObj->GetObjType();
		if (nType == MachineObj_Type_Point
			|| nType == MachineObj_Type_Circle
			|| nType == MachineObj_Type_Ellipse)
		{
			point1 = pObj->GetObjStart(pObj);
			if (point1.y < point.y)
			{
				point = point1;
				pos2 = pos1;
			}
			else if (abs(point1.y - point.y) < Zero)
			{
				if (point1.x < point.x)
				{
					point = point1;
					pos2 = pos1;
				}
			}
		}
		else
		{
			point1 = pObj->GetObjStart(pObj);
			point2 = pObj->GetObjEnd(pObj);
			if ((point1.y < point.y) && (point2.x >= point1.x))
			{
				point = point1;
				pos2 = pos1;
			}
			else if (abs(point1.y - point.y) < Zero && (point2.x >= point1.x))
			{
				if (point1.x < point.x)
				{
					point = point1;
					pos2 = pos1;
				}
			}
			if ((point2.y < point.y) && (point1.x >= point2.x))
			{
				pObj = pObj->ExchangeStartAndEnd(pObj);
				point = point2;
				pos2 = pos1;
			}
			else if (abs(point2.y - point.y) < Zero && (point1.x >= point2.x))
			{
				if (point2.x < point.x)
				{
					pObj = pObj->ExchangeStartAndEnd(pObj);
					point = point2;
					pos2 = pos1;
				}
			}
		}
	}
	pObj = pObjList->GetAt(pos2);
	pObjList->RemoveAt(pos2);
	m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
	Index1++;
	nType = pObj->GetObjType();
	if (nType == MachineObj_Type_Point)
		point = pObj->GetObjStart(pObj);
	else
		point = pObj->GetObjEnd(pObj);
	for (int i = 1; i < Count; i++)
	{
		pos = pObjList->GetHeadPosition();
		pos2 = pos;
		distance = 1000000;
		while (pos)
		{
			pos1 = pos;
			pObj = pObjList->GetNext(pos);
			nType = pObj->GetObjType();
			if (nType == MachineObj_Type_Point
				|| nType == MachineObj_Type_Circle
				|| nType == MachineObj_Type_Ellipse)
			{
				point1 = pObj->GetObjStart(pObj);
				distance1 = (point1.x - point.x)*(point1.x - point.x) + (point1.y - point.y)*(point1.y - point.y);
				if (distance1 < distance)
				{
					distance = distance1;
					pos2 = pos1;
				}
			}
			else
			{
				point1 = pObj->GetObjStart(pObj);
				distance1 = (point1.x - point.x)*(point1.x - point.x) + (point1.y - point.y)*(point1.y - point.y);
				if (distance1 < distance)
				{
					distance = distance1;
					pos2 = pos1;
				}
				point1 = pObj->GetObjEnd(pObj);
				distance1 = (point1.x - point.x)*(point1.x - point.x) + (point1.y - point.y)*(point1.y - point.y);
				if (distance1 < distance)
				{
					pObj = pObj->ExchangeStartAndEnd(pObj);
					distance = distance1;
					pos2 = pos1;
				}
			}
		}
		pObj = pObjList->GetAt(pos2);
		pObjList->RemoveAt(pos2);
		m_pObjProty->m_pObjList->InsertObjAtIndex(Index1, pObj);
		Index1++;
		nType = pObj->GetObjType();
		if (nType == MachineObj_Type_Point)
			point = pObj->GetObjStart(pObj);
		else
			point = pObj->GetObjEnd(pObj);
	}
	delete pObjList;
	pObjList = NULL;
	MessageBox(_T("排序完成!"));
	OnOK();
}


