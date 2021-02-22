//#if !defined(AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_)
//#define AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_
//
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CHalconWnd window
#include "DeviceCamera.h"
#include<HalconCpp.h>
#include<HALCONCpp/HDevThread.h>
#include "PointF.h"
#include <vector>
#include "HalconModel.h"
using namespace HalconCpp;



////////////////////////////////////////////////////////////////
//multiThread
#define MAX_BUFFERS 3

struct ResultContainer
{
	//HalconCpp::HImage   result_img;
	//HalconCpp::HXLDCont symbol_data;
	//HalconCpp::HTuple   time_needed;
	//HalconCpp::HTuple   result_handle;
	//HalconCpp::HTuple   find_data;
	
	HalconCpp::HImage   imgCameraImage;

	//HalconCpp::HImage	imgROI;
	//HalconCpp::HTuple	hvModelID;
	//HalconCpp::HImage	imgModelImage;
	//HalconCpp::HRegion	rgnModelRegion;
	//HalconCpp::HTuple	hvModelIDMatch;
	//HalconCpp::HXLD		xldModelContour;
	//HalconCpp::HXLD		xldContoursAffineTrans;
	//HalconCpp::HTuple	hvContoursAffineTransRow;
	//HalconCpp::HTuple	hvContoursAffineTransColumn;
	//HalconCpp::HTuple	hvContoursAffineTransAngle;

	HalconCpp::HXLD		xldContourCircleHand;
	HalconCpp::HTuple	hvParameterCircleHand;

	HalconCpp::HXLD		xldContourCircles;
	HalconCpp::HTuple	hvParameterCircles;
};
//multiThread
////////////////////////////////////////////////////////////////

class CHalconWnd : public CWnd
{
// Construction
public:
	CHalconWnd();
	virtual ~CHalconWnd();

// Operations
	void AttachWnd(CWnd* pWnd);
	void   DetachWnd();
	CWnd* m_attachWnd;

////////////////////////////////////////////////////////////////
//Scroll
public:
	// Set/get the virtual display size. When the dialog or window
	// size is smaller than the display size, then that is when
	// scrollbars will appear. Set either the display width or display
	// height to zero if you don't want to enable the scrollbar in the
	// corresponding direction.
	void   SetDisplaySize(int displayWidth, int displayHeight);
	const CSize& GetDisplaySize() const;

	// Get current scroll position. This is needed if you are scrolling
	// a custom CWnd which implements its own drawing in OnPaint().
	const CSize& GetScrollPos() const;

	// Get current page size. Useful for debugging purposes.
	const CSize& GetPageSize() const;

	// Scroll back to top, left, or top-left corner of the window.
	void   ScrollToOrigin(bool scrollLeft, bool scrollTop);

	// Message handling.
	BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void  OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void  OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void OnSize(UINT nType, int cx, int cy);

protected:
	int    Get32BitScrollPos(int bar, CScrollBar* pScrollBar);
	void   UpdateScrollInfo();
	void   UpdateScrollBar(int bar, int windowSize, int displaySize,
		LONG& pageSize, LONG& scrollPos, LONG& deltaPos);

	CSize  m_pageSize;
	CSize  m_displaySize;
	CSize  m_scrollPos;
//Scroll
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//Image
public:
	BOOL LoadImageFromHObject(HObject ho_Img);												//从本地地址读图
	BOOL LoadImageFromLocal(LPCSTR szImagePath);												//从本地地址读图
	BOOL LoadImageFromBitmap(HTuple hv_ImageWidth, HTuple hv_ImageHeight, BYTE* pImageBuffer);		//bitmap转HObject
	BOOL DisImage(HObject ho_Img);

protected:
	HObject m_hoImage;				//读图->m_hoImage
//Image
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//Zoom
public:
	BOOL Zoom(double dbFactor);
protected:
	BOOL ZoomIn();
	BOOL ZoomOut();
	double GetZoomFactor();
	BOOL SetWindowHalcon(HTuple nPosX, HTuple nPosY, HTuple nWidth, HTuple nHeight);

	HTuple m_nZoomWidth;
	HTuple m_nZoomHeight;
	BOOL m_bZoom;
	double m_dbZoomFactor;
//Zoom
////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
//Draw
public:
	enum DRAW_MODE
	{
		DRAW_RECTANGLE1,
		DRAW_RECTANGLE2,
		DRAW_CIRCLE,
		DRAW_ELLIPSE,
		DRAW_POLYGON,
		DRAW_REGION,
	};

	BOOL DrawRectangle1();
	HTuple drawRectRow1, drawRectColumn1, drawRectRow2, drawRectColumn2;

	BOOL DrawRectangle2();
	BOOL DrawCircle();
	BOOL DrawEllipse();
	BOOL DrawPolygon();
	BOOL DrawRegion();
	BOOL DrawArea(UINT nMode);
	BOOL IsDrawingArea();

	BOOL m_bDrawingArea;
//Draw
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//DeviceCamera Hardware
protected:
	CDeviceCamera* m_pDevCam;
	//BOOL m_bDevCamIsOpened;
//DeviceCamera Hardware
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//multiThread
public:
	//*********************图像处理*************************//
	//图像预处理，用于相机设置
	void ReverseImgColor(HObject imgInput, HObject* imgReversed);
	void SetImgBrightness(HObject imgInput, HObject* imgBrighted, int nImgBrightness);
	void SetImgContrast(HObject imgInput, HObject* imgContrasted, int nImgContrast);
	int m_nImgMirrorX, m_nImgMirrorY, m_nImgExposure, m_nImgGain;	//采集图像参数
	int m_nImgReverse, m_nImgBrightness, m_nImgContrast;			//图像预处理参数

