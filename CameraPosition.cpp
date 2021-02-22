// CameraPosition.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CameraPosition.h"
#include "DlgCameraPositionSetDestinedMarkPoint.h"
#include "MainFrm.h"
#include "LaserMachineDoc.h"
#include "MachineListContainer.h"
#include "DlgCameraPositionSetRealMarkPoint.h"
#include "DeviceCardWorktable.h"
#include "XSleep.h"

int g_nCountMarkPoints;
std::vector <CPointF> g_vPtPosDestinedMark;
std::vector <CPointF> g_vPtPosRealMark;
//std::vector <CPointF> g_vPtPosDeltaMark;
std::vector <HalconModel> g_vMarkPointModel;


// CCameraPosition

IMPLEMENT_DYNCREATE(CCameraPosition, CFormView)

CCameraPosition::CCameraPosition()
	: CFormView(IDD_CAMERA_POSITION)
{
	m_nCountMarkPoints = 0;
	m_vPtPosDestinedMark.assign(4, CPointF(0, 0));
	m_vPtPosRealMark.assign(4, CPointF(0, 0));
	m_vMarkPointModel.assign(4, HalconModel());

	g_nCountMarkPoints = 0;
	g_vPtPosDestinedMark.assign(4, CPointF(0, 0));
	g_vPtPosRealMark.assign(4, CPointF(0, 0));
	//g_vPtPosDeltaMark.assign(4, CPointF(0, 0));
	g_vMarkPointModel.assign(4, HalconModel());

}

CCameraPosition::~CCameraPosition()
{
}

void CCameraPosition::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCameraPosition, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_POSITION_COUNT_MARK_POINTS, &CCameraPosition::OnBnClickedButtonPositionCountMarkPoints)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_DESTINED_MARK1, &CCameraPosition::OnBnClickedButtonPositionSetDestinedMark1)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_DESTINED_MARK2, &CCameraPosition::OnBnClickedButtonPositionSetDestinedMark2)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_DESTINED_MARK3, &CCameraPosition::OnBnClickedButtonPositionSetDestinedMark3)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_DESTINED_MARK4, &CCameraPosition::OnBnClickedButtonPositionSetDestinedMark4)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_REAL_MARK1, &CCameraPosition::OnBnClickedButtonPositionSetRealMark1)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_REAL_MARK2, &CCameraPosition::OnBnClickedButtonPositionSetRealMark2)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_REAL_MARK3, &CCameraPosition::OnBnClickedButtonPositionSetRealMark3)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_SET_REAL_MARK4, &CCameraPosition::OnBnClickedButtonPositionSetRealMark4)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_CHECK, &CCameraPosition::OnBnClickedButtonPositionCheck)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_TEST_DXF, &CCameraPosition::OnBnClickedButtonPositionTestDxf)
END_MESSAGE_MAP()


// CCameraPosition 诊断

#ifdef _DEBUG
void CCameraPosition::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraPosition::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraPosition 消息处理程序


void CCameraPosition::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	//试图调整主控窗口尺寸，则向上级发送消息，用于锁定本对话框尺寸
	GetParentFrame()->SendMessage(WM_CamPosWindows_Size, NULL, NULL);
}


void CCameraPosition::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类


	//初始化界面
	CBitmap bitmap;
	HBITMAP hbmp;
	bitmap.LoadBitmap(IDB_BITMAP_POSITION_BUTTON_COUNT_MARK_POINTS);
	hbmp = (HBITMAP)bitmap.Detach();
	((CButton*)GetDlgItem(IDC_BUTTON_POSITION_COUNT_MARK_POINTS))->SetBitmap(hbmp);

	//不显示mark点坐标
	//理论坐标
	GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK2)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK3)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK4)->ShowWindow(SW_HIDE);

	//实际坐标
	GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK2)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK3)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK4)->ShowWindow(SW_HIDE);

}


