#ifndef MARKAPI_H
#define MARKAPI_H

#include "StdAfx.h"
#include <string.h>
#include <iostream>
#include<Windows.h>

#include <vector>

using namespace std;

#define BSL_BUFFER_SIZE			256

//所有函数都返回一个整形值
#define BSL_ERR_WRONGPARAM		-1 //传入的参数错误
#define BSL_ERR_SUCCESS         0  //成功
#define BSL_ERR_BSLCADRUN       1  //发现BslCAD在运行
#define BSL_ERR_NOFINDCFGFILE   2  //找不到BslCAD.CFG
#define BSL_ERR_FAILEDOPEN      3  //打开设备失败
#define BSL_ERR_NODEVICE        4  //没有有效的lmc1设备
#define BSL_ERR_HARDVER         5  //设备版本错误
#define BSL_ERR_DEVCFG          6  //找不到设备配置文件
#define BSL_ERR_STOPSIGNAL      7  //报警信号
#define BSL_ERR_USERSTOP        8  //用户停止
#define BSL_ERR_UNKNOW          9  //不明错误
#define BSL_ERR_OUTTIME         10 //超时
#define BSL_ERR_NOINITIAL       11 //未初始化
#define BSL_ERR_READFILE        12 //读文件错误
#define BSL_ERR_OWRWNDNULL      13 //窗口为空
#define BSL_ERR_NOFINDFONT      14 //找不到指定名称的字体
#define BSL_ERR_PENNO           15 //错误的笔号
#define BSL_ERR_NOTTEXT         16 //指定名称的对象不是文本对象
#define BSL_ERR_SAVEFILE        17 //保存文件失败
#define BSL_ERR_NOFINDENT       18 //找不到指定对象
#define BSL_ERR_STATUE			19 //当前状态下不能执行此操作

#define BSL_ERR_LOADNEWFILE		20 //加载振镜校正文件失败
#define BSL_ERR_INCORRECTCALPOINT	21  //检定点数不正确，必须超过3x3点
#define BSL_ERR_INCORRECTFILELINE	22  //文件行数不对

#define BSL_ERR_OPENVEC_FAIL	100 //打开向量文件失败

//初始化全部lmc控制卡
//hOwrWnd 指拥有用户输入焦点的窗口，用于检测用户暂停消息
typedef int (*BSL_InitDevices)(HWND hOwrWnd);

//重置全部控制卡，将重新初始化所有的控制卡
//hOwrWnd 指拥有用户输入焦点的窗口，用于检测用户暂停消息
typedef int (*BSL_ResetDevices)(HWND hOwrWnd);

//重新初始化全部设备,  (拔插设备时调用)
typedef int (*BSL_ReInitDevices)(wchar_t* strDevPath, BOOL bIsAdd);

//显示校正对话框 type=1 九点校正
typedef void (*BSL_ShowCaliDlg)(int iType);

//设置校正文件
//szFileName - 校正文件名
//szParName - 将要设置的参数名称
typedef void (*BSL_SetCalFile)(wchar_t* szFileName, wchar_t* szParName);

//设置是否使用校正文件
//bEnable - 是否使能校正文件
//szParName - 将要设置的参数名称
typedef void (*BSL_SetCalFileFlag)(bool bEnable, wchar_t* szParName);

//设置XY反向
typedef void (*BSL_SetXYFlipFlag)(int iXYFlip, int iXInvert, int iYInvert, wchar_t* szParName);
//设置场镜大小
typedef void (*BSL_SetWorkSize)(float fWorkSize, wchar_t* szParName);

//设置硬件触发端口
typedef void (*BSL_SetHardwareIOPort)(int iPortNum, wchar_t* szParName);

//获取硬件触发端口
typedef void (*BSL_GetHardwareIOPort)(int& iPortNum, wchar_t* szParName);

//获取所有的设备ID
typedef int (*BSL_GetAllDevices)(vector<wchar_t*>& vDevID);

//获取所有的设备ID  建议用这个接口
struct STU_DEVID
{
	char szName[30];
};
typedef int (*BSL_GetAllDevices2)(STU_DEVID vDevID[], int* iDevCount);

//获取所有参数
typedef int (*BSL_GetAllPara)(vector<wchar_t*>& vParName);

//关联设备与参数
typedef int (*BSL_AssocDevPara)(wchar_t* strDevID, wchar_t* strParName);

//打开所有控制卡
typedef int (*BSL_OpenAllDevice)();

//打开特定ID的控制卡
typedef int (*BSL_OpenDevice)(wchar_t* strDevID);

//控制卡
typedef int (*BSL_CloseAllDevice)();

//关闭特定ID的控制卡
typedef int (*BSL_CloseDevice)(wchar_t* strDevID);

//获取所有输出口状态
typedef int (*BSL_GetOutPort)(unsigned short& status);

//设置旋转与移动参数
typedef int (*BSL_SetRotateMoveParam)(double dMoveX, double dMoveY,double dCenterX,double dCenterY,double dRotateAng);

//预览图形文件
//输入参数: strFileName  图形文件名称
//			hWnd 图形显示的窗口
typedef int (*BSL_DrawFileInWnd)(wchar_t* strFileName, CWnd* pWnd, bool bDrawAxis);

//预览图形文件
//输入参数: strFileName  图形文件名称
//			hWnd 图形显示的窗口
typedef int (*BSL_DrawFileInWnd2)(wchar_t* strFileName, DWORD dwWndHandle, bool bDrawAxis);

//预览图形文件
//输入参数: strFileName  图形文件名称
//			nWidth nHeight 图形显示的范围大小
typedef HBITMAP (*BSL_DrawFileInImg)(wchar_t * strFileName, int nWidth, int nHeight, bool bDrawAxis);

//加载图形文件
//输入参数: strFileName  图形文件名称
typedef int (*BSL_LoadDataFile)(wchar_t* strFileName);
//加载矢量文件
//输入参数: strFileName  矢量文件名称
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
//获取某个打开的文件中的图形列表
//输入参数: strFileName  图形文件名称
//			vShapes 图形信息容器
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
//获取某个打开的文件中的图形列表
//输入参数: strFileName  图形文件名称
//			vShapes 图形信息容器
typedef int(*BSL_GetShapesInFile2)(wchar_t* strFileName, ShapeInfo2 vShapes[], int iListCount);

//卸载图形文件
//输入参数: strFileName  图形文件名称
typedef int (*BSL_UnLoadDataFile)(wchar_t* strFileName);

//将图形文件附加到设备
//输入参数: strFileName  图形文件名称
//			strDevID 设备ID
typedef int (*BSL_AppendFileToDevice)(wchar_t* strFileName, wchar_t* strDevID);

//将图形文件从设备解除关联
//输入参数: strFileName  图形文件名称
//			strDevID 设备ID
typedef int (*BSL_UnappendFileFromDevice)(wchar_t* strFileName, wchar_t* strDevID);

//获取设备的关联图形文件列表
//输入参数: vFileName  图形文件名称列表
//			strDevID 设备ID
typedef int (*BSL_GetAssocFilesOfDevice)(wchar_t* strDevID, vector<wchar_t*>& vFileName);

//将图形文件附加到设备
//输入参数: strFileName  图形文件名称
//			strDevID 设备ID
typedef int (*BSL_UnattachFileToDevice)(wchar_t* strFileName, wchar_t* strDevID);

//标刻选定的设备的关联数据文件
typedef int (*BSL_MarkByDeviceId)(wchar_t* szDevId);

//硬件触发标刻选定的设备的关联数据文件
typedef int (*BSL_MarkByDeviceIdOfHardwareTrigger)(wchar_t* szDevId, int nMarkCount, BOOL bContinue, int nTriggerPort, int nTriggerLevel);

//标刻选定的设备的关联数据文件
typedef int (*BSL_MarkByDeviceIdEx)(wchar_t* szDevId, int nMarkCount, BOOL bContinue);

//标刻当前数据库里的所有数据
//输入参数: bFlyMark = true 使能飞动打标  bFlyMark = false 使能飞动打标
typedef int (*BSL_Mark)(wchar_t* szDevId, bool bFlyMark);
typedef int (*BSL_StopMark)(wchar_t* szDevId);

//标刻当前数据库里的指定对象
//输入参数: strEntName 要加工的指定对象的名称
typedef int (*BSL_MarkEntity)(wchar_t* szDevId, wchar_t* szFileName, wchar_t* strEntName);

//飞动标刻当前数据库里的指定对象
//输入参数: strEntName 飞动打标指定对象的名称
typedef int (*BSL_MarkEntityFly)(wchar_t* szDevId, wchar_t* strEntName);

// 读lmc1的输入端口
//输入参数: 读入的输入端口的数据
typedef int (*BSL_ReadPort)(wchar_t* szDevId, unsigned short& data);

// 读lmc1的输出端口
//输入参数: 读入的输出端口的数据
typedef int (*BSL_ReadOutPort)(wchar_t* szDevId, unsigned short& data);

