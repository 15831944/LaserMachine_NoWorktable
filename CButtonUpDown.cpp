#include "stdafx.h"
#include "CButtonLongPush.h"
BEGIN_MESSAGE_MAP(CButtonLongPush, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CButtonLongPush::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnLButtonDown(nFlags, point);
}


void CButtonLongPush::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnLButtonUp(nFlags, point);
}