	BOOL IsXldEmpty(HObject* hoXld);

	//手动抓圆
	void TestFindCircleHand();
	void ThreadFuncTestFindCircleHand(HObject imgCameraImage, HObject* xldCircle, HTuple* hvParameterCircle);
	void DispTestFindCircleHand(HObject xldContourCircle, HTuple hvParameterCircle);
	HTuple m_hvDrawCircleRow, m_hvDrawCircleColumn, m_hvDrawCircleRadius;
	BOOL m_bTestFindCircleHand, m_bCameraMoveHand;

	//自动抓圆
	BOOL AutoFindCircle(std::vector<CPointF>* vPtPos);
	void WaitForFindDone();
	HANDLE  hdFindDone;
	void TestFindCircles();
	void ThreadFuncTestFindCircles(HObject imgCameraImage, HObject* xldContourCircles, HTuple* hvParameterCircles);
	void DispTestFindCircles(HObject xldContourCircles, HTuple hvParameterCircles);
	BOOL m_bTestFindCircles, m_bCameraMove;
	HTuple	m_hvScaleMin, m_hvScaleMax, m_hvMinScore;

	void SetPosFindCircles(BOOL bFlagFinded, HTuple hvPosX, HTuple hvPosY);
	BOOL GetPosFindCircles(std::vector<CPointF>* vPtPos);
	BOOL m_bFlagFinded;
	HTuple m_hvFindedPosX, m_hvFindedPosY;

	//自动抓模板

	//自定义模板匹配
	//BOOL m_bTestCreateModel, m_bTestMatchModel;
	//void TestCreateModel();
	//void ThreadFuncTestCreateModel(HObject imgCameraImage, HObject *imgROI, HTuple* hvModelID, HObject* imgModelImage, HObject* rgnModelRegion);
	//void TestMatchModel();
	//void ThreadFuncTestMatchModel(HObject imgCameraImage, HTuple* hvModelIDMatch, HObject* xldModelContour, HObject* xldContoursAffineTrans,
	//	HTuple* hvContoursAffineTransRow, HTuple* hvContoursAffineTransColumn, HTuple* hvContoursAffineTransAngle);

	//HObject m_hoImageSelected;		//框选的图像
	//HObject m_hoImageROI;			//截取的图像ROI

	//HTuple m_hoShapeModelID;		//模板ID
	//HObject m_hoShapeModelImage;	//模板图像
	//HObject m_hoShapeModelRegion;	//模板区域
	//HObject m_hoShapeModelContour;	//模板轮廓
	//HObject m_hoDomainModelRegion;	//读取m_hoImageSelected框选的区域
	//*********************图像处理*************************//

//打开相机实时采集基本功能
protected:
	HTuple m_nImageWidth, m_nImageHeight;

	// shared data 
	struct    ResultContainer resultData;
	//std::list<HalconCpp::HObject>    imgList;
	CList<HalconCpp::HObject>    imgList;

	// event handles to synchronize threads
	HANDLE  fgStopEvent;
	HANDLE  newImageEvent;
	HANDLE  newResultEvent;
	HANDLE  containerIsFreeEvent;

	// mutexes to guarantee mutual access to shared objects
	CRITICAL_SECTION    newImageMutex;
	CRITICAL_SECTION    resultDataMutex;

public:
	HTuple	m_hWindow;
	BOOL	m_bThreadsAreRunning;
	void OnOpenCamera();
	void OnCloseCamera();
	void StartThreads();
	void StopThread(CWinThread* pThred);
	//void InitialGrabOfImage();
	void InitHalconWnd(HTuple x, HTuple y, HTuple w, HTuple h);

	//ThreadFunc
	static UINT ImgAcqRun(LPVOID lpParam);
	static UINT ImgProcRun(LPVOID lpParam);

private:
	CWinThread* m_pThImgProc;				//线程指针
	DWORD m_dwThImgProc;					//线程ID
	CWinThread* m_pThImgAcq;				//线程指针
	DWORD m_dwThImgAcq;						//线程ID

//multiThread
////////////////////////////////////////////////////////////////


///////////////////////////////与外界交互读图,定位，显示////////////////////////////
protected:
	HImage m_hoImageDisplay;
	HObject m_hoContourMask;
	BOOL m_bShowString;
	HTuple m_hvString;
	HTuple m_hvStringRow;
	HTuple m_hvStringColumn;

public:
	HImage GetImageDisplay();
	BOOL ClearContourMask();
	BOOL SetContourMask(HObject hoContour);
	BOOL ClearStringMask();
	BOOL SetStringMask(HTuple hvString, HTuple hvRow, HTuple hvColumn);
	int LocateModel(HalconModel modelHalcon, std::vector<CPointF>* vPtPos, BOOL bShowModelCotour = TRUE, BOOL bShowModelString = TRUE);
///////////////////////////////与外界交互读图,定位，显示////////////////////////////


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHalconWnd)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	afx_msg LRESULT OnDisp(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_HALCONWND_H__41CAF5F2_2DB6_4426_9C62_70B0229EEA12__INCLUDED_)
