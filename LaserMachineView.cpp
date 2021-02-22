// LaserMachineView.cpp : CLaserMachineView 类的实现
//

#include "stdafx.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LaserMachine.h"
#endif

#include "LaserMachineDoc.h"
#include "LaserMachineView.h"
#include "ObjectProperty.h"
#include "MainFrm.h"
#include "CDlgSetParaGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLaserMachineView

IMPLEMENT_DYNCREATE(CLaserMachineView, CView)

BEGIN_MESSAGE_MAP(CLaserMachineView, CView)
	//// 标准打印命令
	//ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	//ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_ZOOM_UP, &CLaserMachineView::OnZoomUp)
	ON_COMMAND(ID_ZOOM_DOWN, &CLaserMachineView::OnZoomDown)
	ON_COMMAND(ID_ZOOM_ALL, &CLaserMachineView::OnZoomAll)
	ON_COMMAND(ID_ZOOM_RECT, &CLaserMachineView::OnZoomRect)
	ON_COMMAND(ID_DRAW_SELECT, &CLaserMachineView::OnDrawSelect)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_ObjBound_ReSize, &CLaserMachineView::OnObjBoundResize)
	ON_MESSAGE(WM_Init_ReSize, &CLaserMachineView::OnInitResize)
	
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, &CLaserMachineView::OnUpdateDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_RECT, &CLaserMachineView::OnUpdateZoomRect)


	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_SETPARA_GRID, &CLaserMachineView::OnSetparaGrid)
END_MESSAGE_MAP()

// CLaserMachineView 构造/析构

CLaserMachineView::CLaserMachineView()
{
	m_DrawType = DrawType_Default;
	m_LButtonDown = FALSE;
	m_MouseMoved = FALSE;

	m_ptWindowOrg = InitOrgPoint;
	m_ptViewPortOrg = InitOrgPoint;
	m_nHScrollPos = 0;
	m_nVScrollPos = 0;
	m_nHScrollMax = InitScrollMax;
	m_nVScrollMax = InitScrollMax;
	m_rcBound = InitBound;
	m_rcZoomBound = m_rcBound;

}

CLaserMachineView::~CLaserMachineView()
{
	m_nList.clear();
	vector<int>(m_nList).swap(m_nList);
}

BOOL CLaserMachineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//by Cao
	cs.style = cs.style | WS_HSCROLL | WS_VSCROLL;

	return CView::PreCreateWindow(cs);
}

// CLaserMachineView 绘制

void CLaserMachineView::OnDraw(CDC* pDC)
{
	CDC Mem_DC;
	CBitmap bmp;
	ObjRect Objrc = TransLPtoRP(TransDPtoLP(m_rcClient));		//备用,若绘图刷新过慢,可考虑仅绘制窗口内图形
	Mem_DC.CreateCompatibleDC(pDC);     //创建兼容内存DC 
	bmp.CreateCompatibleBitmap(pDC, m_rcClient.Width(), m_rcClient.Height());    //创建内存兼容位图
	Mem_DC.SelectObject(&bmp);          //把内存位图选进内存DC中用来保存在内存DC中绘制的图形
	Mem_DC.SetMapMode(MM_ISOTROPIC);
	Mem_DC.SetWindowOrg(m_ptWindowOrg);
	Mem_DC.SetViewportOrg(m_ptViewPortOrg);
	Mem_DC.SetWindowExt(MultipeDPToLP, MultipeDPToLP);
	Mem_DC.SetViewportExt((int)(m_fZoomFactor * MultipeDPToLP), (int)(m_fZoomFactor * MultipeDPToLP));
	Mem_DC.DPtoLP(m_rcClient);
	//Mem_DC.FillSolidRect(m_rcClient, RGB(255, 255, 255));      //背景填充白色，否则可能为黑色
	Mem_DC.FillSolidRect(m_rcClient, pDC->GetBkColor());
	m_pLaserObjList->DrawObjList(&Mem_DC, m_pLaserObjList, (float)m_fZoomFactor);
	//m_pLaserObjList->DrawObjList(&Mem_DC, m_pLaserObjList, (float)m_fZoomFactor, Objrc); //备用,若绘图刷新过慢,可考虑仅绘制窗口内图形
	pDC->BitBlt(m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height(),
		&Mem_DC, m_rcClient.left, m_rcClient.top, SRCCOPY);
	DrawCoord(pDC);
	DrawGrid(pDC, m_pLaserObjList);

	bmp.DeleteObject();
	Mem_DC.DeleteDC();
	ReleaseDC(&Mem_DC);
}

