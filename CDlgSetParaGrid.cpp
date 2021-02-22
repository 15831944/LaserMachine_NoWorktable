// CDlgSetParaGrid.cpp: 实现文件
//

//#include "pch.h"
#include "stdafx.h"
#include "LaserMachine.h"
#include "CDlgSetParaGrid.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "LaserMachineView.h"
#include "LaserMachineDoc.h"
#include "CDlgDevCfgTabScanner.h"


#include "CGridListCtrlEx\CGridColumnTraitDateTime.h"
#include "CGridListCtrlEx\CGridColumnTraitEdit.h"
#include "CGridListCtrlEx\CGridColumnTraitCombo.h"
#include "CGridListCtrlEx\CGridColumnTraitHyperLink.h"
#include "CGridListCtrlEx\CGridRowTraitXP.h"
#include "CGridListCtrlEx\CGridRowTrait.h"
#include "CGridListCtrlEx\ViewConfigSection.h"


std::vector<double> vecGridX, vecGridY;

void SetGridUnitX(double fGridUnitX)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fGridUnitX);
	WritePrivateProfileString(_T("ProcessSettings"), _T("GRID_UNIT_X"), strTmp, CONFIG_INI_PATH);
}
double ReadGridUnitX()
{
	CString strTmp;
	GetPrivateProfileString(_T("ProcessSettings"), _T("GRID_UNIT_X"), _T("140"), strTmp.GetBuffer(10), 10, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}
void SetGridUnitY(double fGridUnitY)
{
	CString strTmp;
	strTmp.Format(_T("%lf"), fGridUnitY);
	WritePrivateProfileString(_T("ProcessSettings"), _T("GRID_UNIT_Y"), strTmp, CONFIG_INI_PATH);
}
double ReadGridUnitY()
{
	CString strTmp;
	GetPrivateProfileString(_T("ProcessSettings"), _T("GRID_UNIT_Y"), _T("140"), strTmp.GetBuffer(10), 10, CONFIG_INI_PATH);
	return (double)_ttof(strTmp);
}




// CDlgSetParaGrid 对话框

IMPLEMENT_DYNAMIC(CDlgSetParaGrid, CDialogEx)

CDlgSetParaGrid::CDlgSetParaGrid(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETPARA_GRID, pParent)
	, m_fGridUnitX(140)
	, m_fGridUnitY(140)
	, m_fBorderRangeX(0)
	, m_fBorderRangeY(0)
{
	m_fScannerRegion = 140;
	m_fWktableRegion = 500;

}

CDlgSetParaGrid::~CDlgSetParaGrid()
{
}

void CDlgSetParaGrid::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SET_GRID, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_SET_GRID_X, m_fGridUnitX);
	DDV_MinMaxDouble(pDX, m_fGridUnitX, 1, 200);
	DDX_Text(pDX, IDC_EDIT_SET_GRID_Y, m_fGridUnitY);
	DDV_MinMaxDouble(pDX, m_fGridUnitY, 1, 200);
	DDX_Text(pDX, IDC_EDIT_SET_GRID_BORDER_RANGE_X, m_fBorderRangeX);
	DDX_Text(pDX, IDC_EDIT_SET_GRID_BORDER_RANGE_Y, m_fBorderRangeY);
}


