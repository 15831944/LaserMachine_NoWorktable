// CMachineObjPolyline �ӹ�����������
//
#pragma once
#include "MachineObj_Comm.h"
#include "MachineObjLine.h"
#include "MachineObjArc.h"
#include <vector>
using namespace std;

// CMachineObjPolyline ����Ŀ��
class CMachineObjPolyline :public CMachineObj_Comm
{
// ����
public:
	CMachineObjPolyline();
	~CMachineObjPolyline();
	virtual void Serialize(CArchive& ar);

// ����
private:
	int m_VertexCount;
	ObjVPoint m_LastVpoint;
	vector<ObjVPoint> m_pVectorVPoint;


// ����
private:
	int Quadrant(double x, double y);
	void ReSizeBound(ObjVPoint Vpoint);

public:
	void AddObjVpoint(ObjVPoint Vpoint);
	void ChangeLastVpoint(ObjVPoint Vpoint);
	int GetPolylineVertexCount();
	void MovePolylinePoint(ObjVPoint point, int count = 0);
	void MovePolylineStart(ObjPoint point);
	void MovePolylineEnd(ObjPoint point);
	void ExchangeStartAndEnd(CMachineObjPolyline* pObj);
	ObjVPoint GetPolylineStart();
	ObjVPoint GetPolylineEnd();
	ObjVPoint GetPolylinePoint(int Num);
	BOOL TranPolylineToArc(ObjPoint StartPoint, ObjPoint EndPoint, double Convexity,
		ObjPoint* ArcCenter, double* Radius, double* StartAngle, double* EndAngle);
	CMachineObjArc* TranPolylineToArc(ObjPoint StartPoint, ObjPoint EndPoint,
		double Convexity, int nLayer = LayerNum_Default);

	
};

