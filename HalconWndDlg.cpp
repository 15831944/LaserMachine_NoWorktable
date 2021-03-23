// HalconWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HalconWndDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CHalconWndDlg

CHalconWndDlg::CHalconWndDlg()
{
	m_hWindow = NULL;
	m_bDrawingArea = FALSE;
	m_nLastHorzPos = 0;
	m_nLastVertPos = 0;
	m_dbZoomFactor = 1.0;

	//m_modelMarkPoint = MarkPointModel();
	m_modelMarkPoint = HalconModel();
}

CHalconWndDlg::~CHalconWndDlg()
{
}


BEGIN_MESSAGE_MAP(CHalconWndDlg, CWnd)
	//{{AFX_MSG_MAP(CHalconWndDlg)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHalconWndDlg message handlers

int CHalconWndDlg::OnCreate(LPCREATESTRUCT cs) 
{
	if (CWnd::OnCreate(cs) == -1)
		return -1;
	//this->InitHalcon(0,0,cs->cx,cs->cy);
	return 0;
}

BOOL CHalconWndDlg::InitHalcon(int x,int y,int w,int h)
{
	try 
	{
		SetWindowAttr("background_color", "black");
		SetWindowAttr("border_width", 0);
		//SetCheck("~father");
		if(NULL != m_hWindow)
			HalconCpp::CloseWindow(m_hWindow);
		OpenWindow(x, y, w, h, (Hlong)m_hWnd, "visible", "", &m_hWindow);
		//SetCheck("father");
		SetPart(m_hWindow, -1, -1, -1, -1);
		SetColor(m_hWindow, "green");
		SetLineWidth(m_hWindow, 1);
	}
	catch (HException& exception)
	{
		AfxMessageBox(exception.ErrorMessage());
		AfxMessageBox(_T("InitHalcon失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		return FALSE;
	}
	return TRUE;
}

//BOOL CHalconWndDlg::LoadImageFromCamera(LPCSTR szImagePath)
BOOL CHalconWndDlg::LoadImageFromCamera(HImage hoImgCamera)
{
	CRect rect;
	GetClientRect(&rect);

	try
	{
		//ReadImage(&m_hoImage,szImagePath);
		m_hoImage = hoImgCamera;
		//GenEmptyObj(&m_hoXldContour);
		GetImageSize(m_hoImage,&m_hvImageWidth,&m_hvImageHeight);
		//if(! this->InitHalcon(0,0, m_hvImageWidth, m_hvImageHeight) )
		//	return FALSE;
		SetPart(m_hWindow,0, 0, m_hvImageHeight, m_hvImageWidth);
		//DispObj(m_hoImage,m_hWindow);
		//缩放1.0倍
		m_dbZoomFactor = (double)rect.Height() / (double)m_hvImageHeight;
		this->Zoom(m_dbZoomFactor);
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("LoadImageFromCamera窗口失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		return FALSE;
	}
	return TRUE;
}

void CHalconWndDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_HORZ, &minpos, &maxpos); 
	maxpos = GetScrollLimit(SB_HORZ);
 
	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_HORZ);
 
	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;
 
	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;
 
	case SB_ENDSCROLL:   // End scroll.
		break;
 
	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;
 
	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;
 
	case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_HORZ, &info, SIF_ALL);
 
			if (curpos > minpos)
				curpos = max(minpos, curpos - (int) info.nPage);
		}
		break;
 
	case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_HORZ, &info, SIF_ALL);
 
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int) info.nPage);
		}
		break;
 
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;
 
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}
 
	// Set the new position of the thumb (scroll box).
	SetScrollPos(SB_HORZ, curpos);
	ScrollWindow(m_nLastHorzPos-curpos,0);
 
	m_nLastHorzPos = curpos;
	UpdateWindow();
	
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHalconWndDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int minpos = 0;
	int maxpos = 0;
	GetScrollRange(SB_VERT, &minpos, &maxpos); 
	maxpos = GetScrollLimit(SB_VERT);
 
	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_VERT);
 
	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;
 
	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;
 
	case SB_ENDSCROLL:   // End scroll.
		break;
 
	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;
 
	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;
 
	case SB_PAGELEFT:    // Scroll one page left.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_VERT, &info, SIF_ALL);
 
			if (curpos > minpos)
				curpos = max(minpos, curpos - (int) info.nPage);
		}
		break;
 
	case SB_PAGERIGHT:      // Scroll one page right.
		{
			// Get the page size. 
			SCROLLINFO   info;
			GetScrollInfo(SB_VERT, &info, SIF_ALL);
 
			if (curpos < maxpos)
				curpos = min(maxpos, curpos + (int) info.nPage);
		}
		break;
 
	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;
 
	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}
 
	// Set the new position of the thumb (scroll box).
	SetScrollPos(SB_VERT, curpos);
	ScrollWindow(0,m_nLastVertPos - curpos);
 
	m_nLastVertPos = curpos;
	UpdateWindow();
	
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CHalconWndDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if(m_bDrawingArea)
		return FALSE;

	if(zDelta < 0)
		return this->ZoomOut();
	else
		return this->ZoomIn();

}
BOOL CHalconWndDlg::DrawRectangle1()
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	HTuple Row1,Column1,Row2,Column2;
	try
	{
		HalconCpp::DrawRectangle1(m_hWindow, &Row1, &Column1, &Row2, &Column2);
	}
	catch (HException& exception)
	{
		//AfxMessageBox(_T("画矩形失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}

BOOL CHalconWndDlg::DrawRectangle2()
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	HTuple Row, Column, Phi, Length1, Length2;
	try
	{
		HalconCpp::DrawRectangle2(m_hWindow, &Row, &Column, &Phi, &Length1, &Length2);
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画斜矩形失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}
BOOL CHalconWndDlg::DrawRectangle2Mod(HTuple hvRowIn, HTuple hvColumnIn, HTuple hvPhiIn, HTuple hvLengthIn, HTuple hvWidthIn,
	HTuple* hvRowOut, HTuple* hvColumnOut, HTuple* hvPhiOut, HTuple* hvLengthOut, HTuple* hvWidthOut)
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	try
	{
		HalconCpp::DrawRectangle2Mod(m_hWindow, hvRowIn, hvColumnIn, hvPhiIn, hvLengthIn, hvWidthIn,
			&(*hvRowOut), &(*hvColumnOut), &(*hvPhiOut), &(*hvLengthOut), &(*hvWidthOut));
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画矩形失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}

BOOL CHalconWndDlg::DrawCircle()
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	HTuple Row, Column, Radius;
	try
	{
		HalconCpp::DrawCircle(m_hWindow, &Row, &Column, &Radius);
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画圆形失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}
BOOL CHalconWndDlg::DrawCircleMod(HTuple hvRowIn, HTuple hvColumnIn, HTuple hvRaiusIn, HTuple* hvRowOut, HTuple* hvColumnOut, HTuple* hvRadiusOut)
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	try
	{
		HalconCpp::DrawCircleMod(m_hWindow, hvRowIn, hvColumnIn, hvRaiusIn, &(*hvRowOut), &(*hvColumnOut), &(*hvRadiusOut));
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画圆形失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}
BOOL CHalconWndDlg::DrawEllipse()
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	HTuple Row, Column, Phi, Radius1, Radius2;
	try
	{
		HalconCpp::DrawEllipse(m_hWindow, &Row, &Column, &Phi, &Radius1, &Radius2);
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画椭圆失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}
BOOL CHalconWndDlg::DrawPolygon()
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	HObject polygon;
	try
	{
		HalconCpp::DrawPolygon(&polygon, m_hWindow);
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画多边形失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}

BOOL CHalconWndDlg::DrawRegion()
{
	if (m_bDrawingArea)
		return FALSE;
	m_bDrawingArea = TRUE;

	HObject region;
	try
	{
		HalconCpp::DrawRegion(&region, m_hWindow);
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("画区域失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		m_bDrawingArea = FALSE;
		return FALSE;
	}

	m_bDrawingArea = FALSE;
	return TRUE;
}

BOOL CHalconWndDlg::DrawArea(UINT nMode)
{
	switch (nMode)
	{
	case DRAW_RECTANGLE1:
		return this->DrawRectangle1();
	case DRAW_RECTANGLE2:
		return this->DrawRectangle2();
	case DRAW_CIRCLE:
		return this->DrawCircle();
	case DRAW_ELLIPSE:
		return this->DrawEllipse();
	case DRAW_POLYGON:
		return this->DrawPolygon();
	case DRAW_REGION:
		return this->DrawRegion();
	default:
		return FALSE;
	}
}
BOOL CHalconWndDlg::IsDrawingArea()
{
	return m_bDrawingArea;
}

BOOL CHalconWndDlg::ZoomIn()
{
	return this->Zoom(m_dbZoomFactor*1.10);
}
BOOL CHalconWndDlg::ZoomOut()
{
	return this->Zoom(m_dbZoomFactor*0.90);
}
double CHalconWndDlg::GetZoomFactor()
{
	return m_dbZoomFactor;
}

BOOL CHalconWndDlg::Zoom(double fFactor)
{
	CRect rect;
	GetClientRect(&rect);

	//缩放率控制
	if (((double)rect.Width() / (double)rect.Height()) < (m_hvImageWidth.D() / m_hvImageHeight.D()))
	{
		if (fFactor < ((double)rect.Width() / m_hvImageWidth.D()))
			fFactor = (double)rect.Width() / m_hvImageWidth.D();
	}
	else
	{
		if (fFactor < ((double)rect.Height() / m_hvImageHeight.D()))
			fFactor = (double)rect.Height() / m_hvImageHeight.D();
	}
	if(fFactor > 1 )
		fFactor = 1;
	m_dbZoomFactor = fFactor;

	//获取窗口大小
	int nZoomWidth = (int)(fFactor * (double)m_hvImageWidth);
	int nZoomHeight = (int)(fFactor * (double)m_hvImageHeight);

	try
	{
		HalconCpp::SetSystem("flush_graphic", "false");
		//ClearWindow(m_hWindow);
		SetWindowExtents(m_hWindow, 0, 0, nZoomWidth, nZoomHeight);
		DispObj(m_hoImage, m_hWindow);
		//显示十字靶标
		SetColor(m_hWindow, "green");
		DispLine(m_hWindow, m_hvImageHeight / 2, 0, m_hvImageHeight / 2, m_hvImageWidth);
		DispLine(m_hWindow, 0, m_hvImageWidth / 2, m_hvImageHeight, m_hvImageWidth / 2);
		//DispObj(m_hoXldContour, m_hWindow);		
		HalconCpp::SetSystem("flush_graphic", "true");
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("缩放显示失败"));
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		return FALSE;
	}

	//设置滚动条范围
	//CRect rect;
	//GetClientRect(rect);
	if( nZoomWidth > rect.Width() )
	{
		int curPosH = (nZoomWidth - rect.Width()) / 2;
		ShowScrollBar(SB_HORZ, TRUE);
		SetScrollRange(SB_HORZ, 0, nZoomWidth - rect.Width(), TRUE);
		SetScrollPos(SB_HORZ, 0);
		m_nLastHorzPos = 0;

		//中心缩放
		SetScrollPos(SB_HORZ, curPosH);
		ScrollWindow(m_nLastHorzPos - curPosH, 0);
		m_nLastHorzPos = curPosH;
		UpdateWindow();

	}
	else
	{
		SetScrollPos(SB_HORZ, 0);
		ShowScrollBar(SB_HORZ, FALSE);
	}

	if( nZoomHeight > rect.Height() )
	{
		int curPosV = (nZoomHeight - rect.Height()) / 2;
		ShowScrollBar(SB_VERT, TRUE);
		SetScrollRange(SB_VERT, 0, nZoomHeight - rect.Height(), TRUE);
		SetScrollPos(SB_VERT, 0);
		m_nLastVertPos = 0;

		//中心缩放
		SetScrollPos(SB_VERT, curPosV);
		ScrollWindow(0, m_nLastVertPos - curPosV);
		m_nLastVertPos = curPosV;
		UpdateWindow();

	}
	else
	{
		SetScrollPos(SB_VERT, 0);
		ShowScrollBar(SB_VERT, FALSE);
	}


	return TRUE;
}


//BOOL CHalconWndDlg::DispContour(HObject hoXld, CString strColor, int nLineWidth)
//{
//	
//	return TRUE;
//}


BOOL CHalconWndDlg::NewModelCircleHalcon(double fModelCircleRadiusIn, double* fModelCircleRadiusOut)
{
	HObject hoContourCircle, hoModelCircle;
	HObject hoContourCircleCentered, ho_ContCircleModelImage, ho_ContCircleModelRegion, ho_ContCircleModelRegionDilation;
	HTuple hvRow, hvColumn, hvRadius;
	HTuple	hvModelImageHeight, hvModelImageWidth, hv_Hom2d;
	try
	{
		DrawCircleMod(300, 300, (HTuple)fModelCircleRadiusIn, &hvRow, &hvColumn, &hvRadius);
		GenCircleContourXld(&hoContourCircle, 0, 0, hvRadius, 0, 6.28318, "positive", 1);

		hvModelImageHeight = hvRadius * 2 + 10;
		hvModelImageWidth = hvRadius * 2 + 10;
		HomMat2dIdentity(&hv_Hom2d);
		HomMat2dTranslate(hv_Hom2d, hvModelImageHeight / 2, hvModelImageWidth / 2, &hv_Hom2d);
		AffineTransContourXld(hoContourCircle, &hoContourCircleCentered, hv_Hom2d);
		GenImageConst(&ho_ContCircleModelImage, "byte", hvModelImageWidth, hvModelImageHeight);
		PaintXld(hoContourCircleCentered, ho_ContCircleModelImage, &ho_ContCircleModelImage, 255);
		Threshold(ho_ContCircleModelImage, &ho_ContCircleModelRegion, 10, 255);
		DilationRectangle1(ho_ContCircleModelRegion, &ho_ContCircleModelRegionDilation, 3, 3);
		ReduceDomain(ho_ContCircleModelImage, ho_ContCircleModelRegionDilation, &hoModelCircle);

		//m_modelMarkPoint = MarkPointModel();
		m_modelMarkPoint = HalconModel();
		m_modelMarkPoint.m_strModelType = _T("圆");
		m_modelMarkPoint.m_hoImg = m_hoImage;
		m_modelMarkPoint.m_hoXldModel = hoModelCircle;
		m_modelMarkPoint.m_hvModelOriginRow = 0;
		m_modelMarkPoint.m_hvModelOriginColumn = 0;

		*fModelCircleRadiusOut = hvRadius.D();
		return TRUE;
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("生成定位圆失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
		*fModelCircleRadiusOut = 0;
		return FALSE;
	}

}

BOOL CHalconWndDlg::NewModelCrossHalcon(double fModelCrossLengthIn, double fModelCrossWidthIn, double* fModelCrossLengthOut, double* fModelCrossWidthOut)
{
	HObject	ho_Rectangle1, ho_Rectangle2, ho_ContoursUnion;
	HTuple	hvRectRow, hvRectColumn, hvRectPhi, hvRectLength, hvRectWidth;
	HTuple  hv_crossRow, hv_crossCloumn, hv_crossLength, hv_crossWidth;

	try
	{
		//画矩形
		DrawRectangle2Mod(300, 300, 0, fModelCrossLengthIn, fModelCrossWidthIn,
						&hvRectRow, &hvRectColumn, &hvRectPhi ,&hvRectLength, &hvRectWidth);

		//画cross并生成Contour
		hv_crossRow = hvRectRow;
		hv_crossCloumn = hvRectColumn;
		hv_crossLength = hvRectLength;
		hv_crossWidth = hvRectWidth;
		GenRectangle2ContourXld(&ho_Rectangle1, hv_crossRow, hv_crossCloumn, 0, hv_crossWidth, hv_crossLength);
		GenRectangle2ContourXld(&ho_Rectangle2, hv_crossRow, hv_crossCloumn, 0, hv_crossLength, hv_crossWidth);
		Union2ClosedContoursXld(ho_Rectangle1, ho_Rectangle2, &ho_ContoursUnion);
		SetColor(m_hWindow, "red");
		DispObj(ho_ContoursUnion, m_hWindow);

		//暂存模板参数
		//m_modelMarkPoint = MarkPointModel();
		m_modelMarkPoint = HalconModel();
		m_modelMarkPoint.m_strModelType = _T("十字叉");
		m_modelMarkPoint.m_hoImg = m_hoImage;
		m_modelMarkPoint.m_hoXldModel = ho_ContoursUnion;
		m_modelMarkPoint.m_hvModelOriginRow = 0;
		m_modelMarkPoint.m_hvModelOriginColumn = 0;

		*fModelCrossLengthOut = hv_crossLength.D();
		*fModelCrossWidthOut = hv_crossWidth.D();
		return TRUE;
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("生成定位十字叉失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;

		*fModelCrossLengthOut = 0;
		*fModelCrossWidthOut = 0;
		return FALSE;
	}
}

BOOL CHalconWndDlg::NewModelRectOutlineHalcon(double fModelRectWidthIn, double fModelRectHeightIn, double* fModelRectWidthOut, double* fModelRectHeightOut)
{
	//HObject  ho_Junctions, ho_Cross, ho_Rect, hoImageReduced;
	//HTuple  hv_SigmaGrad, hv_SigmaInt, hv_SigmaPoints, hv_ThreshInhom;
	//HTuple  hv_RowJunctions, hv_ColJunctions, hv_CoRRJunctions, hv_JunctionLength;
	//HTuple  hv_CoRCJunctions, hv_CoCCJunctions, hv_RowArea;
	//HTuple  hv_ColArea, hv_CoRRArea, hv_CoRCArea, hv_CoCCArea;

	//HTuple	hv_Button, hv_MouseRow, hv_MouseColumn;
	//HTuple	hv_Index, hv_NearestDistance, hv_NearestIndex, hv_Distance;
	//HTuple	hv_RectRow, hv_RectColumn, hv_RectPhi, hv_RectWidth, hv_RectHeight;
	try
	{
		////生成角点
		//hv_SigmaGrad = 1.0;
		//hv_SigmaInt = 2.0;
		//hv_SigmaPoints = 3.0;
		//hv_ThreshInhom = 400;

		//PointsFoerstner(m_hoImage, hv_SigmaGrad, hv_SigmaInt, hv_SigmaPoints, hv_ThreshInhom,
		//	0.1, "gauss", "false", &hv_RowJunctions, &hv_ColJunctions, &hv_CoRRJunctions,
		//	&hv_CoRCJunctions, &hv_CoCCJunctions, &hv_RowArea, &hv_ColArea, &hv_CoRRArea,
		//	&hv_CoRCArea, &hv_CoCCArea);
		//GenCrossContourXld(&ho_Junctions, hv_RowJunctions, hv_ColJunctions, 50, HTuple(45).TupleRad());
		//SetColor(m_hWindow, "cyan");
		//DispObj(ho_Junctions, m_hWindow);

		////选择角点
		//TupleLength(hv_RowJunctions, &hv_JunctionLength);
		//while (1)
		//{
		//	//Select region with the mouse
		//	//Use right mouse button to quit the loop
		//	GetMbutton(m_hWindow, &hv_MouseRow, &hv_MouseColumn, &hv_Button);
		//	if (4 == hv_Button)
		//	{
		//		break;
		//	}

		//	SetColor(m_hWindow, "cyan");
		//	DispObj(ho_Junctions, m_hWindow);

		//	hv_NearestDistance = 3000;
		//	hv_NearestIndex = 0;
		//	HTuple end_val37 = hv_JunctionLength - 1;
		//	HTuple step_val37 = 1;
		//	for (hv_Index = 0; hv_Index.Continue(end_val37, step_val37); hv_Index += step_val37)
		//	{
		//		DistancePp(HTuple(hv_RowJunctions[hv_Index]), HTuple(hv_ColJunctions[hv_Index]),
		//			hv_MouseRow, hv_MouseColumn, &hv_Distance);
		//		if (0 != (hv_Distance < hv_NearestDistance))
		//		{
		//			hv_NearestDistance = hv_Distance;
		//			hv_NearestIndex = hv_Index;
		//		}
		//	}
		//	GenCrossContourXld(&ho_Cross, HTuple(hv_RowJunctions[hv_NearestIndex]), HTuple(hv_ColJunctions[hv_NearestIndex]), 50, HTuple(45).TupleRad());
		//	SetColor(m_hWindow, "red");
		//	DispObj(ho_Cross, m_hWindow);
		//}

		////生成矩形外框
		//DrawRectangle2Mod(hv_RowJunctions[hv_NearestIndex], hv_ColJunctions[hv_NearestIndex], 0, fModelRectWidthIn, fModelRectHeightIn, &hv_RectRow, &hv_RectColumn, &hv_RectPhi, &hv_RectWidth, &hv_RectHeight);

		////生成模板
		//GenRectangle2(&ho_Rect, hv_RectRow, hv_RectColumn, hv_RectPhi, hv_RectWidth, hv_RectHeight);
		//ReduceDomain(m_hoImage, ho_Rect, &hoImageReduced);


		HObject ho_Region, ho_Line1, ho_Line2, ho_Contours, ho_Cross, ho_Rect, ho_ModelContour;
		HTuple	hv_RgnRow1, hv_RgnColumn1, hv_RgnRow2, hv_RgnColumn2;
		HTuple	hv_ResultRow, hv_ResultColumn, hv_Length;
		HTuple	hv_Row11, hv_Column11, hv_Row12, hv_Column12;
		HTuple	hv_Row21, hv_Column21, hv_Row22, hv_Column22;
		HTuple	hv_CrossRow, hv_CrossColumn, hv_IsOverlapping;
		HTuple	hv_RectRow1, hv_RectColumn1, hv_RectRow2, hv_RectColumn2;
		HTuple	hv_RectRow, hv_RectColumn, hv_RectPhi, hv_RectWidth, hv_RectHeight;

		//画两个直线卡尺
		SetColor(m_hWindow, "cyan");
		draw_rake(&ho_Region, m_hWindow, 30, 60, 15, &hv_RgnRow1, &hv_RgnColumn1, &hv_RgnRow2, &hv_RgnColumn2);
		rake(m_hoImage, &ho_Region, 30, 60, 15, 1, 20, "all", "max", hv_RgnRow1, hv_RgnColumn1, hv_RgnRow2, hv_RgnColumn2, &hv_ResultRow, &hv_ResultColumn);
		TupleLength(hv_ResultRow, &hv_Length);
		pts_to_best_line(&ho_Line1, hv_ResultRow, hv_ResultColumn, hv_Length, &hv_Row11, &hv_Column11, &hv_Row12, &hv_Column12);

		draw_rake(&ho_Region, m_hWindow, 30, 60, 15, &hv_RgnRow1, &hv_RgnColumn1, &hv_RgnRow2, &hv_RgnColumn2);
		rake(m_hoImage, &ho_Region, 30, 60, 15, 1, 20, "all", "max", hv_RgnRow1, hv_RgnColumn1, hv_RgnRow2, hv_RgnColumn2, &hv_ResultRow, &hv_ResultColumn);
		TupleLength(hv_ResultRow, &hv_Length);
		pts_to_best_line(&ho_Line2, hv_ResultRow, hv_ResultColumn, hv_Length, &hv_Row21, &hv_Column21, &hv_Row22, &hv_Column22);

		//生成模板直线，计算模板图像中心
		ConcatObj(ho_Line1, ho_Line2, &ho_Contours);	
		SmallestRectangle1Xld(ho_Contours, &hv_RectRow1, &hv_RectColumn1, &hv_RectRow2, &hv_RectColumn2);
		GenRectangle1(&ho_Rect, hv_RectRow1, hv_RectColumn1, hv_RectRow2, hv_RectColumn2);
		Union1(ho_Rect, &ho_Rect);
		SmallestRectangle2(ho_Rect, &hv_RectRow, &hv_RectColumn, &hv_RectPhi, &hv_RectWidth, &hv_RectHeight);

		SetColor(m_hWindow, "red");
		DispObj(ho_Contours, m_hWindow);

		//计算俩直线中心，以该点为modelOrigin
		IntersectionLines(hv_Row11, hv_Column11, hv_Row12, hv_Column12, hv_Row21, hv_Column21, hv_Row22, hv_Column22, &hv_CrossRow, &hv_CrossColumn, &hv_IsOverlapping);
		SetColor(m_hWindow, "cyan");
		DispCross(m_hWindow, hv_CrossRow, hv_CrossColumn, 50, 0);

		//m_modelMarkPoint = MarkPointModel();
		m_modelMarkPoint = HalconModel();
		m_modelMarkPoint.m_strModelType = _T("矩形轮廓");
		m_modelMarkPoint.m_hoImg = m_hoImage;
		m_modelMarkPoint.m_hoXldModel = ho_Contours;
		m_modelMarkPoint.m_hvModelOriginRow = hv_CrossRow - hv_RectRow;
		m_modelMarkPoint.m_hvModelOriginColumn = hv_CrossColumn - hv_RectColumn;

		//*fModelRectWidthOut = hv_RectWidth.D();
		//*fModelRectHeightOut = hv_RectHeight.D();
		*fModelRectWidthOut = 0;
		*fModelRectHeightOut = 0;
		return TRUE;
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("生成定位矩形轮廓失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;

		*fModelRectWidthOut = 0;
		*fModelRectHeightOut = 0;
		return FALSE;
	}
}


int CHalconWndDlg::MatchModelHalcon(double fScaleMin, double fScaleMax, double fMinScore, double* fPoxX, double* fPoxY, double fPixelSize)
{
	HObject hoImage, hoModel, hoModelContour, hoModelContourAffine;
	HTuple  hv_ModelID, hv_Row, hv_Column, hv_Angle, hv_Scale, hv_Score;
	HTuple	hv_Length, HomMat2D, hv_PosX, hv_PosY;
	HTuple	hv_Class;
	HTuple	hv_ModelOriginRow, hv_ModelOriginColumn;

	try
	{
		hoImage = m_modelMarkPoint.m_hoImg;
		hoModel = m_modelMarkPoint.m_hoXldModel;
		hv_ModelOriginRow = m_modelMarkPoint.m_hvModelOriginRow;
		hv_ModelOriginColumn = m_modelMarkPoint.m_hvModelOriginColumn;
		//WriteImage(hoModel, "bmp", 0, _T("./hoModel.bmp"));

		//清空窗口
		ClearWindow(m_hWindow);
		SetColor(m_hWindow, "green");
		DispObj(hoImage, m_hWindow);
		DispLine(m_hWindow, m_hvImageHeight / 2, 0, m_hvImageHeight / 2, m_hvImageWidth);
		DispLine(m_hWindow, 0, m_hvImageWidth / 2, m_hvImageHeight, m_hvImageWidth / 2);

		//抓标
		GetObjClass(hoModel, &hv_Class);
		if (hv_Class == HTuple("image"))
			CreateScaledShapeModel(hoModel, "auto", -0.39, 0.79, "auto", fScaleMin, fScaleMax,
				"auto", "auto", "ignore_local_polarity", "auto", "auto", &hv_ModelID);
		else
			CreateScaledShapeModelXld(hoModel, "auto", -0.39, 0.79, "auto", fScaleMin, fScaleMax,
				"auto", "auto", "ignore_local_polarity", 5, &hv_ModelID);
		SetShapeModelOrigin(hv_ModelID, hv_ModelOriginRow, hv_ModelOriginColumn);
		GetShapeModelContours(&hoModelContour, hv_ModelID, 1);
		FindScaledShapeModel(hoImage, hv_ModelID, -0.39, 0.78, fScaleMin, fScaleMax, fMinScore, 0, 0.1,
			"least_squares", 0, 0.9, &hv_Row, &hv_Column, &hv_Angle, &hv_Scale, &hv_Score);
		ClearShapeModel(hv_ModelID);

		TupleLength(hv_Row, &hv_Length);
		switch (hv_Length.I())
		{
		case 0:
			return 0;
		case 1:
			//显示抓标轮廓
			HomMat2dIdentity(&HomMat2D);
			HomMat2dScale(HomMat2D, hv_Scale, hv_Scale, 0, 0, &HomMat2D);
			HomMat2dRotate(HomMat2D, hv_Angle, 0, 0, &HomMat2D);
			HomMat2dTranslate(HomMat2D, hv_Row, hv_Column, &HomMat2D);
			AffineTransContourXld(hoModelContour, &hoModelContourAffine, HomMat2D);
			SetColor(m_hWindow, "red");
			DispObj(hoModelContourAffine, m_hWindow);

			SetColor(m_hWindow, "cyan");
			DispCross(m_hWindow, hv_Row, hv_Column, 50, hv_Angle);

			//显示抓标文字信息
			hv_PosX = (hv_Column - m_hvImageWidth / 2) * (HTuple)fPixelSize;
			hv_PosY = (hv_Row - m_hvImageHeight / 2) * (HTuple)fPixelSize;
			hv_PosY = -hv_PosY;
			DispText(m_hWindow, ((("PosX: " + hv_PosX).TupleConcat("PosY: " + hv_PosY)).TupleConcat("Angle: " + hv_Angle.TupleDeg())).TupleConcat("Scale: " + hv_Scale),
				"image", hv_Row + 3, hv_Column + 3, "black", HTuple(), HTuple());

			//回传相对位置坐标
			*fPoxX = hv_PosX.D();
			*fPoxY = hv_PosY.D();

			//模板信息暂存
			m_modelMarkPoint.m_hoXldModelContourAffine = hoModelContourAffine;
			m_modelMarkPoint.m_hvModelScaleMin = fScaleMin;
			m_modelMarkPoint.m_hvModelScaleMax = fScaleMax;
			m_modelMarkPoint.m_hvModelMinScore = fMinScore;

			return 1;
		default:
			return hv_Length.I();
		}
	}
	catch (HException& exception)
	{
		AfxMessageBox(_T("匹配定位点失败"));
		AfxMessageBox(exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;

		*fPoxX = 0;
		*fPoxY = 0;
		return 0;
	}
}

void CHalconWndDlg::draw_rake(HObject* ho_Regions, HTuple hv_WindowHandle, HTuple hv_Elements,
	HTuple hv_DetectHeight, HTuple hv_DetectWidth, HTuple* hv_Row1, HTuple* hv_Column1,
	HTuple* hv_Row2, HTuple* hv_Column2)
{

	// Local iconic variables
	HObject  ho_RegionLines, ho_Rectangle, ho_Arrow1;

	// Local control variables
	HTuple  hv_ATan, hv_Deg1, hv_Deg, hv_i, hv_RowC;
	HTuple  hv_ColC, hv_Distance, hv_RowL2, hv_RowL1, hv_ColL2;
	HTuple  hv_ColL1;

	//disp_message(hv_WindowHandle, //'点击鼠标左键画一条直线,点击右键确认'
	//	HTuple("\265\343\273\367\312\363\261\352\327\363\274\374\273\255\322\273\314\365\326\261\317\337,\265\343\273\367\323\322\274\374\310\267\310\317"),
	//	"window", 12, 12, "red", "false");
	GenEmptyObj(&(*ho_Regions));
	DrawLine(hv_WindowHandle, &(*hv_Row1), &(*hv_Column1), &(*hv_Row2), &(*hv_Column2));
	//disp_line (WindowHandle, Row1, Column1, Row2, Column2)
	GenRegionLine(&ho_RegionLines, (*hv_Row1), (*hv_Column1), (*hv_Row2), (*hv_Column2));
	ConcatObj((*ho_Regions), ho_RegionLines, &(*ho_Regions));
	TupleAtan2((-(*hv_Row2)) + (*hv_Row1), (*hv_Column2) - (*hv_Column1), &hv_ATan);
	TupleDeg(hv_ATan, &hv_Deg1);

	hv_ATan += HTuple(90).TupleRad();

	TupleDeg(hv_ATan, &hv_Deg);


	{
		HTuple end_val14 = hv_Elements;
		HTuple step_val14 = 1;
		for (hv_i = 1; hv_i.Continue(end_val14, step_val14); hv_i += step_val14)
		{
			hv_RowC = (*hv_Row1) + ((((*hv_Row2) - (*hv_Row1)) * hv_i) / (hv_Elements + 1));
			hv_ColC = (*hv_Column1) + ((((*hv_Column2) - (*hv_Column1)) * hv_i) / (hv_Elements + 1));

			if (0 != (hv_Elements == 1))
			{
				DistancePp((*hv_Row1), (*hv_Column1), (*hv_Row2), (*hv_Column2), &hv_Distance);
				GenRectangle2ContourXld(&ho_Rectangle, hv_RowC, hv_ColC, hv_Deg.TupleRad(),
					hv_DetectHeight / 2, hv_Distance / 2);
			}
			else
			{
				GenRectangle2ContourXld(&ho_Rectangle, hv_RowC, hv_ColC, hv_Deg.TupleRad(),
					hv_DetectHeight / 2, hv_DetectWidth / 2);
			}

			ConcatObj((*ho_Regions), ho_Rectangle, &(*ho_Regions));
			if (0 != (hv_i == 1))
			{
				hv_RowL2 = hv_RowC + ((hv_DetectHeight / 2) * ((-hv_ATan).TupleSin()));
				hv_RowL1 = hv_RowC - ((hv_DetectHeight / 2) * ((-hv_ATan).TupleSin()));
				hv_ColL2 = hv_ColC + ((hv_DetectHeight / 2) * ((-hv_ATan).TupleCos()));
				hv_ColL1 = hv_ColC - ((hv_DetectHeight / 2) * ((-hv_ATan).TupleCos()));
				gen_arrow_contour_xld(&ho_Arrow1, hv_RowL1, hv_ColL1, hv_RowL2, hv_ColL2, 25,
					25);
				ConcatObj((*ho_Regions), ho_Arrow1, &(*ho_Regions));
			}
		}
	}

	return;
}

// Chapter: XLD / Creation
// Short Description: Creates an arrow shaped XLD contour. 
void CHalconWndDlg::gen_arrow_contour_xld(HObject* ho_Arrow, HTuple hv_Row1, HTuple hv_Column1,
	HTuple hv_Row2, HTuple hv_Column2, HTuple hv_HeadLength, HTuple hv_HeadWidth)
{

	// Local iconic variables
	HObject  ho_TempArrow;

	// Local control variables
	HTuple  hv_Length, hv_ZeroLengthIndices, hv_DR;
	HTuple  hv_DC, hv_HalfHeadWidth, hv_RowP1, hv_ColP1, hv_RowP2;
	HTuple  hv_ColP2, hv_Index;

	//This procedure generates arrow shaped XLD contours,
	//pointing from (Row1, Column1) to (Row2, Column2).
	//If starting and end point are identical, a contour consisting
	//of a single point is returned.
	//
	//input parameteres:
	//Row1, Column1: Coordinates of the arrows' starting points
	//Row2, Column2: Coordinates of the arrows' end points
	//HeadLength, HeadWidth: Size of the arrow heads in pixels
	//
	//output parameter:
	//Arrow: The resulting XLD contour
	//
	//The input tuples Row1, Column1, Row2, and Column2 have to be of
	//the same length.
	//HeadLength and HeadWidth either have to be of the same length as
	//Row1, Column1, Row2, and Column2 or have to be a single element.
	//If one of the above restrictions is violated, an error will occur.
	//
	//
	//Init
	GenEmptyObj(&(*ho_Arrow));
	//
	//Calculate the arrow length
	DistancePp(hv_Row1, hv_Column1, hv_Row2, hv_Column2, &hv_Length);
	//
	//Mark arrows with identical start and end point
	//(set Length to -1 to avoid division-by-zero exception)
	hv_ZeroLengthIndices = hv_Length.TupleFind(0);
	if (0 != (hv_ZeroLengthIndices != -1))
	{
		hv_Length[hv_ZeroLengthIndices] = -1;
	}
	//
	//Calculate auxiliary variables.
	hv_DR = (1.0 * (hv_Row2 - hv_Row1)) / hv_Length;
	hv_DC = (1.0 * (hv_Column2 - hv_Column1)) / hv_Length;
	hv_HalfHeadWidth = hv_HeadWidth / 2.0;
	//
	//Calculate end points of the arrow head.
	hv_RowP1 = (hv_Row1 + ((hv_Length - hv_HeadLength) * hv_DR)) + (hv_HalfHeadWidth * hv_DC);
	hv_ColP1 = (hv_Column1 + ((hv_Length - hv_HeadLength) * hv_DC)) - (hv_HalfHeadWidth * hv_DR);
	hv_RowP2 = (hv_Row1 + ((hv_Length - hv_HeadLength) * hv_DR)) - (hv_HalfHeadWidth * hv_DC);
	hv_ColP2 = (hv_Column1 + ((hv_Length - hv_HeadLength) * hv_DC)) + (hv_HalfHeadWidth * hv_DR);
	//
	//Finally create output XLD contour for each input point pair
	{
		HTuple end_val45 = (hv_Length.TupleLength()) - 1;
		HTuple step_val45 = 1;
		for (hv_Index = 0; hv_Index.Continue(end_val45, step_val45); hv_Index += step_val45)
		{
			if (0 != (HTuple(hv_Length[hv_Index]) == -1))
			{
				//Create_ single points for arrows with identical start and end point
				GenContourPolygonXld(&ho_TempArrow, HTuple(hv_Row1[hv_Index]), HTuple(hv_Column1[hv_Index]));
			}
			else
			{
				//Create arrow contour
				GenContourPolygonXld(&ho_TempArrow, ((((HTuple(hv_Row1[hv_Index]).TupleConcat(HTuple(hv_Row2[hv_Index]))).TupleConcat(HTuple(hv_RowP1[hv_Index]))).TupleConcat(HTuple(hv_Row2[hv_Index]))).TupleConcat(HTuple(hv_RowP2[hv_Index]))).TupleConcat(HTuple(hv_Row2[hv_Index])),
					((((HTuple(hv_Column1[hv_Index]).TupleConcat(HTuple(hv_Column2[hv_Index]))).TupleConcat(HTuple(hv_ColP1[hv_Index]))).TupleConcat(HTuple(hv_Column2[hv_Index]))).TupleConcat(HTuple(hv_ColP2[hv_Index]))).TupleConcat(HTuple(hv_Column2[hv_Index])));
			}
			ConcatObj((*ho_Arrow), ho_TempArrow, &(*ho_Arrow));
		}
	}
	return;
}

void CHalconWndDlg::pts_to_best_line(HObject* ho_Line, HTuple hv_Rows, HTuple hv_Cols, HTuple hv_ActiveNum,
	HTuple* hv_Row1, HTuple* hv_Col1, HTuple* hv_Row2, HTuple* hv_Col2)
{

	// Local iconic variables
	HObject  ho_Contour;

	// Local control variables
	HTuple  hv_Length, hv_Nr, hv_Nc, hv_Dist, hv_Length1;

	(*hv_Row1) = 0;
	(*hv_Col1) = 0;
	(*hv_Row2) = 0;
	(*hv_Col2) = 0;
	GenEmptyObj(&(*ho_Line));
	TupleLength(hv_Cols, &hv_Length);

	if (0 != (HTuple(hv_Length >= hv_ActiveNum).TupleAnd(hv_ActiveNum > 1)))
	{

		GenContourPolygonXld(&ho_Contour, hv_Rows, hv_Cols);
		FitLineContourXld(ho_Contour, "tukey", hv_ActiveNum, 0, 5, 2, &(*hv_Row1), &(*hv_Col1),
			&(*hv_Row2), &(*hv_Col2), &hv_Nr, &hv_Nc, &hv_Dist);
		TupleLength(hv_Dist, &hv_Length1);
		if (0 != (hv_Length1 < 1))
		{
			return;
		}
		GenContourPolygonXld(&(*ho_Line), (*hv_Row1).TupleConcat((*hv_Row2)), (*hv_Col1).TupleConcat((*hv_Col2)));

	}

	return;
}

void CHalconWndDlg::rake(HObject ho_Image, HObject* ho_Regions, HTuple hv_Elements, HTuple hv_DetectHeight,
	HTuple hv_DetectWidth, HTuple hv_Sigma, HTuple hv_Threshold, HTuple hv_Transition,
	HTuple hv_Select, HTuple hv_Row1, HTuple hv_Column1, HTuple hv_Row2, HTuple hv_Column2,
	HTuple* hv_ResultRow, HTuple* hv_ResultColumn)
{

	// Local iconic variables
	HObject  ho_Rectangle, ho_Arrow1;

	// Local control variables
	HTuple  hv_Width, hv_Height, hv_ATan, hv_Deg1;
	HTuple  hv_Deg, hv_i, hv_RowC, hv_ColC, hv_Distance, hv_RowL2;
	HTuple  hv_RowL1, hv_ColL2, hv_ColL1, hv_MsrHandle_Measure;
	HTuple  hv_RowEdge, hv_ColEdge, hv_Amplitude, hv_tRow, hv_tCol;
	HTuple  hv_t, hv_Number, hv_j;

	GetImageSize(ho_Image, &hv_Width, &hv_Height);

	GenEmptyObj(&(*ho_Regions));
	(*hv_ResultRow) = HTuple();
	(*hv_ResultColumn) = HTuple();
	TupleAtan2((-hv_Row2) + hv_Row1, hv_Column2 - hv_Column1, &hv_ATan);
	TupleDeg(hv_ATan, &hv_Deg1);

	hv_ATan += HTuple(90).TupleRad();

	TupleDeg(hv_ATan, &hv_Deg);


	{
		HTuple end_val13 = hv_Elements;
		HTuple step_val13 = 1;
		for (hv_i = 1; hv_i.Continue(end_val13, step_val13); hv_i += step_val13)
		{
			hv_RowC = hv_Row1 + (((hv_Row2 - hv_Row1) * hv_i) / (hv_Elements + 1));
			hv_ColC = hv_Column1 + (((hv_Column2 - hv_Column1) * hv_i) / (hv_Elements + 1));
			if (0 != (HTuple(HTuple(HTuple(hv_RowC > (hv_Height - 1)).TupleOr(hv_RowC < 0)).TupleOr(hv_ColC > (hv_Width - 1))).TupleOr(hv_ColC < 0)))
			{
				continue;
			}
			if (0 != (hv_Elements == 1))
			{
				DistancePp(hv_Row1, hv_Column1, hv_Row2, hv_Column2, &hv_Distance);
				GenRectangle2ContourXld(&ho_Rectangle, hv_RowC, hv_ColC, hv_Deg.TupleRad(),
					hv_DetectHeight / 2, hv_Distance / 2);
			}
			else
			{
				GenRectangle2ContourXld(&ho_Rectangle, hv_RowC, hv_ColC, hv_Deg.TupleRad(),
					hv_DetectHeight / 2, hv_DetectWidth / 2);
			}

			ConcatObj((*ho_Regions), ho_Rectangle, &(*ho_Regions));
			if (0 != (hv_i == 1))
			{
				hv_RowL2 = hv_RowC + ((hv_DetectHeight / 2) * ((-hv_ATan).TupleSin()));
				hv_RowL1 = hv_RowC - ((hv_DetectHeight / 2) * ((-hv_ATan).TupleSin()));
				hv_ColL2 = hv_ColC + ((hv_DetectHeight / 2) * ((-hv_ATan).TupleCos()));
				hv_ColL1 = hv_ColC - ((hv_DetectHeight / 2) * ((-hv_ATan).TupleCos()));
				gen_arrow_contour_xld(&ho_Arrow1, hv_RowL1, hv_ColL1, hv_RowL2, hv_ColL2, 25,
					25);
				ConcatObj((*ho_Regions), ho_Arrow1, &(*ho_Regions));
			}
			GenMeasureRectangle2(hv_RowC, hv_ColC, hv_Deg.TupleRad(), hv_DetectHeight / 2,
				hv_DetectWidth / 2, hv_Width, hv_Height, "nearest_neighbor", &hv_MsrHandle_Measure);


			if (0 != (hv_Transition == HTuple("negative")))
			{
				hv_Transition = "negative";
			}
			else
			{
				if (0 != (hv_Transition == HTuple("positive")))
				{

					hv_Transition = "positive";
				}
				else
				{
					hv_Transition = "all";
				}
			}

			if (0 != (hv_Select == HTuple("first")))
			{
				hv_Select = "first";
			}
			else
			{
				if (0 != (hv_Select == HTuple("last")))
				{

					hv_Select = "last";
				}
				else
				{
					hv_Select = "all";
				}
			}

			MeasurePos(ho_Image, hv_MsrHandle_Measure, hv_Sigma, hv_Threshold, hv_Transition,
				hv_Select, &hv_RowEdge, &hv_ColEdge, &hv_Amplitude, &hv_Distance);
			CloseMeasure(hv_MsrHandle_Measure);
			hv_tRow = 0;
			hv_tCol = 0;
			hv_t = 0;
			TupleLength(hv_RowEdge, &hv_Number);
			if (0 != (hv_Number < 1))
			{
				continue;
			}
			{
				HTuple end_val69 = hv_Number - 1;
				HTuple step_val69 = 1;
				for (hv_j = 0; hv_j.Continue(end_val69, step_val69); hv_j += step_val69)
				{
					if (0 != ((HTuple(hv_Amplitude[hv_j]).TupleAbs()) > hv_t))
					{

						hv_tRow = HTuple(hv_RowEdge[hv_j]);
						hv_tCol = HTuple(hv_ColEdge[hv_j]);
						hv_t = HTuple(hv_Amplitude[hv_j]).TupleAbs();
					}
				}
			}
			if (0 != (hv_t > 0))
			{

				(*hv_ResultRow) = (*hv_ResultRow).TupleConcat(hv_tRow);
				(*hv_ResultColumn) = (*hv_ResultColumn).TupleConcat(hv_tCol);
			}
		}
	}
	TupleLength((*hv_ResultRow), &hv_Number);


	return;
}

