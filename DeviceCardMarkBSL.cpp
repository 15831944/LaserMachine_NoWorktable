#include "stdafx.h"
#include "DeviceCardMarkBSL.h"
#include "CDlgDevCfgTabScanner.h"
#include <corecrt_math_defines.h>

CDeviceCardMarkBSL::CDeviceCardMarkBSL()
{
	m_bMarkOrRedIsRunning = FALSE;

	m_hMarkDll = NULL;
	m_strDevId = _T("");
	//m_strFileName = _T("./binMark/YuanluMark.orzx");
	//m_strCaliName = _T("./binMark/YuanLuCor.cor");
	m_strFileName = _T("");
	m_strCaliName = _T("");

	m_pThMarkCard = NULL;
	m_pThRedLgtCard = NULL;
	m_pThLaserOn = NULL;
	m_funcMarkByDeviceId = NULL;
	m_funcLaserOnPoint = NULL;
}
CDeviceCardMarkBSL::~CDeviceCardMarkBSL()
{
	////卸载图形文件
	//BSL_UnLoadDataFile func1 = (BSL_UnLoadDataFile)::GetProcAddress(m_hMarkDll, "UnloadDataFile");
	//if (NULL == func1)
	//{
	//	AfxMessageBox(_T("SDK中没有找到BSL_UnLoadDataFile"));
	//	return;
	//}
	//int iRes1 = func1((PTCHAR)(LPCTSTR)m_strFileName);
	//if (iRes1 != BSL_ERR_SUCCESS)
	//{
	//	AfxMessageBox(_T("BSL_UnLoadDataFile失败"));
	//	return;
	//}

	//关闭设备
	BSL_CloseDevice func = (BSL_CloseDevice)::GetProcAddress(m_hMarkDll, "CloseDevice");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_CloseDevice"));
		return;
	}
	int iRes = func((LPTSTR)(LPCTSTR)m_strDevId);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_CloseDevice失败"));
		return;
	}
}

