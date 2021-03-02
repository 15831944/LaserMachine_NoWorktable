// CDlgDevCfgTabCamera.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CDlgDevCfgTabCamera.h"
#include "CameraView.h"
#include "MainFrm.h"
#include "afxdialogex.h"
#include "DeviceCamera.h"
#include "Model.h"


//相机硬件配置读写
void SetDevCameraName(CAMERA_NAME eCameraName)
{
	switch (eCameraName)
	{
	case CAMERA_NAME::CAMERA_NONE:
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME"), _T("CAMERA_NONE"), CONFIG_INI_PATH);
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME_INDEX"), _T("-1"), CONFIG_INI_PATH);
		break;
	case CAMERA_NAME::CAMERA_GENERAL_GE:
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME"), _T("CAMERA_GENERAL_GE"), CONFIG_INI_PATH);
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME_INDEX"), _T("0"), CONFIG_INI_PATH);
		break;
	case CAMERA_NAME::CAMERA_DAHENG_MER:
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME"), _T("CAMERA_DAHENG_MER"), CONFIG_INI_PATH);
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME_INDEX"), _T("1"), CONFIG_INI_PATH);
		break;
	case CAMERA_NAME::CAMERA_2:
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME"), _T("CAMERA_2"), CONFIG_INI_PATH);
		WritePrivateProfileString(_T("DeviceCamera"), _T("NAME_INDEX"), _T("2"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}

CAMERA_NAME ReadDevCameraName()
{
	CAMERA_NAME eCameraName;
	eCameraName = (CAMERA_NAME)GetPrivateProfileInt(_T("DeviceCamera"), _T("NAME_INDEX"), -1, CONFIG_INI_PATH);
	return eCameraName;
}

void SetDevCameraReverse(int nCameraReverse)
{
	switch (nCameraReverse)
	{
	case BST_CHECKED:
		WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_REVERSE"), _T("1"), CONFIG_INI_PATH);
		break;
	case BST_UNCHECKED:
		WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_REVERSE"), _T("0"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
int ReadDevCameraReverse()
{
	int nCameraReverse;
	nCameraReverse = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_REVERSE"), 0, CONFIG_INI_PATH);
	return nCameraReverse;
}
void SetDevCameraMirrorX(int nCameraMirrorX)
{
	switch (nCameraMirrorX)
	{
	case BST_CHECKED:
		WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MIRROR_X"), _T("1"), CONFIG_INI_PATH);
		break;
	case BST_UNCHECKED:
		WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MIRROR_X"), _T("0"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
int ReadDevCameraMirrorX()
{
	int nCameraMirrorX;
	nCameraMirrorX = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_MIRROR_X"), 0, CONFIG_INI_PATH);
	return nCameraMirrorX;
}
void SetDevCameraMirrorY(int nCameraMirrorY)
{
	switch (nCameraMirrorY)
	{
	case BST_CHECKED:
		WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MIRROR_Y"), _T("1"), CONFIG_INI_PATH);
		break;
	case BST_UNCHECKED:
		WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MIRROR_Y"), _T("0"), CONFIG_INI_PATH);
		break;
	default:
		break;
	}
}
int ReadDevCameraMirrorY()
{
	int nCameraMirrorY;
	nCameraMirrorY = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_MIRROR_Y"), 0, CONFIG_INI_PATH);
	return nCameraMirrorY;
}
void SetDevCameraBrightness(int nCameraBrightness)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nCameraBrightness);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_BRIGHTNESS"), strTmp, CONFIG_INI_PATH);
}
int ReadDevCameraBrightness()
{
	int nCameraBrightness;
	nCameraBrightness = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_BRIGHTNESS"), 0, CONFIG_INI_PATH);
	return nCameraBrightness;
}
void SetDevCameraContrast(int nCameraContrast)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nCameraContrast);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_CONTRAST"), strTmp, CONFIG_INI_PATH);
}
int ReadDevCameraContrast()
{
	int nCameraContrast;
	nCameraContrast = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_CONTRAST"), 0, CONFIG_INI_PATH);
	return nCameraContrast;
}
void SetDevCameraExposure(int nCameraExposure)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nCameraExposure);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_EXPOSURE"), strTmp, CONFIG_INI_PATH);
}
int ReadDevCameraExposure()
{
	int nCameraExposure;
	nCameraExposure = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_EXPOSURE"), 0, CONFIG_INI_PATH);
	return nCameraExposure;
}
void SetDevCameraGain(int nCameraGain)
{
	CString strTmp;
	strTmp.Format(_T("%d"), nCameraGain);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_GAIN"), strTmp, CONFIG_INI_PATH);
}
int ReadDevCameraGain()
{
	int nCameraGain;
	nCameraGain = (int)GetPrivateProfileInt(_T("DeviceCamera"), _T("CAMERA_GAIN"), 0, CONFIG_INI_PATH);
	return nCameraGain;
}
void SetDevCameraMoveUnit(double fCameraMoveUnit)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMoveUnit);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MOVE_UNIT"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMoveUnit()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MOVE_UNIT"), _T("100"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraPosX(double fCameraPos)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraPos);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_POS_X"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraPosX()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_POS_X"), _T("0"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraPosY(double fCameraPos)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraPos);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_POS_Y"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraPosY()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_POS_Y"), _T("0"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraPixelSize(double fCameraPixelSize)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraPixelSize);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_PIXEL_SIZE"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraPixelSize()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_PIXEL_SIZE"), _T("0"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevCameraMarkCrossLength(double fCameraMarkCrossLength)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMarkCrossLength);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CROSS_LENGTH"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMarkCrossLength()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CROSS_LENGTH"), _T("5"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraMarkCrossWidth(double fCameraMarkCrossWidth)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMarkCrossWidth);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CROSS_WIDTH"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMarkCrossWidth()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CROSS_WIDTH"), _T("1"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}

