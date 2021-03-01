// CameraView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "CameraView.h"
#include "MainFrm.h"
#include "DeviceCameraDahengMER.h"
#include "DlgSetParaCamera.h"
#include "DeviceCardWorktable.h"
#include "CDlgDevCfgTabCamera.h"
#include "XSleep.h"
#include "Model.h"

// CCameraView

IMPLEMENT_DYNCREATE(CCameraView, CScrollView)

CCameraView::CCameraView()
{
	m_pHalconWnd = NULL;
}

CCameraView::~CCameraView()
{
	delete m_pHalconWnd;
	m_pHalconWnd = NULL;
}

void CCameraView::PostNcDestroy()
{
	m_pHalconWnd->DetachWnd();

	// Delete the C++ instance so the parent does not have
	// to worry about it.
	delete this;
}

void CCameraView::DoDataExchange(CDataExchange* pDX)
{
	// TODO: �ڴ����ר�ô����/����û���

	CScrollView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCameraView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDM_OPEN_CAMERA, &CCameraView::OnOpenCamera)
	ON_COMMAND(IDM_CLOSE_CAMERA, &CCameraView::OnCloseCamera)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//ON_COMMAND(ID_TEST_HALCON_CREATE_MODEL, &CCameraView::OnTestCreateModel)
	//ON_COMMAND(ID_TEST_HALCON_FIND_MODEL, &CCameraView::OnTestFindModel)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(IDM_SETPARA_CAMERA, &CCameraView::OnSetparaCamera)
	//ON_COMMAND(ID_TEST_HALCON_FIND_CIRCLE, &CCameraView::OnTestHalconFindCircle)
	ON_COMMAND(ID_TEST_HALCON_FIND_CIRCLE_HAND, &CCameraView::OnTestHalconFindCircleHand)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_LOCATE, &CCameraView::OnLocate)
	ON_COMMAND(IDM_CAMERA_AUTO_MATCH_CROSS, &CCameraView::OnCameraAutoMatchCross)
	ON_COMMAND(IDM_CAMERA_AUTO_MATCH_CIRCLE, &CCameraView::OnCameraAutoMatchCircle)
END_MESSAGE_MAP()


// CCameraView ��ͼ
void CCameraView::OnInitialUpdate()
{
	// TODO:  �������ͼ�ĺϼƴ�С
	//CSize sizeTotal = CSize(2592, 1944);
	//CSize sizeTotal = CSize(100, 100);
	//SetScrollSizes(MM_TEXT, sizeTotal);

	//m_pHalconWnd->InitHalconWnd(0, 0, (HTuple)sizeTotal.cx, (HTuple)sizeTotal.cy);											//��ʼ��halcon����

	CScrollView::OnInitialUpdate();

}
void CCameraView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CScrollView::OnPaint()
}
void CCameraView::OnDraw(CDC* pDC)
{

}


// CCameraView ���

#ifdef _DEBUG
void CCameraView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CCameraView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCameraView ��Ϣ�������
int CCameraView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pHalconWnd = new CHalconWnd;
	m_pHalconWnd->Create(NULL, _T("CHalconWnd"), WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL,
		CRect(0, 0, 0, 0), this, 0, NULL);
	m_pHalconWnd->AttachWnd(m_pHalconWnd);

	return 0;
}

BOOL CCameraView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return TRUE;
	return CScrollView::OnEraseBkgnd(pDC);
}


int CCameraView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// We handle this message so that when user clicks once in the
	// window, it will be given the focus, and this will allow
	// mousewheel messages to be directed to this window.
	SetFocus();

	return CScrollView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CCameraView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_pHalconWnd->OnHScroll(nSBCode, nPos, pScrollBar);

}


void CCameraView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_pHalconWnd->OnVScroll(nSBCode, nPos, pScrollBar);

}

BOOL CCameraView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//if (m_pCameraViewWnd->OnMouseWheel(nFlags, zDelta, pt))
	//{
	//	this->Invalidate();
	//}
	CRect rect;
	GetClientRect(&rect);

	m_pHalconWnd->OnMouseWheel(nFlags, zDelta, pt);

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}

