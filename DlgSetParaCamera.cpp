// DlgSetParaCamera.cpp: 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "DlgSetParaCamera.h"
#include "afxdialogex.h"
#include "CDlgDevCfgTabCamera.h"

BOOL g_bCameraSettingChanged = TRUE;

// CDlgSetParaCamera 对话框

IMPLEMENT_DYNAMIC(CDlgSetParaCamera, CDialog)

CDlgSetParaCamera::CDlgSetParaCamera(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SETPARA_CAMERA, pParent)
	, m_fCameraMarkCircleRadius(1)
	, m_fCameraMarkCrossLength(5)
	, m_fCameraMarkCrossWidth(1)
{

}

CDlgSetParaCamera::~CDlgSetParaCamera()
{
}

void CDlgSetParaCamera::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_SLIDER1_CAMERA_BIRGHTNESS, m_cSliderCameraBrightness);
	DDX_Control(pDX, IDC_SLIDER1_CAMERA_CONTRAST, m_cSliderCameraContrast);
	DDX_Control(pDX, IDC_SLIDER1_CAMERA_EXPOSURE, m_cSliderCameraExposure);
	DDX_Control(pDX, IDC_SLIDER1_CAMERA_GAIN, m_cSliderCameraGain);
	DDX_Check(pDX, IDC_CHECK1_CAMERA_REVERSE, m_nCameraReverse);
	DDX_Check(pDX, IDC_CHECK1_CAMERA_MIRROR_X, m_nCameraMirrorX);
	DDX_Check(pDX, IDC_CHECK1_CAMERA_MIRROR_Y, m_nCameraMirrorY);
	DDX_Text(pDX, IDC_EDIT1_CAMERA_MOVE_UNIT, m_fCameraMoveUnit);
	DDX_Text(pDX, IDC_EDIT1_CAMERA_MARK_CIRCLE_RADIUS, m_fCameraMarkCircleRadius);
	DDX_Text(pDX, IDC_EDIT_CAMERA_MARK_CROSS_LENGTH, m_fCameraMarkCrossLength);
	DDX_Text(pDX, IDC_EDIT_CAMERA_MARK_CROSS_WIDTH, m_fCameraMarkCrossWidth);

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSetParaCamera, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CDlgSetParaCamera::OnBnClickedButtonClose)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1_CAMERA_BIRGHTNESS, &CDlgSetParaCamera::OnNMCustomdrawSlider1CameraBirghtness)
	ON_BN_CLICKED(IDC_CHECK1_CAMERA_REVERSE, &CDlgSetParaCamera::OnBnClickedCheck1CameraReverse)
	ON_BN_CLICKED(IDC_CHECK1_CAMERA_MIRROR_X, &CDlgSetParaCamera::OnBnClickedCheck1CameraMirrorX)
	ON_BN_CLICKED(IDC_CHECK1_CAMERA_MIRROR_Y, &CDlgSetParaCamera::OnBnClickedCheck1CameraMirrorY)
	ON_EN_CHANGE(IDC_EDIT1_CAMERA_BRIGHTNESS, &CDlgSetParaCamera::OnEnChangeEdit1CameraBrightness)
	ON_EN_CHANGE(IDC_EDIT1_CAMERA_CONTRAST, &CDlgSetParaCamera::OnEnChangeEdit1CameraContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1_CAMERA_CONTRAST, &CDlgSetParaCamera::OnNMCustomdrawSlider1CameraContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1_CAMERA_EXPOSURE, &CDlgSetParaCamera::OnNMCustomdrawSlider1CameraExposure)
	ON_EN_CHANGE(IDC_EDIT1_CAMERA_EXPOSURE, &CDlgSetParaCamera::OnEnChangeEdit1CameraExposure)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1_CAMERA_GAIN, &CDlgSetParaCamera::OnNMCustomdrawSlider1CameraGain)
	ON_EN_CHANGE(IDC_EDIT1_CAMERA_GAIN, &CDlgSetParaCamera::OnEnChangeEdit1CameraGain)
	ON_EN_CHANGE(IDC_EDIT1_CAMERA_MOVE_UNIT, &CDlgSetParaCamera::OnEnChangeEdit1CameraMoveUnit)
	ON_EN_CHANGE(IDC_EDIT1_CAMERA_MARK_CIRCLE_RADIUS, &CDlgSetParaCamera::OnEnChangeEdit1CameraMarkCircleRadius)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_MARK_CROSS_LENGTH, &CDlgSetParaCamera::OnEnChangeEditCameraMarkCrossLength)
	ON_EN_CHANGE(IDC_EDIT_CAMERA_MARK_CROSS_WIDTH, &CDlgSetParaCamera::OnEnChangeEditCameraMarkCrossWidth)
END_MESSAGE_MAP()


// CDlgSetParaCamera 消息处理程序


void CDlgSetParaCamera::OnBnClickedButtonClose()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