//获取激光器四个输入口状态
typedef int (*BSL_GetLaserPortState)(wchar_t* szDevId, unsigned short& data);

// 写lmc1的输出端口
//输入参数: 
// szDevId - 设备ID
// portNum - 输出端口, 目前有效端口为0-7
// nMode - 输出模式, 0-电平，1-脉冲，2-跳变
// nLevel- 输出电平, 0-低电平，1-高电平
// nPulse - 脉冲周期 ,us， 0-65535us,当 nMode=1脉冲模式时有效
//
typedef int (*BSL_WritePort)(wchar_t* szDevId, unsigned short portNum, unsigned short nMode, unsigned short nLevel,unsigned nPulse);


//得到当前数据库里的所有数据的预览图像
//输入参数: pWnd         预览图像显示到哪个窗口
//          nBMPWIDTH    预览图像的宽度
//          nBMPHEIGHT   预览图像的高度
typedef HBITMAP  (*BSL_GetPrevBitmap)(HWND hwnd,int nBMPWIDTH,int nBMPHEIGHT);


//调用设置设备参数的对话框
typedef int (*BSL_DisplayDevCfgDlg)();

//设置当前的字体参数，如果要向数据库里添加新文本对象时会使用此字体参数
typedef int (*BSL_SetFontParam)(wchar_t* strFontName,//字体名称
					 double dCharHeight,//字符高度
					 double dCharWidth,//字符宽度
					 double dCharAngle,//字符倾角
					 double dCharSpace,//字符间距
					 double dLineSpace,//行间距
					 bool   bEqualCharWidth);//等字符宽度模式

//得到指定笔号对应的加工参数
//typedef int (*BSL_GetPenParam)(int nPenNo,//要设置的笔号(0-255)					 
//					 int&      nMarkLoop,//加工次数
//					 double&   dMarkSpeed,//标刻次数mm/s
//					 double&   dPowerRatio,//功率百分比(0-100%)	
//					 double&   dCurrent,//电流A
//					 int&      nFreq,//频率HZ
//					 int&      nQPulseWidth,//Q脉冲宽度us	
//					 int&      nStartTC,//开始延时us
//					 int&      nLaserOffTC,//激光关闭延时us 
//					 int&      nEndTC,//结束延时us
//					 int&      nPolyTC,//拐角延时us   //	
//					 double&   dJumpSpeed, //跳转速度mm/s
//					 int&      nJumpPosTC, //跳转位置延时us
//					 int&      nJumpDistTC,//跳转距离延时us	
//					 double&   dEndComp,//末点补偿mm
//					 double&   dAccDist,//加速距离mm	
//					 double&   dPointTime,//打点延时 ms						 
//					 bool&     bPulsePointMode,//脉冲点模式 
//					 int&      nPulseNum,//脉冲点数目
//					 double&   dFlySpeed);
//设置指定笔号对应的加工参数
//typedef int (*BSL_SetPenParam)(int  nPenNo,//要设置的笔号(0-255)					 
//					 int      nMarkLoop,//加工次数
//					 double   dMarkSpeed,//标刻次数mm/s
//					 double   dPowerRatio,//功率百分比(0-100%)	
//					 double   dCurrent,//电流A
//					 int      nFreq,//频率HZ
//					 int      nQPulseWidth,//Q脉冲宽度us	
//					 int      nStartTC,//开始延时us
//					 int      nLaserOffTC,//激光关闭延时us 
//					 int      nEndTC,//结束延时us
//					 int      nPolyTC,//拐角延时us   //	
//					 double   dJumpSpeed, //跳转速度mm/s
//					 int      nJumpPosTC, //跳转位置延时us
//					 int      nJumpDistTC,//跳转距离延时us	
//					 double   dEndComp,//末点补偿mm
//					 double   dAccDist,//加速距离mm	
//					 double   dPointTime,//打点延时 ms						 
//					 bool     bPulsePointMode,//脉冲点模式 
//					 int      nPulseNum,
//					 double   dFlySpeed);//脉冲点数目

//得到指定笔号对应的加工参数
typedef int (*BSL_GetPenParam)(wchar_t* pFileName,	//文件名称
					 unsigned int nPenNo,//要读取的笔号(0-255)					 
					 int&      nMarkLoop,//加工次数
					 double&   dMarkSpeed,//标刻次数mm/s
					 double&   dPowerRatio,//功率百分比(0-100%)	
					 double&   dCurrent,//电流A
					 int&      nFreq,//频率HZ
					 int&      nQPulseWidth,//Q脉冲宽度us	
					 int&      nStartTC,//开始延时us
					 int&      nLaserOffTC,//激光关闭延时us 
					 int&      nEndTC,//结束延时us
					 int&      nPolyTC,//拐角延时us   //	
					 double&   dJumpSpeed, //跳转速度mm/s
					 int&      nJumpPosTC, //跳转位置延时us
					 int&      nJumpDistTC,//跳转距离延时us	
					 double&   dEndComp,//末点补偿mm
					 //double&   dAccDist,//加速距离mm	
					 //double&   dPointTime,//打点延时 ms						 
					 bool&     bPulsePointMode,//脉冲点模式 
					 int&      nPulseNum,//脉冲点数目
					 float&    POINTTIME
					 /*double&   dFlySpeed*/);
//设置指定笔号对应的加工参数
typedef int (*BSL_SetPenParam)(wchar_t* pFileName,	//文件名称
					 unsigned int  nPenNo,//要设置的笔号(0-255)					 
					 int      nMarkLoop,//加工次数
					 double   dMarkSpeed,//标刻次数mm/s
					 double   dPowerRatio,//功率百分比(0-100%)	
					 double   dCurrent,//电流A
					 int      nFreq,//频率HZ
					 int      nQPulseWidth,//Q脉冲宽度us	
					 int      nStartTC,//开始延时us
					 int      nLaserOffTC,//激光关闭延时us 
					 int      nEndTC,//结束延时us
					 int      nPolyTC,//拐角延时us   //	
					 double   dJumpSpeed, //跳转速度mm/s
					 int      nJumpPosTC, //跳转位置延时us
					 int      nJumpDistTC,//跳转距离延时us	
					 double   dEndComp,//末点补偿mm
					 //double   dAccDist,//加速距离mm	
					// double   dPointTime,//打点延时 ms						 
					 bool     bPulsePointMode,//脉冲点模式 
					 int      nPulseNum,
					 float    POINTTIME
					 /*double   dFlySpeed*/);//脉冲点数目

//设置对象笔号
typedef int (*BSL_SetShapePenNo)(wchar_t* strFileName, /*打开的文件*/
					wchar_t *szEntName,  /*对象名称*/
					unsigned int  nPenNo); /*笔号*/


//清除对象库里所有数据
typedef int (*BSL_ClearEntityLib)(wchar_t* strFileName);  

//对齐方式时数字代表的意义
//   6 ---  5 --- 4
//   |            |
//   |            |
//   7     8      3
//   |            |
//   |            |
//   0 ---  1 --- 2
//加入新文本到数据库中
typedef int (*BSL_AddTextToFile)(
	wchar_t* szFileName,//文本增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	wchar_t* pStr,//要添加的字符串
	wchar_t* pEntName,//字符串对象名称
	double dPosX,//字符串的左下角基点的x坐标
	double dPosY,//字符串的左下角基点的y坐标
	double dPosZ,//字符串对象的z坐标
	int    nAlign,//对齐方式0－8
	double dTextRotateAngle,//字符串绕基点旋转的角度值(弧度值)
	int nPenNo,//对象使用的加工参数
	bool bHatchText);//是否填充文本对象


//加入新文本到数据库中
typedef int (*BSL_AddTextToFileEx)(
	wchar_t* szFileName,//文本增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	wchar_t* pStr,//要添加的字符串
	wchar_t* pEntName,//字符串对象名称
	double dPosX,//字符串的左下角基点的x坐标
	double dPosY,//字符串的左下角基点的y坐标
	double dPosZ,//字符串对象的z坐标
	int    nAlign,//对齐方式0－8
	double dTextRotateAngle,//字符串绕基点旋转的角度值(弧度值)
	int nPenNo,//对象使用的加工参数
	bool bHatchText,double dHeight,wchar_t* pTextFontName);//是否填充文本对象


//加入指定图片文件到数据库中
typedef int (*BSL_AddVectorToFile)(
	wchar_t* szFileName,	//图形文件名称(orz文件)
	wchar_t* pFileName,	//要添加的文件名称 支持的文件有ezd,dxf,dst,plt,ai,bmp,jpg,tga,png,gif,tiff等
	wchar_t* pEntName,  //添加的图元对象名称
	bool   bHatchFile,  //是否填充文件对象 如果是位图文件此参数无效
	bool bCenter);   //是否将矢量图居中


//加入曲线到数据库中
typedef int (*BSL_AddCurveToFile)(double ptBuf[][2],//曲线顶点数组
					   int  ptNum,//曲线顶点数
					   wchar_t* pEntName,//曲线对象名称
					   int nPenNo,//曲线对象使用的笔号
					   int bHatch);//曲线是否填充

