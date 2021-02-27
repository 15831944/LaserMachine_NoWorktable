#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MachineListContainer.h"
#include "LaserMachineView.h"


// CObjectProperty 窗体视图

class CObjectProperty : public CFormView
{
	DECLARE_DYNCREATE(CObjectProperty)

protected:
	CObjectProperty();           // 动态创建所使用的受保护的构造函数
	virtual ~CObjectProperty();
	virtual void OnInitialUpdate();

public:
	enum { IDD = IDD_OBJECT_PROPERTY };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

// 特性
private:
	BOOL m_Init_Flag;
	int m_ObjSel_Old;
	BOOL m_AllSelObjInLayer;
public:
	CLaserMachineDoc* m_pDoc;
	CLaserMachineView* m_pView;
	CMachineListContainer* m_pObjList;
	CListCtrl m_PropertyList;
	float m_Speed;
	float m_Power;
	float m_Frequncy;
	BYTE m_Count;
	float m_PulseWidth;
	float m_WaitTime;
	float m_Rise_Lenth_Step;
	float m_LaserOnDelay;
	float m_LaserOffDelay;
	float m_BeforMarkDelay;
	float m_AfterMarkDelay;
	float m_PolylineDelay;
	int m_ModeSel;

// 实现
private:
	void HScroll(int Index);
	void UIDeselectAll();
	BOOL UISetBySingleSel(int SelIndex);
	void UISetByMultipleSel(int SelIndex);

protected:
	afx_msg LRESULT OnObjlistRefresh(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeydownObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnObjUp();
	afx_msg void OnBnClickedBtnObjDown();
	afx_msg void OnBnClickedBtnObjDelete();
	afx_msg void OnBnClickedBtnObjInsert();
	afx_msg void OnBnClickedBtnObjPolymeric();
	afx_msg void OnBnClickedBtnObjExplode();
	afx_msg void OnBnClickedBtnObjExchange();
	afx_msg void OnBnClickedBtnObjEdit();
	afx_msg void OnBnClickedObjectPropertyBtn1();
	afx_msg void OnBnClickedObjectPropertyBtn2();
	afx_msg void OnBnClickedObjectPropertyBtn3();	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	BOOL m_bLocate;
	CString m_strBtnMark;
	afx_msg void OnBnClickedButtonObjectStartMark();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