BEGIN_MESSAGE_MAP(CDlgSetParaGrid, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SER_GRID_PRESETTING, &CDlgSetParaGrid::OnBnClickedButtonSerGridPresetting)
	ON_BN_CLICKED(IDOK, &CDlgSetParaGrid::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSetParaGrid 消息处理程序






BOOL CDlgSetParaGrid::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_fGridUnitX = ReadGridUnitX();
	m_fGridUnitY = ReadGridUnitY();
	m_fScannerRegion = ReadScannerCaliRegion();

	//获取加工对象外框
	CLaserMachineDoc* pDoc = (CLaserMachineDoc*)((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetActiveDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return FALSE;
	CMachineListContainer* pListContainerTmp = pDoc->m_pLaserObjList;
	ObjRect rectBorder = pListContainerTmp->GetObjBound();
	m_fBorderRangeX = abs(rectBorder.max_x - rectBorder.min_x);
	m_fBorderRangeY = abs(rectBorder.max_y - rectBorder.min_y);

	UpdateData(FALSE);

	// Create and attach image list
	m_ImageList.Create(47, 47, ILC_COLOR | ILC_MASK, 0, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_MIDDLE));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_CORNER_LT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_CORNER_RT));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_CORNER_RD));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_CORNER_LD));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_SIDE_T));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_SIDE_D));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_SIDE_L));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_GRID_SIDE_R));
	m_ListCtrl.SetImageList(&m_ImageList, LVSIL_SMALL);

	// Give better margin to editors
	m_ListCtrl.SetCellMargin(0);
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() & ~LVS_EX_FULLROWSELECT);
	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_NOCOLUMNHEADER);
	m_ListCtrl.SetDefaultRowTrait(new CGridRowTraitXP);
	m_ListCtrl.EnableVisualStyles(true);


	//初始化分格参数
	GenGridListControl(vecGridX, vecGridY);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgSetParaGrid::OnBnClickedButtonSerGridPresetting()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	SetGridUnitX(m_fGridUnitX);
	SetGridUnitY(m_fGridUnitY);

	GenGridListControl(m_fGridUnitX, m_fGridUnitY, m_fBorderRangeX, m_fBorderRangeY);
}


