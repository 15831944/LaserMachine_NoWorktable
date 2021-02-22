#ifndef MARKAPI_H
#define MARKAPI_H

#include "StdAfx.h"
#include <string.h>
#include <iostream>
#include<Windows.h>

#include <vector>

using namespace std;

#define BSL_BUFFER_SIZE			256

//���к���������һ������ֵ
#define BSL_ERR_WRONGPARAM		-1 //����Ĳ�������
#define BSL_ERR_SUCCESS         0  //�ɹ�
#define BSL_ERR_BSLCADRUN       1  //����BslCAD������
#define BSL_ERR_NOFINDCFGFILE   2  //�Ҳ���BslCAD.CFG
#define BSL_ERR_FAILEDOPEN      3  //���豸ʧ��
#define BSL_ERR_NODEVICE        4  //û����Ч��lmc1�豸
#define BSL_ERR_HARDVER         5  //�豸�汾����
#define BSL_ERR_DEVCFG          6  //�Ҳ����豸�����ļ�
#define BSL_ERR_STOPSIGNAL      7  //�����ź�
#define BSL_ERR_USERSTOP        8  //�û�ֹͣ
#define BSL_ERR_UNKNOW          9  //��������
#define BSL_ERR_OUTTIME         10 //��ʱ
#define BSL_ERR_NOINITIAL       11 //δ��ʼ��
#define BSL_ERR_READFILE        12 //���ļ�����
#define BSL_ERR_OWRWNDNULL      13 //����Ϊ��
#define BSL_ERR_NOFINDFONT      14 //�Ҳ���ָ�����Ƶ�����
#define BSL_ERR_PENNO           15 //����ıʺ�
#define BSL_ERR_NOTTEXT         16 //ָ�����ƵĶ������ı�����
#define BSL_ERR_SAVEFILE        17 //�����ļ�ʧ��
#define BSL_ERR_NOFINDENT       18 //�Ҳ���ָ������
#define BSL_ERR_STATUE			19 //��ǰ״̬�²���ִ�д˲���

#define BSL_ERR_LOADNEWFILE		20 //������У���ļ�ʧ��
#define BSL_ERR_INCORRECTCALPOINT	21  //�춨��������ȷ�����볬��3x3��
#define BSL_ERR_INCORRECTFILELINE	22  //�ļ���������

#define BSL_ERR_OPENVEC_FAIL	100 //�������ļ�ʧ��

//��ʼ��ȫ��lmc���ƿ�
//hOwrWnd ָӵ���û����뽹��Ĵ��ڣ����ڼ���û���ͣ��Ϣ
typedef int (*BSL_InitDevices)(HWND hOwrWnd);

//����ȫ�����ƿ��������³�ʼ�����еĿ��ƿ�
//hOwrWnd ָӵ���û����뽹��Ĵ��ڣ����ڼ���û���ͣ��Ϣ
typedef int (*BSL_ResetDevices)(HWND hOwrWnd);

//���³�ʼ��ȫ���豸,  (�β��豸ʱ����)
typedef int (*BSL_ReInitDevices)(wchar_t* strDevPath, BOOL bIsAdd);

//��ʾУ���Ի��� type=1 �ŵ�У��
typedef void (*BSL_ShowCaliDlg)(int iType);

//����У���ļ�
//szFileName - У���ļ���
//szParName - ��Ҫ���õĲ�������
typedef void (*BSL_SetCalFile)(wchar_t* szFileName, wchar_t* szParName);

//�����Ƿ�ʹ��У���ļ�
//bEnable - �Ƿ�ʹ��У���ļ�
//szParName - ��Ҫ���õĲ�������
typedef void (*BSL_SetCalFileFlag)(bool bEnable, wchar_t* szParName);

//����XY����
typedef void (*BSL_SetXYFlipFlag)(int iXYFlip, int iXInvert, int iYInvert, wchar_t* szParName);
//���ó�����С
typedef void (*BSL_SetWorkSize)(float fWorkSize, wchar_t* szParName);

//����Ӳ�������˿�
typedef void (*BSL_SetHardwareIOPort)(int iPortNum, wchar_t* szParName);

//��ȡӲ�������˿�
typedef void (*BSL_GetHardwareIOPort)(int& iPortNum, wchar_t* szParName);

//��ȡ���е��豸ID
typedef int (*BSL_GetAllDevices)(vector<wchar_t*>& vDevID);

//��ȡ���е��豸ID  ����������ӿ�
struct STU_DEVID
{
	char szName[30];
};
typedef int (*BSL_GetAllDevices2)(STU_DEVID vDevID[], int* iDevCount);

//��ȡ���в���
typedef int (*BSL_GetAllPara)(vector<wchar_t*>& vParName);

//�����豸�����
typedef int (*BSL_AssocDevPara)(wchar_t* strDevID, wchar_t* strParName);

//�����п��ƿ�
typedef int (*BSL_OpenAllDevice)();

//���ض�ID�Ŀ��ƿ�
typedef int (*BSL_OpenDevice)(wchar_t* strDevID);

//���ƿ�
typedef int (*BSL_CloseAllDevice)();

//�ر��ض�ID�Ŀ��ƿ�
typedef int (*BSL_CloseDevice)(wchar_t* strDevID);

//��ȡ���������״̬
typedef int (*BSL_GetOutPort)(unsigned short& status);

//������ת���ƶ�����
typedef int (*BSL_SetRotateMoveParam)(double dMoveX, double dMoveY,double dCenterX,double dCenterY,double dRotateAng);

//Ԥ��ͼ���ļ�
//�������: strFileName  ͼ���ļ�����
//			hWnd ͼ����ʾ�Ĵ���
typedef int (*BSL_DrawFileInWnd)(wchar_t* strFileName, CWnd* pWnd, bool bDrawAxis);

//Ԥ��ͼ���ļ�
//�������: strFileName  ͼ���ļ�����
//			hWnd ͼ����ʾ�Ĵ���
typedef int (*BSL_DrawFileInWnd2)(wchar_t* strFileName, DWORD dwWndHandle, bool bDrawAxis);

//Ԥ��ͼ���ļ�
//�������: strFileName  ͼ���ļ�����
//			nWidth nHeight ͼ����ʾ�ķ�Χ��С
typedef HBITMAP (*BSL_DrawFileInImg)(wchar_t * strFileName, int nWidth, int nHeight, bool bDrawAxis);

//����ͼ���ļ�
//�������: strFileName  ͼ���ļ�����
typedef int (*BSL_LoadDataFile)(wchar_t* strFileName);
//����ʸ���ļ�
//�������: strFileName  ʸ���ļ�����
typedef int (*BSL_LoadVectorFile)(wchar_t* strFileName, bool bIsCenter);

struct ShapeInfo
{
	unsigned nShapeIndex;
	wstring wszShapeName;
	int iShapeType;

	ShapeInfo()
	{
		nShapeIndex = 0;
		wszShapeName = L"";
		iShapeType = 0;
	}

	ShapeInfo operator=(const ShapeInfo& info)
	{
		nShapeIndex = info.nShapeIndex;
		iShapeType = info.iShapeType;
		wszShapeName = info.wszShapeName;
		return *this;
	}
};
//��ȡĳ���򿪵��ļ��е�ͼ���б�
//�������: strFileName  ͼ���ļ�����
//			vShapes ͼ����Ϣ����
typedef int(*BSL_GetShapesInFile)(wchar_t* strFileName, vector<ShapeInfo>& vShapes);

struct ShapeInfo2
{
	unsigned nShapeIndex;
	char wszShapeName[256];
	int iShapeType;

	ShapeInfo2()
	{
		nShapeIndex = 0;
		memset(wszShapeName, 0, sizeof(wszShapeName));
		iShapeType = 0;
	}

	ShapeInfo2 operator=(const ShapeInfo2& info)
	{
		nShapeIndex = info.nShapeIndex;
		iShapeType = info.iShapeType;
		strcpy_s(wszShapeName, info.wszShapeName);
		return *this;
	}
};
//��ȡĳ���򿪵��ļ��е�ͼ���б�
//�������: strFileName  ͼ���ļ�����
//			vShapes ͼ����Ϣ����
typedef int(*BSL_GetShapesInFile2)(wchar_t* strFileName, ShapeInfo2 vShapes[], int iListCount);

//ж��ͼ���ļ�
//�������: strFileName  ͼ���ļ�����
typedef int (*BSL_UnLoadDataFile)(wchar_t* strFileName);

//��ͼ���ļ����ӵ��豸
//�������: strFileName  ͼ���ļ�����
//			strDevID �豸ID
typedef int (*BSL_AppendFileToDevice)(wchar_t* strFileName, wchar_t* strDevID);

//��ͼ���ļ����豸�������
//�������: strFileName  ͼ���ļ�����
//			strDevID �豸ID
typedef int (*BSL_UnappendFileFromDevice)(wchar_t* strFileName, wchar_t* strDevID);

//��ȡ�豸�Ĺ���ͼ���ļ��б�
//�������: vFileName  ͼ���ļ������б�
//			strDevID �豸ID
typedef int (*BSL_GetAssocFilesOfDevice)(wchar_t* strDevID, vector<wchar_t*>& vFileName);

//��ͼ���ļ����ӵ��豸
//�������: strFileName  ͼ���ļ�����
//			strDevID �豸ID
typedef int (*BSL_UnattachFileToDevice)(wchar_t* strFileName, wchar_t* strDevID);

//���ѡ�����豸�Ĺ��������ļ�
typedef int (*BSL_MarkByDeviceId)(wchar_t* szDevId);

//Ӳ���������ѡ�����豸�Ĺ��������ļ�
typedef int (*BSL_MarkByDeviceIdOfHardwareTrigger)(wchar_t* szDevId, int nMarkCount, BOOL bContinue, int nTriggerPort, int nTriggerLevel);

//���ѡ�����豸�Ĺ��������ļ�
typedef int (*BSL_MarkByDeviceIdEx)(wchar_t* szDevId, int nMarkCount, BOOL bContinue);

//��̵�ǰ���ݿ������������
//�������: bFlyMark = true ʹ�ܷɶ����  bFlyMark = false ʹ�ܷɶ����
typedef int (*BSL_Mark)(wchar_t* szDevId, bool bFlyMark);
typedef int (*BSL_StopMark)(wchar_t* szDevId);

//��̵�ǰ���ݿ����ָ������
//�������: strEntName Ҫ�ӹ���ָ�����������
typedef int (*BSL_MarkEntity)(wchar_t* szDevId, wchar_t* szFileName, wchar_t* strEntName);

//�ɶ���̵�ǰ���ݿ����ָ������
//�������: strEntName �ɶ����ָ�����������
typedef int (*BSL_MarkEntityFly)(wchar_t* szDevId, wchar_t* strEntName);

// ��lmc1������˿�
//�������: ���������˿ڵ�����
typedef int (*BSL_ReadPort)(wchar_t* szDevId, unsigned short& data);

// ��lmc1������˿�
//�������: ���������˿ڵ�����
typedef int (*BSL_ReadOutPort)(wchar_t* szDevId, unsigned short& data);

//��ȡ�������ĸ������״̬
typedef int (*BSL_GetLaserPortState)(wchar_t* szDevId, unsigned short& data);

// дlmc1������˿�
//�������: 
// szDevId - �豸ID
// portNum - ����˿�, Ŀǰ��Ч�˿�Ϊ0-7
// nMode - ���ģʽ, 0-��ƽ��1-���壬2-����
// nLevel- �����ƽ, 0-�͵�ƽ��1-�ߵ�ƽ
// nPulse - �������� ,us�� 0-65535us,�� nMode=1����ģʽʱ��Ч
//
typedef int (*BSL_WritePort)(wchar_t* szDevId, unsigned short portNum, unsigned short nMode, unsigned short nLevel,unsigned nPulse);


