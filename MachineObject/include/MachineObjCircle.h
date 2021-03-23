// CMachineObjCircle 加工对象圆类
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjCircle命令目标
class CMachineObjCircle :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjCircle();
	CMachineObjCircle(ObjPoint CircleCenter, double CircleRadius, char StartNum = 3,
		int CircleByLayer = LayerNum_Default, ObjDir CircleDir = CCW);
	~CMachineObjCircle();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjPoint m_CircleCenter;
	double m_CircleRadius;
	char m_StartNum;
	ObjDir m_CircleDir;

// 操作
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