BOOL CDeviceCardMarkBSL::InitialCardMark()
{
	// 将当前路径\dll路径添加到本进程的路径中
	TCHAR pAppPath[MAX_PATH];
	CString strBinPath, strBinMarkSDK, strBinCalib;
	if (!::GetModuleFileName(NULL, pAppPath, MAX_PATH))
		return FALSE;
	PathRemoveFileSpec(pAppPath);
	strBinPath = pAppPath;
	strBinPath += _T("\\binMark");
	strBinMarkSDK = strBinPath + _T("\\MarkSDK.dll");
	strBinCalib = strBinPath + _T("\\calib.dll");
	m_strFileName = strBinPath + _T("\\YuanluMark.orzx");
	m_strCaliName = strBinPath + _T("\\YuanLuCor.cor");


	//读DLL
	if (!m_hMarkDll)
	{
		m_hMarkDll = ::LoadLibraryEx(strBinMarkSDK, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		//m_hMarkDll = ::LoadLibrary(_T("./bin/MarkSDK.dll"));
		DWORD dd = ::GetLastError();
		TRACE(L"LoadLibrary MarkSDK error %d\n", dd);
	}

	if (!m_hCalDll)
	{
		m_hCalDll = ::LoadLibraryEx(strBinCalib, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		//m_hCalDll = ::LoadLibrary(_T("./binMark/Calib.dll"));
		DWORD dd = ::GetLastError();
		TRACE(L"LoadLibrary Calib error %d\n", dd);
	}

	//检查DLL
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}
	if (!m_hCalDll)
	{
		AfxMessageBox(_T("m_hCalDll.dll 加载失败"));
		return FALSE;
	}

	//注册拔插响应函数
	//RegisterDevice(); 

	//获取设备ID
	if (!GetFreshDevlist())
		return FALSE;

	//读取文件
	if (!InitialDataFile())
		return FALSE;

	//关联文件到设备
	if (!AppendFileToDevice())
		return FALSE;

	//设置校正文件
	if (!ApplyCaliFile(TRUE))
		return FALSE;

	//线程中所需函数赋值
	if (!InitialBSLFuncCalledInThread())
		return FALSE;


	//设置初始参数
	int m_nScannerXYFlip, m_nScannerInvertX, m_nScannerInvertY;
	m_nScannerXYFlip = ReadScannerXYFlip();
	m_nScannerInvertX = ReadScannerInvertX();
	m_nScannerInvertY = ReadScannerInvertY();
	if (!SetScannerXYFlipFlag(m_nScannerXYFlip, m_nScannerInvertX, m_nScannerInvertY))
		return FALSE;


	return TRUE;
}

BOOL CDeviceCardMarkBSL::StartMarkCardMark()
{
	if (!m_bMarkOrRedIsRunning)
	{
		//ApplyCaliFile(TRUE);
		StartMarkThread();
		m_bMarkOrRedIsRunning = TRUE;
	}

	return TRUE;
}

BOOL CDeviceCardMarkBSL::StopMarkCardMark()
{
	if (m_bMarkOrRedIsRunning)
	{
		StopMarkThread(m_pThMarkCard);
		m_bMarkOrRedIsRunning = FALSE;
	}

	return TRUE;
}

//监测标刻线程，直到线程完成或终止，此时函数才会返回
BOOL CDeviceCardMarkBSL::WaitForThreadsEnded()
{
	//退出标刻线程
	if (m_pThMarkCard)
	{
		BOOL bQuit = FALSE;
		DWORD dRet;
		MSG msg;
		int nCt = 0;
		while (!bQuit)
		{
			if (FALSE == m_bMarkOrRedIsRunning)
				break;

			dRet = MsgWaitForMultipleObjects(1, &m_pThMarkCard->m_hThread, FALSE, INFINITE, QS_ALLINPUT);		
			if (dRet == WAIT_OBJECT_0 + 1)
			{
				//收到消息
				TRACE("加工线程消息,函数返回值为%d \n", dRet);
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TRACE("PeekMessage_Count = %d \n", ++nCt);
					if (msg.message == WM_QUIT)
					{
						bQuit = TRUE;
						break;
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				////收到消息
				//TRACE("加工线程消息,函数返回值为%d \n", dRet);
				//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				//{
				//	TRACE("PeekMessage_Count = %d \n", ++nCt);
				//	TranslateMessage(&msg);
				//	DispatchMessage(&msg);
				//}
				//else
				//	Sleep(1);
			}
			else if (WAIT_OBJECT_0 == dRet)
			{
				//线程退出
				TRACE("加工线程已退出，函数返回值: %d \n", dRet);
				delete m_pThMarkCard;
				m_pThMarkCard = NULL;
				break;
			}
			else
			{
				//线程非正常退出
				TRACE("加工线程非正常退出，函数返回值: %d \n", dRet);
				delete m_pThMarkCard;
				m_pThMarkCard = NULL;
				break;
			}
		}
	}

	//退出红光线程
	if (m_pThRedLgtCard)
	{
		BOOL bQuit = FALSE;
		DWORD dRet;
		MSG msg;
		int nCt = 0;
		while (!bQuit)
		{
			if (FALSE == m_bMarkOrRedIsRunning)
				break;

			dRet = MsgWaitForMultipleObjects(1, &m_pThRedLgtCard->m_hThread, FALSE, INFINITE, QS_ALLINPUT);
			if (dRet == WAIT_OBJECT_0 + 1)
			{
				//收到消息
				TRACE("红光线程消息,函数返回值为%d \n", dRet);
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TRACE("PeekMessage_Count = %d \n", ++nCt);
					if (msg.message == WM_QUIT)
					{
						bQuit = TRUE;
						break;
					}
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else if (WAIT_OBJECT_0 == dRet)
			{
				//线程退出
				TRACE("红光线程退出,函数返回值为%d \n", dRet);
				delete m_pThRedLgtCard;
				m_pThRedLgtCard = NULL;
				break;
			}
			else
			{
				//线程非正常退出
				TRACE("红光线程非正常退出，函数返回值为%d \n", dRet);
				delete m_pThRedLgtCard;
				m_pThRedLgtCard = NULL;
				break;
			}
		}
	}

	//退出激光测试线程
	if (m_pThLaserOn)
	{
		BOOL bQuit = FALSE;
		DWORD dRet;
		MSG msg;
		int nCt = 0;
		while (!bQuit)
		{
			//if (FALSE == m_bMarkOrRedIsRunning)
			//	break;

			dRet = MsgWaitForMultipleObjects(1, &m_pThLaserOn->m_hThread, FALSE, INFINITE, QS_ALLINPUT);
			if (dRet == WAIT_OBJECT_0 + 1)
			{
				//收到消息
				TRACE("出光线程消息,函数返回值为%d \n", dRet);
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{ 
					TRACE("PeekMessage_Count = %d \n", ++nCt);
					if (msg.message == WM_QUIT)
					{
						bQuit = TRUE;
						break;
					} 
					if (!AfxPreTranslateMessage(&msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				 } 

				//TRACE("出光线程消息,函数返回值为%d \n", dRet);
				//if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				//{
				//	TRACE("PeekMessage_Count = %d \n", ++nCt);
				//	TranslateMessage(&msg);
				//	DispatchMessage(&msg);
				//}
				//else
				//{
				//	TRACE("else PeekMessage_Count = %d \n", ++nCt);
				//	Sleep(1);
				//}
			}
			else if (WAIT_OBJECT_0 == dRet)
			{
				//线程退出
				TRACE("出光线程已退出，函数返回值: %d \n", dRet);
				delete m_pThLaserOn;
				m_pThLaserOn = NULL;
				break;
			}
			else
			{
				//线程非正常退出
				TRACE("出光线程非正常退出，函数返回值: %d \n", dRet);
				delete m_pThLaserOn;
				m_pThLaserOn = NULL;
				break;
			}
		}
	}


	//AfxMessageBox(_T("标刻完成"));
	m_bMarkOrRedIsRunning = FALSE;
	return TRUE;
}

BOOL CDeviceCardMarkBSL::LaserOn()
{
	//清空数据库
	DeleteALLEntities();
	//写加工参数
	SetPenFromDefaultProcParm(LayerNum_Reserve1);
	//SetPenFromDefaultProcParm(0);
	//开始打点
	StartLaserOn();

	return TRUE;
}
BOOL CDeviceCardMarkBSL::LaserOff()
{
	//停止标刻函数
	BSL_StopMark func = (BSL_StopMark)::GetProcAddress(m_hMarkDll, "StopMark");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_StopMark"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strDevId);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_StopMark失败"));
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceCardMarkBSL::ShowDlgCali()
{
	if (m_hMarkDll)
	{
		BSL_ShowCaliDlg func = (BSL_ShowCaliDlg)::GetProcAddress(m_hMarkDll, "ShowCaliDlg");
		if (func)
		{
			func(1);
		}
	}

	return TRUE;
}
BOOL CDeviceCardMarkBSL::SetLenRegion(double fWorksize)
{
	if (m_hMarkDll)
	{
		BSL_SetLasterLenAreaParam func = (BSL_SetLasterLenAreaParam)::GetProcAddress(m_hMarkDll, "SetLasterLenAreaParam");
		if (func)
		{
			func(fWorksize, 0, 0, 0, _T("default"));
		}
	}

	return TRUE;

}

BOOL CDeviceCardMarkBSL::SetScannerXYFlipFlag(int nXYFlip, int nInvertX, int nInvertY)
{
	if (m_hMarkDll)
	{
		BSL_SetXYFlipFlag func = (BSL_SetXYFlipFlag)::GetProcAddress(m_hMarkDll, "SetXYFlipFlag");
		if (func)
		{
			func(nXYFlip, nInvertX, nInvertY, L"default");
		}
	}

	return TRUE;
}



BOOL CDeviceCardMarkBSL::SetPensFromAllLayers(CMachineListContainer* pObjList)
{
	//清空pen参数


	//设置pen参数
	penPara penParaTmp;
	int nLayerCount = pObjList->GetLayerCount();
	CMachinePara_Layer* pMachineParaLayerTmp;

	for (int i = 0; i < nLayerCount; i++)
	{
		pMachineParaLayerTmp = pObjList->GetLayerOfNumber(i);

		penParaTmp.nPenNo = i;														//要设置的笔号(0-255)
		if( 0 == pMachineParaLayerTmp->m_MachineMode)
			penParaTmp.nMarkLoop = pMachineParaLayerTmp->m_MachinePara.Times;		//切割模式//加工次数
		else
			penParaTmp.nMarkLoop = 1;												//遍历模式//加工次数
		penParaTmp.dMarkSpeed = pMachineParaLayerTmp->m_MachinePara.Speed;			//标刻速度mm/s
		penParaTmp.dPowerRatio = pMachineParaLayerTmp->m_MachinePara.Power;			//功率百分比(0-100%)	
		penParaTmp.nFreq = pMachineParaLayerTmp->m_MachinePara.Frequncy;			//频率HZ
		penParaTmp.nQPulseWidth = pMachineParaLayerTmp->m_MachinePara.PulseWidth;	//Q脉冲宽度us	

		penParaTmp.nStartTC = gLaserOnDelay;										//开始延时us
		penParaTmp.nLaserOffTC = gLaserOffDelay;									//激光关闭延时us 
		penParaTmp.nEndTC = gAfterMarkDelay;										//结束延时us
		penParaTmp.nPolyTC = gPolylineDelay;										//拐角延时us	
		penParaTmp.nJumpPosTC = gBeforMarkDelay;									//标刻后延时/跳转延时

		//将penPara写入卡中
		BSL_SetPenParam func = (BSL_SetPenParam)::GetProcAddress(m_hMarkDll, "SetPenParam");
		if (NULL == func)
		{
			AfxMessageBox(_T("SDK中没有找到BSL_SetPenParam"));
			return FALSE;
		}
		int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, penParaTmp.nPenNo, penParaTmp.nMarkLoop, penParaTmp.dMarkSpeed,
			penParaTmp.dPowerRatio, penParaTmp.dCurrent, penParaTmp.nFreq, penParaTmp.nQPulseWidth, 
			penParaTmp.nStartTC, penParaTmp.nLaserOffTC, penParaTmp.nEndTC, penParaTmp.nPolyTC,
			penParaTmp.dJumpSpeed, penParaTmp.nJumpPosTC, penParaTmp.nJumpDistTC, penParaTmp.dEndComp,
			penParaTmp.bPulsePointMode, penParaTmp.nPulseNum, penParaTmp.POINTTIME);
		if (iRes != BSL_ERR_SUCCESS)
		{
			AfxMessageBox(_T("BSL_SetPenParam失败"));
			return FALSE;
		}
		
	}
	return TRUE;
}

BOOL CDeviceCardMarkBSL::SetPenFromDefaultProcParm(UINT nPenNo)
{
	penPara penParaTmp;

	penParaTmp.nPenNo = nPenNo;						//要设置的笔号(0-255)
	if (0 == gProcessMode)			
		penParaTmp.nMarkLoop = gProcessTimes;		//切割模式//加工次数
	else
		penParaTmp.nMarkLoop = 1;					//遍历模式//加工次数
	penParaTmp.dMarkSpeed = gProcessSpeed;			//标刻速度mm/s
	penParaTmp.dPowerRatio = gProcessPower;			//功率百分比(0-100%)	
	penParaTmp.nFreq = gProcessFrequncy;			//频率HZ
	penParaTmp.nQPulseWidth = gProcessPulseWidth;	//Q脉冲宽度us	

	penParaTmp.nStartTC = gLaserOnDelay;			//开始延时us
	penParaTmp.nLaserOffTC = gLaserOffDelay;		//激光关闭延时us 
	penParaTmp.nEndTC = gAfterMarkDelay;			//结束延时us
	penParaTmp.nPolyTC = gPolylineDelay;			//拐角延时us	
	penParaTmp.nJumpPosTC = gBeforMarkDelay;		//标刻前延时

	//将penPara写入卡中
	BSL_SetPenParam func = (BSL_SetPenParam)::GetProcAddress(m_hMarkDll, "SetPenParam");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_SetPenParam"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, penParaTmp.nPenNo, penParaTmp.nMarkLoop, penParaTmp.dMarkSpeed,
		penParaTmp.dPowerRatio, penParaTmp.dCurrent, penParaTmp.nFreq, penParaTmp.nQPulseWidth,
		penParaTmp.nStartTC, penParaTmp.nLaserOffTC, penParaTmp.nEndTC, penParaTmp.nPolyTC,
		penParaTmp.dJumpSpeed, penParaTmp.nJumpPosTC, penParaTmp.nJumpDistTC, penParaTmp.dEndComp,
		penParaTmp.bPulsePointMode, penParaTmp.nPulseNum, penParaTmp.POINTTIME);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_SetPenParam失败"));
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardMarkBSL::DeleteALLEntities()
{
	//清空.orzx文件
	BSL_ClearEntityLib func = (BSL_ClearEntityLib)::GetProcAddress(m_hMarkDll, "ClearEntityLib");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_ClearEntityLib"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_ClearEntityLib失败"));
		return FALSE;
	}

	return TRUE;

}