//�õ���ǰ���ݿ�����������ݵ�Ԥ��ͼ��
//�������: pWnd         Ԥ��ͼ����ʾ���ĸ�����
//          nBMPWIDTH    Ԥ��ͼ��Ŀ��
//          nBMPHEIGHT   Ԥ��ͼ��ĸ߶�
typedef HBITMAP  (*BSL_GetPrevBitmap)(HWND hwnd,int nBMPWIDTH,int nBMPHEIGHT);


//���������豸�����ĶԻ���
typedef int (*BSL_DisplayDevCfgDlg)();

//���õ�ǰ��������������Ҫ�����ݿ���������ı�����ʱ��ʹ�ô��������
typedef int (*BSL_SetFontParam)(wchar_t* strFontName,//��������
					 double dCharHeight,//�ַ��߶�
					 double dCharWidth,//�ַ����
					 double dCharAngle,//�ַ����
					 double dCharSpace,//�ַ����
					 double dLineSpace,//�м��
					 bool   bEqualCharWidth);//���ַ����ģʽ

//�õ�ָ���ʺŶ�Ӧ�ļӹ�����
//typedef int (*BSL_GetPenParam)(int nPenNo,//Ҫ���õıʺ�(0-255)					 
//					 int&      nMarkLoop,//�ӹ�����
//					 double&   dMarkSpeed,//��̴���mm/s
//					 double&   dPowerRatio,//���ʰٷֱ�(0-100%)	
//					 double&   dCurrent,//����A
//					 int&      nFreq,//Ƶ��HZ
//					 int&      nQPulseWidth,//Q������us	
//					 int&      nStartTC,//��ʼ��ʱus
//					 int&      nLaserOffTC,//����ر���ʱus 
//					 int&      nEndTC,//������ʱus
//					 int&      nPolyTC,//�ս���ʱus   //	
//					 double&   dJumpSpeed, //��ת�ٶ�mm/s
//					 int&      nJumpPosTC, //��תλ����ʱus
//					 int&      nJumpDistTC,//��ת������ʱus	
//					 double&   dEndComp,//ĩ�㲹��mm
//					 double&   dAccDist,//���پ���mm	
//					 double&   dPointTime,//�����ʱ ms						 
//					 bool&     bPulsePointMode,//�����ģʽ 
//					 int&      nPulseNum,//�������Ŀ
//					 double&   dFlySpeed);
//����ָ���ʺŶ�Ӧ�ļӹ�����
//typedef int (*BSL_SetPenParam)(int  nPenNo,//Ҫ���õıʺ�(0-255)					 
//					 int      nMarkLoop,//�ӹ�����
//					 double   dMarkSpeed,//��̴���mm/s
//					 double   dPowerRatio,//���ʰٷֱ�(0-100%)	
//					 double   dCurrent,//����A
//					 int      nFreq,//Ƶ��HZ
//					 int      nQPulseWidth,//Q������us	
//					 int      nStartTC,//��ʼ��ʱus
//					 int      nLaserOffTC,//����ر���ʱus 
//					 int      nEndTC,//������ʱus
//					 int      nPolyTC,//�ս���ʱus   //	
//					 double   dJumpSpeed, //��ת�ٶ�mm/s
//					 int      nJumpPosTC, //��תλ����ʱus
//					 int      nJumpDistTC,//��ת������ʱus	
//					 double   dEndComp,//ĩ�㲹��mm
//					 double   dAccDist,//���پ���mm	
//					 double   dPointTime,//�����ʱ ms						 
//					 bool     bPulsePointMode,//�����ģʽ 
//					 int      nPulseNum,
//					 double   dFlySpeed);//�������Ŀ

//�õ�ָ���ʺŶ�Ӧ�ļӹ�����
typedef int (*BSL_GetPenParam)(wchar_t* pFileName,	//�ļ�����
					 unsigned int nPenNo,//Ҫ��ȡ�ıʺ�(0-255)					 
					 int&      nMarkLoop,//�ӹ�����
					 double&   dMarkSpeed,//��̴���mm/s
					 double&   dPowerRatio,//���ʰٷֱ�(0-100%)	
					 double&   dCurrent,//����A
					 int&      nFreq,//Ƶ��HZ
					 int&      nQPulseWidth,//Q������us	
					 int&      nStartTC,//��ʼ��ʱus
					 int&      nLaserOffTC,//����ر���ʱus 
					 int&      nEndTC,//������ʱus
					 int&      nPolyTC,//�ս���ʱus   //	
					 double&   dJumpSpeed, //��ת�ٶ�mm/s
					 int&      nJumpPosTC, //��תλ����ʱus
					 int&      nJumpDistTC,//��ת������ʱus	
					 double&   dEndComp,//ĩ�㲹��mm
					 //double&   dAccDist,//���پ���mm	
					 //double&   dPointTime,//�����ʱ ms						 
					 bool&     bPulsePointMode,//�����ģʽ 
					 int&      nPulseNum,//�������Ŀ
					 float&    POINTTIME
					 /*double&   dFlySpeed*/);
//����ָ���ʺŶ�Ӧ�ļӹ�����
typedef int (*BSL_SetPenParam)(wchar_t* pFileName,	//�ļ�����
					 unsigned int  nPenNo,//Ҫ���õıʺ�(0-255)					 
					 int      nMarkLoop,//�ӹ�����
					 double   dMarkSpeed,//��̴���mm/s
					 double   dPowerRatio,//���ʰٷֱ�(0-100%)	
					 double   dCurrent,//����A
					 int      nFreq,//Ƶ��HZ
					 int      nQPulseWidth,//Q������us	
					 int      nStartTC,//��ʼ��ʱus
					 int      nLaserOffTC,//����ر���ʱus 
					 int      nEndTC,//������ʱus
					 int      nPolyTC,//�ս���ʱus   //	
					 double   dJumpSpeed, //��ת�ٶ�mm/s
					 int      nJumpPosTC, //��תλ����ʱus
					 int      nJumpDistTC,//��ת������ʱus	
					 double   dEndComp,//ĩ�㲹��mm
					 //double   dAccDist,//���پ���mm	
					// double   dPointTime,//�����ʱ ms						 
					 bool     bPulsePointMode,//�����ģʽ 
					 int      nPulseNum,
					 float    POINTTIME
					 /*double   dFlySpeed*/);//�������Ŀ

//���ö���ʺ�
typedef int (*BSL_SetShapePenNo)(wchar_t* strFileName, /*�򿪵��ļ�*/
					wchar_t *szEntName,  /*��������*/
					unsigned int  nPenNo); /*�ʺ�*/


//������������������
typedef int (*BSL_ClearEntityLib)(wchar_t* strFileName);  

//���뷽ʽʱ���ִ��������
//   6 ---  5 --- 4
//   |            |
//   |            |
//   7     8      3
//   |            |
//   |            |
//   0 ---  1 --- 2
//�������ı������ݿ���
typedef int (*BSL_AddTextToFile)(
	wchar_t* szFileName,//�ı����ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	wchar_t* pStr,//Ҫ��ӵ��ַ���
	wchar_t* pEntName,//�ַ�����������
	double dPosX,//�ַ��������½ǻ����x����
	double dPosY,//�ַ��������½ǻ����y����
	double dPosZ,//�ַ��������z����
	int    nAlign,//���뷽ʽ0��8
	double dTextRotateAngle,//�ַ����ƻ�����ת�ĽǶ�ֵ(����ֵ)
	int nPenNo,//����ʹ�õļӹ�����
	bool bHatchText);//�Ƿ�����ı�����


//�������ı������ݿ���
typedef int (*BSL_AddTextToFileEx)(
	wchar_t* szFileName,//�ı����ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	wchar_t* pStr,//Ҫ��ӵ��ַ���
	wchar_t* pEntName,//�ַ�����������
	double dPosX,//�ַ��������½ǻ����x����
	double dPosY,//�ַ��������½ǻ����y����
	double dPosZ,//�ַ��������z����
	int    nAlign,//���뷽ʽ0��8
	double dTextRotateAngle,//�ַ����ƻ�����ת�ĽǶ�ֵ(����ֵ)
	int nPenNo,//����ʹ�õļӹ�����
	bool bHatchText,double dHeight,wchar_t* pTextFontName);//�Ƿ�����ı�����


//����ָ��ͼƬ�ļ������ݿ���
typedef int (*BSL_AddVectorToFile)(
	wchar_t* szFileName,	//ͼ���ļ�����(orz�ļ�)
	wchar_t* pFileName,	//Ҫ��ӵ��ļ����� ֧�ֵ��ļ���ezd,dxf,dst,plt,ai,bmp,jpg,tga,png,gif,tiff��
	wchar_t* pEntName,  //��ӵ�ͼԪ��������
	bool   bHatchFile,  //�Ƿ�����ļ����� �����λͼ�ļ��˲�����Ч
	bool bCenter);   //�Ƿ�ʸ��ͼ����


//�������ߵ����ݿ���
typedef int (*BSL_AddCurveToFile)(double ptBuf[][2],//���߶�������
					   int  ptNum,//���߶�����
					   wchar_t* pEntName,//���߶�������
					   int nPenNo,//���߶���ʹ�õıʺ�
					   int bHatch);//�����Ƿ����

//��ָ����IP�Ͷ˿ڷ����ַ���
//�������: m_dwIpAddress	IP��ַ
//			m_strPort       �˿ں�
//          m_dwConnectTimeout     ���ӳ�ʱ
//          m_dwReceiveTimeout     ���ճ�ʱ
//          sendStr                ��������
typedef int (*BSL_SendStrByTcpIp)(DWORD m_dwIpAddress, wchar_t * m_strPort, DWORD m_dwConnectTimeout,DWORD m_dwReceiveTimeout, wchar_t * sendStr);


//�����ֱ�߶ε����ݿ���
typedef int (*BSL_AddLinesToFile)(
	wchar_t* szFileName,//���ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	double ptBuf[][2],//ֱ�߶ζ�������
	int  ptNum,//ֱ�߶ζ�����
	wchar_t* pEntName,//��������
	int nPenNo//���߶���ʹ�õıʺ�
	);

//����һ��㵽���ݿ���
typedef int (*BSL_AddPointToFile)(
	wchar_t* szFileName,//���ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	double ptBuf[][2],//ֱ�߶ζ�������
	int  ptNum,//ֱ�߶ζ�����
	wchar_t* pEntName,//��������
	int nPenNo//���߶���ʹ�õıʺ�
	);

//�����������ߵ����ݿ���
typedef int (*BSL_AddHelixToFile)(wchar_t* szFileName,//���ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	float fLeft,	//���Ͻ�x���꣬ mm
	float fTop,		//���Ͻ�y���꣬ mm
	float fWidth,	//��ȣ� mm
	float fHeight,	//�߶ȣ� mm
	int bDblHelix,	//�Ƿ�˫������ 0-��1-��
	double fSplitAngle,	//��������СȦ��ֽǣ���, (����˫��������)
	unsigned int nType, //�����ݾ��������󣬻����𽥼�С(���ڵ���������)
	unsigned int nDir,//����0-��ʱ��/�������⣻ 1-˳ʱ��/��������(���ڵ���������)
	float fMinRadius,   //�ڲ���С�뾶(���ڵ���������)
	float fMinGap,//��С�����߾�(���ڵ���������)
	float fMaxGap,//��������߾�(���ڵ���������)
	float fGapStep,//�ݾ�仯��,��˫��������ʱ��Ϊ�����߼�ࣩ
	unsigned int nOutCount,//��߽绷��(���ڵ���������)
	unsigned int nInCount,//�ڱ߽绷��(���ڵ���������)
	int nLoopCount,//ѭ������, Ϊ0ʱ����ѭ��(���ڵ���������)
	wchar_t* pEntName,//���߶�������
	int nPenNo,//���߶���ʹ�õıʺ�
	int bHatch);//�����Ƿ����


#define BARCODETYPE_39      0
#define BARCODETYPE_93      1
#define BARCODETYPE_128A    2
#define BARCODETYPE_128B    3
#define BARCODETYPE_128C    4
#define BARCODETYPE_128OPT  5
#define BARCODETYPE_EAN128A 6
#define BARCODETYPE_EAN128B 7
#define BARCODETYPE_EAN128C 8
#define BARCODETYPE_EAN13   9
#define BARCODETYPE_EAN8    10
#define BARCODETYPE_UPCA    11
#define BARCODETYPE_UPCE    12
#define BARCODETYPE_25      13
#define BARCODETYPE_INTER25 14
#define BARCODETYPE_CODABAR 15
#define BARCODETYPE_PDF417  16
#define BARCODETYPE_DATAMTX 17
#define BARCODETYPE_USERDEF  18

#define BARCODEATTRIB_REVERSE          0x0008 //���뷴ת
#define BARCODEATTRIB_HUMANREAD        0x1000 //��ʾ��ʶ���ַ�
#define BARCODEATTRIB_CHECKNUM         0x0004 //��ҪУ����
#define BARCODEATTRIB_PDF417_SHORTMODE 0x0040 //PDF417Ϊ����ģʽ
#define BARCODEATTRIB_DATAMTX_DOTMODE  0x0080 //DataMtrixΪ��ģʽ
#define BARCODEATTRIB_CIRCLEMODE       0x0100 //�Զ����ά��ΪԲģʽ


#define DATAMTX_SIZEMODE_SMALLEST  0
#define DATAMTX_SIZEMODE_10X10     1
#define DATAMTX_SIZEMODE_12X12     2
#define DATAMTX_SIZEMODE_14X14     3
#define DATAMTX_SIZEMODE_16X16     4
#define DATAMTX_SIZEMODE_18X18     5
#define DATAMTX_SIZEMODE_20X20     6
#define DATAMTX_SIZEMODE_22X22     7
#define DATAMTX_SIZEMODE_24X24     8
#define DATAMTX_SIZEMODE_26X26     9
#define DATAMTX_SIZEMODE_32X32     10
#define DATAMTX_SIZEMODE_36X36     11
#define DATAMTX_SIZEMODE_40X40     12
#define DATAMTX_SIZEMODE_44X44     13
#define DATAMTX_SIZEMODE_48X48     14
#define DATAMTX_SIZEMODE_52X52     15
#define DATAMTX_SIZEMODE_64X64     16
#define DATAMTX_SIZEMODE_72X72     17
#define DATAMTX_SIZEMODE_80X80     18
#define DATAMTX_SIZEMODE_88X88     19
#define DATAMTX_SIZEMODE_96X96     20
#define DATAMTX_SIZEMODE_104X104   21
#define DATAMTX_SIZEMODE_120X120   22
#define DATAMTX_SIZEMODE_132X132   23
#define DATAMTX_SIZEMODE_144X144   24
#define DATAMTX_SIZEMODE_8X18     25
#define DATAMTX_SIZEMODE_8X32     26
#define DATAMTX_SIZEMODE_12X26     27
#define DATAMTX_SIZEMODE_12X36     28
#define DATAMTX_SIZEMODE_16X36     29
#define DATAMTX_SIZEMODE_16X48     30
//�������뵽���ݿ���
typedef int (*BSL_AddBarcodeToFile)(
	wchar_t* strFileName,
	wchar_t* pStr,	//�ַ���
	wchar_t* pEntName,//�ַ�����������
	double dPosX, //�ַ����½ǻ���x����
	double dPosY, //�ַ����½ǻ���y����
	double dPosZ, //�ַ�z����
	int    nAlign,//���뷽ʽ0��8
	int    nPenNo,
	int    bHatchText,
	int    nBarcodeType,//��������
	WORD   wBarCodeAttrib,//��������
	double dHeight,//��������ĸ�	
	double dNarrowWidth,//��խģ���	
	double dBarWidthScale[4],//�������	(����խģ������)
	double dSpaceWidthScale[4],//�տ����(����խģ������)
	double dMidCharSpaceScale,//�ַ��������(����խģ������)
	double dQuietLeftScale,//������հ׿�ȱ���(����խģ������)
	double dQuietMidScale,//�����пհ׿�ȱ���(����խģ������)
	double dQuietRightScale,//�����ҿհ׿�ȱ���(����խģ������)	
	double dQuietTopScale,//�����Ͽհ׿�ȱ���(����խģ������)
	double dQuietBottomScale,//�����¿հ׿�ȱ���(����խģ������)						 
	int    nRow,//��ά������
	int    nCol,//��ά������
	int    nCheckLevel,//pdf417�����������0-8
	int    nSizeMode,//DataMatrix�ߴ�ģʽ0-30
	double dTextHeight,//��ʶ���ַ�����߶�
	double dTextWidth,//��ʶ���ַ�������
	double dTextOffsetX,//��ʶ���ַ�X����ƫ��
	double dTextOffsetY,//��ʶ���ַ�Y����ƫ��
	double dTextSpace,//��ʶ���ַ����
	double dDiameter,
	wchar_t* pTextFontName);//�ı���������

// �������к�
typedef int (*BSL_ResetSN)(wchar_t* strFileName);

//���ĵ�ǰ���ݿ����ָ���ı�������ı�
//�������: strFileName		ͼ���ļ�����
//			strTextName     Ҫ�������ݵ��ı����������
//          strTextNew      �µ��ı�����
typedef int (*BSL_ChangeTextByName)(wchar_t* strFileName, wchar_t* strTextName, wchar_t* strTextNew);


//���ĵ�ǰ���ݿ����ָ���ı�Ⱥ�����ĵ����ı�
//�������: strFileName  ͼ���ļ�����
//			strTextName     Ҫ�������ݵ��ı�Ⱥ����������(���Ⱥ��)
//			iElementIndex	Ҫ�������ݵĵ����ı����ı�Ⱥ�����ͼԪ�б��е�������
//          strTextNew      �µ��ı�����
typedef int (*BSL_ChangeTextInGroupByName)(wchar_t* strFileName, wchar_t* strTextName, int iElementIndex, wchar_t* strTextNew);

//���ĵ�ǰ���ݿ����ָ���ı�������ı�
//�������: strFileName		ͼ���ļ�����
//			iShapeIndex     Ҫ�������ݵ��ı�������ͼ���б��е�������
//          strTextNew      �µ��ı�����
typedef int (*BSL_ChangeTextByIndex)(wchar_t* strFileName, int iShapeIndex, wchar_t* strTextNew);

typedef int (*BSL_SetTextEntParam)(wchar_t* szFileName,
	wchar_t* strTextName,
	wchar_t* strFontName,
	double dCharHeight, 
	double dCharWidth, 
	double dCharAngle, 
	double dCharSpace, 
	double dLineSpace,
	bool   bEqualCharWidth);

typedef int (*BSL_GetTextEntParam)(wchar_t* szFileName, //ͼ���ļ���
	wchar_t* strTextName,
	wchar_t*	sFontName,
	double&  dCharHeight, 
	double&  dCharWidth, 
	double&  dCharAngle, 
	double&  dCharSpace, 
	double&  dLineSpace,
	bool&   bEqualCharWidth);

//����index ��ʾ/����ͼԪ
typedef int (*BSL_ShowOrHideEntityByIndex)(wchar_t* strFileName, int iShapeIndex, bool bShow);
//����name ��ʾ/����ͼԪ
typedef int (*BSL_ShowOrHideEntityByName)(wchar_t* strFileName, wchar_t* strTextName, bool bShow);
//����index ��ȡͼԪ����״̬
typedef bool (*BSL_IsEntityVisibleByIndex)(wchar_t* strFileName, int iShapeIndex);
//����name ��ȡͼԪ����״̬
typedef bool (*BSL_IsEntityVisibleByName)(wchar_t* strFileName, wchar_t* strTextName);

//ɾ����ǰ���ݿ����ָ���ı�����
//�������: strFileName		ͼ���ļ�����
//			strEntName      Ҫɾ�����������
typedef bool (*BSL_DeleteEntityByName) (wchar_t* strFileName, wchar_t* strEntName);

//ɾ����ǰ���ݿ�������ж���
//�������: strFileName		ͼ���ļ�����
typedef bool (*BSL_DeleteAllEntityByName) (wchar_t* strFileName);

//������ת�任����
//�������: dCenterX ��ת����x����
//          dCenterY ��ת����y����
//          dRotateAng ��ת�Ƕ�(����ֵ)
typedef void (*BSL_SetRotateParam) (double dCenterX,double dCenterY,double dRotateAng);


//////////////////////////////////////////////////////////////////
//��չ�ắ��

//��չ���ƶ���ָ������λ��
//�������:  szDevId=�豸ID,
//          axis     ��չ��  0 = ��0  1 = ��1
//          GoalPos  ����λ��
typedef int (*BSL_AxisMoveTo) (wchar_t* szDevId, int axis,double GoalPos);

//��չ��У��ԭ��
//�������:  szDevId=�豸ID,axis     ��չ��  0 = ��0  1 = ��1
typedef int (*BSL_AxisCorrectOrigin) (wchar_t* szDevId, int axis);

//�õ���չ��ĵ�ǰ����
//�������:  szDevId=�豸ID,axis��չ��  0 = ��0  1 = ��1
typedef double (*BSL_GetAxisCoor) (wchar_t* szDevId, int axis);

//��չ���ƶ���ָ����������λ��
//�������: szDevId=�豸ID,
//          axis     ��չ��  0 = ��0  1 = ��1
//          nGoalPos  ��������λ��
typedef int (*BSL_AxisMoveToPulse) (wchar_t* szDevId, int axis, double nGoalPos);

//�õ���չ��ĵ�ǰ��������
//�������:  szDevId=�豸ID, axis��չ��  0 = ��0  1 = ��1
typedef int (*BSL_GetAxisCoorPulse) (wchar_t* szDevId, int axis);


//��λ��չ������
//�������:  szDevId=�豸ID, bEnAxis0 = ʹ����0  bEnAxis1 = ʹ����1
typedef double (*BSL_Reset) (wchar_t* szDevId, bool bEnAxis0 , bool bEnAxis1);