//向指定的IP和端口发送字符串
//输入参数: m_dwIpAddress	IP地址
//			m_strPort       端口号
//          m_dwConnectTimeout     连接超时
//          m_dwReceiveTimeout     接收超时
//          sendStr                发送内容
typedef int (*BSL_SendStrByTcpIp)(DWORD m_dwIpAddress, wchar_t * m_strPort, DWORD m_dwConnectTimeout,DWORD m_dwReceiveTimeout, wchar_t * sendStr);


//加入多直线段到数据库中
typedef int (*BSL_AddLinesToFile)(
	wchar_t* szFileName,//增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	double ptBuf[][2],//直线段顶点数组
	int  ptNum,//直线段顶点数
	wchar_t* pEntName,//对象名称
	int nPenNo//曲线对象使用的笔号
	);

//加入一组点到数据库中
typedef int (*BSL_AddPointToFile)(
	wchar_t* szFileName,//增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	double ptBuf[][2],//直线段顶点数组
	int  ptNum,//直线段顶点数
	wchar_t* pEntName,//对象名称
	int nPenNo//曲线对象使用的笔号
	);

//加入螺旋线线到数据库中
typedef int (*BSL_AddHelixToFile)(wchar_t* szFileName,//增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	float fLeft,	//左上角x坐标， mm
	float fTop,		//左上角y坐标， mm
	float fWidth,	//宽度， mm
	float fHeight,	//高度， mm
	int bDblHelix,	//是否双螺旋线 0-否，1-是
	double fSplitAngle,	//螺旋线最小圈拆分角，度, (用于双向螺旋线)
	unsigned int nType, //控制螺距是逐渐增大，还是逐渐减小(用于单向螺旋线)
	unsigned int nDir,//方向：0-逆时针/由内向外； 1-顺时针/由外向内(用于单向螺旋线)
	float fMinRadius,   //内部最小半径(用于单向螺旋线)
	float fMinGap,//最小螺旋线距(用于单向螺旋线)
	float fMaxGap,//最大螺旋线距(用于单向螺旋线)
	float fGapStep,//螺距变化量,（双向螺旋线时，为螺旋线间距）
	unsigned int nOutCount,//外边界环数(用于单向螺旋线)
	unsigned int nInCount,//内边界环数(用于单向螺旋线)
	int nLoopCount,//循环次数, 为0时，不循环(用于单向螺旋线)
	wchar_t* pEntName,//曲线对象名称
	int nPenNo,//曲线对象使用的笔号
	int bHatch);//曲线是否填充


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

#define BARCODEATTRIB_REVERSE          0x0008 //条码反转
#define BARCODEATTRIB_HUMANREAD        0x1000 //显示人识别字符
#define BARCODEATTRIB_CHECKNUM         0x0004 //需要校验码
#define BARCODEATTRIB_PDF417_SHORTMODE 0x0040 //PDF417为缩短模式
#define BARCODEATTRIB_DATAMTX_DOTMODE  0x0080 //DataMtrix为点模式
#define BARCODEATTRIB_CIRCLEMODE       0x0100 //自定义二维码为圆模式


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
//加入条码到数据库中
typedef int (*BSL_AddBarcodeToFile)(
	wchar_t* strFileName,
	wchar_t* pStr,	//字符串
	wchar_t* pEntName,//字符串对象名称
	double dPosX, //字符左下角基点x坐标
	double dPosY, //字符左下角基点y坐标
	double dPosZ, //字符z坐标
	int    nAlign,//对齐方式0－8
	int    nPenNo,
	int    bHatchText,
	int    nBarcodeType,//条码类型
	WORD   wBarCodeAttrib,//条码属性
	double dHeight,//整个条码的高	
	double dNarrowWidth,//最窄模块宽	
	double dBarWidthScale[4],//条宽比例	(与最窄模块宽相比)
	double dSpaceWidthScale[4],//空宽比例(与最窄模块宽相比)
	double dMidCharSpaceScale,//字符间隔比例(与最窄模块宽相比)
	double dQuietLeftScale,//条码左空白宽度比例(与最窄模块宽相比)
	double dQuietMidScale,//条码中空白宽度比例(与最窄模块宽相比)
	double dQuietRightScale,//条码右空白宽度比例(与最窄模块宽相比)	
	double dQuietTopScale,//条码上空白宽度比例(与最窄模块宽相比)
	double dQuietBottomScale,//条码下空白宽度比例(与最窄模块宽相比)						 
	int    nRow,//二维码行数
	int    nCol,//二维码列数
	int    nCheckLevel,//pdf417错误纠正级别0-8
	int    nSizeMode,//DataMatrix尺寸模式0-30
	double dTextHeight,//人识别字符字体高度
	double dTextWidth,//人识别字符字体宽度
	double dTextOffsetX,//人识别字符X方向偏移
	double dTextOffsetY,//人识别字符Y方向偏移
	double dTextSpace,//人识别字符间距
	double dDiameter,
	wchar_t* pTextFontName);//文本字体名称

// 重置序列号
typedef int (*BSL_ResetSN)(wchar_t* strFileName);

//更改当前数据库里的指定文本对象的文本
//输入参数: strFileName		图形文件名称
//			strTextName     要更改内容的文本对象的名称
//          strTextNew      新的文本内容
typedef int (*BSL_ChangeTextByName)(wchar_t* strFileName, wchar_t* strTextName, wchar_t* strTextNew);


//更改当前数据库里的指定文本群组对象的单个文本
//输入参数: strFileName  图形文件名称
//			strTextName     要更改内容的文本群组对象的名称(最大群组)
//			iElementIndex	要更改内容的单个文本在文本群组对象图元列表中的索引号
//          strTextNew      新的文本内容
typedef int (*BSL_ChangeTextInGroupByName)(wchar_t* strFileName, wchar_t* strTextName, int iElementIndex, wchar_t* strTextNew);

//更改当前数据库里的指定文本对象的文本
//输入参数: strFileName		图形文件名称
//			iShapeIndex     要更改内容的文本对象在图形列表中的索引号
//          strTextNew      新的文本内容
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

typedef int (*BSL_GetTextEntParam)(wchar_t* szFileName, //图形文件名
	wchar_t* strTextName,
	wchar_t*	sFontName,
	double&  dCharHeight, 
	double&  dCharWidth, 
	double&  dCharAngle, 
	double&  dCharSpace, 
	double&  dLineSpace,
	bool&   bEqualCharWidth);

//根据index 显示/隐藏图元
typedef int (*BSL_ShowOrHideEntityByIndex)(wchar_t* strFileName, int iShapeIndex, bool bShow);
//根据name 显示/隐藏图元
typedef int (*BSL_ShowOrHideEntityByName)(wchar_t* strFileName, wchar_t* strTextName, bool bShow);
//根据index 获取图元显隐状态
typedef bool (*BSL_IsEntityVisibleByIndex)(wchar_t* strFileName, int iShapeIndex);
//根据name 获取图元显隐状态
typedef bool (*BSL_IsEntityVisibleByName)(wchar_t* strFileName, wchar_t* strTextName);

//删除当前数据库里的指定文本对象
//输入参数: strFileName		图形文件名称
//			strEntName      要删除对象的名称
typedef bool (*BSL_DeleteEntityByName) (wchar_t* strFileName, wchar_t* strEntName);

//删除当前数据库里的所有对象
//输入参数: strFileName		图形文件名称
typedef bool (*BSL_DeleteAllEntityByName) (wchar_t* strFileName);

//设置旋转变换参数
//输入参数: dCenterX 旋转中心x坐标
//          dCenterY 旋转中心y坐标
//          dRotateAng 旋转角度(弧度值)
typedef void (*BSL_SetRotateParam) (double dCenterX,double dCenterY,double dRotateAng);


//////////////////////////////////////////////////////////////////
//扩展轴函数

//扩展轴移动到指定坐标位置
//输入参数:  szDevId=设备ID,
//          axis     扩展轴  0 = 轴0  1 = 轴1
//          GoalPos  坐标位置
typedef int (*BSL_AxisMoveTo) (wchar_t* szDevId, int axis,double GoalPos);

//扩展轴校正原点
//输入参数:  szDevId=设备ID,axis     扩展轴  0 = 轴0  1 = 轴1
typedef int (*BSL_AxisCorrectOrigin) (wchar_t* szDevId, int axis);

//得到扩展轴的当前坐标
//输入参数:  szDevId=设备ID,axis扩展轴  0 = 轴0  1 = 轴1
typedef double (*BSL_GetAxisCoor) (wchar_t* szDevId, int axis);

//扩展轴移动到指定脉冲坐标位置
//输入参数: szDevId=设备ID,
//          axis     扩展轴  0 = 轴0  1 = 轴1
//          nGoalPos  脉冲坐标位置
typedef int (*BSL_AxisMoveToPulse) (wchar_t* szDevId, int axis, double nGoalPos);