void CCameraView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	CRect rect;
	GetClientRect(&rect);

	if (m_pHalconWnd != NULL && ::IsWindow(m_pHalconWnd->m_hWnd))
	{
		m_pHalconWnd->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(),
			SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Initialization: Set the display size if needed.
	// Resize and reposition the scrolling window.
	if (m_pHalconWnd != NULL && m_pHalconWnd->GetDisplaySize() == CSize(0, 0))
	{
		if (rect.Width() > 0 && rect.Height() > 0)
		{
			m_pHalconWnd->SetDisplaySize(rect.Width(), rect.Height());
			m_pHalconWnd->Zoom(1);
		}
	}

	m_pHalconWnd->OnSize(nType, cx, cy);

}


void CCameraView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//���halcon���ڻ�ͼ�Ͳ���Ӧ�Ҽ��˵�
	if (m_pHalconWnd->IsDrawingArea())
		return;


	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);
		point = rect.TopLeft();
		point.Offset(5, 5);
	}
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_POPUP_VIEW_CAMERA));
	if (m_pHalconWnd->m_bThreadsAreRunning)
	{
		menu.EnableMenuItem(IDM_OPEN_CAMERA, MF_DISABLED);
		menu.EnableMenuItem(IDM_CLOSE_CAMERA, MF_ENABLED);
	}
	else
	{
		menu.EnableMenuItem(IDM_OPEN_CAMERA, MF_ENABLED);
		menu.EnableMenuItem(IDM_CLOSE_CAMERA, MF_DISABLED);
	}

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);

}


void CCameraView::OnOpenCamera()
{
	m_pHalconWnd->OnOpenCamera();
}

void CCameraView::OnCloseCamera()
{
	m_pHalconWnd->OnCloseCamera();
}


//void CCameraView::OnTestCreateModel()
//{
//	// TODO: �ڴ���������������
//	//m_pHalconWnd->DrawRectangle1();
//	//m_pHalconWnd->DrawCircle();
//
//	m_pHalconWnd->TestCreateModel();
//	//m_pHalconWnd->TestDxf();
//}
//
//void CCameraView::OnTestFindModel()
//{
//	double fRadius, fPixelSize, fScaleMin, fScaleMax, fMinScore;
//	fRadius = ReadDevCameraMarkCircleRadius();
//	fPixelSize = ReadDevCameraPixelSize();
//	fMinScore = ReadDevCameraMarkCircleFindMinScore();
//	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
//	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();
//	HalconModel hoModel(_T("Բ"), fRadius, fPixelSize);
//	hoModel.SetScale(fScaleMin, fScaleMax);
//	hoModel.SetMinScore(fMinScore);
//
//	std::vector<CPointF> ptVec;
//	m_pHalconWnd->LocateModel(hoModel, &ptVec);
//}

void CCameraView::OnSetparaCamera()
{
	// TODO: �ڴ���������������
	CDlgSetParaCamera dlgSetParaCamera;
	dlgSetParaCamera.DoModal();
}


BOOL CCameraView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (NULL == pDevCardWorktable)
		return CScrollView::PreTranslateMessage(pMsg);

	double fCameraMoveUnit;
	//int nReverseX, nReverseY;
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		fCameraMoveUnit = ReadDevCameraMoveUnit();
		fCameraMoveUnit /= 1000;
		//nReverseX = ReadDevWorktableAxisXReverse();
		//nReverseY = ReadDevWorktableAxisYReverse();
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			//fCameraMoveUnit = (nReverseX) ? -fCameraMoveUnit : fCameraMoveUnit;
			pDevCardWorktable->PosMoveXYHand(-fCameraMoveUnit, 0);
			break;
		case VK_RIGHT:
			//fCameraMoveUnit = (nReverseX) ? -fCameraMoveUnit : fCameraMoveUnit;
			pDevCardWorktable->PosMoveXYHand(fCameraMoveUnit, 0);
			break;
		case VK_DOWN:
			//fCameraMoveUnit = (nReverseY) ? -fCameraMoveUnit : fCameraMoveUnit;
			pDevCardWorktable->PosMoveXYHand(0, -fCameraMoveUnit);
			break;
		case VK_UP:
			//fCameraMoveUnit = (nReverseY) ? -fCameraMoveUnit : fCameraMoveUnit;
			pDevCardWorktable->PosMoveXYHand(0, fCameraMoveUnit);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		//if (pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT)
		//{
		//	pDevCardWorktable->StopMoveX(TRUE);
		//}
		//else if (pMsg->wParam == VK_DOWN || pMsg->wParam == VK_UP)
		//{
		//	pDevCardWorktable->StopMoveY(TRUE);
		//}
		break;
	default:
		break;
	}

	return CScrollView::PreTranslateMessage(pMsg);
}


