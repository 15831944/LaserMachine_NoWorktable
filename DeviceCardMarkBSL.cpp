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
	////ж��ͼ���ļ�
	//BSL_UnLoadDataFile func1 = (BSL_UnLoadDataFile)::GetProcAddress(m_hMarkDll, "UnloadDataFile");
	//if (NULL == func1)
	//{
	//	AfxMessageBox(_T("SDK��û���ҵ�BSL_UnLoadDataFile"));
	//	return;
	//}
	//int iRes1 = func1((PTCHAR)(LPCTSTR)m_strFileName);
	//if (iRes1 != BSL_ERR_SUCCESS)
	//{
	//	AfxMessageBox(_T("BSL_UnLoadDataFileʧ��"));
	//	return;
	//}

	//�ر��豸
	BSL_CloseDevice func = (BSL_CloseDevice)::GetProcAddress(m_hMarkDll, "CloseDevice");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_CloseDevice"));
		return;
	}
	int iRes = func((LPTSTR)(LPCTSTR)m_strDevId);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_CloseDeviceʧ��"));
		return;
	}
}

BOOL CDeviceCardMarkBSL::InitialCardMark()
{
	// ����ǰ·��\dll·����ӵ������̵�·����
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


	//��DLL
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

	//���DLL
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}
	if (!m_hCalDll)
	{
		AfxMessageBox(_T("m_hCalDll.dll ����ʧ��"));
		return FALSE;
	}

	//ע��β���Ӧ����
	//RegisterDevice(); 

	//��ȡ�豸ID
	if (!GetFreshDevlist())
		return FALSE;

	//��ȡ�ļ�
	if (!InitialDataFile())
		return FALSE;

	//�����ļ����豸
	if (!AppendFileToDevice())
		return FALSE;

	//����У���ļ�
	if (!ApplyCaliFile(TRUE))
		return FALSE;

	//�߳������躯����ֵ
	if (!InitialBSLFuncCalledInThread())
		return FALSE;


	//���ó�ʼ����
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

//������̣߳�ֱ���߳���ɻ���ֹ����ʱ�����Ż᷵��
BOOL CDeviceCardMarkBSL::WaitForThreadsEnded()
{
	//�˳�����߳�
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
				//�յ���Ϣ
				TRACE("�ӹ��߳���Ϣ,��������ֵΪ%d \n", dRet);
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
				////�յ���Ϣ
				//TRACE("�ӹ��߳���Ϣ,��������ֵΪ%d \n", dRet);
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
				//�߳��˳�
				TRACE("�ӹ��߳����˳�����������ֵ: %d \n", dRet);
				delete m_pThMarkCard;
				m_pThMarkCard = NULL;
				break;
			}
			else
			{
				//�̷߳������˳�
				TRACE("�ӹ��̷߳������˳�����������ֵ: %d \n", dRet);
				delete m_pThMarkCard;
				m_pThMarkCard = NULL;
				break;
			}
		}
	}

	//�˳�����߳�
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
				//�յ���Ϣ
				TRACE("����߳���Ϣ,��������ֵΪ%d \n", dRet);
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
				//�߳��˳�
				TRACE("����߳��˳�,��������ֵΪ%d \n", dRet);
				delete m_pThRedLgtCard;
				m_pThRedLgtCard = NULL;
				break;
			}
			else
			{
				//�̷߳������˳�
				TRACE("����̷߳������˳�����������ֵΪ%d \n", dRet);
				delete m_pThRedLgtCard;
				m_pThRedLgtCard = NULL;
				break;
			}
		}
	}

	//�˳���������߳�
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
				//�յ���Ϣ
				TRACE("�����߳���Ϣ,��������ֵΪ%d \n", dRet);
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

				//TRACE("�����߳���Ϣ,��������ֵΪ%d \n", dRet);
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
				//�߳��˳�
				TRACE("�����߳����˳�����������ֵ: %d \n", dRet);
				delete m_pThLaserOn;
				m_pThLaserOn = NULL;
				break;
			}
			else
			{
				//�̷߳������˳�
				TRACE("�����̷߳������˳�����������ֵ: %d \n", dRet);
				delete m_pThLaserOn;
				m_pThLaserOn = NULL;
				break;
			}
		}
	}


	//AfxMessageBox(_T("������"));
	m_bMarkOrRedIsRunning = FALSE;
	return TRUE;
}