//��ȡ��չ�����
typedef int (*BSL_GetAxisParam) (wchar_t* szDevId,  //�豸ID
	wchar_t* szParName,  //������
	int     axis,       //��չ��  0 = ��0  1 = ��1
	USHORT  &ROTAXIS,			// �Ƿ���ת�� 1-�ǣ�0-����
	USHORT	&REVROT,			// �Ƿ�ת	1-��ת��0-��ת
	int		&nAxisDir,			// �û����õģ���չ�᷽��0-3�ֱ��ʾX,Y,Z,U
	USHORT	&nPPR,				// ÿת������
	float	&LPR,				// ÿת�ݼ��,mm
	float	&MINCOORD,			// ��С����,mm
	float	&MAXCOORD,			// �������,mm
	float	&MINPPS,			// ��С�ٶȣ�����/��
	float	&MAXPPS,				// ����ٶȣ�����/��
	float	&RUNPPS,				// ���ת�٣�����/��
	float	&STTPPS,				// ��������ٶ�, ����/s ��STTPPS ����С�� RUNPPS
	float	&ACCTIME,			// ����ʱ��,ms

	USHORT	&nZeroType,			// ������ͣ�0���͵�ƽ��1���ߵ�ƽ��2������
	float	&fZeroPPS,			// ��0�ٶ�, ����/s
	float	&fZeroTimeout,		// ��0��ʱ��s
	USHORT	&AccurToZero,		// �Ƿ�ȷ����
	float	&PPDEC,				// ���ٱ�, ����ת��ʱ��Ч
	USHORT	&nMoMode,			// �������ģʽ: 0-Ĭ��ģʽ�� 1-����ģʽ
	USHORT	&nMoOrignLevel,		// �����ƽ: 1-ԭ���Ǹߵ�ƽ��0-ԭ���ǵ͵�ƽ

	float	&fOrgX,				//ƽ̨ԭ�㣨��㣩,���ڷָ����ƶ���̣���̹�������ʹ��
	float	&fOrgY,				//ƽ̨ԭ�㣨��㣩,���ڷָ����ƶ���̣���̹�������ʹ��
	bool	&bAutoZero,			//�Ƿ��Զ����㣬true x,yͬʱ���㣬���򶼲�����,����ʱ��bBackOriginָ���ķ�ʽ��
	bool	&bBackOrigin,		//���з�ʽ�Ƿ�ֱ��ԭ��,true:ֱ��ԭ�㣬false:ԭ·����,��̹�������ʹ��

		//��չ��У������
	float	&DISLOCCOMPENSATE,	// ��λ����, mm,����е��������Ƚϴ�ʱ����ƽ��ƴͼ�ӹ�ʱ�ᵼ�´�λ�����󣬵��ڴ˲�����������λ����
	float	&GAPCOMPENSATE,      // ��϶����(mm),�������˶�ʱ���ּ�ļ�϶���

	float	&LIGHTOUTDEVIATION,	// ����ʱ�����(ms)
	float	&MARKSPEEDDEVIATION,	// ����ٶ�ƫ��(ms/s)
	float	&ROTTIMEDEVIATION,	// ��תʱ��ƫ��(ms/s)
	float	&POINTDISTENCE,		// �������뷧ֵ(mm)

	float	&GVSX,				//XͰ��ʧ��ϵ��
	float	&GVSY,				//YͰ��ʧ��ϵ��
	float	&GVT				//����ʧ��ϵ��
	);	


//�����������Զ���
#define FONTATB_JSF        0x0001        //JczSingle����
#define FONTATB_TTF        0x0002        //TrueType����   
#define FONTATB_DMF        0x0004        //DotMatrix����   
#define FONTATB_BCF        0x0008        //BarCode����  

//���ͼ�¼
struct FontRecord
{  	
    wchar_t   szFontName[BSL_BUFFER_SIZE];     //��������	    
    DWORD   dwFontAttrib;       //��������
};

//�õ���ǰϵͳ֧�ֵ������������
//�������: ��
//�������: vFonts ��������
typedef int (*BSL_GetAllFonts) (vector<FontRecord>& vFonts);

//���浱ǰ���ݿ������ж���ָ��ͼ���ļ���
//�������: strFileName ͼ���ļ�����
typedef int (*BSL_SaveEntLibToFile) (wchar_t* strFileName);

//�ƶ�����ĳһ��
typedef int (*BSL_GoToPos)(wchar_t* szDevId, double x, double y);


//�õ�ָ������������С����
typedef int (*BSL_GetEntSizeByIndex) (wchar_t* strFileName,
	int iIndex,
	double& dMinx,
	double& dMiny,
	double& dMaxx,
	double& dMaxy,
	double& dZ);

//�õ�ָ������������С����
typedef int (*BSL_GetEntSizeByName) (wchar_t* strFileName,
	wchar_t* strEntName,//��������
	double& dMinx,
	double& dMiny,
	double& dMaxx,
	double& dMaxy,
    double& dZ);

// ����ѡ��ͼԪ
typedef int(*BSL_CopyEntByIndex) (wchar_t* strFileName, int iIndex, wchar_t* pNewEntName);

// ����ѡ��ͼԪ
typedef int(*BSL_CopyEntByName) (wchar_t* strFileName, wchar_t* strEntName, wchar_t* pNewEntName);

//�ƶ�ָ�������������
//iIndex ����������
typedef int (*BSL_MoveEntityRelByIndex) (wchar_t* strFileName, int iIndex, double dMovex, double dMovey);

//�ƶ�ָ�������������
//strEntName ��������
typedef int (*BSL_MoveEntityRelByName) (wchar_t* strFileName, wchar_t* strEntName, double dMovex, double dMovey);

//�ƶ�ָ�������������
//iIndex ����������
typedef int(*BSL_MoveEntityAbsByIndex) (wchar_t* strFileName, int iIndex, double dPtx, double dPty);

//�ƶ�ָ�������������
//strEntName ��������
typedef int(*BSL_MoveEntityAbsByName) (wchar_t* strFileName, wchar_t* strEntName, double dPtx, double dPty);

//����ָ������������������(dCenx��dCeny)  dScaleX=X�������ű���  dScaleY=Y�������ű���
typedef int(*BSL_ScaleEntityByIndex) (wchar_t* strFileName,
	int iIndex,//����������
	double dCenx,
	double dCeny,
	double dScaleX,
	double dScaleY);

//����ָ������������������(dCenx��dCeny)  dScaleX=X�������ű���  dScaleY=Y�������ű���
typedef int (*BSL_ScaleEntityByName) (wchar_t* strFileName,
	wchar_t* strEntName,//��������
	double dCenx,
	double dCeny,
	double dScaleX,
	double dScaleY);

//����ָ�����󣬾�����������(dCenx��dCeny)  bMirrorX=TRUE X������  bMirrorY=TRUE Y������
typedef int (*BSL_MirrorEntityByIndex) (wchar_t* strFileName,
	wchar_t* pEntName,//����������
	double dCenx,
	double dCeny,
	bool   bMirrorX,
	bool   bMirrorY);

//����ָ�����󣬾�����������(dCenx��dCeny)  bMirrorX=TRUE X������  bMirrorY=TRUE Y������
typedef int(*BSL_MirrorEntityByName) (wchar_t* strFileName,
	wchar_t* strEntName,//��������
	double dCenx,
	double dCeny,
	bool   bMirrorX,
	bool   bMirrorY);

//��תָ������  
//iIndex����������
//(dCenx��dCeny) ��ת��������
//dAngle=��ת�Ƕ�(��ʱ��Ϊ������λΪ��)
typedef int (*BSL_RotateEntityByIndex) (wchar_t* strFileName, int iIndex, double dCenx, double dCeny, double dAngle);

//��תָ������  
//pEntName ��������
//(dCenx��dCeny) ��ת��������
//dAngle = ��ת�Ƕ�(��ʱ��Ϊ������λΪ��)
typedef int(*BSL_RotateEntityByName) (wchar_t* strFileName, wchar_t* strEntName, double dCenx, double dCeny, double dAngle);

//��תָ������  
//iIndex����������
//(dCenx��dCeny) ��ת��������
//dAngle=��ת�Ƕ�(��ʱ��Ϊ������λΪ��)
typedef int(*BSL_SlopeEntityByIndex) (wchar_t* strFileName, int iIndex, double dCenx, double dCeny, double dx, double dy);

//��תָ������  
//pEntName ��������
//(dCenx��dCeny) ��ת��������
//dAngle = ��ת�Ƕ�(��ʱ��Ϊ������λΪ��)
typedef int(*BSL_SlopeEntityByName) (wchar_t* strFileName, wchar_t* strEntName, double dCenx, double dCeny, double dx, double dy);

//ʹ��һ���豸��ʾ���
//szDevId-�豸ID
//bCountinue - �Ƿ�������ʾ���
typedef int (*BSL_RedLightMark) (wchar_t* szDevId, int bCountinue);

//ʹ��һ���豸��ʾ���
//szDevId-�豸ID
//bCountinue - �Ƿ�������ʾ���
//strFileName - �ļ�����
//vShpIndex - �����ͼ�����
typedef int (*BSL_RedLightMarkByEnt) (wchar_t* szDevId, wchar_t* strFileName,vector<int>&vShpIndex,int bCountinue);

//ʹ��һ���豸��ʾ���
//szDevId-�豸ID
//bCountinue - �Ƿ�������ʾ���
//strFileName - �ļ�����
//vShpIndex - ָ�򱣴�ͼԪ��ŵ�ָ��
//iShpCount - ������ͼԪ����
typedef int (*BSL_RedLightMarkByEnt2) (wchar_t* szDevId, wchar_t* strFileName, int*vShpIndex,int iShpCount,int bCountinue);

//��һ���������һ��ʱ��
//keep-����ʱ�䣬 ms
//pen - ʹ�õıʺ�
typedef int (*BSL_LarseOnPoint)(wchar_t* szDevId,double x, double y, double keep, int pen);//

typedef int (*BSL_MarkLine) (wchar_t* szDevId, double x1, double y1, double x2, double y2, int pen);//

typedef int (*BSL_MarkPoint) (wchar_t* szDevId, double x, double y, double delay, int pen);//

//���һ���
typedef int (*BSL_MarkPoints)(wchar_t* szDevId, vector<POINTF>& vPoints,int nPenNum);//

//�õ���������
//�������:  ��������
typedef int (*BSL_GetEntityCount) (wchar_t * strFileName);

//�õ�ָ����ŵĶ�������
//�������: nEntityIndex ָ����������(Χ: 0 �� (lmc1_GetEntityCount()-1))
//�������: szEntName ���������
typedef int (*BSL_GetEntityNameByIndex) (wchar_t * strFileName, int nEntityIndex, wchar_t szEntName[BSL_BUFFER_SIZE]);

//����ָ����ŵ�ʵ����
//�������: nEntityIndex ָ����������(Χ: 0 �� (lmc1_GetEntityCount()-1))
//�������: szEntName ���������
typedef int(*BSL_SetEntityNameByIndex) (wchar_t * strFileName, int nEntityIndex, wchar_t* strEntName);

//����ָ����ŵ�ʵ����
//�������: nEntityIndex ָ����������(Χ: 0 �� (lmc1_GetEntityCount()-1))
//�������: szEntName ���������
typedef int(*BSL_ChangeEntName) (wchar_t * strFileName, wchar_t szOldEntName[BSL_BUFFER_SIZE], wchar_t szNewEntName[BSL_BUFFER_SIZE]);

// �ƶ�ͼԪλ��
typedef int(*BSL_MoveEntityOrderByIndex) (wchar_t * strFileName, int iIndex, int iOrderOffset);

// ����ͼԪλ��
typedef int(*BSL_ReverseAllEntOrder) (wchar_t * strFileName);

//ͨ��ʵ������ȡ�ʺ�
typedef int(*BSL_GetPenNoByEntName) (wchar_t * strFileName, wchar_t strEntName[BSL_BUFFER_SIZE]);

typedef int (*BSL_GetCurCoor) (double& x, double& y);//

//typedef int (*BSL_GotoPos) (double x,double y);

//�õ�ָ��������ı�
typedef int (*BSL_GetTextByName) (wchar_t * strFileName, wchar_t* strTextName, wchar_t strText[BSL_BUFFER_SIZE]);

//�õ�ָ�������ı���������
typedef int (*BSL_GetFontTypeNameByName) (wchar_t * strFileName, wchar_t* strTextName, int& nFontType, wchar_t strText[BSL_BUFFER_SIZE]);

//�õ�ָ�������ϴδ����ı�
typedef int (*BSL_GetLastMarkTextByName) (wchar_t * strFileName, wchar_t* strTextName, wchar_t strText[BSL_BUFFER_SIZE]);

//����һ�����򲻱��
typedef int(*BSL_MaskArea)(wchar_t* strFileName, POINTF* vPoints, int iPtCount);

 //����߶�
typedef int(*BSL_MarkLines) (wchar_t* szDevId, vector<vector<POINTF>> &lines, int pneNo);

  //����߶� ����c#
