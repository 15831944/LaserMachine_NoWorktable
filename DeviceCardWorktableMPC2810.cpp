#include "stdafx.h"
#include "DeviceCardWorktableMPC2810.h"
#include "Mpc2810.h"
#include "XSleep.h"

CDeviceCardWorktableMPC2810::CDeviceCardWorktableMPC2810()
{
	m_nTotalAxes = -1;
	m_nTotalCards = -1;

	//m_axis��ʼ��
	//m_axisX.nIndex = 1;
	//m_axisY.nIndex = 2;
	//m_axisZ.nIndex = 3;
}

CDeviceCardWorktableMPC2810:: ~CDeviceCardWorktableMPC2810()
{

}


BOOL CDeviceCardWorktableMPC2810::InitialCardWorktable()
{
	//��������ʼ��
	if (!InitialBoard())
		return FALSE;

	//�˶�������ʼ��
	if (!InitialParamMove())
		return FALSE;

	//�������ʼ��
	if (!InitialAxis())
		return FALSE;

	//��������ʼ��
	if (!InitialEncoder())
		return FALSE;

	//ר�������źų�ʼ��
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
		AfxMessageBox(_T("ResetZeroWorktableʧ��"));
		reset_err();
		return FALSE;
	}

	return TRUE;
}


BOOL CDeviceCardWorktableMPC2810::PosMoveXY(double fPosX, double fPosY, BOOL bCheckPos)
{
	//��ֹͣ�˶�
	sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisX.nIndex, 0); 
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHigh * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHigh * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//�������Ƿ���
	if (m_axisX.nReverse == 1)
		fPosX = -fPosX;
	if (m_axisY.nReverse == 1)
		fPosY = -fPosY;

	//�ݴ浱ǰλ�ã������յ��ж�
	double fPosStartX, fPosStartY, fPosEndX, fPosEndY;
	if (bCheckPos)
	{
		GetAbsPosXY(&fPosStartX, &fPosStartY);
		fPosEndX = fPosStartX + fPosX;
		fPosEndY = fPosStartY + fPosY;
	}

	//��ʼ�����˶�
	fast_pmove2(m_axisX.nIndex, fPosX * m_axisX.fPulsePerMM, m_axisY.nIndex, fPosY * m_axisY.fPulsePerMM);

	//λ���յ��ж�
	while (bCheckPos)
	{		
		WaitForMoveEndedXY();
		GetAbsPosXY(&fPosStartX, &fPosStartY);
		if ( abs(fPosEndX - fPosStartX) < 0.001 && abs(fPosEndY - fPosStartY) < 0.001 )
			break;
		//AfxMessageBox(_T("û�е�λ������һ��"));
		fast_pmove2(m_axisX.nIndex, (fPosEndX - fPosStartX) * m_axisX.fPulsePerMM, m_axisY.nIndex, (fPosEndY - fPosStartY) * m_axisY.fPulsePerMM);
	}

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveXYʧ��"));
		reset_err();
		return FALSE;
	}

	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::PosMoveXYHand(double fPosX, double fPosY)
{
	//��ֹͣ�˶�
	sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisX.nIndex, 0);
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHand * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHand * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//��ʼ�����˶�
	if (m_axisX.nReverse == 1)
		fPosX = -fPosX;
	if (m_axisY.nReverse == 1)
		fPosY = -fPosY;
	fast_pmove2(m_axisX.nIndex, fPosX * m_axisX.fPulsePerMM, m_axisY.nIndex, fPosY * m_axisY.fPulsePerMM);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveXYHandʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::PosMoveZ(double fPos)
{
	//��ֹͣ�˶�
	sudden_stop(m_axisZ.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHigh * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//��ʼ�����˶�
	if (m_axisZ.nReverse == 1)
		fPos = -fPos;
	fast_pmove(m_axisZ.nIndex, fPos * m_axisZ.fPulsePerMM);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveZʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::PosMoveZHand(double fPos)
{
	//��ֹͣ�˶�
	sudden_stop(m_axisZ.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHand * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//��ʼ�����˶�
	if (m_axisZ.nReverse == 1)
		fPos = -fPos;
	fast_pmove(m_axisZ.nIndex, fPos * m_axisZ.fPulsePerMM);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("PosMoveZHandʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::JogMoveX(int nDir)
{
	//��ֹͣ�˶�
	sudden_stop(m_axisX.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisX.nIndex, 0);
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHand * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	//��ʼ�����˶�
	if (m_axisX.nReverse == 1)
		nDir = -nDir;
	fast_vmove(m_axisX.nIndex, nDir);


	if (0 != get_last_err())
	{
		AfxMessageBox(_T("JogMoveXʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::JogMoveY(int nDir)
{
	//��ֹͣ�˶�
	sudden_stop(m_axisY.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHand * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//��ʼ�����˶�
	if (m_axisY.nReverse == 1)
		nDir = -nDir;
	fast_vmove(m_axisY.nIndex, nDir);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("JogMoveYʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::JogMoveZ(int nDir)
{
	//��ֹͣ�˶�
	sudden_stop(m_axisZ.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHand * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//��ʼ�����˶�
	if (m_axisZ.nReverse == 1)
		nDir = -nDir;
	fast_vmove(m_axisZ.nIndex, nDir);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("JogMoveZʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::HomeMoveXY(int nDirX, int nDirY)
{
	//��ֹͣ�˶�
	sudden_stop2(m_axisX.nIndex, m_axisY.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisX.nIndex, 0);
	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax * m_axisX.fPulsePerMM);
	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow * m_axisX.fPulsePerMM, m_axisX.fSpeedHigh * m_axisX.fPulsePerMM, m_axisX.fSpeedAcc * m_axisX.fPulsePerMM);

	set_s_curve(m_axisY.nIndex, 0);
	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax * m_axisY.fPulsePerMM);
	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow * m_axisY.fPulsePerMM, m_axisY.fSpeedHigh * m_axisY.fPulsePerMM, m_axisY.fSpeedAcc * m_axisY.fPulsePerMM);

	//��ʼ�����˶�
	fast_hmove2(m_axisX.nIndex, nDirX, m_axisY.nIndex, nDirY);
	WaitForMoveEndedXY();
	reset_pos(m_axisX.nIndex);
	reset_pos(m_axisY.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("HomeMoveXYʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

BOOL CDeviceCardWorktableMPC2810::HomeMoveZ(int nDir)
{
	//��ֹͣ�˶�
	sudden_stop(m_axisZ.nIndex);

	//�����˶����� - Ĭ�������˶�
	set_s_curve(m_axisZ.nIndex, 0);
	set_maxspeed(m_axisZ.nIndex, m_axisZ.fSpeedMax * m_axisZ.fPulsePerMM);
	set_profile(m_axisZ.nIndex, m_axisZ.fSpeedLow * m_axisZ.fPulsePerMM, m_axisZ.fSpeedHigh * m_axisZ.fPulsePerMM, m_axisZ.fSpeedAcc * m_axisZ.fPulsePerMM);

	//��ʼ�����˶�
	fast_hmove(m_axisZ.nIndex, nDir);
	WaitForMoveEndedZ();
	reset_pos(m_axisZ.nIndex);

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("HomeMoveZʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}

//BOOL CDeviceCardWorktableMPC2810::LineMoveXY(double fPosX, double fPosY)
//{
//	//�����˶����� - Ĭ�������˶�
//	set_s_curve(m_axisX.nIndex, 0);
//	set_maxspeed(m_axisX.nIndex, m_axisX.fSpeedMax);
//	set_profile(m_axisX.nIndex, m_axisX.fSpeedLow, m_axisX.fSpeedHigh, m_axisX.fSpeedAcc);
//
//	set_s_curve(m_axisY.nIndex, 0);
//	set_maxspeed(m_axisY.nIndex, m_axisY.fSpeedMax);
//	set_profile(m_axisY.nIndex, m_axisY.fSpeedLow, m_axisY.fSpeedHigh, m_axisY.fSpeedAcc);
//
//	//��ʼ�����˶�
//	fast_line2(m_axisX.nIndex, fPosX * m_axisX.fPulsePerMM, m_axisY.nIndex, fPosY * m_axisY.fPulsePerMM);
//
//	if (0 != get_last_err())
//	{
//		AfxMessageBox(_T("LineMoveXYʧ��"));
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
		AfxMessageBox(_T("StopMoveXYʧ��"));
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
		AfxMessageBox(_T("StopMoveXʧ��"));
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
		AfxMessageBox(_T("StopMoveYʧ��"));
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
		AfxMessageBox(_T("StopMoveZʧ��"));
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
		//�������һ����û��ֹͣ���ͼ����ȴ�

		//��Ӧ��Ϣ
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		XSleep(50);
	}

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("WaitForMoveEndedXYʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}
BOOL CDeviceCardWorktableMPC2810::WaitForMoveEndedZ()
{
	while (check_done(m_axisZ.nIndex))
	{
		//���Z��û��ֹͣ���ͼ����ȴ�
	}

	if (0 != get_last_err())
	{
		AfxMessageBox(_T("WaitForMoveEndedZʧ��"));
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
		//AfxMessageBox(_T("GetAbsPosXYʧ��"));
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
		//AfxMessageBox(_T("GetAbsPosZʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;

}



//MPC2810

//��������ʼ��
BOOL CDeviceCardWorktableMPC2810::InitialBoard()
{
	m_nTotalAxes = auto_set();			//�Զ�����
	if (m_nTotalAxes <= 0)
	{
		AfxMessageBox(_T("��ⲻ��MPC2810��!"));
		return FALSE;
	}

	m_nTotalCards = init_board();		//��ʼ��
	if (m_nTotalCards <= 0)
	{
		AfxMessageBox(_T("��ʼ������!"));
		return FALSE;
	}

	return TRUE;
}

//�������ʼ��
BOOL CDeviceCardWorktableMPC2810::InitialAxis()
{
	//�˶��������ṩ���ֻ�ԭ��ģʽ��
	//	0����⵽ԭ��ӽ������ź�������ֹͣ�˶���
	//	1����⵽���ֱ����� Z �������ź�ʱ����ֹͣ�˶���
	//	2����⵽ԭ��ӽ������ź������������� Z ��������ֹͣ��
	//	3�������ٶ�ģʽʱ�������ź���Ч���٣���ԭ��ӽ������ź���Чֹͣ�˶���
	//	4�������ٶ�ģʽ������ԭ���˶���ԭ���ź���Чʱ�������ᰴ�����˶���ʽ���õļ��ٶ��𽥼��������٣�ֱ�� Z ������Ч����ֹͣ�˶���
	//	5�������ٶ�ģʽ������ԭ���˶���ԭ���ź���Чʱ�������ᰴ�����˶���ʽ���õļ��ٶȼ���ֹͣ���ٷ����˶����� Z ����ֹͣ�����˶���
	//	ע�⣬ģʽ 0~2 ֻ�����ڳ����˶��������ֻ�ԭ��ģʽֻ�ڿ����˶�����Ч��
	//	�ڻ�ԭ���Ӧ����λ�ø�λ������reset_pos���������ᵱǰλ������Ϊԭ�����ꡣ
	//	�������ڻ�ԭ������У����ȼ�⵽��Ч����λ�źţ������Ὣ�Զ�������ԭ��
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
		AfxMessageBox(_T("�������ʼ��ʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}

//��������ʼ��
BOOL CDeviceCardWorktableMPC2810::InitialEncoder()
{
	//set_encoder_mode
	//enable_lock_enc
	//enable_gear
	//enable_handwheel
	//set_enc_thread

	return TRUE;
}

//ר�������źų�ʼ��
BOOL CDeviceCardWorktableMPC2810::InitialDedicatedInput()
{
	//ר���������:����/��λ/ԭ��/����
	//for (int i = 0; i < m_nTotalAxes; i++)
	//{
	//	set_sd_logic(i + 1, 0);
	//	set_el_logic(i + 1, 0);
	//	set_org_logic(i + 1, 0);
	//	set_alm_logic(i + 1, 0);
	//}

	//ר���������:����/��λ/ԭ��/����
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
		AfxMessageBox(_T("ר�������źų�ʼ��ʧ��"));
		reset_err();
		return FALSE;
	}
	return TRUE;
}

BOOL CDeviceCardWorktableMPC2810::InitialParamMove()
{
	//��ini��ʼ��m_axisX,m_axisY,m_axisZ

	//XY�������ʼ��
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

	//Z�������ʼ��
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


