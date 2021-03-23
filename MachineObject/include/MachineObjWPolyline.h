// CMachineObjWPolyline �ӹ�����չ��������
//
#pragma once
#include "MachineObjPolyline.h"

// CMachineObjWArc ����Ŀ��
class CMachineObjWPolyline :public CMachineObjPolyline
{
// ����
public:
	CMachineObjWPolyline();
	CMachineObjWPolyline(CMachineObjPolyline* pPolyline, int Duplicate, float GapDistance);
	~CMachineObjWPolyline();
	virtual void Serialize(CArchive& ar);

// ����
private:
	int m_Duplicate;
	float m_GapDistance;
public:
	vector<VectVpoint*> m_pDupList;


// ����
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