typedef int(*BSL_MarkLines2) (wchar_t* szDevId, POINTF vPoints[], int iLineCount, int iPtCount[], int penNum);

//�ֿ���ͼ���ļ��е�ͼ�ζ���
//��̵ķ�Χ������ͼ�ε������Ӿ��δ�С�����ʱ���Զ����ֿ������������Ķ���
//�������: szDevId �豸ID
//          szDocName Ҫ�ӹ����ļ�����
//			dx-�ֿ�Ŀ��
//			dy-�ֿ�ĸ߶�
typedef int (*BSL_MarkBlockByDoc) (wchar_t* szDevId, wchar_t* szDocName, double dx, double dy);

/*
 * ���ݴ���ķֿ�����λ���ҵ���Ӧ�Ŀ�
 * szDocName: �ļ���
 * type ���ֿ����� 0Ϊ���ݳ���ֿ�
 * x��x����ֿ鳤����X����ֿ���
 * y��y����ֿ�����Y����ֿ���
 * centralPoint���ֿ����ĵ�λ��BSL_FindBlockMark
*/
typedef int (*BSL_FindBlockMark) (wchar_t *szDocName,int type,double x,double y,POINTF centralPoint);

struct BlockPosPathCShape
{
	double x;                     //���Ͻ�X����
	double y;			          //���Ͻ�Y����
	double width;		          //�ֿ���
	double height;		          //�ֿ�߶�
}; 


 
#define MAX_SHAPE_FILL_COUNT				4	// 4����䷽ʽ�����ֵ��Ӧ��С��3 added by yjw 2015.05.15

//�������
enum BSL_FILLTYPE{
	BSL_FT_CIRCULAR = 0,		/* ������� */
	BSL_FT_SINGLE_LINE,			/* ����, �ڵ�����ͨ���ǲ��Ͽ� */
	BSL_FT_SINGLE_LINE_BREAK,	/* ���Σ���Խ������������ͼ��ʱ���м��Ͽ�*/
	BSL_FT_MULTI_LINE,			/* ���ߣ�������䣬���߶������˲�����*/
	BSL_FT_MULTI_LINE_TWO_DIR	/* ���ߣ�˫����䣬���߶������˲��������ɼ��ٿ���ʱ��*/
};

enum BSL_FONTTYPE
{
	FT_TRUETYPE = 0,
	FT_SINGLELINE,
	FT_CODEBAR,
	FT_PTMATRIC//,      //�������� 
};


struct BSL_ShapeFillPara
{
	BSL_FILLTYPE m_nFillType;	//�������, 
	int m_nExecuteType;		//���ͼ�ε����㷽ʽ��0=��� 1=��  2=�� 3=�
	int m_nIndex;			//�ڼ������
	BOOL m_bEnable;			//ʹ�ܵ�ǰ���
	BOOL m_bRoundInvert;

	double m_fLineSpacing;	//�߼��
	double m_fMargin;		// �߾�

	BOOL m_fill_rotate;		//�Զ���ת�Ƕȱ��
	double m_fRotateAngle;	//��ת�Ƕ�

	double  m_fstrFillGraduallyMaxs;	//������������������
	float   m_fstrFillGraduallyRange;		//�����������������
	double  m_fstrFillGraduallyRate; //��������仯����
	float   m_fstrFillGraduallyActualRange; //��������ʵ�ʿ��
	BOOL    m_bEnableFillGradually;		//ʹ�ܽ������

	// �������ԶԻ��������Ч��
	BOOL m_bWholeConsider;  /* ������㣬���������ʱ��Ч*/
	BOOL m_bAlongBorder; /* �Ʊ���һ�Σ����������ʱ��Ч*/
	BOOL m_bCrossFill; //�������, by tgf 20180410
	BOOL m_bQuickFill; //�������(���ڵ��ߵ����뵥��˫��), by tgf 20180702
	double m_fAngle;  // �������ת�ĽǶ�(����ֵ)���Ի�����Ч
	UINT m_nFillMarkCount;// ����߱�̴���
	int m_nPenNum;      //�ʺ�
	COLORREF m_cPenColor; //��ɫ
	UINT m_nCircularCount; // �߽绷�����ǳ��Ʊ���һȦ����ĵĻ�,�Ի��������Ч
	double m_fCircularGap;  // ����࣬
	double m_fInnerSpacing;   //ֱ���������ǻ����Ʊ���һȦ�����
	// ע�⣺�����Ʊ���һȦ�������Ʊ���һȦ�����������û�м��ġ�	

	BOOL   m_bArrangeEqually;	//ƽ���ֲ����������Ϊfalse,������������Ч
	double m_fStartPreserve;	// ��ʼ����
	double m_fEndPreserve;		//��������

	BSL_ShapeFillPara()
	{
		m_bEnable = FALSE;
		m_nFillType = BSL_FT_CIRCULAR;
		m_nExecuteType = 0;
		m_bWholeConsider = TRUE;
		m_bAlongBorder = FALSE;
		m_bCrossFill = FALSE;
		m_bQuickFill = FALSE;
		m_fAngle= 0;
		m_nFillMarkCount = 1;
		m_nPenNum = 0;
		m_fLineSpacing = 0.06;
		m_bArrangeEqually = TRUE;
		m_fMargin = 0;
		m_fStartPreserve= 0 ;
		m_fEndPreserve=0;
		m_fInnerSpacing=0;
		m_nCircularCount = 0;
		m_fCircularGap = 0.5;
		m_bRoundInvert = FALSE;
		m_cPenColor = RGB(0,0,0);
		m_fill_rotate= FALSE;
		m_fRotateAngle = 0;
		m_fstrFillGraduallyMaxs  = 0.06;
		m_fstrFillGraduallyRange = 6;
		m_fstrFillGraduallyRate = 0.006;
		m_fstrFillGraduallyActualRange = 6;
	}		
};


struct BSL_FillPara
{
	/*ʹ��������/���Ʊ���һ�Σ�
	 * 0:�����������Ʊ���һ�Σ�1:���������Ʊߣ�2�������������Ʊߣ�3:���������Ʊ�
	 * ������������������ʱ�������������ǰ����������������������������ߺ�
	 * �Ʊ�һ�εı�̣����������֮��
	 */
	int m_bOutLine;		
	BOOL m_bOutLineFirst;	//�Ƿ��ȱ������
	BOOL m_bKeepSeperate;   //����������Ķ���
	BOOL m_bDelUngroup;		//ɾ�����ʱ�Ƿ��ɢȺ��
	BSL_ShapeFillPara m_arrPar[MAX_SHAPE_FILL_COUNT];   //�������
	BSL_FillPara()
	{
		m_bOutLine = TRUE;
		m_bOutLineFirst = TRUE;
		m_bKeepSeperate = FALSE;
		m_bDelUngroup = TRUE;
		BOOL bFirstParEnabled = TRUE;
		for (UINT i = 0; i < MAX_SHAPE_FILL_COUNT; i++)
		{
			m_arrPar[i].m_bEnable = bFirstParEnabled;
			m_arrPar[i].m_nPenNum = 0;
			m_arrPar[i].m_nIndex = i;
			bFirstParEnabled = FALSE;
		}
	}
};


//const int HATCHATTRIB_ALLCALC = 0x01;//ȫ��������Ϊ����һ�����
//const int HATCHATTRIB_BIDIR   = 0x08;//˫�����
//const int HATCHATTRIB_EDGE    = 0x02;//��һ�α�
//const int HATCHATTRIB_LOOP    = 0x10;//�������

////���õ�ǰ�������������Ҫ�����ݿ�������¶���ʱʹ�����ʱ����ʹ�ô˲������
//typedef int (*BSL_SetFillParam)(bool bEnableContour,//ʹ����������
//					  int    bEnableHatch1,//ʹ�����1
//					  int    nPenNo1,//����	
//					  int    nHatchAttrib1,//�������
//					  double dHatchEdgeDist1,//����߱߾�
//					  double dHatchLineDist1,//����߼��
//					  double dHatchStartOffset1,//�������ʼƫ�ƾ���
//					  double dHatchEndOffset1,//����߽���ƫ�ƾ���
//					  double dHatchAngle1,//����߽Ƕ�	(����ֵ)
//					  int    bEnableHatch2,//ʹ�����1
//					  int    nPenNo2,//����	
//					  int    nHatchAttrib2,//�������
//					  double dHatchEdgeDist2,//����߱߾�
//					  double dHatchLineDist2,//����߼��
//					  double dHatchStartOffset2,//�������ʼƫ�ƾ���
//					  double dHatchEndOffset2,//����߽���ƫ�ƾ���
//					  double dHatchAngle2);//����߽Ƕ�	(����ֵ)	

//���õ�ǰ�������������Ҫ���ļ�������¶���ʱʹ�����ʱ����ʹ�ô˲������
typedef int (*BSL_SetFillParam)(const BSL_FillPara& fillPar);

//��ȡͼԪ��������
typedef int (*BSL_GetEntFillParam) (wchar_t* szFileName, wchar_t* pHatchName, BSL_FillPara& fillPar);



 /*���������߻�ȡ�������
 * outline - [����]�����ߣ����ɶ���·�����ɣ��߶νӵ�����
 * outlinepnts - [����]ÿ������·���Ľӵ���
 * outlinecount - [����]����·������
 * fillPar - [����]������
 * fillLines - [���]����ߣ����ɶ���·�����ɣ��߶ζ˵�����
 * filllinepnts - [���]ÿ�����·���Ľӵ���
 * filllinecount - [���]���·������
*/
 typedef int(*BSL_GetFillData) (const POINTF outline[], const int outlinepnts[], const int outlinecount, const BSL_FillPara fillPar, POINTF fillLines[], int& filllinecount, int filllinepnts[]);

 //������
 typedef int (*BSL_FillEntity) (wchar_t * strFileName, wchar_t* strEntName, wchar_t* pEntNameNew);
 //ɾ�����
 typedef int (*BSL_UnFillEnt) (wchar_t * strFileName, wchar_t* strEntName, bool bUnGroup);

  //��䵥������
 typedef int (*BSL_FillSingleEntity) (wchar_t * strFileName, int nShapeIndex, wchar_t* pEntNameNew);
 //ɾ���������
 typedef int (*BSL_UnFillSingleEnt) (wchar_t * strFileName, int nShapeIndex, bool bUnGroup);

 //Ⱥ������ʵ�� ��szEntName1��szEntName2 Ⱥ�������ΪszEntName3��Ĭ���ñʺ�1
 typedef int (*BSL_GroupEnt) (wchar_t * strFileName, wchar_t szEntName1[BSL_BUFFER_SIZE],wchar_t  szEntName2[BSL_BUFFER_SIZE],wchar_t  szEntName3[BSL_BUFFER_SIZE],int nPenNo);
 //��ɢȺ��
 typedef int (*BSL_UnGroupEnt) (wchar_t * strFileName, wchar_t szEntName[BSL_BUFFER_SIZE]);

 //typedef int (*BSL_SetFillParam3) (bool bEnableContour,//ʹ����������
 //	int    nParamIndex,//���������ֵΪ1,2,3
 //	int    bEnableHatch,//ʹ�����
 //	int    nPenNo,//����	
 //	int    nHatchType,//������� 0���� 1˫�� 2���� 3���� 4���β�����
 //	bool   bHatchAllCalc,//�Ƿ�ȫ��������Ϊ����һ�����
 //	bool   bHatchEdge,//�Ʊ�һ��
 //	bool   bHatchAverageLine,//�Զ�ƽ���ֲ���
 //	double dHatchAngle,//����߽Ƕ�	
 //	double dHatchLineDist,//����߼��
 //	double dHatchEdgeDist,//����߱߾�					  
 //	double dHatchStartOffset,//�������ʼƫ�ƾ���
 //	double dHatchEndOffset,//����߽���ƫ�ƾ���
 //	double dHatchLineReduction,//ֱ������
 //	double dHatchLoopDist,//�����
 //	int    nEdgeLoop,//����
 //	bool   bHatchLoopRev,//���η�ת
 //	bool   bHatchAutoRotate,//�Ƿ��Զ���ת�Ƕ�
 //	double dHatchRotateAngle,//�Զ���ת�Ƕ�
 //	bool bHatchCross);//�������	


  //ͼԪ�Ǽ���Ϣ,by tgf 20190129
