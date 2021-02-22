#pragma once


////////////////////////////////////////////////////////////////////
//相机硬件配置 外部调用
#define MAX_DOUBLE_PRECISION 10

enum class CAMERA_NAME
{
	CAMERA_NONE				= -1,
	CAMERA_GENERAL_GE		= 0,
	CAMERA_DAHENG_MER		= 1,
	CAMERA_2				= 2
};
extern void SetDevCameraName(CAMERA_NAME eCameraName);
extern CAMERA_NAME ReadDevCameraName();
extern void SetDevCameraReverse(int nCameraReverse);
extern int ReadDevCameraReverse();
extern void SetDevCameraMirrorX(int nCameraMirrorX);
extern int ReadDevCameraMirrorX();
extern void SetDevCameraMirrorY(int nCameraMirrorY);
extern int ReadDevCameraMirrorY();
extern void SetDevCameraBrightness(int nCameraBrightness);
extern int ReadDevCameraBrightness();
extern void SetDevCameraContrast(int nCameraContrast);
extern int ReadDevCameraContrast();
extern void SetDevCameraExposure(int nCameraExposure);
extern int ReadDevCameraExposure();
extern void SetDevCameraGain(int nCameraGain);
extern int ReadDevCameraGain();
extern void SetDevCameraMoveUnit(double fCameraMoveUnit);
extern double ReadDevCameraMoveUnit();
extern void SetDevCameraPosX(double fCameraPos);
extern double ReadDevCameraPosX();
extern void SetDevCameraPosY(double fCameraPos);
extern double ReadDevCameraPosY();
extern void SetDevCameraPixelSize(double fCameraPixelSize);
extern double ReadDevCameraPixelSize();
extern void SetDevCameraMarkCircleRadius(double fCameraMarkCircleRadius);
extern double ReadDevCameraMarkCircleRadius();
extern void SetDevCameraMarkCircleFindScaleMin(double fCameraMarkCircleFindScaleMin);
extern double ReadDevCameraMarkCircleFindScaleMin();
extern void SetDevCameraMarkCircleFindScaleMax(double fCameraMarkCircleFindScaleMax);
extern double ReadDevCameraMarkCircleFindScaleMax();
extern void SetDevCameraMarkCircleFindMinScore(double fCameraMarkCircleMinScore);
extern double ReadDevCameraMarkCircleFindMinScore();

//相机硬件配置 外部调用
////////////////////////////////////////////////////////////////////

// CDlgDevCfgTabCamera 对话框
class CDlgDevCfgTabCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDevCfgTabCamera)

public:
	CDlgDevCfgTabCamera(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgDevCfgTabCamera();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEVICE_CONFIG_TAB_CAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCameraApply();


	int m_nIndexRadioCamera;		//选择不同相机设备的标识（0/1/2对应不同的radio按钮）
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
	const int m_cnSliderSliderCameraExposureMax = 1000000;    /* Slider max position                                   */
	//增益
	int m_nCameraGain;
	CSliderCtrl m_cSliderCameraGain;
	const int m_cnSliderSliderCameraGainMin = 0;      /* Slider min position                                   */
	const int m_cnSliderSliderCameraGainMax = 17;    /* Slider max position                                   */
	//相机中心到振镜中心坐标
	double m_fCameraPosX, m_fCameraPosY;
	//像素尺寸
	double m_fCameraPixelSize;

	virtual BOOL OnInitDialog();

public:
	afx_msg void OnNMCustomdrawSliderCameraBirghtness(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditCameraBrightness();
	afx_msg void OnNMCustomdrawSliderCameraContrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditCameraContrast();
	afx_msg void OnNMCustomdrawSliderCameraExposure(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditCameraExposure();
	afx_msg void OnNMCustomdrawSliderCameraGain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeEditCameraGain();
};