//得到扩展轴的当前脉冲坐标
//输入参数:  szDevId=设备ID, axis扩展轴  0 = 轴0  1 = 轴1
typedef int (*BSL_GetAxisCoorPulse) (wchar_t* szDevId, int axis);


//复位扩展轴坐标
//输入参数:  szDevId=设备ID, bEnAxis0 = 使能轴0  bEnAxis1 = 使能轴1
typedef double (*BSL_Reset) (wchar_t* szDevId, bool bEnAxis0 , bool bEnAxis1);

//获取扩展轴参数
typedef int (*BSL_GetAxisParam) (wchar_t* szDevId,  //设备ID
	wchar_t* szParName,  //参数名
	int     axis,       //扩展轴  0 = 轴0  1 = 轴1
	USHORT  &ROTAXIS,			// 是否旋转轴 1-是，0-不是
	USHORT	&REVROT,			// 是否反转	1-反转，0-正转
	int		&nAxisDir,			// 用户设置的，扩展轴方向：0-3分别表示X,Y,Z,U
	USHORT	&nPPR,				// 每转脉冲数
	float	&LPR,				// 每转螺间距,mm
	float	&MINCOORD,			// 最小坐标,mm
	float	&MAXCOORD,			// 最大坐标,mm
	float	&MINPPS,			// 最小速度，脉冲/秒
	float	&MAXPPS,				// 最大速度，脉冲/秒
	float	&RUNPPS,				// 电机转速，脉冲/秒
	float	&STTPPS,				// 电机启动速度, 脉冲/s ，STTPPS 必须小于 RUNPPS
	float	&ACCTIME,			// 加速时间,ms

	USHORT	&nZeroType,			// 零点类型，0：低电平、1：高电平、2：脉冲
	float	&fZeroPPS,			// 回0速度, 脉冲/s
	float	&fZeroTimeout,		// 回0超时，s
	USHORT	&AccurToZero,		// 是否精确回零
	float	&PPDEC,				// 减速比, 是旋转轴时有效
	USHORT	&nMoMode,			// 电机回零模式: 0-默认模式， 1-回零模式
	USHORT	&nMoOrignLevel,		// 电机电平: 1-原点是高电平，0-原点是低电平

	float	&fOrgX,				//平台原点（零点）,用于分割与移动标刻，标刻过程中需使用
	float	&fOrgY,				//平台原点（零点）,用于分割与移动标刻，标刻过程中需使用
	bool	&bAutoZero,			//是否自动回零，true x,y同时回零，否则都不回零,回零时按bBackOrigin指定的方式回
	bool	&bBackOrigin,		//运行方式是否直回原点,true:直回原点，false:原路返回,标刻过程中需使用

		//扩展轴校正参数
	float	&DISLOCCOMPENSATE,	// 错位补偿, mm,当机械制造的误差比较大时，在平面拼图加工时会导致错位的现象，调节此参数可消除错位现象。
	float	&GAPCOMPENSATE,      // 间隙补偿(mm),补偿在运动时齿轮间的间隙误差

	float	&LIGHTOUTDEVIATION,	// 出光时间误差(ms)
	float	&MARKSPEEDDEVIATION,	// 打标速度偏差(ms/s)
	float	&ROTTIMEDEVIATION,	// 旋转时间偏差(ms/s)
	float	&POINTDISTENCE,		// 两点间距离阀值(mm)

	float	&GVSX,				//X桶形失真系数
	float	&GVSY,				//Y桶形失真系数
	float	&GVT				//梯形失真系数
	);	


//字体类型属性定义
#define FONTATB_JSF        0x0001        //JczSingle字型
#define FONTATB_TTF        0x0002        //TrueType字型   
#define FONTATB_DMF        0x0004        //DotMatrix字型   
#define FONTATB_BCF        0x0008        //BarCode字型  

//字型记录
struct FontRecord
{  	
    wchar_t   szFontName[BSL_BUFFER_SIZE];     //字体名字	    
    DWORD   dwFontAttrib;       //字体属性
};

//得到当前系统支持的所有字体参数
//输入参数: 无
//输出参数: vFonts 字体向量
typedef int (*BSL_GetAllFonts) (vector<FontRecord>& vFonts);

//保存当前数据库里所有对象到指定图形文件里
//输入参数: strFileName 图形文件名称
typedef int (*BSL_SaveEntLibToFile) (wchar_t* strFileName);

//移动振镜至某一点
typedef int (*BSL_GoToPos)(wchar_t* szDevId, double x, double y);


//得到指定对象的最大最小坐标
typedef int (*BSL_GetEntSizeByIndex) (wchar_t* strFileName,
	int iIndex,
	double& dMinx,
	double& dMiny,
	double& dMaxx,
	double& dMaxy,
	double& dZ);

//得到指定对象的最大最小坐标
typedef int (*BSL_GetEntSizeByName) (wchar_t* strFileName,
	wchar_t* strEntName,//对象名称
	double& dMinx,
	double& dMiny,
	double& dMaxx,
	double& dMaxy,
    double& dZ);

// 复制选定图元
typedef int(*BSL_CopyEntByIndex) (wchar_t* strFileName, int iIndex, wchar_t* pNewEntName);

// 复制选定图元
typedef int(*BSL_CopyEntByName) (wchar_t* strFileName, wchar_t* strEntName, wchar_t* pNewEntName);

//移动指定对象相对坐标
//iIndex 对象索引号
typedef int (*BSL_MoveEntityRelByIndex) (wchar_t* strFileName, int iIndex, double dMovex, double dMovey);

//移动指定对象相对坐标
//strEntName 对象名称
typedef int (*BSL_MoveEntityRelByName) (wchar_t* strFileName, wchar_t* strEntName, double dMovex, double dMovey);

//移动指定对象绝对坐标
//iIndex 对象索引号
typedef int(*BSL_MoveEntityAbsByIndex) (wchar_t* strFileName, int iIndex, double dPtx, double dPty);

//移动指定对象绝对坐标
//strEntName 对象名称
typedef int(*BSL_MoveEntityAbsByName) (wchar_t* strFileName, wchar_t* strEntName, double dPtx, double dPty);

//缩放指定对象，缩放中心坐标(dCenx，dCeny)  dScaleX=X方向缩放比例  dScaleY=Y方向缩放比例
typedef int(*BSL_ScaleEntityByIndex) (wchar_t* strFileName,
	int iIndex,//对象索引号
	double dCenx,
	double dCeny,
	double dScaleX,
	double dScaleY);

//缩放指定对象，缩放中心坐标(dCenx，dCeny)  dScaleX=X方向缩放比例  dScaleY=Y方向缩放比例
typedef int (*BSL_ScaleEntityByName) (wchar_t* strFileName,
	wchar_t* strEntName,//对象名称
	double dCenx,
	double dCeny,
	double dScaleX,
	double dScaleY);

//镜像指定对象，镜像中心坐标(dCenx，dCeny)  bMirrorX=TRUE X方向镜像  bMirrorY=TRUE Y方向镜像
typedef int (*BSL_MirrorEntityByIndex) (wchar_t* strFileName,
	wchar_t* pEntName,//对象索引号
	double dCenx,
	double dCeny,
	bool   bMirrorX,
	bool   bMirrorY);

//镜像指定对象，镜像中心坐标(dCenx，dCeny)  bMirrorX=TRUE X方向镜像  bMirrorY=TRUE Y方向镜像
typedef int(*BSL_MirrorEntityByName) (wchar_t* strFileName,
	wchar_t* strEntName,//对象名称
	double dCenx,
	double dCeny,
	bool   bMirrorX,
	bool   bMirrorY);

//旋转指定对象  
//iIndex对象索引号
//(dCenx，dCeny) 旋转中心坐标
//dAngle=旋转角度(逆时针为正，单位为度)
typedef int (*BSL_RotateEntityByIndex) (wchar_t* strFileName, int iIndex, double dCenx, double dCeny, double dAngle);

//旋转指定对象  
//pEntName 对象名称
//(dCenx，dCeny) 旋转中心坐标
//dAngle = 旋转角度(逆时针为正，单位为度)
typedef int(*BSL_RotateEntityByName) (wchar_t* strFileName, wchar_t* strEntName, double dCenx, double dCeny, double dAngle);

//旋转指定对象  
//iIndex对象索引号
//(dCenx，dCeny) 旋转中心坐标
//dAngle=旋转角度(逆时针为正，单位为度)
typedef int(*BSL_SlopeEntityByIndex) (wchar_t* strFileName, int iIndex, double dCenx, double dCeny, double dx, double dy);

//旋转指定对象  
//pEntName 对象名称
//(dCenx，dCeny) 旋转中心坐标
//dAngle = 旋转角度(逆时针为正，单位为度)
typedef int(*BSL_SlopeEntityByName) (wchar_t* strFileName, wchar_t* strEntName, double dCenx, double dCeny, double dx, double dy);

//使用一个设备显示红光
//szDevId-设备ID
//bCountinue - 是否连续显示红光
typedef int (*BSL_RedLightMark) (wchar_t* szDevId, int bCountinue);

