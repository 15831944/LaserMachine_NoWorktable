#pragma once


// CObjectProtyDlg1 �Ի���

class CObjectProtyDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CObjectProtyDlg1)

public:
	CObjectProtyDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CObjectProtyDlg1();

// �Ի�������
	enum { IDD = IDD_OBJECT_PROPERTY_DLG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	UINT m_Duplicate;
	float m_GapDistance;
	virtual void OnOK();
};
