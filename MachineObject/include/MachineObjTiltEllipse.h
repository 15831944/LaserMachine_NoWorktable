// CMachineObjTiltEllipse 加工对象斜椭圆类（含弧）
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjTiltEllipse 命令目标
class CMachineObjTiltEllipse :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjTiltEllipse();
	CMachineObjTiltEllipse(ObjPoint EllipseCenter, ObjPoint LongAxisOffset,
		double EllipseRatio, double ArcStartRadian, double ArcEndRadian,
		int EllipseByLayer = LayerNum_Default, ObjDir dir = CCW);
	~CMachineObjTiltEllipse();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjPoint m_EllipseCenter;
	ObjPoint m_LongAxisOffset;
	double m_EllipseRatio;
	double m_ArcStartRadian;
	double m_ArcEndRadian;

// 操作
private:
	void ReSizeBound();
public:
	void ExchangeStartAndEnd(CMachineObjTiltEllipse* pObj);
	void MoveTiltEllipseCenter(ObjPoint point);
	void MoveTiltEllipseStart(ObjPoint point);
	void MoveTiltEllipseEnd(ObjPoint point);
	void MoveTileEllipse(double X_shift, double Y_shift);
	void SetTiltEllipseXRadius(double radius);
	void SetTiltEllipseRatio(double ratio);
	void SetStartAndEndRadian(double radian1, double radian2, ObjDir dir);
	void SetRotateRadian(double radian);
	ObjPoint GetTiltEllipseCenter();
	ObjPoint GetTiltEllipseStart();
	ObjPoint GetTiltEllipseEnd();
	ObjPoint GetTiltEllipsePoint(double radian);
	double GetTiltEllipseXRadius();
	double GetTiltEllipseRatio();
	double GetTiltEllipseYRadius();
	double GetRotateRadian();
	double GetStartRadian();
	double GetEndRadian();
	ObjDir GetArcDir();
	double CalDirAngle(double Radian);
	double CalDistance(ObjPoint point);
	double CalAbsStartRadian();
	double CalAbsEndRadian();
	


};