void CLaserMachineView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	//设置逻辑窗口与显示窗口的坐标对应关系
	UpdateHVscroll();
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowOrg(m_ptWindowOrg);
	pDC->SetViewportOrg(m_ptViewPortOrg);
	pDC->SetWindowExt(MultipeDPToLP, MultipeDPToLP);
	pDC->SetViewportExt((int)(m_fZoomFactor * MultipeDPToLP), (int)(m_fZoomFactor * MultipeDPToLP));
	SetScrollRange(SB_VERT, 0, m_nVScrollMax, TRUE);
	SetScrollPos(SB_VERT, m_nVScrollPos);
	SetScrollRange(SB_HORZ, 0, m_nHScrollMax, TRUE);
	SetScrollPos(SB_HORZ, m_nHScrollPos);
	CView::OnPrepareDC(pDC, pInfo);
}

void CLaserMachineView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	//**pMainWnd->ShowWindow(SW_MAX);
	CLaserMachineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pLaserObjList = pDoc->m_pLaserObjList;
	ResetViewSize();
}

BOOL CLaserMachineView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


//// CLaserMachineView 打印
//
//BOOL CLaserMachineView::OnPreparePrinting(CPrintInfo* pInfo)
//{
//	// 默认准备
//	return DoPreparePrinting(pInfo);
//}
//
//void CLaserMachineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO:  添加额外的打印前进行的初始化过程
//}
//
//void CLaserMachineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO:  添加打印后进行的清理过程
//}
//

// CLaserMachineView 诊断

#ifdef _DEBUG
void CLaserMachineView::AssertValid() const
{
	CView::AssertValid();
}

void CLaserMachineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLaserMachineDoc* CLaserMachineView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLaserMachineDoc)));
	return (CLaserMachineDoc*)m_pDocument;
}
#endif //_DEBUG


// CLaserMachineView 消息处理程序
BOOL CLaserMachineView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	CPoint ptInput(pt);
	ScreenToClient(&ptInput);
//	if (!m_pListDraw->IsEmpty())
	{
		if (zDelta > 0)
		{
			ZoomUpInPoint(ptInput);
		}
		else
		{
			ZoomDownInPoint(ptInput);
		}

		Invalidate();
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CLaserMachineView::OnZoomUp()
{
	m_DrawType = DrawType_Default;
	ZoomUpInPoint(CPoint(m_rcClient.CenterPoint()));
	Invalidate();
}

void CLaserMachineView::OnZoomDown()
{
	m_DrawType = DrawType_Default;
	ZoomDownInPoint(CPoint(m_rcClient.CenterPoint()));
	Invalidate();
}

void CLaserMachineView::OnZoomAll()
{
	m_DrawType = DrawType_Default;
	ResetViewSize();
	Invalidate();
}

void CLaserMachineView::OnZoomRect()
{
	m_DrawType = DrawType_Zoom;
}

void CLaserMachineView::OnUpdateZoomRect(CCmdUI *pCmdUI)
{
	if (m_DrawType == DrawType_Zoom)
		pCmdUI->Enable(FALSE);
}

void CLaserMachineView::OnDrawSelect()
{
	
	if (m_pLaserObjList->IsEmptyObj())
		return;
	m_DrawType = DrawType_Select;
}

void CLaserMachineView::OnUpdateDrawSelect(CCmdUI *pCmdUI)
{
	if (m_DrawType == DrawType_Select||m_pLaserObjList->IsEmptyObj())
		pCmdUI->Enable(FALSE);
}

void CLaserMachineView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nInc = 0;
	int nNewPos = m_nHScrollPos;
	switch (nSBCode)
	{
	case SB_LINEUP:
		nNewPos -= DetaLineHScroll;
		nInc = DetaLineHScroll;
		break;
	case SB_LINEDOWN:
		nNewPos += DetaLineHScroll;
		nInc = -DetaLineHScroll;
		break;
	case SB_PAGEUP:
		nNewPos -= DetaPageHScroll;
		nNewPos = max(0, min(nNewPos, m_nHScrollMax));
		nInc = m_nHScrollPos - nNewPos;
		break;
	case SB_PAGEDOWN:
		nNewPos += DetaPageHScroll;
		nNewPos = max(0, min(nNewPos, m_nHScrollMax));
		nInc = m_nHScrollPos - nNewPos;
		break;
	case SB_THUMBPOSITION:
		nInc = m_nHScrollPos - nPos;
		nNewPos = nPos;
		break;
	default:
		break;
	}
	m_nHScrollPos = nNewPos;
	m_ptViewPortOrg += CPoint(nInc * ScrollStep, 0);
	Invalidate();
	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CLaserMachineView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nInc = 0;;
	int nNewPos = m_nVScrollPos;
	switch (nSBCode)
	{
	case SB_LINEUP:
		nNewPos -= DetaLineVScroll;
		nInc = DetaLineVScroll;
		break;
	case SB_LINEDOWN:
		nNewPos += DetaLineVScroll;
		nInc = -DetaLineVScroll;
		break;
	case SB_PAGEUP:
		nNewPos -= DetaPageVScroll;
		nNewPos = max(0, min(nNewPos, m_nVScrollMax));
		nInc = m_nVScrollPos - nNewPos;
		break;
	case SB_PAGEDOWN:
		nNewPos += DetaPageVScroll;
		nNewPos = max(0, min(nNewPos, m_nVScrollMax));
		nInc = m_nVScrollPos - nNewPos;
		break;
	case SB_THUMBPOSITION:
		nInc = m_nVScrollPos - nPos;
		nNewPos = nPos;
		break;
	default:
		break;
	}
	m_nVScrollPos = nNewPos;
	m_ptViewPortOrg += CPoint(0, nInc * ScrollStep);
	Invalidate();
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}


