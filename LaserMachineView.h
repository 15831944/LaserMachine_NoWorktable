
// LaserMachineView.h : CLaserMachineView ��Ľӿ�
//

#pragma once
#include "LaserMachineDoc.h"

#include "MachineListContainer.h"



class CLaserMachineView : public CView
{
protected: // �������л�����
	CLaserMachineView();
	DECLARE_DYNCREATE(CLaserMachineView)

// ����
public:
	CLaserMachineDoc* GetDocument() const;
	CMachineListContainer* m_pLaserObjList;
	CPoint m_ptWindowOrg;		//��ʾ�豸����ԭ��
	CPoint m_ptViewPortOrg;		//��ʾ��������ԭ��
	CRect  m_rcBound;			//ͼ�����
	CRect  m_rcZoomBound;		//���ź��ͼ�����
	BYTE m_DrawType;			//��ͼ��������
	BOOL m_LButtonDown;			//��������ѹ��
	BOOL m_MouseMoved;			//ѹ����������,����ƶ���
	CPoint m_LButtonFirst;		//���ѹ��ʱ�豸����
	CPoint m_ptLButtonTemp;		//���ѹ��ʱ,��괦˲ʱ����	
	CRect  m_rcClient;			//��ͼ���ڳߴ�
	double m_fZoomFactor;		//��������
	int m_nHScrollPos;
	int m_nVScrollPos;
	int m_nHScrollMax;			
	int m_nVScrollMax;
	bool m_bObjDirDisp;
	bool m_bObjDirDisp_EN;
	bool m_bObjNodeDisp;
	ObjPoint m_NodePoint;
	vector<int> m_nList;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
//protected:
//	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
private:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

// ʵ��
public:
	virtual ~CLaserMachineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// ��Ϣӳ�亯��
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

//�Զ��庯��
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
	CPoint TransDPtoLP(CPoint ptDevice);	//�豸����ת�����߼�����
	CRect  TransDPtoLP(CRect rcDevice);
	CPoint TransLPtoDP(CPoint ptLogic);	//�߼�����ת�����豸����
	CRect  TransLPtoDP(CRect rcLogic);
	CPoint TransRPtoLP(ObjPoint ptReal);	//��������ת�����߼�����
	CRect  TransRBdtoLBd(ObjRect ObjBound);
	ObjPoint TransLPtoRP(CPoint ptLogic);	//�߼�����ת������������
	ObjRect  TransLPtoRP(CRect rcLogic);

public:
	
//	CPoint TransDPtoRP(CPoint ptInput);	//�豸����ת������ʵ����
//	CRect  TransDPtoRP(CRect  rcInput);
//	CPoint TransRPtoDP(CPoint ptInput);	//��ʵ����ת�����豸����
//	CRect  TransRPtoDP(CRect rcInput);

//����
public:
	
	//CPoint m_ptRealOrg;			//��ʵ����ԭ��
	//CPoint m_ptViewRealOrg;		//��ʵ�Ӵ�ԭ��
	//CRect  marksBound;			//Marks���
	
	
	        

	//CPoint m_ptTopLeft;
	//CPoint m_ptBotomRight;
	

	//CRect m_rcZoomInput;

public:
	
	//CLaserMachineObjList* m_pListDrawGrid;		//�ָ������ʾ����
	//CLaserMachineObjList* m_pListGridBound;
	//CLaserMachineObjList* m_pListSelect;		//ѡ���������
	//CLaserMachineObjList* m_pListInClient;
	//BOOL              m_bFlagInvalidate;
	//int               m_nTypeCurrentShow;

//	CLaserMachineObjList  m_pListObjBak;		//ʵ�����������
//	CLaserMachineObjList  m_listProperty;		//�ӹ������ݴ�����

//	CLaserMachineObjList  m_listArrayTemp;

//	CRITICAL_SECTION	m_csListLock;
//	CRITICAL_SECTION	m_csListGridLock;


public:
	afx_msg void OnSetparaGrid();
protected:
	afx_msg LRESULT OnStartMark(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopMark(WPARAM wParam, LPARAM lParam);
	//�ӹ����̿���**************************�ӹ����̿���
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
	CWinThread* m_pThMarkProc;				//�߳�ָ��
	//DWORD m_dwThMarkProc;					//�߳�ID
	long m_lTimeStartMarkProcess;
	HWND m_pHwndHalconWnd;
	//�ӹ����̿���**************************�ӹ����̿���

public:
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonAxisZMove();
};

#ifndef _DEBUG  // LaserMachineView.cpp �еĵ��԰汾
inline CLaserMachineDoc* CLaserMachineView::GetDocument() const
   { return reinterpret_cast<CLaserMachineDoc*>(m_pDocument); }
#endif

