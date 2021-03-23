// ObjectProperty.cpp : 实现文件
//

#include "stdafx.h"
#include "LaserMachine.h"
#include "LaserMachineDoc.h"
#include "LaserMachineView.h"
#include "MainFrm.h"
#include "ObjectProperty.h"
#include "ObjectProtyDlg1.h"
#include "ObjectProtyDlg2.h"


// ********************User Micro Define
#define UnDisp_Geometry_Property\
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC50)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC51)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC52)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT23)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT24)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO3)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO4)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO5)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO6)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO7)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO8)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO9)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO10)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO11)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO12)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO13)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_CHECK1)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN19)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN20)->ShowWindow(SW_HIDE);

#define Disp_Machine_Property\
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("加工属性"));\
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 35, 375, 188, 375, BS_CENTER); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC3)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC4)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC5)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC6)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC7)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC8)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC9)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC12)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC13)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC14)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC15)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC16)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC17)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC18)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC19)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC20)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC21)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC22)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT1)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT2)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT3)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT4)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT6)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT7)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT8)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT9)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT10)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO1)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO2)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN_SAVE)->ShowWindow(SW_SHOW); \
	UnDisp_Geometry_Property

#define UnDisp_Machine_Property\
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC3)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC4)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC5)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC6)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC7)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC8)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC9)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC12)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC13)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC14)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC15)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC16)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC17)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC18)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC19)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC20)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC21)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC22)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT1)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT2)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT3)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT4)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT6)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT7)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT8)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT9)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT10)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO1)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_RADIO2)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN_SAVE)->ShowWindow(SW_HIDE); \
	UnDisp_Geometry_Property

#define Disp_Laser_Dlg\
	if (gLaserType==IPG_QCW_Laser)\
	{\
	GetDlgItem(IDC_OBJ_PROTY_STATIC10)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT5)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC11)->ShowWindow(SW_SHOW); \
	}\
	else\
	{\
	GetDlgItem(IDC_OBJ_PROTY_STATIC10)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT5)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC11)->ShowWindow(SW_HIDE); \
	}
#define Disp_Layer_Special\
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN12)->ShowWindow(SW_SHOW);
#define Close_Layer_Special\
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN12)->ShowWindow(SW_HIDE);

#define Disp_Object_Panel\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->SetWindowText(_T("上移对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->SetWindowText(_T("下移对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->SetWindowText(_T("删除对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("编辑对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN5)->SetWindowText(_T("组合群组")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN5)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->SetWindowText(_T("解散群组")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->SetWindowText(_T("转为多段线")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN8)->SetWindowText(_T("合并多段线")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN8)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC27)->SetWindowText(_T("对象所在图层")); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC27)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT13)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_COMBO1)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN9)->SetWindowText(_T("改变图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN9)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->SetWindowText(_T("生成填充区")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->SetWindowText(_T("生成扩展线")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN12)->SetWindowText(_T("加工排序")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN12)->ShowWindow(SW_HIDE);\
	Disp_Machine_Property

#define Disp_Layer_Panel\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->SetWindowText(_T("上移图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->SetWindowText(_T("下移图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->SetWindowText(_T("关闭图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("锁定图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN5)->SetWindowText(_T("修改图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN5)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->SetWindowText(_T("删除图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->SetWindowText(_T("清除空图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN8)->SetWindowText(_T("合并冗余层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN8)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC27)->SetWindowText(_T("图层名称")); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC27)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_COMBO1)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT13)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_BTN9)->SetWindowText(_T("新建图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN9)->ShowWindow(SW_SHOW);\
	Disp_Machine_Property\
	Close_Layer_Special

#define Disp_Layer_List\
	m_PropertyList.DeleteAllItems(); \
	m_PropertyList.DeleteColumn(3); \
	m_PropertyList.DeleteColumn(2); \
	m_PropertyList.DeleteColumn(1); \
	m_PropertyList.DeleteColumn(0); \
	m_PropertyList.InsertColumn(0, _T("索 引"), LVCFMT_CENTER, 40); \
	m_PropertyList.InsertColumn(1, _T("图层名称"), LVCFMT_CENTER, 100); \
	m_PropertyList.InsertColumn(2, _T("状 态"), LVCFMT_CENTER, 50); \
	m_PropertyList.InsertColumn(3, _T("统 计"), LVCFMT_CENTER, 50); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC1)->SetWindowTextW(_T("图层列表/对象列表"));
#define Disp_Object_List\
	m_PropertyList.DeleteAllItems(); \
	m_PropertyList.DeleteColumn(3); \
	m_PropertyList.DeleteColumn(2); \
	m_PropertyList.DeleteColumn(1); \
	m_PropertyList.DeleteColumn(0); \
	m_PropertyList.InsertColumn(0, _T("索  引"), LVCFMT_CENTER, 55); \
	m_PropertyList.InsertColumn(1, _T("对象类型"), LVCFMT_CENTER, 85); \
	m_PropertyList.InsertColumn(2, _T("图  层"), LVCFMT_CENTER, 100); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC1)->SetWindowTextW(_T("对象列表/图层列表"));

//**
#define Enable_Layer_BTN_UpAndDown\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(TRUE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(TRUE);

#define Enable_Layer_OBJ_BTN_UpAndDown\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(TRUE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(TRUE);

#define Disable_Layer_BTN_UpAndDown\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(FALSE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(FALSE);

#define Disable_Layer_OBJ_BTN_UpAndDown\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(FALSE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(FALSE);
/////
#define Enable_Layer_BTN_Close\
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->SetWindowText(_T("关闭图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->EnableWindow(TRUE);
#define Enable_Layer_BTN_Open\
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->SetWindowText(_T("打开图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->EnableWindow(TRUE);
#define Disable_Layer_BTN_Close\
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->SetWindowText(_T("关闭图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN3)->EnableWindow(FALSE);
#define Enable_Layer_BTN_Lock\
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("锁定图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->EnableWindow(TRUE);
#define Enable_Layer_BTN_Unlock\
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("解锁图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->EnableWindow(TRUE);
#define Disable_Layer_BTN_Lock\
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("锁定图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->EnableWindow(FALSE);
#define Enable_Layer_BTN_Modify		GetDlgItem(IDC_OBJ_PROTY_BTN5)->EnableWindow(TRUE);
#define Disable_Layer_BTN_Modify	GetDlgItem(IDC_OBJ_PROTY_BTN5)->EnableWindow(FALSE);
#define Enable_Layer_BTN_Delete		GetDlgItem(IDC_OBJ_PROTY_BTN6)->EnableWindow(TRUE);
#define Disable_Layer_BTN_Delete	GetDlgItem(IDC_OBJ_PROTY_BTN6)->EnableWindow(FALSE);
#define Enable_Layer_BTN_ClearLayer\
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->SetWindowText(_T("清除空图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->EnableWindow(TRUE);
#define Enable_Layer_BTN_ClearObject\
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->SetWindowText(_T("清除空对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->EnableWindow(TRUE);
#define Disable_Layer_BTN_ClearLayer\
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->SetWindowText(_T("清除空图层")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN7)->EnableWindow(FALSE);
#define Enable_Layer_BTN_Combine	GetDlgItem(IDC_OBJ_PROTY_BTN8)->EnableWindow(TRUE);
#define Disable_Layer_BTN_Combine	GetDlgItem(IDC_OBJ_PROTY_BTN8)->EnableWindow(FALSE);
#define Enable_Layer_BTN_New		GetDlgItem(IDC_OBJ_PROTY_BTN9)->EnableWindow(TRUE);
#define Disable_Layer_BTN_New		GetDlgItem(IDC_OBJ_PROTY_BTN9)->EnableWindow(FALSE);

#define Enable_OBJ_BTN_UpAndDown\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->SetWindowText(_T("上移对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(TRUE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->SetWindowText(_T("下移对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_UpAndDown\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->SetWindowText(_T("上移对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(FALSE); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->SetWindowText(_T("下移对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_ReDirect\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->SetWindowText(_T("交换方向")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_ReDirect\
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->SetWindowText(_T("交换方向")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN1)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_ReNode\
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->SetWindowText(_T("改变起点")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_ReNode\
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->SetWindowText(_T("改变起点")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN2)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_Delete		GetDlgItem(IDC_OBJ_PROTY_BTN3)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_Delete		GetDlgItem(IDC_OBJ_PROTY_BTN3)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_Edit\
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("编辑对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_Edit\
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->SetWindowText(_T("编辑对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN4)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_Group		GetDlgItem(IDC_OBJ_PROTY_BTN5)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_Group		GetDlgItem(IDC_OBJ_PROTY_BTN5)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_DisGroup\
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->SetWindowText(_T("解散群组")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->EnableWindow(TRUE);
#define Enable_OBJ_BTN_BreakPolyline\
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->SetWindowText(_T("分解对象")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN6)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_DisGroup	GetDlgItem(IDC_OBJ_PROTY_BTN6)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_Polyline		GetDlgItem(IDC_OBJ_PROTY_BTN7)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_Polyline	GetDlgItem(IDC_OBJ_PROTY_BTN7)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_CombinePoly	GetDlgItem(IDC_OBJ_PROTY_BTN8)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_CombinePoly	GetDlgItem(IDC_OBJ_PROTY_BTN8)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_ChangeLayer	GetDlgItem(IDC_OBJ_PROTY_BTN9)->EnableWindow(TRUE);
#define Disable_OBJ_BTN_ChangeLayer	GetDlgItem(IDC_OBJ_PROTY_BTN9)->EnableWindow(FALSE);
#define Enable_OBJ_BTN_FillCreat\
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->SetWindowText(_T("生成填充区")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->ShowWindow(SW_SHOW);
#define Enable_OBJ_BTN_FillDestroy\
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->SetWindowText(_T("取消填充区")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN10)->ShowWindow(SW_SHOW);
#define Disable_OBJ_BTN_FillCreat	GetDlgItem(IDC_OBJ_PROTY_BTN10)->ShowWindow(SW_HIDE);
#define Enable_OBJ_BTN_WidenCreat\
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->SetWindowText(_T("生成展宽线")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->ShowWindow(SW_SHOW);
#define Enable_OBJ_BTN_WidenDegen\
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->SetWindowText(_T("取消展宽")); \
	GetDlgItem(IDC_OBJ_PROTY_BTN11)->ShowWindow(SW_SHOW);
#define Disable_OBJ_BTN_WidenCreat	GetDlgItem(IDC_OBJ_PROTY_BTN11)->ShowWindow(SW_HIDE);
#define Enable_OBJ_BTN_Route		GetDlgItem(IDC_OBJ_PROTY_BTN12)->ShowWindow(SW_SHOW);
#define Disable_OBJ_BTN_Route		GetDlgItem(IDC_OBJ_PROTY_BTN12)->ShowWindow(SW_HIDE);
#define Enable_OBJ_Dot_Proty\
	GetDlgItem(IDC_OBJ_PROTY_STATIC23)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT11)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC24)->ShowWindow(SW_SHOW);\
	GetDlgItem(IDC_OBJ_PROTY_BTN13)->ShowWindow(SW_SHOW);
#define Disable_OBJ_Dot_Proty\
	GetDlgItem(IDC_OBJ_PROTY_STATIC23)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT11)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC24)->ShowWindow(SW_HIDE);\
	GetDlgItem(IDC_OBJ_PROTY_BTN13)->ShowWindow(SW_HIDE);
#define Enable_OBJ_Rise_By_Pass\
	GetDlgItem(IDC_OBJ_PROTY_STATIC25)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT12)->ShowWindow(SW_SHOW); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC26)->ShowWindow(SW_SHOW);\
	GetDlgItem(IDC_OBJ_PROTY_BTN14)->ShowWindow(SW_SHOW);
#define Disable_OBJ_Rise_By_Pass\
	GetDlgItem(IDC_OBJ_PROTY_STATIC25)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_EDIT12)->ShowWindow(SW_HIDE); \
	GetDlgItem(IDC_OBJ_PROTY_STATIC26)->ShowWindow(SW_HIDE);\
	GetDlgItem(IDC_OBJ_PROTY_BTN14)->ShowWindow(SW_HIDE);
// ********************

// CObjectProperty
IMPLEMENT_DYNCREATE(CObjectProperty, CFormView)

CObjectProperty::CObjectProperty()
	: CFormView(CObjectProperty::IDD)
	, m_LaserOnDelay(gLaserOnDelay)
	, m_LaserOffDelay(gLaserOffDelay)
	, m_BeforMarkDelay(gBeforMarkDelay)
	, m_AfterMarkDelay(gAfterMarkDelay)
	, m_PolylineDelay(gPolylineDelay)
	, m_Rise_Lenth_Step(0)
	, m_WaitTime(0)
{
	m_Init_Flag = FALSE;
	m_bDispObject = false;
	m_bDegenerate = true;
	m_ProtyListIndex.swap(vector<UINT>());
	m_SelectedObj.swap(vector<UINT>());
	m_nSelGroup = 0;

	m_bLocate = FALSE;
	m_strBtnMark = _T("直接加工");

}

CObjectProperty::~CObjectProperty()
{
}

void CObjectProperty::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OBJECT_PROPERTY_LIST, m_PropertyList);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT1, m_Speed);
	DDV_MinMaxFloat(pDX, m_Speed, 0.0, 20000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT2, m_Power);
	DDV_MinMaxFloat(pDX, m_Power, 0.0, 100.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT3, m_Frequncy);
	DDV_MinMaxFloat(pDX, m_Frequncy, 0.0, 20000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT4, m_Count);
	DDV_MinMaxUInt(pDX, m_Count, 0, 100000);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT5, m_PulseWidth);
	DDV_MinMaxFloat(pDX, m_PulseWidth, 0.0, 1000000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT6, m_LaserOnDelay);
	DDV_MinMaxFloat(pDX, m_LaserOnDelay, -100000.0, 100000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT7, m_LaserOffDelay);
	DDV_MinMaxFloat(pDX, m_LaserOffDelay, -100000.0, 100000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT8, m_BeforMarkDelay);
	DDV_MinMaxFloat(pDX, m_BeforMarkDelay, -100000.0, 100000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT9, m_AfterMarkDelay);
	DDV_MinMaxFloat(pDX, m_AfterMarkDelay, -100000.0, 100000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT10, m_PolylineDelay);
	DDV_MinMaxFloat(pDX, m_PolylineDelay, -100000.0, 100000.0);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT11, m_WaitTime);
	DDV_MinMaxFloat(pDX, m_WaitTime, 0, 999999);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT12, m_Rise_Lenth_Step);
	DDV_MinMaxFloat(pDX, m_Rise_Lenth_Step, -100, 100);
	DDX_Radio(pDX, IDC_OBJ_PROTY_RADIO1, m_ModeSel);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT13, m_LayerName);
	DDX_Control(pDX, IDC_OBJ_PROTY_COMBO1, m_LayerNameListBox);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT14, m_dVar1);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT15, m_dVar2);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT16, m_dVar3);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT17, m_dVar4);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT18, m_dVar5);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT19, m_dVar6);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT20, m_dVar7);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT21, m_dVar8);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT22, m_dVar9);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT23, m_dVar10);
	DDX_Text(pDX, IDC_OBJ_PROTY_EDIT24, m_dVar11);
	DDX_Radio(pDX, IDC_OBJ_PROTY_RADIO3, m_OutlinePrior);
	DDX_Check(pDX, IDC_OBJ_PROTY_CHECK1, m_FillEnable);
	DDX_Radio(pDX, IDC_OBJ_PROTY_RADIO6, m_nSelGroup);
	DDX_Radio(pDX, IDC_OBJ_PROTY_RADIO10, m_GapMode);
	DDX_Radio(pDX, IDC_OBJ_PROTY_RADIO12, m_FillMode);
}

void CObjectProperty::OnInitialUpdate()
{
	if (m_Init_Flag)
		return;
	m_Init_Flag = TRUE;
	CFormView::OnInitialUpdate();
	CLaserMachineView* pView = (CLaserMachineView*)
		((CMainFrame*)AfxGetApp()->m_pMainWnd)->m_wndSplitter1.GetPane(0, 0);
	CLaserMachineDoc* pDoc = pView->GetDocument();
	if (!pDoc)
		return;
	m_pView = pView;
	m_pObjList = pDoc->m_pLaserObjList;
	m_pDoc = pDoc;
	m_ObjSel_Old = -1;
	m_LayerSel_Old = -1;
	m_bDispObject = false;
	m_PropertyList.SetExtendedStyle(m_PropertyList.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 初始化显示为图层列表
	Disp_Layer_List
	Disp_Layer_Panel
	Disable_Layer_BTN_New
	Disp_Laser_Dlg
	
	gPara_To_mPara();
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CObjectProperty, CFormView)
	ON_WM_SIZE()
	ON_MESSAGE(WM_ObjList_Refresh, &CObjectProperty::OnObjlistRefresh)
	ON_NOTIFY(LVN_KEYDOWN, IDC_OBJECT_PROPERTY_LIST, &CObjectProperty::OnKeydownObjectPropertyList)
	ON_WM_MOUSEMOVE()
	ON_STN_CLICKED(IDC_OBJ_PROTY_STATIC1, &CObjectProperty::OnClickedObjectOrLayer)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN_SAVE, &CObjectProperty::OnClickedObjProtyBtnSave)
	ON_NOTIFY(NM_CLICK, IDC_OBJECT_PROPERTY_LIST, &CObjectProperty::OnClickObjectPropertyList)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN1, &CObjectProperty::OnObjProtyBtnLayerOrObjUp)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN2, &CObjectProperty::OnObjProtyBtnLayerOrObjDown)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN3, &CObjectProperty::OnObjProtyBtnLayerOpenAndCloseOrObjDelete)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN4, &CObjectProperty::OnObjProtyBtnLayerLockAndUnlockOrObjEdit)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN5, &CObjectProperty::OnObjProtyBtnLayerModifyOrObjGroup)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN6, &CObjectProperty::OnObjProtyBtnLayerDeleteOrObjExplode)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN7, &CObjectProperty::OnObjProtyBtnLayerClear)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN8, &CObjectProperty::OnObjProtyBtnCombine)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN9, &CObjectProperty::OnObjProtyBtnLayerNew)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN11, &CObjectProperty::OnClickedObjProtyExtend)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN10, &CObjectProperty::OnClickedObjProtyFill)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN15, &CObjectProperty::OnClickedObjProtyBtn15)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN16, &CObjectProperty::OnClickedObjProtyBtn16)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN17, &CObjectProperty::OnClickedObjProtyBtn17)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN18, &CObjectProperty::OnClickedObjProtyBtn18)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN19, &CObjectProperty::OnClickedObjProtyBtn19)
	ON_BN_CLICKED(IDC_OBJ_PROTY_BTN20, &CObjectProperty::OnClickedObjProtyBtn20)
	ON_BN_CLICKED(IDC_OBJ_PROTY_CHECK1, &CObjectProperty::OnClickedObjProtyCheck1)
	ON_BN_CLICKED(IDC_OBJ_PROTY_RADIO6, &CObjectProperty::OnClickedObjProtyRadio6)
	ON_COMMAND(IDC_OBJ_PROTY_RADIO7, &CObjectProperty::OnClickedObjProtyRadio6)
	ON_COMMAND(IDC_OBJ_PROTY_RADIO8, &CObjectProperty::OnClickedObjProtyRadio6)
	ON_COMMAND(IDC_OBJ_PROTY_RADIO9, &CObjectProperty::OnClickedObjProtyRadio6)
	ON_BN_CLICKED(IDC_BUTTON_OBJECT_START_MARK, &CObjectProperty::OnBnClickedButtonObjectStartMark)
