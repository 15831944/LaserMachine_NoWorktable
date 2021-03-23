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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

// 特性
private:
	BOOL m_Init_Flag;
	int m_ObjSel_Old;
	bool m_bDispObject;
	bool m_bDegenerate;
	//
	int m_LayerSel_Old;
	vector <UINT> m_ProtyListIndex;
	vector <UINT> m_SelectedObj;
	CMachineObj_Comm* m_Edit_pObj;
	double m_dVar1;
	double m_dVar2;
	double m_dVar3;
	double m_dVar4;
	double m_dVar5;
	double m_dVar6;
	double m_dVar7;
	double m_dVar8;
	double m_dVar9;
	double m_dVar10;
	double m_dVar11;
	int m_SelNode;
	int m_OutlinePrior;
	BOOL m_FillEnable;
	int m_nSelGroup;
	int m_FillMode;
	int m_GapMode;
	FillPara m_FillPara[4];
	byte m_nSel_Old;


public:
	CLaserMachineDoc* m_pDoc;
	CLaserMachineView* m_pView;
	CMachineListContainer* m_pObjList;
	CListCtrl m_PropertyList;
	CComboBox m_LayerNameListBox;
	float m_Speed;
	float m_Power;
	float m_Frequncy;
	UINT m_Count;
	float m_PulseWidth;
	float m_WaitTime;
	float m_Rise_Lenth_Step;
	float m_LaserOnDelay;
	float m_LaserOffDelay;
	float m_BeforMarkDelay;
	float m_AfterMarkDelay;
	float m_PolylineDelay;
	int m_ModeSel;
	CString m_LayerName;

// 实现
private:
	void HScroll(int Index);
	void gPara_To_mPara();
	void LayerPara_To_mPara(CMachinePara_Layer* pLayer);
	void UIRefreshLayer();
	void UIRefreshObject(int Index);
	void UIRefreshObject();
	void ClearAllObjSel();
	void ClearActiveLayerSel();
	int FindProtyListIndex(int ObjListIndex);
	void SetExtenfPara();
	void SetFillPara();
	void EditPoint(CMachineObj_Comm* pObj);
	void SavePoint(CMachineObj_Comm* pObj);
	void EditLine(CMachineObj_Comm* pObj);
	void SaveLineModify(CMachineObj_Comm* pObj);
	void ExchangeLineStartAndEnd(CMachineObj_Comm* pObj);
	void EditCircle(CMachineObj_Comm* pObj);
	void SaveCircleModify(CMachineObj_Comm* pObj);
	void ExchangeCircleStartAndEnd(CMachineObj_Comm* pObj);
	void ChangeCircleNode(CMachineObj_Comm* pObj);
	void EditArc(CMachineObj_Comm* pObj);
	void SaveArcModify(CMachineObj_Comm* pObj);
	void ExchangeArcStartAndEnd(CMachineObj_Comm* pObj);
	void EditEllipse(CMachineObj_Comm* pObj);
	void SaveEllipseModify(CMachineObj_Comm* pObj);
	void ExchangeEllipseStartAndEnd(CMachineObj_Comm* pObj);
	void ChangeEllipseNode(CMachineObj_Comm* pObj);
	void EditArcEll(CMachineObj_Comm* pObj);
	void SaveArcEllModify(CMachineObj_Comm* pObj);
	void ExchangeArcEllStartAndEnd(CMachineObj_Comm* pObj);
	void EditTiltEllipse(CMachineObj_Comm* pObj);
	void SaveTiltEllipseModify(CMachineObj_Comm* pObj);
	void ExchangeTiltEllipseStartAndEnd(CMachineObj_Comm* pObj);
	void EditPolyline(CMachineObj_Comm* pObj);
	void SavePolylineModify(CMachineObj_Comm* pObj);
	void ExchangePolylineStartAndEnd(CMachineObj_Comm* pObj);
	void ClosePolyline(CMachineObj_Comm* pObj);
	void LastNodePolyline(CMachineObj_Comm* pObj);
	void NextNodePolyline(CMachineObj_Comm* pObj);
	void EditGroup(CMachineObj_Comm* pObj);
	void SaveGroupModify(CMachineObj_Comm* pObj);
	void EditWiden(CMachineObj_Comm* pObj);
	void SaveWiden();
	void EditFill(CMachineObj_Comm* pObj);
	void SaveFill();

protected:
	afx_msg LRESULT OnObjlistRefresh(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//20210127
	afx_msg void OnClickedObjectOrLayer();
	afx_msg void OnClickedObjProtyBtnSave();
	afx_msg void OnClickObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeydownObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnObjProtyBtnLayerOrObjUp();
	afx_msg void OnObjProtyBtnLayerOrObjDown();
	afx_msg void OnObjProtyBtnLayerOpenAndCloseOrObjDelete();
	afx_msg void OnObjProtyBtnLayerLockAndUnlockOrObjEdit();
	afx_msg void OnObjProtyBtnLayerModifyOrObjGroup();
	afx_msg void OnObjProtyBtnLayerDeleteOrObjExplode();
	afx_msg void OnObjProtyBtnLayerClear();
	afx_msg void OnObjProtyBtnCombine();
	afx_msg void OnObjProtyBtnLayerNew();
	afx_msg void OnClickedObjProtyExtend();
	afx_msg void OnClickedObjProtyFill();
	afx_msg void OnClickedObjProtyBtn15();
	afx_msg void OnClickedObjProtyBtn16();
	afx_msg void OnClickedObjProtyBtn17();
	afx_msg void OnClickedObjProtyBtn18();
	afx_msg void OnClickedObjProtyBtn19();
	afx_msg void OnClickedObjProtyBtn20();
	afx_msg void OnClickedObjProtyCheck1();
	afx_msg void OnClickedObjProtyRadio6();

	BOOL m_bLocate;
	CString m_strBtnMark;
	afx_msg void OnBnClickedButtonObjectStartMark();

};


