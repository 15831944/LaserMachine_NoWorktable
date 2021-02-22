// DlgCameraPositionSetRealMarkPoint.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "DlgCameraPositionSetRealMarkPoint.h"
#include "afxdialogex.h"
#include "HalconWndDlg.h"
#include "CDlgDevCfgTabCamera.h"
#include "CameraPosition.h"
#include "DeviceCardWorktable.h"
#include "CameraView.h"
#include "MainFrm.h"



// CDlgCameraPositionSetRealMarkPoint 对话框

IMPLEMENT_DYNAMIC(CDlgCameraPositionSetRealMarkPoint, CDialogEx)

CDlgCameraPositionSetRealMarkPoint::CDlgCameraPositionSetRealMarkPoint(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAMERA_POSITION_SET_REAL_MARK_POINT, pParent)
	, m_nCBIndexModelType(0)
	, m_fModelCircleRadius(0.5)
	, m_fModelParamScaleMin(0.95)
	, m_fModelParamScaleMax(1.05)
	, m_fModelParamMinScore(0.7)
	, m_fModelCrossLength(1)
	, m_fModelCrossWidth(0.2)
	, m_fModelRectWidth(0.5)
	, m_fModelRectHeight(0.5)
{
	m_ptPosMatched = CPointF();
}

CDlgCameraPositionSetRealMarkPoint::~CDlgCameraPositionSetRealMarkPoint()
{
}

void CDlgCameraPositionSetRealMarkPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_POSITION_MODEL_TYPE, m_nCBIndexModelType);
	DDV_MinMaxInt(pDX, m_nCBIndexModelType, 0, 2);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_CIRCLE_RADIUS, m_fModelCircleRadius);
	DDV_MinMaxDouble(pDX, m_fModelCircleRadius, 0, 10);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_PARAM_SCALE_MIN, m_fModelParamScaleMin);
	DDV_MinMaxDouble(pDX, m_fModelParamScaleMin, 0.5, 1);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_PARAM_SCALE_MAX, m_fModelParamScaleMax);
	DDV_MinMaxDouble(pDX, m_fModelParamScaleMax, 1, 1.5);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_PARAM_MIN_SCORE, m_fModelParamMinScore);
	DDV_MinMaxDouble(pDX, m_fModelParamMinScore, 0, 1);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_CROSS_LENGTH, m_fModelCrossLength);
	DDV_MinMaxDouble(pDX, m_fModelCrossLength, 0, 10);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_CROSS_WIDTH, m_fModelCrossWidth);
	DDV_MinMaxDouble(pDX, m_fModelCrossWidth, 0, 10);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_RECT_WIDTH, m_fModelRectWidth);
	DDV_MinMaxDouble(pDX, m_fModelRectWidth, 0, 10);
	DDX_Text(pDX, IDC_EDIT_POSITION_MODEL_RECT_HEIGHT, m_fModelRectHeight);
	DDV_MinMaxDouble(pDX, m_fModelRectHeight, 0, 10);
}


BEGIN_MESSAGE_MAP(CDlgCameraPositionSetRealMarkPoint, CDialogEx)
	ON_WM_MOUSEWHEEL()
	ON_BN_CLICKED(IDC_BUTTON_POSITION_MODEL_NEW, &CDlgCameraPositionSetRealMarkPoint::OnBnClickedButtonPositionModelNew)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_MODEL_MATCH, &CDlgCameraPositionSetRealMarkPoint::OnBnClickedButtonPositionModelMatch)
	ON_CBN_SELCHANGE(IDC_COMBO_POSITION_MODEL_TYPE, &CDlgCameraPositionSetRealMarkPoint::OnCbnSelchangeComboPositionModelType)
	ON_BN_CLICKED(IDOK, &CDlgCameraPositionSetRealMarkPoint::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgCameraPositionSetRealMarkPoint::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_FIND_TEST_DXF, &CDlgCameraPositionSetRealMarkPoint::OnBnClickedButtonFindTestDxf)
END_MESSAGE_MAP()



