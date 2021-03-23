// CDlgDevCfgTabScanner.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CDlgDevCfgTabScanner.h"
#include "afxdialogex.h"
#include "DeviceCardMark.h"
#include "DeviceCardMarkBSL.h"
#include "MainFrm.h"
#include "LaserMachineDoc.h"
#include "CameraView.h"
#include "DeviceCardWorktable.h"
#include "CDlgDevCfgTabCamera.h"
#include "XSleep.h"
#include "HalconModel.h"
#include "Model.h"

void SetScannerMarkArcStep(double fScannerArcStep)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fScannerArcStep);
	WritePrivateProfileString(_T("Scanner"), _T("SCANNER_MARK_ARC_STEP"), strTmp, CONFIG_INI_PATH);
}
double ReadScannerMarkArcStep()
{
	CString strTmp;
	GetPrivateProfileString(_T("Scanner"), _T("SCANNER_MARK_ARC_STEP"), _T("0.05"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}


void SetScannerLenRegion(double fScannerLenRegion)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fScannerLenRegion);
	WritePrivateProfileString(_T("Scanner"), _T("SCANNER_LEN_REGION"), strTmp, CONFIG_INI_PATH);
}
double ReadScannerLenRegion()
{
	CString strTmp;
	GetPrivateProfileString(_T("Scanner"), _T("SCANNER_LEN_REGION"), _T("500"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetScannerCaliRegion(double fScannerCaliRegion)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fScannerCaliRegion);
	WritePrivateProfileString(_T("Scanner"), _T("SCANNER_CALI_REGION"), strTmp, CONFIG_INI_PATH);
}
double ReadScannerCaliRegion()
{
	CString strTmp;
	GetPrivateProfileString(_T("Scanner"), _T("SCANNER_CALI_REGION"), _T("40"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetScannerXYFlip(int nScannerXYFlip)
{
	switch (nScannerXYFlip)
	{
	case BST_CHECKED:
		WritePrivateProfileString(_T("Scanner"), _T("XY_FLIP"), _T("1"), CONFIG_INI_PATH);
		break;
	case BST_UNCHECKED:
		WritePrivateProfileString(_T("Scanner"), _T("XY_FLIP"), _T("0"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
int ReadScannerXYFlip()
{
	int nScannerXYFlip;
	nScannerXYFlip = (int)GetPrivateProfileInt(_T("Scanner"), _T("XY_FLIP"), 0, CONFIG_INI_PATH);
	return nScannerXYFlip;
}
void SetScannerInvertX(int nScannerInvertX)
{
	switch (nScannerInvertX)
	{
	case BST_CHECKED:
		WritePrivateProfileString(_T("Scanner"), _T("INVERT_X"), _T("1"), CONFIG_INI_PATH);
		break;
	case BST_UNCHECKED:
		WritePrivateProfileString(_T("Scanner"), _T("INVERT_X"), _T("0"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
int ReadScannerInvertX()
{
	int nScannerInvertX;
	nScannerInvertX = (int)GetPrivateProfileInt(_T("Scanner"), _T("INVERT_X"), 0, CONFIG_INI_PATH);
	return nScannerInvertX;
}
void SetScannerInvertY(int nScannerInvertY)
{
	switch (nScannerInvertY)
	{
	case BST_CHECKED:
		WritePrivateProfileString(_T("Scanner"), _T("INVERT_Y"), _T("1"), CONFIG_INI_PATH);
		break;
	case BST_UNCHECKED:
		WritePrivateProfileString(_T("Scanner"), _T("INVERT_Y"), _T("0"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
int ReadScannerInvertY()
{
	int nScannerInvertY;
	nScannerInvertY = (int)GetPrivateProfileInt(_T("Scanner"), _T("INVERT_Y"), 0, CONFIG_INI_PATH);
	return nScannerInvertY;
}




// CDlgDevCfgTabScanner 对话框

IMPLEMENT_DYNAMIC(CDlgDevCfgTabScanner, CDialogEx)

CDlgDevCfgTabScanner::CDlgDevCfgTabScanner(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICE_CONFIG_TAB_SCANNER, pParent)
	, m_nIndexMatrixCaliPoint(0)
	, m_fLenRegion(180)
	, m_fCaliRegion(140)
	, m_fCaliRadius(0.5)
	, m_fCaliFindScaleMin(0.95)
	, m_fCaliFindScaleMax(1.15)
	, m_fCaliFindMinScore(0.7)
	, m_nScannerXYFlip(0)
	, m_nScannerInvertX(0)
	, m_nScannerInvertY(0)
{

}

CDlgDevCfgTabScanner::~CDlgDevCfgTabScanner()
{
}

void CDlgDevCfgTabScanner::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_SCANNER_MATRIX_CALI_POINT, m_nIndexMatrixCaliPoint);
	DDV_MinMaxInt(pDX, m_nIndexMatrixCaliPoint, 0, 5);
	DDX_Text(pDX, IDC_EDIT_SCANNER_LEN_REGION, m_fLenRegion);
	DDV_MinMaxDouble(pDX, m_fLenRegion, 0, 500);
	DDX_Text(pDX, IDC_EDIT_SCANNER_CALI_REGION, m_fCaliRegion);
	DDV_MinMaxDouble(pDX, m_fCaliRegion, 0, m_fLenRegion);
	DDX_Text(pDX, IDC_EDIT_SCANNER_CALI_RADIUS, m_fCaliRadius);
	DDV_MinMaxDouble(pDX, m_fCaliRadius, 0.1, 1000);
	DDX_Text(pDX, IDC_EDIT_SCANNER_FIND_SCALE_MIN, m_fCaliFindScaleMin);
	DDV_MinMaxDouble(pDX, m_fCaliFindScaleMin, 0.5, 1.5);
	DDX_Text(pDX, IDC_EDIT_SCANNER_FIND_SCALE_MAX, m_fCaliFindScaleMax);
	DDV_MinMaxDouble(pDX, m_fCaliFindScaleMax, 0.5, 1.5);
	DDX_Text(pDX, IDC_EDIT_SCANNER_FIND_SCORE_MIN, m_fCaliFindMinScore);
	DDV_MinMaxDouble(pDX, m_fCaliFindMinScore, 0, 1);
	DDX_Check(pDX, IDC_CHECKIDC_SCANNER_XY_FLIP, m_nScannerXYFlip);
	DDX_Check(pDX, IDC_CHECKIDC_SCANNER_INVERT_X, m_nScannerInvertX);
	DDX_Check(pDX, IDC_CHECKIDC_SCANNER_INVERT_Y, m_nScannerInvertY);
}


BEGIN_MESSAGE_MAP(CDlgDevCfgTabScanner, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_DLG_CALI, &CDlgDevCfgTabScanner::OnBnClickedButtonShowDlgCali)
	ON_BN_CLICKED(IDC_BUTTON_SCANNER_MARK_CALI_POINT, &CDlgDevCfgTabScanner::OnBnClickedButtonScannerMarkCaliPoint)
	ON_BN_CLICKED(IDC_BUTTON_SCANNER_AUTO_FIND_CALI_POINT, &CDlgDevCfgTabScanner::OnBnClickedButtonScannerAutoFindCaliPoint)
	ON_CBN_SELCHANGE(IDC_COMBO_SCANNER_MATRIX_CALI_POINT, &CDlgDevCfgTabScanner::OnCbnSelchangeComboScannerMatrixCaliPoint)
	ON_EN_CHANGE(IDC_EDIT_SCANNER_CALI_REGION, &CDlgDevCfgTabScanner::OnEnChangeEditScannerCaliRegion)
	ON_EN_CHANGE(IDC_EDIT_SCANNER_CALI_RADIUS, &CDlgDevCfgTabScanner::OnEnChangeEditScannerCaliRadius)
	ON_EN_CHANGE(IDC_EDIT_SCANNER_FIND_SCALE_MIN, &CDlgDevCfgTabScanner::OnEnChangeEditScannerFindScaleMin)
	ON_EN_CHANGE(IDC_EDIT_SCANNER_FIND_SCALE_MAX, &CDlgDevCfgTabScanner::OnEnChangeEditScannerFindScaleMax)
	ON_EN_CHANGE(IDC_EDIT_SCANNER_FIND_SCORE_MIN, &CDlgDevCfgTabScanner::OnEnChangeEditScannerFindMinScore)
	ON_BN_CLICKED(IDC_CHECKIDC_SCANNER_XY_FLIP, &CDlgDevCfgTabScanner::OnBnClickedCheckidcScannerXyFlip)
	ON_BN_CLICKED(IDC_CHECKIDC_SCANNER_INVERT_X, &CDlgDevCfgTabScanner::OnBnClickedCheckidcScannerInvertX)
	ON_BN_CLICKED(IDC_CHECKIDC_SCANNER_INVERT_Y, &CDlgDevCfgTabScanner::OnBnClickedCheckidcScannerInvertY)
	ON_EN_CHANGE(IDC_EDIT_SCANNER_LEN_REGION, &CDlgDevCfgTabScanner::OnEnChangeEditScannerLenRegion)
	ON_BN_CLICKED(IDC_BUTTON_SCANNER_FIND_ALL_CALI_POINTS, &CDlgDevCfgTabScanner::OnBnClickedButtonScannerFindAllCaliPoints)
END_MESSAGE_MAP()


// CDlgDevCfgTabScanner 消息处理程序
BOOL CDlgDevCfgTabScanner::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化校正圆combo控件
	((CComboBox*)GetDlgItem(IDC_COMBO_SCANNER_MATRIX_CALI_POINT))->InsertString(0, (_T("3 * 3")));
	((CComboBox*)GetDlgItem(IDC_COMBO_SCANNER_MATRIX_CALI_POINT))->InsertString(1, (_T("5 * 5")));
	((CComboBox*)GetDlgItem(IDC_COMBO_SCANNER_MATRIX_CALI_POINT))->InsertString(2, (_T("9 * 9")));
	((CComboBox*)GetDlgItem(IDC_COMBO_SCANNER_MATRIX_CALI_POINT))->InsertString(3, (_T("17 * 17")));
	((CComboBox*)GetDlgItem(IDC_COMBO_SCANNER_MATRIX_CALI_POINT))->InsertString(4, (_T("33 * 33")));
	((CComboBox*)GetDlgItem(IDC_COMBO_SCANNER_MATRIX_CALI_POINT))->InsertString(5, (_T("65 * 65")));

	m_fLenRegion = ReadScannerLenRegion();
	m_fCaliRegion = ReadScannerCaliRegion();
	m_fCaliRadius = ReadDevCameraMarkCircleRadius();
	m_fCaliFindScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	m_fCaliFindScaleMax = ReadDevCameraMarkCircleFindScaleMax();
	m_fCaliFindMinScore = ReadDevCameraMarkCircleFindMinScore();
	m_nScannerXYFlip = ReadScannerXYFlip();
	m_nScannerInvertX = ReadScannerInvertX();
	m_nScannerInvertY = ReadScannerInvertY();

	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

int CDlgDevCfgTabScanner::GetCountMatrixCaliPointFromIndex()
{
	switch (m_nIndexMatrixCaliPoint)
	{
	case 0:
		return 3;
	case 1:
		return 5;
	case 2:
		return 9;
	case 3:
		return 17;
	case 4:
		return 33;
	case 5:
		return 65;
	default:
		return 0;
	}
}


void CDlgDevCfgTabScanner::OnBnClickedButtonShowDlgCali()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//写区域尺寸
	//SetScannerLenRegion(m_fLenRegion);
	if(pDevCardMark)
		pDevCardMark->SetLenRegion(m_fLenRegion);

	CString strTmp;
	strTmp.Format(_T("%e"), m_fLenRegion);
	WritePrivateProfileString(_T("default"), _T("LEN_WORKSIZE"), strTmp, _T("./binMark/config/LmcPars.cfg"));
	WritePrivateProfileString(_T("CalCoefs"), _T("WorkSize"), strTmp, _T("./binMark/YuanluCor.cor"));


	HINSTANCE m_hMarkDll = NULL;
	HINSTANCE m_hCalDll = NULL;

	if (!m_hMarkDll)
	{
		m_hMarkDll = ::LoadLibrary(_T("MarkSDK.dll"));
		DWORD dd = ::GetLastError();
		TRACE(L"LoadLibrary MarkSDK error %d\n", dd);
	}
	if (!m_hCalDll)
	{
		m_hCalDll = ::LoadLibrary(_T("Calib.dll"));
		DWORD dd = ::GetLastError();
		TRACE(L"LoadLibrary Calib error %d\n", dd);
	}

	if (m_hMarkDll)
	{
		BSL_ShowCaliDlg func = (BSL_ShowCaliDlg)::GetProcAddress(m_hMarkDll, "ShowCaliDlg");
		if (func)
		{
			func(1);
		}
	}

	//pDevCardMark->ShowDlgCali();
}


void CDlgDevCfgTabScanner::OnBnClickedButtonScannerMarkCaliPoint()
{
	// TODO: 在此添加控件通知处理程序代码
	
	//判断打标卡指针//清空打标卡缓冲区//写加工参数
	if (NULL == pDevCardMark
		|| FALSE == pDevCardMark->DeleteALLEntities()
		|| FALSE == pDevCardMark->SetPenFromDefaultProcParm(LayerNum_Reserve1))
		return;

	//判断校正区域
	//m_fCaliRegion = 140;
	if (0 >= m_fCaliRegion)
	{
		AfxMessageBox(_T("请设置正确的校正区域"));
		return;
	}
	//判断打点矩阵
	const int nCtMatrix = GetCountMatrixCaliPointFromIndex();
	if (1 >= nCtMatrix)
	{
		AfxMessageBox(_T("请设置正确的Mark点矩阵"));
		return;
	}

	//计算校正点坐标
	const double fStepMatrix = m_fCaliRegion / ((double)nCtMatrix - 1);		//网格点间距
	const double fRadiusMarkPoint = m_fCaliRadius;							//网格点半径
	const int nNumMatrix = nCtMatrix / 2;									//网格点坐标标识
	double fCenterPos[2];													//网格点坐标
	for (int iY = nNumMatrix; iY >= -nNumMatrix; iY--)						//由上到下
	{
		for (int iX = -nNumMatrix; iX <= nNumMatrix; iX++)					//由左到右
		{
			TRACE("(%d, %d)\n", iX, iY);
			fCenterPos[0] = fStepMatrix * iX;
			fCenterPos[1] = fStepMatrix * iY;
			pDevCardMark->AddEntityCircle(fCenterPos, fRadiusMarkPoint, 0, 0, LayerNum_Reserve1);	//0度开始，顺时针，默认笔号
		}
	}
	pDevCardMark->SaveEntityToFile();

	//开始打矩阵圆
	pDevCardMark->StartMarkCardMark();
	pDevCardMark->WaitForThreadsEnded();
}


void CDlgDevCfgTabScanner::OnBnClickedButtonScannerAutoFindCaliPoint()
{
	// TODO: 在此添加控件通知处理程序代码

	//判断运动控制卡
	if (NULL == pDevCardWorktable)
		return;
	//判断相机是否打开
	CCameraView* pCameraView = (CCameraView*)
						((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter1.GetPane(1, 0);
	if (NULL == pCameraView)
		return;
	if (FALSE == pCameraView->m_pHalconWnd->m_bThreadsAreRunning)
	{
		AfxMessageBox(_T("请先打开相机"));
		return;
	}

	//判断打点矩阵
	const int nCtMatrix = GetCountMatrixCaliPointFromIndex();
	if (1 >= nCtMatrix)
	{
		AfxMessageBox(_T("请设置正确的Mark点矩阵"));
		return;
	}
	//生成目标点坐标矩阵
	const double fStepMatrix = m_fCaliRegion / ((double)nCtMatrix - 1);		//网格点间距
	std::vector <CPointF> vPtPosMatrixDext;
	const int nNumMatrix = nCtMatrix / 2;									//网格点坐标标识
	for (int iY = nNumMatrix; iY >= -nNumMatrix; iY--)						//由上到下
	{
		for (int iX = -nNumMatrix; iX <= nNumMatrix; iX++)					//由左到右
		{
			TRACE("(%d, %d)\n", iX, iY);
			vPtPosMatrixDext.push_back(CPointF((FLOAT)fStepMatrix * iX, (FLOAT)fStepMatrix * iY));
		}
	}
	//生成定位圆模板
	double fRadius, fPixelSize, fScaleMin, fScaleMax, fMinScore;
	fRadius = ReadDevCameraMarkCircleRadius();
	fPixelSize = ReadDevCameraPixelSize();
	fMinScore = ReadDevCameraMarkCircleFindMinScore();
	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();
	HalconModel modelCircle(_T("圆"), fRadius, fPixelSize);
	modelCircle.SetScale(fScaleMin, fScaleMax);
	modelCircle.SetMinScore(fMinScore);

	CString strTmpWt;
	double fPosTmpWtX, fPosTmpWtY, fPosTmpWtOrgX, fPosTmpWtOrgY;
	//存当前位置坐标
	double fPosResvX, fPosResvY;
	pDevCardWorktable->GetAbsPosXY(&fPosResvX, &fPosResvY);
	//移动工作台到第一个点
	double fPosCameraX, fPosCameraY;
	fPosCameraX = ReadDevCameraPosX();
	fPosCameraY = ReadDevCameraPosY();
	//pDevCardWorktable->PosMoveXY(fPosCameraX - (m_fCaliRegion / 2) - fStepMatrix, fPosCameraY + (m_fCaliRegion / 2));
	pDevCardWorktable->PosMoveXY(fPosCameraX, fPosCameraY, TRUE);
	pDevCardWorktable->WaitForMoveEndedXY();
	Sleep(1000);
	pDevCardWorktable->GetAbsPosXY(&fPosTmpWtOrgX, &fPosTmpWtOrgY);
	pDevCardWorktable->PosMoveXY( - (m_fCaliRegion / 2) - fStepMatrix,  (m_fCaliRegion / 2), TRUE);
	pDevCardWorktable->WaitForMoveEndedXY();
	//strTmpWt.Format(_T("准备\n%.2f\n%.2f"), fPosCameraX - (m_fCaliRegion / 2) - fStepMatrix, fPosCameraY + (m_fCaliRegion / 2));
	//AfxMessageBox(strTmpWt);
	Sleep(1000);
	//AfxMessageBox(_T("准备抓标"));

	//自动抓标循环
	int nCtFinded = 0;
	CString strTmp;
	std::vector <int> vIndexUnFinded;
	std::vector <CPointF> vPtPosMatrixDelta, vPtPosMatrixReal, vPtPosTmp;
	for (int i = 1; i <= nCtMatrix * nCtMatrix; i++)
	{
		//向右横移
		//AfxMessageBox(strTmpWt);
		pDevCardWorktable->PosMoveXY(fStepMatrix, 0, TRUE);
		//strTmpWt.Format(_T("开始运动: %.2f, %.2f"), fStepMatrix, 0);
		//SetDlgItemText(IDC_STATIC_MARK_POINT, strTmpWt);
		pDevCardWorktable->WaitForMoveEndedXY();
		pDevCardWorktable->GetAbsPosXY(&fPosTmpWtX, &fPosTmpWtY);
		strTmpWt.Format(_T("当前在第%d-%d个点\n当前坐标为%.2f, %.2f"), 1 + (i-1)/nCtMatrix,
																	i%nCtMatrix != 0 ? i % nCtMatrix : nCtMatrix, 
																	fPosTmpWtX - fPosTmpWtOrgX, fPosTmpWtY - fPosTmpWtOrgY);
		SetDlgItemText(IDC_STATIC_MARK_POINT, strTmpWt);
		XSleep(1000);
		//strTmp.Format(_T("当前点%d"), i);
		//AfxMessageBox(strTmp);

		//抓圆10次，抓不到退出流程
		int nCtSearch = 10;
		while (nCtSearch)
		{
			int nFindedPt = pCameraView->m_pHalconWnd->LocateModel(modelCircle, &vPtPosTmp);
			if (1 == nFindedPt)
			{
				XSleep(1000);
				//如果抓到一个
				//strTmp.Format(_T("当前点%d\n抓到1个圆\n(%lf, %lf)"), i, vPtPosTmp.front().x, vPtPosTmp.front().y);
				//AfxMessageBox(strTmp);
				vPtPosMatrixDelta.push_back(vPtPosTmp.front());
				vPtPosMatrixReal.push_back(vPtPosMatrixDext[(size_t)i - 1] + vPtPosTmp.front());
				nCtFinded++;
				break;
			}
			else
			{
				XSleep(1);
				//如果没抓到圆
				//strTmp.Format(_T("当前点%d\n没有抓到圆"), i);
				//AfxMessageBox(strTmp);
				//vPtPosMatrixDelta.push_back(CPointF(0, 0));
				//vPtPosMatrixReal.push_back(vPtPosMatrixDext[(size_t)i - 1]);
				//vIndexUnFinded.push_back(i);
			}

			nCtSearch--;
		}

		//if (FALSE == pCameraView->m_pHalconWnd->AutoFindCircle(&vPtPosTmp))
		//{
		//	XSleep(1);
		//	//如果没抓到圆
		//	//strTmp.Format(_T("当前点%d\n没有抓到圆"), i);
		//	//AfxMessageBox(strTmp);
		//	vPtPosMatrixDelta.push_back(CPointF(0, 0));
		//	vPtPosMatrixReal.push_back(vPtPosMatrixDext[(size_t)i - 1]);
		//	vIndexUnFinded.push_back(i);
		//}
		//else if (1 < vPtPosTmp.size())
		//{
		//	XSleep(1);
		//	//如果抓到多个圆
		//	//strTmp.Format(_T("当前点%d\n抓到多个圆"), i);
		//	//AfxMessageBox(strTmp);
		//	vPtPosMatrixDelta.push_back(CPointF(0, 0));
		//	vPtPosMatrixReal.push_back(vPtPosMatrixDext[(size_t)i - 1]);
		//	vIndexUnFinded.push_back(i);
		//}
		//else
		//{
		//	XSleep(1000);
		//	//如果抓到一个
		//	//strTmp.Format(_T("当前点%d\n抓到1个圆\n(%lf, %lf)"), i, vPtPosTmp.front().x, vPtPosTmp.front().y);
		//	//AfxMessageBox(strTmp);
		//	vPtPosMatrixDelta.push_back(vPtPosTmp.front());
		//	vPtPosMatrixReal.push_back(vPtPosMatrixDext[(size_t)i - 1] + vPtPosTmp.front());
		//}

		//如果10次都没有找到圆就跳出流程
		if (0 == nCtSearch)
		{
			double fPosXTmp, fPosYTmp;
			pDevCardWorktable->GetAbsPosXY(&fPosXTmp, &fPosYTmp);
			//strTmpWt.Format(_T("完毕%.2f\n%.2f"), fPosResvX - fPosXTmp, fPosResvY - fPosYTmp);
			//AfxMessageBox(strTmpWt);
			pDevCardWorktable->PosMoveXY(fPosResvX - fPosXTmp, fPosResvY - fPosYTmp, TRUE);
			pDevCardWorktable->WaitForMoveEndedXY();
			XSleep(1);
			break;
		}

		//末点移动
		if (i == nCtMatrix * nCtMatrix)
		{
			//如果是最后一个点，回原位置
			double fPosXTmp, fPosYTmp;
			pDevCardWorktable->GetAbsPosXY(&fPosXTmp, &fPosYTmp);
			//strTmpWt.Format(_T("完毕%.2f\n%.2f"), fPosResvX - fPosXTmp, fPosResvY - fPosYTmp);
			//AfxMessageBox(strTmpWt);
			pDevCardWorktable->PosMoveXY(fPosResvX - fPosXTmp, fPosResvY - fPosYTmp, TRUE);
			pDevCardWorktable->WaitForMoveEndedXY();
			XSleep(1);
		}
		else if (0 == i % nCtMatrix)
		{
			//如果不是最后一个点，且是行尾，移动到下一行第一个点左边
			//strTmpWt.Format(_T("去下一行\n%.2f\n%.2f"), -(m_fCaliRegion + fStepMatrix), -fStepMatrix);
			//AfxMessageBox(strTmpWt);
			//strTmpWt.Format(_T("当前在第%d个点\n当前坐标为%.2f, %.2f\n下一条移动指令为%.2f, %.2f"), i, fPosTmpWtX - fPosTmpWtOrgX, fPosTmpWtY - fPosTmpWtOrgY, -(m_fCaliRegion + fStepMatrix), -fStepMatrix);
			//SetDlgItemText(IDC_STATIC_MARK_POINT, strTmpWt);
			pDevCardWorktable->PosMoveXY(-(m_fCaliRegion + fStepMatrix), -fStepMatrix, TRUE);
			strTmpWt.Format(_T("开始运动: %.2f, %.2f"), -(m_fCaliRegion + fStepMatrix), -fStepMatrix);
			SetDlgItemText(IDC_STATIC_MARK_POINT, strTmpWt);
			pDevCardWorktable->WaitForMoveEndedXY();
			pDevCardWorktable->GetAbsPosXY(&fPosTmpWtX, &fPosTmpWtY);
			strTmpWt.Format(_T("当前在行首坐标为%.2f, %.2f"), fPosTmpWtX - fPosTmpWtOrgX, fPosTmpWtY - fPosTmpWtOrgY);
			SetDlgItemText(IDC_STATIC_MARK_POINT, strTmpWt);
			XSleep(1000);
		}
	}
	
	//显示抓到了几个点，哪几个点没抓到
	//int nCtUnFinded = (int)vIndexUnFinded.size();
	//int nCtFinded = nCtMatrix * nCtMatrix - nCtUnFinded;
	CString strMsg, strTmp1;
	strMsg.Format(_T("总共%d个校正点，抓到了%d个点"), nCtMatrix* nCtMatrix, nCtFinded);
	//strMsg.Format(_T("总共%d个校正点，抓到了%d个，没抓到%d个\n没抓到的点："), nCtMatrix * nCtMatrix, nCtFinded, nCtUnFinded);
	//for (int i = 0; i < nCtUnFinded; i++)
	//{
	//	strTmp1.Format(_T("%d, "), vIndexUnFinded[i]);
	//	strMsg += strTmp1;
	//}
	AfxMessageBox(strMsg);

	//生成.txt corRegion或corDelta
	WriteTxtCor(_T("Delta"), &vPtPosMatrixDelta);
	WriteTxtCor(_T("Real"), &vPtPosMatrixReal);

}


void CDlgDevCfgTabScanner::OnCbnSelchangeComboScannerMatrixCaliPoint()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CDlgDevCfgTabScanner::OnEnChangeEditScannerCaliRegion()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetScannerCaliRegion(m_fCaliRegion);
}

void CDlgDevCfgTabScanner::WriteTxtCor(CString strCor, std::vector <CPointF>* vPtPos)
{
	//设定文件名
	CString strTmp, strTxtCorFileNameTmp;
	CString strTxtCorFileName = _T("./binMark/cor");

	const int nCtPt = (int)vPtPos->size();
	strTmp.Format(_T("%dx%d"), (int)sqrt(nCtPt), (int)sqrt(nCtPt));
	strTxtCorFileName += strTmp;
	strTxtCorFileName += strCor;

	//判断文件是否存在，如果不存在，则创造该文件；如果存在，则创造新的文件
	strTmp.Format(_T(".txt"));
	strTxtCorFileNameTmp = strTxtCorFileName + strTmp;
	int nCtCorFile = 0;
	while (-1 != GetFileAttributes(strTxtCorFileNameTmp))
	{
		//如果文件存在
		nCtCorFile++;
		strTmp.Format(_T("_%d"), nCtCorFile);
		strTxtCorFileNameTmp = strTxtCorFileName + strTmp;
		strTmp.Format(_T(".txt"));
		strTxtCorFileNameTmp += strTmp;
	}
	strTxtCorFileName = strTxtCorFileNameTmp;

	//打开文件
	CStdioFile fileTmp;
	CString strLineTmp;
	BOOL bFlagOpenFile = fileTmp.Open(strTxtCorFileName, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite);
	if (bFlagOpenFile == FALSE)
	{
		AfxMessageBox(_T("文件打开失败！"));
		return;
	}
	UpdateData(TRUE);
	fileTmp.SeekToBegin();

	//写文件
	for (int i = 0; i < nCtPt; i++)
	{
		strLineTmp.Format(_T("%.5f %.5f\n"), vPtPos->at(i).x, vPtPos->at(i).y);
		fileTmp.WriteString(strLineTmp);

	}
	fileTmp.Close();
}

void CDlgDevCfgTabScanner::OnEnChangeEditScannerCaliRadius()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCircleRadius(m_fCaliRadius);
}


void CDlgDevCfgTabScanner::OnEnChangeEditScannerFindScaleMin()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCircleFindScaleMin(m_fCaliFindScaleMin);
}


void CDlgDevCfgTabScanner::OnEnChangeEditScannerFindScaleMax()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCircleFindScaleMax(m_fCaliFindScaleMax);
}


void CDlgDevCfgTabScanner::OnEnChangeEditScannerFindMinScore()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCircleFindMinScore(m_fCaliFindMinScore);
}


void CDlgDevCfgTabScanner::OnBnClickedCheckidcScannerXyFlip()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetScannerXYFlip(m_nScannerXYFlip);
	pDevCardMark->SetScannerXYFlipFlag(m_nScannerXYFlip, m_nScannerInvertX, m_nScannerInvertY);
}


void CDlgDevCfgTabScanner::OnBnClickedCheckidcScannerInvertX()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetScannerInvertX(m_nScannerInvertX);
	pDevCardMark->SetScannerXYFlipFlag(m_nScannerXYFlip, m_nScannerInvertX, m_nScannerInvertY);
}


void CDlgDevCfgTabScanner::OnBnClickedCheckidcScannerInvertY()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetScannerInvertY(m_nScannerInvertY);
	pDevCardMark->SetScannerXYFlipFlag(m_nScannerXYFlip, m_nScannerInvertX, m_nScannerInvertY);
}


void CDlgDevCfgTabScanner::OnEnChangeEditScannerLenRegion()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetScannerLenRegion(m_fLenRegion);
	//
	//CString strTmp;
	//strTmp.Format(_T("%e"), m_fLenRegion);
	//WritePrivateProfileString(_T("default"), _T("LEN_WORKSIZE"), strTmp, _T("./binMark/config/LmcPars.cfg"));
	//WritePrivateProfileString(_T("CalCoefs"), _T("WorkSize"), strTmp, _T("./binMark/YuanluCor.cor"));


}


void CDlgDevCfgTabScanner::OnBnClickedButtonScannerFindAllCaliPoints()
{
	// TODO: 在此添加控件通知处理程序代码

	//判断相机是否打开
	CCameraView* pCameraView = (CCameraView*)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter1.GetPane(1, 0);
	if (NULL == pCameraView)
		return;
	if (FALSE == pCameraView->m_pHalconWnd->m_bThreadsAreRunning)
	{
		AfxMessageBox(_T("请先打开相机"));
		return;
	}

	//判断打点矩阵
	const int nCtMatrix = GetCountMatrixCaliPointFromIndex();
	if (1 >= nCtMatrix)
	{
		AfxMessageBox(_T("请设置正确的Mark点矩阵"));
		return;
	}
	//生成目标点坐标矩阵
	const double fStepMatrix = m_fCaliRegion / ((double)nCtMatrix - 1);		//网格点间距
	std::vector <CPointF> vPtPosMatrixDext;
	const int nNumMatrix = nCtMatrix / 2;									//网格点坐标标识
	for (int iY = nNumMatrix; iY >= -nNumMatrix; iY--)						//由上到下
	{
		for (int iX = -nNumMatrix; iX <= nNumMatrix; iX++)					//由左到右
		{
			TRACE("(%d, %d)\n", iX, iY);
			vPtPosMatrixDext.push_back(CPointF((FLOAT)fStepMatrix * iX, (FLOAT)fStepMatrix * iY));
		}
	}
	//生成定位圆模板
	double fRadius, fPixelSize, fScaleMin, fScaleMax, fMinScore;
	fRadius = ReadDevCameraMarkCircleRadius();
	fPixelSize = ReadDevCameraPixelSize();
	fMinScore = ReadDevCameraMarkCircleFindMinScore();
	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();
	ModelBase* pModel = ModelFactory::creatModel(ModelType::MT_Circle, fPixelSize, fRadius);
	pModel->SetMinScore(fMinScore);
	pModel->SetScale(fScaleMin, fScaleMax);

	//自动抓标循环
	std::vector <CPointF> vPtPosMatrixDelta, vPtPosMatrixReal;
	std::vector <double> vFAngle;
	pModel->LocateModel(vPtPosMatrixReal, vFAngle, TRUE, TRUE, TRUE, nCtMatrix, nCtMatrix);
	if ((size_t)nCtMatrix * nCtMatrix != vPtPosMatrixReal.size())
	{
		delete pModel;
		pModel = NULL;
		AfxMessageBox(_T("没有找到所有mark点"));
		return;
	}

	//根据抓标结果生成目标点阵
	CPointF ptCameraPos;
	ptCameraPos.x = ReadDevCameraPosX();
	ptCameraPos.y = ReadDevCameraPosY();
	for (int i = 0; i < nCtMatrix * nCtMatrix; i++)
	{
		vPtPosMatrixReal[i] += ptCameraPos;
		vPtPosMatrixDelta.push_back(vPtPosMatrixReal[i] - vPtPosMatrixDext[i]);
	}

	//生成.txt corReal或corDelta
	WriteTxtCor(_T("Delta"), &vPtPosMatrixDelta);
	WriteTxtCor(_T("Real"), &vPtPosMatrixReal);

	delete pModel;
	pModel = NULL;
}