void CCameraPosition::OnBnClickedButtonPositionCountMarkPoints()
{
	// TODO: 在此添加控件通知处理程序代码
	switch (m_nCountMarkPoints)
	{
	case 0:
		m_nCountMarkPoints = 1;
		break;
	case 1:
		m_nCountMarkPoints = 2;
		break;
	case 2:
		m_nCountMarkPoints = 3;
		break;
	case 3:
		m_nCountMarkPoints = 4;
		break;
	case 4:
		m_nCountMarkPoints = 0;
		break;
	default:
		m_nCountMarkPoints = 0;
		break;
	}
	RefreshUI(m_nCountMarkPoints);
	return;
}

void CCameraPosition::RefreshUI(int nCtMarkPoints)
{
	CBitmap bitmap;
	HBITMAP hbmp;

	switch (nCtMarkPoints)
	{
	case 0:
		bitmap.LoadBitmap(IDB_BITMAP_POSITION_BUTTON_COUNT_MARK_POINTS);
		hbmp = (HBITMAP)bitmap.Detach();
		((CButton*)GetDlgItem(IDC_BUTTON_POSITION_COUNT_MARK_POINTS))->SetBitmap(hbmp);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK1)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK4)->ShowWindow(SW_HIDE);
		break;
	case 1:
		bitmap.LoadBitmap(IDB_BITMAP_POSITION_BUTTON_COUNT_MARK_POINTS1);
		hbmp = (HBITMAP)bitmap.Detach();
		((CButton*)GetDlgItem(IDC_BUTTON_POSITION_COUNT_MARK_POINTS))->SetBitmap(hbmp);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK2)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK4)->ShowWindow(SW_HIDE);
		break;
	case 2:
		bitmap.LoadBitmap(IDB_BITMAP_POSITION_BUTTON_COUNT_MARK_POINTS2);
		hbmp = (HBITMAP)bitmap.Detach();
		((CButton*)GetDlgItem(IDC_BUTTON_POSITION_COUNT_MARK_POINTS))->SetBitmap(hbmp);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK3)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK4)->ShowWindow(SW_HIDE);
		break;
	case 3:
		bitmap.LoadBitmap(IDB_BITMAP_POSITION_BUTTON_COUNT_MARK_POINTS3);
		hbmp = (HBITMAP)bitmap.Detach();
		((CButton*)GetDlgItem(IDC_BUTTON_POSITION_COUNT_MARK_POINTS))->SetBitmap(hbmp);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK3)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK4)->ShowWindow(SW_HIDE);
		break;
	case 4:
		bitmap.LoadBitmap(IDB_BITMAP_POSITION_BUTTON_COUNT_MARK_POINTS4);
		hbmp = (HBITMAP)bitmap.Detach();
		((CButton*)GetDlgItem(IDC_BUTTON_POSITION_COUNT_MARK_POINTS))->SetBitmap(hbmp);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK1)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK2)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK3)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_DESTINED_MARK4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_REAL_POS_MARK4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_POSITION_SET_REAL_MARK4)->ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
}

BOOL CCameraPosition::RefreshMarkPoints()
{
	CLaserMachineDoc* pDoc = (CLaserMachineDoc*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	CMachineListContainer* pObjList = pDoc->m_pLaserObjList;
	POSITION pos;
	CMachineObj_Comm* pObj;
	ObjRect objRectTmp;
	int nLayerMark, nLayerTmp;
	int nCountMarkPoints = 0;

	nLayerMark = pObjList->FindLayerByName(LayerName_Mark);
	if (0 > nLayerMark)
		return FALSE;

	pos = pObjList->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjList->GetObjNext(pos);
		nLayerTmp = pObj->m_ObjByLayer;
		if (nLayerTmp != nLayerMark)
			continue;
		objRectTmp = pObj->GetObjBound();
		m_vPtPosDestinedMark[nCountMarkPoints] = CPointF((FLOAT)(objRectTmp.max_x + objRectTmp.min_x) / 2,
														(FLOAT)(objRectTmp.max_y + objRectTmp.min_y) / 2);
		nCountMarkPoints++;
		if (4 <= nCountMarkPoints)
			break;
	}

	for (int i = nCountMarkPoints; i < 4; i++)
	{
		m_vPtPosDestinedMark[i] = CPointF(0, 0);
	}

	//刷新坐标显示
	CString strTmp;
	for (int i = 0; i < 4; i++)
	{
		if (i < nCountMarkPoints)
		{
			strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosDestinedMark[i].x, m_vPtPosDestinedMark[i].y);
			GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1+i)->SetWindowTextW(strTmp);
		}
		else
		{
			GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1 + i)->SetWindowTextW(NULL);
		}
	}

	m_nCountMarkPoints = nCountMarkPoints;
	RefreshUI(nCountMarkPoints);

	return TRUE;
}