BOOL CDeviceCardMarkBSL::SaveEntityToFile()
{
	BSL_SaveEntLibToFile func = (BSL_SaveEntLibToFile)::GetProcAddress(m_hMarkDll, "SaveEntLibToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_SaveEntLibToFile"));
		return FALSE;
	}
	wchar_t* szFileName = (PTCHAR)(LPCTSTR)m_strFileName;
	int iRes = func(szFileName);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_SaveEntLibToFile失败"));
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardMarkBSL::AddEntityLines(int nCount, double ptPos[][2], int nPenNo)
{
	//添加多段线
	BSL_AddLinesToFile func = (BSL_AddLinesToFile)::GetProcAddress(m_hMarkDll, "AddLinesToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_AddLinesToFile"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, ptPos, nCount, L"插入的线段", nPenNo);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AddLinesToFile失败"));
		return FALSE;
	}

	return TRUE;

}

BOOL CDeviceCardMarkBSL::AddEntityCircle(double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo)
{
	//解析圆上插补坐标
	int nCountPt;
	double(*ptBuf)[2];
	double fMarkArcStepAngle;

	fMarkArcStepAngle = m_fMarkArcStep / fRadius * 180 / M_PI;
	nCountPt =(int) ((2 * M_PI * fRadius) / m_fMarkArcStep) + 2;
	ptBuf = new double[nCountPt][2];

	
	if (0 == nDir)//顺时针
	{
		for (int i = 0; i < nCountPt-1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart -= fMarkArcStepAngle;
		}

		ptBuf[nCountPt-1][0] = ptBuf[0][0];
		ptBuf[nCountPt-1][1] = ptBuf[0][1];
	}
	else if (1 == nDir)//逆时针
	{
		for (int i = 0; i < nCountPt-1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart += fMarkArcStepAngle;
		}

		ptBuf[nCountPt-1][0] = ptBuf[0][0];
		ptBuf[nCountPt-1][1] = ptBuf[0][1];
	}
	else
	{
		return FALSE;
	}

	//将ptBuf写入文件
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}

	//添加多段线
	BSL_AddLinesToFile func = (BSL_AddLinesToFile)::GetProcAddress(m_hMarkDll, "AddLinesToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_AddLinesToFile"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, ptBuf, nCountPt, L"插入的圆", nPenNo);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AddLinesToFile失败"));
		return FALSE;
	}

	delete[] ptBuf;

	return TRUE;
}


