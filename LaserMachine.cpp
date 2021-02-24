
// LaserMachine.cpp : 定义应用程序的类行为。
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


//设备类全局指针
CDeviceCardMark* pDevCardMark = NULL;
CDeviceCardWorktable* pDevCardWorktable = NULL;
CDeviceLaser* pDevLaser = NULL;


// CLaserMachineApp

BEGIN_MESSAGE_MAP(CLaserMachineApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CLaserMachineApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CLaserMachineApp 构造

CLaserMachineApp::CLaserMachineApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("LaserMachine.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CLaserMachineApp 对象

CLaserMachineApp theApp;


// CLaserMachineApp 初始化

BOOL CLaserMachineApp::InitInstance()
{
	//****本程序只容许运行一个实例，不要修改默认的文件名****
	//****2019.5 By Cao****
	HANDLE hEvt = CreateEventW(NULL, FALSE, FALSE, _T("LaserMachineK"));
	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		AfxMessageBox(_T("加工程序已经运行！"));
		return FALSE;
	}
	

	////测试环境变量//////////////////////////////////////////
	//#define BUFSIZE 4096
	//#define VARNAME _TEXT("Path")
	//LPTSTR pszOldVal;
	//pszOldVal = (LPTSTR)malloc(BUFSIZE * sizeof(TCHAR));

	//TCHAR pEnvPaths[BUFSIZE];
	//TCHAR pAppPath[MAX_PATH];
	//CString strEnvPaths, strAppPath;

	//GetEnvironmentVariable(VARNAME, pEnvPaths, BUFSIZE);
	//strEnvPaths = pEnvPaths;

	//// 将当前路径\dll路径添加到本进程的路径中
	//if (!::GetModuleFileName(NULL, pAppPath, MAX_PATH))
	//	return FALSE;
	//PathRemoveFileSpec(pAppPath);
	//strAppPath = pAppPath;

	//strEnvPaths.TrimRight(_T(";"));
	//strEnvPaths += _T(";") + strAppPath + _T("\\MyDllPathTest;");
	//SetEnvironmentVariable(VARNAME, strEnvPaths);
	////测试环境变量/////////////////////////////////////////////


	//设备类全局指针，在界面生成之前初始化硬件
	//打标卡
	pDevCardMark = new CDeviceCardMarkBSL;
	if (FALSE == pDevCardMark->InitialCardMark())
	{
		delete pDevCardMark;
		pDevCardMark = NULL;
		AfxMessageBox(_T("打标卡初始化失败"));
	}
	//运动控制卡
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
		//AfxMessageBox(_T("请选择运动控制卡"));
	}
	else
	{
		//if (FALSE == pDevCardWorktable->InitialCardWorktable())
		pDevCardWorktable->InitialCardWorktable();
		{
			delete pDevCardWorktable;
			pDevCardWorktable = NULL;
			//AfxMessageBox(_T("运动控制卡初始化失败"));
		}
	}
	//激光器硬件
	switch (ReadDevLaserTypeIndex())
	{
	case 1:
		pDevLaser = new CDeviceLaserBellin;
		break;
	default:
		pDevLaser = NULL;
		break;
	}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("LaserMachine_Para"));
	LoadStdProfileSettings(8);  // 加载标准 INI 文件选项(包括 MRU)

	
	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLaserMachineDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CLaserMachineView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();


	return TRUE;
}

int CLaserMachineApp::ExitInstance()
{
	//TODO:  处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	//设备类全局指针
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

	//全局变量释放内存
	//g_vPtPosDestinedMark.clear();
	//g_vPtPosRealMark.clear();
	//g_vMarkPointModel.clear();
	std::vector <CPointF>().swap(g_vPtPosDestinedMark);
	std::vector <CPointF>().swap(g_vPtPosRealMark);
	std::vector <HalconModel>().swap(g_vMarkPointModel);


	//AfxMessageBox(_T("ExitInstance完成"));
	//强行结束自己
	//HANDLE hself = GetCurrentProcess();
	//TerminateProcess(hself, 0);
	//_CrtDumpMemoryLeaks();
	

	return CWinApp::ExitInstance();
}

// CLaserMachineApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CLaserMachineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CLaserMachineApp 消息处理程序


void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}




//afx_msg LRESULT CAboutDlg::OnStartMark(WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}
