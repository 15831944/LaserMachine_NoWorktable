
// LaserMachine.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "LaserMachine.h"
#include "MainFrm.h"

#include "LaserMachineDoc.h"
#include "LaserMachineView.h"
#include "DeviceCardMarkBSL.h"
#include "DeviceCardWorktableMPC2810.h"
#include "CameraPosition.h"
#include "DeviceLaserBellin.h"
#include "CDlgDevCfgTabLaser.h"


//�豸��ȫ��ָ��
CDeviceCardMark* pDevCardMark = NULL;
CDeviceCardWorktable* pDevCardWorktable = NULL;
CDeviceLaser* pDevLaser = NULL;


// CLaserMachineApp

BEGIN_MESSAGE_MAP(CLaserMachineApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CLaserMachineApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CLaserMachineApp ����

CLaserMachineApp::CLaserMachineApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("LaserMachine.AppID.NoVersion"));

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CLaserMachineApp ����

CLaserMachineApp theApp;


// CLaserMachineApp ��ʼ��

BOOL CLaserMachineApp::InitInstance()
{
	//****������ֻ��������һ��ʵ������Ҫ�޸�Ĭ�ϵ��ļ���****
	//****2019.5 By Cao****
	HANDLE hEvt = CreateEventW(NULL, FALSE, FALSE, _T("LaserMachineK"));
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		AfxMessageBox(_T("�ӹ������Ѿ����У�"));
		return FALSE;
	}
	

	////���Ի�������//////////////////////////////////////////
	//#define BUFSIZE 4096
	//#define VARNAME _TEXT("Path")
	//LPTSTR pszOldVal;
	//pszOldVal = (LPTSTR)malloc(BUFSIZE * sizeof(TCHAR));

	//TCHAR pEnvPaths[BUFSIZE];
	//TCHAR pAppPath[MAX_PATH];
	//CString strEnvPaths, strAppPath;

	//GetEnvironmentVariable(VARNAME, pEnvPaths, BUFSIZE);
	//strEnvPaths = pEnvPaths;

	//// ����ǰ·��\dll·����ӵ������̵�·����
	//if (!::GetModuleFileName(NULL, pAppPath, MAX_PATH))
	//	return FALSE;
	//PathRemoveFileSpec(pAppPath);
	//strAppPath = pAppPath;

	//strEnvPaths.TrimRight(_T(";"));
	//strEnvPaths += _T(";") + strAppPath + _T("\\MyDllPathTest;");
	//SetEnvironmentVariable(VARNAME, strEnvPaths);
	////���Ի�������/////////////////////////////////////////////


	//�豸��ȫ��ָ�룬�ڽ�������֮ǰ��ʼ��Ӳ��
	//��꿨
	pDevCardMark = new CDeviceCardMarkBSL;
	if (FALSE == pDevCardMark->InitialCardMark())
	{
		delete pDevCardMark;
		pDevCardMark = NULL;
		AfxMessageBox(_T("��꿨��ʼ��ʧ��"));
	}
	//�˶����ƿ�
	switch (ReadDevWorktableName())
	{
	case WORKTABLE_NAME::WORKTABLE_NONE:
		pDevCardWorktable = NULL;
		break;
	case WORKTABLE_NAME::WORKTABLE_MPC2810:
		pDevCardWorktable = new CDeviceCardWorktableMPC2810;
		break;
	default:
		pDevCardWorktable = NULL;
		break;
	}
	if (NULL == pDevCardWorktable)
	{
		//AfxMessageBox(_T("��ѡ���˶����ƿ�"));
	}
	else
	{
		//if (FALSE == pDevCardWorktable->InitialCardWorktable())
		pDevCardWorktable->InitialCardWorktable();
		{
			delete pDevCardWorktable;
			pDevCardWorktable = NULL;
			//AfxMessageBox(_T("�˶����ƿ���ʼ��ʧ��"));
		}
	}
	//������Ӳ��
	switch (ReadDevLaserTypeIndex())
	{
	case 1:
		pDevLaser = new CDeviceLaserBellin;
		break;
	default:
		pDevLaser = NULL;
		break;
	}

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("LaserMachine_Para"));
	LoadStdProfileSettings(8);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	
	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLaserMachineDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CLaserMachineView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();


	return TRUE;
}

int CLaserMachineApp::ExitInstance()
{
	//TODO:  �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	//�豸��ȫ��ָ��
	if (pDevCardMark)
	{
		delete pDevCardMark;
		pDevCardMark = NULL;
	}
	if (pDevCardWorktable)
	{
		delete pDevCardWorktable;
		pDevCardWorktable = NULL;
	}
	if (pDevLaser)
	{
		delete pDevLaser;
		pDevLaser = NULL;
	}

	//ȫ�ֱ����ͷ��ڴ�
	//g_vPtPosDestinedMark.clear();
	//g_vPtPosRealMark.clear();
	//g_vMarkPointModel.clear();
	std::vector <CPointF>().swap(g_vPtPosDestinedMark);
	std::vector <CPointF>().swap(g_vPtPosRealMark);
	std::vector <HalconModel>().swap(g_vMarkPointModel);


	//AfxMessageBox(_T("ExitInstance���"));
	//ǿ�н����Լ�
	//HANDLE hself = GetCurrentProcess();
	//TerminateProcess(hself, 0);
	//_CrtDumpMemoryLeaks();
	

	return CWinApp::ExitInstance();
}

// CLaserMachineApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
protected:
//	afx_msg LRESULT OnStartMark(WPARAM wParam, LPARAM lParam);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
//	ON_REGISTERED_MESSAGE(WM_START_MARK, &CAboutDlg::OnStartMark)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CLaserMachineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CLaserMachineApp ��Ϣ�������


void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}




//afx_msg LRESULT CAboutDlg::OnStartMark(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}
