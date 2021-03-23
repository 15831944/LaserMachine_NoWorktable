#pragma once


// CObjectProtyDlg2 �Ի���

class CObjectProtyDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CObjectProtyDlg2)

public:
	CObjectProtyDlg2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CObjectProtyDlg2();

// �Ի�������
	enum { IDD = IDD_OBJECT_PROPERTY_DLG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
private:
	int m_nSelGroup;
	double m_FillAngle;
	double m_FillGap;
	double m_FillCurtail;
	int m_OutlinePrior;
	int m_GapMode;
	int m_FillMode;
	BOOL m_FillEnable;
	byte m_Prior;
	double m_Angle[4];
	double m_Gap[4];
	double m_Curtail[4];
	byte m_GMode[4];
	byte m_FMode[4];
	bool m_Enable[4];
	byte m_nSel_Old;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedObjectPropertyDlg2Radio4();
	afx_msg void OnClickedObjectPropertyDlg2Check1();
	afx_msg void OnClickedObjectPropertyDlg2Save();
};