void CCameraPosition::OnBnClickedButtonPositionSetDestinedMark1()
{
	// TODO: 在此添加控件通知处理程序代码

	CDlgCameraPositionSetDestinedMarkPoint dlgSetDestinedMarkPoint;
	dlgSetDestinedMarkPoint.SetDestinedPtPos(m_vPtPosDestinedMark[0]);
	if (IDOK != dlgSetDestinedMarkPoint.DoModal())
		return;

	CString strTmp;
	m_vPtPosDestinedMark[0] = dlgSetDestinedMarkPoint.GetDestindPtPos();
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosDestinedMark[0].x, m_vPtPosDestinedMark[0].y);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK1)->SetWindowTextW(strTmp);
}


void CCameraPosition::OnBnClickedButtonPositionSetDestinedMark2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgCameraPositionSetDestinedMarkPoint dlgSetDestinedMarkPoint;
	dlgSetDestinedMarkPoint.SetDestinedPtPos(m_vPtPosDestinedMark[1]);
	if (IDOK != dlgSetDestinedMarkPoint.DoModal())
		return;

	CString strTmp;
	m_vPtPosDestinedMark[1] = dlgSetDestinedMarkPoint.GetDestindPtPos();
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosDestinedMark[1].x, m_vPtPosDestinedMark[1].y);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK2)->SetWindowTextW(strTmp);
}


void CCameraPosition::OnBnClickedButtonPositionSetDestinedMark3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgCameraPositionSetDestinedMarkPoint dlgSetDestinedMarkPoint;
	dlgSetDestinedMarkPoint.SetDestinedPtPos(m_vPtPosDestinedMark[2]);
	if (IDOK != dlgSetDestinedMarkPoint.DoModal())
		return;

	CString strTmp;
	m_vPtPosDestinedMark[2] = dlgSetDestinedMarkPoint.GetDestindPtPos();
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosDestinedMark[2].x, m_vPtPosDestinedMark[2].y);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK3)->SetWindowTextW(strTmp);
}


void CCameraPosition::OnBnClickedButtonPositionSetDestinedMark4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgCameraPositionSetDestinedMarkPoint dlgSetDestinedMarkPoint;
	dlgSetDestinedMarkPoint.SetDestinedPtPos(m_vPtPosDestinedMark[3]);
	if (IDOK != dlgSetDestinedMarkPoint.DoModal())
		return;

	CString strTmp;
	m_vPtPosDestinedMark[3] = dlgSetDestinedMarkPoint.GetDestindPtPos();
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosDestinedMark[3].x, m_vPtPosDestinedMark[3].y);
	GetDlgItem(IDC_EDIT_POSITION_DESTINED_POS_MARK4)->SetWindowTextW(strTmp);
}

void CCameraPosition::OnBnClickedButtonPositionSetRealMark1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgCameraPositionSetRealMarkPoint dlgSetRealMarkPoint;
	if (IDOK != dlgSetRealMarkPoint.DoModal())
		return;

	m_vPtPosRealMark[0] = dlgSetRealMarkPoint.GetMatchedPtPos();
	m_vMarkPointModel[0] = dlgSetRealMarkPoint.GetMatchedModel();
	CString strTmp;
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosRealMark[0].x, m_vPtPosRealMark[0].y);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK1)->SetWindowTextW(strTmp);
}


