#pragma once
#include "ObjectProperty.h"
#include "afxwin.h"

// CObjPropertyDlgEdit �Ի���
class CObjPropertyDlgEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CObjPropertyDlgEdit)

public:
	CObjPropertyDlgEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CObjPropertyDlgEdit();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_OBJECT_PROPERTY_DLGEDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

// ����
public:
	CObjectProperty* m_pObjProty;
	CString m_ObjType;
	CComboBox m_LayerList1;
	BOOL m_bSizeChanged;
	float m_ProcessSpeed;
	BYTE m_ProcessTimes;
	BYTE m_ProcessMode;
	float m_ProcessPower;
	float m_ProcessFrequncy;
	float m_ProcessPulseWidth;
	float m_ProcessWaitTime;
	float m_Rise_Lenth_Step;
	double m_Start_X;
	double m_Start_Y;
	double m_End_X;
	double m_End_Y;
	double m_Center_X;
	double m_Center_Y;
	double m_Radius;
	double m_Ratio;
	double m_Start_Angle;
	double m_End_Angle;
	double m_RotateAngle;

// ʵ��
public:
	afx_msg void OnSelchangeObjProtyDlgeditCombox1();
	afx_msg void OnBnClickedChangeObjLayer();
	afx_msg void OnBnClickedChangeObjProty();
	afx_msg void OnBnClickedChangeLayerProty();
	afx_msg void OnBnClickedClearRedundLayer();
	afx_msg void OnBnClickedAddNewLayer();
	afx_msg void OnBnClickedModifyObj();
	afx_msg void OnBnClickedObjPathSort1();
	afx_msg void OnBnClickedObjPathSort2();
	afx_msg void OnBnClickedObjPathSort3();
	afx_msg void OnBnClickedObjPathSort4();
	afx_msg void OnBnClickedObjPathSort5();
};
