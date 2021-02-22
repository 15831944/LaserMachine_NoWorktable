// DlgCameraPositionSetDestinedMarkPoint.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "DlgCameraPositionSetDestinedMarkPoint.h"
#include "afxdialogex.h"
#include "CameraPosition.h"

// CDlgCameraPositionSetDestinedMarkPoint 对话框

IMPLEMENT_DYNAMIC(CDlgCameraPositionSetDestinedMarkPoint, CDialogEx)

CDlgCameraPositionSetDestinedMarkPoint::CDlgCameraPositionSetDestinedMarkPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAMERA_POSITION_SET_DESTINED_MARK_POINT, pParent)
	, m_fPostionSetDestinedMarkPointX(0)
	, m_fPostionSetDestinedMarkPointY(0)
{

}

CDlgCameraPositionSetDestinedMarkPoint::~CDlgCameraPositionSetDestinedMarkPoint()
{
}

void CDlgCameraPositionSetDestinedMarkPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POSITION_SET_DESTINED_MARK_POINT_X, m_fPostionSetDestinedMarkPointX);
	DDX_Text(pDX, IDC_EDIT_POSITION_SET_DESTINED_MARK_POINT_Y, m_fPostionSetDestinedMarkPointY);
}


BEGIN_MESSAGE_MAP(CDlgCameraPositionSetDestinedMarkPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgCameraPositionSetDestinedMarkPoint::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCameraPositionSetDestinedMarkPoint 消息处理程序


void CDlgCameraPositionSetDestinedMarkPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CDialogEx::OnOK();
}


BOOL CDlgCameraPositionSetDestinedMarkPoint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


CPointF CDlgCameraPositionSetDestinedMarkPoint::GetDestindPtPos()
{
	return CPointF((FLOAT)m_fPostionSetDestinedMarkPointX, (FLOAT)m_fPostionSetDestinedMarkPointY);
}

void CDlgCameraPositionSetDestinedMarkPoint::SetDestinedPtPos(CPointF ptPosDestined)
{
	m_fPostionSetDestinedMarkPointX = ptPosDestined.x;
	m_fPostionSetDestinedMarkPointY = ptPosDestined.y;
}
