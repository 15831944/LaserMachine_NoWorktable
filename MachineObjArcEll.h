// CMachineObjArcEll 加工对象正椭圆弧
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjArcEll命令目标
class CMachineObjArcEll :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjArcEll();
	CMachineObjArcEll(ObjPoint EllipseCenter, double EllipseXRadius,
		double EllipseRatio, double ArcStartRadian, double ArcEndRadian,
		int ArcByLayer = LayerNum_Default, ObjDir dir = CCW);
	~CMachineObjArcEll();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjPoint m_EllipseCenter;
	double m_EllipseXRadius;
	double m_EllipseRatio;
	double m_ArcStartRadian;
	double m_ArcEndRadian;
	
// 操作 
private:
	int Quadrant(double x, double y);
	void ReSizeBound();
public:
	void MovetEllipseCenter(ObjPoint point);
	void MoveArcStart(ObjPoint point);
	void MoveArcEnd(ObjPoint point);
	void SetEllipseXradius(double radius);
	void SetEllipseRatio(double ratio);
	void SetStartAndEndRadian(double radian1, double radian2);
	void ExchangeStartAndEnd(CMachineObjArcEll* pObj);
	ObjPoint GetEllipseCenter();
	ObjPoint GetArcStart();
	ObjPoint GetArcEnd();
	ObjPoint GetEllipseArcPoint(double Radian);
	double GetEllipseXRadius();
	double GetEllipseRatio();
	double GetEllipseYRadius();
	double GetStartRadian();
	double GetEndRadian();
	ObjDir GetArcDir();
	double CalDirAngle(double Radian);
	
};

