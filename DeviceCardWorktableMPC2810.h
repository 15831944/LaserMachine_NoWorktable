#pragma once
#include "DeviceCardWorktable.h"


class CDeviceCardWorktableMPC2810 :
    public CDeviceCardWorktable
{
	// ����
public:
	CDeviceCardWorktableMPC2810();
	virtual ~CDeviceCardWorktableMPC2810();

	// ����
protected:
	int m_nTotalAxes, m_nTotalCards;


	// ʵ��
public:
	//�忨��ʼ��
	virtual BOOL InitialCardWorktable();
	virtual BOOL ResetZeroWorktable();

	//�˶���������

	//�˶�ָ�� - �����˶����� - ��λ
	virtual BOOL PosMoveXY(double fPosX, double fPosY, BOOL bCheckPos = FALSE);
	virtual BOOL PosMoveXYHand(double fPosX, double fPosY);
	//BOOL PosMoveXYProc(double fPosX, double fPosY);
	virtual BOOL PosMoveZ(double fPos);
	virtual BOOL PosMoveZHand(double fPos);
	//�˶�ָ�� - �����˶����� - ����
	virtual BOOL JogMoveX(int nDir);
	virtual BOOL JogMoveY(int nDir);
	virtual BOOL JogMoveZ(int nDir);
	//�˶�ָ�� - �����˶����� - ��ԭ��
	virtual BOOL HomeMoveXY(int nDirX, int nDirY);
	virtual BOOL HomeMoveZ(int nDir);
	//�˶�ָ�� - �岹�˶����� - ���Բ岹
	//BOOL LineMoveXY(double fPosX, double fPosY);
	//�˶�ָ�� - �岹�˶����� - Բ���岹
	//BOOL ArcMoveXY(double fCenterX, double fCenterY, double fAngle);

	//�ƶ�ָ��
	virtual BOOL StopMoveXY(BOOL bSudden, BOOL bCheckPos = FALSE);
	virtual BOOL StopMoveX(BOOL bSudden, BOOL bCheckPos = FALSE);
	virtual BOOL StopMoveY(BOOL bSudden, BOOL bCheckPos = FALSE);
	virtual BOOL StopMoveZ(BOOL bSudden, BOOL bCheckPos = FALSE);

	//I/O����


	//λ�ú�״̬����
	virtual BOOL WaitForMoveEndedXY();
	virtual BOOL WaitForMoveEndedZ();
	virtual BOOL GetAbsPosXY(double* fAbsPosX, double* fAbsPosY);
	virtual BOOL GetAbsPosZ(double* fAbsPos);


	//MPC2810
protected:

	////////////////////////////////////////////////////
	//�忨��ʼ��
	//��������ʼ��
	BOOL InitialBoard();
	//�������ʼ��
	BOOL InitialAxis();
	//��������ʼ��
	BOOL InitialEncoder();
	//ר�������źų�ʼ��
	BOOL InitialDedicatedInput();
	//�˶�������ʼ��
	BOOL InitialParamMove();
	//�忨��ʼ��
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//�˶���������
	//�˶���������
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//�˶�ָ��
	//�˶�ָ��
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//�ƶ�ָ��
	//�ƶ�ָ��
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//I/O����
	int ReadInputAll(int nCardNo);
	int ReadInputBit(int nCardNo, int nBitNo);
	BOOL WriteOutput(int nCardNo, int nByteData);
	BOOL WriteOutput(int nCardNo, int nBitNo, int nStatus);
	//I/O����
	///////////////////////////////////////////////////


	////////////////////////////////////////////////////
	//λ�ú�״̬����
	//λ�ú�״̬����
	///////////////////////////////////////////////////
	

	////////////////////////////////////////////////////
	//������봦��
	//������봦��
	///////////////////////////////////////////////////

};

