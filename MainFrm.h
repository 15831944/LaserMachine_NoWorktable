// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once


class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

protected:
	// �ָ��Ƕ���Ա
	bool m_bSplitter_Flag;
	bool m_bObPrtyWindows_Hide;
	bool m_bCamPosWindows_Hide;
	// �ؼ���Ƕ���Ա
	CToolBar m_wndToolBar;
	CToolBar m_wndToolBar1;
	bool m_bToolBar_Flag;

public:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter1;
	CStatusBar m_wndStatusBar;
	



// ����
public:
	CString m_strSysPassword;

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif




// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnMainwindowsResume(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCtrlwindowsSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnObprtywindowsSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCamPoswindowsSize(WPARAM wParam, LPARAM lParam);

public:
	afx_msg void OnObjPrtyPanelDisp();
	afx_msg void OnCamPosPanelDisp();
	afx_msg void OnDrawToVideo();
	
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDeviceConfig();	
	afx_msg void OnClose();
protected:
	afx_msg LRESULT OnGetCameraHwnd(WPARAM wParam, LPARAM lParam);
};


