// ObjectProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "LaserMachineDoc.h"
#include "LaserMachineView.h"
#include "MainFrm.h"
#include "ObjectProperty.h"
#include "ObjPropertyDlgEdit.h"


// CObjectProperty
IMPLEMENT_DYNCREATE(CObjectProperty, CFormView)

CObjectProperty::CObjectProperty()
	: CFormView(CObjectProperty::IDD)
	, m_LaserOnDelay(gLaserOnDelay)
	, m_LaserOffDelay(gLaserOffDelay)
	, m_BeforMarkDelay(gBeforMarkDelay)
	, m_AfterMarkDelay(gAfterMarkDelay)
	, m_PolylineDelay(gPolylineDelay)
	, m_Rise_Lenth_Step(0)
	, m_WaitTime(0)
{
	m_Init_Flag = FALSE;
	m_bLocate = FALSE;
	m_strBtnMark = _T("直接加工");
}

CObjectProperty::~CObjectProperty()
{
}

void CObjectProperty::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OBJECT_PROPERTY_LIST, m_PropertyList);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT1, m_Speed);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT2, m_Power);
	DDV_MinMaxFloat(pDX, m_Power, 0, 100.0);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT3, m_Frequncy);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT4, m_Count);
	DDV_MinMaxByte(pDX, m_Count, 0, 255);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT5, m_PulseWidth);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT6, m_WaitTime);
	DDV_MinMaxFloat(pDX, m_WaitTime, 0, 999999);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT7, m_Rise_Lenth_Step);
	DDV_MinMaxFloat(pDX, m_Rise_Lenth_Step, -100, 100);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT8, m_LaserOnDelay);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT9, m_LaserOffDelay);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT10, m_BeforMarkDelay);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT11, m_AfterMarkDelay);
	DDX_Text(pDX, IDC_OBJECT_PROPERTY_EDIT12, m_PolylineDelay);
	DDX_Radio(pDX, IDC_OBJECT_PROPERTY_RADIO1, m_ModeSel);
}

void CObjectProperty::OnInitialUpdate()
{
	if (m_Init_Flag)
		return;
	m_Init_Flag = TRUE;
	CFormView::OnInitialUpdate();
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	CLaserMachineDoc* pDoc = pView->GetDocument();
	if (!pDoc)
		return;
	m_pView = pView;
	m_pObjList = pDoc->m_pLaserObjList;
	m_pDoc = pDoc;
	m_ObjSel_Old = -1;

	m_PropertyList.SetExtendedStyle(m_PropertyList.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 为列表视图控件添加五列   
	m_PropertyList.InsertColumn(0, _T("索引"), LVCFMT_LEFT, 36, 0);
	m_PropertyList.InsertColumn(1, _T("类   型"), LVCFMT_CENTER, 60, 1);
	m_PropertyList.InsertColumn(2, _T("图 层"), LVCFMT_CENTER, 48, 2);
	m_PropertyList.InsertColumn(3, _T("起点坐标"), LVCFMT_CENTER, 110, 3);
	m_PropertyList.InsertColumn(4, _T("终点坐标"), LVCFMT_CENTER, 110, 4);

	UIDeselectAll();
	if (gLaserType == IPG_Fiber_Laser)
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_STATIC9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJECT_PROPERTY_EDIT5)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJECT_PROPERTY_STATIC10)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJECT_PROPERTY_STATIC13)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJECT_PROPERTY_EDIT7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_OBJECT_PROPERTY_STATIC14)->ShowWindow(SW_HIDE);
	}
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CObjectProperty, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ObjList_Refresh, &CObjectProperty::OnObjlistRefresh)
	ON_NOTIFY(NM_CLICK, IDC_OBJECT_PROPERTY_LIST, &CObjectProperty::OnClickObjectPropertyList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_OBJECT_PROPERTY_LIST, &CObjectProperty::OnKeydownObjectPropertyList)
	ON_NOTIFY(NM_RCLICK, IDC_OBJECT_PROPERTY_LIST, &CObjectProperty::OnRclickObjectPropertyList)
	ON_BN_CLICKED(IDC_BTN_OBJ_UP, &CObjectProperty::OnBnClickedBtnObjUp)
	ON_BN_CLICKED(IDC_BTN_OBJ_DOWN, &CObjectProperty::OnBnClickedBtnObjDown)
	ON_BN_CLICKED(IDC_BTN_OBJ_DELETE, &CObjectProperty::OnBnClickedBtnObjDelete)
	ON_BN_CLICKED(IDC_BTN_OBJ_INSERT, &CObjectProperty::OnBnClickedBtnObjInsert)
	ON_BN_CLICKED(IDC_BTN_OBJ_T_G, &CObjectProperty::OnBnClickedBtnObjPolymeric)
	ON_BN_CLICKED(IDC_BTN_OBJ_EXPLODE, &CObjectProperty::OnBnClickedBtnObjExplode)
	ON_BN_CLICKED(IDC_BTN_OBJ_EXCHANGE, &CObjectProperty::OnBnClickedBtnObjExchange)
	ON_BN_CLICKED(IDC_BTN_OBJ_EDIT, &CObjectProperty::OnBnClickedBtnObjEdit)
	ON_BN_CLICKED(IDC_OBJECT_PROPERTY_BTN3, &CObjectProperty::OnBnClickedObjectPropertyBtn3)
	ON_BN_CLICKED(IDC_OBJECT_PROPERTY_BTN1, &CObjectProperty::OnBnClickedObjectPropertyBtn1)
	ON_BN_CLICKED(IDC_OBJECT_PROPERTY_BTN2, &CObjectProperty::OnBnClickedObjectPropertyBtn2)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_OBJECT_START_MARK, &CObjectProperty::OnBnClickedButtonObjectStartMark)
