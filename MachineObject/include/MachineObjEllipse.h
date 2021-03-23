// CMachineObjEllipse 加工对象正椭圆类（长轴与X轴或Y轴重合）
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjEllipse命令目标
class CMachineObjEllipse :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjEllipse();
	CMachineObjEllipse(ObjPoint EllipseCenter, double m_EllipseXRadius,
		double EllipseRatio, char StartNum = 3, int EllipseByLayer = LayerNum_Default,
		ObjDir m_EllipseDir = CCW);
	~CMachineObjEllipse();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjPoint m_EllipseCenter;
	double m_EllipseXRadius;
	double m_EllipseRatio;
	char m_StartNum;
	ObjDir m_EllipseDir;

// 操作
private:
	void ReSizeBound();
public:
	void SetEllipseXradius(double xRadius);
	void SetEllipseRatio(double ratio);
	void MoveEllipseStart(ObjPoint point);
	void MoveEllipseCenter(ObjPoint point);
	void MoveEllipse(double X_shift, double Y_shift);
	ObjPoint GetEllipseCenter();
	ObjPoint GetEllipseStart();
	ObjPoint GetEllipsePoint(double Radian);
	ObjDir GetEllipseDir();
	double CalDirAngle(double Radian);
	void ExchangeDirection();
	void SetEllipseStart(char StartNum);
	char GetEllipseStartNum();
	double GetEllipseXRadius();
	double GetEllipseRatio();
	double GetEllipseYRadius();
	
};