END_MESSAGE_MAP()


// CObjectProperty 诊断
#ifdef _DEBUG
void CObjectProperty::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjectProperty::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// 自定义函数
void CObjectProperty::HScroll(int Index)
{
	int nItem = m_PropertyList.GetTopIndex();	// 获取顶层索引
	CRect rc;
	m_PropertyList.GetItemRect(nItem, rc, LVIR_BOUNDS);
	nItem = Index - nItem - 5;
	CSize sz(0, nItem * rc.Height());	// 取得要滚动的size
	m_PropertyList.Scroll(sz);
}

//2021.02
void CObjectProperty::gPara_To_mPara()
{
	m_Speed = gProcessSpeed;
	m_Power = gProcessPower;
	m_Frequncy = (float)gProcessFrequncy / 1000;
	m_Count = gProcessTimes;
	m_PulseWidth = gProcessPulseWidth;
	m_ModeSel = gProcessMode;
	m_WaitTime = gProcessWaitTime;
	m_LaserOnDelay = gLaserOnDelay;
	m_LaserOffDelay = gLaserOffDelay;
	m_BeforMarkDelay = gBeforMarkDelay;
	m_AfterMarkDelay = gAfterMarkDelay;
	m_PolylineDelay = gPolylineDelay;
}

void CObjectProperty::LayerPara_To_mPara(CMachinePara_Layer* pLayer)
{
	m_Speed = pLayer->m_MachinePara.Speed;
	m_Power = pLayer->m_MachinePara.Power;
	m_Frequncy = (float)(pLayer->m_MachinePara.Frequncy) / 1000;
	m_Count = pLayer->m_MachinePara.Times;
	m_PulseWidth = pLayer->m_MachinePara.PulseWidth;
	m_ModeSel = pLayer->m_MachineMode;
	m_WaitTime = 0.0;
	m_LaserOnDelay = pLayer->m_MachinePara.LaserOnDelay;
	m_LaserOffDelay = pLayer->m_MachinePara.LaserOffDelay;
	m_BeforMarkDelay = pLayer->m_MachinePara.BeforMarkDelay;
	m_AfterMarkDelay = pLayer->m_MachinePara.AfterMarkDelay;
	m_PolylineDelay = pLayer->m_MachinePara.PolylineDelay;
}

void CObjectProperty::UIRefreshLayer()
{
	int Count = m_PropertyList.GetItemCount();
	int SelCount = 0;
	bool Flag_Closed = false;
	bool Flag_Locked = false;
	int Index = 0;
	CMachinePara_Layer* pLayer;
	for (int i = 0; i < Count; i++)
	{
		CString str = m_PropertyList.GetItemText(i, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		pLayer = m_pObjList->GetLayerOfNumber(nLayer);
		if (m_PropertyList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_PropertyList.SetItemText(i, 2, _T("已选中"));
			SelCount++;
			Index = nLayer;
			if (pLayer != NULL)
			{
				if (((pLayer->m_bIsLayerStatus) & IsObjClosed) != 0)
					Flag_Closed = true;
				if (((pLayer->m_bIsLayerStatus) & IsObjLocked) != 0)
					Flag_Locked = true;
			}
		}
		else
		{
			if (pLayer != NULL)
			{
				if (((pLayer->m_bIsLayerStatus) & IsObjClosed) != 0)
					m_PropertyList.SetItemText(i, 2, _T("已关闭"));
				else if (((pLayer->m_bIsLayerStatus) & IsObjLocked) != 0)
					m_PropertyList.SetItemText(i, 2, _T("已锁定"));
				else if (nLayer < LayerNum_Default)
					m_PropertyList.SetItemText(i, 2, _T("系 统"));
				else
					m_PropertyList.SetItemText(i, 2, _T("活 动"));
			}
		}
	}
	if (SelCount == 1)
	{
		pLayer = m_pObjList->GetLayerOfNumber(Index);
		LayerPara_To_mPara(pLayer);
		m_LayerName = pLayer->m_LayerName;
		if (Flag_Closed)
		{
			Enable_Layer_BTN_Open
			Disable_Layer_BTN_Lock
		}
		else
		{
			Enable_Layer_BTN_Close
			if (Flag_Locked)
			{
				Enable_Layer_BTN_Unlock
			}
			else
			{
				Enable_Layer_BTN_Lock
			}
		}
		if (Index < LayerNum_Default)
		{
			Disable_Layer_BTN_Modify
			Disable_Layer_BTN_Delete
			Disable_Layer_BTN_UpAndDown
			Disable_Layer_BTN_ClearLayer
		}
		else
		{
			Enable_Layer_BTN_Modify
			Enable_Layer_BTN_Delete
			Enable_Layer_BTN_UpAndDown
			Enable_Layer_BTN_ClearObject
		}
	}
	else
	{
		gPara_To_mPara();
		m_LayerName = "";
		Disable_Layer_BTN_UpAndDown
		Disable_Layer_BTN_Close
		Disable_Layer_BTN_Lock
		Disable_Layer_BTN_Modify
		Disable_Layer_BTN_Delete
		if (SelCount == 0)
		{
			Enable_Layer_BTN_ClearLayer
		}
		else
		{
			Disable_Layer_BTN_ClearLayer
		}
	}
	Enable_Layer_BTN_Combine
}

void CObjectProperty::UIRefreshObject(int Index)
{
	CMachineObj_Comm* pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
	int ObjType = pObj->GetObjType();
	CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(pObj->m_ObjByLayer);
	int nLayer = pObj->m_ObjByLayer;
	ObjPoint point1, point2;
	if (nLayer < LayerNum_Group)
		m_LayerNameListBox.SetCurSel(nLayer);
	else if (nLayer == LayerNum_Group)
		m_LayerNameListBox.SetCurSel(-1);
	else
		m_LayerNameListBox.SetCurSel(nLayer - LayerNum_Group - 1);
	LayerPara_To_mPara(pLayer);
	Enable_OBJ_BTN_UpAndDown
	Enable_OBJ_BTN_Delete
	Enable_OBJ_BTN_Edit
	Disable_OBJ_BTN_Group
	switch (ObjType)
	{
		case MachineObj_Type_Arc:
			Enable_OBJ_BTN_Polyline
			Disable_OBJ_BTN_DisGroup
			break;
		case MachineObj_Type_Line:
			Enable_OBJ_BTN_Polyline
			Disable_OBJ_BTN_DisGroup
			break;
		case MachineObj_Type_Group:
			Disable_OBJ_BTN_Polyline
			Enable_OBJ_BTN_DisGroup
			break;
		case MachineObj_Type_Polyline:
			Disable_OBJ_BTN_Polyline
			Enable_OBJ_BTN_BreakPolyline
			break;
		default:
			Disable_OBJ_BTN_DisGroup
			Disable_OBJ_BTN_Polyline
			break;
	}
	Disable_OBJ_BTN_CombinePoly
	Enable_OBJ_BTN_ChangeLayer
	if (ObjType == MachineObj_Type_Point)
	{
		Enable_OBJ_Dot_Proty
		m_WaitTime = ((CMachineObjPoint*)pObj)->m_MachineWaitTime;
	}
	else
	{
		Disable_OBJ_Dot_Proty
		m_WaitTime = gProcessWaitTime;
	}
	//************特殊操作*********
	if (nLayer < LayerNum_Default)
	{
		Disable_OBJ_BTN_FillCreat
		Disable_OBJ_BTN_WidenCreat
		Disable_OBJ_BTN_Route
	}
	else
	{
		//Fill判定
		if (ObjType == MachineObj_Type_Polyline)
		{
			point1 = pObj->GetObjStart(pObj);
			point2 = pObj->GetObjEnd(pObj);
			if ((abs(point1.x - point2.x) < Zero) && (abs(point1.y - point2.y) < Zero))
			{
				m_bDegenerate = false;
				Enable_OBJ_BTN_FillCreat
			}
			else
			{
				Disable_OBJ_BTN_FillCreat
			}
		}
		else if ((ObjType == MachineObj_Type_Circle)
			|| (ObjType == MachineObj_Type_Ellipse))
		{
			m_bDegenerate = false;
			Enable_OBJ_BTN_FillCreat
		}
		else if ((ObjType == MachineObj_Type_FillPolyline))
		{
			m_bDegenerate = true;
			Enable_OBJ_BTN_FillDestroy;
		}
		else
		{
			Disable_OBJ_BTN_FillCreat
		}
		//Widen 判定
		if ((ObjType == MachineObj_Type_Line)
			|| (ObjType == MachineObj_Type_Arc)
			|| (ObjType == MachineObj_Type_Polyline))
		{
			m_bDegenerate = false;
			Enable_OBJ_BTN_WidenCreat
		}
		else if ((ObjType == MachineObj_Type_WLine)		///////////////////////////////////////////////////////////////////////////////////
			|| (ObjType == MachineObj_Type_WArc)
			|| (ObjType == MachineObj_Type_WPolyline))
		{
			m_bDegenerate = true;
			Enable_OBJ_BTN_WidenDegen
		}
		else
		{
			Disable_OBJ_BTN_WidenCreat
		}
		Disable_OBJ_BTN_Route
	}
}

void CObjectProperty::UIRefreshObject()
{
	POSITION pos;
	int Index;
	CMachineObj_Comm* pObj;
	CMachinePara_Layer* pLayer;
	int ObjType;
	int nLayer = 0;
	ObjPoint point1, point2;
	m_SelectedObj.swap(vector<UINT>());
	int Count = m_PropertyList.GetSelectedCount();
	if (Count < 1)
	{
		//无选中
		m_LayerNameListBox.SetCurSel(-1);
		gPara_To_mPara();
		Disable_OBJ_BTN_UpAndDown
		Disable_OBJ_BTN_Delete
		Disable_OBJ_BTN_Edit
		Disable_OBJ_BTN_Group
		Disable_OBJ_BTN_DisGroup
		Disable_OBJ_BTN_Polyline
		Disable_OBJ_BTN_CombinePoly
		Disable_OBJ_BTN_ChangeLayer
		Disable_OBJ_Dot_Proty
		Disable_OBJ_Rise_By_Pass
		Disable_OBJ_BTN_FillCreat
		Disable_OBJ_BTN_WidenCreat
		Disable_OBJ_BTN_Route
	}
	//无选中 结束
	//else if (Count == 1)
	//{
	//	//选中1个
	//	pos = m_PropertyList.GetFirstSelectedItemPosition();
	//	while (pos)
	//	{
	//		Index = m_PropertyList.GetNextSelectedItem(pos);
	//	}
	//	if (Index < 0 || Index >= m_PropertyList.GetItemCount())
	//		return;
	//	m_SelectedObj.push_back(Index);
	//	UIRefreshObject(Index);
	//}
	////选中1个结束
	else
	{
		//有选中
		bool Flag_InSysLayer = false;
		bool Flag_SingleLayer = true;
		bool Flag_AllPoint = true;
		bool Flag_AllGroup = true;
		bool Flag_AllPolyline = true;
		bool Flag_AllEnPolyline = true;
		bool Flag_AllEnCombine = true;
		bool Flag_AllEnDirect = true;
		bool Flag_AllCircle = true;
		bool Flag_AllEnFill = true;
		bool Flag_AllFill = true;
		bool Flag_AllEnWiden = true;
		bool Flag_AllWiden = true;

		pos = m_PropertyList.GetFirstSelectedItemPosition();
		Index = m_PropertyList.GetNextSelectedItem(pos);
		pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
		int nLayer_Old = pObj->m_ObjByLayer;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
			if (Index < 0 || Index >= m_PropertyList.GetItemCount())
				break;
			m_SelectedObj.push_back(Index);
			pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
			nLayer = pObj->m_ObjByLayer;
			if ((nLayer < LayerNum_Default) && (nLayer != LayerNum_Group))
				Flag_InSysLayer = true;
			if (nLayer != nLayer_Old)
				Flag_SingleLayer = false;
			ObjType = pObj->GetObjType();
			switch (ObjType)
			{
			case MachineObj_Type_Point:
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_Line:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_Circle:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;	//**true
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_Arc:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_Ellipse:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
//				Flag_AllCircle = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;	//**
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_ArcEll:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;	//**
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_TiltEllipse:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;		//**
				Flag_AllFill = false;
				Flag_AllEnWiden = false;	//**
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_Polyline:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllCircle = false;
				Flag_AllEnPolyline = false;
				point1 = pObj->GetObjStart(pObj);
				point2 = pObj->GetObjEnd(pObj);
				if ((abs(point1.x - point2.x) > Zero) || (abs(point1.y - point2.y) > Zero))
					Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_Group:
				Flag_AllPoint = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;
				Flag_AllWiden = false;
				break;
			case MachineObj_Type_WLine:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;
				break;
			case MachineObj_Type_WArc:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;
				break;
			case MachineObj_Type_WPolyline:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;
				break;
			case MachineObj_Type_FillPolyline:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllEnWiden = false;
				Flag_AllWiden = false;
				break;
			default:
				Flag_AllPoint = false;
				Flag_AllGroup = false;
				Flag_AllPolyline = false;
				Flag_AllEnPolyline = false;
				Flag_AllEnCombine = false;
				Flag_AllEnDirect = false;
				Flag_AllCircle = false;
				Flag_AllEnFill = false;
				Flag_AllFill = false;
				Flag_AllEnWiden = false;
				Flag_AllWiden = false;
				break;
			}
		}

		if (Flag_SingleLayer)
		{
			pLayer = m_pObjList->GetLayerOfNumber(nLayer);
			if (nLayer < LayerNum_Default)
				m_LayerNameListBox.SetCurSel(nLayer);
			else
				m_LayerNameListBox.SetCurSel(nLayer - LayerNum_Group - 1);
			LayerPara_To_mPara(pLayer);
		}
		else
		{
			m_LayerNameListBox.SetCurSel(-1);
			gPara_To_mPara();
		}
		if (Flag_AllPoint)
		{
			Enable_OBJ_Dot_Proty
				m_WaitTime = ((CMachineObjPoint*)pObj)->m_MachineWaitTime;
		}
		else
		{
			Disable_OBJ_Dot_Proty
				m_WaitTime = gProcessWaitTime;
		}

		//*********
		if (Count == 1)
		{
			Enable_OBJ_BTN_UpAndDown
		}
		else
		{
			if (Flag_AllEnDirect && Flag_AllCircle)
			{
				Enable_OBJ_BTN_ReDirect
				Enable_OBJ_BTN_ReNode
			}
			else if (Flag_AllEnDirect)
			{
				Enable_OBJ_BTN_ReDirect
				Disable_OBJ_BTN_ReNode
			}
			else if (Flag_AllCircle)
			{
				Disable_OBJ_BTN_ReDirect
				Enable_OBJ_BTN_ReNode
			}
			else
			{
				Disable_OBJ_BTN_UpAndDown
			}
		}
		Enable_OBJ_BTN_Delete
		if (((Count == 1) && (ObjType != MachineObj_Type_Invaild))	//Group
			|| Flag_AllFill || Flag_AllWiden)
		{
			Enable_OBJ_BTN_Edit
		}
		else
		{
			Disable_OBJ_BTN_Edit
		}
		if (((Flag_InSysLayer && Flag_SingleLayer) || (!Flag_InSysLayer)) && (Count != 1))
		{
			Enable_OBJ_BTN_Group
		}
		else
		{
			Disable_OBJ_BTN_Group
		}
		if (Flag_AllGroup)
		{
			Enable_OBJ_BTN_DisGroup
		}
		else if (Flag_AllPolyline)
		{
			Enable_OBJ_BTN_BreakPolyline
		}
		else
		{
			Disable_OBJ_BTN_DisGroup
		}
		if (Flag_AllEnPolyline)
		{
			Enable_OBJ_BTN_Polyline
		}
		else
		{
			Disable_OBJ_BTN_Polyline
		}
		if (Flag_AllEnCombine && Flag_SingleLayer && (Count != 1))
		{
			Enable_OBJ_BTN_CombinePoly
		}
		else
		{
			Disable_OBJ_BTN_CombinePoly
		}
		Enable_OBJ_BTN_ChangeLayer;

		//********特殊操作
		if (Flag_AllEnFill)
		{
			m_bDegenerate = false;
			Enable_OBJ_BTN_FillCreat
		}
		else if (Flag_AllFill)
		{
			m_bDegenerate = true;
			Enable_OBJ_BTN_FillDestroy
		}
		else
		{
			Disable_OBJ_BTN_FillCreat
		}
		if (Flag_AllEnWiden)
		{
			m_bDegenerate = false;
			Enable_OBJ_BTN_WidenCreat
		}
		else if (Flag_AllWiden)
		{
			m_bDegenerate = true;
			Enable_OBJ_BTN_WidenDegen
		}
		else
		{
			Disable_OBJ_BTN_WidenCreat
		}
		if (Flag_InSysLayer || (Count == 1))
		{
			Disable_OBJ_BTN_Route
		}
		else
		{
			Enable_OBJ_BTN_Route
		}


	}
	//选中多个结束
}

