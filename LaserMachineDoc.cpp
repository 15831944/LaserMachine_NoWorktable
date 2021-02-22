
// LaserMachineDoc.cpp : CLaserMachineDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "LaserMachine.h"
#endif

#include "LaserMachineDoc.h"
#include "LaserMachineView.h"
#include "ObjectProperty.h"
#include "MainFrm.h"

#include <propkey.h>
#include <locale.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLaserMachineDoc
IMPLEMENT_DYNCREATE(CLaserMachineDoc, CDocument)

BEGIN_MESSAGE_MAP(CLaserMachineDoc, CDocument)
	ON_COMMAND(ID_FILE_IMPORT1, &CLaserMachineDoc::OnFileImport)
	ON_COMMAND(ID_FILE_SAVE, &CLaserMachineDoc::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CLaserMachineDoc::OnFileOpen)
	ON_COMMAND(ID_IMPORT_DXF, &CLaserMachineDoc::OnImportDxf)
END_MESSAGE_MAP()


// CLaserMachineDoc 构造/析构

CLaserMachineDoc::CLaserMachineDoc()
{
	// TODO:  在此添加一次性构造代码
	m_pLaserObjList = new CMachineListContainer;
	m_pLaserObjList->m_MachineModeDefault = gProcessMode;
	m_pLaserObjList->m_MachineWaitTimeDefault = gProcessWaitTime;
	m_pLaserObjList->m_MachineParaDefault.Speed = gProcessSpeed;
	m_pLaserObjList->m_MachineParaDefault.Frequncy = gProcessFrequncy;
	m_pLaserObjList->m_MachineParaDefault.Power = gProcessPower;
	m_pLaserObjList->m_MachineParaDefault.Times = gProcessTimes;
	m_pLaserObjList->m_MachineParaDefault.PulseWidth = gProcessPulseWidth;
}

CLaserMachineDoc::~CLaserMachineDoc()
{
	delete m_pLaserObjList;

}


// 虚函数重写

// CLaserMachineDoc 序列化
void CLaserMachineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		CString str;
		ar << filesheadflag;
		str.Format(_T("%s"), fileshead1);
		ar << str;
		str.Format(_T("%s"), fileshead2);
		ar << str;
		str.Format(_T("%s"), fileshead3);
		ar << str;
		str.Format(_T("%s"), fileshead4);
		ar << str;
		//***设备基本参数在此 待补
		//
		m_pLaserObjList->Serialize(ar);

		ar << filesendflag;

	}
	else
	{
		int nTemp;
		LONG64 lTemp;
		CString str, str1;

		m_pLaserObjList->ClearAll();

		ar >> nTemp;
		if (nTemp != filesheadflag)
			return;
		ar >> str;
		str1.Format(_T("%s"), fileshead1);
		if (str != str1)
			return;
		ar >> str;
		str1.Format(_T("%s"), fileshead2);
		if (str != str1)
			return;
		ar >> str;
		str1.Format(_T("%s"), fileshead3);
		if (str != str1)
			return;
		ar >> str;
		str1.Format(_T("%s"), fileshead4);
		if (str != str1)
			return;
		//***设备基本参数在此 待补
		//
		m_pLaserObjList->Serialize(ar);
		ar >> lTemp;

		if (lTemp == filesendflag)
		{
			return;					
		}
		else
		{
			m_pLaserObjList->ClearAllObj();	//否则清除物件表中所有对象
			return;
		}
	}
}

BOOL CLaserMachineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (m_pLaserObjList->IsEmptyObj())
		return TRUE;
	if (IDNO == AfxMessageBox(_T("清除现有工作工作区！"), MB_YESNO))
		return TRUE;
	m_pLaserObjList->ClearAllObj();
	//通知显示窗口刷新
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->SendMessage(WM_Init_ReSize, NULL, NULL);
	//通知属性窗口刷新
	CObjectProperty* pObjProperty = (CObjectProperty*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
	pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);
	AfxGetMainWnd()->SetWindowText(_T("无标题"));
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->Invalidate();
	return TRUE;
}

