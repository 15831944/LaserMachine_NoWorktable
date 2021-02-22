#pragma once

#include "PointF.h"

// CDlgCameraPositionSetDestinedMarkPoint 对话框

class CDlgCameraPositionSetDestinedMarkPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCameraPositionSetDestinedMarkPoint)

public:
	CDlgCameraPositionSetDestinedMarkPoint(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgCameraPositionSetDestinedMarkPoint();

public:
	CPointF GetDestindPtPos();
	void SetDestinedPtPos(CPointF ptPosDestined);
	double m_fPostionSetDestinedMarkPointX;
	double m_fPostionSetDestinedMarkPointY;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAMERA_POSITION_SET_DESTINED_MARK_POINT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