//使用一个设备显示红光
//szDevId-设备ID
//bCountinue - 是否连续显示红光
//strFileName - 文件名称
//vShpIndex - 待红光图形序号
typedef int (*BSL_RedLightMarkByEnt) (wchar_t* szDevId, wchar_t* strFileName,vector<int>&vShpIndex,int bCountinue);

//使用一个设备显示红光
//szDevId-设备ID
//bCountinue - 是否连续显示红光
//strFileName - 文件名称
//vShpIndex - 指向保存图元序号的指针
//iShpCount - 待红光的图元数量
typedef int (*BSL_RedLightMarkByEnt2) (wchar_t* szDevId, wchar_t* strFileName, int*vShpIndex,int iShpCount,int bCountinue);

//在一点持续出光一段时间
//keep-出光时间， ms
//pen - 使用的笔号
typedef int (*BSL_LarseOnPoint)(wchar_t* szDevId,double x, double y, double keep, int pen);//

typedef int (*BSL_MarkLine) (wchar_t* szDevId, double x1, double y1, double x2, double y2, int pen);//

typedef int (*BSL_MarkPoint) (wchar_t* szDevId, double x, double y, double delay, int pen);//

//标刻一组点
typedef int (*BSL_MarkPoints)(wchar_t* szDevId, vector<POINTF>& vPoints,int nPenNum);//

//得到对象总数
//输出参数:  对象总数
typedef int (*BSL_GetEntityCount) (wchar_t * strFileName);

//得到指定序号的对象名称
//输入参数: nEntityIndex 指定对象的序号(围: 0 － (lmc1_GetEntityCount()-1))
//输出参数: szEntName 对象的名称
typedef int (*BSL_GetEntityNameByIndex) (wchar_t * strFileName, int nEntityIndex, wchar_t szEntName[BSL_BUFFER_SIZE]);

//设置指定序号的实体名
//输入参数: nEntityIndex 指定对象的序号(围: 0 － (lmc1_GetEntityCount()-1))
//输出参数: szEntName 对象的名称
typedef int(*BSL_SetEntityNameByIndex) (wchar_t * strFileName, int nEntityIndex, wchar_t* strEntName);

//设置指定序号的实体名
//输入参数: nEntityIndex 指定对象的序号(围: 0 － (lmc1_GetEntityCount()-1))
//输出参数: szEntName 对象的名称
typedef int(*BSL_ChangeEntName) (wchar_t * strFileName, wchar_t szOldEntName[BSL_BUFFER_SIZE], wchar_t szNewEntName[BSL_BUFFER_SIZE]);

// 移动图元位置
typedef int(*BSL_MoveEntityOrderByIndex) (wchar_t * strFileName, int iIndex, int iOrderOffset);

// 反向图元位置
typedef int(*BSL_ReverseAllEntOrder) (wchar_t * strFileName);

//通过实体名获取笔号
typedef int(*BSL_GetPenNoByEntName) (wchar_t * strFileName, wchar_t strEntName[BSL_BUFFER_SIZE]);

typedef int (*BSL_GetCurCoor) (double& x, double& y);//

//typedef int (*BSL_GotoPos) (double x,double y);

//得到指定对象的文本
typedef int (*BSL_GetTextByName) (wchar_t * strFileName, wchar_t* strTextName, wchar_t strText[BSL_BUFFER_SIZE]);

//得到指定对象文本类型名称
typedef int (*BSL_GetFontTypeNameByName) (wchar_t * strFileName, wchar_t* strTextName, int& nFontType, wchar_t strText[BSL_BUFFER_SIZE]);

//得到指定对象上次打标的文本
typedef int (*BSL_GetLastMarkTextByName) (wchar_t * strFileName, wchar_t* strTextName, wchar_t strText[BSL_BUFFER_SIZE]);

//屏蔽一块区域不标刻
typedef int(*BSL_MaskArea)(wchar_t* strFileName, POINTF* vPoints, int iPtCount);

 //标刻线段
typedef int(*BSL_MarkLines) (wchar_t* szDevId, vector<vector<POINTF>> &lines, int pneNo);

  //标刻线段 兼容c#
typedef int(*BSL_MarkLines2) (wchar_t* szDevId, POINTF vPoints[], int iLineCount, int iPtCount[], int penNum);

//分块标刻图形文件中的图形对象
//标刻的范围按所有图形的最大外接矩形大小，标刻时会自动将分块中心与振镜中心对齐
//输入参数: szDevId 设备ID
//          szDocName 要加工的文件名称
//			dx-分块的宽度
//			dy-分块的高度
typedef int (*BSL_MarkBlockByDoc) (wchar_t* szDevId, wchar_t* szDocName, double dx, double dy);

/*
 * 根据传入的分块中心位置找到对应的块
 * szDocName: 文件名
 * type ：分块类型 0为根据长宽分块
 * x：x反向分块长或者X方向分块数
 * y：y方向分块宽或者Y方向分块数
 * centralPoint：分块中心点位置BSL_FindBlockMark
*/
typedef int (*BSL_FindBlockMark) (wchar_t *szDocName,int type,double x,double y,POINTF centralPoint);

struct BlockPosPathCShape
{
	double x;                     //左上角X坐标
	double y;			          //左上角Y坐标
	double width;		          //分块宽度
	double height;		          //分块高度
}; 


 
#define MAX_SHAPE_FILL_COUNT				4	// 4个填充方式，这个值不应该小于3 added by yjw 2015.05.15

//填充类型
enum BSL_FILLTYPE{
	BSL_FT_CIRCULAR = 0,		/* 环形填充 */
	BSL_FT_SINGLE_LINE,			/* 弓形, 在单个连通区是不断开 */
	BSL_FT_SINGLE_LINE_BREAK,	/* 弓形，跨越两个不相连的图块时，中间会断开*/
	BSL_FT_MULTI_LINE,			/* 多线，单向填充，各线段在两端不相连*/
	BSL_FT_MULTI_LINE_TWO_DIR	/* 多线，双向填充，各线段在两端不相连，可减少空跳时间*/
};

enum BSL_FONTTYPE
{
	FT_TRUETYPE = 0,
	FT_SINGLELINE,
	FT_CODEBAR,
	FT_PTMATRIC//,      //点阵字体 
};


struct BSL_ShapeFillPara
{
	BSL_FILLTYPE m_nFillType;	//填充类型, 
	int m_nExecuteType;		//多个图形的运算方式，0=异或 1=交  2=并 3=差，
	int m_nIndex;			//第几个填充
	BOOL m_bEnable;			//使能当前填充
	BOOL m_bRoundInvert;

	double m_fLineSpacing;	//线间距
	double m_fMargin;		// 边距

	BOOL m_fill_rotate;		//自动旋转角度标刻
	double m_fRotateAngle;	//旋转角度

	double  m_fstrFillGraduallyMaxs;	//渐变区域填充线最大间距
	float   m_fstrFillGraduallyRange;		//渐变区域设置填充宽度
	double  m_fstrFillGraduallyRate; //渐变区域变化幅度
	float   m_fstrFillGraduallyActualRange; //渐变区域实际宽度
	BOOL    m_bEnableFillGradually;		//使能渐变填充

	// 以下属性对环形填充无效的
	BOOL m_bWholeConsider;  /* 整体计算，当环形填充时无效*/
	BOOL m_bAlongBorder; /* 绕边走一次，当环形填充时无效*/
	BOOL m_bCrossFill; //交叉填充, by tgf 20180410
	BOOL m_bQuickFill; //快速填充(用于单线单向与单线双向), by tgf 20180702
	double m_fAngle;  // 填充线旋转的角度(弧度值)，对环形无效
	UINT m_nFillMarkCount;// 填充线标刻次数
	int m_nPenNum;      //笔号
	COLORREF m_cPenColor; //颜色
	UINT m_nCircularCount; // 边界环数，是除绕边走一圈以外的的环,对环形填充无效
	double m_fCircularGap;  // 环间距，
	double m_fInnerSpacing;   //直线缩进，是环与绕边走一圈里面的
	// 注意：环与绕边走一圈的区别：绕边走一圈与填充线条是没有间距的。	

