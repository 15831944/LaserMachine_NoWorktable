
// LaserMachineView.h : CLaserMachineView 类的接口
//

#pragma once
#include "LaserMachineDoc.h"

#include "MachineListContainer.h"



class CLaserMachineView : public CView
{
protected: // 仅从序列化创建
	CLaserMachineView();
	DECLARE_DYNCREATE(CLaserMachineView)

// 特性
public:
	CLaserMachineDoc* GetDocument() const;
	CMachineListContainer* m_pLaserObjList;
	CPoint m_ptWindowOrg;		//显示设备坐标原点
	CPoint m_ptViewPortOrg;		//显示窗口坐标原点
	CRect  m_rcBound;			//图形外框
	CRect  m_rcZoomBound;		//缩放后的图形外框
	BYTE m_DrawType;			//绘图操作类型
	BOOL m_LButtonDown;			//鼠标左键已压下
	BOOL m_MouseMoved;			//压下鼠标左键后,鼠标移动中
	CPoint m_LButtonFirst;		//鼠标压下时设备坐标
	CPoint m_ptLButtonTemp;		//鼠标压下时,光标处瞬时坐标	
	CRect  m_rcClient;			//绘图窗口尺寸
	double m_fZoomFactor;		//缩放因子
	int m_nHScrollPos;
	int m_nVScrollPos;
	int m_nHScrollMax;			
	int m_nVScrollMax;
	bool m_bObjDirDisp;
	bool m_bObjDirDisp_EN;
	bool m_bObjNodeDisp;
	ObjPoint m_NodePoint;
	vector<int> m_nList;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
//protected:
//	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
private:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

// 实现
public:
	virtual ~CLaserMachineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 消息映射函数
private:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnZoomUp();
	afx_msg void OnZoomDown();
	afx_msg void OnZoomAll();
	afx_msg void OnZoomRect();
	afx_msg void OnUpdateZoomRect(CCmdUI *pCmdUI);
	afx_msg void OnDrawSelect();
	afx_msg void OnUpdateDrawSelect(CCmdUI *pCmdUI);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	
protected:
	afx_msg LRESULT OnObjBoundResize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInitResize(WPARAM wParam, LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()

//自定义函数
private:
	void DrawCoord(CDC* pDC);
	void DrawGrid(CDC* pDC, CMachineListContainer* m_pObjList);

public:
	void ResetViewSize();
	void UpdateHVscroll();
	void InitHScroll();
	void InitVScroll();
	void ZoomUpInPoint(CPoint ptZoom);
	void ZoomDownInPoint(CPoint ptZoom);
	void ZoomInRect(CRect rcZoom);
	void UpdateZoomBoundRect();
	CPoint TransDPtoLP(CPoint ptDevice);	//设备坐标转换成逻辑坐标
	CRect  TransDPtoLP(CRect rcDevice);
	CPoint TransLPtoDP(CPoint ptLogic);	//逻辑坐标转换成设备坐标
	CRect  TransLPtoDP(CRect rcLogic);
	CPoint TransRPtoLP(ObjPoint ptReal);	//物理坐标转换成逻辑坐标
	CRect  TransRBdtoLBd(ObjRect ObjBound);
	ObjPoint TransLPtoRP(CPoint ptLogic);	//逻辑坐标转换成物理坐标
	ObjRect  TransLPtoRP(CRect rcLogic);

public:
	
//	CPoint TransDPtoRP(CPoint ptInput);	//设备坐标转换成真实坐标
//	CRect  TransDPtoRP(CRect  rcInput);
//	CPoint TransRPtoDP(CPoint ptInput);	//真实坐标转换成设备坐标
//	CRect  TransRPtoDP(CRect rcInput);

//变量
public:
	
	//CPoint m_ptRealOrg;			//真实坐标原点
	//CPoint m_ptViewRealOrg;		//真实视窗原点
	//CRect  marksBound;			//Marks外框
	
	
	        

	//CPoint m_ptTopLeft;
	//CPoint m_ptBotomRight;
	

	//CRect m_rcZoomInput;

public:
	
	//CLaserMachineObjList* m_pListDrawGrid;		//分格对象显示链表
	//CLaserMachineObjList* m_pListGridBound;
	//CLaserMachineObjList* m_pListSelect;		//选择对象链表
	//CLaserMachineObjList* m_pListInClient;
	//BOOL              m_bFlagInvalidate;
	//int               m_nTypeCurrentShow;

//	CLaserMachineObjList  m_pListObjBak;		//实体对象链表备份
//	CLaserMachineObjList  m_listProperty;		//加工参数暂存链表

//	CLaserMachineObjList  m_listArrayTemp;

//	CRITICAL_SECTION	m_csListLock;
//	CRITICAL_SECTION	m_csListGridLock;


public:
	afx_msg void OnSetparaGrid();
protected:
	afx_msg LRESULT OnStartMark(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopMark(WPARAM wParam, LPARAM lParam);
	//加工进程控制**************************加工进程控制
public:
	BOOL m_bLocate;
	BOOL m_bMarkThreadIsRunning;
	void StartMarkThread();
	void StopMarkThread(CWinThread* pThred);
	void WaitForMarkThreadEnded();
	//ThreadFunc
	static UINT MarkProcRun(LPVOID lpParam);
	//shared data
	//CMachineListContainer* m_pListContainer;
	// event handles to synchronize threads
	HANDLE  MarkProcStopEvent;
	// mutexes to guarantee mutual access to shared objects
	CRITICAL_SECTION    ProcObjListMutex;
private:
	CWinThread* m_pThMarkProc;				//线程指针
	//DWORD m_dwThMarkProc;					//线程ID
	long m_lTimeStartMarkProcess;
	HWND m_pHwndHalconWnd;
	//加工进程控制**************************加工进程控制

public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonAxisZMove();
};

#ifndef _DEBUG  // LaserMachineView.cpp 中的调试版本
inline CLaserMachineDoc* CLaserMachineView::GetDocument() const
   { return reinterpret_cast<CLaserMachineDoc*>(m_pDocument); }
#endif