void CCameraPosition::OnBnClickedButtonPositionSetRealMark2()
{
	// TODO: 在此添加控件通知处理程序代码
	//先运动到mark点2附近，再拍照设置
	CPointF fPosRealMark;
	fPosRealMark = m_vPtPosRealMark[0] + m_vPtPosDestinedMark[1] - m_vPtPosDestinedMark[0];
	double fPosTmpX, fPosTmpY;
	pDevCardWorktable->GetAbsPosXY(&fPosTmpX, &fPosTmpY);
	pDevCardWorktable->PosMoveXY(fPosRealMark.x - fPosTmpX, fPosRealMark.y - fPosTmpY, TRUE);
	XSleep(1000);
	CDlgCameraPositionSetRealMarkPoint dlgSetRealMarkPoint;
	if (IDOK != dlgSetRealMarkPoint.DoModal())
		return;

	m_vPtPosRealMark[1] = dlgSetRealMarkPoint.GetMatchedPtPos();
	m_vMarkPointModel[1] = dlgSetRealMarkPoint.GetMatchedModel();
	CString strTmp;
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosRealMark[1].x, m_vPtPosRealMark[1].y);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK2)->SetWindowTextW(strTmp);

}


void CCameraPosition::OnBnClickedButtonPositionSetRealMark3()
{
	// TODO: 在此添加控件通知处理程序代码

	CDlgCameraPositionSetRealMarkPoint dlgSetRealMarkPoint;
	if (IDOK != dlgSetRealMarkPoint.DoModal())
		return;

	m_vPtPosRealMark[2] = dlgSetRealMarkPoint.GetMatchedPtPos();
	m_vMarkPointModel[2] = dlgSetRealMarkPoint.GetMatchedModel();
	CString strTmp;
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosRealMark[2].x, m_vPtPosRealMark[2].y);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK3)->SetWindowTextW(strTmp);
}


void CCameraPosition::OnBnClickedButtonPositionSetRealMark4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgCameraPositionSetRealMarkPoint dlgSetRealMarkPoint;
	if (IDOK != dlgSetRealMarkPoint.DoModal())
		return;

	m_vPtPosRealMark[3] = dlgSetRealMarkPoint.GetMatchedPtPos();
	m_vMarkPointModel[3] = dlgSetRealMarkPoint.GetMatchedModel();
	CString strTmp;
	strTmp.Format(_T("%.4lf, %.4lf"), m_vPtPosRealMark[3].x, m_vPtPosRealMark[3].y);
	GetDlgItem(IDC_EDIT_POSITION_REAL_POS_MARK4)->SetWindowTextW(strTmp);
}


void CCameraPosition::OnBnClickedButtonPositionCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	g_nCountMarkPoints = m_nCountMarkPoints;
	g_vPtPosDestinedMark = m_vPtPosDestinedMark;
	g_vPtPosRealMark = m_vPtPosRealMark;
	g_vMarkPointModel = m_vMarkPointModel;

	//double fPosSavedX, fPosSavedY;
	//pDevCardWorktable->GetAbsPosXY(&fPosSavedX, &fPosSavedY);
	//g_vPtPosRealMark[0].x += (FLOAT)fPosSavedX;
	//g_vPtPosRealMark[0].y += (FLOAT)fPosSavedY;
}



std::vector<std::vector<double>> g_vecTestDXF;
void CCameraPosition::OnBnClickedButtonPositionTestDxf()
{
	// TODO: 在此添加控件通知处理程序代码
	g_vecTestDXF.clear();

	CDlgCameraPositionSetRealMarkPoint dlgTestDXF;
	if (IDOK != dlgTestDXF.DoModal())
		return;

}
