#pragma once

extern BOOL g_bCameraSettingChanged;

// CDlgSetParaCamera 对话框

class CDlgSetParaCamera : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetParaCamera)

public:
	CDlgSetParaCamera(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgSetParaCamera();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETPARA_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedCheck1CameraReverse();
	afx_msg void OnBnClickedCheck1CameraMirrorX();
	afx_msg void OnBnClickedCheck1CameraMirrorY();
	afx_msg void OnNMCustomdrawSlider1CameraBirghtness(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1CameraBrightness();
	afx_msg void OnNMCustomdrawSlider1CameraContrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1CameraContrast();
	afx_msg void OnNMCustomdrawSlider1CameraExposure(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1CameraExposure();
	afx_msg void OnNMCustomdrawSlider1CameraGain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEdit1CameraGain();

	//CmaeraView指针

	//反转//镜像
	int m_nCameraReverse, m_nCameraMirrorX, m_nCameraMirrorY;
	//亮度
	int m_nCameraBrightness;
	CSliderCtrl m_cSliderCameraBrightness;
	const int m_cnSliderSliderCameraBrightnessMin = -255;      /* Slider min position                                   */
	const int m_cnSliderSliderCameraBrightnessMax = 255;    /* Slider max position                                   */
	//对比度
	int m_nCameraContrast;
	CSliderCtrl m_cSliderCameraContrast;
	const int m_cnSliderSliderCameraContrastMin = 0;      /* Slider min position                                   */
	const int m_cnSliderSliderCameraContrastMax = 255;    /* Slider max position                                   */
	//曝光
	int m_nCameraExposure;
	CSliderCtrl m_cSliderCameraExposure;
	const int m_cnSliderSliderCameraExposureMin = 36;      /* Slider min position                                   */
	const int m_cnSliderSliderCameraExposureMax = 50000;    /* Slider max position                                   */
	//增益
	int m_nCameraGain;
	CSliderCtrl m_cSliderCameraGain;
	const int m_cnSliderSliderCameraGainMin = 0;      /* Slider min position                                   */
	const int m_cnSliderSliderCameraGainMax = 17;    /* Slider max position                                   */
	//移动步长
	double m_fCameraMoveUnit;
	//Mark圆半径
protected:
	double m_fCameraMarkCircleRadius;
	double m_fCameraMarkCrossLength;
	double m_fCameraMarkCrossWidth;

	afx_msg void OnEnChangeEdit1CameraMoveUnit();
	afx_msg void OnEnChangeEdit1CameraMarkCircleRadius();
public:
	afx_msg void OnEnChangeEditCameraMarkCrossLength();
	afx_msg void OnEnChangeEditCameraMarkCrossWidth();
};
