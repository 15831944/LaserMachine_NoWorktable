#pragma once
#include <afx.h>
#include "CDlgDevCfgTabWorktable.h"


class CDeviceCardWorktable :
    public CObject
{
	// ����
public:
	CDeviceCardWorktable();
	virtual ~CDeviceCardWorktable();

	// ����
protected:


	// ʵ��
public:
	class paramAxis
	{
	public:
		paramAxis() {};

		int nIndex;					//�����
		int nReverse;				//ֻӰ���ֶ���/��/��/���ƶ�����̨ʱ��ķ��򣬲�Ӱ���������ĵ�λ�˶�
		double fPulsePerMM;			//���嵱��
		int nModeHome;				//�˶��������ṩ���ֻ�ԭ��ģʽ��
									//	0����⵽ԭ��ӽ������ź�������ֹͣ�˶���
									//	1����⵽���ֱ����� Z �������ź�ʱ����ֹͣ�˶���
									//	2����⵽ԭ��ӽ������ź������������� Z ��������ֹͣ��
									//	3�������ٶ�ģʽʱ�������ź���Ч���٣���ԭ��ӽ������ź���Чֹͣ�˶���
									//	4�������ٶ�ģʽ������ԭ���˶���ԭ���ź���Чʱ�������ᰴ�����˶���ʽ���õļ��ٶ��𽥼��������٣�ֱ�� Z ������Ч����ֹͣ�˶���
									//	5�������ٶ�ģʽ������ԭ���˶���ԭ���ź���Чʱ�������ᰴ�����˶���ʽ���õļ��ٶȼ���ֹͣ���ٷ����˶����� Z ����ֹͣ�����˶���
		int nFlagSoftlimit;			//ʹ�������λ

		int nFlagSlowdown;			//ʹ��ר�����룺����/��λ/ԭ��/���� - nFlag=0 �ر� - nFlag=1 ����
		int nModeSlowdown;			//����/��λ/ԭ��/���� - nMode=0 �͵�ƽ��Ч - nMode=1 �ߵ�ƽ��Ч
		int nFlagLimit;
		int nModeLimit;
		int nFlagOrg;
		int nModeOrg;
		int nFlagAlm;
		int nModeAlm;

		double fSpeedMax;			//�ٶȲ���
		double fSpeedLow;
		double fSpeedHigh;			//Ĭ�Ͽ����ٶȣ������ָ��ӹ�ʱ���ٶ�
		double fSpeedAcc;
		double fSpeedHand;			//�ֶ��ƶ�����̨�ٶ�
		double fSpeedDefaultProc;	//�ù���̨�ӹ�ʱ��Ĭ���ٶ�

		void SetParamAxis(int nIndex, int nReverse, double fPulsePerMM, int nModeHome, int nFlagSoftlimit,
			int nFlagSlowdown, int nModeSlowdown, int nFlagLimit, int nModeLimit, int nFlagOrg, int nModeOrg, int nFlagAlm, int nModeAlm,
			double fSpeedMax, double fSpeedLow, double fSpeedHigh, double fSpeedAcc, double fSpeedHand, double fSpeedDefaultProc)
		{
			this->nIndex = nIndex;
			this->nReverse = nReverse;
			this->fPulsePerMM = fPulsePerMM;
			this->nModeHome = nModeHome;
			this->nFlagSoftlimit = nFlagSoftlimit;

			this->nFlagSlowdown = nFlagSlowdown;
			this->nModeSlowdown = nModeSlowdown;
			this->nFlagLimit = nFlagLimit;
			this->nModeLimit = nModeLimit;
			this->nFlagOrg = nFlagOrg;
			this->nModeOrg = nModeOrg;
			this->nFlagAlm = nFlagAlm;
			this->nModeAlm = nModeAlm;

			this->fSpeedMax = fSpeedMax;
			this->fSpeedLow = fSpeedLow;
			this->fSpeedHigh = fSpeedHigh;
			this->fSpeedAcc = fSpeedAcc;
			this->fSpeedHand = fSpeedHand;
			this->fSpeedDefaultProc = fSpeedDefaultProc;
		}

	};
	paramAxis m_axisX, m_axisY, m_axisZ;

public:
	//�忨��ʼ��
	virtual BOOL InitialCardWorktable() = 0;
	virtual BOOL ResetZeroWorktable() = 0;

	//�˶���������

	//�˶�ָ�� - �����˶����� - ��λ
	virtual BOOL PosMoveXY(double fPosX, double fPosY, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL PosMoveXYHand(double fPosX, double fPosY) = 0;
	//BOOL PosMoveXYProc(double fPosX, double fPosY) = 0;
	virtual BOOL PosMoveZ(double fPos) = 0;
	virtual BOOL PosMoveZHand(double fPos) = 0;
	//�˶�ָ�� - �����˶����� - ����
	virtual BOOL JogMoveX(int nDir) = 0;
	virtual BOOL JogMoveY(int nDir) = 0;
	virtual BOOL JogMoveZ(int nDir) = 0;
	//�˶�ָ�� - �����˶����� - ��ԭ��
	virtual BOOL HomeMoveXY(int nDirX, int nDirY) = 0;
	virtual BOOL HomeMoveZ(int nDir) = 0;
	//�˶�ָ�� - �岹�˶����� - ���Բ岹
	//BOOL LineMoveXY(double fPosX, double fPosY);
	//�˶�ָ�� - �岹�˶����� - Բ���岹
	//BOOL ArcMoveXY(double fCenterX, double fCenterY, double fAngle);

	//�ƶ�ָ��
	virtual BOOL StopMoveXY(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL StopMoveX(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL StopMoveY(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;
	virtual BOOL StopMoveZ(BOOL bSudden, BOOL bCheckPos = FALSE) = 0;

	//I/O����


	//λ�ú�״̬����
	virtual BOOL WaitForMoveEndedXY() = 0;
	virtual BOOL WaitForMoveEndedZ() = 0;
	virtual BOOL GetAbsPosXY(double* fAbsPosX, double* fAbsPosY) = 0;
	virtual BOOL GetAbsPosZ(double* fAbsPos) = 0;

};

extern CDeviceCardWorktable* pDevCardWorktable;