BOOL CDlgCameraPositionSetRealMarkPoint::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCameraView* pCameraView = (CCameraView*)
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->m_wndSplitter1.GetPane(1, 0);
	if (NULL == pCameraView || FALSE == pCameraView->m_pHalconWnd->m_bThreadsAreRunning)
	{
		AfxMessageBox(_T("请先打开相机"));
		return FALSE;
	}

	//halcon窗口
	CRect rect;
	GetDlgItem(IDC_STATIC_HALCON_DLG)->GetWindowRect(&rect);
	ScreenToClient(&rect); 

	if (!m_wndHalconDlg.Create(NULL, _T("HALWINDOW"), WS_TABSTOP | WS_CHILD | WS_VISIBLE, rect, this, NULL))
	{
		AfxMessageBox(_T("FAILED TO CREATE IMAGE WINDOW"));
		return TRUE;
	}
	::MoveWindow(m_wndHalconDlg.m_hWnd, rect.left, rect.top, rect.Width(), rect.Height(), TRUE);

	//读相机图像
	m_wndHalconDlg.InitHalcon(rect.left, rect.top, rect.Width(), rect.Height());
	m_wndHalconDlg.LoadImageFromCamera(pCameraView->m_pHalconWnd->GetImageDisplay());


	//界面初始化
	//初始化校正圆combo控件
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION_MODEL_TYPE))->InsertString(0, (_T("圆")));
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION_MODEL_TYPE))->InsertString(1, (_T("十字叉")));
	((CComboBox*)GetDlgItem(IDC_COMBO_POSITION_MODEL_TYPE))->InsertString(2, (_T("矩形轮廓")));
	//初始化模板参数界面
	GetDlgItem(IDC_STATIC_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_HIDE);


	UpdateData(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CDlgCameraPositionSetRealMarkPoint::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_wndHalconDlg.OnMouseWheel(nFlags, zDelta, pt))
	{
		this->Invalidate();
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDlgCameraPositionSetRealMarkPoint::OnBnClickedButtonPositionModelNew()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	switch (m_nCBIndexModelType)
	{
	case 0:
		//新建圆
		NewModelCircle();
		break;
	case 1:
		//新建十字叉
		NewModelCross();
		break;
	case 2:
		//新建矩形轮廓
		NewModelRectOutline();
		break;
	default:
		break;
	}

	UpdateData(FALSE);

}


BOOL CDlgCameraPositionSetRealMarkPoint::NewModelCircle()
{
	double fPixelSize, fRadiusPixelIn, fRadiusPixelOut;

	fPixelSize = ReadDevCameraPixelSize();
	fRadiusPixelIn = m_fModelCircleRadius / fPixelSize;
	m_wndHalconDlg.NewModelCircleHalcon(fRadiusPixelIn, &fRadiusPixelOut);
	m_fModelCircleRadius = fRadiusPixelOut * fPixelSize;

	return TRUE;
}
BOOL CDlgCameraPositionSetRealMarkPoint::NewModelCross()
{
	double fPixelSize, fCrossLengthPixelIn, fCrossWidthPixelIn, fCrossLengthPixelOut, fCrossWidthPixelOut;

	fPixelSize = ReadDevCameraPixelSize();
	fCrossLengthPixelIn = m_fModelCrossLength / fPixelSize;
	fCrossWidthPixelIn = m_fModelCrossWidth / fPixelSize;
	m_wndHalconDlg.NewModelCrossHalcon(fCrossLengthPixelIn, fCrossWidthPixelIn, &fCrossLengthPixelOut, &fCrossWidthPixelOut);
	m_fModelCrossLength = fCrossLengthPixelOut * fPixelSize;
	m_fModelCrossWidth = fCrossWidthPixelOut * fPixelSize;

	return TRUE;
}
BOOL CDlgCameraPositionSetRealMarkPoint::NewModelRectOutline()
{
	double fPixelSize, fRectWidthPixelIn, fRectHeightPixelIn, fRectWidthPixelOut, fRectHeightPixelOut;

	fPixelSize = ReadDevCameraPixelSize();
	fRectWidthPixelIn = m_fModelRectWidth / fPixelSize;
	fRectHeightPixelIn = m_fModelRectHeight / fPixelSize;
	m_wndHalconDlg.NewModelRectOutlineHalcon(fRectWidthPixelIn, fRectHeightPixelIn, &fRectWidthPixelOut, &fRectHeightPixelOut);
	m_fModelRectWidth = fRectWidthPixelOut * fPixelSize;
	m_fModelRectHeight = fRectHeightPixelOut * fPixelSize;

	return TRUE;
}


void CDlgCameraPositionSetRealMarkPoint::OnBnClickedButtonPositionModelMatch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int nCtMatched;
	double fPosX, fPosY, fPixelSize;

	fPixelSize = ReadDevCameraPixelSize();
	nCtMatched = m_wndHalconDlg.MatchModelHalcon(m_fModelParamScaleMin, m_fModelParamScaleMax, m_fModelParamMinScore, &fPosX, &fPosY, fPixelSize);

	switch (nCtMatched)
	{
	case 0:
		m_ptPosMatched = CPointF(0, 0);
		AfxMessageBox(_T("没有找到模板"));
		break;
	case 1:
		m_ptPosMatched = CPointF((FLOAT)fPosX, (FLOAT)fPosY);
		break;
	default:
		m_ptPosMatched = CPointF(0, 0);
		AfxMessageBox(_T("找到多个模板"));
		break;
	}
	
	return;
}