struct EntityInfo
{
	wstring wszDocname;//�ĵ����ƣ�ͼԪ�����ĵ�
	int iIndex;	//���ڴ����λ������
	int iType;		//ͼԪ����
	wstring wszName;//ͼԪ����
	//ͼԪ��Ӿ��ε�ͼֽ����
	double x;		//ͼԪ�󶥵�x���꣨mm��
	double y;		//ͼԪ�󶥵�y���꣨mm��
	double width;	//ͼԪ��ȣ�mm��
	double height;	//ͼԪ�߶ȣ�mm��

	EntityInfo()
	{
		iIndex = -1;
		iType = -1;
		wszName = L"";
		x = 0;
		y = 0;
		width = -1;	//������ʾ����ЧͼԪ
		height = -1;//������ʾ����ЧͼԪ
	}

	EntityInfo operator=(const EntityInfo& info)
	{
		wszDocname = info.wszDocname;
		iIndex = info.iIndex;
		iType = info.iType;
		wszName = info.wszName;
		x = info.x;
		y = info.y;
		width = info.width;
		height = info.height;
		return *this;
	}
};

 //ͼԪ�Ǽ���Ϣ,by tgf 20190129
struct EntityInfoCSharp
{
	char wszDocname[256];//�ĵ����ƣ�ͼԪ�����ĵ�
	int iIndex;	//���ڴ����λ������
	int iType;		//ͼԪ����
	char wszName[256];//ͼԪ����
	//ͼԪ��Ӿ��ε�ͼֽ����
	double x;		//ͼԪ�󶥵�x���꣨mm��
	double y;		//ͼԪ�󶥵�y���꣨mm��
	double width;	//ͼԪ��ȣ�mm��
	double height;	//ͼԪ�߶ȣ�mm��

	EntityInfoCSharp()
	{
		strcpy_s(wszDocname, "");
		iIndex = -1;
		iType = -1;
		strcpy_s(wszName, "");
		x = 0;
		y = 0;
		width = -1;	//������ʾ����ЧͼԪ
		height = -1;//������ʾ����ЧͼԪ
	}

	EntityInfoCSharp operator=(const EntityInfoCSharp& info)
	{
		strcpy_s(wszDocname, info.wszDocname);
		iIndex = info.iIndex;
		iType = info.iType;
		strcpy_s(wszName, info.wszName);
		x = info.x;
		y = info.y;
		width = info.width;
		height = info.height;
		return *this;
	}
};

//�������ͼԪ��Ϣ,by tgf 20190129
//���鲻�ܿ�Խ�ĵ�
struct AreaEntityGroup
{
	//����Χ
	double x;		//ͼԪ�󶥵�x���꣨mm��
	double y;		//ͼԪ�󶥵�y���꣨mm��
	double width;	//ͼԪ��ȣ�mm��
	double height;	//ͼԪ�߶ȣ�mm��

	int nCount;		//������ͼԪ����
	vector<EntityInfo> vEntity;//������ͼԪ

	AreaEntityGroup()
	{
		x = 0;
		y = 0;
		width = -1;	//������ʾ����ЧͼԪ
		height = -1;//������ʾ����ЧͼԪ
	}

	AreaEntityGroup operator=(const AreaEntityGroup& group)
	{
		x = group.x;
		y = group.y;
		width = group.width;
		height = group.height;
		vEntity.assign(group.vEntity.begin(), group.vEntity.end());
		return *this;
	}
};

//��ȡ�����е�ȫ��ͼԪ�Ǽ���Ϣ
//�������: vEntities ͼԪ�Ǽ���Ϣ����
typedef int(*BSL_GetAllEntities)(wchar_t* szDocName, vector<EntityInfo>& vEntities);

//��ȡ�����е���Ӿ���С�ڸ����ߴ��ͼ�Σ����Ұ�����ȫ��ͼԪ�Ǽ���Ϣ
//���������width - ��� mm
//			height - �߶� mm
//�������: vEntities ͼԪ�Ǽ���Ϣ����
typedef int(*BSL_GetEntitiesBySize)(wchar_t* szDocName, double width, double height, vector<AreaEntityGroup>& vGroup);

//���һ�������ڵ�ͼԪ
//by tgf 20190129
//���������szDevId �豸ID
//          group ͼԪ�Ǽ���Ϣ����
typedef int(*BSL_MarkEntitiesInGroup)(wchar_t* szDevId, AreaEntityGroup& group);


/*
 * ��ȡͼԪ�ı��·���� added by tgf 20190813
 * bDoFill - �Ƿ�����������
 * sFileName - �ļ�����
 * sEntName - ͼԪ����
 * outPaths - ͼԪ���·��
 * outPen - ���·�����Ʊʺ�
 * fillPaths - ͼԪ���·��
 * fillPen - ���·�����Ʊʺ�
 */
typedef int(*BSL_GetShapeMarkPaths)(bool bDoFill, wchar_t* sFileName, wchar_t* sShapeName, vector<vector<POINTF>>& outPaths, int& outPen, vector<vector<POINTF>>& fillPaths, int& fillPen);


//�������ͼԪ��Ϣ for C#
//���鲻�ܿ�Խ�ĵ�
struct AreaEntityGroupCSharp
{
	//����Χ
	double x;		//ͼԪ�󶥵�x���꣨mm��
	double y;		//ͼԪ�󶥵�y���꣨mm��
	double width;	//ͼԪ��ȣ�mm��
	double height;	//ͼԪ�߶ȣ�mm��

	int nCount;		//������ͼԪ����
	EntityInfo pEntity[100];//������ͼԪ

	AreaEntityGroupCSharp()
	{
		x = 0;
		y = 0;
		width = -1;	//������ʾ����ЧͼԪ
		height = -1;//������ʾ����ЧͼԪ
	}

	AreaEntityGroupCSharp operator=(const AreaEntityGroupCSharp& group)
	{
		x = group.x;
		y = group.y;
		width = group.width;
		height = group.height;
		for (int i = 0; i < nCount; i++)
		{
			this->pEntity[i] = group.pEntity[i];
		}

		//vEntity.assign(group.vEntity.begin(), group.vEntity.end());
		return *this;
	}
};

//��ȡ�����е�ȫ��ͼԪ�Ǽ���Ϣ for C#
//�������: vEntities ͼԪ�Ǽ���Ϣ����
typedef int(*BSL_GetAllEntities2)(wchar_t* szDocName, int& nCount, EntityInfoCSharp pEntities[]);

//��ȡ�����е���Ӿ���С�ڸ����ߴ��ͼ�Σ����Ұ�����ȫ��ͼԪ�Ǽ���Ϣ   for C#
//���������width - ��� mm
//			height - �߶� mm
//�������: vEntities ͼԪ�Ǽ���Ϣ����
//typedef int(*BSL_GetEntitiesBySize2)(wchar_t* szDocName, double width, double height, int& nCount, AreaEntityGroupCSharp pGroup[]);

//���һ�������ڵ�ͼԪ   for C#
//by tgf 20190129
//���������szDevId �豸ID
//          group ͼԪ�Ǽ���Ϣ����
//typedef int(*BSL_MarkEntitiesInGroup2)(wchar_t* szDevId, AreaEntityGroupCSharp groupC);


//����G-CODE
typedef int(*BSL_ExportGCode)(wchar_t* strFileName, vector<wstring>& vecGCode);
//����G-CODE by name
typedef int(*BSL_ExportGCodeByName)(wchar_t* strFileName, wchar_t* strEntName, vector<wstring>& vecGCode);
//����G-CODE by index
typedef int(*BSL_ExportGCodeByIndex)(wchar_t* strFileName, int iIndex, vector<wstring>& vecGCode);

//C++ API����Ҫc#�ӿ�
////��ȡ���е�GCODE ��c#����
//struct STU_GCODE
//{
//	char wszGCode[256];
//};
////����G-CODE for C#
//typedef int(*BSL_ExportGCode2)(wchar_t* strFileName, STU_GCODE wstrGCode[], int& nCount);
////����G-CODE by name for C#
//typedef int(*BSL_ExportGCodeByName2)(wchar_t* strFileName, wchar_t* strEntName, STU_GCODE wstrGCode[], int& nCount);
////����G-CODE by index for C#
//typedef int(*BSL_ExportGCodeByIndex2)(wchar_t* strFileName, int iIndex, STU_GCODE wstrGCode[], int& nCount);

//��������������ת�Ƕȣ��ȣ���ƫ�ƣ�mm������ת���ģ�mm��
typedef void (*BSL_SetOffsetValues)(double r, double dx,double dy,double cx,double cy);

// //�滻ʸ���ļ�
// szFileName ģ���ļ�
// szFileNameVector ����ʸ���ļ�
// strEntName Ҫ�滻Ϊʸ��ͼ������
typedef int (*BSL_ReplaceVectorFile)(wchar_t* szFileName, wchar_t* szFileNameVector, wchar_t* szEntName);



//������У���ļ�
//�������: strCalFileName  У���ļ�·��
typedef int (*BSL_LoadNewCalFile)(vector<wchar_t*>& vCalFileName);

//������ͼ��
//�������: szDevId			�豸ID
//�������: strCalFileName  У���ļ�·��
typedef int (*BSL_MarkMaxShape)(wchar_t* szDevId, wchar_t* strCalFileName);

//��̾ŵ����
//�������: szDevId			�豸ID
//�������: strCalFileName  У���ļ�·��
//�������: fValSize		��Ч�춨���� mm
//�������: fTagSize		У����ǳߴ� mm
typedef int (*BSL_MarkNinePointRect)(wchar_t* szDevId, wchar_t* strCalFileName, double fValSize, double fTagSize);

//���У�����
//�������: szDevId			�豸ID
//�������: strCalFileName  У���ļ�·��
//�������: fValSize		��Ч�춨���� mm
//�������: fTagSize		У����ǳߴ� mm
//�������: nIndex			У�������б�ǰ����    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
typedef int (*BSL_MarkMultiCalPoint)(wchar_t* szDevId, wchar_t* strCalFileName, double fValSize, double fTagSize, int nIndex);

//�����֤ͼ��
//�������: szDevId			�豸ID
//�������: strCalFileName  У���ļ�·��
//�������: nIndex			У�������б�ǰ����    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
//�������: nGap			�߿��� mm  min(nGap, 5.0)  һ��ȡ5   
typedef int (*BSL_MarkCheckShape)(wchar_t* szDevId, wchar_t* strCalFileName, int nIndex, double nGap);


//����춨����
typedef struct gridCalData{
	double xT;	//���۵�X
	double yT;	//���۵�Y
	double xA;	//ʵ���X
	double yA;	//ʵ���Y
	gridCalData & operator = (const gridCalData &src ){
		xT = src.xT;
		yT = src.yT;
		xA = src.xA;
		yA = src.yA;
		return *this;
	}
}GRIDCALDATA;

//�������ֵ
//�������: nIndex			У�������б�ǰ����    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
//�������: vCalData		����춨��ʵ������
typedef int (*BSL_LoadMeasuredValueFile)(int nIndex, vector<GRIDCALDATA>& vCalData);

