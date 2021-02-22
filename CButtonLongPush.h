#pragma once
#include <afxwin.h>
class CButtonLongPush :
    public CButton
{
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