//****待补充
void CLaserMachineView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_MouseMoved = FALSE;
	if (m_DrawType == DrawType_Zoom)
	{
		m_LButtonDown = TRUE;
		m_LButtonFirst = TransDPtoLP(point);
		m_ptLButtonTemp = m_LButtonFirst;
	}
	else if (m_DrawType == DrawType_Select)
	{
		m_LButtonDown = TRUE;
		m_LButtonFirst = TransDPtoLP(point);
		m_ptLButtonTemp = m_LButtonFirst;

		/*ObjPoint Objpt = TransLPtoRP(TransDPtoLP(point));
		CRect rc;
		ObjRect Objrc;
		rc = CRect(CPoint(-PickBoxSize, -PickBoxSize), CPoint(PickBoxSize, PickBoxSize));
		Objrc = TransLPtoRP(TransDPtoLP(rc));
		float BoxSize = (float)(Objrc.max_x - Objrc.min_x) / 2;
		Objrc = TransLPtoRP(TransDPtoLP(m_rcClient));
		int nSel;
		CObjectProperty* pObjProperty = (CObjectProperty*)
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
		if (GetAsyncKeyState(VK_CONTROL) >= 0)
		{
			m_pLaserObjList->SetObjUnSelectAll();
			nSel = m_pLaserObjList->PickObjectList(m_pLaserObjList, Objpt, Objrc, BoxSize);
			if (nSel >= 0)
				pObjProperty->SendMessage(WM_ObjList_Refresh, 1, nSel);
			else
				pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);
			Invalidate();
		}
		else
		{
			nSel = m_pLaserObjList->PickObjectList(m_pLaserObjList, Objpt, Objrc, BoxSize);
			if (nSel >= 0)
			{
				pObjProperty->SendMessage(WM_ObjList_Refresh, 2, nSel);
				Invalidate();
			}
		}*/
	}
	CView::OnLButtonDown(nFlags, point);
}
//****待补充
void CLaserMachineView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_DrawType == DrawType_Zoom && m_LButtonDown && m_MouseMoved)
	{
		CRect rcTemp;
		CPoint ptTemp;
		long Temp;
		CDC* pDC = GetDC();
		ptTemp = TransDPtoLP(point);
		if (ptTemp.x < m_LButtonFirst.x)
		{
			Temp = m_LButtonFirst.x;
			m_LButtonFirst.x = ptTemp.x;
			ptTemp.x = Temp;
		}
		if (ptTemp.y < m_LButtonFirst.y)
		{
			Temp = m_LButtonFirst.y;
			m_LButtonFirst.y = ptTemp.y;
			ptTemp.y = Temp;
		}
		rcTemp.SetRect(m_LButtonFirst, ptTemp);
		rcTemp.NormalizeRect();
		pDC->Rectangle(rcTemp);
		rcTemp.left = TransLPtoDP(m_LButtonFirst).x;
		rcTemp.top = TransLPtoDP(m_LButtonFirst).y;
		rcTemp.right = TransLPtoDP(ptTemp).x;
		rcTemp.bottom = TransLPtoDP(ptTemp).y;
		ReleaseDC(pDC);
		ZoomInRect(rcTemp);
		Invalidate();
	}
	else if (m_DrawType == DrawType_Select && m_LButtonDown && m_MouseMoved)
	{
		CRect rcTemp;
		CPoint ptTemp;
		long Temp;
		CDC* pDC = GetDC();
		ptTemp = TransDPtoLP(point);
		if (ptTemp.x < m_LButtonFirst.x)
		{
			Temp = m_LButtonFirst.x;
			m_LButtonFirst.x = ptTemp.x;
			ptTemp.x = Temp;
		}
		if (ptTemp.y < m_LButtonFirst.y)
		{
			Temp = m_LButtonFirst.y;
			m_LButtonFirst.y = ptTemp.y;
			ptTemp.y = Temp;
		}
		rcTemp.SetRect(m_LButtonFirst, ptTemp);
		rcTemp.NormalizeRect();
		pDC->Rectangle(rcTemp);
		ReleaseDC(pDC);
		
		ObjRect Objrc, Objrc1;
		Objrc = TransLPtoRP(TransDPtoLP(m_rcClient));
		Objrc1.min_x = TransLPtoRP(m_LButtonFirst).x;
		Objrc1.max_x = TransLPtoRP(ptTemp).x;
		Objrc1.min_y = TransLPtoRP(ptTemp).y;
		Objrc1.max_y = TransLPtoRP(m_LButtonFirst).y;
		m_pLaserObjList->SetObjUnSelectAll();
		m_nList.clear();
		m_nList = m_pLaserObjList->PickMultObjList(m_pLaserObjList, Objrc, Objrc1);
		if (!m_nList.empty())
		{
			CObjectProperty* pObjProperty = (CObjectProperty*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
			pObjProperty->SendMessage(WM_ObjList_Refresh, 3, (LPARAM)&m_nList);
		}
		Invalidate();
	}
	else if (m_DrawType == DrawType_Select && m_LButtonDown && !m_MouseMoved)
	{
		ObjPoint Objpt = TransLPtoRP(TransDPtoLP(point));
		CRect rc;
		ObjRect Objrc;
		rc = CRect(CPoint(-PickBoxSize, -PickBoxSize), CPoint(PickBoxSize, PickBoxSize));
		Objrc = TransLPtoRP(TransDPtoLP(rc));
		float BoxSize = (float)(Objrc.max_x - Objrc.min_x) / 2;
		Objrc = TransLPtoRP(TransDPtoLP(m_rcClient));
		int nSel;
		CObjectProperty* pObjProperty = (CObjectProperty*)
			((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
		if (GetAsyncKeyState(VK_CONTROL) >= 0)
		{
			m_pLaserObjList->SetObjUnSelectAll();
			nSel = m_pLaserObjList->PickObjectList(m_pLaserObjList, Objpt, Objrc, BoxSize);
			if (nSel >= 0)
				pObjProperty->SendMessage(WM_ObjList_Refresh, 1, nSel);
			else
				pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);
			Invalidate();
		}
		else
		{
			nSel = m_pLaserObjList->PickObjectList(m_pLaserObjList, Objpt, Objrc, BoxSize);
			if (nSel >= 0)
			{
				pObjProperty->SendMessage(WM_ObjList_Refresh, 2, nSel);
				Invalidate();
			}
		}
	}






	m_LButtonDown = FALSE;
	m_MouseMoved = FALSE;
	CView::OnLButtonUp(nFlags, point);
}
//****待补充
void CLaserMachineView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if ((m_DrawType == DrawType_Zoom || m_DrawType == DrawType_Select) && m_LButtonDown)		//框选
	{
		m_MouseMoved = TRUE;
		CRect rcTemp(0, 0, 0, 0);
		CPoint ptTemp = TransDPtoLP(point);
		CDC* pDC = GetDC();
		OnPrepareDC(pDC);
		HANDLE hGdi = GetStockObject(NULL_BRUSH);
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)hGdi);
		pDC->SelectObject(pBrush);
		pDC->SetROP2(R2_NOTXORPEN);
		rcTemp.SetRect(m_LButtonFirst, m_ptLButtonTemp);
		rcTemp.NormalizeRect();
		pDC->Rectangle(rcTemp);
		rcTemp.SetRect(m_LButtonFirst, ptTemp);
		rcTemp.NormalizeRect();
		pDC->Rectangle(rcTemp);
		m_ptLButtonTemp = ptTemp;
		ReleaseDC(pDC);
	}

	
	//状态栏显示图形坐标
	ObjPoint point1 = TransLPtoRP(TransDPtoLP(point));
	CString str;
	str.Format(_T("图形坐标: %.3f,%.3f"), point1.x, point1.y);
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->m_wndStatusBar.SetPaneText(2, str);
	pFrame->SetActiveView(this);
	CView::OnMouseMove(nFlags, point);
}

