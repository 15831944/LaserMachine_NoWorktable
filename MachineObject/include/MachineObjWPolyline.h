// CMachineObjWPolyline 加工对象展宽多段线类
//
#pragma once
#include "MachineObjPolyline.h"

// CMachineObjWArc 命令目标
class CMachineObjWPolyline :public CMachineObjPolyline
{
// 构造
public:
	CMachineObjWPolyline();
	CMachineObjWPolyline(CMachineObjPolyline* pPolyline, int Duplicate, float GapDistance);
	~CMachineObjWPolyline();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	int m_Duplicate;
	float m_GapDistance;
public:
	vector<VectVpoint*> m_pDupList;


// 操作
private:
	ObjVPoint CalCrossPoint(ObjVPoint VP_Last, ObjVPoint VP_Now, ObjVPoint VP_Next,
		double *Angle_Last, double *Convexity_Lsat, float Offset,
		ObjVPoint* vpoint_last, VectVpoint* pList);
	void ExtendWPolyline();
public:
	CMachineObjPolyline* DegenerateToPolyline();
	void MoveWPolyline(double X_shift, double Y_shift);
	int GetDupNumber();
	float GetGapDistance();
	void SetDupNumber(int DupNumber);
	void SetGapDistance(float GapDistance);
	void ReCreatWPolyline(int DupNumber, float GapDistance);
	
};