void SetDevCameraMarkCircleRadius(double fCameraMarkCircleRadius)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMarkCircleRadius);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_RADIUS"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMarkCircleRadius()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_RADIUS"), _T("1"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraMarkCircleFindScaleMin(double fCameraMarkCircleFindScaleMin)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMarkCircleFindScaleMin);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_FIND_SCALE_MIN"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMarkCircleFindScaleMin()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_FIND_SCALE_MIN"), _T("0.9"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraMarkCircleFindScaleMax(double fCameraMarkCircleFindScaleMax)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMarkCircleFindScaleMax);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_FIND_SCALE_MAX"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMarkCircleFindScaleMax()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_FIND_SCALE_MAX"), _T("1.1"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetDevCameraMarkCircleFindMinScore(double fCameraMarkCircleMinScore)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fCameraMarkCircleMinScore);
	WritePrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_FIND_MIN_SCORE"), strTmp, CONFIG_INI_PATH);
}
double ReadDevCameraMarkCircleFindMinScore()
{
	CString strTmp;
	GetPrivateProfileString(_T("DeviceCamera"), _T("CAMERA_MARK_CIRCLE_FIND_MIN_SCORE"), _T("0.7"), strTmp.GetBuffer(MAX_DOUBLE_PRECISION), MAX_DOUBLE_PRECISION, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}


// CDlgDevCfgTabCamera 对话框

IMPLEMENT_DYNAMIC(CDlgDevCfgTabCamera, CDialogEx)

CDlgDevCfgTabCamera::CDlgDevCfgTabCamera(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEVICE_CONFIG_TAB_CAMERA, pParent)
	, m_fMarkRadius(0.5)
	, m_fMarkDistance(10)
{

}

CDlgDevCfgTabCamera::~CDlgDevCfgTabCamera()
{
}

void CDlgDevCfgTabCamera::DoDataExchange(CDataExchange* pDX)
{
	DDX_Radio(pDX, IDC_RADIO_CAMERA_DAHENG, m_nIndexRadioCamera);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_BIRGHTNESS, m_cSliderCameraBrightness);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_CONTRAST, m_cSliderCameraContrast);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_EXPOSURE, m_cSliderCameraExposure);
	DDX_Control(pDX, IDC_SLIDER_CAMERA_GAIN, m_cSliderCameraGain);
	DDX_Check(pDX, IDC_CHECK_CAMERA_REVERSE, m_nCameraReverse);
	DDX_Check(pDX, IDC_CHECK_CAMERA_MIRROR_X, m_nCameraMirrorX);
	DDX_Check(pDX, IDC_CHECK_CAMERA_MIRROR_Y, m_nCameraMirrorY);
	DDX_Text(pDX, IDC_EDIT_CAMERA_POS_X, m_fCameraPosX);
	DDX_Text(pDX, IDC_EDIT_CAMERA_POS_Y, m_fCameraPosY);
	DDX_Text(pDX, IDC_EDIT_CAMERA_PIXEL_SIZE, m_fCameraPixelSize);
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CAMERA_MARK_RADIUS, m_fMarkRadius);
	DDV_MinMaxDouble(pDX, m_fMarkRadius, 0, DBL_MAX);
	DDX_Text(pDX, IDC_EDIT_CAMERA_MARK_DISTANCE, m_fMarkDistance);
	DDV_MinMaxDouble(pDX, m_fMarkDistance, 0, DBL_MAX);
}