//����У���ļ�
//�������: strCalFileName  У���ļ�·��
//�������: nIndex			У�������б�ǰ����    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
//�������: vCalData		����춨�����ۺ�ʵ������
typedef int (*BSL_SaveCalFile)(wchar_t* strCalFileName, int nIndex, vector<GRIDCALDATA> vCalData);


//������Բ�����ݿ���
typedef int (*BSL_AddCircleToFile)(
	wchar_t* szFileName,//Բ���ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	wchar_t* pEntName,//Բ��������
	double dPosX,//Բ���ĵ��x����
	double dPosY,//Բ���ĵ��y����
	double dPosZ,//Բ�����z����
	double dRadius,//Բ�뾶
	double dRotateAngle,//�����ĵ���ת�ĽǶ�ֵ(����ֵ)
	int nPenNo,//����ʹ�õļӹ�����
	bool bFill //�Ƿ�������
	);

//��������Բ�����ݿ���
typedef int (*BSL_AddEllipseToFile)(
	wchar_t* szFileName,//��Բ���ӵ���Ŀ���ļ��������Ӻ���Ȼ��Ҫ�ֶ�������ܱ��浽�ļ���
	wchar_t* pEntName,//��Բ��������
	double dPosX,//��Բ���ĵ��x����
	double dPosY,//��Բ���ĵ��y����
	double dPosZ,//��Բ�����z����
	double dLongAxis,//��Բ����
	double dMinorAxis,//��Բ����
	double dRotateAngle,//�����ĵ���ת�ĽǶ�ֵ(����ֵ)
	int nPenNo,//����ʹ�õļӹ�����
	bool bFill //�Ƿ�������
	);

/*///////////////////////////////
	 _________________  
	|		 |		  | X1
	|		 |		  |
	|		 | a 	  |	
	|--------|--------| X2
	|        |		  |
	|		 |		  |
	|________|________| X3
	Y1       Y2      Y3
/*///////////////////////////////
//���ݵ�ǰ���ݿ����ֹ�У��������ʵ�ʲ������ݼ�������Ƽ�ֵ
//�������: dx_T  X�᷽�����۱߳� mm
//�������: dy_T  Y�᷽�����۱߳� mm
//�������: da_A  �Ƕ�a��ʵ�ʲ����Ƕ�(��)
//�������: dx1_A  ʵ�ʲ�����X1�ĳ��� mm
//�������: dx2_A  ʵ�ʲ�����X2�ĳ��� mm
//�������: dx3_A  ʵ�ʲ�����X3�ĳ��� mm
//�������: dy1_A  ʵ�ʲ�����Y1�ĳ��� mm
//�������: dy2_A  ʵ�ʲ�����Y2�ĳ��� mm
//�������: dy3_A  ʵ�ʲ�����Y3�ĳ��� mm
//�������: dScaleX  X�᷽��ķ�������
//�������: dScaleY  Y�᷽��ķ�������
//�������: dDistorX  X�᷽���Ͱ��ʧ��ϵ��
//�������: dDistorY  Y�᷽���Ͱ��ʧ��ϵ��
//�������: dHorverX  X�᷽���ƽ���ı���ʧ��ϵ��
//�������: dHorverY  Y�᷽���ƽ���ı���ʧ��ϵ��
//�������: dTrapedistorX  X�᷽�������ʧ��ϵ��
//�������: dTrapedistorY  Y�᷽�������ʧ��ϵ��
typedef int (*BSL_GenerateRecommendedValues)(
	double dx_T,
	double dy_T,
	double da_A,
	double dx1_A,
	double dx2_A,
	double dx3_A,
	double dy1_A,
	double dy2_A,
	double dy3_A,
	double& dScaleX,
	double& dScaleY,
	double& dDistorX,
	double& dDistorY,
	double& dHorverX,
	double& dHorverY,
	double& dTrapedistorX,
	double& dTrapedistorY
	);

//�޸ĵ�ǰ���ݿ��е��ֹ�У������
//���������szParName  ��Ҫ���õĲ�������
//�������: dScaleX  X�᷽��ķ�������
//�������: dScaleY  Y�᷽��ķ�������
//�������: dDistorX  X�᷽���Ͱ��ʧ��ϵ��
//�������: dDistorY  Y�᷽���Ͱ��ʧ��ϵ��
//�������: dHorverX  X�᷽���ƽ���ı���ʧ��ϵ��
//�������: dHorverY  Y�᷽���ƽ���ı���ʧ��ϵ��
//�������: dTrapedistorX  X�᷽�������ʧ��ϵ��
//�������: dTrapedistorY  Y�᷽�������ʧ��ϵ��
//�������: bSaveToFile  �Ƿ񱣴浽��׼�����ļ�(BslCAD.cfg)
typedef int (*BSL_ModifyManualCorPara)(
	wchar_t* szParName,
	double dScaleX,
	double dScaleY,
	double dDistorX,
	double dDistorY,
	double dHorverX,
	double dHorverY,
	double dTrapedistorX,
	double dTrapedistorY,
	bool bSaveToFile
	);

//�����豸�����Ĳ��� ��ת�Ƕȣ��ȣ���ƫ�ƣ�mm������ת���ģ�mm��
//��������� szDevId    �豸ID
//��������� szFileName ģ���ļ�
//��������� szParName  ���õĲ�������
//��������� r   ��ת�Ƕ�
//��������� dx  Xƫ��
//��������� dy  Yƫ��
//��������� cx  ��ת����X����
//��������� cy  ��ת����Y����
typedef void (*BSL_SetOffsetValuesOfDevice)(wchar_t* szDevId, wchar_t* szFileName, wchar_t* szParName, double r, double dx,double dy,double cx,double cy);


// ����·�����ݣ��������Ļ���ÿ����䷽ʽһ��ʵ����
typedef struct tagPathData
{
	int nPenIdx;			// �ʺ�
	int nMarkCount;			// ��̴���
	vector<vector<POINTF>> vLine;			// ·��
	tagPathData(){
		nPenIdx = 0;
		nMarkCount = 1;
	}
	tagPathData& operator = (const tagPathData& src){
		nPenIdx = src.nPenIdx;
		nMarkCount = src.nMarkCount;
		vLine.assign(src.vLine.begin(),src.vLine.end());
		return *this;
	}	
}PATHDATA;

//�ʺŲ���
typedef struct tagPenPar{
	int iSwitchOn;			//�ʺ��Ƿ��
	CString strName;		//��������
	wstring wstrName;		//�������ƣ����������л�
	UINT nMachineCount;		//�ӹ���Ŀ
	UINT nRunSpeed;			//�ӹ��ٶ�
	UINT nLaserPower;		//���⹦��
	int nEffectWaitTime;	//���������·��ȴ���Чʱ��,us
	float fCurrent;			//����
	float fLaserFreq;		//����Ƶ��
	float fLaserZkb;		//ռ�ձ�(���˼������µ�Q����)	
	int  nMopaPulse;		//Mopa����
	int iOpenDelay;			//������ʱ us,[-(2^15-1), (2^15-1)]
	int iShutDelay;			//�ع���ʱ	
	int iEndDelay;			//������ʱ
	int iCornerDelay;		//�ս���ʱ
	int iStepDelay;			//������ʱ
	float fStepLen;			//��̲���

	bool bChangeOfCornerDelay;	//�ս���ʱ�Ƿ�ɱ�
	int  nVoltADOutput;			//ʹ�ܵ�ѹ���

	int iDAAdvance;         //DA��ǰ���
	float fOverlapLen;      //�ص�����,mm (�պ�ͼ�ε���β�ص�)
	float fAccLen;          //�������� 
	float fDecLen;          //��������
	float fDAPowerSt;       //DA��ʼ����
	float fDAPowerEnd;      //DA��������
	float fPWMZkbSt;        //PWM��ʼռ�ձ�
	float fPWMZkbEnd;       //PWM����ռ�ձ�


	COLORREF cPenColor;		//�ʺ���ɫ

	//�߼�������ÿ���ʺŶ����Լ��ĸ߼�����, by tgf 20180709
	UINT JUMPSPEED;				//��ת�ٶ�, mm/s
	UINT JUMPPOSITONDELAY;		//��תλ����ʱ,us
	UINT JUMPDISTANCEDELAY;		//��ת������ʱ,us
	UINT ENDCOMP;					//ĩ�㲹��
	UINT ACCDISTANCE;				//�ӵ����
	float POINTTIME;				//���ʱ�� ms
	BOOL PULSEPOINTMODE;			//�Ƿ�ʹ��ʸ�����ģʽ
	UINT PULSEPERPOINT;			//ÿ����������
	BOOL WOBBLE;					//����
	float WOBBLEDIAMETER;			//����ֱ��
	float WOBBLEDISTANCE;			//�������
	BOOL ENDADDPOINT;				//ĩβ�ӵ�
	UINT ADDCOUNT;				//�ӵ���Ŀ
	float  ADDPOINTDISTANCE;		//�ӵ����
	float ADDPOINTTIME;				//���ʱ��
	UINT ADDPOINTCYCLES;			//�ӵ����
	UINT   OPENLIGHTBEHIND;			//�����ͺ�,us, [-2^9, 2^9]������Ӧ�÷��ڱʺŲ����еģ����ڸ�Ϊ���ڸ߼�������

	UINT	JUMPMINDELAY;			//��С��ת��ʱ
	UINT	JUMPMAXDELAY;			//�����ת��ʱ
	UINT	JUMPMAXDISTANCE;		//�����ת����

	tagPenPar()
	{

	}
	tagPenPar& operator=(const tagPenPar& penpar)
	{
		strName					=			penpar.strName;
		wstrName				=			penpar.wstrName;
		ACCDISTANCE = penpar.ACCDISTANCE		;			
		ADDCOUNT				=				penpar.ADDCOUNT			;
		ADDPOINTCYCLES		=				penpar.ADDPOINTCYCLES		;
		ADDPOINTDISTANCE		=				penpar.ADDPOINTDISTANCE	;
		ADDPOINTTIME			=				penpar.ADDPOINTTIME		;
		bChangeOfCornerDelay	=				penpar.bChangeOfCornerDelay;
		cPenColor			=				penpar.cPenColor			;
		ENDADDPOINT			=				penpar.ENDADDPOINT		;
		ENDCOMP				=				penpar.ENDCOMP			;
		fAccLen				=				penpar.fAccLen			;
		fCurrent				=				penpar.fCurrent			;
		fDAPowerEnd			=				penpar.fDAPowerEnd		;
		fDAPowerSt			=				penpar.fDAPowerSt			;
		fDecLen				=				penpar.fDecLen			;
		fLaserFreq			=				penpar.fLaserFreq			;
		fLaserZkb			=				penpar.fLaserZkb			;
		fOverlapLen			=				penpar.fOverlapLen		;
		fPWMZkbEnd			=				penpar.fPWMZkbEnd			;
		fPWMZkbSt			=				penpar.fPWMZkbSt			;
		fStepLen				=				penpar.fStepLen			;
		iCornerDelay			=				penpar.iCornerDelay		;
		iDAAdvance			=				penpar.iDAAdvance			;
		iEndDelay			=				penpar.iEndDelay			;
		iOpenDelay			=				penpar.iOpenDelay			;
		iShutDelay			=				penpar.iShutDelay			;
		iStepDelay			=				penpar.iStepDelay			;
		iSwitchOn			=				penpar.iSwitchOn			;
		JUMPDISTANCEDELAY	=				penpar.JUMPDISTANCEDELAY	;
		JUMPMAXDELAY			=				penpar.JUMPMAXDELAY		;
		JUMPMAXDISTANCE		=				penpar.JUMPMAXDISTANCE	;
		JUMPMINDELAY			=				penpar.JUMPMINDELAY		;
		JUMPPOSITONDELAY		=				penpar.JUMPPOSITONDELAY	;
		JUMPSPEED			=				penpar.JUMPSPEED			;
		nEffectWaitTime		=				penpar.nEffectWaitTime	;
		nLaserPower			=				penpar.nLaserPower		;
		nMachineCount		=				penpar.nMachineCount		;
		nMopaPulse			=				penpar.nMopaPulse			;
		nRunSpeed			=				penpar.nRunSpeed			;
		nVoltADOutput		=				penpar.nVoltADOutput		;
		OPENLIGHTBEHIND		=				penpar.OPENLIGHTBEHIND	;
		POINTTIME			=				penpar.POINTTIME			;
		PULSEPERPOINT		=				penpar.PULSEPERPOINT		;
		PULSEPOINTMODE		=				penpar.PULSEPOINTMODE		;
		WOBBLE				=				penpar.WOBBLE				;
		WOBBLEDIAMETER		=				penpar.WOBBLEDIAMETER		;
		WOBBLEDISTANCE		=				penpar.WOBBLEDISTANCE		;
		return *this;
	}
}PENPAR;
/**
  * ��ȡ�ļ������д��·������
  * szDevId���豸ID
  * szDocName: �ļ���
  * bRotOffset: �Ƿ���ƫ����ת
  * r   ��ת�Ƕ�
  * dx  Xƫ��
  * dy  Yƫ��
  * cx  ��ת����X����
  * cy  ��ת����Y����
  * vMarkPaths������������
  * penpar: ����ʺŲ���
*/
typedef int (*BSL_GetMarkDataPaths)(wchar_t* szDevId, wchar_t * szDocName, bool bRotOffset, double r, double dx,double dy,double cx,double cy, vector<PATHDATA>& vMarkPaths, PENPAR & penpar);

