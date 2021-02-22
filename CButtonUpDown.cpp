#include "stdafx.h"
#include "CButtonLongPush.h"
BEGIN_MESSAGE_MAP(CButtonLongPush, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CButtonLongPush::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonDown(nFlags, point);
}


void CButtonLongPush::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonUp(nFlags, point);
}
