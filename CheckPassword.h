#pragma once


// CCheckPassword 对话框

class CCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CCheckPassword)

public:
	CCheckPassword(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCheckPassword();

// 对话框数据
	enum { IDD = IDD_CHECKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_strPassword;
	CString m_strCheckTitle;
};