END_MESSAGE_MAP()


// CObjectProperty 诊断
#ifdef _DEBUG
void CObjectProperty::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectProperty::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// 自定义函数
void CObjectProperty::HScroll(int Index)
{
	int nItem = m_PropertyList.GetTopIndex();	// 获取顶层索引
	CRect rc;
	m_PropertyList.GetItemRect(nItem, rc, LVIR_BOUNDS);
	nItem = Index - nItem - 5;
	CSize sz(0, nItem * rc.Height());	// 取得要滚动的size
	m_PropertyList.Scroll(sz);
}

void CObjectProperty::UIDeselectAll()
{
	POSITION pos;
	int index;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		index = m_PropertyList.GetNextSelectedItem(pos);
		m_PropertyList.SetItemState(index, LVNI_FOCUSED & LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
	}
	GetDlgItem(IDC_BTN_OBJ_UP)->SetWindowText(_T("上移"));
	GetDlgItem(IDC_BTN_OBJ_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_DOWN)->SetWindowText(_T("下移"));
	GetDlgItem(IDC_BTN_OBJ_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_DELETE)->SetWindowText(_T("删除"));
	GetDlgItem(IDC_BTN_OBJ_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_INSERT)->SetWindowText(_T("插入"));
	GetDlgItem(IDC_BTN_OBJ_INSERT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_T_G)->SetWindowText(_T("聚合"));
	GetDlgItem(IDC_BTN_OBJ_T_G)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_EXPLODE)->SetWindowText(_T("分 解"));
	GetDlgItem(IDC_BTN_OBJ_EXPLODE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->SetWindowText(_T("起终点互换"));
	GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_EDIT)->SetWindowText(_T("编 辑"));
	GetDlgItem(IDC_BTN_OBJ_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->SetWindowText(_T("修改对象\n加工参数"));
	GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJECT_PROPERTY_BTN3)->EnableWindow(TRUE);
	//***加工参数区
	m_Speed = gProcessSpeed;
	m_Power = gProcessPower;
	m_Frequncy = (float)gProcessFrequncy / 1000;
	m_Count = gProcessTimes;
	m_PulseWidth = gProcessPulseWidth;
	m_ModeSel = gProcessMode;
	m_WaitTime = gProcessWaitTime;
}

BOOL CObjectProperty::UISetBySingleSel(int Index)
{
	int nType;
	CString str;
	ProcessPara para;
	if (Index == m_ObjSel_Old)
	{
		//*****选中被取消
		m_ObjSel_Old = -1;
		UIDeselectAll();
		return FALSE;
	}
	else
	{
		//*****选中
		m_ObjSel_Old = Index;
		//***属性区
		nType = m_pObjList->GetObjAtIndex(Index)->GetObjType();
		GetDlgItem(IDC_BTN_OBJ_UP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBJ_DOWN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBJ_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBJ_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBJ_INSERT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBJ_T_G)->EnableWindow(FALSE);
		if (nType == MachineObj_Type_Polyline)
		{
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->SetWindowText(_T("分 解"));
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->EnableWindow(TRUE);
		}
		else if (nType == MachineObj_Type_Group)
		{
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->SetWindowText(_T("打 散"));
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->SetWindowText(_T("分 解"));
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->EnableWindow(FALSE);
		}
		if (nType == MachineObj_Type_Line
			|| nType == MachineObj_Type_Arc
			|| nType == MachineObj_Type_ArcEll
			|| nType == MachineObj_Type_TiltEllipse
			|| nType == MachineObj_Type_Polyline)
		{
			GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->SetWindowText(_T("起终点互换"));
			GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->EnableWindow(TRUE);

		}
		else if (nType == MachineObj_Type_Circle
			|| nType == MachineObj_Type_Ellipse)
		{
			GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->SetWindowText(_T("改变起点"));
			GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->SetWindowText(_T("换 向"));
			GetDlgItem(IDC_BTN_OBJ_EXPLODE)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->SetWindowText(_T("起终点互换"));
			GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->EnableWindow(FALSE);
		}
		//***加工参数区
		str = m_PropertyList.GetItemText(Index, 2);
		if (str == _T("Border") || str == _T("Mark") || str == ""
			|| nType == MachineObj_Type_Group)
		{
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(FALSE);
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(FALSE);
			m_Speed = 0;
			m_Power = 0;
			m_Frequncy = 0;
			m_Count = 0;
			m_PulseWidth = 0;
			m_ModeSel = -1;
			m_WaitTime = 0;
			GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_HIDE);
		}
		else
		{
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(TRUE);
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(TRUE);
			para = m_pObjList->GetLayerOfName(str)->m_MachinePara;
			m_Speed = para.Speed;
			m_Power = para.Power;
			m_Frequncy = (float)para.Frequncy / 1000;
			m_Count = para.Times;
			m_PulseWidth = para.PulseWidth;
			m_ModeSel = m_pObjList->GetLayerOfName(str)->m_MachineMode;
			if (nType == MachineObj_Type_Point)
			{
				GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_SHOW);
				m_WaitTime = ((CMachineObjPoint*)m_pObjList->GetObjAtIndex(Index))->m_MachineWaitTime;
			}
			else
			{
				GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_HIDE);
			}
		}
	}
	UpdateData(FALSE);
	return TRUE;
}