BOOL CDeviceCardMarkBSL::AddEntityArc(double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo)
{
	//解析圆弧上插补坐标
	int nCountPt; 
	double(*ptBuf)[2];
	double fAngleDelt = fAngleEnd - fAngleStart;
	double fMarkArcStepAngle;
	fMarkArcStepAngle = m_fMarkArcStep / fRadius * 180 / M_PI;

	if (0 == nDir)//顺时针
	{
		if (0 <= fAngleDelt)//劣弧
			nCountPt = (int) (((M_PI * (360 - fAngleDelt) / 180) * fRadius) / m_fMarkArcStep) + 2;
		else//优弧
			nCountPt = (int) (((M_PI * abs(fAngleDelt) / 180) * fRadius) / m_fMarkArcStep) + 2;

		ptBuf = new double[nCountPt][2];

		for (int i = 0; i < nCountPt - 1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart -= fMarkArcStepAngle;
		}

		ptBuf[nCountPt-1][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleEnd / 180);
		ptBuf[nCountPt-1][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleEnd / 180);
	}
	else if (1 == nDir)//逆时针
	{
		if (0 <= fAngleDelt)//优弧
			nCountPt = (int) (((M_PI * fAngleDelt / 180) * fRadius) / m_fMarkArcStep) + 2;
		else//劣弧
			nCountPt = (int) (((M_PI * (360 - abs(fAngleDelt)) / 180) * fRadius) / m_fMarkArcStep) + 2;

		ptBuf = new double[nCountPt][2];

		for (int i = 0; i < nCountPt - 1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart += fMarkArcStepAngle;
		}

		ptBuf[nCountPt-1][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleEnd / 180);
		ptBuf[nCountPt-1][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleEnd / 180);
	}
	else
	{
		return FALSE;
	}

	//将ptBuf写入文件
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}

	//添加多段线
	BSL_AddLinesToFile func = (BSL_AddLinesToFile)::GetProcAddress(m_hMarkDll, "AddLinesToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_AddLinesToFile"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, ptBuf, nCountPt, L"插入的圆弧", nPenNo);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AddLinesToFile失败"));
		return FALSE;
	}

	delete[] ptBuf;

	return TRUE;
}



