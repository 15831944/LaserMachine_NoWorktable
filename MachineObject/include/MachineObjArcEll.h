// CMachineObjArcEll �ӹ���������Բ��
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjArcEll����Ŀ��
class CMachineObjArcEll :public CMachineObj_Comm
{
// ����
public:
	CMachineObjArcEll();
	CMachineObjArcEll(ObjPoint EllipseCenter, double EllipseXRadius,
		double EllipseRatio, double ArcStartRadian, double ArcEndRadian,
		int ArcByLayer = LayerNum_Default, ObjDir dir = CCW);
	~CMachineObjArcEll();
	virtual void Serialize(CArchive& ar);

// ����
private:
	ObjPoint m_EllipseCenter;
	double m_EllipseXRadius;
	double m_EllipseRatio;
	double m_ArcStartRadian;
	double m_ArcEndRadian;
	
// ���� 
private:
	int Quadrant(double x, double y);
	void ReSizeBound();
public:
	void MoveArcEllCenter(ObjPoint point);
	void MoveArcEllStart(ObjPoint point);
	void MoveArcEllEnd(ObjPoint point);
	void MoveArcEll(double X_shift, double Y_shift);
	void SetArcEllXradius(double radius);
	void SetArcEllRatio(double ratio);
	void SetStartAndEndRadian(double radian1, double radian2, ObjDir dir);
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