	BOOL   m_bArrangeEqually;	//平均分布各条，如果为false,则以下属性有效
	double m_fStartPreserve;	// 开始保留
	double m_fEndPreserve;		//结束保留

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
	/*使能轮廓和/或绕边走一次：
	 * 0:无轮廓，无绕边走一次；1:有轮廓无绕边；2：无轮廓，有绕边；3:有轮廓有绕边
	 * 当有轮廓且优先轮廓时，轮廓在填充线前，若不优先轮廓，则轮廓在填充线后；
	 * 绕边一次的标刻，总是在填充之后。
	 */
	int m_bOutLine;		
	BOOL m_bOutLineFirst;	//是否先标刻轮廓
	BOOL m_bKeepSeperate;   //保持填充对象的独立
	BOOL m_bDelUngroup;		//删除填充时是否解散群组
	BSL_ShapeFillPara m_arrPar[MAX_SHAPE_FILL_COUNT];   //多组参数
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


//const int HATCHATTRIB_ALLCALC = 0x01;//全部对象作为整体一起计算
//const int HATCHATTRIB_BIDIR   = 0x08;//双向填充
//const int HATCHATTRIB_EDGE    = 0x02;//走一次边
//const int HATCHATTRIB_LOOP    = 0x10;//环形填充

////设置当前的填充参数，如果要向数据库里添加新对象时使能填充时，会使用此参数填充
//typedef int (*BSL_SetFillParam)(bool bEnableContour,//使能轮廓本身
//					  int    bEnableHatch1,//使能填充1
//					  int    nPenNo1,//填充笔	
//					  int    nHatchAttrib1,//填充属性
//					  double dHatchEdgeDist1,//填充线边距
//					  double dHatchLineDist1,//填充线间距
//					  double dHatchStartOffset1,//填充线起始偏移距离
//					  double dHatchEndOffset1,//填充线结束偏移距离
//					  double dHatchAngle1,//填充线角度	(弧度值)
//					  int    bEnableHatch2,//使能填充1
//					  int    nPenNo2,//填充笔	
//					  int    nHatchAttrib2,//填充属性
//					  double dHatchEdgeDist2,//填充线边距
//					  double dHatchLineDist2,//填充线间距
//					  double dHatchStartOffset2,//填充线起始偏移距离
//					  double dHatchEndOffset2,//填充线结束偏移距离
//					  double dHatchAngle2);//填充线角度	(弧度值)	

//设置当前的填充参数，如果要向文件里添加新对象时使能填充时，会使用此参数填充
typedef int (*BSL_SetFillParam)(const BSL_FillPara& fillPar);

//获取图元的填充参数
typedef int (*BSL_GetEntFillParam) (wchar_t* szFileName, wchar_t* pHatchName, BSL_FillPara& fillPar);



 /*根据轮廓线获取填充数据
 * outline - [输入]轮廓线（可由多条路径构成）线段接点坐标
 * outlinepnts - [输入]每条轮廓路径的接点数
 * outlinecount - [输入]轮廓路径数量
 * fillPar - [输入]填充参数
 * fillLines - [输出]填充线（可由多条路径构成）线段端点坐标
 * filllinepnts - [输出]每条填充路径的接点数
 * filllinecount - [输出]填充路径数量
*/
 typedef int(*BSL_GetFillData) (const POINTF outline[], const int outlinepnts[], const int outlinecount, const BSL_FillPara fillPar, POINTF fillLines[], int& filllinecount, int filllinepnts[]);

 //填充对象
 typedef int (*BSL_FillEntity) (wchar_t * strFileName, wchar_t* strEntName, wchar_t* pEntNameNew);
 //删除填充
 typedef int (*BSL_UnFillEnt) (wchar_t * strFileName, wchar_t* strEntName, bool bUnGroup);

  //填充单个对象
 typedef int (*BSL_FillSingleEntity) (wchar_t * strFileName, int nShapeIndex, wchar_t* pEntNameNew);
 //删除单个填充
 typedef int (*BSL_UnFillSingleEnt) (wchar_t * strFileName, int nShapeIndex, bool bUnGroup);

 //群组两个实体 将szEntName1和szEntName2 群组后命名为szEntName3，默认用笔号1
 typedef int (*BSL_GroupEnt) (wchar_t * strFileName, wchar_t szEntName1[BSL_BUFFER_SIZE],wchar_t  szEntName2[BSL_BUFFER_SIZE],wchar_t  szEntName3[BSL_BUFFER_SIZE],int nPenNo);
 //解散群体
 typedef int (*BSL_UnGroupEnt) (wchar_t * strFileName, wchar_t szEntName[BSL_BUFFER_SIZE]);

 //typedef int (*BSL_SetFillParam3) (bool bEnableContour,//使能轮廓本身
 //	int    nParamIndex,//填充参数序号值为1,2,3
 //	int    bEnableHatch,//使能填充
 //	int    nPenNo,//填充笔	
 //	int    nHatchType,//填充类型 0单向 1双向 2回形 3弓形 4弓形不反向
 //	bool   bHatchAllCalc,//是否全部对象作为整体一起计算
 //	bool   bHatchEdge,//绕边一次
 //	bool   bHatchAverageLine,//自动平均分布线
 //	double dHatchAngle,//填充线角度	
 //	double dHatchLineDist,//填充线间距
 //	double dHatchEdgeDist,//填充线边距					  
 //	double dHatchStartOffset,//填充线起始偏移距离
 //	double dHatchEndOffset,//填充线结束偏移距离
 //	double dHatchLineReduction,//直线缩进
 //	double dHatchLoopDist,//环间距
 //	int    nEdgeLoop,//环数
 //	bool   bHatchLoopRev,//环形反转
 //	bool   bHatchAutoRotate,//是否自动旋转角度
 //	double dHatchRotateAngle,//自动旋转角度
 //	bool bHatchCross);//交叉填充	


  //图元骨架信息,by tgf 20190129
struct EntityInfo
{
	wstring wszDocname;//文档名称，图元所属文档
	int iIndex;	//在内存库中位置索引
	int iType;		//图元类型
	wstring wszName;//图元名称
	//图元外接矩形的图纸坐标
	double x;		//图元左顶点x坐标（mm）
	double y;		//图元左顶点y坐标（mm）
	double width;	//图元宽度（mm）
	double height;	//图元高度（mm）

