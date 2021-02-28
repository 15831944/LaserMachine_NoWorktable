// MainFrm.h : CMainFrame 类的接口
//

#pragma once


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

protected:
	// 分割窗口嵌入成员
	bool m_bSplitter_Flag;
	bool m_bObPrtyWindows_Hide;
	bool m_bCamPosWindows_Hide;
	// 控件条嵌入成员
	CToolBar m_wndToolBar;
	CToolBar m_wndToolBar1;
	bool m_bToolBar_Flag;

public:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter1;
	CStatusBar m_wndStatusBar;
	



// 操作
public:
	CString m_strSysPassword;

// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif




// 生成的消息映射函数
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