BEGIN_MESSAGE_MAP(CDlgDevCfgTabCamera, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_APPLY, &CDlgDevCfgTabCamera::OnBnClickedButtonCameraApply)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CAMERA_BIRGHTNESS, &CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraBirghtness)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_BRIGHTNESS, &CDlgDevCfgTabCamera::OnEnChangeEditCameraBrightness)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CAMERA_CONTRAST, &CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraContrast)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_CONTRAST, &CDlgDevCfgTabCamera::OnEnChangeEditCameraContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CAMERA_EXPOSURE, &CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraExposure)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_EXPOSURE, &CDlgDevCfgTabCamera::OnEnChangeEditCameraExposure)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CAMERA_GAIN, &CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraGain)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_GAIN, &CDlgDevCfgTabCamera::OnEnChangeEditCameraGain)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_CAL_PIXEL_SIZE, &CDlgDevCfgTabCamera::OnBnClickedButtonCameraCalPixelSize)
	ON_BN_CLICKED(IDC_BUTTON_CAMERA_CALI_CAMERA_CENTER, &CDlgDevCfgTabCamera::OnBnClickedButtonCameraCaliCameraCenter)
END_MESSAGE_MAP()


// CDlgDevCfgTabCamera 消息处理程序
BOOL CDlgDevCfgTabCamera::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//选择相机
	m_nIndexRadioCamera = (int)ReadDevCameraName();

	//一、设定Check Box为 选中状态
	//((CButton*)GetDlgItem(ID号))->SetCheck(TRUE);
	//(SetCheck(FALSE)) 为不选中, 如果想初始化为选中状态, 则在InitDlg函数中加入下面这段语句。
	//((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	//二、检查Check Box是否为选中状态
	//	可使用GetCheck()这个函数, 如下：
	//	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()) 判断是否选中；
	//	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_RADIO3))->GetCheck()) 判断是否未选中。

	//反转，镜像
	m_nCameraReverse = ReadDevCameraReverse();
	m_nCameraMirrorX = ReadDevCameraMirrorX();
	m_nCameraMirrorY = ReadDevCameraMirrorY();
	//亮度
	m_nCameraBrightness = ReadDevCameraBrightness();
	m_cSliderCameraBrightness.SetRange(m_cnSliderSliderCameraBrightnessMin, m_cnSliderSliderCameraBrightnessMax, TRUE);
	m_cSliderCameraBrightness.SetPos(m_nCameraBrightness);
	//对比度
	m_nCameraContrast = ReadDevCameraContrast();
	m_cSliderCameraContrast.SetRange(m_cnSliderSliderCameraContrastMin, m_cnSliderSliderCameraContrastMax, TRUE);
	m_cSliderCameraContrast.SetPos(m_nCameraContrast);
	//曝光
	m_nCameraExposure = ReadDevCameraExposure();
	m_cSliderCameraExposure.SetRange(m_cnSliderSliderCameraExposureMin, m_cnSliderSliderCameraExposureMax, TRUE);
	m_cSliderCameraExposure.SetPos(m_nCameraExposure);
	//增益
	m_nCameraGain = ReadDevCameraGain();
	m_cSliderCameraGain.SetRange(m_cnSliderSliderCameraGainMin, m_cnSliderSliderCameraGainMax, TRUE);
	m_cSliderCameraGain.SetPos(m_nCameraGain);
	//相机中心->振镜中心位移
	m_fCameraPosX = ReadDevCameraPosX();
	m_fCameraPosY = ReadDevCameraPosY();
	//像素尺寸
	m_fCameraPixelSize = ReadDevCameraPixelSize();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgDevCfgTabCamera::OnBnClickedButtonCameraApply()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	//写ini
	SetDevCameraName((CAMERA_NAME)m_nIndexRadioCamera);
	SetDevCameraReverse(m_nCameraReverse);
	SetDevCameraMirrorX(m_nCameraMirrorX);
	SetDevCameraMirrorY(m_nCameraMirrorY);
	SetDevCameraBrightness(m_nCameraBrightness);
	SetDevCameraContrast(m_nCameraContrast);
	SetDevCameraExposure(m_nCameraExposure);	
	SetDevCameraGain(m_nCameraGain);
	SetDevCameraPosX(m_fCameraPosX);
	SetDevCameraPosY(m_fCameraPosY);
	SetDevCameraPixelSize(m_fCameraPixelSize);

}


void CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraBirghtness(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraBrightness.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT_CAMERA_BRIGHTNESS, strTmp);

	m_nCameraBrightness = nPosTmp;

	*pResult = 0;
}