void CObjectProperty::UISetByMultipleSel(int Index)
{
	POSITION pos, pos1;
	int nLayer, nType;
	float PointTime;
	CString str;
	ProcessPara para;
	BOOL bEnPolyline = TRUE;
	BOOL bExchange = TRUE;
	m_ObjSel_Old = Index;
	str = m_PropertyList.GetItemText(Index, 2);
	nLayer = m_pObjList->FindLayerByName(str);
	PointTime = 0;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	pos1 = pos;
	Index = m_PropertyList.GetNextSelectedItem(pos1);
	nLayer = m_pObjList->GetObjAtIndex(Index)->m_ObjByLayer;
	while (pos)
	{
		Index = m_PropertyList.GetNextSelectedItem(pos);
		m_pObjList->SetObjSelect(Index);
		//***属性区
		nType = m_pObjList->GetObjAtIndex(Index)->GetObjType();
		if (!(nType == MachineObj_Type_Line
			|| nType == MachineObj_Type_Arc
			|| nType == MachineObj_Type_Polyline))
			bEnPolyline = FALSE;
		if (nLayer != m_pObjList->GetObjAtIndex(Index)->m_ObjByLayer)
			bEnPolyline = FALSE;
		if (!(nType == MachineObj_Type_Line
			|| nType == MachineObj_Type_Arc
			|| nType == MachineObj_Type_ArcEll
			|| nType == MachineObj_Type_TiltEllipse
			|| nType == MachineObj_Type_Polyline))
			bExchange = FALSE;
		//***参数区
		str = m_PropertyList.GetItemText(Index, 2);
		if (nLayer != m_pObjList->FindLayerByName(str))
			nLayer = -1;
		if (nType == MachineObj_Type_Point)
		{
			GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_SHOW);
			m_WaitTime = ((CMachineObjPoint*)m_pObjList->GetObjAtIndex(Index))->m_MachineWaitTime;
			if (m_WaitTime != PointTime && PointTime != 0)
				PointTime = -1;
			else
				PointTime = m_WaitTime;
		}
	}
	//*****属性区
	GetDlgItem(IDC_BTN_OBJ_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_EDIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_OBJ_DELETE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_OBJ_INSERT)->EnableWindow(TRUE);
	if (bEnPolyline)
	{
		GetDlgItem(IDC_BTN_OBJ_T_G)->SetWindowText(_T("聚 合"));
		GetDlgItem(IDC_BTN_OBJ_T_G)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_OBJ_T_G)->SetWindowText(_T("聚 合"));
		GetDlgItem(IDC_BTN_OBJ_T_G)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_BTN_OBJ_EXPLODE)->SetWindowText(_T("组 合"));
	GetDlgItem(IDC_BTN_OBJ_EXPLODE)->EnableWindow(TRUE);
	if (bExchange)
	{
		GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->SetWindowText(_T("起终点互换"));
		GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->SetWindowText(_T("起终点互换"));
		GetDlgItem(IDC_BTN_OBJ_EXCHANGE)->EnableWindow(FALSE);
	}
	//*****参数区
	if (nLayer < 0)
	{
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(FALSE);
		m_Speed = -9999;
		m_Power = -9999;
		m_Frequncy = -9999;
		m_Count = 0;
		m_PulseWidth = 0;
		m_ModeSel = -1;
		m_WaitTime = 0;
	}
	else
	{
		if (nLayer == 0 || nLayer == 1)
		{
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(FALSE);
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(FALSE);
			m_Speed = 0;
			m_Power = 0;
			m_Frequncy = 0;
			m_Count = 0;
			m_PulseWidth = 0;
			m_ModeSel = -1;
			m_WaitTime = 0;
		}
		else
		{
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(TRUE);
			GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(TRUE);
			para = m_pObjList->GetLayerOfNumber(nLayer)->m_MachinePara;
			m_Speed = para.Speed;
			m_Power = para.Power;
			m_Frequncy = (float)para.Frequncy / 1000;
			m_Count = para.Times;
			m_PulseWidth = para.PulseWidth;
			m_ModeSel = m_pObjList->GetLayerOfNumber(nLayer)->m_MachineMode;
		}

	}
	if (PointTime < 0)
		m_WaitTime = -9999;
	UpdateData(FALSE);
}

