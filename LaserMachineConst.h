// LaserMachineConst.h ���г����ඨ�� 2019/06-07 by Cao
//
#pragma once
#include "MachineObjDef.h"

//����λ�óߴ�
#define	MainWindowsWidth		1680
#define MainWindowsHight		1050
#define ControlWindowsWidth		260
#define ObPrtyWindowsWidth		300
#define CamPosWindowsWidth		300

#define MultipeScroll			1.2		//���������ű���
#define MultipeScrollMin		0.0001	//���������ű���
#define MultipeScrollMax		1.2		//���������ű���
#define MultipeDPToLP			10000000
#define InitBound				CRect(-25000, -25000, 25000, 25000)	//��ʼ�Ӵ���С
#define InitOrgPoint			CPoint(0, 0)				//�豸���߼�����ԭ��ĳ�ʼ��ֵ
#define ScrollStep				10							//������������
#define InitScrollMax			1000						//�����������ʼֵ
#define OrgRectSize				0.02
#define DetaLineHScroll			1			//��������
#define DetaPageHScroll			2			//��������
#define DetaLineVScroll			1			//��������
#define DetaPageVScroll			2			//��������

#define DrawType_Default		0
#define DrawType_Zoom			100
#define DrawType_Select			101

//�豸Ӳ������
#define IPG_Fiber_Laser			1			//IPG���˼�����

//�豸�ӹ������޶�
#define Process_MaxSpeed		50000
#define Process_MinSpeed		0
#define Process_MaxPower		100
#define Process_MinPower		0
#define Process_MaxTime			255
#define Process_MinTime			0
#define Process_MaxFrequncy		50000000
#define Process_MinFrequncy		1
#define Process_MaxPulseWidth	1000000
#define Process_MinPulseWidth	0
#define Process_MaxMode			1
#define Process_MinMode			0
#define Process_MaxDotTime		100000
#define Process_MinDotTime		0

//��Ϣ����
#define WM_CtrlWindows_Size		WM_USER + 10
#define WM_ObPrtyWindows_Size	WM_USER + 11
#define WM_CamPosWindows_Size	WM_USER + 12
#define WM_MainWindows_Resume	WM_USER + 13
#define WM_ObjBound_ReSize		WM_USER + 14
#define WM_Init_ReSize			WM_USER + 15
#define WM_ObjList_Refresh		WM_USER + 16
#define WM_File_MRU_Open		WM_USER + 17

#define WM_GET_CAMERA_HWND		WM_USER + 50


#define WM_START_MARK		WM_USER + 188
#define WM_STOP_MARK		WM_USER + 189
#define ID_TIMEER_MARK_PROCESS_TIME WM_USER+190