void CObjectProperty::ClearAllObjSel()
{
	CMachineObj_Comm* pObj;
	int Count = m_ProtyListIndex.size();
	for (int i = 0; i < Count; i++)
	{
		pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[i]);
		pObj->m_bIsObjStatus &= ~IsObjSel;
	}
}

void CObjectProperty::ClearActiveLayerSel()
{
	CMachinePara_Layer* pLayer;
	byte status;
	int Count = m_pObjList->GetLayerCount();
	for (int i = 0; i < Count; i++)
	{
		pLayer = m_pObjList->GetLayerOfNumber(i);
		status = pLayer->m_bIsLayerStatus;
		if (((status & IsObjClosed) == 0) && ((status & IsObjLocked) == 0))
			pLayer->m_bIsLayerStatus &= ~IsObjSel;
	}
}

int CObjectProperty::FindProtyListIndex(int ObjListIndex)
{
	int Count = m_ProtyListIndex.size();
	for (int i = 0; i < Count; i++)
	{
		if (ObjListIndex == m_ProtyListIndex[i])
			return i;
	}
	return -1;
}

void CObjectProperty::SetExtenfPara()
{
	CObjectProtyDlg1 dlg;
	dlg.DoModal();
	return;
}

void CObjectProperty::SetFillPara()
{
	CObjectProtyDlg2 dlg;
	dlg.DoModal();
	return;

}

