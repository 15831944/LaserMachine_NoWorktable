// CMachineObjCircle �ӹ�����Բ��
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjCircle����Ŀ��
class CMachineObjCircle :public CMachineObj_Comm
{
// ����
public:
	CMachineObjCircle();
	CMachineObjCircle(ObjPoint CircleCenter, double CircleRadius, char StartNum = 3,
		int CircleByLayer = LayerNum_Default, ObjDir CircleDir = CCW);
	~CMachineObjCircle();
	virtual void Serialize(CArchive& ar);

// ����
private:
	ObjPoint m_CircleCenter;
	double m_CircleRadius;
	char m_StartNum;
	ObjDir m_CircleDir;

// ����
private:
	void ReSizeBound();
public:
	ObjPoint GetCircleCenter();
	ObjPoint GetCircleStart();
	ObjPoint GetCirclePoint(double Angle);
	ObjDir GetCircleDir();
	double CalDirAngle(double Angle);
	void ExchangeDirection();
	void MoveCircleCenter(ObjPoint CircleCenter);
	void SetCircleStart(char StartNum);
	void SetCircleRadius(double radius);
	char GetCircleStartNum();
	void MoveCircleStart(ObjPoint CircleStart);
	void MoveCircle(double X_shift, double Y_shift);
	double GetCircleRadius();
	
};