void CDlgDevCfgTabCamera::OnEnChangeEditCameraBrightness()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT_CAMERA_BRIGHTNESS);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT_CAMERA_BRIGHTNESS, NULL, 1);
	m_cSliderCameraBrightness.SetPos(nPosTmp);
	m_nCameraBrightness = nPosTmp;
}




void CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraContrast(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraContrast.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT_CAMERA_CONTRAST, strTmp);

	m_nCameraContrast = nPosTmp;

	*pResult = 0;
}


void CDlgDevCfgTabCamera::OnEnChangeEditCameraContrast()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT_CAMERA_CONTRAST);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT_CAMERA_CONTRAST, NULL, 1);
	m_cSliderCameraContrast.SetPos(nPosTmp);
	m_nCameraContrast = nPosTmp;

}


void CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraExposure(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraExposure.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT_CAMERA_EXPOSURE, strTmp);

	m_nCameraExposure = nPosTmp;


	*pResult = 0;
}


void CDlgDevCfgTabCamera::OnEnChangeEditCameraExposure()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT_CAMERA_EXPOSURE);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT_CAMERA_EXPOSURE, NULL, 1);
	m_cSliderCameraExposure.SetPos(nPosTmp);
	m_nCameraExposure = nPosTmp;

}


void CDlgDevCfgTabCamera::OnNMCustomdrawSliderCameraGain(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraGain.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT_CAMERA_GAIN, strTmp);

	m_nCameraGain = nPosTmp;


	*pResult = 0;
}


void CDlgDevCfgTabCamera::OnEnChangeEditCameraGain()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT_CAMERA_GAIN);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT_CAMERA_GAIN, NULL, 1);
	m_cSliderCameraGain.SetPos(nPosTmp);
	m_nCameraGain = nPosTmp;

}



void CDlgDevCfgTabCamera::OnBnClickedButtonCameraCalPixelSize()
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

	UpdateData(TRUE);

	double fPixelSize, fRadius, fDistance, fScaleMin, fScaleMax, fMinScore;
	fPixelSize = m_fCameraPixelSize;
	fRadius = m_fMarkRadius;
	fDistance = m_fMarkDistance;
	fMinScore = ReadDevCameraMarkCircleFindMinScore();
	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();

	std::vector<CPointF> ptPos;
	ModelBase* pModel = ModelFactory::creatModel(ModelType::MT_Circle, fPixelSize, fRadius);
	pModel->SetScale(fScaleMin, fScaleMax);
	pModel->SetMinScore(fMinScore);
	pModel->LocateModel(ptPos);
	
	if (2 == ptPos.size())
	{
		double fDistanceCal, fDistanceCalX, fDistanceCalY;
		CPointF pt1, pt2, ptDistance;
		pt1 = ptPos[0];
		pt2 = ptPos[1];

		fDistanceCalX = abs(pt1.x - pt2.x);
		fDistanceCalY = abs(pt1.y - pt2.y);
		fDistanceCal = sqrt(pow(fDistanceCalX, 2) + pow(fDistanceCalY, 2));

		m_fCameraPixelSize *= fDistance / fDistanceCal;
		UpdateData(FALSE);
	}
	else
		AfxMessageBox(_T("没有找到两个标记圆"));
	
	
	
	delete pModel;
	pModel = NULL;

}


void CDlgDevCfgTabCamera::OnBnClickedButtonCameraCaliCameraCenter()
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

	UpdateData(TRUE);

	double fPixelSize, fRadius, fScaleMin, fScaleMax, fMinScore;
	fPixelSize = m_fCameraPixelSize;
	fRadius = m_fMarkRadius;
	fMinScore = ReadDevCameraMarkCircleFindMinScore();
	fScaleMin = ReadDevCameraMarkCircleFindScaleMin();
	fScaleMax = ReadDevCameraMarkCircleFindScaleMax();

	std::vector<CPointF> ptPos;
	ModelBase* pModel = ModelFactory::creatModel(ModelType::MT_Circle, fPixelSize, fRadius);
	pModel->SetScale(fScaleMin, fScaleMax);
	pModel->SetMinScore(fMinScore);
	pModel->SetMatchDomain(CPointF(0, 0), 10);
	pModel->LocateModel(ptPos);

	if (1 != ptPos.size())
	{
		AfxMessageBox(_T("没有找到mark圆"));
		return;
	}

	CPointF ptScannerCenter = ptPos[0];
	if(20 < abs(ptScannerCenter.x) && 20 < abs(ptScannerCenter.x))
	{
		AfxMessageBox(_T("相机 - 振镜中心距过大"));
		return;
	}

	m_fCameraPosX = -ptScannerCenter.x;
	m_fCameraPosY = -ptScannerCenter.y;

	UpdateData(FALSE);

}