void CObjectProperty::EditPoint(CMachineObj_Comm* pObj)
{
	CMachineObjPoint* pPoint = (CMachineObjPoint*)pObj;
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 170, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("点坐标      X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 500, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 500, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pPoint->GetPoint();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SavePoint(CMachineObj_Comm* pObj)
{
	CMachineObjPoint* pPoint = (CMachineObjPoint*)pObj;
	if (UpdateData(TRUE))
	{
		pPoint->SetPoint(ObjPoint(m_dVar1, m_dVar2));
		m_pView->Invalidate();
	}
}

void CObjectProperty::EditLine(CMachineObj_Comm* pObj)
{
	CMachineObjLine* pLine = (CMachineObjLine*)pObj;
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 325, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("起点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 45, 460, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("终点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 459, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 215, 460, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 45, 480, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 479, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 215, 480, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 45, 520, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("中心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 519, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowPos(NULL, 215, 520, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 540, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->SetWindowPos(NULL, 130, 539, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 215, 540, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 100, 580, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("交换起终点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 630, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 630, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pLine->GetLineStart();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	point = pLine->GetLineEnd();
	m_dVar3 = point.x;
	m_dVar4 = point.y;
	ObjRect rect = pLine->GetObjBound();
	m_dVar5 = (rect.max_x + rect.min_x) / 2;
	m_dVar6 = (rect.max_y + rect.min_y) / 2;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::ExchangeLineStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjLine* pLine = (CMachineObjLine*)pObj;
	double dtemp1 = m_dVar1;
	double dtemp2 = m_dVar2;
	pLine->ExchangeStartAndEnd(pLine);
	m_dVar1 = m_dVar3;
	m_dVar2 = m_dVar4;
	m_dVar3 = dtemp1;
	m_dVar4 = dtemp2;
	UpdateData(FALSE);
	m_pView->Invalidate();
		
}

void CObjectProperty::SaveLineModify(CMachineObj_Comm* pObj)
{
	CMachineObjLine* pLine = (CMachineObjLine*)pObj;
	double dtemp1 = m_dVar5;
	double dtemp2 = m_dVar6;
	if (UpdateData(TRUE))
	{
		pLine->SetLine(ObjPoint(m_dVar1, m_dVar2), ObjPoint(m_dVar3, m_dVar4));
		pLine->MoveLine(m_dVar5 - dtemp1, m_dVar6 - dtemp2);
		ObjPoint point;
		point = pLine->GetLineStart();
		m_dVar1 = point.x;
		m_dVar2 = point.y;
		point = pLine->GetLineEnd();
		m_dVar3 = point.x;
		m_dVar4 = point.y;
		ObjRect rect = pLine->GetObjBound();
		m_dVar5 = (rect.max_x + rect.min_x) / 2;
		m_dVar6 = (rect.max_y + rect.min_y) / 2;
		m_Edit_pObj = pLine;
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
}

void CObjectProperty::EditCircle(CMachineObj_Comm* pObj)
{
	CMachineObjCircle* pCircle = (CMachineObjCircle*)pObj;
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 325, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("圆心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 45, 455, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("半径          R"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 454, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 215, 455, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 45, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("方向"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 180, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 45, 500, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("起点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 499, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowPos(NULL, 215, 500, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 520, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 519, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 215, 520, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->SetWindowPos(NULL, 50, 560, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->SetWindowText(_T("切换起点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 150, 560, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("换 向"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 630, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 630, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pCircle->GetCircleCenter();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	m_dVar3 = pCircle->GetCircleRadius();
	if (pCircle->GetCircleDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("顺时针"));
	point = pCircle->GetCircleStart();
	m_dVar4 = point.x;
	m_dVar5 = point.y;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveCircleModify(CMachineObj_Comm* pObj)
{
	CMachineObjCircle* pCircle = (CMachineObjCircle*)pObj;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	double dTemp3 = m_dVar3;
	double dTemp4 = m_dVar4;
	double dTemp5 = m_dVar5;
	if (UpdateData(TRUE))
	{
		if (((abs(dTemp1-m_dVar1)>Zero) || (abs(dTemp2-m_dVar2)>Zero) || (abs(dTemp3-m_dVar3)>Zero))
			&& ((abs(dTemp4-m_dVar4)>Zero) || (abs(dTemp5-m_dVar5)>Zero)))
		{
			MessageBox(_T("这些参数不容许同时修改!"));
			m_dVar1 = dTemp1;
			m_dVar2 = dTemp2;
			m_dVar3 = dTemp3;
			m_dVar4 = dTemp4;
			m_dVar5 = dTemp5;
		}
		else
		{
			pCircle->SetCircleRadius(m_dVar3);
			double x, y;
			x = m_dVar1 - dTemp1 + m_dVar4 - dTemp4;
			if (abs(x) < Zero)
				x = 0;
			y = m_dVar2 - dTemp2 + m_dVar5 - dTemp5;
			if (abs(y) < Zero)
				y = 0;
			pCircle->MoveCircle(x, y);
		}
		ObjPoint point = pCircle->GetCircleCenter();
		m_dVar1 = point.x;
		m_dVar2 = point.y;
		pCircle->GetCircleStart();
		m_dVar4 = point.x;
		m_dVar5 = point.y;
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
}

void CObjectProperty::ExchangeCircleStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjCircle* pCircle = (CMachineObjCircle*)pObj;
	pCircle->ExchangeDirection();
	if (pCircle->GetCircleDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("顺时针"));
	m_pView->Invalidate();
}

void CObjectProperty::ChangeCircleNode(CMachineObj_Comm* pObj)
{
	CMachineObjCircle* pCircle = (CMachineObjCircle*)pObj;
	char StartNum = pCircle->GetCircleStartNum();
	StartNum++;
	if (StartNum > 3)
		StartNum = 0;
	pCircle->SetCircleStart(StartNum);
	ObjPoint point = pCircle->GetCircleStart();
	m_dVar4 = point.x;
	m_dVar5 = point.y;
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::EditArc(CMachineObj_Comm* pObj)
{
	CMachineObjArc* pArc = (CMachineObjArc*)pObj;
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 360, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("圆心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 45, 455, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("圆弧半径    R"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 454, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 215, 455, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 45, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("起始角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 474, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 215, 475, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 45, 495, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("终止角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 494, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowPos(NULL, 215, 495, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 515, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("方向"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 180, 515, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowPos(NULL, 45, 540, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowTextW(_T("圆弧起点  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->SetWindowPos(NULL, 130, 539, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowPos(NULL, 215, 540, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowPos(NULL, 45, 560, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->SetWindowPos(NULL, 130, 559, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowPos(NULL, 215, 560, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->SetWindowPos(NULL, 45, 580, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->SetWindowTextW(_T("圆弧终点  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->SetWindowPos(NULL, 130, 579, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->SetWindowPos(NULL, 215, 580, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->SetWindowPos(NULL, 45, 600, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->SetWindowPos(NULL, 130, 599, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->SetWindowPos(NULL, 215, 600, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 100, 640, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("交换起终点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 680, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 680, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pArc->GetArcCenter();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	m_dVar3 = pArc->GetArcRadius();
	m_dVar4 = pArc->GetStartAngle();
	m_dVar5 = pArc->GetEndAngle();
	if (pArc->GetArcDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("顺时针"));
	point = pArc->GetArcStart();
	m_dVar6 = point.x;
	m_dVar7 = point.y;
	point = pArc->GetArcEnd();
	m_dVar8 = point.x;
	m_dVar9 = point.y;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveArcModify(CMachineObj_Comm* pObj)
{
	CMachineObjArc* pArc = (CMachineObjArc*)pObj;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	double dTemp3 = m_dVar3;
	double dTemp4 = m_dVar4;
	double dTemp5 = m_dVar5;
	double dTemp6 = m_dVar6;
	double dTemp7 = m_dVar7;
	double dTemp8 = m_dVar8;
	double dTemp9 = m_dVar9;
	if (UpdateData(TRUE))
	{
		if (((abs(dTemp1-m_dVar1)>Zero) || (abs(dTemp2-m_dVar2)>Zero) || (abs(dTemp3-m_dVar3)>Zero)
			|| (abs(dTemp4-m_dVar4)>Zero) || (abs(dTemp5-m_dVar5)>Zero))
			&& ((abs(dTemp6-m_dVar6)>Zero) || (abs(dTemp7-m_dVar7)>Zero))
			&& ((abs(dTemp8-m_dVar8)>Zero) || (abs(dTemp9-m_dVar9)>Zero)))
		{
			MessageBox(_T("这些参数不容许同时修改!"));
			m_dVar1 = dTemp1;
			m_dVar2 = dTemp2;
			m_dVar3 = dTemp3;
			m_dVar4 = dTemp4;
			m_dVar5 = dTemp5;
			m_dVar6 = dTemp6;
			m_dVar7 = dTemp7;
			m_dVar8 = dTemp8;
			m_dVar9 = dTemp9;
		}
		else
		{
			pArc->SetArcRadius(m_dVar3);
			pArc->SetStartAndEndAngle(m_dVar4, m_dVar5, pArc->GetArcDir());
			double x, y;
			x = m_dVar1 - dTemp1 + m_dVar6 - dTemp6 + m_dVar8 - dTemp8;
			if (abs(x) < Zero)
				x = 0;
			y = m_dVar2 - dTemp2 + m_dVar7 - dTemp7 + m_dVar9 - dTemp9;
			if (abs(y) < Zero)
				y = 0;
			pArc->MoveArc(x, y);
			ObjPoint point;
			point = pArc->GetArcCenter();
			m_dVar1 = point.x;
			m_dVar2 = point.y;
			if (pArc->GetArcDir() == CCW)
				GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("逆时针"));
			else
				GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("顺时针"));
			point = pArc->GetArcStart();
			m_dVar6 = point.x;
			m_dVar7 = point.y;
			point = pArc->GetArcEnd();
			m_dVar8 = point.x;
			m_dVar9 = point.y;
		}
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
}

void CObjectProperty::ExchangeArcStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjArc* pArc = (CMachineObjArc*)pObj;
	double dtemp1 = m_dVar4;
	pArc->ExchangeStartAndEnd(pArc);
	m_dVar4 = m_dVar5;
	m_dVar5 = dtemp1;
	dtemp1 = m_dVar6;
	m_dVar6 = m_dVar8;
	m_dVar8 = dtemp1;
	dtemp1 = m_dVar7;
	m_dVar7 = m_dVar9;
	m_dVar9 = dtemp1;
	if (pArc->GetArcDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("顺时针"));
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::EditEllipse(CMachineObj_Comm* pObj)
{
	CMachineObjEllipse* pEllipse = (CMachineObjEllipse*)pObj;
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 325, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("圆心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 45, 455, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("长轴(X)   a"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 454, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 215, 455, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 45, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("短轴(Y)   b"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 474, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 45, 495, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("方向"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 180, 495, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 520, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("起点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 519, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 215, 520, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowPos(NULL, 45, 540, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->SetWindowPos(NULL, 130, 539, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowPos(NULL, 215, 540, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->SetWindowPos(NULL, 50, 580, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->SetWindowText(_T("切换起点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 150, 580, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("换 向"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 630, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 630, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pEllipse->GetEllipseCenter();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	m_dVar3 = pEllipse->GetEllipseXRadius();
	m_dVar4 = pEllipse->GetEllipseYRadius();
	if (pEllipse->GetEllipseDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("顺时针"));
	point = pEllipse->GetEllipseStart();
	m_dVar5 = point.x;
	m_dVar6 = point.y;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveEllipseModify(CMachineObj_Comm* pObj)
{
	CMachineObjEllipse* pEllipse = (CMachineObjEllipse*)pObj;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	double dTemp3 = m_dVar3;
	double dTemp4 = m_dVar4;
	double dTemp5 = m_dVar5;
	double dTemp6 = m_dVar6;
	if (UpdateData(TRUE))
	{
		if (((abs(dTemp1-m_dVar1)>Zero) || (abs(dTemp2-m_dVar2)>Zero) || (abs(dTemp3-m_dVar3)>Zero) || (abs(dTemp4-m_dVar4)>Zero))
			&& ((abs(dTemp5-m_dVar5)>Zero) || (abs(dTemp6-m_dVar6)>Zero)))
		{
			MessageBox(_T("这些参数不容许同时修改!"));
			m_dVar1 = dTemp1;
			m_dVar2 = dTemp2;
			m_dVar3 = dTemp3;
			m_dVar4 = dTemp4;
			m_dVar5 = dTemp5;
			m_dVar6 = dTemp6;
		}
		else
		{
			pEllipse->SetEllipseXradius(m_dVar3);
			pEllipse->SetEllipseRatio(m_dVar4 / m_dVar3);
			double x, y;
			x = m_dVar1 - dTemp1 + m_dVar5 - dTemp5;
			if (abs(x) < Zero)
				x = 0;
			y = m_dVar2 - dTemp2 + m_dVar6 - dTemp6;
			if (abs(y) < Zero)
				y = 0;
			pEllipse->MoveEllipse(x, y);
			ObjPoint point = pEllipse->GetEllipseCenter();
			m_dVar1 = point.x;
			m_dVar2 = point.y;
			point = pEllipse->GetEllipseStart();
			m_dVar5 = point.x;
			m_dVar6 = point.y;
		}
		UpdateData(FALSE);
		m_pView->Invalidate();
	}


}

void CObjectProperty::ExchangeEllipseStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjEllipse* pEllipse = (CMachineObjEllipse*)pObj;
	pEllipse->ExchangeDirection();
	if (pEllipse->GetEllipseDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("顺时针"));
	m_pView->Invalidate();
}

void CObjectProperty::ChangeEllipseNode(CMachineObj_Comm* pObj)
{
	CMachineObjEllipse* pEllipse = (CMachineObjEllipse*)pObj;
	char StartNum = pEllipse->GetEllipseStartNum();
	StartNum++;
	if (StartNum > 3)
		StartNum = 0;
	pEllipse->SetEllipseStart(StartNum);
	ObjPoint point = pEllipse->GetEllipseStart();
	m_dVar5 = point.x;
	m_dVar6 = point.y;
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::EditArcEll(CMachineObj_Comm* pObj)
{
	CMachineObjArcEll* pArcEll = (CMachineObjArcEll*)pObj;
	UnDisp_Machine_Property
		GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 370, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("圆心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 45, 455, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("长轴(X)    a"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 454, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 215, 455, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 45, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("短轴(Y)    b"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 474, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 215, 475, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 45, 495, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("起始角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 494, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowPos(NULL, 215, 495, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 515, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("终止角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->SetWindowPos(NULL, 130, 514, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 215, 515, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowPos(NULL, 45, 535, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowTextW(_T("方向"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowPos(NULL, 180, 535, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowPos(NULL, 45, 560, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowTextW(_T("弧起点     X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->SetWindowPos(NULL, 130, 559, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowPos(NULL, 215, 560, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->SetWindowPos(NULL, 45, 580, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->SetWindowTextW(_T("                 Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->SetWindowPos(NULL, 130, 579, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->SetWindowPos(NULL, 215, 580, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->SetWindowPos(NULL, 45, 600, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->SetWindowTextW(_T("弧终点     X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->SetWindowPos(NULL, 130, 599, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->SetWindowPos(NULL, 215, 600, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->SetWindowPos(NULL, 45, 620, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->SetWindowTextW(_T("                 Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT23)->SetWindowPos(NULL, 130, 619, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT23)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->SetWindowPos(NULL, 215, 620, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 100, 660, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("交换起终点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 700, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 700, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pArcEll->GetEllipseCenter();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	m_dVar3 = pArcEll->GetEllipseXRadius();
	m_dVar4 = pArcEll->GetEllipseYRadius();
	m_dVar5 = pArcEll->GetStartRadian() * 180 / M_PI;
	m_dVar6 = pArcEll->GetEndRadian() * 180 / M_PI;
	if (pArcEll->GetArcDir()==CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("顺时针"));
	point = pArcEll->GetArcStart();
	m_dVar7 = point.x;
	m_dVar8 = point.y;
	point = pArcEll->GetArcEnd();
	m_dVar9 = point.x;
	m_dVar10 = point.y;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveArcEllModify(CMachineObj_Comm* pObj)
{
	CMachineObjArcEll* pArcEll = (CMachineObjArcEll*)pObj;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	double dTemp3 = m_dVar3;
	double dTemp4 = m_dVar4;
	double dTemp5 = m_dVar5;
	double dTemp6 = m_dVar6;
	double dTemp7 = m_dVar7;
	double dTemp8 = m_dVar8;
	double dTemp9 = m_dVar9;
	double dTemp10 = m_dVar10;
	if (UpdateData(TRUE))
	{
		if (((abs(dTemp1 - m_dVar1)>Zero) || (abs(dTemp2 - m_dVar2)>Zero) || (abs(dTemp3 - m_dVar3)>Zero)
			|| (abs(dTemp4 - m_dVar4)>Zero) || (abs(dTemp5 - m_dVar5)>Zero) || (abs(dTemp6 - m_dVar6)>Zero))
			&& ((abs(dTemp7 - m_dVar7)>Zero) || (abs(dTemp8 - m_dVar8)>Zero))
			&& ((abs(dTemp9 - m_dVar9)>Zero) || (abs(dTemp10 - m_dVar10)>Zero)))
		{
			MessageBox(_T("这些参数不容许同时修改!"));
			m_dVar1 = dTemp1;
			m_dVar2 = dTemp2;
			m_dVar3 = dTemp3;
			m_dVar4 = dTemp4;
			m_dVar5 = dTemp5;
			m_dVar6 = dTemp6;
			m_dVar7 = dTemp7;
			m_dVar8 = dTemp8;
			m_dVar9 = dTemp9;
			m_dVar10 = dTemp10;
		}
		else
		{
			pArcEll->SetArcEllXradius(m_dVar3);
			pArcEll->SetArcEllRatio(m_dVar4 / m_dVar3);
			pArcEll->SetStartAndEndRadian(m_dVar5 / 180 * M_PI, m_dVar6 / 180 * M_PI, pArcEll->GetArcDir());
			double x, y;
			x = m_dVar1 - dTemp1 + m_dVar7 - dTemp7 + m_dVar9 - dTemp9;
			if (abs(x) < Zero)
				x = 0;
			y = m_dVar2 - dTemp2 + m_dVar8 - dTemp8 + m_dVar10 - dTemp10;
			if (abs(y) < Zero)
				y = 0;
			pArcEll->MoveArcEll(x, y);
			ObjPoint point;
			point = pArcEll->GetEllipseCenter();
			m_dVar1 = point.x;
			m_dVar2 = point.y;
			if (pArcEll->GetArcDir() == CCW)
				GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("逆时针"));
			else
				GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("顺时针"));
			point = pArcEll->GetArcStart();
			m_dVar7 = point.x;
			m_dVar8 = point.y;
			point = pArcEll->GetArcEnd();
			m_dVar9 = point.x;
			m_dVar10 = point.y;
		}
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
}

void CObjectProperty::ExchangeArcEllStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjArcEll* pArcEll = (CMachineObjArcEll*)pObj;
	pArcEll->ExchangeStartAndEnd(pArcEll);
	m_dVar5 = pArcEll->GetStartRadian() * 180 / M_PI;
	m_dVar6 = pArcEll->GetEndRadian() * 180 / M_PI;
	if (pArcEll->GetArcDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("顺时针"));
	ObjPoint point;
	point = pArcEll->GetArcStart();
	m_dVar7 = point.x;
	m_dVar8 = point.y;
	point = pArcEll->GetArcEnd();
	m_dVar9 = point.x;
	m_dVar10 = point.y;
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::EditTiltEllipse(CMachineObj_Comm* pObj)
{
	CMachineObjTiltEllipse* pTiltEllipse = (CMachineObjTiltEllipse*)pObj;
	UnDisp_Machine_Property
		GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 390, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("圆心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 45, 455, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("长轴(X)    a"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 454, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 215, 455, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 45, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("短轴(Y)    b"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 474, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 215, 475, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 45, 495, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("起始角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 494, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowPos(NULL, 215, 495, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 515, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("终止角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->SetWindowPos(NULL, 130, 514, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 215, 515, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowPos(NULL, 45, 535, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowTextW(_T("旋转角"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->SetWindowPos(NULL, 130, 534, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowPos(NULL, 215, 535, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowPos(NULL, 45, 555, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowTextW(_T("方向"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowPos(NULL, 180, 555, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC43)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->SetWindowPos(NULL, 45, 580, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->SetWindowTextW(_T("弧起点     X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC44)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->SetWindowPos(NULL, 130, 579, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT21)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->SetWindowPos(NULL, 215, 580, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC45)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->SetWindowPos(NULL, 45, 600, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->SetWindowTextW(_T("                 Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC46)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->SetWindowPos(NULL, 130, 599, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT22)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->SetWindowPos(NULL, 215, 600, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC47)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->SetWindowPos(NULL, 45, 620, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->SetWindowTextW(_T("弧终点     X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC48)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT23)->SetWindowPos(NULL, 130, 619, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT23)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->SetWindowPos(NULL, 215, 620, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC49)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC50)->SetWindowPos(NULL, 45, 640, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC50)->SetWindowTextW(_T("                 Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC50)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT24)->SetWindowPos(NULL, 130, 639, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT24)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC51)->SetWindowPos(NULL, 215, 640, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC51)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC51)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 100, 680, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("交换起终点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 720, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 720, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjPoint point;
	point = pTiltEllipse->GetTiltEllipseCenter();
	m_dVar1 = point.x;
	m_dVar2 = point.y;
	m_dVar3 = pTiltEllipse->GetTiltEllipseXRadius();
	m_dVar4 = pTiltEllipse->GetTiltEllipseYRadius();
	m_dVar5 = pTiltEllipse->GetStartRadian() * 180 / M_PI;
	m_dVar6 = pTiltEllipse->GetEndRadian() * 180 / M_PI;
	m_dVar7 = pTiltEllipse->GetRotateRadian() * 180 / M_PI;
	if (pTiltEllipse->GetArcDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("顺时针"));
	point = pTiltEllipse->GetTiltEllipseStart();
	m_dVar8 = point.x;
	m_dVar9 = point.y;
	point = pTiltEllipse->GetTiltEllipseEnd();
	m_dVar10 = point.x;
	m_dVar11 = point.y;
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveTiltEllipseModify(CMachineObj_Comm* pObj)
{
	CMachineObjTiltEllipse* pTiltEllipse = (CMachineObjTiltEllipse*)pObj;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	double dTemp3 = m_dVar3;
	double dTemp4 = m_dVar4;
	double dTemp5 = m_dVar5;
	double dTemp6 = m_dVar6;
	double dTemp7 = m_dVar7;
	double dTemp8 = m_dVar8;
	double dTemp9 = m_dVar9;
	double dTemp10 = m_dVar10;
	double dTemp11 = m_dVar11;
	if (UpdateData(TRUE))
	{
		if (((abs(dTemp1 - m_dVar1) > Zero) || (abs(dTemp2 - m_dVar2) > Zero) || (abs(dTemp3 - m_dVar3) > Zero)
			|| (abs(dTemp4 - m_dVar4) > Zero) || (abs(dTemp5 - m_dVar5) > Zero) || (abs(dTemp6 - m_dVar6) > Zero)
			|| (abs(dTemp7 - m_dVar7) > Zero))
			&& ((abs(dTemp8 - m_dVar8) > Zero) || (abs(dTemp9 - m_dVar9) > Zero))
			&& ((abs(dTemp10 - m_dVar10) > Zero) || (abs(dTemp11 - m_dVar11) > Zero)))
		{
			MessageBox(_T("这些参数不容许同时修改!"));
			m_dVar1 = dTemp1;
			m_dVar2 = dTemp2;
			m_dVar3 = dTemp3;
			m_dVar4 = dTemp4;
			m_dVar5 = dTemp5;
			m_dVar6 = dTemp6;
			m_dVar7 = dTemp7;
			m_dVar8 = dTemp8;
			m_dVar9 = dTemp9;
			m_dVar10 = dTemp10;
			m_dVar11 = dTemp11;
		}
		else
		{
			pTiltEllipse->SetTiltEllipseXRadius(m_dVar3);
			pTiltEllipse->SetTiltEllipseRatio(m_dVar4 / m_dVar3);
			pTiltEllipse->SetStartAndEndRadian(m_dVar5 / 180 * M_PI, m_dVar6 / 180 * M_PI, pTiltEllipse->GetArcDir());
			pTiltEllipse->SetRotateRadian(m_dVar7 / 180 * M_PI);
			double x, y;
			x = m_dVar1 - dTemp1 + m_dVar8 - dTemp8 + m_dVar10 - dTemp10;
			if (abs(x) < Zero)
				x = 0;
			y = m_dVar2 - dTemp2 + m_dVar9 - dTemp9 + m_dVar11 - dTemp11;
			if (abs(y) < Zero)
				y = 0;
			pTiltEllipse->MoveTileEllipse(x, y);
			ObjPoint point;
			point = pTiltEllipse->GetTiltEllipseCenter();
			m_dVar1 = point.x;
			m_dVar2 = point.y;
			if (pTiltEllipse->GetArcDir() == CCW)
				GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("逆时针"));
			else
				GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("顺时针"));
			point = pTiltEllipse->GetTiltEllipseStart();
			m_dVar8 = point.x;
			m_dVar9 = point.y;
			point = pTiltEllipse->GetTiltEllipseEnd();
			m_dVar10 = point.x;
			m_dVar11 = point.y;
		}
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
}

void CObjectProperty::ExchangeTiltEllipseStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjTiltEllipse* pTiltEllipse = (CMachineObjTiltEllipse*)pObj;
	pTiltEllipse->ExchangeStartAndEnd(pTiltEllipse);
	m_dVar5 = pTiltEllipse->GetStartRadian() * 180 / M_PI;
	m_dVar6 = pTiltEllipse->GetEndRadian() * 180 / M_PI;
	if (pTiltEllipse->GetArcDir() == CCW)
		GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("逆时针"));
	else
		GetDlgItem(IDC_OBJ_PROTY_STATIC43)->SetWindowTextW(_T("顺时针"));
	ObjPoint point;
	point = pTiltEllipse->GetTiltEllipseStart();
	m_dVar8 = point.x;
	m_dVar9 = point.y;
	point = pTiltEllipse->GetTiltEllipseEnd();
	m_dVar10 = point.x;
	m_dVar11 = point.y;
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::EditPolyline(CMachineObj_Comm* pObj)
{
	CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
	UnDisp_Machine_Property
		GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 350, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	CString str;
	str.Format(_T("%d"), pPolyline->GetPolylineVertexCount());
	str = _T("节点数:  ") + str;
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 410, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(str);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("起点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 45, 455, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 454, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 215, 455, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 45, 475, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("终点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 130, 474, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 215, 475, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 45, 495, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->SetWindowPos(NULL, 130, 494, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowPos(NULL, 215, 495, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC36)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowPos(NULL, 50, 525, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->SetWindowText(_T("交换起终点"));
	GetDlgItem(IDC_OBJ_PROTY_BTN15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->SetWindowPos(NULL, 150, 525, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->SetWindowText(_T("闭合多段线"));
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->ShowWindow(SW_SHOW);
	str.Format(_T("%d"), m_SelNode);
	str = _T("当前节点:  ") + str;
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowPos(NULL, 45, 570, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(str);
	GetDlgItem(IDC_OBJ_PROTY_STATIC37)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN19)->SetWindowPos(NULL, 150, 567, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN19)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN20)->SetWindowPos(NULL, 185, 567, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN20)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN20)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowPos(NULL, 45, 595, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->SetWindowTextW(_T("节点坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC38)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->SetWindowPos(NULL, 130, 594, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT18)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowPos(NULL, 215, 595, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC39)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowPos(NULL, 45, 615, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC40)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->SetWindowPos(NULL, 130, 614, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT19)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowPos(NULL, 215, 615, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC41)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowPos(NULL, 45, 635, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->SetWindowTextW(_T("节点曲度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC42)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->SetWindowPos(NULL, 130, 635, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT20)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 680, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 680, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjVPoint vpoint;
	vpoint = pPolyline->GetPolylineStart();
	m_dVar1 = vpoint.x;
	m_dVar2 = vpoint.y;
	vpoint = pPolyline->GetPolylineEnd();
	m_dVar3 = vpoint.x;
	m_dVar4 = vpoint.y;
	if (abs(m_dVar1 - m_dVar3) < Zero && abs(m_dVar2 - m_dVar4) < Zero)
		GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(FALSE);
	else
		GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(TRUE);
	vpoint = pPolyline->GetPolylinePoint(m_SelNode);
	m_dVar5 = vpoint.x;
	m_dVar6 = vpoint.y;
	m_dVar7 = vpoint.convexity;
	m_pView->m_bObjNodeDisp = true;
	m_pView->m_NodePoint.x = m_dVar5;
	m_pView->m_NodePoint.y = m_dVar6;
	m_pView->Invalidate();
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SavePolylineModify(CMachineObj_Comm* pObj)
{
	CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
	ObjVPoint vpoint;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	double dTemp3 = m_dVar3;
	double dTemp4 = m_dVar4;
	double dTemp5 = m_dVar5;
	double dTemp6 = m_dVar6;
	double dTemp7 = m_dVar7;
	if (UpdateData(TRUE))
	{
		if (((abs(dTemp1 - m_dVar1)>Zero) || (abs(dTemp2 - m_dVar2)>Zero))
			&& ((abs(dTemp3 - m_dVar3)>Zero) || (abs(dTemp4 - m_dVar4)>Zero))
			&& ((abs(dTemp5 - m_dVar5)>Zero) || (abs(dTemp6 - m_dVar6)>Zero) || (abs(dTemp7 - m_dVar7)>Zero)))
		{
			MessageBox(_T("这些参数不容许同时修改!"));
			m_dVar1 = dTemp1;
			m_dVar2 = dTemp2;
			m_dVar3 = dTemp3;
			m_dVar4 = dTemp4;
			m_dVar5 = dTemp5;
			m_dVar6 = dTemp6;
			m_dVar7 = dTemp7;
		}
		else
		{
			vpoint.x = m_dVar5;
			vpoint.y = m_dVar6;
			vpoint.convexity = m_dVar7;
			if ((abs(dTemp5 - m_dVar5)>Zero) || (abs(dTemp6 - m_dVar6)>Zero) || (abs(dTemp7 - m_dVar7)>Zero))
				pPolyline->ModifyPolylineVpoint(vpoint, m_SelNode);
			double x, y;
			x = m_dVar1 - dTemp1 + m_dVar3 - dTemp3;
			if (abs(x) < Zero)
				x = 0;
			y = m_dVar2 - dTemp2 + m_dVar4 - dTemp4;
			if (abs(y) < Zero)
				y = 0;
			pPolyline->MovePolyline(x, y);
		}
		vpoint = pPolyline->GetPolylineStart();
		m_dVar1 = vpoint.x;
		m_dVar2 = vpoint.y;
		vpoint = pPolyline->GetPolylineEnd();
		m_dVar3 = vpoint.x;
		m_dVar4 = vpoint.y;
		if ((m_dVar1 == m_dVar3) && (m_dVar2 == m_dVar4))
			GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(FALSE);
		else
			GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(TRUE);
		vpoint = pPolyline->GetPolylinePoint(m_SelNode);
		m_dVar5 = vpoint.x;
		m_dVar6 = vpoint.y;
		m_dVar7 = vpoint.convexity;
		m_pView->m_NodePoint.x = m_dVar5;
		m_pView->m_NodePoint.y = m_dVar6;
		m_pView->Invalidate();
		UpdateData(FALSE);
	}
}

void CObjectProperty::LastNodePolyline(CMachineObj_Comm* pObj)
{
	CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
	if (m_SelNode > 0)
	{
		m_SelNode--;
		CString str;
		str.Format(_T("%d"), m_SelNode);
		str = _T("当前节点:  ") + str;
		GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(str);
		ObjVPoint vpoint = pPolyline->GetPolylinePoint(m_SelNode);
		m_dVar5 = vpoint.x;
		m_dVar6 = vpoint.y;
		m_dVar7 = vpoint.convexity;
		m_pView->m_NodePoint.x = m_dVar5;
		m_pView->m_NodePoint.y = m_dVar6;
		m_pView->Invalidate();
		UpdateData(FALSE);
	}
}

void CObjectProperty::NextNodePolyline(CMachineObj_Comm* pObj)
{
	CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
	if (m_SelNode < (pPolyline->GetPolylineVertexCount() - 1))
	{
		m_SelNode++;
		CString str;
		str.Format(_T("%d"), m_SelNode);
		str = _T("当前节点:  ") + str;
		GetDlgItem(IDC_OBJ_PROTY_STATIC37)->SetWindowTextW(str);
		ObjVPoint vpoint = pPolyline->GetPolylinePoint(m_SelNode);
		m_dVar5 = vpoint.x;
		m_dVar6 = vpoint.y;
		m_dVar7 = vpoint.convexity;
		m_pView->m_NodePoint.x = m_dVar5;
		m_pView->m_NodePoint.y = m_dVar6;
		m_pView->Invalidate();
		UpdateData(FALSE);
	}
}

void CObjectProperty::ExchangePolylineStartAndEnd(CMachineObj_Comm* pObj)
{
	CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
	pPolyline->ExchangeStartAndEnd(pPolyline);
	ObjVPoint vpoint;
	vpoint = pPolyline->GetPolylineStart();
	m_dVar1 = vpoint.x;
	m_dVar2 = vpoint.y;
	vpoint = pPolyline->GetPolylineEnd();
	m_dVar3 = vpoint.x;
	m_dVar4 = vpoint.y;
	vpoint = pPolyline->GetPolylinePoint(m_SelNode);
	m_dVar5 = vpoint.x;
	m_dVar6 = vpoint.y;
	m_dVar7 = vpoint.convexity;
	m_pView->m_NodePoint.x = m_dVar5;
	m_pView->m_NodePoint.y = m_dVar6;
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::ClosePolyline(CMachineObj_Comm* pObj)
{
	CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
	pPolyline->ClosePolylineEndToStart();
	m_dVar3 = m_dVar1;
	m_dVar4 = m_dVar2;
	CString str;
	str.Format(_T("%d"), pPolyline->GetPolylineVertexCount() - 1);
	str = _T("节点数:  ") + str;
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(str);
	GetDlgItem(IDC_OBJ_PROTY_BTN18)->EnableWindow(FALSE);
	UpdateData(FALSE);
	m_pView->Invalidate();
}

void CObjectProperty::EditGroup(CMachineObj_Comm* pObj)
{
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("对象几何属性"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 180, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("中心坐标  X"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 130, 414, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 215, 415, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 45, 435, 85, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("                  Y"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 130, 434, 80, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 215, 435, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 480, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 480, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	ObjRect rect = pGroup->GetObjBound();
	m_dVar1 = (rect.max_x + rect.min_x) / 2;
	m_dVar2 = (rect.max_y + rect.min_y) / 2;
	m_pView->m_bObjNodeDisp = true;
	m_pView->m_NodePoint = ObjPoint(m_dVar1, m_dVar2);
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveGroupModify(CMachineObj_Comm* pObj)
{
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	double dTemp1 = m_dVar1;
	double dTemp2 = m_dVar2;
	if (UpdateData(TRUE))
	{
		double x = m_dVar1 - dTemp1;
		double y = m_dVar2 - dTemp2;
		if (abs(x) > Zero || abs(y) > Zero)
		{
			pGroup->MoveGroup(x, y);
			ObjRect rect = pGroup->GetObjBound();
			m_dVar1 = (rect.max_x + rect.min_x) / 2;
			m_dVar2 = (rect.max_y + rect.min_y) / 2;
			m_pView->m_bObjNodeDisp = true;
			m_pView->m_NodePoint = ObjPoint(m_dVar1, m_dVar2);
			UpdateData(FALSE);
			m_pView->Invalidate();
		}
	}
}

void CObjectProperty::EditWiden(CMachineObj_Comm* pObj)
{
	int nCount = m_SelectedObj.size();
	CString str;
	if (nCount > 1)
	{
		str.Format(_T("%d"), nCount);
		str = _T("展宽线参数(") + str + _T(")");
	}
	else
		str = _T("展宽线参数");
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(str);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 30, 375, 210, 150, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 45, 415, 120, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("展宽线数(必须为奇数)"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 170, 414, 30, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 45, 440, 100, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("展宽线间距"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 150, 439, 50, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 210, 440, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 480, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 480, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);
	int nType = pObj->GetObjType();
	if (nType == MachineObj_Type_WLine)
	{
		CMachineObjWLine* pWLine = (CMachineObjWLine*)pObj;
		m_dVar1 = (double)pWLine->GetDupNumber() * 2 + 1;
		m_dVar2 = (double)pWLine->GetGapDistance();
	}
	else if (nType == MachineObj_Type_WArc)
	{
		CMachineObjWArc* pWArc = (CMachineObjWArc*)pObj;
		m_dVar1 = (double)pWArc->GetDupNumber() * 2 + 1;
		m_dVar2 = (double)pWArc->GetGapDistance();
	}
	else if (nType == MachineObj_Type_WPolyline)
	{
		CMachineObjWPolyline* pWPolyline = (CMachineObjWPolyline*)pObj;
		m_dVar1 = (double)pWPolyline->GetDupNumber() * 2 + 1;
		m_dVar2 = (double)pWPolyline->GetGapDistance();
	}
	else
	{
		m_dVar1 = 1;
		m_dVar2 = 0;
	}
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveWiden()
{
	int nCount = m_SelectedObj.size();
	if (UpdateData(TRUE))
	{
		UINT n = (UINT)m_dVar1;
		if ((n & 1) == 0)
		{
			MessageBox(_T("线数必须为奇数"));
		}
		else
		{
			n = UINT(n / 2);
			for (int i = 0; i < nCount; i++)
			{
				int nIndex = m_ProtyListIndex[m_SelectedObj[i]];
				CMachineObj_Comm* pObj1 = m_pObjList->GetObjAtIndex(nIndex);
				int nType = pObj1->GetObjType();
				if (nType == MachineObj_Type_WLine)
				{
					CMachineObjWLine* pWLine = (CMachineObjWLine*)pObj1;
					pWLine->ReCreatWLine(n, (float)m_dVar2);
				}
				else if (nType == MachineObj_Type_WArc)
				{
					CMachineObjWArc* pWArc = (CMachineObjWArc*)pObj1;
					pWArc->ReCreatWArc(n, (float)m_dVar2);
				}
				else if (nType == MachineObj_Type_WPolyline)
				{
					CMachineObjWPolyline* pWPolyline = (CMachineObjWPolyline*)pObj1;
					pWPolyline->ReCreatWPolyline(n, (float)m_dVar2);
				}
			}
			m_pView->Invalidate();
		}
	}
}

void CObjectProperty::EditFill(CMachineObj_Comm* pObj)
{
	int nCount = m_SelectedObj.size();
	CString str;
	if (nCount > 1)
	{
		str.Format(_T("%d"), nCount);
		str = _T("填充参数(") + str + _T(")");
	}
	else
		str = _T("填充参数");
	UnDisp_Machine_Property
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowTextW(_T("填充参数"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->SetWindowPos(NULL, 12, 375, 250, 380, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO3)->SetWindowPos(NULL, 30, 400, 55, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO3)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_RADIO4)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO3), 100, 400, 65, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO4)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_RADIO5)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO4), 175, 400, 65, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO5)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO5)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_STATIC52)->SetWindowTextW(_T("填充组别选择"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC52)->SetWindowPos(NULL, 20, 430, 234, 260, BS_CENTER);
	GetDlgItem(IDC_OBJ_PROTY_STATIC52)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO6)->SetWindowPos(NULL, 30, 460, 50, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO6)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO6)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_RADIO7)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO6), 85, 460, 50, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO7)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO7)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_RADIO8)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO7), 140, 460, 50, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO8)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO8)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_RADIO9)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO8), 195, 460, 50, 20, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO9)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO9)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowPos(NULL, 50, 500, 80, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->SetWindowTextW(_T("填充角度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC28)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->SetWindowPos(NULL, 140, 499, 60, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT14)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowPos(NULL, 205, 500, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->SetWindowTextW(_T("度"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC29)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowPos(NULL, 50, 525, 80, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->SetWindowTextW(_T("填充间距"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC30)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->SetWindowPos(NULL, 140, 524, 60, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT15)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowPos(NULL, 205, 525, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC31)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowPos(NULL, 50, 550, 80, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->SetWindowTextW(_T("缩进距离"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC32)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->SetWindowPos(NULL, 140, 549, 60, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_EDIT16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowPos(NULL, 205, 550, 20, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->SetWindowTextW(_T("mm"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC33)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowPos(NULL, 50, 575, 80, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->SetWindowTextW(_T("填充线分布"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC34)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO10)->SetWindowPos(NULL, 135, 575, 50, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO10)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO11)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO10), 190, 575, 50, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO11)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowPos(NULL, 50, 600, 80, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->SetWindowTextW(_T("填充方向"));
	GetDlgItem(IDC_OBJ_PROTY_STATIC35)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO12)->SetWindowPos(NULL, 135, 600, 50, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO12)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_RADIO13)->SetWindowPos(GetDlgItem(IDC_OBJ_PROTY_RADIO12), 190, 600, 50, 14, BS_LEFT);
	GetDlgItem(IDC_OBJ_PROTY_RADIO13)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_CHECK1)->SetWindowPos(NULL, 100, 660, 100, 16, BS_RIGHT);
	GetDlgItem(IDC_OBJ_PROTY_CHECK1)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_CHECK1)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->SetWindowPos(NULL, 70, 710, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN16)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->SetWindowPos(NULL, 150, 710, 0, 0, SWP_NOSIZE);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_OBJ_PROTY_BTN17)->EnableWindow(TRUE);

	int nType = pObj->GetObjType();
	if (nType == MachineObj_Type_FillPolyline)
	{
		CMachineObjFillPolyline* pFillPolyline = (CMachineObjFillPolyline*)pObj;
		m_OutlinePrior = pFillPolyline->GetOutlinePrior();
		for (int i = 0; i < 4; i++)
		{
			m_FillPara[i] = pFillPolyline->GetFillPolylinePara(i);
		}
	}
	else
	{
		//
	}
	m_nSel_Old = m_nSelGroup;
	m_dVar1 = m_FillPara[m_nSelGroup].FillAngle;
	m_dVar2 = m_FillPara[m_nSelGroup].FillGap;
	m_dVar3 = m_FillPara[m_nSelGroup].Curtail;
	m_GapMode = m_FillPara[m_nSelGroup].GapMode;
	m_FillMode = m_FillPara[m_nSelGroup].FillMode;
	m_FillEnable = m_FillPara[m_nSelGroup].IsEnable;
	if (m_FillEnable)
	{
		GetDlgItem(IDC_OBJ_PROTY_EDIT14)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT15)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT16)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO12)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO13)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_OBJ_PROTY_CHECK1))->SetCheck(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJ_PROTY_EDIT14)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT15)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT16)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO12)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO13)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_OBJ_PROTY_CHECK1))->SetCheck(FALSE);
	}
	m_Edit_pObj = pObj;
	UpdateData(FALSE);
}

void CObjectProperty::SaveFill()
{
	int nCount = m_SelectedObj.size();
	if (UpdateData(TRUE))
	{
		m_FillPara[m_nSelGroup].FillAngle = m_dVar1;
		m_FillPara[m_nSelGroup].FillGap = m_dVar2;
		m_FillPara[m_nSelGroup].Curtail = m_dVar3;
		m_FillPara[m_nSelGroup].GapMode = m_GapMode;
		m_FillPara[m_nSelGroup].FillMode = m_FillMode;
		if (m_FillEnable)
			m_FillPara[m_nSelGroup].IsEnable = true;
		else
			m_FillPara[m_nSelGroup].IsEnable = false;
		for (int i = 0; i < nCount; i++)
		{
			int nIndex = m_ProtyListIndex[m_SelectedObj[i]];
			CMachineObjFillPolyline* pFillPolyline = (CMachineObjFillPolyline*)(m_pObjList->GetObjAtIndex(nIndex));
			pFillPolyline->ReCreatFillPolyline(m_OutlinePrior, m_FillPara);
		}
	}
	m_pView->Invalidate();
}


// CObjectProperty 消息处理程序
void CObjectProperty::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	//试图调整窗口尺寸，则向上级发送消息，用于锁定本对话框尺寸
	GetParentFrame()->SendMessage(WM_ObPrtyWindows_Size, NULL, NULL);
}

afx_msg LRESULT CObjectProperty::OnObjlistRefresh(WPARAM wParam, LPARAM lParam)
{
	if (m_pObjList->IsEmptyObj())
	{
		//新建文件入口
		m_PropertyList.DeleteAllItems();
		m_bDispObject = true;
		OnClickedObjectOrLayer();
		return -1;
	}
	//新建文件处理结束
	if (wParam == 0 && lParam == 0)
	{
		//导入文件入口
		m_PropertyList.DeleteAllItems();
		m_bDispObject = true;
		OnClickedObjectOrLayer();
		return 0;
	}
	//导入文件处理结束
	if (m_bDispObject)
	{
		//对象属性列表
		m_pView->m_bObjNodeDisp = false;
		Disp_Machine_Property
		int nIndex = 0;
		CMachineObj_Comm* pObj;
		if (wParam == 1 && lParam < 0)
		{
			//单选模式,无有效选中对象
			ClearAllObjSel();
			m_ObjSel_Old = -1;
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
		//单选模式,无有效选中对象处理结束
		else if (wParam == 1)
		{
			//单选模式,选中索引为"lParam"对象
			ClearAllObjSel();
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			nIndex = FindProtyListIndex(lParam);
			if ((nIndex != m_ObjSel_Old) && (nIndex >= 0))
			{
				m_ObjSel_Old = nIndex;
				pObj = m_pObjList->GetObjAtIndex(lParam);
				pObj->m_bIsObjStatus |= IsObjSel;
				m_PropertyList.SetItemState(nIndex, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				HScroll(nIndex);
			}
			else
			{
				m_ObjSel_Old = -1;
			}
		}
		//单选模式,选中索引为"lParam"对象处理结束
		else if (wParam == 2)
		{
			//复选模式
			nIndex = FindProtyListIndex(lParam);
			if (nIndex >= 0)
			{
				pObj = m_pObjList->GetObjAtIndex(lParam);
				if (m_PropertyList.GetItemState(nIndex, LVIS_SELECTED) == LVIS_SELECTED)
				{
					pObj->m_bIsObjStatus &= ~IsObjSel;
					m_ObjSel_Old = -1;
					m_PropertyList.SetItemState(nIndex, LVNI_FOCUSED & LVIS_SELECTED,
						LVNI_FOCUSED | LVIS_SELECTED);
				}
				else
				{
					pObj->m_bIsObjStatus |= IsObjSel;
					m_ObjSel_Old = nIndex;
					m_PropertyList.SetItemState(nIndex, LVNI_FOCUSED | LVIS_SELECTED,
						LVNI_FOCUSED | LVIS_SELECTED);
					HScroll(nIndex);
				}
			}
		}
		//复选模式处理结束
		else if (wParam == 3)
		{
			//多选模式
			ClearActiveLayerSel();
			int Count = m_PropertyList.GetItemCount();
			for (int i = 0; i < Count; i++)
			{
				pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[i]);
				pObj->m_bIsObjStatus &= ~IsObjSel;
			}
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			vector<int> *nList;
			nList = (vector<int>*)(lParam);
			Count = (*nList).size();
			for (int i = 0; i < Count; i++)
			{
				pObj = m_pObjList->GetObjAtIndex((*nList)[i]);
				pObj->m_bIsObjStatus |= IsObjSel;
				nIndex = FindProtyListIndex((*nList)[i]);
				m_PropertyList.SetItemState(nIndex, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				m_ObjSel_Old = nIndex;
			}
			HScroll(nIndex);
		}
		//多选模式处理结束
		UIRefreshObject();
	}
	//对象属性列表结束
	else
	{
		//图层列表
		CString str;
		if (wParam == 1 && lParam < 0)
		{
			//点选模式,无有效选中对象
			m_pObjList->SetLayerUnSelectAll();
			m_LayerSel_Old = -1;
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			UIRefreshLayer();
		}
		//点选模式,无有效选中对象处理结束
		else if (wParam == 1)
		{
			//单选模式,选中索引为"lParam"对象
			CMachineObj_Comm* pObj = m_pObjList->GetObjAtIndex(lParam);
			pObj->m_bIsObjStatus &= ~IsObjSel;
			int nLayer = pObj->m_ObjByLayer;
			CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(nLayer);
			str = m_PropertyList.GetItemText(2, 1);
			str.Remove(' ');
			str.MakeUpper();
			if (nLayer > LayerNum_Group)
			{
				if (str == _T("MIX"))
					nLayer -= 2;
				else
					nLayer -= 3;
			}
			if (m_PropertyList.GetItemState(nLayer, LVIS_SELECTED) != 0)
			{
				pLayer->m_bIsLayerStatus &= IsObjSel;
				m_LayerSel_Old = -1;
				m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
			}
			else
			{
				pLayer->m_bIsLayerStatus |= IsObjSel;
				m_LayerSel_Old = nLayer;
				m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				m_PropertyList.SetItemState(nLayer, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
			}
		}
		//单选模式,选中索引为"lParam"对象处理结束
		else if (wParam == 2)
		{
			//复选模式
			CMachineObj_Comm* pObj = m_pObjList->GetObjAtIndex(lParam);
			pObj->m_bIsObjStatus &= ~IsObjSel;
			int nLayer = pObj->m_ObjByLayer;
			CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(nLayer);
			str = m_PropertyList.GetItemText(2, 1);
			str.Remove(' ');
			str.MakeUpper();
			if (nLayer > LayerNum_Group)
			{
				if (str == _T("MIX"))
					nLayer -= 2;
				else
					nLayer -= 3;
			}
			if (m_PropertyList.GetItemState(nLayer, LVIS_SELECTED) != 0)
			{
				pLayer->m_bIsLayerStatus &= ~IsObjSel;
				m_LayerSel_Old = -1;
				m_PropertyList.SetItemState(nLayer, LVNI_FOCUSED & LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
			}
			else
			{
				pLayer->m_bIsLayerStatus |= IsObjSel;
				m_LayerSel_Old = nLayer;
				m_PropertyList.SetItemState(nLayer, LVNI_FOCUSED & LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				m_PropertyList.SetItemState(nLayer, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
			}
		}
		//复选模式处理结束
		else if (wParam == 3)
		{
			//多选模式
			m_pObjList->SetObjUnSelectAll();
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			vector<int> *nList;
			nList = (vector<int>*)(lParam);
			int Count_ObjSel = (*nList).size();
			vector <bool> ListLayerSel;
			int nLayer = m_pObjList->GetLayerCount();
			for (int i = 0; i < nLayer; i++)
			{
				ListLayerSel.push_back(false);
			}
			for (int i = 0; i < Count_ObjSel; i++)
			{
				ListLayerSel[(m_pObjList->GetObjAtIndex((*nList)[i]))->m_ObjByLayer] = true;
			}
			for (int i = 0; i < nLayer; i++)
			{
				CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(i);
				if (ListLayerSel[i] == true)
				{
					pLayer->m_bIsLayerStatus |= IsObjSel;
					if (i <= LayerNum_Group)
						m_PropertyList.SetItemState(i, LVNI_FOCUSED | LVIS_SELECTED,
						LVNI_FOCUSED | LVIS_SELECTED);
					else
					{
						str = m_PropertyList.GetItemText(2, 1);
						str.Remove(' ');
						str.MakeUpper();
						if (str == _T("MIX"))
							m_PropertyList.SetItemState(i - 2, LVNI_FOCUSED | LVIS_SELECTED,
							LVNI_FOCUSED | LVIS_SELECTED);
						else
							m_PropertyList.SetItemState(i - 3, LVNI_FOCUSED | LVIS_SELECTED,
							LVNI_FOCUSED | LVIS_SELECTED);
					}
				}
			}
		}
		//多选模式处理结束
		UIRefreshLayer();
	}
	//图层列表结束
	m_PropertyList.SetFocus();
	UpdateData(FALSE);
	return 0;
}

void CObjectProperty::OnKeydownObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	*pResult = 0;
	if (m_bDispObject)
	{
		//往上或往下选中加工对象表中元素
		if (!(pLVKeyDow->wVKey == VK_UP || pLVKeyDow->wVKey == VK_DOWN) ||
			m_PropertyList.GetSelectedCount() == 0)
			return;
		if (m_PropertyList.GetSelectedCount() > 1)
		{
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			ClearAllObjSel();
			return;
		}
		CMachineObj_Comm* pObj;
		int Count = m_PropertyList.GetItemCount();
		POSITION pos = m_PropertyList.GetFirstSelectedItemPosition();
		int	Index = m_PropertyList.GetNextSelectedItem(pos);
		if ((pLVKeyDow->wVKey == VK_UP) && (Index > 0))
		{
			pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
			pObj->m_bIsObjStatus &= ~IsObjSel;
			pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index - 1]);
			pObj->m_bIsObjStatus |= IsObjSel;
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			UIRefreshObject(Index - 1);
			m_ObjSel_Old = Index - 1;
			m_SelectedObj.swap(vector<UINT>());
			m_SelectedObj.push_back(m_ObjSel_Old);
		}
		else if ((pLVKeyDow->wVKey == VK_DOWN) && (Index + 1) < Count)
		{
			pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
			pObj->m_bIsObjStatus &= ~IsObjSel;
			pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index + 1]);
			pObj->m_bIsObjStatus |= IsObjSel;
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			UIRefreshObject(Index + 1);
			m_ObjSel_Old = Index + 1;
			m_SelectedObj.swap(vector<UINT>());
			m_SelectedObj.push_back(m_ObjSel_Old);
		}
		m_pView->Invalidate();
		return;
	}
	else
	{
		//上下移动图层列表中元素
		if (!(pLVKeyDow->wVKey == VK_UP || pLVKeyDow->wVKey == VK_DOWN)
			|| m_PropertyList.GetSelectedCount() != 1)
			return;
		if (pLVKeyDow->wVKey == VK_UP)
		{
			m_LayerSel_Old = -1;
			if (m_PropertyList.GetSelectedCount() != 1)
				return;
			POSITION pos;
			int Index = 0;
			pos = m_PropertyList.GetFirstSelectedItemPosition();
			while (pos)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
			}
			if (Index < 0 || Index >= m_PropertyList.GetItemCount())
				return;
			CString str = m_PropertyList.GetItemText(Index, 1);
			int nLayer = m_pObjList->FindLayerByName(str);
			if (nLayer < 0 || nLayer >= m_pObjList->GetLayerCount())
				return;
			if (nLayer < LayerNum_Default)
			{
				MessageBox(_T("不可移动的图层!"));
				m_PropertyList.SetItemState(Index + 1, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				return;
			}
			if (nLayer == LayerNum_Default)
			{
				MessageBox(_T("该图层已是第一加工层!"));
				m_PropertyList.SetItemState(Index + 1, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
				return;
			}
			m_pObjList->LayerMoveUpAtIndex(nLayer);
			CString str1;
			str = m_PropertyList.GetItemText(Index, 1);
			str1 = m_PropertyList.GetItemText(Index - 1, 1);
			m_PropertyList.SetItemText(Index - 1, 1, str);
			m_PropertyList.SetItemText(Index, 1, str1);
			str = m_PropertyList.GetItemText(Index, 2);
			str1 = m_PropertyList.GetItemText(Index - 1, 2);
			m_PropertyList.SetItemText(Index - 1, 2, str);
			m_PropertyList.SetItemText(Index, 2, str1);
			str = m_PropertyList.GetItemText(Index, 3);
			str1 = m_PropertyList.GetItemText(Index - 1, 3);
			m_PropertyList.SetItemText(Index - 1, 3, str);
			m_PropertyList.SetItemText(Index, 3, str1);
			m_LayerSel_Old = Index - 1;
		}
		else if (pLVKeyDow->wVKey == VK_DOWN)
		{
			m_LayerSel_Old = -1;
			if (m_PropertyList.GetSelectedCount() != 1)
				return;
			POSITION pos;
			int Index = 0;
			pos = m_PropertyList.GetFirstSelectedItemPosition();
			while (pos)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
			}
			if (Index < 0 || Index >= m_PropertyList.GetItemCount())
				return;
			CString str = m_PropertyList.GetItemText(Index, 1);
			int nLayer = m_pObjList->FindLayerByName(str);
			if (nLayer < 0 || nLayer >= m_pObjList->GetLayerCount())
				return;
			if (nLayer < LayerNum_Default)
			{
				MessageBox(_T("不可移动的图层!"));
				return;
			}
			if (nLayer >= m_pObjList->GetLayerCount() - 1)
			{
				MessageBox(_T("该图层已是最后加工层!"));
				return;
			}
			m_pObjList->LayerMoveDownAtIndex(nLayer);
			CString str1;
			str = m_PropertyList.GetItemText(Index, 1);
			str1 = m_PropertyList.GetItemText(Index + 1, 1);
			m_PropertyList.SetItemText(Index + 1, 1, str);
			m_PropertyList.SetItemText(Index, 1, str1);
			str = m_PropertyList.GetItemText(Index, 2);
			str1 = m_PropertyList.GetItemText(Index + 1, 2);
			m_PropertyList.SetItemText(Index + 1, 2, str);
			m_PropertyList.SetItemText(Index, 2, str1);
			str = m_PropertyList.GetItemText(Index, 3);
			str1 = m_PropertyList.GetItemText(Index + 1, 3);
			m_PropertyList.SetItemText(Index + 1, 3, str);
			m_PropertyList.SetItemText(Index, 3, str1);
			m_LayerSel_Old = Index + 1;
		}
	}
}

void CObjectProperty::OnMouseMove(UINT nFlags, CPoint point)
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	pFrame->SetActiveView(this);
	CFormView::OnMouseMove(nFlags, point);
}

////////////以下为2021年重写
void CObjectProperty::OnClickedObjectOrLayer()
{
	POSITION pos;
	CMachineObj_Comm* pObj;
	CString str;
	m_bDispObject = !m_bDispObject;
	m_ObjSel_Old = -1;
	m_LayerSel_Old = -1;
	m_pView->m_bObjNodeDisp = false;
	if (!m_pObjList->IsEmptyObj())
	{
		if (m_bDispObject)
		{
			//Object Panel
			Disp_Object_List
			Disp_Object_Panel

			int i = 0;
			int j = 0;
			m_ProtyListIndex.swap(vector<UINT>());
			pos = m_pObjList->GetObjHeadPosition();
			while (pos)
			{
				CMachinePara_Layer* pLayer;
				pObj = m_pObjList->GetObjNext(pos);
				int nLayer = pObj->m_ObjByLayer;
				pLayer = m_pObjList->GetLayerOfNumber(nLayer);
				byte status = pLayer->m_bIsLayerStatus & IsObjClosed;
				byte status1 = pLayer->m_bIsLayerStatus & IsObjLocked;
				if (status == 0 && status1 == 0)
				{
					str.Format(_T("%d"), i + 1);
					m_PropertyList.InsertItem(i, str);
					switch (pObj->GetObjType())
					{
					case MachineObj_Type_Point:
						str = _T("点");
						break;
					case MachineObj_Type_Line:
						str = _T("直线");
						break;
					case MachineObj_Type_Circle:
						str = _T("圆");
						break;
					case MachineObj_Type_Arc:
						str = _T("圆弧");
						break;
					case MachineObj_Type_Ellipse:
						str = _T("椭圆");
						break;
					case MachineObj_Type_ArcEll:
						str = _T("椭圆弧");
						break;
					case MachineObj_Type_TiltEllipse:
						str = _T("斜椭圆弧");
						break;
					case MachineObj_Type_Polyline:
						str = _T("多段线");
						break;
					case MachineObj_Type_Group:
						str = _T("群 组");
						break;
					case MachineObj_Type_WLine:
						str = _T("展宽直线");
						break;
					case MachineObj_Type_WArc:
						str = _T("展宽圆弧");
						break;
					case MachineObj_Type_WPolyline:
						str = _T("展宽多段线");
						break;
					case MachineObj_Type_FillPolyline:
						str = _T("填充区域");
						break;
					default:
						str = "";
						break;
					}
					if (((pLayer->m_bIsLayerStatus & IsObjSel) != 0) || (pObj->m_bIsObjStatus & IsObjSel) !=0)
					{
						m_PropertyList.SetItemState(i, LVNI_FOCUSED | LVIS_SELECTED,
							LVNI_FOCUSED | LVIS_SELECTED);
						m_ObjSel_Old = i;
					}
						
					m_PropertyList.SetItemText(i, 1, str);
					str = (m_pObjList->GetLayerOfNumber(pObj->m_ObjByLayer))->m_LayerName;
					m_PropertyList.SetItemText(i, 2, str);
					m_ProtyListIndex.push_back(j);
					j++;
					i++;
				}
				else
				{
					j++;
				}
			}
			m_LayerNameListBox.ResetContent();
			int LayerCount = m_pObjList->GetLayerCount();
			int Index = 0;
			for (int i = 0; i < LayerNum_Group; i++)
			{
				CString str = m_pObjList->GetLayerOfNumber(i)->m_LayerName;
				m_LayerNameListBox.InsertString(Index, str);
				Index++;
			}
			for (int i = LayerNum_Default; i < LayerCount; i++)
			{
				CString str = m_pObjList->GetLayerOfNumber(i)->m_LayerName;
				m_LayerNameListBox.InsertString(Index, str);
				Index++;
			}
			UIRefreshObject();
		}
		//Object Panel end
		else
		{
			//Layer Panel
			Disp_Layer_List
			Disp_Layer_Panel
			Enable_Layer_BTN_New

			vector <UINT> ListLayerObjCount;
			int nLayer = m_pObjList->GetLayerCount();
			for (int i = 0; i < nLayer; i++)
			{
				ListLayerObjCount.push_back(0);
			}
			pos = m_pObjList->GetObjHeadPosition();
			while (pos)
			{
				pObj = m_pObjList->GetObjNext(pos);
				ListLayerObjCount[pObj->m_ObjByLayer]++;
			}
			int nLayerCount = 0;
			m_LayerSel_Old = -1;
			for (int i = 0; i < LayerNum_Group; i++)
			{
				str.Format(_T("%d"), nLayerCount + 1);
				m_PropertyList.InsertItem(nLayerCount, str);
				str = (m_pObjList->GetLayerOfNumber(i))->m_LayerName;
				m_PropertyList.SetItemText(nLayerCount, 1, str);
				if (((m_pObjList->GetLayerOfNumber(i)->m_bIsLayerStatus) & IsObjSel) != 0)
				{
					m_PropertyList.SetItemState(nLayerCount, LVNI_FOCUSED | LVIS_SELECTED,
						LVNI_FOCUSED | LVIS_SELECTED);
					m_LayerSel_Old = nLayerCount;
				}
				str.Format(_T("%d"), ListLayerObjCount[i]);
				m_PropertyList.SetItemText(nLayerCount, 3, str);
				nLayerCount++;
			}
			if (ListLayerObjCount[LayerNum_Group] != 0)
			{
				str.Format(_T("%d"), nLayerCount + 1);
				m_PropertyList.InsertItem(nLayerCount, str);
				str = (m_pObjList->GetLayerOfNumber(LayerNum_Group))->m_LayerName;
				m_PropertyList.SetItemText(nLayerCount, 1, str);
				if (((m_pObjList->GetLayerOfNumber(LayerNum_Group)->m_bIsLayerStatus) & IsObjSel) != 0)
				{
					m_PropertyList.SetItemState(nLayerCount, LVNI_FOCUSED | LVIS_SELECTED,
						LVNI_FOCUSED | LVIS_SELECTED);
					m_LayerSel_Old = nLayerCount;
				}
				str.Format(_T("%d"), ListLayerObjCount[LayerNum_Group]);
				m_PropertyList.SetItemText(nLayerCount, 3, str);
				nLayerCount++;
			}
			for (int i = LayerNum_Default; i < nLayer; i++)
			{
				str.Format(_T("%d"), nLayerCount + 1);
				m_PropertyList.InsertItem(nLayerCount, str);
				str = m_pObjList->GetLayerOfNumber(i)->m_LayerName;
				m_PropertyList.SetItemText(nLayerCount, 1, str);
				if (((m_pObjList->GetLayerOfNumber(i)->m_bIsLayerStatus) & IsObjSel) != 0)
				{
					m_PropertyList.SetItemState(nLayerCount, LVNI_FOCUSED | LVIS_SELECTED,
						LVNI_FOCUSED | LVIS_SELECTED);
					m_LayerSel_Old = nLayerCount;
				}
				str.Format(_T("%d"), ListLayerObjCount[i]);
				if (ListLayerObjCount[LayerNum_Group] != 0)
					str = str + _T("*");
				m_PropertyList.SetItemText(nLayerCount, 3, str);
				nLayerCount++;
			}
			UIRefreshLayer();
		}
		//Layer Panel end
	}
	else
	{
		m_bDispObject = false;
		Disp_Layer_List
		Disp_Layer_Panel
		Disable_Layer_BTN_ClearLayer
		Disable_Layer_BTN_Combine
		Disable_Layer_BTN_New
	}
	UpdateData(FALSE);
}

void CObjectProperty::OnClickedObjProtyBtnSave()
{
	if (!UpdateData(TRUE))
		return;
	ProcessPara para;
	para.Speed = m_Speed;
	para.Power = m_Power;
	para.Frequncy = (UINT)(m_Frequncy * 1000);
	para.Times = m_Count;
	para.PulseWidth = m_PulseWidth;
	para.LaserOnDelay = m_LaserOnDelay;
	para.LaserOffDelay = m_LaserOffDelay;
	para.BeforMarkDelay = m_BeforMarkDelay;
	para.AfterMarkDelay = m_AfterMarkDelay;
	para.PolylineDelay = m_PolylineDelay;
	if (!m_pDoc->Check_Process_Para1(para, m_ModeSel))
	{
		MessageBox(_T("加工参数超限!"));
		return;
	}
	gProcessSpeed = m_Speed;
	gProcessPower = m_Power;
	gProcessFrequncy = (UINT)(m_Frequncy * 1000);
	gProcessTimes = m_Count;
	gProcessPulseWidth = m_PulseWidth;
	gProcessMode = m_ModeSel;
	gLaserOnDelay = m_LaserOnDelay;
	gLaserOffDelay = m_LaserOffDelay;
	gBeforMarkDelay = m_BeforMarkDelay;
	gAfterMarkDelay = m_AfterMarkDelay;
	gPolylineDelay = m_PolylineDelay;
}

void CObjectProperty::OnObjProtyBtnLayerNew()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count == 0)
			return;
		int Index = m_LayerNameListBox.GetCurSel();
		CString str;
		m_LayerNameListBox.GetLBText(Index, str);
		int nLayer = m_pObjList->FindLayerByName(str);
		if ((nLayer < 0) || (nLayer > m_pObjList->GetLayerCount()))
			return;
		for (int i = 0; i < Count; i++)
		{
			Index = m_SelectedObj[i];
			CMachineObj_Comm*pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
			m_pObjList->ChangeObjByLayer(pObj, nLayer);
		}
		m_bDispObject = false;
		OnClickedObjectOrLayer();
		m_pView->Invalidate();
	}
	//Change_ObjectByLayer End
	else
	{
		if (!UpdateData(TRUE))
			return;
		if (m_pObjList->IsEmptyObj())
			return;
		CString str = m_LayerName;
		str.Remove(' ');
		if (str == "")
		{
			MessageBox(_T("图层名不能为空"));
			return;
		}
		int nTemp = m_pObjList->FindLayerByName(str);
		if (nTemp >= LayerNum_Default)
		{
			MessageBox(_T("图层名已存在"));
			return;
		}
		if (nTemp >= 0)
		{
			MessageBox(_T("无效的图层名"));
			return;
		}
		ProcessPara para;
		para.Speed = m_Speed;
		para.Power = m_Power;
		para.Frequncy = (UINT)(m_Frequncy * 1000);
		para.Times = m_Count;
		para.PulseWidth = m_PulseWidth;
		para.LaserOnDelay = m_LaserOnDelay;
		para.LaserOffDelay = m_LaserOffDelay;
		para.BeforMarkDelay = m_BeforMarkDelay;
		para.AfterMarkDelay = m_AfterMarkDelay;
		para.PolylineDelay = m_PolylineDelay;
		if (!m_pDoc->Check_Process_Para1(para, m_ModeSel))
		{
			MessageBox(_T("加工参数超限!"));
			return;
		}
		CMachinePara_Layer* pLayer = new CMachinePara_Layer(str, m_ModeSel, para, 0);
		m_pObjList->AddLayer(pLayer);
		int ListCount = m_PropertyList.GetItemCount();
		str.Format(_T("%d"), ListCount + 1);
		m_PropertyList.InsertItem(ListCount, str);
		m_PropertyList.SetItemText(ListCount, 1, pLayer->m_LayerName);
		m_PropertyList.SetItemText(ListCount, 2, _T("活动"));
		m_PropertyList.SetItemText(ListCount, 3, _T("0"));
	}
	//New_Layer End
}

void CObjectProperty::OnObjProtyBtnLayerOpenAndCloseOrObjDelete()
{
	if (m_bDispObject)
	{
		if (MessageBox(_T("确定删除选中对象?\n(删除是不可恢复的!)"),
			_T(""), MB_YESNO | MB_ICONWARNING) != IDYES)
			return;
		int Count = m_SelectedObj.size();
		if (Count == 0)
		{
			MessageBox(_T("无可删除对象!"));
			return;
		}
		int Index;
		for (int i = 0; i < Count; i++)
		{
			Index = m_SelectedObj[Count - 1 - i];
			m_pObjList->DeleteObjAtIndex(m_ProtyListIndex[Index]);
		}
		m_SelectedObj.swap(vector<UINT>());
		m_bDispObject = false;
		OnClickedObjectOrLayer();
		m_pObjList->RefeshBound();
		ObjRect rect = m_pObjList->GetObjBound();
		if ((abs(rect.min_x) > InvalidLength) || (abs(rect.min_y) > InvalidLength))
			m_pObjList->MoveObjectListCoordinate(-rect.min_x, -rect.min_y);
		m_pView->SendMessage(WM_ObjBound_ReSize, NULL, NULL);
	}
	//Obj_Delete End
	else
	{
		if (m_PropertyList.GetSelectedCount() != 1)
			return;
		POSITION pos;
		int Index = 0;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
		}
		CString str = m_PropertyList.GetItemText(Index, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(nLayer);
		if ((pLayer->m_bIsLayerStatus & IsObjClosed) == 0)
		{
			Enable_Layer_BTN_Open
			Enable_Layer_BTN_UpAndDown
			Disable_Layer_BTN_Lock
			Disable_Layer_BTN_Modify
			Disable_Layer_BTN_Delete
			pLayer->m_bIsLayerStatus = pLayer->m_bIsLayerStatus | IsObjClosed;
			m_PropertyList.SetItemText(Index, 2, _T("已关闭"));
		}
		else
		{
			Enable_Layer_BTN_Close
			Enable_Layer_BTN_UpAndDown
			pLayer->m_bIsLayerStatus = pLayer->m_bIsLayerStatus & ~IsObjClosed;
			if ((pLayer->m_bIsLayerStatus & IsObjLocked) == 0)
			{
				Enable_Layer_BTN_Lock
				Enable_Layer_BTN_Modify
				Enable_Layer_BTN_Delete
				m_PropertyList.SetItemText(Index, 2, _T("活 动"));
			}
			else
			{
				Enable_Layer_BTN_Unlock
				Disable_Layer_BTN_Modify
				Disable_Layer_BTN_Delete
				m_PropertyList.SetItemText(Index, 2, _T("已锁定"));
			}
		}
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
	//Layer_Open_Close End
}

void CObjectProperty::OnObjProtyBtnLayerLockAndUnlockOrObjEdit()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if ((Count <= 0) || (Count > m_PropertyList.GetItemCount()))
			return;
		m_pView->m_bObjNodeDisp = false;
		if (Count == 1)
		{
			//Single Object_Edit
			POSITION pos;
			int Index;
			pos = m_PropertyList.GetFirstSelectedItemPosition();
			while (pos)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
			}
			CMachineObj_Comm* pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
			int nType = pObj->GetObjType();
			switch (nType)
			{
			case MachineObj_Type_Point:
				EditPoint(pObj);
				break;
			case MachineObj_Type_Line:
				EditLine(pObj);
				break;
			case MachineObj_Type_Circle:
				EditCircle(pObj);
				break;
			case MachineObj_Type_Arc:
				EditArc(pObj);
				break;
			case MachineObj_Type_Ellipse:
				EditEllipse(pObj);
				break;
			case MachineObj_Type_ArcEll:
				EditArcEll(pObj);
				break;
			case MachineObj_Type_TiltEllipse:
				EditTiltEllipse(pObj);
				break;
			case MachineObj_Type_Polyline:
				m_SelNode = 0;
				EditPolyline(pObj);
				break;
			case MachineObj_Type_Group:
				EditGroup(pObj);
				break;
			case MachineObj_Type_WLine:
				EditWiden(pObj);
				break;
			case MachineObj_Type_WArc:
				EditWiden(pObj);
				break;
			case MachineObj_Type_WPolyline:
				EditWiden(pObj);
				break;
			case MachineObj_Type_FillPolyline:
				EditFill(pObj);
				break;
			default:
				break;
			}
		}
		//Single Object_Edit End
		else
		{
			//Multi Object_Edit
			CMachineObj_Comm* pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[m_SelectedObj[0]]);
			int nType = pObj->GetObjType();
			if (nType == MachineObj_Type_WLine
				|| nType == MachineObj_Type_WArc
				|| nType == MachineObj_Type_WPolyline)
			{
				EditWiden(pObj);
			}
			else if (nType == MachineObj_Type_FillPolyline)
			{
				EditFill(pObj);
			}
		}
		//Multi Object_Edit End
		Disable_OBJ_BTN_UpAndDown
			Disable_OBJ_BTN_FillCreat
			Disable_OBJ_BTN_ChangeLayer
			Disable_OBJ_BTN_WidenCreat
			Disable_OBJ_BTN_Polyline
			Disable_OBJ_BTN_DisGroup
			Disable_OBJ_BTN_Route
			Disable_OBJ_BTN_Group
		m_pView->Invalidate();
	}
	//Object_Edit End
	else
	{
		if (m_PropertyList.GetSelectedCount() != 1)
			return;
		POSITION pos;
		int Index = 0;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
		}
		CString str = m_PropertyList.GetItemText(Index, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(nLayer);
		if ((pLayer->m_bIsLayerStatus & IsObjLocked) == 0)
		{
			Enable_Layer_BTN_Unlock
			Disable_Layer_BTN_Modify
			Disable_Layer_BTN_Delete
			pLayer->m_bIsLayerStatus = pLayer->m_bIsLayerStatus | IsObjLocked;
			m_PropertyList.SetItemText(Index, 2, _T("已锁定"));
		}
		else
		{
			Enable_Layer_BTN_Lock
			Enable_Layer_BTN_Modify
			Enable_Layer_BTN_Delete
			pLayer->m_bIsLayerStatus = pLayer->m_bIsLayerStatus & ~IsObjLocked;
			m_PropertyList.SetItemText(Index, 2, _T("活 动"));
		}
		UpdateData(FALSE);
		m_pView->Invalidate();
	}
	//Layer_Lock_Unlock End
}

void CObjectProperty::OnObjProtyBtnLayerModifyOrObjGroup()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count <= 1)
			return;
		vector<int> nList;
		int Index = m_ProtyListIndex[m_SelectedObj[0]];
		for (int i = 0; i < Count; i++)
		{
			nList.push_back(m_ProtyListIndex[m_SelectedObj[i]]);
		}
		if (m_pObjList->GroupObjAtIndex(nList))
		{
			m_pObjList->SetObjSelect(Index);
			m_bDispObject = false;
			OnClickedObjectOrLayer();
			HScroll(m_SelectedObj[0]);
			m_PropertyList.SetFocus();
		}
	}
	//Object_Group End
	else
	{
		if (m_PropertyList.GetSelectedCount() != 1)
			return;
		POSITION pos;
		int Index = 0;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
		}
		if (Index < 0 || Index >= m_PropertyList.GetItemCount())
			return;
		CString str = m_PropertyList.GetItemText(Index, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		if (nLayer < LayerNum_Default)
		{
			MessageBox(_T("系统保留层,不能修改!"));
			return;
		}
		UpdateData(TRUE);
		str = m_LayerName;
		str.Remove(' ');
		int nLayer1 = m_pObjList->FindLayerByName(str);
		if (nLayer1 > 0 && nLayer1 != nLayer)
		{
			MessageBox(_T("图层已存在!"));
			return;
		}
		ProcessPara para;
		para.Speed = m_Speed;
		para.Power = m_Power;
		para.Frequncy = (UINT)(m_Frequncy * 1000);
		para.Times = m_Count;
		para.PulseWidth = m_PulseWidth;
		para.LaserOnDelay = m_LaserOnDelay;
		para.LaserOffDelay = m_LaserOffDelay;
		para.BeforMarkDelay = m_BeforMarkDelay;
		para.AfterMarkDelay = m_AfterMarkDelay;
		para.PolylineDelay = m_PolylineDelay;
		if (!m_pDoc->Check_Process_Para1(para, m_ModeSel))
		{
			MessageBox(_T("加工参数超限!"));
			return;
		}
		CMachinePara_Layer* pLayer;
		pLayer = m_pObjList->GetLayerOfNumber(nLayer);
		if ((nLayer1 < 0) && (!(str == "")))
			pLayer->m_LayerName = str;
		pLayer->m_MachineMode = m_ModeSel;
		pLayer->m_MachinePara = para;
		m_PropertyList.SetItemText(Index, 1, pLayer->m_LayerName);
	}
	//Layer_Modify End
}

void CObjectProperty::OnObjProtyBtnLayerDeleteOrObjExplode()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count < 1)
			return;
		int Index;
		for (int i = 0; i < Count; i++)
		{
			Index = m_SelectedObj[Count - 1 - i];
			m_pObjList->ExplodeObjAtIndex(m_ProtyListIndex[Index]);
		}
		m_SelectedObj.swap(vector<UINT>());
		m_pObjList->SetObjSelect(m_ProtyListIndex[Index]);
		m_bDispObject = false;
		OnClickedObjectOrLayer();
		HScroll(m_SelectedObj[0]);
		m_PropertyList.SetFocus();
		m_pView->Invalidate();
	}
	//Object_Explode End
	else
	{
		if (m_PropertyList.GetSelectedCount() > 1)
			return;
		int Index = m_PropertyList.GetSelectionMark();
		CString str = m_PropertyList.GetItemText(Index, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		if ((nLayer < 0) || (nLayer >= m_pObjList->GetLayerCount()))
		{
			MessageBox(_T("指定图层不存在!"));
			return;
		}
		else if (nLayer < LayerNum_Default)
		{
			MessageBox(_T("这个图层不容许删除!"));
			return;
		}
		str = _T("删除图层\"") + str + _T("\"") + _T("和其中的所有加工对象\n\n");
		str = str + _T("   该删除是不可逆的! 是否继续?");
		if (IDNO == MessageBox(str, _T("删  除"), MB_YESNO))
			return;
		m_pObjList->DeleteLayerOfNumber(nLayer);
		m_bDispObject = true;
		OnClickedObjectOrLayer();
		ObjRect rect = m_pObjList->GetObjBound();
		if ((abs(rect.min_x) > InvalidLength) || (abs(rect.min_y) > InvalidLength))
			m_pObjList->MoveObjectListCoordinate(-rect.min_x, -rect.min_y);
		m_pView->Invalidate();
	}
	//Layer_Delete End
}

void CObjectProperty::OnObjProtyBtnLayerClear()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count < 1)
			return;
		int Index;
		for (int i = 0; i < Count; i++)
		{
			Index = m_SelectedObj[i];
			Index = m_ProtyListIndex[Index];
			m_pObjList->PolymerObjAtIndex(Index);
		}
		m_bDispObject = false;
		OnClickedObjectOrLayer();
	}
	//Object_PolyLine End
	else
	{
		if (m_PropertyList.GetSelectedCount() == 1)
		{
			int Index = m_PropertyList.GetSelectionMark();
			CString str = m_PropertyList.GetItemText(Index, 1);
			int nLayer = m_pObjList->FindLayerByName(str);
			if ((nLayer < 0) || (nLayer >= m_pObjList->GetLayerCount()))
				return;
			else if (nLayer < LayerNum_Default)
				return;
			m_pObjList->ClearNullObject(nLayer);
			m_bDispObject = true;
			OnClickedObjectOrLayer();
			m_pView->Invalidate();
		}
		else
		{
			m_pObjList->ClearNullLayer();
			m_bDispObject = true;
			OnClickedObjectOrLayer();
		}
	}
	//Layer_Clear End
}

void CObjectProperty::OnObjProtyBtnLayerOrObjUp()
{
	int Index;
	POSITION pos;
	CString str, str1;
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if ((Count <= 0) || (Count > m_PropertyList.GetItemCount()))
			return;
		if (Count == 1)
		{
			m_ObjSel_Old = -1;
			if (m_PropertyList.GetSelectedCount() != 1)
			{
				MessageBox(_T("无法上移"));
				return;
			}
			pos = m_PropertyList.GetFirstSelectedItemPosition();
			while (pos)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
			}
			if (Index <= 0 || Index >= m_PropertyList.GetItemCount())
			{
				MessageBox(_T("无法上移"));
				return;
			}
			if (!m_pObjList->ExchangeObjAtIndex(m_ProtyListIndex[Index], m_ProtyListIndex[Index - 1]))
			{
				MessageBox(_T("无法上移"));
				return;
			}
			str = m_PropertyList.GetItemText(Index - 1, 1);
			m_PropertyList.SetItemText(Index - 1, 1, m_PropertyList.GetItemText(Index, 1));
			m_PropertyList.SetItemText(Index, 1, str);
			str = m_PropertyList.GetItemText(Index - 1, 2);
			m_PropertyList.SetItemText(Index - 1, 2, m_PropertyList.GetItemText(Index, 2));
			m_PropertyList.SetItemText(Index, 2, str);
			str = m_PropertyList.GetItemText(Index - 1, 3);
			m_PropertyList.SetItemText(Index - 1, 3, m_PropertyList.GetItemText(Index, 3));
			m_PropertyList.SetItemText(Index, 3, str);
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_PropertyList.SetItemState(Index - 1, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_LayerSel_Old = Index - 1;
			HScroll(Index);
			m_PropertyList.SetFocus();
		}
		//Object_Up End
		else
		{
			vector<int> nList;
			for (int i = 0; i < Count; i++)
			{
				nList.push_back(m_ProtyListIndex[m_SelectedObj[i]]);
			}
			if (!m_pObjList->ReverseObj(nList))
				MessageBox(_T("无法换向!"));
			else
				m_pView->Invalidate();
		}
		//Object_Redir End
	}
	//Object End
	else
	{
		m_LayerSel_Old = -1;
		if (m_PropertyList.GetSelectedCount() != 1)
			return;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
		}
		if (Index < 0 || Index >= m_PropertyList.GetItemCount())
			return;
		str = m_PropertyList.GetItemText(Index, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		if (nLayer < 0 || nLayer >= m_pObjList->GetLayerCount())
			return;
		if (nLayer < LayerNum_Default)
		{
			MessageBox(_T("不可移动的图层!"));
			return;
		}
		if (nLayer == LayerNum_Default)
		{
			MessageBox(_T("该图层已是第一加工层!"));
			return;
		}
		m_pObjList->LayerMoveUpAtIndex(nLayer);
		str = m_PropertyList.GetItemText(Index, 1);
		str1 = m_PropertyList.GetItemText(Index - 1, 1);
		m_PropertyList.SetItemText(Index - 1, 1, str);
		m_PropertyList.SetItemText(Index, 1, str1);
		str = m_PropertyList.GetItemText(Index, 2);
		str1 = m_PropertyList.GetItemText(Index - 1, 2);
		m_PropertyList.SetItemText(Index - 1, 2, str);
		m_PropertyList.SetItemText(Index, 2, str1);
		str = m_PropertyList.GetItemText(Index, 3);
		str1 = m_PropertyList.GetItemText(Index - 1, 3);
		m_PropertyList.SetItemText(Index - 1, 3, str);
		m_PropertyList.SetItemText(Index, 3, str1);
		m_PropertyList.SetItemState(Index, LVNI_FOCUSED & LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		m_PropertyList.SetItemState(Index - 1, LVNI_FOCUSED | LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		m_LayerSel_Old = Index - 1;
		HScroll(Index);
		m_PropertyList.SetFocus();
	}
	//Layer_Up End
}

void CObjectProperty::OnObjProtyBtnLayerOrObjDown()
{
	int Index;
	POSITION pos;
	CString str, str1;
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if ((Count <= 0) || (Count > m_PropertyList.GetItemCount()))
			return;
		if (Count == 1)
		{
			m_ObjSel_Old = -1;
			if (m_PropertyList.GetSelectedCount() != 1)
			{
				MessageBox(_T("无法下移"));
				return;
			}
			pos = m_PropertyList.GetFirstSelectedItemPosition();
			while (pos)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
			}
			if (Index < 0 || (Index + 1) >= m_PropertyList.GetItemCount())
			{
				MessageBox(_T("无法下移"));
				return;
			}
			if (!m_pObjList->ExchangeObjAtIndex(m_ProtyListIndex[Index], m_ProtyListIndex[Index + 1]))
			{
				MessageBox(_T("无法上移"));
				return;
			}
			str = m_PropertyList.GetItemText(Index + 1, 1);
			m_PropertyList.SetItemText(Index + 1, 1, m_PropertyList.GetItemText(Index, 1));
			m_PropertyList.SetItemText(Index, 1, str);
			str = m_PropertyList.GetItemText(Index + 1, 2);
			m_PropertyList.SetItemText(Index + 1, 2, m_PropertyList.GetItemText(Index, 2));
			m_PropertyList.SetItemText(Index, 2, str);
			str = m_PropertyList.GetItemText(Index + 1, 3);
			m_PropertyList.SetItemText(Index + 1, 3, m_PropertyList.GetItemText(Index, 3));
			m_PropertyList.SetItemText(Index, 3, str);
			m_PropertyList.SetItemState(Index, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_PropertyList.SetItemState(Index + 1, LVNI_FOCUSED | LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			m_LayerSel_Old = Index + 1;
			HScroll(Index);
			m_PropertyList.SetFocus();
		}
		//Object_Down End
		else
		{
			vector<int> nList;
			for (int i = 0; i < Count; i++)
			{
				nList.push_back(m_ProtyListIndex[m_SelectedObj[i]]);
			}
			if (!m_pObjList->ChangeObjNode(nList))
				MessageBox(_T("无法换向!"));
			else
				m_pView->Invalidate();
		}
		//Object_ChangeNode End
	}
	//Object End
	else
	{
		m_LayerSel_Old = -1;
		if (m_PropertyList.GetSelectedCount() != 1)
			return;
		pos = m_PropertyList.GetFirstSelectedItemPosition();
		while (pos)
		{
			Index = m_PropertyList.GetNextSelectedItem(pos);
		}
		if (Index < 0 || Index >= m_PropertyList.GetItemCount())
			return;
		CString str = m_PropertyList.GetItemText(Index, 1);
		int nLayer = m_pObjList->FindLayerByName(str);
		if (nLayer < 0 || nLayer >= m_pObjList->GetLayerCount())
			return;
		if (nLayer < LayerNum_Default)
		{
			MessageBox(_T("不可移动的图层!"));
			return;
		}
		if (nLayer >= m_pObjList->GetLayerCount() - 1)
		{
			MessageBox(_T("该图层已是最后加工层!"));
			return;
		}
		m_pObjList->LayerMoveDownAtIndex(nLayer);
		str = m_PropertyList.GetItemText(Index, 1);
		str1 = m_PropertyList.GetItemText(Index + 1, 1);
		m_PropertyList.SetItemText(Index + 1, 1, str);
		m_PropertyList.SetItemText(Index, 1, str1);
		str = m_PropertyList.GetItemText(Index, 2);
		str1 = m_PropertyList.GetItemText(Index + 1, 2);
		m_PropertyList.SetItemText(Index + 1, 2, str);
		m_PropertyList.SetItemText(Index, 2, str1);
		str = m_PropertyList.GetItemText(Index, 3);
		str1 = m_PropertyList.GetItemText(Index + 1, 3);
		m_PropertyList.SetItemText(Index + 1, 3, str);
		m_PropertyList.SetItemText(Index, 3, str1);
		m_PropertyList.SetItemState(Index, LVNI_FOCUSED & LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		m_PropertyList.SetItemState(Index + 1, LVNI_FOCUSED | LVIS_SELECTED,
			LVNI_FOCUSED | LVIS_SELECTED);
		m_LayerSel_Old = Index + 1;
		HScroll(Index);
		m_PropertyList.SetFocus();
	}
	//Layer_Down End
}

void CObjectProperty::OnClickObjectPropertyList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (m_pObjList->IsEmptyObj())
		return;
	CString str;
	int Index, nCount;
	nCount = m_PropertyList.GetSelectedCount();
	if (m_bDispObject)
	{
		//对象列表
		m_pView->m_bObjNodeDisp = false;
		Disp_Machine_Property
		Index = pNMItemActivate->iItem;
		CMachineObj_Comm* pObj;
		ClearActiveLayerSel();
		if (nCount < 1)
		{
			//空选
			ClearAllObjSel();
			m_ObjSel_Old = -1;
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
		//空选
		else if (nCount == 1)
		{
			//****单选****
			ClearAllObjSel();
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			if (Index == m_ObjSel_Old)
			{
				//再次选中同一行,取消选中
				m_ObjSel_Old = -1;
			}
			//选中取消 处理结束
			else
			{
				//选中新行
				m_ObjSel_Old = Index;
				pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
				pObj->m_bIsObjStatus |= IsObjSel;
				m_PropertyList.SetItemState(Index, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
			}
			//选中有效
		}
		//单选 处理结束
		else
		{
			//****多选****
			int Count1 = m_PropertyList.GetItemCount();
			for (int i = 0; i < Count1; i++)
			{
				pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[i]);
				pObj->m_bIsObjStatus &= ~IsObjSel;
			}
			m_ObjSel_Old = Index;
			POSITION pos = m_PropertyList.GetFirstSelectedItemPosition();
			for (int i = 0; i < nCount; i++)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
				pObj = m_pObjList->GetObjAtIndex(m_ProtyListIndex[Index]);
				pObj->m_bIsObjStatus |= IsObjSel;
			}
		}
		//多选 结束
		UIRefreshObject();
	}
	//对象列表 结束
	else
	{
		//图层列表
		Index = pNMItemActivate->iItem;
		if (nCount < 1)
		{
			//空选
			m_pObjList->SetLayerUnSelectAll();
			m_LayerSel_Old = -1;
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
		}
		//空选
		else if (nCount == 1)
		{
			//****单选****
			m_pObjList->SetLayerUnSelectAll();
			m_PropertyList.SetItemState(-1, LVNI_FOCUSED & LVIS_SELECTED,
				LVNI_FOCUSED | LVIS_SELECTED);
			if (Index == m_LayerSel_Old)
			{
				//再次选中同一行,取消选中
				m_LayerSel_Old = -1;
			}
			//选中取消 处理结束
			else
			{
				//选中新行
				m_LayerSel_Old = Index;
				CString str = m_PropertyList.GetItemText(Index, 1);
				CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfName(str);
				pLayer->m_bIsLayerStatus |= IsObjSel;
				m_PropertyList.SetItemState(Index, LVNI_FOCUSED | LVIS_SELECTED,
					LVNI_FOCUSED | LVIS_SELECTED);
			}
			//选中有效
		}
		//单选 处理结束
		else
		{
			//****多选****
			m_LayerSel_Old = Index;
			POSITION pos = m_PropertyList.GetFirstSelectedItemPosition();
			for (int i = 0; i < nCount; i++)
			{
				Index = m_PropertyList.GetNextSelectedItem(pos);
				str = m_PropertyList.GetItemText(Index, 1);
				int nLayer = m_pObjList->FindLayerByName(str);
				CMachinePara_Layer* pLayer = m_pObjList->GetLayerOfNumber(nLayer);
				pLayer->m_bIsLayerStatus = pLayer->m_bIsLayerStatus | IsObjSel;
			}
		}
		//多选 结束
		UIRefreshLayer();
	}
	//图层列表
	UpdateData(FALSE);
	m_pView->Invalidate();
	*pResult = 0;
}

void CObjectProperty::OnObjProtyBtnCombine()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count <= 1)
			return;
		vector<int> nList;
		int Index = m_ProtyListIndex[m_SelectedObj[0]];
		for (int i = 0; i < Count; i++)
		{
			nList.push_back(m_ProtyListIndex[m_SelectedObj[i]]);
		}
		ClearAllObjSel();
		m_pObjList->PolymerObjAtIndex(nList);
		m_pObjList->SetObjSelect(Index);
		m_bDispObject = false;
		OnClickedObjectOrLayer();
		HScroll(m_SelectedObj[0]);
		m_PropertyList.SetFocus();
		m_pView->Invalidate();
	}
	//Object_Combine_Polyline End
	else
	{
		CString str = _T("    合并加工参数相同的图层\n\n");
		str = str + _T("   该操作是不可逆的! 是否继续?");
		if (IDNO == MessageBox(str, _T("合并冗余层"), MB_YESNO))
			return;
		m_pObjList->ClearRedundLayer();
		m_bDispObject = true;
		OnClickedObjectOrLayer();
	}
	//Layer_Combine End
}

void CObjectProperty::OnClickedObjProtyExtend()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count < 1)
			return;
		vector<int> nList;
		for (int i = 0; i < Count; i++)
		{
			nList.push_back(m_ProtyListIndex[m_SelectedObj[i]]);
		}
		if (!m_bDegenerate)
			m_pObjList->ExtendObjAtIndex(nList, gDupNumber, gGapDistance);
		else
			m_pObjList->Degenerate(nList);
		m_bDispObject = false;
		OnClickedObjectOrLayer();
		HScroll(m_SelectedObj[0]);
		m_PropertyList.SetFocus();
		m_pView->Invalidate();
	}
	//Object End
	else
	{

	}
	//Layer End
}

BOOL CObjectProperty::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		CButton* pBTN = ((CButton*)GetDlgItem(IDC_OBJ_PROTY_BTN11));
		if (pBTN->GetState() != 0)
		{
			SetExtenfPara();
			return TRUE;
		}
		pBTN = ((CButton*)GetDlgItem(IDC_OBJ_PROTY_BTN10));
		if (pBTN->GetState() != 0)
		{
			SetFillPara();
			return TRUE;
		}
		pBTN = ((CButton*)GetDlgItem(IDC_BUTTON_OBJECT_START_MARK));
		if (pBTN->GetState() != 0)
		{
			CString str;
			GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->GetWindowText(str);

			if (_T("停止加工") == str)
			{
				//do nothing
			}
			else if (FALSE == m_bLocate)
			{
				m_bLocate = TRUE;
				m_strBtnMark = _T("定位加工");
				GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
			}
			else
			{
				m_bLocate = FALSE;
				m_strBtnMark = _T("直接加工");
				GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
			}
		}

		
	}
	return CFormView::PreTranslateMessage(pMsg);
}

void CObjectProperty::OnClickedObjProtyFill()
{
	if (m_bDispObject)
	{
		int Count = m_SelectedObj.size();
		if (Count < 1)
			return;
		vector<int> nList;
		for (int i = 0; i < Count; i++)
		{
			nList.push_back(m_ProtyListIndex[m_SelectedObj[i]]);
		}
		if (!m_bDegenerate)
		{
			FillPara para1, para2, para3, para4;
			para1.FillAngle = gFillAngle0;
			para1.FillGap = gFillGap0;
			para1.Curtail = gCurtail0;
			para1.FillMode = gFillMode0;
			para1.GapMode = gGapMode0;
			para1.IsEnable = gFillEnable0;
			para2.FillAngle = gFillAngle1;
			para2.FillGap = gFillGap1;
			para2.Curtail = gCurtail1;
			para2.FillMode = gFillMode1;
			para2.GapMode = gGapMode1;
			para2.IsEnable = gFillEnable1;
			para3.FillAngle = gFillAngle2;
			para3.FillGap = gFillGap2;
			para3.Curtail = gCurtail2;
			para3.FillMode = gFillMode2;
			para3.GapMode = gGapMode2;
			para3.IsEnable = gFillEnable2;
			para4.FillAngle = gFillAngle3;
			para4.FillGap = gFillGap3;
			para4.Curtail = gCurtail3;
			para4.FillMode = gFillMode3;
			para4.GapMode = gGapMode3;
			para4.IsEnable = gFillEnable3;
			m_pObjList->FillObjAtIndex(nList, gFillOutlinePrior, para1, para2, para3, para4);
		}
			
		else
			m_pObjList->Degenerate(nList);
		m_bDispObject = false;
		OnClickedObjectOrLayer();
		HScroll(m_SelectedObj[0]);
		m_PropertyList.SetFocus();
		m_pView->Invalidate();
	}
	//Object End
	else
	{

	}
	//Layer End
}

void CObjectProperty::OnClickedObjProtyBtn15()
{
	if (!m_bDispObject)
	{
		Disp_Machine_Property
			return;
	}
	else if (m_Edit_pObj != NULL)
	{
		int nType = m_Edit_pObj->GetObjType();
		switch (nType)
		{
		case MachineObj_Type_Point:

			break;
		case MachineObj_Type_Line:
			ExchangeLineStartAndEnd(m_Edit_pObj);
			break;
		case MachineObj_Type_Circle:
			ExchangeCircleStartAndEnd(m_Edit_pObj);
			break;
		case MachineObj_Type_Arc:
			ExchangeArcStartAndEnd(m_Edit_pObj);
			break;
		case MachineObj_Type_Ellipse:
			ExchangeEllipseStartAndEnd(m_Edit_pObj);
			break;
		case MachineObj_Type_ArcEll:
			ExchangeArcEllStartAndEnd(m_Edit_pObj);
			break;
		case MachineObj_Type_TiltEllipse:
			ExchangeTiltEllipseStartAndEnd(m_Edit_pObj);
			break;
		case MachineObj_Type_Polyline:
			ExchangePolylineStartAndEnd(m_Edit_pObj);
		default:
			break;
		}
		return;
	}
}

void CObjectProperty::OnClickedObjProtyBtn16()
{
	if (!m_bDispObject)
	{
		Disp_Machine_Property
		return;
	}
	else if (m_Edit_pObj != NULL)
	{
		int nType = m_Edit_pObj->GetObjType();
		switch (nType)
		{
		case MachineObj_Type_Point:
			SavePoint(m_Edit_pObj);
			break;
		case MachineObj_Type_Line:
			SaveLineModify(m_Edit_pObj);
			break;
		case MachineObj_Type_Circle:
			SaveCircleModify(m_Edit_pObj);
			break;
		case MachineObj_Type_Arc:
			SaveArcModify(m_Edit_pObj);
			break;
		case MachineObj_Type_Ellipse:
			SaveEllipseModify(m_Edit_pObj);
			break;
		case MachineObj_Type_ArcEll:
			SaveArcEllModify(m_Edit_pObj);
			break;
		case MachineObj_Type_TiltEllipse:
			SaveTiltEllipseModify(m_Edit_pObj);
			break;
		case MachineObj_Type_Polyline:
			SavePolylineModify(m_Edit_pObj);
			break;
		case MachineObj_Type_Group:
			SaveGroupModify(m_Edit_pObj);
			break;
		case MachineObj_Type_WLine:
			SaveWiden();
			break;
		case MachineObj_Type_WArc:
			SaveWiden();
			break;
		case MachineObj_Type_WPolyline:
			SaveWiden();
			break;
		case MachineObj_Type_FillPolyline:
			SaveFill();
			break;
		default:
			break;
		}
	}
}

void CObjectProperty::OnClickedObjProtyBtn17()
{
	m_pView->m_bObjNodeDisp = false;
	m_pView->Invalidate();
	Disp_Machine_Property
	UIRefreshObject();
}

void CObjectProperty::OnClickedObjProtyBtn18()
{
	if (!m_bDispObject)
	{
		Disp_Machine_Property
			return;
	}
	else if (m_Edit_pObj != NULL)
	{
		int nType = m_Edit_pObj->GetObjType();
		switch (nType)
		{
		case MachineObj_Type_Circle:
			ChangeCircleNode(m_Edit_pObj);
			break;
		case MachineObj_Type_Ellipse:
			ChangeEllipseNode(m_Edit_pObj);
			break;
		case MachineObj_Type_Polyline:
			ClosePolyline(m_Edit_pObj);
			break;
		default:
			break;
		}
		return;
	}
}

void CObjectProperty::OnClickedObjProtyBtn19()
{
	if (!m_bDispObject)
	{
		Disp_Machine_Property
		return;
	}
	else if (m_Edit_pObj != NULL)
	{
		int nType = m_Edit_pObj->GetObjType();
		switch (nType)
		{
		case MachineObj_Type_Polyline:
			LastNodePolyline(m_Edit_pObj);
			break;
		default:
			break;
		}
		return;
	}
}

void CObjectProperty::OnClickedObjProtyBtn20()
{
	if (!m_bDispObject)
	{
		Disp_Machine_Property
			return;
	}
	else if (m_Edit_pObj != NULL)
	{
		int nType = m_Edit_pObj->GetObjType();
		switch (nType)
		{
		case MachineObj_Type_Polyline:
			NextNodePolyline(m_Edit_pObj);
			break;
		default:
			break;
		}
		return;
	}
}

void CObjectProperty::OnClickedObjProtyCheck1()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_OBJ_PROTY_CHECK1);
	if (pBtn->GetCheck())
	{
		GetDlgItem(IDC_OBJ_PROTY_EDIT14)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT15)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT16)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO12)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO13)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJ_PROTY_EDIT14)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT15)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT16)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO12)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO13)->EnableWindow(FALSE);
	}
}