BOOL CDeviceCardMarkBSL::LaserOn()
{
	//������ݿ�
	DeleteALLEntities();
	//д�ӹ�����
	SetPenFromDefaultProcParm(LayerNum_Reserve1);
	//SetPenFromDefaultProcParm(0);
	//��ʼ���
	StartLaserOn();

	return TRUE;
}
BOOL CDeviceCardMarkBSL::LaserOff()
{
	//ֹͣ��̺���
	BSL_StopMark func = (BSL_StopMark)::GetProcAddress(m_hMarkDll, "StopMark");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_StopMark"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strDevId);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_StopMarkʧ��"));
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
	//���pen����


	//����pen����
	penPara penParaTmp;
	int nLayerCount = pObjList->GetLayerCount();
	CMachinePara_Layer* pMachineParaLayerTmp;

	for (int i = 0; i < nLayerCount; i++)
	{
		pMachineParaLayerTmp = pObjList->GetLayerOfNumber(i);

		penParaTmp.nPenNo = i;														//Ҫ���õıʺ�(0-255)
		if( 0 == pMachineParaLayerTmp->m_MachineMode)
			penParaTmp.nMarkLoop = pMachineParaLayerTmp->m_MachinePara.Times;		//�и�ģʽ//�ӹ�����
		else
			penParaTmp.nMarkLoop = 1;												//����ģʽ//�ӹ�����
		penParaTmp.dMarkSpeed = pMachineParaLayerTmp->m_MachinePara.Speed;			//����ٶ�mm/s
		penParaTmp.dPowerRatio = pMachineParaLayerTmp->m_MachinePara.Power;			//���ʰٷֱ�(0-100%)	
		penParaTmp.nFreq = pMachineParaLayerTmp->m_MachinePara.Frequncy;			//Ƶ��HZ
		penParaTmp.nQPulseWidth = pMachineParaLayerTmp->m_MachinePara.PulseWidth;	//Q������us	

		penParaTmp.nStartTC = gLaserOnDelay;										//��ʼ��ʱus
		penParaTmp.nLaserOffTC = gLaserOffDelay;									//����ر���ʱus 
		penParaTmp.nEndTC = gAfterMarkDelay;										//������ʱus
		penParaTmp.nPolyTC = gPolylineDelay;										//�ս���ʱus	
		penParaTmp.nJumpPosTC = gBeforMarkDelay;									//��̺���ʱ/��ת��ʱ

		//��penParaд�뿨��
		BSL_SetPenParam func = (BSL_SetPenParam)::GetProcAddress(m_hMarkDll, "SetPenParam");
		if (NULL == func)
		{
			AfxMessageBox(_T("SDK��û���ҵ�BSL_SetPenParam"));
			return FALSE;
		}
		int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, penParaTmp.nPenNo, penParaTmp.nMarkLoop, penParaTmp.dMarkSpeed,
			penParaTmp.dPowerRatio, penParaTmp.dCurrent, penParaTmp.nFreq, penParaTmp.nQPulseWidth, 
			penParaTmp.nStartTC, penParaTmp.nLaserOffTC, penParaTmp.nEndTC, penParaTmp.nPolyTC,
			penParaTmp.dJumpSpeed, penParaTmp.nJumpPosTC, penParaTmp.nJumpDistTC, penParaTmp.dEndComp,
			penParaTmp.bPulsePointMode, penParaTmp.nPulseNum, penParaTmp.POINTTIME);
		if (iRes != BSL_ERR_SUCCESS)
		{
			AfxMessageBox(_T("BSL_SetPenParamʧ��"));
			return FALSE;
		}
		
	}
	return TRUE;
}