void CDlgSetParaGrid::GenGridListControl(double fBorderRangeX, double fBorderRangeY)
{
	//检查超限
	if (m_fWktableRegion < fBorderRangeX || m_fWktableRegion < fBorderRangeY)
	{
		AfxMessageBox(_T("加工对象超幅面"));
		return;
	}

	//计算每一条分格线参数
	int nCtGridX, nCtGridY;
	std::vector<CString> vecGridStringX, vecGridStringY;
	CString strTmp;
	nCtGridX = (int)ceil(fBorderRangeX / m_fScannerRegion);
	nCtGridY = (int)ceil(fBorderRangeY / m_fScannerRegion);
	for (int i = 0; i < nCtGridX; i++)
	{
		strTmp.Format(_T("%.2f"), i * m_fScannerRegion);
		vecGridStringX.push_back(strTmp);
	}
	strTmp.Format(_T("%.2f"), fBorderRangeX);
	vecGridStringX.push_back(strTmp);
	for (int j = 0; j < nCtGridY; j++)
	{
		strTmp.Format(_T("%.2f"), j * m_fScannerRegion);
		vecGridStringY.push_back(strTmp);
	}
	strTmp.Format(_T("%.2f"), fBorderRangeY);
	vecGridStringY.push_back(strTmp);

	//删除旧表
	int nCtColumn = m_ListCtrl.GetColumnCount();
	while (nCtColumn)
	{
		m_ListCtrl.DeleteColumn(--nCtColumn);
	}
	m_ListCtrl.DeleteAllItems();

	//根据分格参数生成新表
	//创建列
	m_ListCtrl.InsertHiddenLabelColumn();	// Requires one never uses column 0
	for (int nCol = 0; nCol < vecGridStringX.size() + 1; nCol++)
	{
		m_ListCtrl.InsertColumnTrait(nCol + 1, _T(""), LVCFMT_CENTER, 48, nCol, new CGridColumnTraitEdit);
	}

	//导入数据
	for (int nRowID = 0; nRowID < vecGridStringY.size() + 1; nRowID++)
	{
		m_ListCtrl.InsertItem(nRowID, _T(""));						//每另起一行先添加隐藏列

		for (int nColID = 0; nColID < vecGridStringX.size() + 1; nColID++)
		{
			if (nColID == 0)
			{
				if (nRowID == vecGridStringY.size())						//左下角原点位置添加文字说明
					m_ListCtrl.SetItemText(nRowID, nColID + 1, _T("Y / X"));
				else												//除左下角外的每行行首为Y方向分割线坐标
					m_ListCtrl.SetItemText(nRowID, nColID + 1, vecGridStringY[vecGridStringY.size() - nRowID - 1]);
			}
			else
			{
				if (nRowID == vecGridStringY.size())						//最后一行除左下角外为X方向分割线坐标
					m_ListCtrl.SetItemText(nRowID, nColID + 1, vecGridStringX[(size_t)nColID - 1]);
				else
				{
					//L型坐标的右上角部分为网格线
					//根据网格线不同位置导入不同icon
					if (nRowID == 0 && nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 1);			//左上角
					else if (nRowID == 0 && nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 2);			//右上角
					else if (nRowID == vecGridStringY.size() - 1 && nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 4);			//左下角
					else if (nRowID == vecGridStringY.size() - 1 && nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 3);			//右下角
					else if (nRowID == 0)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 5);			//上边
					else if (nRowID == vecGridStringY.size() - 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 6);			//下边
					else if (nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 7);			//左边
					else if (nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 8);			//右边
					else
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 0);			//中间

				}
			}
		}
	}
}
void CDlgSetParaGrid::GenGridListControl(double fGridUnitX, double fGridUnitY, double fBorderRangeX, double fBorderRangeY)
{
	//检查超限
	if (m_fWktableRegion < fBorderRangeX || m_fWktableRegion < fBorderRangeY)
	{
		AfxMessageBox(_T("加工对象超幅面"));
		return;
	}
	if (m_fScannerRegion < m_fGridUnitX || m_fScannerRegion < m_fGridUnitY)
	{
		AfxMessageBox(_T("分格参数超幅面"));
		return;
	}

	//计算每一条分格线参数
	int nCtGridX, nCtGridY;
	std::vector<CString> vecGridStringX, vecGridStringY;
	CString strTmp;
	nCtGridX = (int)ceil(fBorderRangeX / fGridUnitX);
	nCtGridY = (int)ceil(fBorderRangeY / fGridUnitY);
	for (int i = 0; i < nCtGridX; i++)
	{
		strTmp.Format(_T("%.2f"), i * fGridUnitX);
		vecGridStringX.push_back(strTmp);
	}
	strTmp.Format(_T("%.2f"), fBorderRangeX);
	vecGridStringX.push_back(strTmp);
	for (int j = 0; j < nCtGridY; j++)
	{
		strTmp.Format(_T("%.2f"), j * fGridUnitY);
		vecGridStringY.push_back(strTmp);
	}
	strTmp.Format(_T("%.2f"), fBorderRangeY);
	vecGridStringY.push_back(strTmp);

	//删除旧表
	int nCtColumn = m_ListCtrl.GetColumnCount();
	while (nCtColumn)
	{
		m_ListCtrl.DeleteColumn(--nCtColumn);
	}
	m_ListCtrl.DeleteAllItems();

	//根据分格参数生成新表
	//创建列
	m_ListCtrl.InsertHiddenLabelColumn();	// Requires one never uses column 0
	for (int nCol = 0; nCol < vecGridStringX.size() + 1; nCol++)
	{
		m_ListCtrl.InsertColumnTrait(nCol + 1, _T(""), LVCFMT_CENTER, 48, nCol, new CGridColumnTraitEdit);
	}

	//导入数据
	for (int nRowID = 0; nRowID < vecGridStringY.size() + 1; nRowID++)
	{
		m_ListCtrl.InsertItem(nRowID, _T(""));						//每另起一行先添加隐藏列

		for (int nColID = 0; nColID < vecGridStringX.size() + 1; nColID++)
		{
			if (nColID == 0)
			{
				if (nRowID == vecGridStringY.size())						//左下角原点位置添加文字说明
					m_ListCtrl.SetItemText(nRowID, nColID + 1, _T("Y / X"));
				else												//除左下角外的每行行首为Y方向分割线坐标
					m_ListCtrl.SetItemText(nRowID, nColID + 1, vecGridStringY[vecGridStringY.size() - nRowID - 1]);
			}
			else
			{
				if (nRowID == vecGridStringY.size())						//最后一行除左下角外为X方向分割线坐标
					m_ListCtrl.SetItemText(nRowID, nColID + 1, vecGridStringX[(size_t)nColID - 1]);
				else
				{
					//L型坐标的右上角部分为网格线
					//根据网格线不同位置导入不同icon
					if (nRowID == 0 && nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 1);			//左上角
					else if (nRowID == 0 && nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 2);			//右上角
					else if (nRowID == vecGridStringY.size() - 1 && nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 4);			//左下角
					else if (nRowID == vecGridStringY.size() - 1 && nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 3);			//右下角
					else if (nRowID == 0)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 5);			//上边
					else if (nRowID == vecGridStringY.size() - 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 6);			//下边
					else if (nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 7);			//左边
					else if (nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 8);			//右边
					else
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 0);			//中间

				}
			}
		}
	}
}
void CDlgSetParaGrid::GenGridListControl(std::vector<double> vecGridX, std::vector<double> vecGridY)
{
	//计算每一条分格线参数
	std::vector<CString> vecGridStringX, vecGridStringY;
	CString strTmp;
	for (int i = 0; i < vecGridX.size(); i++)
	{
		strTmp.Format(_T("%.2f"), vecGridX[i]);
		vecGridStringX.push_back(strTmp);
	}
	for (int j = 0; j < vecGridY.size(); j++)
	{
		strTmp.Format(_T("%.2f"), vecGridY[j]);
		vecGridStringY.push_back(strTmp);
	}

	//删除旧表
	int nCtColumn = m_ListCtrl.GetColumnCount();
	while (nCtColumn)
	{
		m_ListCtrl.DeleteColumn(--nCtColumn);
	}
	m_ListCtrl.DeleteAllItems();

	//根据分格参数生成新表
	//创建列
	m_ListCtrl.InsertHiddenLabelColumn();	// Requires one never uses column 0
	for (int nCol = 0; nCol < vecGridStringX.size() + 1; nCol++)
	{
		m_ListCtrl.InsertColumnTrait(nCol + 1, _T(""), LVCFMT_CENTER, 48, nCol, new CGridColumnTraitEdit);
	}

	//导入数据
	for (int nRowID = 0; nRowID < vecGridStringY.size() + 1; nRowID++)
	{
		m_ListCtrl.InsertItem(nRowID, _T(""));						//每另起一行先添加隐藏列

		for (int nColID = 0; nColID < vecGridStringX.size() + 1; nColID++)
		{
			if (nColID == 0)
			{
				if (nRowID == vecGridStringY.size())						//左下角原点位置添加文字说明
					m_ListCtrl.SetItemText(nRowID, nColID + 1, _T("Y / X"));
				else												//除左下角外的每行行首为Y方向分割线坐标
					m_ListCtrl.SetItemText(nRowID, nColID + 1, vecGridStringY[vecGridStringY.size() - nRowID - 1]);
			}
			else
			{
				if (nRowID == vecGridStringY.size())						//最后一行除左下角外为X方向分割线坐标
					m_ListCtrl.SetItemText(nRowID, nColID + 1, vecGridStringX[(size_t)nColID - 1]);
				else
				{
					//L型坐标的右上角部分为网格线
					//根据网格线不同位置导入不同icon
					if (nRowID == 0 && nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 1);			//左上角
					else if (nRowID == 0 && nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 2);			//右上角
					else if (nRowID == vecGridStringY.size() - 1 && nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 4);			//左下角
					else if (nRowID == vecGridStringY.size() - 1 && nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 3);			//右下角
					else if (nRowID == 0)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 5);			//上边
					else if (nRowID == vecGridStringY.size() - 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 6);			//下边
					else if (nColID == 1)
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 7);			//左边
					else if (nColID == vecGridStringX.size())
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 8);			//右边
					else
						m_ListCtrl.SetCellImage(nRowID, nColID + 1, 0);			//中间

				}
			}
		}
	}
}


void CDlgSetParaGrid::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	vecGridX.clear();
	vecGridY.clear();

	int nCtRow, nCtColume;
	nCtColume = m_ListCtrl.GetColumnCount();
	nCtRow = m_ListCtrl.GetItemCount();
	for (int i = 2; i < nCtColume; i++)
		vecGridX.push_back(_ttof(m_ListCtrl.GetItemText(nCtRow - 1, i)));
	for (int j = nCtRow - 2; j >= 0; j--)
		vecGridY.push_back(_ttof(m_ListCtrl.GetItemText(j, 1)));
	
	//通知窗口重绘
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	pView->Invalidate();

	CDialogEx::OnOK();
}