BOOL CLaserMachineDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CString str;
	if (m_pLaserObjList->IsEmptyObj())
	{
		return FALSE;
	}
	if (PathFileExists(lpszPathName))
	{
		if (AfxMessageBox(_T("覆盖原文件?"), MB_YESNO) == IDNO)
			return FALSE;
	}
	str = lpszPathName;
	str = str.Right(str.GetLength() - str.ReverseFind(_T('\\')) - 1);
	AfxGetMainWnd()->SetWindowText(str);
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->Invalidate();
	return CDocument::OnSaveDocument(lpszPathName);
}

BOOL CLaserMachineDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	m_strPathName = lpszPathName;
	m_bModified = 1;
	//通知显示窗口刷新
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
	//通知属性窗口刷新
	CObjectProperty* pObjProperty = (CObjectProperty*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
	pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);
	CString str = lpszPathName;
	str = str.Right(str.GetLength() - str.ReverseFind(_T('\\')) - 1);
	AfxGetMainWnd()->SetWindowText(str);
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->Invalidate();
	return TRUE;
}


#ifdef SHARED_HANDLERS

// 缩略图的支持
void CLaserMachineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CLaserMachineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CLaserMachineDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLaserMachineDoc 诊断
#ifdef _DEBUG
void CLaserMachineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLaserMachineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLaserMachineDoc 命令
void CLaserMachineDoc::OnImportDxf()
{
	CString str;
	str = _T("CAD图形文件DXF (*.dxf)|*.dxf|");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str, NULL);
	CString lpszFileName;
	if (fileDlg.DoModal() != IDOK)
		return;
	if (!m_pLaserObjList->IsEmptyObj())
	{
		str = fileDlg.GetFileName();
		str = _T("是否删除加工文件\n并导入新文件") + str;
		if (AfxMessageBox(str, MB_YESNO) == IDNO)
			return;
	}
	//清除链表物件
	m_pLaserObjList->ClearAllObj();
	//载入默认加工参数
	m_pLaserObjList->m_MachineModeDefault = gProcessMode;
	m_pLaserObjList->m_MachineParaDefault.Frequncy = gProcessFrequncy;
	m_pLaserObjList->m_MachineParaDefault.Power = gProcessPower;
	m_pLaserObjList->m_MachineParaDefault.PulseWidth = gProcessPulseWidth;
	m_pLaserObjList->m_MachineParaDefault.Speed = gProcessSpeed;
	m_pLaserObjList->m_MachineParaDefault.Times = gProcessTimes;
	m_pLaserObjList->m_MachineWaitTimeDefault = gProcessWaitTime;
	AfxGetApp()->BeginWaitCursor();
	str = fileDlg.GetFileExt();
	if (str == _T("dxf"))
	{
		str = fileDlg.GetPathName();
		if (m_pLaserObjList->Parsedxf(str))
		{
			m_pLaserObjList->LayerRename();
			m_bModified = TRUE;
			str = fileDlg.GetPathName();
			str = str.Left(str.ReverseFind(_T('.')));
			m_strPathName = str + _T(".wls");
			//通知显示窗口刷新
			CLaserMachineView* pView = (CLaserMachineView*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
			pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
			//通知属性窗口刷新
			CObjectProperty* pObjProperty = (CObjectProperty*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
			pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);

			AfxGetMainWnd()->SetWindowText(fileDlg.GetFileName());
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
		else
		{
			AfxMessageBox(_T("文件不包含有效的加工对象!"));
			m_pLaserObjList->ClearAllObj();
			m_bModified = TRUE;
			m_strPathName = _T("");

			AfxGetMainWnd()->SetWindowText(_T("无标题"));
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
	}
}

void CLaserMachineDoc::OnFileOpen()
{
	CString strFileName, str;
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT,
		_T("加工文件WLS (*.wls)|*.wls|"), NULL);
	if (fileDlg.DoModal() == IDCANCEL)
		return;
	strFileName = fileDlg.GetPathName();
	if (fileDlg.GetFileExt() != _T("wls"))
		return;
	if (strFileName == m_strPathName)
	{
		if (!m_pLaserObjList->IsEmptyObj())
		{
			str.Format(_T("重新载入加工文件%s?"), fileDlg.GetFileName());
			if (AfxMessageBox(str, MB_YESNO) != IDYES)
				return;
		}
	}
	else
	{
		if (!m_pLaserObjList->IsEmptyObj())
		{
			str.Format(_T("载入新加工文件%s?"), fileDlg.GetFileName());
			if (AfxMessageBox(str, MB_YESNO) != IDYES)
				return;
		}
	}
	m_pLaserObjList->ClearAll();
	if (!CDocument::OnOpenDocument(strFileName))
		return;
	m_strPathName = strFileName;
	m_bModified = 1;
	//通知显示窗口刷新
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
	//通知属性窗口刷新
	CObjectProperty* pObjProperty = (CObjectProperty*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
	pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);

	AfxGetMainWnd()->SetWindowText(fileDlg.GetFileName());
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->Invalidate();
}

void CLaserMachineDoc::OnFileImport()
{
	CString str;
	str = _T("CAD图形文件DXF (*.dxf)|*.dxf|");
	//str = str + _T("图像文件BMP (*.bmp)|*.bmp|");
	//str = str + _T("光绘文件PLT (*.plt)|*.plt|");
	//str =str+ _T("Gerber文件 (*.gbr)|*.gbr|");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str, NULL);
	CString lpszFileName;

	if (fileDlg.DoModal() != IDOK)
		return;
	if (!m_pLaserObjList->IsEmptyObj())
	{
		str = fileDlg.GetFileName();
		str = _T("是否删除加工文件\n并导入新文件") + str;
		if (AfxMessageBox(str, MB_YESNO) == IDNO)
			return;
	}
	//清除链表物件
	m_pLaserObjList->ClearAllObj();
	//载入默认加工参数
	m_pLaserObjList->m_MachineModeDefault = gProcessMode;
	m_pLaserObjList->m_MachineParaDefault.Frequncy = gProcessFrequncy;
	m_pLaserObjList->m_MachineParaDefault.Power = gProcessPower;
	m_pLaserObjList->m_MachineParaDefault.PulseWidth = gProcessPulseWidth;
	m_pLaserObjList->m_MachineParaDefault.Speed = gProcessSpeed;
	m_pLaserObjList->m_MachineParaDefault.Times = gProcessTimes;
	m_pLaserObjList->m_MachineWaitTimeDefault = gProcessWaitTime;
	AfxGetApp()->BeginWaitCursor();
	str = fileDlg.GetFileExt();
	if (str == _T("dxf"))
	{
		str = fileDlg.GetPathName();
		if (m_pLaserObjList->Parsedxf(str))
		{
			m_pLaserObjList->LayerRename();
			m_bModified = TRUE;
			str = fileDlg.GetPathName();
			str = str.Left(str.ReverseFind(_T('.')));
			m_strPathName = str+_T(".wls");
			//通知显示窗口刷新
			CLaserMachineView* pView = (CLaserMachineView*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
			pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
			//通知属性窗口刷新
			CObjectProperty* pObjProperty = (CObjectProperty*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
			pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);

			AfxGetMainWnd()->SetWindowText(fileDlg.GetFileName());
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
		else
		{
			AfxMessageBox(_T("文件不包含有效的加工对象!"));
			m_pLaserObjList->ClearAllObj();
			m_bModified = TRUE;
			m_strPathName = _T("");
			
			AfxGetMainWnd()->SetWindowText(_T("无标题"));
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
	}
	else if (str == _T("bmp"))
	{
		//待补充

	}
	else if (str == _T("plt"))
	{
		//待补充

	}
	else if (str == _T("gbr"))
	{
		//待补充

	}
	return;
}

BOOL CLaserMachineDoc::Check_Process_Para1(ProcessPara para, int mode)
{
	if (para.Frequncy > Process_MaxFrequncy || para.Frequncy < Process_MinFrequncy
		|| para.Power>Process_MaxPower || para.Power < Process_MinPower
		|| para.PulseWidth>Process_MaxPulseWidth || para.PulseWidth < Process_MinPulseWidth
		|| para.Speed>Process_MaxSpeed || para.Speed < Process_MinSpeed
		|| para.Times>Process_MaxTime || para.Times < Process_MinTime
		|| mode>Process_MaxMode || mode<Process_MinMode)
		return FALSE;
	return TRUE;
}

BOOL CLaserMachineDoc::Check_Process_Para2(float wait_time)
{
	if (wait_time<Process_MinDotTime || wait_time>Process_MaxDotTime)
		return FALSE;
	return TRUE;
}