void CObjectProperty::OnClickedObjProtyRadio6()
{
	UpdateData(TRUE);
	if (m_nSel_Old == m_nSelGroup)
		return;
	if (m_nSel_Old > 3 || m_nSelGroup > 3)
		return;
	m_FillPara[m_nSel_Old].FillAngle = m_dVar1;
	m_FillPara[m_nSel_Old].FillGap = m_dVar2;
	m_FillPara[m_nSel_Old].Curtail = m_dVar3;
	m_FillPara[m_nSel_Old].GapMode = m_GapMode;
	m_FillPara[m_nSel_Old].FillMode = m_FillMode;
	if (m_FillEnable)
		m_FillPara[m_nSel_Old].IsEnable = true;
	else
		m_FillPara[m_nSel_Old].IsEnable = false;
	m_nSel_Old = m_nSelGroup;
	m_dVar1 = m_FillPara[m_nSelGroup].FillAngle;
	m_dVar2 = m_FillPara[m_nSelGroup].FillGap;
	m_dVar3 = m_FillPara[m_nSelGroup].Curtail;
	m_GapMode = m_FillPara[m_nSelGroup].GapMode;
	m_FillMode = m_FillPara[m_nSelGroup].FillMode;
	m_FillEnable = m_FillPara[m_nSelGroup].IsEnable;
	if (m_FillEnable)
	{
		GetDlgItem(IDC_OBJ_PROTY_EDIT14)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT15)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT16)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO10)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO11)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO12)->EnableWindow(TRUE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO13)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_OBJ_PROTY_CHECK1))->SetCheck(TRUE);
	}
	else
	{
		GetDlgItem(IDC_OBJ_PROTY_EDIT14)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT15)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_EDIT16)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO10)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO11)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO12)->EnableWindow(FALSE);
		GetDlgItem(IDC_OBJ_PROTY_RADIO13)->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_OBJ_PROTY_CHECK1))->SetCheck(FALSE);
	}
	UpdateData(FALSE);
}


void CObjectProperty::OnBnClickedButtonObjectStartMark()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->GetWindowText(str);

	if (_T("停止加工") == str)
	{
		::SendMessage(m_pView->GetSafeHwnd(), WM_STOP_MARK, NULL, NULL);
		GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(_T("停止加工"));
		::SendMessage(m_pView->GetSafeHwnd(), WM_START_MARK, m_bLocate, NULL);
		GetDlgItem(IDC_BUTTON_OBJECT_START_MARK)->SetWindowText(m_strBtnMark);
	}
}