//void CCameraView::OnTestHalconFindCircle()
//{
//	// TODO: �ڴ���������������
//
//	//m_pHalconWnd->TestFindCircles();
//
//	//CArray <CPointF, CPointF&> arPtPos;
//	std::vector <CPointF> vPtPos;
//	if (FALSE == m_pHalconWnd->AutoFindCircle(&vPtPos))		//���ûץ��Բ
//		return;
//	if (1 < vPtPos.size())									//���ץ�����Բ
//		return;
//	if (NULL == pDevCardWorktable)							//���ץ��һ��
//		return;
//	CPointF ptTmp = vPtPos.front();
//	if(pDevCardWorktable)
//		pDevCardWorktable->PosMoveXYHand(ptTmp.x, ptTmp.y);	
//}


void CCameraView::OnTestHalconFindCircleHand()
{
	// TODO: �ڴ���������������
	if (FALSE == m_pHalconWnd->m_bThreadsAreRunning)
	{
		AfxMessageBox(_T("���ȴ����"));
		return;
	}

	m_pHalconWnd->TestFindCircleHand();

}


afx_msg LRESULT CCameraView::OnLocate(WPARAM wParam, LPARAM lParam)
{

	m_pHalconWnd->LocateModel(*((HalconModel*)wParam), (std::vector<CPointF>*)lParam);

	return 0;
}


void CCameraView::OnCameraAutoMatchCross()
{
	// TODO: �ڴ���������������
	if (FALSE == m_pHalconWnd->m_bThreadsAreRunning)
	{
		AfxMessageBox(_T("���ȴ����"));
		return;
	}

	double fLength, fWidth, fPixelSize, fScaleMin, fScaleMax, fMinScore;
	fLength = ReadDevCameraMarkCrossLength();
	fWidth = ReadDevCameraMarkCrossWidth();
	fPixelSize = ReadDevCameraPixelSize();
	fMinScore = ReadDevCameraMarkCircleFindMinScore();
	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();

	ModelBase* pModel = ModelFactory::creatModel(ModelType::MT_Cross, fPixelSize, fLength, fWidth);
	pModel->SetScale(fScaleMin, fScaleMax);
	pModel->SetMinScore(fMinScore);

	std::vector<CPointF> vecPtPos;
	pModel->LocateModel(vecPtPos);
}


void CCameraView::OnCameraAutoMatchCircle()
{
	// TODO: �ڴ���������������
	if (FALSE == m_pHalconWnd->m_bThreadsAreRunning)
	{
		AfxMessageBox(_T("���ȴ����"));
		return;
	}

	double fRadius, fPixelSize, fScaleMin, fScaleMax, fMinScore;
	fRadius = ReadDevCameraMarkCircleRadius();
	fPixelSize = ReadDevCameraPixelSize();
	fMinScore = ReadDevCameraMarkCircleFindMinScore();
	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();

	ModelBase* pModel = ModelFactory::creatModel(ModelType::MT_Circle, fPixelSize, fRadius);
	pModel->SetScale(fScaleMin, fScaleMax);
	pModel->SetMinScore(fMinScore);

	std::vector<CPointF> vecPtPos;
	pModel->LocateModel(vecPtPos);

}