//BSLCard*********************************************************BSLCard//

BOOL CDeviceCardMarkBSL::ApplyCaliFile(BOOL bFlagCaliFile)
{
	//if (FALSE == bFlagCaliFile)
	//	return TRUE;

	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}

	BSL_SetCalFileFlag func1 = (BSL_SetCalFileFlag)::GetProcAddress(m_hMarkDll, "SetCalFileFlag");
	if (NULL == func1)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_SetCalFileFlag"));
		return FALSE;
	}
	func1(bFlagCaliFile, L"default");

	if (bFlagCaliFile)
	{
		BSL_SetCalFile func = (BSL_SetCalFile)::GetProcAddress(m_hMarkDll, "SetCalFile");
		if (NULL == func)
		{
			AfxMessageBox(_T("SDK中没有找到BSL_SetCalFile"));
			return FALSE;
		}
		func((PTCHAR)(LPCTSTR)m_strCaliName, L"default");
	}
	
	return TRUE;
}


//标刻线程控制
void CDeviceCardMarkBSL::StartMarkThread()
{
	// reset all event handles to initial states 

	// stop threads if still running ...
	if (m_pThMarkCard)
	{
		WaitForThreadsEnded();
		m_pThMarkCard = NULL;
	}

	m_pThMarkCard = AfxBeginThread(ThreadMarkCard, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, 0);
	m_pThMarkCard->m_bAutoDelete = FALSE;
	m_pThMarkCard->ResumeThread();

}
void CDeviceCardMarkBSL::StopMarkThread(CWinThread* pThred)
{
	if (NULL == pThred)
		return;

	//先用调用停止标刻函数，再强制停止进程
	//停止标刻函数
	BSL_StopMark func = (BSL_StopMark)::GetProcAddress(m_hMarkDll, "StopMark");
	if (NULL != func)
	{
		int iRes = func((PTCHAR)(LPCTSTR)m_strDevId);
		if (iRes != BSL_ERR_SUCCESS)
		{
			AfxMessageBox(_T("BSL_StopMark失败"));
		}
	}
	else
	{
		AfxMessageBox(_T("SDK中没有找到BSL_StopMark"));
	}

	//等待标刻线程停止
	WaitForThreadsEnded();


	//DWORD dwExit = 0;
	//MSG msg;
	//do
	//{
	//	Sleep(1);
	//	dwExit = 0;
	//	GetExitCodeThread(pThred->m_hThread, &dwExit);
	//	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	//	{
	//		::TranslateMessage(&msg);
	//		::DispatchMessage(&msg);
	//	}
	//} while (dwExit == STILL_ACTIVE);

	////删除线程指针
	//delete pThred;
	//pThred = NULL;
}