BOOL CDeviceCardMarkBSL::SetPenFromDefaultProcParm(UINT nPenNo)
{
	penPara penParaTmp;

	penParaTmp.nPenNo = nPenNo;						//Ҫ���õıʺ�(0-255)
	if (0 == gProcessMode)			
		penParaTmp.nMarkLoop = gProcessTimes;		//�и�ģʽ//�ӹ�����
	else
		penParaTmp.nMarkLoop = 1;					//����ģʽ//�ӹ�����
	penParaTmp.dMarkSpeed = gProcessSpeed;			//����ٶ�mm/s
	penParaTmp.dPowerRatio = gProcessPower;			//���ʰٷֱ�(0-100%)	
	penParaTmp.nFreq = gProcessFrequncy;			//Ƶ��HZ
	penParaTmp.nQPulseWidth = gProcessPulseWidth;	//Q������us	

	penParaTmp.nStartTC = gLaserOnDelay;			//��ʼ��ʱus
	penParaTmp.nLaserOffTC = gLaserOffDelay;		//����ر���ʱus 
	penParaTmp.nEndTC = gAfterMarkDelay;			//������ʱus
	penParaTmp.nPolyTC = gPolylineDelay;			//�ս���ʱus	
	penParaTmp.nJumpPosTC = gBeforMarkDelay;		//���ǰ��ʱ

	//��penParaд�뿨��
	BSL_SetPenParam func = (BSL_SetPenParam)::GetProcAddress(m_hMarkDll, "SetPenParam");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_SetPenParam"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, penParaTmp.nPenNo, penParaTmp.nMarkLoop, penParaTmp.dMarkSpeed,
		penParaTmp.dPowerRatio, penParaTmp.dCurrent, penParaTmp.nFreq, penParaTmp.nQPulseWidth,
		penParaTmp.nStartTC, penParaTmp.nLaserOffTC, penParaTmp.nEndTC, penParaTmp.nPolyTC,
		penParaTmp.dJumpSpeed, penParaTmp.nJumpPosTC, penParaTmp.nJumpDistTC, penParaTmp.dEndComp,
		penParaTmp.bPulsePointMode, penParaTmp.nPulseNum, penParaTmp.POINTTIME);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_SetPenParamʧ��"));
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardMarkBSL::DeleteALLEntities()
{
	//���.orzx�ļ�
	BSL_ClearEntityLib func = (BSL_ClearEntityLib)::GetProcAddress(m_hMarkDll, "ClearEntityLib");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_ClearEntityLib"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_ClearEntityLibʧ��"));
		return FALSE;
	}

	return TRUE;

}

BOOL CDeviceCardMarkBSL::SaveEntityToFile()
{
	BSL_SaveEntLibToFile func = (BSL_SaveEntLibToFile)::GetProcAddress(m_hMarkDll, "SaveEntLibToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_SaveEntLibToFile"));
		return FALSE;
	}
	wchar_t* szFileName = (PTCHAR)(LPCTSTR)m_strFileName;
	int iRes = func(szFileName);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_SaveEntLibToFileʧ��"));
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardMarkBSL::AddEntityLines(int nCount, double ptPos[][2], int nPenNo)
{
	//��Ӷ����
	BSL_AddLinesToFile func = (BSL_AddLinesToFile)::GetProcAddress(m_hMarkDll, "AddLinesToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_AddLinesToFile"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, ptPos, nCount, L"������߶�", nPenNo);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AddLinesToFileʧ��"));
		return FALSE;
	}

	return TRUE;

}