// CObjectProperty 消息处理程序
void CObjectProperty::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	//试图调整窗口尺寸，则向上级发送消息，用于锁定本对话框尺寸
	GetParentFrame()->SendMessage(WM_ObPrtyWindows_Size, NULL, NULL);
}

afx_msg LRESULT CObjectProperty::OnObjlistRefresh(WPARAM wParam, LPARAM lParam)
{
	if (m_pObjList->IsEmptyObj())
	{
		m_PropertyList.DeleteAllItems();
		return -1;
	}
	if (wParam == 0 && lParam == 0)
	{
		int i = 0;
		CString str;
		ObjVPoint pVpoint;
		ObjPoint point1, point2;
		CMachineObj_Comm* pObj;
		POSITION pos;
		point1 = ObjPoint(0, 0);
		point2 = point1;
		m_PropertyList.DeleteAllItems();
		pos = m_pObjList->GetObjHeadPosition();
		while (pos)
		{
			str.Format(_T("%d"), i);
			m_PropertyList.InsertItem(i, str);
			pObj = m_pObjList->GetObjNext(pos);
			switch (pObj->GetObjType())
			{
			case MachineObj_Type_Point:
				str = _T("点");
				CMachineObjPoint* pPoint;
				pPoint = (CMachineObjPoint*)pObj;
				point1 = pPoint->GetPoint();
				point2.x = pPoint->m_MachineWaitTime;
				break;
			case MachineObj_Type_Line:
				str = _T("直线");
				CMachineObjLine* pLine;
				pLine = (CMachineObjLine*)pObj;
				point1 = pLine->GetLineStart();
				point2 = pLine->GetLineEnd();
				break;
			case MachineObj_Type_Circle:
				str = _T("园");
				CMachineObjCircle* pCircle;
				pCircle = (CMachineObjCircle*)pObj;
				point1 = pCircle->GetCircleStart();
				point2 = point1;
				break;
			case MachineObj_Type_Arc:
				str = _T("园弧");
				CMachineObjArc* pArc;
				pArc = (CMachineObjArc*)pObj;
				point1 = pArc->GetArcStart();
				point2 = pArc->GetArcEnd();
				break;
			case MachineObj_Type_Ellipse:
				str = _T("椭园");
				CMachineObjEllipse* pEllipse;
				pEllipse = (CMachineObjEllipse*)pObj;
				point1 = pEllipse->GetEllipseStart();
				point2 = point1;
				break;
			case MachineObj_Type_ArcEll:
				str = _T("椭园弧");
				CMachineObjArcEll* pArcEll;
				pArcEll = (CMachineObjArcEll*)pObj;
				point1 = pArcEll->GetArcStart();
				point2 = pArcEll->GetArcEnd();
				break;
			case MachineObj_Type_TiltEllipse:
				str = _T("斜椭园弧");
				CMachineObjTiltEllipse* pTileEll;
				pTileEll = (CMachineObjTiltEllipse*)pObj;
				point1 = pTileEll->GetTiltEllipseStart();
				point2 = pTileEll->GetTiltEllipseEnd();
				break;
			case MachineObj_Type_Polyline:
				str = _T("多段线");
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj;
				pVpoint = pPolyline->GetPolylineStart();
				point1.x = pVpoint.x;
				point1.y = pVpoint.y;
				pVpoint = pPolyline->GetPolylineEnd();
				point2.x = pVpoint.x;
				point2.y = pVpoint.y;
				break;
			case MachineObj_Type_Group:
				str = _T("群 组");
				break;
			default:
				str = "";
				break;
			}
			m_PropertyList.SetItemText(i, 1, str);
			str = (m_pObjList->GetLayerOfNumber(pObj->m_ObjByLayer))->m_LayerName;
			m_PropertyList.SetItemText(i, 2, str);
			if (pObj->GetObjType() == MachineObj_Type_Group)
			{
				str = _T("");
				m_PropertyList.SetItemText(i, 3, str);
				m_PropertyList.SetItemText(i, 4, str);
			}
			else
			{
				str.Format(_T("%.3f,%.3f"), point1.x, point1.y);
				m_PropertyList.SetItemText(i, 3, str);
				if (pObj->GetObjType() == MachineObj_Type_Point)
				{
					if (point2.x < 1000)
						str.Format(_T("停留时间=%.1fms"), point2.x);
					else
						str.Format(_T("停留时间=%.2fs"), point2.x / 1000);
				}
				else
					str.Format(_T("%.3f,%.3f"), point2.x, point2.y);
				m_PropertyList.SetItemText(i, 4, str);
			}
			i++;
		}
		m_ObjSel_Old = -1;
		UIDeselectAll();
	}
	else if (wParam==1)
	{
		int Count = m_PropertyList.GetItemCount();
		for (int Index = 0; Index < Count; Index++)
		{
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
		m_PropertyList.SetItemState(lParam, LVNI_FOCUSED | LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		m_ObjSel_Old = -1;
		UISetBySingleSel(lParam);
		HScroll(lParam);
		m_PropertyList.SetFocus();
		UpdateData(FALSE);
	}
	else if (wParam == 2)
	{
		m_PropertyList.SetItemState(lParam, LVNI_FOCUSED | LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		UISetByMultipleSel(lParam);
		HScroll(lParam);
		m_PropertyList.SetFocus();
		UpdateData(FALSE);
	}
	else if (wParam == 3)
	{
		for (int Index = 0; Index < m_PropertyList.GetItemCount(); Index++)
		{
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
		vector<int> *nList;
		nList = (vector<int>*)(lParam);
		int Count = (*nList).size();
		if (Count == 1)
		{
			m_PropertyList.SetItemState((*nList)[0], LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_ObjSel_Old = -1;
			UISetBySingleSel((*nList)[0]);
			HScroll((*nList)[0]);
			m_PropertyList.SetFocus();
			UpdateData(FALSE);
		}
		else if (Count > 1)
		{
			for (int i = 0; i < Count; i++)
			{
				m_PropertyList.SetItemState((*nList)[i], LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				m_ObjSel_Old = -1;
			}
			m_ObjSel_Old = -1;
			UISetByMultipleSel((*nList)[0]);
			HScroll((*nList)[0]);
			m_PropertyList.SetFocus();
			UpdateData(FALSE);
		}
	}
	return 0;
}

void CObjectProperty::OnClickObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	
	int nCount = m_PropertyList.GetSelectedCount();
	if (nCount < 1)
	{
		m_pObjList->SetObjUnSelectAll();
		m_ObjSel_Old = -1;
		m_pView->Invalidate();
		return;
	}
	int Index = pNMItemActivate->iItem;
	if (nCount == 1)
	{
		//****单选****
		m_pObjList->SetObjUnSelectAll();
		if (UISetBySingleSel(Index))
			m_pObjList->SetObjSelect(Index);
		
	}
	else
	{
		//****多选****
		m_AllSelObjInLayer = FALSE;
		m_pObjList->SetObjUnSelectAll();
		UISetByMultipleSel(Index);
	}
	UpdateData(FALSE);
	m_pView->Invalidate();
	return;
}

void CObjectProperty::OnKeydownObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	*pResult = 0;
	m_AllSelObjInLayer = FALSE;
	if (!(pLVKeyDow->wVKey == VK_UP || pLVKeyDow->wVKey == VK_DOWN)
		|| m_PropertyList.GetSelectedCount() == 0)
		return;
	int nCount = m_PropertyList.GetItemCount();
	if ((pLVKeyDow->wVKey == VK_UP) && (m_ObjSel_Old != 0))
		UISetBySingleSel(m_ObjSel_Old - 1);
	else if ((pLVKeyDow->wVKey == VK_DOWN) && (m_ObjSel_Old < (nCount - 1)))
		UISetBySingleSel(m_ObjSel_Old + 1);
	m_pObjList->SetObjUnSelectAll();
	m_pObjList->SetObjSelect(m_ObjSel_Old);
	m_pView->Invalidate();
}

void CObjectProperty::OnRclickObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if (pNMItemActivate->iSubItem != 2 && m_PropertyList.GetSelectedCount() == 1)
	{
		m_AllSelObjInLayer = FALSE;
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->SetWindowText(_T("修改对象\n加工参数"));
		return;
	}
	CString str, str1;
	POSITION pos;
	ProcessPara para;
	int Index, nCount;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	Index = m_PropertyList.GetNextSelectedItem(pos);
	str = m_PropertyList.GetItemText(Index, 2);
	nCount = m_PropertyList.GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		str1 = m_PropertyList.GetItemText(i, 2);
		if (str == str1)
		{
			m_PropertyList.SetItemState(i, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
		else
		{
			m_PropertyList.SetItemState(i, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
	}
	m_pObjList->SetObjUnSelectAll();
	m_pObjList->GetLayerOfName(str)->m_bIsLayerSel = TRUE;
	m_ObjSel_Old = Index;
	GetDlgItem(IDC_BTN_OBJ_UP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_DOWN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBJ_EDIT)->EnableWindow(TRUE);
	if (str != LayerName_Border&&str != LayerName_Mark)
	{
		m_AllSelObjInLayer = TRUE;
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->SetWindowText(_T("修改该层\n加工参数"));
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(TRUE);
	}
	else
	{
		m_AllSelObjInLayer = FALSE;
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->SetWindowText(_T("修改对象\n加工参数"));
		GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->EnableWindow(FALSE);
		
	}
	GetDlgItem(IDC_OBJECT_PROPERTY_BTN2)->EnableWindow(TRUE);
	para = m_pObjList->GetLayerOfName(str)->m_MachinePara;
	m_Speed = para.Speed;
	m_Power = para.Power;
	m_Frequncy = (float)para.Frequncy / 1000;
	m_Count = para.Times;
	m_PulseWidth = para.PulseWidth;
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::OnBnClickedBtnObjUp()
{
	int n, nIndex;
	CString str;
	if (n = m_PropertyList.GetSelectedCount() == 1)
	{
		POSITION pos;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		nIndex = m_PropertyList.GetNextSelectedItem(pos);
		if (m_pObjList->MoveObjUp(nIndex))
		{
			str = m_PropertyList.GetItemText(nIndex - 1, 1);
			m_PropertyList.SetItemText(nIndex - 1, 1, m_PropertyList.GetItemText(nIndex, 1));
			m_PropertyList.SetItemText(nIndex, 1, str);
			str = m_PropertyList.GetItemText(nIndex - 1, 2);
			m_PropertyList.SetItemText(nIndex - 1, 2, m_PropertyList.GetItemText(nIndex, 2));
			m_PropertyList.SetItemText(nIndex, 2, str);
			str = m_PropertyList.GetItemText(nIndex - 1, 3);
			m_PropertyList.SetItemText(nIndex - 1, 3, m_PropertyList.GetItemText(nIndex, 3));
			m_PropertyList.SetItemText(nIndex, 3, str);
			str = m_PropertyList.GetItemText(nIndex - 1, 4);
			m_PropertyList.SetItemText(nIndex - 1, 4, m_PropertyList.GetItemText(nIndex, 4));
			m_PropertyList.SetItemText(nIndex, 4, str);
			m_PropertyList.SetItemState(nIndex - 1,
				LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_PropertyList.SetItemState(nIndex ,
				LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_ObjSel_Old = nIndex - 1;
		}
		else
			MessageBox(_T("无法上移"));
	}
	else
		MessageBox(_T("无法上移"));
	HScroll(nIndex);
	m_PropertyList.SetFocus();
}

void CObjectProperty::OnBnClickedBtnObjDown()
{
	int n, nIndex;
	CString str;
	if (n = m_PropertyList.GetSelectedCount() == 1)
	{
		POSITION pos;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		nIndex = m_PropertyList.GetNextSelectedItem(pos);
		if (m_pObjList->MoveObjDown(nIndex))
		{
			str = m_PropertyList.GetItemText(nIndex + 1, 1);
			m_PropertyList.SetItemText(nIndex + 1, 1, m_PropertyList.GetItemText(nIndex, 1));
			m_PropertyList.SetItemText(nIndex, 1, str);
			str = m_PropertyList.GetItemText(nIndex + 1, 2);
			m_PropertyList.SetItemText(nIndex + 1, 2, m_PropertyList.GetItemText(nIndex, 2));
			m_PropertyList.SetItemText(nIndex, 2, str);
			str = m_PropertyList.GetItemText(nIndex + 1, 3);
			m_PropertyList.SetItemText(nIndex + 1, 3, m_PropertyList.GetItemText(nIndex, 3));
			m_PropertyList.SetItemText(nIndex, 3, str);
			str = m_PropertyList.GetItemText(nIndex + 1, 4);
			m_PropertyList.SetItemText(nIndex + 1, 4, m_PropertyList.GetItemText(nIndex, 4));
			m_PropertyList.SetItemText(nIndex, 4, str);
			m_PropertyList.SetItemState(nIndex + 1,
				LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_PropertyList.SetItemState(nIndex,
				LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_ObjSel_Old = nIndex + 1;
		}
		else
			MessageBox(_T("无法下移"));
	}
	else
		MessageBox(_T("无法下移"));
	HScroll(nIndex);
	m_PropertyList.SetFocus();
}

void CObjectProperty::OnBnClickedBtnObjDelete()
{
	m_AllSelObjInLayer = FALSE;
	GetDlgItem(IDC_OBJECT_PROPERTY_BTN1)->SetWindowText(_T("修改对象\n加工参数"));
	if (MessageBox(_T("确定删除选中对象?\n(删除是不可恢复的!)"),
		_T(""), MB_YESNO | MB_ICONWARNING) != IDYES)
		return;
	int Index, i;
	POSITION pos;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	i = 0;
	while (pos)
	{
		Index = m_PropertyList.GetNextSelectedItem(pos);
		m_pObjList->DeleteObjAtIndex(Index - i);
		i++;
	}
	OnObjlistRefresh(NULL, NULL);
	HScroll(Index);
	m_pObjList->RefeshBound();
	m_pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
}

//对象插入待定
void CObjectProperty::OnBnClickedBtnObjInsert()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CObjectProperty::OnBnClickedBtnObjPolymeric()
{
	if (m_PropertyList.GetSelectedCount() <= 1)
		return;
	POSITION pos;
	int Index;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	vector<int> nList;
	while (pos)
	{
		Index = m_PropertyList.GetNextSelectedItem(pos);
		nList.push_back(Index);
	}
	if (m_pObjList->PolymerObjAtIndex(nList))
	{
		OnObjlistRefresh(NULL, NULL);
		m_PropertyList.SetItemState(nList[0],
			LVNI_FOCUSED | LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		HScroll(nList[0]);
		UISetBySingleSel(nList[0]);
		m_pObjList->SetObjSelect(nList[0]);
		m_PropertyList.SetFocus();
		m_pView->Invalidate();
	}
	nList.clear();
	vector<int>(nList).swap(nList);
}

void CObjectProperty::OnBnClickedBtnObjExplode()
{
	if (m_PropertyList.GetSelectedCount() < 1)
		return;
	POSITION pos;
	int Index;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	if (m_PropertyList.GetSelectedCount() == 1)
	{
		//已选对象=1 
		Index = m_PropertyList.GetNextSelectedItem(pos);
		int nType = m_pObjList->GetObjAtIndex(Index)->GetObjType();
		//园或椭圆为换向
		if (nType == MachineObj_Type_Circle)
		{
			CMachineObjCircle* pCircle = (CMachineObjCircle*) m_pObjList->GetObjAtIndex(Index);
			pCircle->ExchangeDirection();
			m_pView->Invalidate();
		}
		else if (nType == MachineObj_Type_Ellipse)
		{
			CMachineObjEllipse* pEllipse = (CMachineObjEllipse*)m_pObjList->GetObjAtIndex(Index);
			pEllipse->ExchangeDirection();
			m_pView->Invalidate();
		}
		//其他则分解或打散 
		else
		{
			if (m_pObjList->ExplodeObjAtIndex(Index))
			{
				OnObjlistRefresh(NULL, NULL);
				m_PropertyList.SetItemState(Index,
					LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				HScroll(Index);
				UISetBySingleSel(Index);
				m_PropertyList.SetFocus();
				m_pObjList->SetObjSelect(Index);
				m_pView->Invalidate();
			}
		}
	}
	else
	{
		//已选对象>1 组合
		vector<int> nList;
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
			nList.push_back(Index);
		}
		if (m_pObjList->GroupObjAtIndex(nList))
		{
			OnObjlistRefresh(NULL, NULL);
			m_PropertyList.SetItemState(nList[0],
				LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			HScroll(nList[0]);
			UISetBySingleSel(nList[0]);
			m_pObjList->SetObjSelect(nList[0]);
			m_PropertyList.SetFocus();
		}
		nList.clear();
		vector<int>(nList).swap(nList);
	}
}

void CObjectProperty::OnBnClickedBtnObjExchange()
{
	vector<int> nList;
	POSITION pos;
	int Index, Count;
	ObjPoint point;
	CString str;
	pos = m_PropertyList.GetFirstSelectedItemPosition();
	while (pos)
	{
		Index = m_PropertyList.GetNextSelectedItem(pos);
		nList.push_back(Index);
	}
	if (m_pObjList->ExchangeObjStartAndEnd(nList))
	{
		CMachineObj_Comm* pObj;
		Count = nList.size();
		for (int i = 0; i < Count; i++)
		{
			m_PropertyList.SetItemState(nList[i], LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			pObj = m_pObjList->GetObjAtIndex(nList[i]);
			point = pObj->GetObjStart(pObj);
			str.Format(_T("%.3f,%.3f"), point.x, point.y);
			m_PropertyList.SetItemText(nList[i], 3, str);
			point = pObj->GetObjEnd(pObj);
			str.Format(_T("%.3f,%.3f"), point.x, point.y);
			m_PropertyList.SetItemText(nList[i], 4, str);

		}
		if (Count == 1)
		{
			m_ObjSel_Old = -1;
			UISetBySingleSel(nList[0]);
			m_ObjSel_Old = nList[0];
		}
		else
		{
			UISetByMultipleSel(nList[0]);
			m_ObjSel_Old = nList[0];
		}
		m_pView->Invalidate();
	}
	HScroll(nList[0]);
	m_PropertyList.SetFocus();
	nList.clear();
	vector<int>(nList).swap(nList);
}

//待完善
void CObjectProperty::OnBnClickedBtnObjEdit()
{
	if (m_PropertyList.GetSelectedCount() < 1)
		return;
	CObjPropertyDlgEdit dlg;
	dlg.m_pObjProty = this;
	dlg.DoModal();
	m_PropertyList.SetFocus();
	OnObjlistRefresh(NULL, NULL);
	POSITION pos = m_pObjList->GetObjHeadPosition();
	int nIndex = 0;
	int nSel = -1;
	while (pos)
	{
		if ((m_pObjList->GetObjNext(pos))->m_bIsObjSel == TRUE)
		{
			m_PropertyList.SetItemState(nIndex, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			if (nSel < 0)
				nSel = nIndex;
		}
		nIndex++;
	}
	if (m_PropertyList.GetSelectedCount() == 1)
	{
		UISetBySingleSel(nSel);
	}
	else if (m_PropertyList.GetSelectedCount() > 1)
	{
		UISetByMultipleSel(nSel);
	}
	HScroll(nSel);
	m_PropertyList.SetFocus();
	if (dlg.m_bSizeChanged)
		m_pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
	else
		m_pView->Invalidate();
}

void CObjectProperty::OnBnClickedObjectPropertyBtn1()
{
	if (!UpdateData(TRUE))
		return;
	POSITION pos;
	ProcessPara para;
	CMachinePara_Layer* pLayer;
	CMachineObj_Comm* pObj;
	int Index;
	para.Speed = m_Speed;
	para.Power = m_Power;
	para.Frequncy = (UINT)(m_Frequncy * 1000);
	para.Times = m_Count;
	para.PulseWidth = m_PulseWidth;
	if (!m_pDoc->Check_Process_Para1(para, m_ModeSel))
		return;
	if (m_AllSelObjInLayer)
	{
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		Index = m_pObjList->GetObjAtIndex(m_PropertyList.GetNextSelectedItem(pos))->m_ObjByLayer;
		pLayer = m_pObjList->GetLayerOfNumber(Index);
		pLayer->m_MachinePara = para;
		pLayer->m_MachineMode = m_ModeSel;
	}
	else
	{
		vector<int> nList;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
			nList.push_back(Index);
		}
		m_pObjList->FindLayerByParaAddOrChange(para, m_ModeSel, nList);
		nList.clear();
		vector<int>(nList).swap(nList);
	}
	if (GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->IsWindowVisible()
		&& m_pDoc->Check_Process_Para2(m_WaitTime))
	{
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
			pObj = m_pObjList->GetObjAtIndex(Index);
			if (pObj->GetObjType() == MachineObj_Type_Point)
			{
				((CMachineObjPoint*)pObj)->m_MachineWaitTime = m_WaitTime;
			}
		}
	}
	OnObjlistRefresh(NULL, NULL);
	GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_HIDE);

	pos = m_pObjList->GetObjHeadPosition();
	Index = 0;
	int nSel = -1;
	while (pos)
	{
		pObj = m_pObjList->GetObjNext(pos);
		if (pObj->m_bIsObjSel == TRUE || (m_pObjList->GetLayerOfNumber(pObj->m_ObjByLayer))->m_bIsLayerSel)
		{
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			if (nSel < 0)
				nSel = Index;
			if (pObj->GetObjType() == MachineObj_Type_Point)
			{
				GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJECT_PROPERTY_EDIT6)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_OBJECT_PROPERTY_STATIC12)->ShowWindow(SW_SHOW);
			}
		}
		Index++;
	}
	if (m_PropertyList.GetSelectedCount() == 1)
	{
		UISetBySingleSel(nSel);
	}
	else if (m_PropertyList.GetSelectedCount() > 1)
	{
		UISetByMultipleSel(nSel);
	}
	HScroll(nSel);
	m_PropertyList.SetFocus();
	m_pView->Invalidate();
}

void CObjectProperty::OnBnClickedObjectPropertyBtn2()
{
	if (!UpdateData(TRUE))
		return;
	ProcessPara para;
	int ntemp;
	para.Speed = m_Speed;
	para.Power = m_Power;
	para.Frequncy = (UINT)(m_Frequncy * 1000);
	para.Times = m_Count;
	para.PulseWidth = m_PulseWidth;
	ntemp = m_ModeSel;
	if (!m_pDoc->Check_Process_Para1(para, ntemp))
		return;
	gProcessSpeed = m_Speed;
	gProcessPower = m_Power;
	gProcessFrequncy = (UINT)(m_Frequncy * 1000);
	gProcessTimes = m_Count;
	gProcessPulseWidth = m_PulseWidth;
	gProcessMode = m_ModeSel;
	if (GetDlgItem(IDC_OBJECT_PROPERTY_STATIC11)->IsWindowVisible()
		&& m_pDoc->Check_Process_Para2(m_WaitTime))
		gProcessWaitTime = m_WaitTime;
}

void CObjectProperty::OnBnClickedObjectPropertyBtn3()
{
	if (!UpdateData(TRUE))
		return;
	//数据有效性校验待补
	gLaserOnDelay = m_LaserOnDelay;
	gLaserOffDelay = m_LaserOffDelay;
	gBeforMarkDelay = m_BeforMarkDelay;
	gAfterMarkDelay = m_AfterMarkDelay;
	gPolylineDelay = m_PolylineDelay;
}

void CObjectProperty::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->SetActiveView(this);
	CFormView::OnMouseMove(nFlags, point);
}



void CObjectProperty::OnBnClickedButtonObjectStartMark()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->GetWindowText(str);

	if (_T("停止加工") == str)
	{
		::SendMessage(m_pView->GetSafeHwnd(), WM_STOP_MARK, NULL, NULL);
		GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(_T("停止加工"));
		::SendMessage(m_pView->GetSafeHwnd(), WM_START_MARK, m_bLocate, NULL);
		GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
	}
}


BOOL CObjectProperty::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (WM_RBUTTONDOWN == pMsg->message)
	{
		CRect rt;
		POINT pt;
		::GetWindowRect(GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->GetSafeHwnd(), &rt); //得到button所在的rect
		::GetCursorPos(&pt);															//得到鼠标动作的位置
		if (PtInRect(&rt, pt))															 //判断鼠标动作是否在button范围之内     
		{
			CString str;
			GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->GetWindowText(str);

			if (_T("停止加工") == str)
			{
				//do nothing
			}
			else if (FALSE == m_bLocate)
			{
				m_bLocate = TRUE;
				m_strBtnMark = _T("定位加工");
				GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
			}
			else
			{
				m_bLocate = FALSE;
				m_strBtnMark = _T("直接加工");
				GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
			}
		}
	}


	return CFormView::PreTranslateMessage(pMsg);
}