/**
  * ���·����
  * szDevId���豸ID
  * vMarkPaths���������
  * penpar���ʺŲ���
  * szParName  ���ò�������
*/
typedef int (*BSL_MarkDocDataPaths)(wchar_t* szDevId, vector<PATHDATA> vMarkPaths, PENPAR penpar, wchar_t* szParName);


///////////////for C#
/*
typedef struct PathDataShape{
	int nLineCount;		//����   ·����
	POINTF pPoint[10000];	//�����Ҫ�ĵ��������ڴ�ֵ���򷵻�ʧ��,��Ҫ��������ֵ
	int nPtCount[1000];	//����·������ �����Ҫ��ÿ�е��������ڴ�ֵ���򷵻�ʧ��,��Ҫ��������ֵ

}PATHDATASHAPE;
*/

//typedef struct LineDataShape{
struct LineDataShape {
		int nPtCount;		//����   ����
	POINTF pPoint[500];	//�����Ҫ�ĵ��������ڴ�ֵ���򷵻�ʧ��,��Ҫ��������ֵ
	LineDataShape()
	{
		nPtCount = -1;
	}
	LineDataShape operator=(const LineDataShape& info)
	{
		nPtCount = info.nPtCount;
		for (int i = 0; i < nPtCount; i++)
		{
			this->pPoint[i] = info.pPoint[i];
		}
		return *this;
	}
};
//typedef struct PathDataShape{
struct PathDataShape {
		int nPenIdx;			// �ʺ�
	int nMarkCount;			// ��̴���
	int nLineCount;		//����   ·����
	LineDataShape pLine[500];	//�����Ҫ�ĵ��������ڴ�ֵ���򷵻�ʧ��,��Ҫ��������ֵ
	PathDataShape()
	{
		nLineCount = -1;
	}
	PathDataShape operator=(const PathDataShape& info)
	{
		nLineCount = info.nLineCount;
		for (int i = 0; i < nLineCount; i++)
		{
			this->pLine[i] = info.pLine[i];
		}
		return *this;
	}
};

//�ʺŲ���
//typedef struct PenPar{
struct PenPar {
		int iSwitchOn;			//�ʺ��Ƿ��
	char cName[256];		//��������
	char wcName[256];		//�������ƣ����������л�
	UINT nMachineCount;		//�ӹ���Ŀ
	UINT nRunSpeed;			//�ӹ��ٶ�
	UINT nLaserPower;		//���⹦��
	int nEffectWaitTime;	//���������·��ȴ���Чʱ��,us
	float fCurrent;			//����
	float fLaserFreq;		//����Ƶ��
	float fLaserZkb;		//ռ�ձ�(���˼������µ�Q����)	
	int  nMopaPulse;		//Mopa����
	int iOpenDelay;			//������ʱ us,[-(2^15-1), (2^15-1)]
	int iShutDelay;			//�ع���ʱ	
	int iEndDelay;			//������ʱ
	int iCornerDelay;		//�ս���ʱ
	int iStepDelay;			//������ʱ
	float fStepLen;			//��̲���

	bool bChangeOfCornerDelay;	//�ս���ʱ�Ƿ�ɱ�
	int  nVoltADOutput;			//ʹ�ܵ�ѹ���

	int iDAAdvance;         //DA��ǰ���
	float fOverlapLen;      //�ص�����,mm (�պ�ͼ�ε���β�ص�)
	float fAccLen;          //�������� 
	float fDecLen;          //��������
	float fDAPowerSt;       //DA��ʼ����
	float fDAPowerEnd;      //DA��������
	float fPWMZkbSt;        //PWM��ʼռ�ձ�
	float fPWMZkbEnd;       //PWM����ռ�ձ�

	COLORREF cPenColor;		//�ʺ���ɫ

	//�߼�������ÿ���ʺŶ����Լ��ĸ߼�����, by tgf 20180709
	UINT JUMPSPEED;				//��ת�ٶ�, mm/s
	UINT JUMPPOSITONDELAY;		//��תλ����ʱ,us
	UINT JUMPDISTANCEDELAY;		//��ת������ʱ,us
	UINT ENDCOMP;					//ĩ�㲹��
	UINT ACCDISTANCE;				//�ӵ����
	float POINTTIME;				//���ʱ�� ms
	BOOL PULSEPOINTMODE;			//�Ƿ�ʹ��ʸ�����ģʽ
	UINT PULSEPERPOINT;			//ÿ����������
	BOOL WOBBLE;					//����
	float WOBBLEDIAMETER;			//����ֱ��
	float WOBBLEDISTANCE;			//�������
	BOOL ENDADDPOINT;				//ĩβ�ӵ�
	UINT ADDCOUNT;				//�ӵ���Ŀ
	float  ADDPOINTDISTANCE;		//�ӵ����
	float ADDPOINTTIME;				//���ʱ��
	UINT ADDPOINTCYCLES;			//�ӵ����
	UINT   OPENLIGHTBEHIND;			//�����ͺ�,us, [-2^9, 2^9]������Ӧ�÷��ڱʺŲ����еģ����ڸ�Ϊ���ڸ߼�������

	UINT	JUMPMINDELAY;			//��С��ת��ʱ
	UINT	JUMPMAXDELAY;			//�����ת��ʱ
	UINT	JUMPMAXDISTANCE;		//�����ת����

	PenPar()
	{
		strcpy_s(cName, "");
		strcpy_s(wcName, "");
	}

	PenPar operator=(const PenPar& penpar)
	{
		strcpy_s(cName, penpar.cName);
		strcpy_s(wcName, penpar.wcName);
		ACCDISTANCE = penpar.ACCDISTANCE		;			
		ADDCOUNT				=				penpar.ADDCOUNT			;
		ADDPOINTCYCLES		=				penpar.ADDPOINTCYCLES		;
		ADDPOINTDISTANCE		=				penpar.ADDPOINTDISTANCE	;
		ADDPOINTTIME			=				penpar.ADDPOINTTIME		;
		bChangeOfCornerDelay	=				penpar.bChangeOfCornerDelay;
		cPenColor			=				penpar.cPenColor			;
		ENDADDPOINT			=				penpar.ENDADDPOINT		;
		ENDCOMP				=				penpar.ENDCOMP			;
		fAccLen				=				penpar.fAccLen			;
		fCurrent				=				penpar.fCurrent			;
		fDAPowerEnd			=				penpar.fDAPowerEnd		;
		fDAPowerSt			=				penpar.fDAPowerSt			;
		fDecLen				=				penpar.fDecLen			;
		fLaserFreq			=				penpar.fLaserFreq			;
		fLaserZkb			=				penpar.fLaserZkb			;
		fOverlapLen			=				penpar.fOverlapLen		;
		fPWMZkbEnd			=				penpar.fPWMZkbEnd			;
		fPWMZkbSt			=				penpar.fPWMZkbSt			;
		fStepLen				=				penpar.fStepLen			;
		iCornerDelay			=				penpar.iCornerDelay		;
		iDAAdvance			=				penpar.iDAAdvance			;
		iEndDelay			=				penpar.iEndDelay			;
		iOpenDelay			=				penpar.iOpenDelay			;
		iShutDelay			=				penpar.iShutDelay			;
		iStepDelay			=				penpar.iStepDelay			;
		iSwitchOn			=				penpar.iSwitchOn			;
		JUMPDISTANCEDELAY	=				penpar.JUMPDISTANCEDELAY	;
		JUMPMAXDELAY			=				penpar.JUMPMAXDELAY		;
		JUMPMAXDISTANCE		=				penpar.JUMPMAXDISTANCE	;
		JUMPMINDELAY			=				penpar.JUMPMINDELAY		;
		JUMPPOSITONDELAY		=				penpar.JUMPPOSITONDELAY	;
		JUMPSPEED			=				penpar.JUMPSPEED			;
		nEffectWaitTime		=				penpar.nEffectWaitTime	;
		nLaserPower			=				penpar.nLaserPower		;
		nMachineCount		=				penpar.nMachineCount		;
		nMopaPulse			=				penpar.nMopaPulse			;
		nRunSpeed			=				penpar.nRunSpeed			;
		nVoltADOutput		=				penpar.nVoltADOutput		;
		OPENLIGHTBEHIND		=				penpar.OPENLIGHTBEHIND	;
		POINTTIME			=				penpar.POINTTIME			;
		PULSEPERPOINT		=				penpar.PULSEPERPOINT		;
		PULSEPOINTMODE		=				penpar.PULSEPOINTMODE		;
		WOBBLE				=				penpar.WOBBLE				;
		WOBBLEDIAMETER		=				penpar.WOBBLEDIAMETER		;
		WOBBLEDISTANCE		=				penpar.WOBBLEDISTANCE		;
		return *this;
	}
};

/**
  * ��ȡ�ļ������д��·������ for C#
  * szDevId���豸ID
  * szDocName: �ļ���
  * bRotOffset: �Ƿ���ƫ����ת
  * r   ��ת�Ƕ�
  * dx  Xƫ��
  * dy  Yƫ��
  * cx  ��ת����X����
  * cy  ��ת����Y����
  * nCount �����Ŀ
  * pMarkPaths������������
  * penpar   ����ʺŲ���
*/
typedef int (*BSL_GetMarkDataPaths2)(wchar_t* szDevId, wchar_t * szDocName, bool bRotOffset, double r, double dx, double dy, double cx, double cy, int& nCount, PathDataShape pMarkPaths[], PenPar & penpar);

/**
  * ���·���� for C#
  * szDevId���豸ID
  * nCount ��Ŀ
  * pMarkPaths���������
  * penpar   �ʺŲ���
  * szParName  ���ò�������
*/
typedef int (*BSL_MarkDocDataPaths2)(wchar_t* szDevId, int nCount, PathDataShape pMarkPaths[], PenPar penpar, wchar_t* szParName);
///////////////for C#

typedef int (*BSL_SetLasterLenAreaParam)(double workSize, double rotateAngel, double offsetX, double offsetY, wchar_t* szParName);

#endif