afx_msg LRESULT CLaserMachineView::OnObjBoundResize(WPARAM wParam, LPARAM lParam)
{
	if (m_pLaserObjList->IsEmptyObj())
	{
		m_rcBound = InitBound;
		m_rcZoomBound = m_rcBound;
		ResetViewSize();
		Invalidate();
		return 0;
	}
	m_rcBound = TransRBdtoLBd(m_pLaserObjList->GetObjBound());
	m_rcZoomBound = m_rcBound;
	ResetViewSize();
	Invalidate();
	return 0;
}

afx_msg LRESULT CLaserMachineView::OnInitResize(WPARAM wParam, LPARAM lParam)
{
	m_rcBound = InitBound;
	m_rcZoomBound = m_rcBound;
	ResetViewSize();
	Invalidate();
	return 0;
}

//自定义函数处理程序
void CLaserMachineView::DrawGrid(CDC* pDC, CMachineListContainer* m_pObjList)
{
	//画网格
	CPen* pOldPen = NULL;
	CPen penNew;
	penNew.CreatePen(PS_DASH, 2, PenColor_Grid);	//坐标轴颜色
	pOldPen = pDC->SelectObject(&penNew);

	ObjRect rtBound = m_pObjList->GetObjBound();
	ObjPoint GridOrg(rtBound.min_x, rtBound.min_y);
	for (auto valX : vecGridX)
	{
		pDC->MoveTo(TransRPtoLP(ObjPoint(GridOrg.x + valX, GridOrg.y + vecGridY.front())));
		pDC->LineTo(TransRPtoLP(ObjPoint(GridOrg.x + valX, GridOrg.y + vecGridY.back())));
	}
	for (auto valY : vecGridY)
	{
		pDC->MoveTo(TransRPtoLP(ObjPoint(GridOrg.x + vecGridX.front(), GridOrg.y + valY)));
		pDC->LineTo(TransRPtoLP(ObjPoint(GridOrg.x + vecGridX.back(), GridOrg.y + valY)));
	}
	//pDC->MoveTo(TransRPtoLP(ObjPoint(0, 0)));
	//pDC->LineTo(TransRPtoLP(ObjPoint(70, 0)));
	//pDC->LineTo(TransRPtoLP(ObjPoint(70, 70)));
	//pDC->LineTo(TransRPtoLP(ObjPoint(0, 70)));
	//pDC->LineTo(TransRPtoLP(ObjPoint(0, 0)));

	pDC->SelectObject(pOldPen);

}

