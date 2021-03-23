#pragma once


// CObjectProtyDlg1 对话框

class CObjectProtyDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CObjectProtyDlg1)

public:
	CObjectProtyDlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CObjectProtyDlg1();

// 对话框数据
	enum { IDD = IDD_OBJECT_PROPERTY_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	UINT m_Duplicate;
	float m_GapDistance;
	virtual void OnOK();
};