	EntityInfo()
	{
		iIndex = -1;
		iType = -1;
		wszName = L"";
		x = 0;
		y = 0;
		width = -1;	//负数表示非有效图元
		height = -1;//负数表示非有效图元
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

 //图元骨架信息,by tgf 20190129
struct EntityInfoCSharp
{
	char wszDocname[256];//文档名称，图元所属文档
	int iIndex;	//在内存库中位置索引
	int iType;		//图元类型
	char wszName[256];//图元名称
	//图元外接矩形的图纸坐标
	double x;		//图元左顶点x坐标（mm）
	double y;		//图元左顶点y坐标（mm）
	double width;	//图元宽度（mm）
	double height;	//图元高度（mm）

	EntityInfoCSharp()
	{
		strcpy_s(wszDocname, "");
		iIndex = -1;
		iType = -1;
		strcpy_s(wszName, "");
		x = 0;
		y = 0;
		width = -1;	//负数表示非有效图元
		height = -1;//负数表示非有效图元
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

//区域分组图元信息,by tgf 20190129
//分组不能跨越文档
struct AreaEntityGroup
{
	//区域范围
	double x;		//图元左顶点x坐标（mm）
	double y;		//图元左顶点y坐标（mm）
	double width;	//图元宽度（mm）
	double height;	//图元高度（mm）

	int nCount;		//分组内图元数量
	vector<EntityInfo> vEntity;//分组内图元

	AreaEntityGroup()
	{
		x = 0;
		y = 0;
		width = -1;	//负数表示非有效图元
		height = -1;//负数表示非有效图元
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

//获取缓存中的全部图元骨架信息
//输出参数: vEntities 图元骨架信息容器
typedef int(*BSL_GetAllEntities)(wchar_t* szDocName, vector<EntityInfo>& vEntities);

//获取缓存中的外接矩形小于给定尺寸的图形，并且按区域全部图元骨架信息
//输入参数：width - 宽度 mm
//			height - 高度 mm
//输出参数: vEntities 图元骨架信息容器
typedef int(*BSL_GetEntitiesBySize)(wchar_t* szDocName, double width, double height, vector<AreaEntityGroup>& vGroup);

//标刻一个分组内的图元
//by tgf 20190129
//输入参数：szDevId 设备ID
//          group 图元骨架信息容器
typedef int(*BSL_MarkEntitiesInGroup)(wchar_t* szDevId, AreaEntityGroup& group);


/*
 * 获取图元的标刻路径， added by tgf 20190813
 * bDoFill - 是否计算填充数据
 * sFileName - 文件名称
 * sEntName - 图元名称
 * outPaths - 图元外框路径
 * outPen - 外框路径绘制笔号
 * fillPaths - 图元填充路径
 * fillPen - 填充路径绘制笔号
 */
typedef int(*BSL_GetShapeMarkPaths)(bool bDoFill, wchar_t* sFileName, wchar_t* sShapeName, vector<vector<POINTF>>& outPaths, int& outPen, vector<vector<POINTF>>& fillPaths, int& fillPen);


//区域分组图元信息 for C#
//分组不能跨越文档
struct AreaEntityGroupCSharp
{
	//区域范围
	double x;		//图元左顶点x坐标（mm）
	double y;		//图元左顶点y坐标（mm）
	double width;	//图元宽度（mm）
	double height;	//图元高度（mm）

	int nCount;		//分组内图元数量
	EntityInfo pEntity[100];//分组内图元

	AreaEntityGroupCSharp()
	{
		x = 0;
		y = 0;
		width = -1;	//负数表示非有效图元
		height = -1;//负数表示非有效图元
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

//获取缓存中的全部图元骨架信息 for C#
//输出参数: vEntities 图元骨架信息容器
typedef int(*BSL_GetAllEntities2)(wchar_t* szDocName, int& nCount, EntityInfoCSharp pEntities[]);

//获取缓存中的外接矩形小于给定尺寸的图形，并且按区域全部图元骨架信息   for C#
//输入参数：width - 宽度 mm
//			height - 高度 mm
//输出参数: vEntities 图元骨架信息容器
//typedef int(*BSL_GetEntitiesBySize2)(wchar_t* szDocName, double width, double height, int& nCount, AreaEntityGroupCSharp pGroup[]);

//标刻一个分组内的图元   for C#
//by tgf 20190129
//输入参数：szDevId 设备ID
//          group 图元骨架信息容器
//typedef int(*BSL_MarkEntitiesInGroup2)(wchar_t* szDevId, AreaEntityGroupCSharp groupC);


//导出G-CODE
typedef int(*BSL_ExportGCode)(wchar_t* strFileName, vector<wstring>& vecGCode);
//导出G-CODE by name
typedef int(*BSL_ExportGCodeByName)(wchar_t* strFileName, wchar_t* strEntName, vector<wstring>& vecGCode);
//导出G-CODE by index
typedef int(*BSL_ExportGCodeByIndex)(wchar_t* strFileName, int iIndex, vector<wstring>& vecGCode);

//C++ API不需要c#接口
////获取所有的GCODE 供c#调用
//struct STU_GCODE
//{
//	char wszGCode[256];
//};
////导出G-CODE for C#
//typedef int(*BSL_ExportGCode2)(wchar_t* strFileName, STU_GCODE wstrGCode[], int& nCount);
////导出G-CODE by name for C#
//typedef int(*BSL_ExportGCodeByName2)(wchar_t* strFileName, wchar_t* strEntName, STU_GCODE wstrGCode[], int& nCount);
////导出G-CODE by index for C#
//typedef int(*BSL_ExportGCodeByIndex2)(wchar_t* strFileName, int iIndex, STU_GCODE wstrGCode[], int& nCount);

//打标过程中设置旋转角度（度），偏移（mm），旋转中心（mm）
typedef void (*BSL_SetOffsetValues)(double r, double dx,double dy,double cx,double cy);

// //替换矢量文件
// szFileName 模板文件
// szFileNameVector 输入矢量文件
// strEntName 要替换为矢量图的名称
typedef int (*BSL_ReplaceVectorFile)(wchar_t* szFileName, wchar_t* szFileNameVector, wchar_t* szEntName);



//加载振镜校正文件
//输出参数: strCalFileName  校正文件路径
typedef int (*BSL_LoadNewCalFile)(vector<wchar_t*>& vCalFileName);

//标刻最大图形
//输入参数: szDevId			设备ID
//输入参数: strCalFileName  校正文件路径
typedef int (*BSL_MarkMaxShape)(wchar_t* szDevId, wchar_t* strCalFileName);

//标刻九点矩形
//输入参数: szDevId			设备ID
//输入参数: strCalFileName  校正文件路径
//输入参数: fValSize		有效检定区域 mm
//输入参数: fTagSize		校正标记尺寸 mm
typedef int (*BSL_MarkNinePointRect)(wchar_t* szDevId, wchar_t* strCalFileName, double fValSize, double fTagSize);

//多点校正标刻
//输入参数: szDevId			设备ID
//输入参数: strCalFileName  校正文件路径
//输入参数: fValSize		有效检定区域 mm
//输入参数: fTagSize		校正标记尺寸 mm
//输入参数: nIndex			校正点数列表当前索引    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
typedef int (*BSL_MarkMultiCalPoint)(wchar_t* szDevId, wchar_t* strCalFileName, double fValSize, double fTagSize, int nIndex);

//标刻验证图形
//输入参数: szDevId			设备ID
//输入参数: strCalFileName  校正文件路径
//输入参数: nIndex			校正点数列表当前索引    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
//输入参数: nGap			线框间隔 mm  min(nGap, 5.0)  一般取5   
typedef int (*BSL_MarkCheckShape)(wchar_t* szDevId, wchar_t* strCalFileName, int nIndex, double nGap);


//网格检定数据
typedef struct gridCalData{
	double xT;	//理论点X
	double yT;	//理论点Y
	double xA;	//实测点X
	double yA;	//实测点Y
	gridCalData & operator = (const gridCalData &src ){
		xT = src.xT;
		yT = src.yT;
		xA = src.xA;
		yA = src.yA;
		return *this;
	}
}GRIDCALDATA;

//导入测量值
//输入参数: nIndex			校正点数列表当前索引    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
//输出参数: vCalData		网格检定点实测数据
typedef int (*BSL_LoadMeasuredValueFile)(int nIndex, vector<GRIDCALDATA>& vCalData);

//保存校正文件
//输入参数: strCalFileName  校正文件路径
//输入参数: nIndex			校正点数列表当前索引    0: 3*3   1: 5*5   2: 9*9   3: 17*17   4: 33*33   5: 65*65    6: 25*25
//输入参数: vCalData		网格检定点理论和实测数据
typedef int (*BSL_SaveCalFile)(wchar_t* strCalFileName, int nIndex, vector<GRIDCALDATA> vCalData);


//加入新圆到数据库中
typedef int (*BSL_AddCircleToFile)(
	wchar_t* szFileName,//圆增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	wchar_t* pEntName,//圆对象名称
	double dPosX,//圆中心点的x坐标
	double dPosY,//圆中心点的y坐标
	double dPosZ,//圆对象的z坐标
	double dRadius,//圆半径
	double dRotateAngle,//绕中心点旋转的角度值(弧度值)
	int nPenNo,//对象使用的加工参数
	bool bFill //是否填充对象
	);

//加入新椭圆到数据库中
typedef int (*BSL_AddEllipseToFile)(
	wchar_t* szFileName,//椭圆增加到的目标文件名，增加后仍然需要手动保存才能保存到文件。
	wchar_t* pEntName,//椭圆对象名称
	double dPosX,//椭圆中心点的x坐标
	double dPosY,//椭圆中心点的y坐标
	double dPosZ,//椭圆对象的z坐标
	double dLongAxis,//椭圆长轴
	double dMinorAxis,//椭圆短轴
	double dRotateAngle,//绕中心点旋转的角度值(弧度值)
	int nPenNo,//对象使用的加工参数
	bool bFill //是否填充对象
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
//根据当前数据库中手工校正参数和实际测量数据计算产生推荐值
//输入参数: dx_T  X轴方向理论边长 mm
//输入参数: dy_T  Y轴方向理论边长 mm
//输入参数: da_A  角度a的实际测量角度(°)
//输入参数: dx1_A  实际测量的X1的长度 mm
//输入参数: dx2_A  实际测量的X2的长度 mm
//输入参数: dx3_A  实际测量的X3的长度 mm
//输入参数: dy1_A  实际测量的Y1的长度 mm
//输入参数: dy2_A  实际测量的Y2的长度 mm
//输入参数: dy3_A  实际测量的Y3的长度 mm
//输出参数: dScaleX  X轴方向的放缩比例
//输出参数: dScaleY  Y轴方向的放缩比例
//输出参数: dDistorX  X轴方向的桶形失真系数
//输出参数: dDistorY  Y轴方向的桶形失真系数
//输出参数: dHorverX  X轴方向的平行四边形失真系数
//输出参数: dHorverY  Y轴方向的平行四边形失真系数
//输出参数: dTrapedistorX  X轴方向的梯形失真系数
//输出参数: dTrapedistorY  Y轴方向的梯形失真系数
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

//修改当前数据库中的手工校正参数
//输入参数：szParName  将要设置的参数名称
//输入参数: dScaleX  X轴方向的放缩比例
//输入参数: dScaleY  Y轴方向的放缩比例
//输入参数: dDistorX  X轴方向的桶形失真系数
//输入参数: dDistorY  Y轴方向的桶形失真系数
//输入参数: dHorverX  X轴方向的平行四边形失真系数
//输入参数: dHorverY  Y轴方向的平行四边形失真系数
//输入参数: dTrapedistorX  X轴方向的梯形失真系数
//输入参数: dTrapedistorY  Y轴方向的梯形失真系数
//输入参数: bSaveToFile  是否保存到标准配置文件(BslCAD.cfg)
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

//设置设备关联的参数 旋转角度（度），偏移（mm），旋转中心（mm）
//输入参数： szDevId    设备ID
//输入参数： szFileName 模板文件
//输入参数： szParName  设置的参数名称
//输入参数： r   旋转角度
//输入参数： dx  X偏移
//输入参数： dy  Y偏移
//输入参数： cx  旋转中心X坐标
//输入参数： cy  旋转中心Y坐标
typedef void (*BSL_SetOffsetValuesOfDevice)(wchar_t* szDevId, wchar_t* szFileName, wchar_t* szParName, double r, double dx,double dy,double cx,double cy);


// 单个路径数据（对于填充的话是每种填充方式一个实例）
typedef struct tagPathData
{
	int nPenIdx;			// 笔号
	int nMarkCount;			// 标刻次数
	vector<vector<POINTF>> vLine;			// 路径
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

//笔号参数
typedef struct tagPenPar{
	int iSwitchOn;			//笔号是否打开
	CString strName;		//参数名称
	wstring wstrName;		//参数名称，仅用于序列化
	UINT nMachineCount;		//加工数目
	UINT nRunSpeed;			//加工速度
	UINT nLaserPower;		//激光功率
	int nEffectWaitTime;	//功率设置下发等待生效时间,us
	float fCurrent;			//电流
	float fLaserFreq;		//激光频率
	float fLaserZkb;		//占空比(光纤激光器下的Q脉宽)	
	int  nMopaPulse;		//Mopa脉宽
	int iOpenDelay;			//开关延时 us,[-(2^15-1), (2^15-1)]
	int iShutDelay;			//关光延时	
	int iEndDelay;			//结束延时
	int iCornerDelay;		//拐角延时
	int iStepDelay;			//步距延时
	float fStepLen;			//标刻步距

	bool bChangeOfCornerDelay;	//拐角延时是否可变
	int  nVoltADOutput;			//使能电压输出

	int iDAAdvance;         //DA提前输出
	float fOverlapLen;      //重叠长度,mm (闭合图形的首尾重叠)
	float fAccLen;          //缓升距离 
	float fDecLen;          //缓降距离
	float fDAPowerSt;       //DA起始功率
	float fDAPowerEnd;      //DA结束功率
	float fPWMZkbSt;        //PWM起始占空比
	float fPWMZkbEnd;       //PWM结束占空比


	COLORREF cPenColor;		//笔号颜色

	//高级参数，每个笔号都有自己的高级参数, by tgf 20180709
	UINT JUMPSPEED;				//跳转速度, mm/s
	UINT JUMPPOSITONDELAY;		//跳转位置延时,us
	UINT JUMPDISTANCEDELAY;		//跳转距离延时,us
	UINT ENDCOMP;					//末点补偿
	UINT ACCDISTANCE;				//加点距离
	float POINTTIME;				//打点时间 ms
	BOOL PULSEPOINTMODE;			//是否使用矢量打点模式
	UINT PULSEPERPOINT;			//每个点脉冲数
	BOOL WOBBLE;					//抖动
	float WOBBLEDIAMETER;			//抖动直径
	float WOBBLEDISTANCE;			//抖动间距
	BOOL ENDADDPOINT;				//末尾加点
	UINT ADDCOUNT;				//加点数目
	float  ADDPOINTDISTANCE;		//加点距离
	float ADDPOINTTIME;				//打点时间
	UINT ADDPOINTCYCLES;			//加点次数
	UINT   OPENLIGHTBEHIND;			//开光滞后,us, [-2^9, 2^9]，本来应该放在笔号参数中的，现在改为放在高级参数中

	UINT	JUMPMINDELAY;			//最小跳转延时
	UINT	JUMPMAXDELAY;			//最大跳转延时
	UINT	JUMPMAXDISTANCE;		//最大跳转距离

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
  * 获取文件中所有打标路径数据
  * szDevId：设备ID
  * szDocName: 文件名
  * bRotOffset: 是否做偏移旋转
  * r   旋转角度
  * dx  X偏移
  * dy  Y偏移
  * cx  旋转中心X坐标
  * cy  旋转中心Y坐标
  * vMarkPaths：输出标刻数据
  * penpar: 输出笔号参数
*/
typedef int (*BSL_GetMarkDataPaths)(wchar_t* szDevId, wchar_t * szDocName, bool bRotOffset, double r, double dx,double dy,double cx,double cy, vector<PATHDATA>& vMarkPaths, PENPAR & penpar);

/**
  * 标刻路径点
  * szDevId：设备ID
  * vMarkPaths：标刻数据
  * penpar：笔号参数
  * szParName  配置参数名称
*/
typedef int (*BSL_MarkDocDataPaths)(wchar_t* szDevId, vector<PATHDATA> vMarkPaths, PENPAR penpar, wchar_t* szParName);


///////////////for C#
/*
typedef struct PathDataShape{
	int nLineCount;		//行数   路径数
	POINTF pPoint[10000];	//如果需要的点数量大于此值，则返回失败,需要传入更大的值
	int nPtCount[1000];	//各行路径点数 如果需要的每行点数量大于此值，则返回失败,需要传入更大的值

}PATHDATASHAPE;
*/

//typedef struct LineDataShape{
struct LineDataShape {
		int nPtCount;		//行数   点数
	POINTF pPoint[500];	//如果需要的点数量大于此值，则返回失败,需要传入更大的值
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
		int nPenIdx;			// 笔号
	int nMarkCount;			// 标刻次数
	int nLineCount;		//行数   路径数
	LineDataShape pLine[500];	//如果需要的点数量大于此值，则返回失败,需要传入更大的值
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

//笔号参数
//typedef struct PenPar{
struct PenPar {
		int iSwitchOn;			//笔号是否打开
	char cName[256];		//参数名称
	char wcName[256];		//参数名称，仅用于序列化
	UINT nMachineCount;		//加工数目
	UINT nRunSpeed;			//加工速度
	UINT nLaserPower;		//激光功率
	int nEffectWaitTime;	//功率设置下发等待生效时间,us
	float fCurrent;			//电流
	float fLaserFreq;		//激光频率
	float fLaserZkb;		//占空比(光纤激光器下的Q脉宽)	
	int  nMopaPulse;		//Mopa脉宽
	int iOpenDelay;			//开关延时 us,[-(2^15-1), (2^15-1)]
	int iShutDelay;			//关光延时	
	int iEndDelay;			//结束延时
	int iCornerDelay;		//拐角延时
	int iStepDelay;			//步距延时
	float fStepLen;			//标刻步距

	bool bChangeOfCornerDelay;	//拐角延时是否可变
	int  nVoltADOutput;			//使能电压输出

	int iDAAdvance;         //DA提前输出
	float fOverlapLen;      //重叠长度,mm (闭合图形的首尾重叠)
	float fAccLen;          //缓升距离 
	float fDecLen;          //缓降距离
	float fDAPowerSt;       //DA起始功率
	float fDAPowerEnd;      //DA结束功率
	float fPWMZkbSt;        //PWM起始占空比
	float fPWMZkbEnd;       //PWM结束占空比

	COLORREF cPenColor;		//笔号颜色

	//高级参数，每个笔号都有自己的高级参数, by tgf 20180709
	UINT JUMPSPEED;				//跳转速度, mm/s
	UINT JUMPPOSITONDELAY;		//跳转位置延时,us
	UINT JUMPDISTANCEDELAY;		//跳转距离延时,us
	UINT ENDCOMP;					//末点补偿
	UINT ACCDISTANCE;				//加点距离
	float POINTTIME;				//打点时间 ms
	BOOL PULSEPOINTMODE;			//是否使用矢量打点模式
	UINT PULSEPERPOINT;			//每个点脉冲数
	BOOL WOBBLE;					//抖动
	float WOBBLEDIAMETER;			//抖动直径
	float WOBBLEDISTANCE;			//抖动间距
	BOOL ENDADDPOINT;				//末尾加点
	UINT ADDCOUNT;				//加点数目
	float  ADDPOINTDISTANCE;		//加点距离
	float ADDPOINTTIME;				//打点时间
	UINT ADDPOINTCYCLES;			//加点次数
	UINT   OPENLIGHTBEHIND;			//开光滞后,us, [-2^9, 2^9]，本来应该放在笔号参数中的，现在改为放在高级参数中

	UINT	JUMPMINDELAY;			//最小跳转延时
	UINT	JUMPMAXDELAY;			//最大跳转延时
	UINT	JUMPMAXDISTANCE;		//最大跳转距离

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
  * 获取文件中所有打标路径数据 for C#
  * szDevId：设备ID
  * szDocName: 文件名
  * bRotOffset: 是否做偏移旋转
  * r   旋转角度
  * dx  X偏移
  * dy  Y偏移
  * cx  旋转中心X坐标
  * cy  旋转中心Y坐标
  * nCount 输出数目
  * pMarkPaths：输出标刻数据
  * penpar   输出笔号参数
*/
typedef int (*BSL_GetMarkDataPaths2)(wchar_t* szDevId, wchar_t * szDocName, bool bRotOffset, double r, double dx, double dy, double cx, double cy, int& nCount, PathDataShape pMarkPaths[], PenPar & penpar);

/**
  * 标刻路径点 for C#
  * szDevId：设备ID
  * nCount 数目
  * pMarkPaths：标刻数据
  * penpar   笔号参数
  * szParName  配置参数名称
*/
typedef int (*BSL_MarkDocDataPaths2)(wchar_t* szDevId, int nCount, PathDataShape pMarkPaths[], PenPar penpar, wchar_t* szParName);
///////////////for C#

typedef int (*BSL_SetLasterLenAreaParam)(double workSize, double rotateAngel, double offsetX, double offsetY, wchar_t* szParName);

#endif