void CLaserMachineView::DrawCoord(CDC* pDC)		//**绘制坐标系函数，尺寸为初始化时视窗大小
{
	CPen* pOldPen = NULL;
	CPen penNew;
	penNew.CreatePen(PS_SOLID, 2, PenColor_Coord);	//坐标轴颜色
	pOldPen = pDC->SelectObject(&penNew);
	pDC->MoveTo(InitBound.left, 0);
	pDC->LineTo(InitBound.right, 0);
	pDC->LineTo(int(InitBound.right*0.95), int(InitBound.bottom*0.02));
	pDC->MoveTo(InitBound.right, 0);
	pDC->LineTo(int(InitBound.right*0.95), int(InitBound.top*0.02));

	pDC->MoveTo(0, InitBound.bottom);
	pDC->LineTo(0, InitBound.top);
	pDC->LineTo(int(InitBound.right*0.02), int(InitBound.top*0.95));
	pDC->MoveTo(0, InitBound.top);
	pDC->LineTo(int(InitBound.left*0.02), int(InitBound.top*0.95));

//	penNew1.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
//	pDC->SelectObject(&penNew1);
	pDC->MoveTo(int(InitBound.left*OrgRectSize), int(InitBound.bottom*OrgRectSize));
	pDC->LineTo(int(InitBound.right*OrgRectSize), int(InitBound.bottom*OrgRectSize));
	pDC->LineTo(int(InitBound.right*OrgRectSize), int(InitBound.top*OrgRectSize));
	pDC->LineTo(int(InitBound.left*OrgRectSize), int(InitBound.top*OrgRectSize));
	pDC->LineTo(int(InitBound.left*OrgRectSize), int(InitBound.bottom*OrgRectSize));

	pDC->SelectObject(pOldPen);
}

