// CMachineObjPolyline �ӹ�����������
//
#pragma once
#include "MachineObj_Comm.h"
#include "MachineObjLine.h"
#include "MachineObjArc.h"

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
	ObjVPoint m_LastVpoint;
protected:
	int m_VertexCount;
	VectVpoint m_pVectorVPoint;


// ����
private:
	int Quadrant(double x, double y);
	void ReSizeBound(ObjVPoint Vpoint);

public:
	VectVpoint GetPolylineVPointVect();
	void AddObjVpoint(ObjVPoint Vpoint);
	void ChangeLastVpoint(ObjVPoint Vpoint);
	int GetPolylineVertexCount();
	void MovePolylinePoint(ObjVPoint point, int count = 0);
	void MovePolylineStart(ObjPoint point);
	void MovePolylineEnd(ObjPoint point);
	void MovePolyline(double X_shift, double Y_shift);
	void ExchangeStartAndEnd(CMachineObjPolyline* pObj);
	void ModifyPolylineVpoint(ObjVPoint Vpoint, int Vertex_Num);
	ObjVPoint GetPolylineStart();
	ObjVPoint GetPolylineEnd();
	ObjVPoint GetPolylinePoint(int Num);
	BOOL TranPolylineToArc(ObjPoint StartPoint, ObjPoint EndPoint, double Convexity,
		ObjPoint* ArcCenter, double* Radius, double* StartAngle, double* EndAngle);
	CMachineObjArc* TranPolylineToArc(ObjPoint StartPoint, ObjPoint EndPoint,
		double Convexity, int nLayer = LayerNum_Default);
	void ClosePolylineEndToStart();


	
};

