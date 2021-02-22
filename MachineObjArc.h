// CMachineObjArc �ӹ�����԰��
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjArc����Ŀ��
class CMachineObjArc :public CMachineObj_Comm
{
// ����
public:
	CMachineObjArc();
	CMachineObjArc(ObjPoint ArcCenter, double m_ArcRadius,
		double StartAngle, double EndAngle,
		int ArcByLayer = LayerNum_Default, ObjDir dir = CCW);
	~CMachineObjArc();
	virtual void Serialize(CArchive& ar);

// ����
private:
	ObjPoint m_ArcCenter;
	double m_ArcRadius;
	double m_StartAngle;
	double m_EndAngle;

// ���� 
private:
	int Quadrant(double x, double y);
	void ReSizeBound();
public:
	void MoveArcCenter(ObjPoint point);
	void MoveArcStart(ObjPoint point);
	void MoveArcEnd(ObjPoint point);
	void SetArcRadius(double radius);
	void SetStartAndEndAngle(double angle1, double angle2);
	void ExchangeStartAndEnd(CMachineObjArc* pObj);
	ObjPoint GetArcCenter();
	ObjPoint GetArcStart();
	ObjPoint GetArcEnd();
	double GetStartAngle();
	double GetEndAngle();
	ObjPoint GetArcPoint(double Angle);
	double GetArcRadius();
	ObjDir GetArcDir();
	double CalDirAngle(double Angle);
	
};