void CLaserMachineView::ResetViewSize()
{
	double factor;
	GetClientRect(m_rcClient);
	m_fZoomFactor = (double)m_rcClient.Width() / (double)m_rcBound.Width();
	factor = (double)m_rcClient.Height() / (double)m_rcBound.Height();
	if (m_fZoomFactor > factor)
		m_fZoomFactor = factor;
	UpdateZoomBoundRect();
	m_ptViewPortOrg = CPoint(m_rcClient.CenterPoint().x - m_rcZoomBound.Width() / 2,
		m_rcClient.CenterPoint().y - m_rcZoomBound.Height() / 2);
}

void CLaserMachineView::UpdateHVscroll()
{
	GetClientRect(m_rcClient);
	m_ptWindowOrg = CPoint(m_rcBound.TopLeft());
	InitHScroll();
	InitVScroll();
}

void CLaserMachineView::InitHScroll()
{
	m_nHScrollMax = (int)(abs(m_rcClient.Width() - m_rcZoomBound.Width()) / ScrollStep);
	if (m_rcClient.Width() >= m_rcZoomBound.Width())
		m_nHScrollPos = m_nHScrollMax - (int)(m_ptViewPortOrg.x / ScrollStep);
	else
		m_nHScrollPos = -(int)(m_ptViewPortOrg.x / ScrollStep);
}

void CLaserMachineView::InitVScroll()
{
	m_nVScrollMax = (int)(abs(m_rcClient.Height() - m_rcZoomBound.Height()) / ScrollStep);
	if (m_rcClient.Height() >= m_rcZoomBound.Height())
		m_nVScrollPos = m_nVScrollMax - (int)(m_ptViewPortOrg.y / ScrollStep);
	else
		m_nVScrollPos = -(int)(m_ptViewPortOrg.y / ScrollStep);
}

void CLaserMachineView::ZoomUpInPoint(CPoint ptZoom)
{
	CPoint ptTem1, ptTem2;
	ptTem1 = TransDPtoLP(ptZoom);
	m_fZoomFactor = m_fZoomFactor * MultipeScroll;
	if (m_fZoomFactor > MultipeScrollMax)
		m_fZoomFactor = MultipeScrollMax;
	UpdateZoomBoundRect();
	ptTem2 = TransLPtoDP(ptTem1);
	m_ptViewPortOrg += CPoint(ptZoom.x - ptTem2.x, ptZoom.y - ptTem2.y);
}

void CLaserMachineView::ZoomDownInPoint(CPoint ptZoom)
{
	CPoint ptTem1, ptTem2;
	ptTem1 = TransDPtoLP(ptZoom);
	m_fZoomFactor = m_fZoomFactor / MultipeScroll;
	if (m_fZoomFactor < MultipeScrollMin)
		m_fZoomFactor = MultipeScrollMin;
	UpdateZoomBoundRect();
	ptTem2 = TransLPtoDP(ptTem1);
	m_ptViewPortOrg += CPoint(ptZoom.x - ptTem2.x, ptZoom.y - ptTem2.y);
}