BOOL CDeviceCardMarkBSL::AddEntityCircle(double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo)
{
	//����Բ�ϲ岹����
	int nCountPt;
	double(*ptBuf)[2];
	double fMarkArcStepAngle;

	fMarkArcStepAngle = m_fMarkArcStep / fRadius * 180 / M_PI;
	nCountPt =(int) ((2 * M_PI * fRadius) / m_fMarkArcStep) + 2;
	ptBuf = new double[nCountPt][2];

	
	if (0 == nDir)//˳ʱ��
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
	else if (1 == nDir)//��ʱ��
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

	//��ptBufд���ļ�
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}

	//��Ӷ����
	BSL_AddLinesToFile func = (BSL_AddLinesToFile)::GetProcAddress(m_hMarkDll, "AddLinesToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_AddLinesToFile"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, ptBuf, nCountPt, L"�����Բ", nPenNo);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AddLinesToFileʧ��"));
		return FALSE;
	}

	delete[] ptBuf;

	return TRUE;
}


BOOL CDeviceCardMarkBSL::AddEntityArc(double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo)
{
	//����Բ���ϲ岹����
	int nCountPt; 
	double(*ptBuf)[2];
	double fAngleDelt = fAngleEnd - fAngleStart;
	double fMarkArcStepAngle;
	fMarkArcStepAngle = m_fMarkArcStep / fRadius * 180 / M_PI;

	if (0 == nDir)//˳ʱ��
	{
		if (0 <= fAngleDelt)//�ӻ�
			nCountPt = (int) (((M_PI * (360 - fAngleDelt) / 180) * fRadius) / m_fMarkArcStep) + 2;
		else//�Ż�
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
	else if (1 == nDir)//��ʱ��
	{
		if (0 <= fAngleDelt)//�Ż�
			nCountPt = (int) (((M_PI * fAngleDelt / 180) * fRadius) / m_fMarkArcStep) + 2;
		else//�ӻ�
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

	//��ptBufд���ļ�
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}

	//��Ӷ����
	BSL_AddLinesToFile func = (BSL_AddLinesToFile)::GetProcAddress(m_hMarkDll, "AddLinesToFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_AddLinesToFile"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, ptBuf, nCountPt, L"�����Բ��", nPenNo);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AddLinesToFileʧ��"));
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
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}

	BSL_SetCalFileFlag func1 = (BSL_SetCalFileFlag)::GetProcAddress(m_hMarkDll, "SetCalFileFlag");
	if (NULL == func1)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_SetCalFileFlag"));
		return FALSE;
	}
	func1(bFlagCaliFile, L"default");

	if (bFlagCaliFile)
	{
		BSL_SetCalFile func = (BSL_SetCalFile)::GetProcAddress(m_hMarkDll, "SetCalFile");
		if (NULL == func)
		{
			AfxMessageBox(_T("SDK��û���ҵ�BSL_SetCalFile"));
			return FALSE;
		}
		func((PTCHAR)(LPCTSTR)m_strCaliName, L"default");
	}
	
	return TRUE;
}


//����߳̿���
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

	//���õ���ֹͣ��̺�������ǿ��ֹͣ����
	//ֹͣ��̺���
	BSL_StopMark func = (BSL_StopMark)::GetProcAddress(m_hMarkDll, "StopMark");
	if (NULL != func)
	{
		int iRes = func((PTCHAR)(LPCTSTR)m_strDevId);
		if (iRes != BSL_ERR_SUCCESS)
		{
			AfxMessageBox(_T("BSL_StopMarkʧ��"));
		}
	}
	else
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_StopMark"));
	}

	//�ȴ�����߳�ֹͣ
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

	////ɾ���߳�ָ��
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
		AfxMessageBox(_T("SDK��û���ҵ�BSL_MarkByDeviceId"));
		return 1;
	}
	int iRes = func((PTCHAR)(LPCTSTR)strDevID);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_MarkByDeviceIdʧ��"));
		return 1;
	}

	//AfxMessageBox(_T("BSL_MarkByDeviceId���"));
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

	//��ʼ���
	if (strDevID.IsEmpty())
	{
		return 1;
	}
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_LarseOnPoint"));
		return 1;
	}
	int iRes = func((PTCHAR)(LPCTSTR)strDevID, 0, 0, 60000, LayerNum_Reserve1);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_LarseOnPointʧ��"));
		return 1;
	}

	//AfxMessageBox(_T("�������"));
	return 0;
}