UINT CDeviceCardMarkBSL::ThreadMarkCard(LPVOID lpParam)
{
	CDeviceCardMarkBSL* pCardBSL = (CDeviceCardMarkBSL*)lpParam;
	CString strDevID = pCardBSL->m_strDevId;
	BSL_MarkByDeviceId func = pCardBSL->m_funcMarkByDeviceId;

	if (strDevID.IsEmpty())
	{
		return 1;
	}
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_MarkByDeviceId"));
		return 1;
	}
	int iRes = func((PTCHAR)(LPCTSTR)strDevID);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_MarkByDeviceId失败"));
		return 1;
	}

	//AfxMessageBox(_T("BSL_MarkByDeviceId完成"));
	return 0;
}


void CDeviceCardMarkBSL::StartLaserOn()
{
	if (m_pThLaserOn)
	{
		WaitForThreadsEnded();
		m_pThLaserOn = NULL;
	}

	m_pThLaserOn = AfxBeginThread(ThreadLaserOn, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, 0);
	m_pThLaserOn->m_bAutoDelete = FALSE;
	m_pThLaserOn->ResumeThread();
}

UINT CDeviceCardMarkBSL::ThreadLaserOn(LPVOID lpParam)
{
	CDeviceCardMarkBSL* pCardBSL = (CDeviceCardMarkBSL*)lpParam;
	CString strDevID = pCardBSL->m_strDevId;
	BSL_LarseOnPoint func = pCardBSL->m_funcLaserOnPoint;

	//开始打点
	if (strDevID.IsEmpty())
	{
		return 1;
	}
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_LarseOnPoint"));
		return 1;
	}
	int iRes = func((PTCHAR)(LPCTSTR)strDevID, 0, 0, 60000, LayerNum_Reserve1);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_LarseOnPoint失败"));
		return 1;
	}

	//AfxMessageBox(_T("出光结束"));
	return 0;
}