void CLaserMachineView::ZoomInRect(CRect rcZoom)
{
	CRect rcZoomRect = TransDPtoLP(rcZoom);
	CPoint ptZoomCenter1, ptZoomCenter2;
	ptZoomCenter1 = TransDPtoLP(rcZoom.CenterPoint());
	double factor;
	GetClientRect(m_rcClient);
	m_fZoomFactor = (double)m_rcClient.Width() / (double)rcZoomRect.Width();
	factor = (double)m_rcClient.Height() / (double)rcZoomRect.Height();
	if (m_fZoomFactor > factor)
		m_fZoomFactor = factor;
	if (m_fZoomFactor > 2.2)
		m_fZoomFactor = 2.1111;
	UpdateZoomBoundRect();
	ptZoomCenter2 = TransLPtoDP(ptZoomCenter1);

	m_ptViewPortOrg += CPoint(m_rcClient.CenterPoint() - ptZoomCenter2);
}

void CLaserMachineView::UpdateZoomBoundRect()
{
	m_rcZoomBound.SetRect(m_rcBound.left, m_rcBound.top,
		m_rcBound.left + (int)(m_rcBound.Width() * m_fZoomFactor),
		m_rcBound.top + (int)(m_rcBound.Height() * m_fZoomFactor));
	m_rcZoomBound.NormalizeRect();
}

CPoint CLaserMachineView::TransDPtoLP(CPoint ptDevice)
{
	CPoint ptRet(ptDevice);
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);
	pDC->DPtoLP(&ptRet);
	int nRet = ReleaseDC(pDC);
	return ptRet;
}

CRect CLaserMachineView::TransDPtoLP(CRect rcDevice)
{
	CRect rcRet(rcDevice);
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);
	pDC->DPtoLP(&rcRet);
	int nRet = ReleaseDC(pDC);
	return rcRet;
}

CPoint CLaserMachineView::TransLPtoDP(CPoint ptLogic)
{
	CPoint ptRet(ptLogic);
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);

	pDC->LPtoDP(&ptRet);
	int nRet = ReleaseDC(pDC);
	return ptRet;
}

CRect CLaserMachineView::TransLPtoDP(CRect rcLogic)
{
	CRect rcRet(rcLogic);
	CDC* pDC = GetDC();
	OnPrepareDC(pDC);

	pDC->LPtoDP(&rcRet);
	int nRet = ReleaseDC(pDC);
	return rcRet;
}

CPoint CLaserMachineView::TransRPtoLP(ObjPoint ptObj)
{
	CPoint point;
	point.x = (long)(ptObj.x*MultipeObjToLP);
	point.y = (long)(-ptObj.y*MultipeObjToLP);
	return point;
}

CRect CLaserMachineView::TransRBdtoLBd(ObjRect ObjBound)
{
	CRect rect;
	rect.left = (long)(ObjBound.min_x * MultipeObjToLP) - OffsetBound;
	rect.right = (long)(ObjBound.max_x * MultipeObjToLP) + OffsetBound;
	rect.top = -(long)(ObjBound.max_y * MultipeObjToLP) - OffsetBound;
	rect.bottom = -(long)(ObjBound.min_y * MultipeObjToLP) + OffsetBound;
	return rect;
}

ObjPoint CLaserMachineView::TransLPtoRP(CPoint ptLogic)
{
	ObjPoint point;
	point.x = (double)ptLogic.x / (double)MultipeObjToLP;
	point.y = -(double)ptLogic.y / (double)MultipeObjToLP;
	return point;
}

ObjRect CLaserMachineView::TransLPtoRP(CRect rcLogic)
{
	ObjRect rect;
	rect.min_x = (double)rcLogic.left / (double)MultipeObjToLP;
	rect.max_x = (double)rcLogic.right / (double)MultipeObjToLP;
	rect.max_y = -(double)rcLogic.top / (double)MultipeObjToLP;
	rect.min_y = -(double)rcLogic.bottom / (double)MultipeObjToLP;
	return rect;
}


void CLaserMachineView::OnSetparaGrid()
{
	// TODO: 在此添加命令处理程序代码
	CDlgSetParaGrid dlgSetParaGrid;
	dlgSetParaGrid.DoModal();
}