//��ȡ���е��豸ID 
BOOL CDeviceCardMarkBSL::GetFreshDevlist()
{
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}

	BSL_GetAllDevices2 func = (BSL_GetAllDevices2)::GetProcAddress(m_hMarkDll, "GetAllDevices2");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_GetAllDevices2"));
		return FALSE;
	}

	STU_DEVID* pDevs = new STU_DEVID[10];  //���֧��8�ſ�
	int iCount = 0;
	int iRes = func(pDevs, &iCount);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_GetAllDevices2ʧ��"));
		delete[] pDevs;
		return FALSE;
	}

	if (0 >= iCount)
	{
		AfxMessageBox(_T("BSL_GetAllDevices2δ����Ӳ��"));
		delete[] pDevs;
		return FALSE;
	}

	m_strDevId = (CString)pDevs[0].szName;
	if (m_strDevId.IsEmpty())
	{
		AfxMessageBox(_T("m_strDevIdΪ��"));
		delete[] pDevs;
		return FALSE;
	}

	delete [] pDevs;
	return TRUE;

}

//��.orzx�ļ�
BOOL CDeviceCardMarkBSL::InitialDataFile()
{
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}
	//��ȡ.orzx�ļ�
	BSL_LoadDataFile func = (BSL_LoadDataFile)::GetProcAddress(m_hMarkDll, "LoadDataFile");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_LoadDataFile"));
		return FALSE;
	}
	int iRes = func((LPTSTR)(LPCTSTR)m_strFileName);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_LoadDataFileʧ��"));
		return FALSE;
	}

	//���.orzx�ļ�
	BSL_ClearEntityLib func1 = (BSL_ClearEntityLib)::GetProcAddress(m_hMarkDll, "ClearEntityLib");
	if (NULL == func1)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_ClearEntityLib"));
		return FALSE;
	}
	int iRes1 = func1((PTCHAR)(LPCTSTR)m_strFileName);
	if (iRes1 != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_ClearEntityLibʧ��"));
		return FALSE;
	}


	return TRUE;
}

BOOL CDeviceCardMarkBSL::AppendFileToDevice()
{
	if (!m_hMarkDll)
	{
		AfxMessageBox(_T("MarkSDK.dll ����ʧ��"));
		return FALSE;
	}

	//�����ļ����豸
	BSL_AppendFileToDevice func = (BSL_AppendFileToDevice)::GetProcAddress(m_hMarkDll, "AppendFileToDevice");
	if (NULL == func)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_AppendFileToDevice"));
		return FALSE;
	}
	int iRes = func((PTCHAR)(LPCTSTR)m_strFileName, (PTCHAR)(LPCTSTR)m_strDevId);
	if (iRes != BSL_ERR_SUCCESS)
	{
		AfxMessageBox(_T("BSL_AppendFileToDeviceʧ��"));
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardMarkBSL::InitialBSLFuncCalledInThread()
{
	m_funcMarkByDeviceId = (BSL_MarkByDeviceId)::GetProcAddress(m_hMarkDll, "MarkByDeviceId");
	if (NULL == m_funcMarkByDeviceId)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_MarkByDeviceId"));
		return FALSE;
	}
	//m_funcMarkPoint = (BSL_MarkPoint)::GetProcAddress(m_hMarkDll, "MarkPoint");
	//if (NULL == m_funcMarkPoint)
	//{
	//	AfxMessageBox(_T("SDK��û���ҵ�BSL_MarkPoint"));
	//	return FALSE;
	//}
	m_funcLaserOnPoint = (BSL_LarseOnPoint)::GetProcAddress(m_hMarkDll, "LarseOnPoint");
	if (NULL == m_funcLaserOnPoint)
	{
		AfxMessageBox(_T("SDK��û���ҵ�BSL_LarseOnPoint"));
		return FALSE;
	}

	

	return TRUE;

}