//获取所有的设备ID 
BOOL CDeviceCardMarkBSL::GetFreshDevlist()
{
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}

	BSL_GetAllDevices2 func = (BSL_GetAllDevices2)::GetProcAddress(m_hMarkDll, "GetAllDevices2");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_GetAllDevices2"));
		return FALSE;
	}

	STU_DEVID* pDevs = new STU_DEVID[10];  //最多支持8张卡
	int iCount = 0;
	int iRes = func(pDevs, &iCount);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_GetAllDevices2失败"));
		delete[] pDevs;
		return FALSE;
	}

	if (0 >= iCount)
	{
		AfxMessageBox(_T("BSL_GetAllDevices2未发现硬件"));
		delete[] pDevs;
		return FALSE;
	}

	m_strDevId = (CString)pDevs[0].szName;
	if (m_strDevId.IsEmpty())
	{
		AfxMessageBox(_T("m_strDevId为空"));
		delete[] pDevs;
		return FALSE;
	}

	delete [] pDevs;
	return TRUE;

}

//读.orzx文件
BOOL CDeviceCardMarkBSL::InitialDataFile()
{
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}
	//读取.orzx文件
	BSL_LoadDataFile func = (BSL_LoadDataFile)::GetProcAddress(m_hMarkDll, "LoadDataFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_LoadDataFile"));
		return FALSE;
	}
	int iRes = func((LPTSTR)(LPCTSTR)m_strFileName);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_LoadDataFile失败"));
		return FALSE;
	}

	//清空.orzx文件
	BSL_ClearEntityLib func1 = (BSL_ClearEntityLib)::GetProcAddress(m_hMarkDll, "ClearEntityLib");
	if (NULL == func1)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_ClearEntityLib"));
		return FALSE;
	}
	int iRes1 = func1((PTCHAR)(LPCTSTR)m_strFileName);
	if (iRes1 != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_ClearEntityLib失败"));
		return FALSE;
	}


	return TRUE;
}

BOOL CDeviceCardMarkBSL::AppendFileToDevice()
{
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll 加载失败"));
		return FALSE;
	}

	//关联文件到设备
	BSL_AppendFileToDevice func = (BSL_AppendFileToDevice)::GetProcAddress(m_hMarkDll, "AppendFileToDevice");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_AppendFileToDevice"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, (PTCHAR)(LPCTSTR)m_strDevId);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AppendFileToDevice失败"));
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardMarkBSL::InitialBSLFuncCalledInThread()
{
	m_funcMarkByDeviceId = (BSL_MarkByDeviceId)::GetProcAddress(m_hMarkDll, "MarkByDeviceId");
	if (NULL == m_funcMarkByDeviceId)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_MarkByDeviceId"));
		return FALSE;
	}
	//m_funcMarkPoint = (BSL_MarkPoint)::GetProcAddress(m_hMarkDll, "MarkPoint");
	//if (NULL == m_funcMarkPoint)
	//{
	//	AfxMessageBox(_T("SDK中没有找到BSL_MarkPoint"));
	//	return FALSE;
	//}
	m_funcLaserOnPoint = (BSL_LarseOnPoint)::GetProcAddress(m_hMarkDll, "LarseOnPoint");
	if (NULL == m_funcLaserOnPoint)
	{
		AfxMessageBox(_T("SDK中没有找到BSL_LarseOnPoint"));
		return FALSE;
	}

	

	return TRUE;

}