BOOL CDlgSetParaCamera::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	

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
	//步长
	m_fCameraMoveUnit = ReadDevCameraMoveUnit();
	//mark圆半径
	m_fCameraMarkCircleRadius = ReadDevCameraMarkCircleRadius();
	//mark十字叉长宽
	m_fCameraMarkCrossLength = ReadDevCameraMarkCrossLength();
	m_fCameraMarkCrossWidth = ReadDevCameraMarkCrossWidth();

	UpdateData(FALSE);

	 
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgSetParaCamera::OnBnClickedCheck1CameraReverse()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraReverse(m_nCameraReverse);

	g_bCameraSettingChanged = TRUE;
}


void CDlgSetParaCamera::OnBnClickedCheck1CameraMirrorX()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMirrorX(m_nCameraMirrorX);

	g_bCameraSettingChanged = TRUE;

}


void CDlgSetParaCamera::OnBnClickedCheck1CameraMirrorY()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMirrorY(m_nCameraMirrorY);

	g_bCameraSettingChanged = TRUE;

}


void CDlgSetParaCamera::OnNMCustomdrawSlider1CameraBirghtness(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraBrightness.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT1_CAMERA_BRIGHTNESS, strTmp);

	m_nCameraBrightness = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraBrightness(m_nCameraBrightness);
	g_bCameraSettingChanged = TRUE;


	*pResult = 0;
}


void CDlgSetParaCamera::OnEnChangeEdit1CameraBrightness()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT1_CAMERA_BRIGHTNESS);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT1_CAMERA_BRIGHTNESS, NULL, 1);
	m_cSliderCameraBrightness.SetPos(nPosTmp);
	m_nCameraBrightness = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraBrightness(m_nCameraBrightness);
	g_bCameraSettingChanged = TRUE;

}

void CDlgSetParaCamera::OnNMCustomdrawSlider1CameraContrast(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraContrast.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT1_CAMERA_CONTRAST, strTmp);

	m_nCameraContrast = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraContrast(m_nCameraContrast);
	g_bCameraSettingChanged = TRUE;

	*pResult = 0;
}


void CDlgSetParaCamera::OnEnChangeEdit1CameraContrast()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT1_CAMERA_CONTRAST);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT1_CAMERA_CONTRAST, NULL, 1);
	m_cSliderCameraContrast.SetPos(nPosTmp);
	m_nCameraContrast = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraContrast(m_nCameraContrast);
	g_bCameraSettingChanged = TRUE;

}




void CDlgSetParaCamera::OnNMCustomdrawSlider1CameraExposure(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraExposure.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT1_CAMERA_EXPOSURE, strTmp);

	m_nCameraExposure = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraExposure(m_nCameraExposure);
	g_bCameraSettingChanged = TRUE;

	*pResult = 0;
}


void CDlgSetParaCamera::OnEnChangeEdit1CameraExposure()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT1_CAMERA_EXPOSURE);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT1_CAMERA_EXPOSURE, NULL, 1);
	m_cSliderCameraExposure.SetPos(nPosTmp);
	m_nCameraExposure = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraExposure(m_nCameraExposure);
	g_bCameraSettingChanged = TRUE;

}


void CDlgSetParaCamera::OnNMCustomdrawSlider1CameraGain(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPosTmp = m_cSliderCameraGain.GetPos();   //获得滑块的当前位置
	CString strTmp = _T("");
	strTmp.Format(_T("%d"), nPosTmp);
	SetDlgItemText(IDC_EDIT1_CAMERA_GAIN, strTmp);

	m_nCameraGain = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraGain(m_nCameraGain);
	g_bCameraSettingChanged = TRUE;


	*pResult = 0;
}


void CDlgSetParaCamera::OnEnChangeEdit1CameraGain()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CEdit* pEditTmp = (CEdit*)GetDlgItem(IDC_EDIT1_CAMERA_GAIN);
	int nLenth = pEditTmp->GetWindowTextLength();
	pEditTmp->SetSel(nLenth, nLenth, FALSE);
	pEditTmp->SetFocus();

	int nPosTmp = GetDlgItemInt(IDC_EDIT1_CAMERA_GAIN, NULL, 1);
	m_cSliderCameraGain.SetPos(nPosTmp);
	m_nCameraGain = nPosTmp;

	UpdateData(TRUE);
	SetDevCameraGain(m_nCameraGain);
	g_bCameraSettingChanged = TRUE;

}


void CDlgSetParaCamera::OnEnChangeEdit1CameraMoveUnit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	SetDevCameraMoveUnit(m_fCameraMoveUnit);
}


void CDlgSetParaCamera::OnEnChangeEdit1CameraMarkCircleRadius()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCircleRadius(m_fCameraMarkCircleRadius);

}


void CDlgSetParaCamera::OnEnChangeEditCameraMarkCrossLength()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCrossLength(m_fCameraMarkCrossLength);

}


void CDlgSetParaCamera::OnEnChangeEditCameraMarkCrossWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetDevCameraMarkCrossWidth(m_fCameraMarkCrossWidth);
}
