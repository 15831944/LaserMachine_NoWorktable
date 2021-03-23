// CDialogAxisZMove.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CDialogAxisZMove.h"
#include "afxdialogex.h"
#include "DeviceCardMarkBSL.h"


// CDialogAxisZMove 对话框

IMPLEMENT_DYNAMIC(CDialogAxisZMove, CDialogEx)

CDialogAxisZMove::CDialogAxisZMove(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_AXIS_Z_MOVE, pParent)
{
	m_nCountMove = 0;
}

CDialogAxisZMove::~CDialogAxisZMove()
{
}

void CDialogAxisZMove::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogAxisZMove, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDialogAxisZMove::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialogAxisZMove 消息处理程序


BOOL CDialogAxisZMove::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
		//BSL板卡调扩展轴
	CDeviceCardMarkBSL* pBSL = (CDeviceCardMarkBSL*)pDevCardMark;
	if (pBSL != NULL)
	{
		if (WM_KEYDOWN == pMsg->message && VK_UP == pMsg->wParam)
		{
			if(20 > m_nCountMove)
				m_nCountMove++;
			pBSL->MoveAxisRel(0, m_nCountMove * DEFAULT_AXIS_Z_MOVE_UNIT);
		}
		else if (WM_KEYDOWN == pMsg->message && VK_DOWN == pMsg->wParam)
		{
			if (20 > m_nCountMove)
				m_nCountMove++;
			pBSL->MoveAxisRel(0, -m_nCountMove * DEFAULT_AXIS_Z_MOVE_UNIT);
		}
		else if (WM_KEYUP == pMsg->message)
		{
			m_nCountMove = 0;
		}
		else if (WM_KEYDOWN == pMsg->message && VK_LEFT == pMsg->wParam)
		{
			pBSL->MoveAxisRel(0, -2);
		}
		else if (WM_KEYDOWN == pMsg->message && VK_RIGHT == pMsg->wParam)
		{
			pBSL->MoveAxisRel(0, 2);
		}


	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogAxisZMove::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	int nnn = m_nCountMove;

	CDialogEx::OnCancel();
}
