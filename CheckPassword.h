#pragma once


// CCheckPassword �Ի���

class CCheckPassword : public CDialog
{
	DECLARE_DYNAMIC(CCheckPassword)

public:
	CCheckPassword(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckPassword();

// �Ի�������
	enum { IDD = IDD_CHECKPASSWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CString m_strPassword;
	CString m_strCheckTitle;
};