CPointF CDlgCameraPositionSetRealMarkPoint::GetMatchedPtPos()
{
	if (NULL == pDevCardWorktable)
		return CPointF();

	double fPosSavedX, fPosSavedY;
	pDevCardWorktable->GetAbsPosXY(&fPosSavedX, &fPosSavedY);
	m_ptPosMatched.x += (FLOAT)fPosSavedX;
	m_ptPosMatched.y += (FLOAT)fPosSavedY;

	return m_ptPosMatched;
}

HalconModel CDlgCameraPositionSetRealMarkPoint::GetMatchedModel()
{
	return m_wndHalconDlg.m_modelMarkPoint;
}


//BOOL CDlgCameraPositionSetRealMarkPoint::MatchModelCircle()
//{
//	return TRUE;
//}
//BOOL CDlgCameraPositionSetRealMarkPoint::MatchModelCross()
//{
//	return TRUE;
//}
//BOOL CDlgCameraPositionSetRealMarkPoint::MatchModelRectOutline()
//{
//	return TRUE;
//}




void CDlgCameraPositionSetRealMarkPoint::OnCbnSelchangeComboPositionModelType()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	switch (m_nCBIndexModelType)
	{
	case 0:
		GetDlgItem(IDC_STATIC_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_HIDE);

		break;
	case 1:
		GetDlgItem(IDC_STATIC_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_HIDE);

		break;
	case 2:
		GetDlgItem(IDC_STATIC_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CIRCLE_RADIUS)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_WIDTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_CROSS_LENGTH)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_WIDTH)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_POSITION_MODEL_RECT_HEIGHT)->ShowWindow(SW_SHOW);

		break;
	default:
		break;
	}
}


void CDlgCameraPositionSetRealMarkPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDlgCameraPositionSetRealMarkPoint::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDlgCameraPositionSetRealMarkPoint::OnBnClickedButtonFindTestDxf()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	std::vector<double> vecDouble;
	double fPixlSize = ReadDevCameraPixelSize();

	  // Local iconic variables
	HObject  ho_Contours, ho_Image1, ho_ContoursTrans;
	HObject  ho_Image, ho_Domain, ho_ModelImages, ho_ModelRegions;
	HObject  ho_ConnectedRegions, ho_SelectedRegions, ho_ModelContours;
	HObject  ho_ModelCont, ho_ModelTrans;

	// Local control variables
	HTuple  hv_WindowHandle, hv_DxfStatus, hv_HomMat2DIdentity1;
	HTuple  hv_HomMat2DScale1, hv_Area, hv_Row, hv_Column, hv_ModelID;
	HTuple  hv_Angle, hv_Scale, hv_Score, hv_Model, hv_Length;
	HTuple  hv_I, hv_HomMat2D;
	HTuple  hv_Width, hv_Height;
	HTuple  hv_NumLevels, hv_AreaModelRegions, hv_RowModelRegions, hv_ColumnModelRegions, hv_HeightPyramid;

	try
	{
		//dev_open_file_dialog ('read_contour_xld_dxf', 'default', 'default', Selection)
		//ReadContourXldDxf(&ho_Contours, "D:/YuanLu/5. dxf/qiege.dxf", HTuple(), HTuple(), &hv_DxfStatus);
		ReadContourXldDxf(&ho_Contours, _T("./qiege.dxf"), HTuple(), HTuple(), &hv_DxfStatus);
		ho_Image1 = m_wndHalconDlg.m_hoImage;
		GetImageSize(ho_Image1, &hv_Width, &hv_Height);

		//HomMat2dIdentity(&hv_HomMat2DIdentity1);
		//HomMat2dScale(hv_HomMat2DIdentity1, 1 / fPixlSize, 1 / fPixlSize, 0, 0, &hv_HomMat2DScale1);
		////HomMat2dScale(hv_HomMat2DIdentity1, 46, 46, 0, 0, &hv_HomMat2DScale1);
		//AffineTransContourXld(ho_Contours, &ho_ContoursTrans, hv_HomMat2DScale1);
		////if (HDevWindowStack::IsOpen())
		////	DispObj(ho_ContoursTrans, HDevWindowStack::GetActive());
		////DispObj(ho_ContoursTrans, m_wndHalconDlg.m_hWindow);

		gen_model_image_of_bright_object_with_holes_COPY_1(ho_Contours, &ho_Image, 1/ fPixlSize, hv_Width, hv_Height);
		//DispObj(ho_Image, m_wndHalconDlg.m_hWindow);
		//dev_set_color ('green')
		//set_tposition (WindowHandle, 20, 20)
		//write_string (WindowHandle, 'Generating shape model ' + J$'d')
		GetDomain(ho_Image, &ho_Domain);
		AreaCenter(ho_Domain, &hv_Area, &hv_Row, &hv_Column);
		InspectShapeModel(ho_Image, &ho_ModelImages, &ho_ModelRegions, 10, 50);
		AreaCenter(ho_ModelRegions, &hv_AreaModelRegions, &hv_RowModelRegions, &hv_ColumnModelRegions);
		CountObj(ho_ModelRegions, &hv_HeightPyramid);
		//确定金字塔的层级
		for (HTuple hv_i = 1; hv_i.Continue(hv_HeightPyramid, 1); hv_i += 1)
		{
			if (TRUE == (HTuple(hv_AreaModelRegions[hv_i - 1]) >= 15))
			{
				hv_NumLevels = hv_i;
			}
		}

		//Since the shape models contain a few extraneous edges,
		//they will be removed here to give a slightly nicer
		//visualization.
		//Connection(ho_ModelRegions, &ho_ConnectedRegions);
		//SelectShape(ho_ConnectedRegions, &ho_SelectedRegions, "area", "and", 20, 100000);
		//Union1(ho_SelectedRegions, &ho_ModelRegions);
		//GenContoursSkeletonXld(ho_ModelRegions, &ho_ModelContours, 1, "filter");
		//if (HDevWindowStack::IsOpen())
		//	SetColor(HDevWindowStack::GetActive(), "red");
		//if (HDevWindowStack::IsOpen())
		//	DispObj(ho_ModelContours, HDevWindowStack::GetActive());

		CreateScaledShapeModel(ho_Image, hv_NumLevels, HTuple(0).TupleRad(), HTuple(360).TupleRad(),
			"auto", 0.95, 1.05, "auto", "none", "ignore_global_polarity", 50, 10, &hv_ModelID);
		//CreateScaledShapeModelXld(ho_ModelContours, "auto", HTuple(0).TupleRad(), HTuple(360).TupleRad(), 
		//	"auto", 0.9, 1.1, "auto", "auto", "ignore_local_polarity", 5, &hv_ModelID);
		GetShapeModelContours(&ho_ModelCont, hv_ModelID, 1);
		SelectShapeXld(ho_ModelCont, &ho_ModelContours, "contlength", "and", 20, 99999);
		FindScaledShapeModels(ho_Image1, hv_ModelID, HTuple(0).TupleRad(), HTuple(360).TupleRad(),
			0.95, 1.05, m_fModelParamMinScore, 0, 0.5, "least_squares", hv_NumLevels, 0, &hv_Row, &hv_Column, &hv_Angle,
			&hv_Scale, &hv_Score, &hv_Model);

		TupleLength(hv_Row, &hv_Length);
		{
			for (hv_I = 0; hv_I.Continue(hv_Length - 1, 1); hv_I += 1)
			{

				VectorAngleToRigid(0, 0, 0, HTuple(hv_Row[hv_I]), HTuple(hv_Column[hv_I]), HTuple(hv_Angle[hv_I]),
					&hv_HomMat2D);
				AffineTransContourXld(ho_ModelContours, &ho_ModelTrans, hv_HomMat2D);
				DispObj(ho_ModelTrans, m_wndHalconDlg.m_hWindow);

				vecDouble.push_back((hv_Column[hv_I] - (hv_Width / 2)).D() * fPixlSize);
				vecDouble.push_back(-(hv_Row[hv_I] - (hv_Height / 2)).D() * fPixlSize);
				vecDouble.push_back(hv_Angle[hv_I].D());
				g_vecTestDXF.push_back(vecDouble);
				vecDouble.clear();
			}
		}
	}
	catch (HException& exception)
	{
		AfxMessageBox((HString)exception.ErrorMessage());
		if ((int)exception.ErrorCode() < 0)
			throw exception;
	}

}



