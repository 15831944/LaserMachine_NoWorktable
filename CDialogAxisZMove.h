#pragma once

#define DEFAULT_AXIS_Z_MOVE_UNIT 0.05

// CDialogAxisZMove 对话框

class CDialogAxisZMove : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAxisZMove)

public:
	CDialogAxisZMove(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialogAxisZMove();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_AXIS_Z_MOVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedCancel();

protected:
	int m_nCountMove;
};
