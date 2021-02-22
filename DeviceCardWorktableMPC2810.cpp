#include "stdafx.h"
#include "DeviceCardWorktableMPC2810.h"
#include "Mpc2810.h"
#include "XSleep.h"

CDeviceCardWorktableMPC2810::CDeviceCardWorktableMPC2810()
{
	m_nTotalAxes = -1;
	m_nTotalCards = -1;

	//m_axis初始化
	//m_axisX.nIndex = 1;
	//m_axisY.nIndex = 2;
	//m_axisZ.nIndex = 3;
}

CDeviceCardWorktableMPC2810:: ~CDeviceCardWorktableMPC2810()
{

}


BOOL CDeviceCardWorktableMPC2810::InitialCardWorktable()
{
	//控制器初始化
	if (!InitialBoard())
		return FALSE;

	//运动参数初始化
	if (!InitialParamMove())
		return FALSE;

	//控制轴初始化
	if (!InitialAxis())
		return FALSE;

	//编码器初始化
	if (!InitialEncoder())
		return FALSE;

	//专用输入信号初始化
	if (!InitialDedicatedInput())
		return FALSE;

	return TRUE;
}

BOOL CDeviceCardWorktableMPC2810::ResetZeroWorktable()
{
	reset_pos(m_axisX.nIndex);
	reset_pos(m_axisY.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("ResetZeroWorktable失败"));
		reset_err();
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardWorktableMPC2810::PosMoveXY(double fPosX, double fPosY, BOOL bCheckPos)
{
	//先停止运动
	sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisX.nIndex, 0); 
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHigh * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHigh * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//设置轴是否反向
	if (m_axisX.nReverse == 1)
		fPosX = -fPosX;
	if (m_axisY.nReverse == 1)
		fPosY = -fPosY;

	//暂存当前位置，用于终点判断
	double fPosStartX, fPosStartY, fPosEndX, fPosEndY;
	if (bCheckPos)
	{
		GetAbsPosXY(&fPosStartX, &fPosStartY);
		fPosEndX = fPosStartX + fPosX;
		fPosEndY = fPosStartY + fPosY;
	}

	//开始梯形运动
	fast_pmove2(m_axisX.nIndex, fPosX * m_axisX.fPulsePerMM, m_axisY.nIndex, fPosY * m_axisY.fPulsePerMM);

	//位置终点判断
	while (bCheckPos)
	{		
		WaitForMoveEndedXY();
		GetAbsPosXY(&fPosStartX, &fPosStartY);
		if ( abs(fPosEndX - fPosStartX) < 0.001 && abs(fPosEndY - fPosStartY) < 0.001 )
			break;
		//AfxMessageBox(_T("没有到位，再走一次"));
		fast_pmove2(m_axisX.nIndex, (fPosEndX - fPosStartX) * m_axisX.fPulsePerMM, m_axisY.nIndex, (fPosEndY - fPosStartY) * m_axisY.fPulsePerMM);
	}

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveXY失败"));
		reset_err();
		return FALSE;
	}

	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::PosMoveXYHand(double fPosX, double fPosY)
{
	//先停止运动
	sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisX.nIndex, 0);
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHand * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHand * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//开始梯形运动
	if (m_axisX.nReverse == 1)
		fPosX = -fPosX;
	if (m_axisY.nReverse == 1)
		fPosY = -fPosY;
	fast_pmove2(m_axisX.nIndex, fPosX * m_axisX.fPulsePerMM, m_axisY.nIndex, fPosY * m_axisY.fPulsePerMM);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveXYHand失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::PosMoveZ(double fPos)
{
	//先停止运动
	sudden_stop(m_axisZ.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHigh * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//开始梯形运动
	if (m_axisZ.nReverse == 1)
		fPos = -fPos;
	fast_pmove(m_axisZ.nIndex, fPos * m_axisZ.fPulsePerMM);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveZ失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::PosMoveZHand(double fPos)
{
	//先停止运动
	sudden_stop(m_axisZ.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHand * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//开始梯形运动
	if (m_axisZ.nReverse == 1)
		fPos = -fPos;
	fast_pmove(m_axisZ.nIndex, fPos * m_axisZ.fPulsePerMM);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveZHand失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::JogMoveX(int nDir)
{
	//先停止运动
	sudden_stop(m_axisX.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisX.nIndex, 0);
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHand * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	//开始梯形运动
	if (m_axisX.nReverse == 1)
		nDir = -nDir;
	fast_vmove(m_axisX.nIndex, nDir);


	if (0 != get_last_err())
	{
		AfxMessageBox(_T("JogMoveX失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::JogMoveY(int nDir)
{
	//先停止运动
	sudden_stop(m_axisY.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHand * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//开始梯形运动
	if (m_axisY.nReverse == 1)
		nDir = -nDir;
	fast_vmove(m_axisY.nIndex, nDir);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("JogMoveY失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::JogMoveZ(int nDir)
{
	//先停止运动
	sudden_stop(m_axisZ.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHand * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//开始梯形运动
	if (m_axisZ.nReverse == 1)
		nDir = -nDir;
	fast_vmove(m_axisZ.nIndex, nDir);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("JogMoveZ失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::HomeMoveXY(int nDirX, int nDirY)
{
	//先停止运动
	sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisX.nIndex, 0);
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHigh * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHigh * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//开始梯形运动
	fast_hmove2(m_axisX.nIndex, nDirX, m_axisY.nIndex, nDirY);
	WaitForMoveEndedXY();
	reset_pos(m_axisX.nIndex);
	reset_pos(m_axisY.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("HomeMoveXY失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::HomeMoveZ(int nDir)
{
	//先停止运动
	sudden_stop(m_axisZ.nIndex);

	//设置运动参数 - 默认梯形运动
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHigh * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//开始梯形运动
	fast_hmove(m_axisZ.nIndex, nDir);
	WaitForMoveEndedZ();
	reset_pos(m_axisZ.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("HomeMoveZ失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

//BOOL CDeviceCardWorktableMPC2810::LineMoveXY(double fPosX, double fPosY)
//{
//	//设置运动参数 - 默认梯形运动
//	set_s_curve(m_axisX.nIndex, 0);
//	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax);
//	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow, m_axisX.fSpeedHigh, m_axisX.fSpeedAcc);
//
//	set_s_curve(m_axisY.nIndex, 0);
//	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax);
//	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow, m_axisY.fSpeedHigh, m_axisY.fSpeedAcc);
//
//	//开始梯形运动
//	fast_line2(m_axisX.nIndex, fPosX * m_axisX.fPulsePerMM, m_axisY.nIndex, fPosY * m_axisY.fPulsePerMM);
//
//	if (0 != get_last_err())
//	{
//		AfxMessageBox(_T("LineMoveXY失败"));
//		reset_err();
//		return FALSE;
//	}
//	return TRUE;
//
//}

BOOL CDeviceCardWorktableMPC2810::StopMoveXY(BOOL bSudden, BOOL bCheckPos)
{
	if (bSudden)
		sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);
	else
		decel_stop2(m_axisX.nIndex, m_axisY.nIndex);

	if (bCheckPos)
		WaitForMoveEndedXY();

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("StopMoveXY失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceCardWorktableMPC2810::StopMoveX(BOOL bSudden, BOOL bCheckPos)
{
	if (bSudden)
		sudden_stop(m_axisX.nIndex);
	else
		decel_stop(m_axisX.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("StopMoveX失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceCardWorktableMPC2810::StopMoveY(BOOL bSudden, BOOL bCheckPos)
{
	if (bSudden)
		sudden_stop(m_axisY.nIndex);
	else
		decel_stop(m_axisY.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("StopMoveY失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}
BOOL CDeviceCardWorktableMPC2810::StopMoveZ(BOOL bSudden, BOOL bCheckPos)
{
	if (bSudden)
		sudden_stop(m_axisZ.nIndex);
	else
		decel_stop(m_axisZ.nIndex);

	if (bCheckPos)
		WaitForMoveEndedZ();


	if (0 != get_last_err())
	{
		AfxMessageBox(_T("StopMoveZ失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceCardWorktableMPC2810::WaitForMoveEndedXY()
{
	XSleep(1);

	MSG msg;
	while (check_done(m_axisX.nIndex) || check_done(m_axisY.nIndex))
	{
		//如果任意一个轴没有停止，就继续等待

		//响应消息
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		XSleep(50);
	}

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("WaitForMoveEndedXY失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}
BOOL CDeviceCardWorktableMPC2810::WaitForMoveEndedZ()
{
	while (check_done(m_axisZ.nIndex))
	{
		//如果Z轴没有停止，就继续等待
	}

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("WaitForMoveEndedZ失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::GetAbsPosXY(double* fAbsPosX, double* fAbsPosY)
{
	double fAbsPosPulseX, fAbsPosPulseY;
	get_abs_pos(m_axisX.nIndex, &fAbsPosPulseX);
	get_abs_pos(m_axisY.nIndex, &fAbsPosPulseY);
	*fAbsPosX = fAbsPosPulseX / m_axisX.fPulsePerMM;
	*fAbsPosY = fAbsPosPulseY / m_axisY.fPulsePerMM;

	if (0 != get_last_err())
	{
		//AfxMessageBox(_T("GetAbsPosXY失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::GetAbsPosZ(double* fAbsPos)
{
	double fAbsPosPulse;
	get_abs_pos(m_axisZ.nIndex, &fAbsPosPulse);
	*fAbsPos = fAbsPosPulse / m_axisZ.fPulsePerMM;

	if (0 != get_last_err())
	{
		//AfxMessageBox(_T("GetAbsPosZ失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}



//MPC2810

//控制器初始化
BOOL CDeviceCardWorktableMPC2810::InitialBoard()
{
	m_nTotalAxes = auto_set();			//自动设置
	if (m_nTotalAxes <= 0)
	{
		AfxMessageBox(_T("检测不到MPC2810卡!"));
		return FALSE;
	}

	m_nTotalCards = init_board();		//初始化
	if (m_nTotalCards <= 0)
	{
		AfxMessageBox(_T("初始化错误!"));
		return FALSE;
	}

	return TRUE;
}

//控制轴初始化
BOOL CDeviceCardWorktableMPC2810::InitialAxis()
{
	//运动控制器提供六种回原点模式：
	//	0：检测到原点接近开关信号轴立即停止运动；
	//	1：检测到出现编码器 Z 相脉冲信号时立即停止运动。
	//	2：检测到原点接近开关信号轴立即反向，遇 Z 脉冲立即停止。
	//	3：梯形速度模式时，减速信号有效减速，当原点接近开关信号有效停止运动。
	//	4：梯形速度模式下作回原点运动，原点信号有效时，控制轴按快速运动方式设置的加速度逐渐减速至低速，直到 Z 脉冲有效立即停止运动。
	//	5：梯形速度模式下作回原点运动，原点信号有效时，控制轴按快速运动方式设置的加速度减速停止。再反向运动，遇 Z 脉冲停止反向运动。
	//	注意，模式 0~2 只能用于常速运动，后三种回原点模式只在快速运动下有效。
	//	在回原点后，应调用位置复位函数“reset_pos“将控制轴当前位置设置为原点坐标。
	//	控制轴在回原点过程中，若先检测到有效的限位信号，控制轴将自动反向找原点
	set_home_mode(m_axisX.nIndex, m_axisX.nModeHome);
	set_home_mode(m_axisY.nIndex, m_axisY.nModeHome);
	set_home_mode(m_axisZ.nIndex, m_axisZ.nModeHome);

	enable_softlimit(m_axisX.nIndex, m_axisX.nFlagSoftlimit);
	enable_softlimit(m_axisY.nIndex, m_axisY.nFlagSoftlimit);
	enable_softlimit(m_axisZ.nIndex, m_axisZ.nFlagSoftlimit);

	//enable_io_pos
	//set_outmode
	//enable_poserr_limit
	//enable_input_mode
	//set_steps_pr

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("控制轴初始化失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}

//编码器初始化
BOOL CDeviceCardWorktableMPC2810::InitialEncoder()
{
	//set_encoder_mode
	//enable_lock_enc
	//enable_gear
	//enable_handwheel
	//set_enc_thread

	return TRUE;
}

//专用输入信号初始化
BOOL CDeviceCardWorktableMPC2810::InitialDedicatedInput()
{
	//专用输入包括:减速/限位/原点/报警
	//for (int i = 0; i < m_nTotalAxes; i++)
	//{
	//	set_sd_logic(i + 1, 0);
	//	set_el_logic(i + 1, 0);
	//	set_org_logic(i + 1, 0);
	//	set_alm_logic(i + 1, 0);
	//}

	//专用输入包括:减速/限位/原点/报警
	enable_sd(m_axisX.nIndex, m_axisX.nFlagSlowdown);
	set_sd_logic(m_axisX.nIndex, m_axisX.nModeSlowdown);
	enable_el(m_axisX.nIndex, m_axisX.nFlagLimit);
	set_el_logic(m_axisX.nIndex, m_axisX.nModeLimit);
	enable_org(m_axisX.nIndex, m_axisX.nFlagOrg);
	set_org_logic(m_axisX.nIndex, m_axisX.nModeOrg);
	enable_alm(m_axisX.nIndex, m_axisX.nFlagAlm);
	set_alm_logic(m_axisX.nIndex, m_axisX.nModeAlm);

	enable_sd(m_axisY.nIndex, m_axisY.nFlagSlowdown);
	set_sd_logic(m_axisY.nIndex, m_axisY.nModeSlowdown);
	enable_el(m_axisY.nIndex, m_axisY.nFlagLimit);
	set_el_logic(m_axisY.nIndex, m_axisY.nModeLimit);
	enable_org(m_axisY.nIndex, m_axisY.nFlagOrg);
	set_org_logic(m_axisY.nIndex, m_axisY.nModeOrg);
	enable_alm(m_axisY.nIndex, m_axisY.nFlagAlm);
	set_alm_logic(m_axisY.nIndex, m_axisY.nModeAlm);

	enable_sd(m_axisZ.nIndex, m_axisZ.nFlagSlowdown);
	set_sd_logic(m_axisZ.nIndex, m_axisZ.nModeSlowdown);
	enable_el(m_axisZ.nIndex, m_axisZ.nFlagLimit);
	set_el_logic(m_axisZ.nIndex, m_axisZ.nModeLimit);
	enable_org(m_axisZ.nIndex, m_axisZ.nFlagOrg);
	set_org_logic(m_axisZ.nIndex, m_axisZ.nModeOrg);
	enable_alm(m_axisZ.nIndex, m_axisZ.nFlagAlm);
	set_alm_logic(m_axisZ.nIndex, m_axisZ.nModeAlm);


	if (0 != get_last_err())
	{
		AfxMessageBox(_T("专用输入信号初始化失败"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceCardWorktableMPC2810::InitialParamMove()
{
	//读ini初始化m_axisX,m_axisY,m_axisZ

	//XY轴参数初始化
	int nAxisXIndex = ReadDevWorktableAxisXIndex();				
	int nAxisYIndex = ReadDevWorktableAxisYIndex();
	int nAxisXReverse = ReadDevWorktableAxisXReverse();
	int nAxisYReverse = ReadDevWorktableAxisYReverse();
	double fPulsePerMM = ReadDevWorktablePulsePerMMXY();
	int nModeHome = ReadDevWorktableModeHomeXY();
	int nFlagSoftlimit = ReadDevWorktableFlagSlowdownXY();
	int nFlagSlowdown = ReadDevWorktableFlagSlowdownXY();
	int nModeSlowdown = ReadDevWorktableModeSlowdownXY();
	int nFlagLimit = ReadDevWorktableFlagLimitXY();
	int nModeLimit = ReadDevWorktableModeLimitXY();
	int nFlagOrg = ReadDevWorktableFlagOrgXY();
	int nModeOrg = ReadDevWorktableModeOrgXY();
	int nFlagAlm = ReadDevWorktableFlagAlmXY();
	int nModeAlm = ReadDevWorktableModeAlmXY();
	double fSpeedMax = ReadDevWorktableSpeedMaxXY();
	double fSpeedLow = ReadDevWorktableSpeedLowXY();
	double fSpeedHigh = ReadDevWorktableSpeedHighXY();
	double fSpeedAcc = ReadDevWorktableSpeedAccXY();
	double fSpeedHand = ReadDevWorktableSpeedHandXY();
	double fSpeedDefaultProc = ReadDevWorktableSpeedProcXY();
	
	m_axisX.SetParamAxis(nAxisXIndex, nAxisXReverse, fPulsePerMM, nModeHome, nFlagSoftlimit,
					nFlagSlowdown, nModeSlowdown, nFlagLimit, nModeLimit, nFlagOrg, nModeOrg, nFlagAlm, nModeAlm,
					fSpeedMax, fSpeedLow, fSpeedHigh, fSpeedAcc, fSpeedHand, fSpeedDefaultProc);

	m_axisY.SetParamAxis(nAxisYIndex, nAxisYReverse, fPulsePerMM, nModeHome, nFlagSoftlimit,
		nFlagSlowdown, nModeSlowdown, nFlagLimit, nModeLimit, nFlagOrg, nModeOrg, nFlagAlm, nModeAlm,
		fSpeedMax, fSpeedLow, fSpeedHigh, fSpeedAcc, fSpeedHand, fSpeedDefaultProc);

	//Z轴参数初始化
	int nAxisZIndex = ReadDevWorktableAxisZIndex();
	int nAxisZReverse = ReadDevWorktableAxisZReverse();
	fPulsePerMM = ReadDevWorktablePulsePerMMZ();
	nModeHome = ReadDevWorktableModeHomeZ();
	nFlagSoftlimit = ReadDevWorktableFlagSlowdownZ();
	nFlagSlowdown = ReadDevWorktableFlagSlowdownZ();
	nModeSlowdown = ReadDevWorktableModeSlowdownZ();
	nFlagLimit = ReadDevWorktableFlagLimitZ();
	nModeLimit = ReadDevWorktableModeLimitZ();
	nFlagOrg = ReadDevWorktableFlagOrgZ();
	nModeOrg = ReadDevWorktableModeOrgZ();
	nFlagAlm = ReadDevWorktableFlagAlmZ();
	nModeAlm = ReadDevWorktableModeAlmZ();
	fSpeedMax = ReadDevWorktableSpeedMaxZ();
	fSpeedLow = ReadDevWorktableSpeedLowZ();
	fSpeedHigh = ReadDevWorktableSpeedHighZ();
	fSpeedAcc = ReadDevWorktableSpeedAccZ();
	fSpeedHand = ReadDevWorktableSpeedHandZ();
	fSpeedDefaultProc = ReadDevWorktableSpeedProcZ();

	m_axisZ.SetParamAxis(nAxisZIndex, nAxisZReverse, fPulsePerMM, nModeHome, nFlagSoftlimit,
		nFlagSlowdown, nModeSlowdown, nFlagLimit, nModeLimit, nFlagOrg, nModeOrg, nFlagAlm, nModeAlm,
		fSpeedMax, fSpeedLow, fSpeedHigh, fSpeedAcc, fSpeedHand, fSpeedDefaultProc);

	return TRUE;
}