// Short Description: Create an image of bright object with holes from XLD contours 
void CDlgCameraPositionSetRealMarkPoint::gen_model_image_of_bright_object_with_holes_COPY_1(HObject ho_Contours, HObject* ho_ModelImage,
	HTuple hv_Scale, HTuple hv_Width, HTuple hv_Height)
{

	// Local iconic variables
	HObject  ho_EmptyObject, ho_ContoursClassified;
	HObject  ho_Boundaries, ho_Holes, ho_ObjectSelected, ho_BoundariesScaled;
	HObject  ho_BoundariesCenteredAndScaled, ho_HolesCenteredAndScaled;
	HObject  ho_Region, ho_RegionDilation;

	// Local control variables
	HTuple  hv_Number, hv_i, hv_IsHole, hv_HomMat2DIdentity;
	HTuple  hv_HomMat2DScale, hv_Area, hv_RowScaled, hv_ColScaled;
	HTuple  hv_PointOrder, hv_HomMat2D, hv_NumberBoundaries;
	HTuple  hv_NumberHoles;

	UnionAdjacentContoursXld(ho_Contours, &ho_Contours, 1, 1, "attr_keep");

	//We can use the set operations for closed contours
	//to classify the contours into outer boundaries and holes
	GenEmptyObj(&ho_EmptyObject);
	DifferenceClosedContoursXld(ho_Contours, ho_EmptyObject, &ho_ContoursClassified);
	GenEmptyObj(&ho_Boundaries);
	GenEmptyObj(&ho_Holes);
	CountObj(ho_ContoursClassified, &hv_Number);
	{
		HTuple end_val9 = hv_Number;
		HTuple step_val9 = 1;
		for (hv_i = 1; hv_i.Continue(end_val9, step_val9); hv_i += step_val9)
		{
			SelectObj(ho_ContoursClassified, &ho_ObjectSelected, hv_i);
			GetContourGlobalAttribXld(ho_ObjectSelected, "is_hole", &hv_IsHole);
			if (0 != (hv_IsHole == 1))
			{
				ConcatObj(ho_Holes, ho_ObjectSelected, &ho_Holes);
			}
			else
			{
				ConcatObj(ho_Boundaries, ho_ObjectSelected, &ho_Boundaries);
			}
		}
	}

	HomMat2dIdentity(&hv_HomMat2DIdentity);
	HomMat2dScale(hv_HomMat2DIdentity, hv_Scale, hv_Scale, 0, 0, &hv_HomMat2DScale);

	AffineTransContourXld(ho_Boundaries, &ho_BoundariesScaled, hv_HomMat2DScale);
	AreaCenterXld(ho_BoundariesScaled, &hv_Area, &hv_RowScaled, &hv_ColScaled, &hv_PointOrder);
	HomMat2dTranslate(hv_HomMat2DScale, (hv_Height / 2) - (hv_RowScaled.TupleMean()), (hv_Width / 2) - (hv_ColScaled.TupleMean()),
		&hv_HomMat2D);
	AffineTransContourXld(ho_Boundaries, &ho_BoundariesCenteredAndScaled, hv_HomMat2D);
	AffineTransContourXld(ho_Holes, &ho_HolesCenteredAndScaled, hv_HomMat2D);

	GenImageConst(&(*ho_ModelImage), "byte", hv_Width, hv_Height);
	CountObj(ho_BoundariesCenteredAndScaled, &hv_NumberBoundaries);
	{
		HTuple end_val30 = hv_NumberBoundaries;
		HTuple step_val30 = 1;
		for (hv_i = 1; hv_i.Continue(end_val30, step_val30); hv_i += step_val30)
		{
			SelectObj(ho_BoundariesCenteredAndScaled, &ho_ObjectSelected, hv_i);
			PaintXld(ho_ObjectSelected, (*ho_ModelImage), &(*ho_ModelImage), 255);
		}
	}
	CountObj(ho_HolesCenteredAndScaled, &hv_NumberHoles);
	{
		HTuple end_val35 = hv_NumberHoles;
		HTuple step_val35 = 1;
		for (hv_i = 1; hv_i.Continue(end_val35, step_val35); hv_i += step_val35)
		{
			SelectObj(ho_HolesCenteredAndScaled, &ho_ObjectSelected, hv_i);
			PaintXld(ho_ObjectSelected, (*ho_ModelImage), &(*ho_ModelImage), 0);
		}
	}
	Threshold((*ho_ModelImage), &ho_Region, 10, 255);
	DilationRectangle1(ho_Region, &ho_RegionDilation, 3, 3);
	ReduceDomain((*ho_ModelImage), ho_RegionDilation, &(*ho_ModelImage));
	return;
}


