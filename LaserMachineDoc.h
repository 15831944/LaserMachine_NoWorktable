
// LaserMachineDoc.h : CLaserMachineDoc 类的接口
//


#pragma once
#include "MachineListContainer.h"

class CLaserMachineDoc : public CDocument
{
protected: // 仅从序列化创建
	CLaserMachineDoc();
	DECLARE_DYNCREATE(CLaserMachineDoc)

// 特性
public:
	CMachineListContainer* m_pLaserObjList;



// 操作
public:
	afx_msg void OnFileOpen();
	BOOL Check_Process_Para1(ProcessPara para, int mode);
	BOOL Check_Process_Para2(float wait_time);


// 重写
public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CLaserMachineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	afx_msg void OnFileImport();
	

	

	
	afx_msg void OnImportDxf();
};
