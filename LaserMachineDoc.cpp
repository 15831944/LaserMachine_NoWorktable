
// LaserMachineDoc.cpp : CLaserMachineDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CLaserMachineDoc ����/����

CLaserMachineDoc::CLaserMachineDoc()
{
	// TODO:  �ڴ����һ���Թ������
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


// �麯����д

// CLaserMachineDoc ���л�
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
		//***�豸���������ڴ� ����
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
		//***�豸���������ڴ� ����
		//
		m_pLaserObjList->Serialize(ar);
		ar >> lTemp;

		if (lTemp == filesendflag)
		{
			return;					
		}
		else
		{
			m_pLaserObjList->ClearAllObj();	//�����������������ж���
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
	if (IDNO == AfxMessageBox(_T("������й�����������"), MB_YESNO))
		return TRUE;
	m_pLaserObjList->ClearAllObj();
	//֪ͨ��ʾ����ˢ��
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->SendMessage(WM_Init_ReSize, NULL, NULL);
	//֪ͨ���Դ���ˢ��
	CObjectProperty* pObjProperty = (CObjectProperty*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
	pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);
	AfxGetMainWnd()->SetWindowText(_T("�ޱ���"));
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
		if (AfxMessageBox(_T("����ԭ�ļ�?"), MB_YESNO) == IDNO)
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
	//֪ͨ��ʾ����ˢ��
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
	//֪ͨ���Դ���ˢ��
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

// ����ͼ��֧��
void CLaserMachineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CLaserMachineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CLaserMachineDoc ���
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


// CLaserMachineDoc ����
void CLaserMachineDoc::OnImportDxf()
{
	CString str;
	str = _T("CADͼ���ļ�DXF (*.dxf)|*.dxf|");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str, NULL);
	CString lpszFileName;
	if (fileDlg.DoModal() != IDOK)
		return;
	if (!m_pLaserObjList->IsEmptyObj())
	{
		str = fileDlg.GetFileName();
		str = _T("�Ƿ�ɾ���ӹ��ļ�\n���������ļ�") + str;
		if (AfxMessageBox(str, MB_YESNO) == IDNO)
			return;
	}
	//����������
	m_pLaserObjList->ClearAllObj();
	//����Ĭ�ϼӹ�����
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
			//֪ͨ��ʾ����ˢ��
			CLaserMachineView* pView = (CLaserMachineView*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
			pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
			//֪ͨ���Դ���ˢ��
			CObjectProperty* pObjProperty = (CObjectProperty*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
			pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);

			AfxGetMainWnd()->SetWindowText(fileDlg.GetFileName());
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
		else
		{
			AfxMessageBox(_T("�ļ���������Ч�ļӹ�����!"));
			m_pLaserObjList->ClearAllObj();
			m_bModified = TRUE;
			m_strPathName = _T("");

			AfxGetMainWnd()->SetWindowText(_T("�ޱ���"));
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
	}
}

void CLaserMachineDoc::OnFileOpen()
{
	CString strFileName, str;
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT,
		_T("�ӹ��ļ�WLS (*.wls)|*.wls|"), NULL);
	if (fileDlg.DoModal() == IDCANCEL)
		return;
	strFileName = fileDlg.GetPathName();
	if (fileDlg.GetFileExt() != _T("wls"))
		return;
	if (strFileName == m_strPathName)
	{
		if (!m_pLaserObjList->IsEmptyObj())
		{
			str.Format(_T("��������ӹ��ļ�%s?"), fileDlg.GetFileName());
			if (AfxMessageBox(str, MB_YESNO) != IDYES)
				return;
		}
	}
	else
	{
		if (!m_pLaserObjList->IsEmptyObj())
		{
			str.Format(_T("�����¼ӹ��ļ�%s?"), fileDlg.GetFileName());
			if (AfxMessageBox(str, MB_YESNO) != IDYES)
				return;
		}
	}
	m_pLaserObjList->ClearAll();
	if (!CDocument::OnOpenDocument(strFileName))
		return;
	m_strPathName = strFileName;
	m_bModified = 1;
	//֪ͨ��ʾ����ˢ��
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
	//֪ͨ���Դ���ˢ��
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
	str = _T("CADͼ���ļ�DXF (*.dxf)|*.dxf|");
	//str = str + _T("ͼ���ļ�BMP (*.bmp)|*.bmp|");
	//str = str + _T("����ļ�PLT (*.plt)|*.plt|");
	//str =str+ _T("Gerber�ļ� (*.gbr)|*.gbr|");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, str, NULL);
	CString lpszFileName;

	if (fileDlg.DoModal() != IDOK)
		return;
	if (!m_pLaserObjList->IsEmptyObj())
	{
		str = fileDlg.GetFileName();
		str = _T("�Ƿ�ɾ���ӹ��ļ�\n���������ļ�") + str;
		if (AfxMessageBox(str, MB_YESNO) == IDNO)
			return;
	}
	//����������
	m_pLaserObjList->ClearAllObj();
	//����Ĭ�ϼӹ�����
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
			//֪ͨ��ʾ����ˢ��
			CLaserMachineView* pView = (CLaserMachineView*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
			pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
			//֪ͨ���Դ���ˢ��
			CObjectProperty* pObjProperty = (CObjectProperty*)
				((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter.GetPane(0, 2);
			pObjProperty->SendMessage(WM_ObjList_Refresh, NULL, NULL);

			AfxGetMainWnd()->SetWindowText(fileDlg.GetFileName());
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
		else
		{
			AfxMessageBox(_T("�ļ���������Ч�ļӹ�����!"));
			m_pLaserObjList->ClearAllObj();
			m_bModified = TRUE;
			m_strPathName = _T("");
			
			AfxGetMainWnd()->SetWindowText(_T("�ޱ���"));
			CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
			pFrame->Invalidate();
		}
	}
	else if (str == _T("bmp"))
	{
		//������

	}
	else if (str == _T("plt"))
	{
		//������

	}
	else if (str == _T("gbr"))
	{
		//������

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









