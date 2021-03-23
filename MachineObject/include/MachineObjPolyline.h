// CMachineObjPolyline 加工对象多段线类
//
#pragma once
#include "MachineObj_Comm.h"
#include "MachineObjLine.h"
#include "MachineObjArc.h"

// CMachineObjPolyline 命令目标
class CMachineObjPolyline :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjPolyline();
	~CMachineObjPolyline();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjVPoint m_LastVpoint;
protected:
	int m_VertexCount;
	VectVpoint m_pVectorVPoint;


// 操作
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

