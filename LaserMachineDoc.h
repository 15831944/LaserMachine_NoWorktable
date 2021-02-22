
// LaserMachineDoc.h : CLaserMachineDoc ��Ľӿ�
//


#pragma once
#include "MachineListContainer.h"

class CLaserMachineDoc : public CDocument
{
protected: // �������л�����
	CLaserMachineDoc();
	DECLARE_DYNCREATE(CLaserMachineDoc)

// ����
public:
	CMachineListContainer* m_pLaserObjList;



// ����
public:
	afx_msg void OnFileOpen();
	BOOL Check_Process_Para1(ProcessPara para, int mode);
	BOOL Check_Process_Para2(float wait_time);


// ��д
public:
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnNewDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CLaserMachineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	afx_msg void OnFileImport();
	

	

	
	afx_msg void OnImportDxf();
};
