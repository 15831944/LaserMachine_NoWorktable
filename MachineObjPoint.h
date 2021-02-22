// CMachineObjPoint �ӹ��������
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjPoint ����Ŀ��
class CMachineObjPoint :public CMachineObj_Comm
{
// ����
public:
	CMachineObjPoint();
	CMachineObjPoint(ObjPoint Point, float MachineWaitTime = 0,
		int PointByLayer = LayerNum_Default);
	~CMachineObjPoint();
	virtual void Serialize(CArchive& ar);

// ����
private:
	ObjPoint m_Point;
public:
	float m_MachineWaitTime;	//ͣ��ʱ�� ��λms

// ����
private:
	void ReSizeBound();
public:
	void SetPoint(ObjPoint Point);
	ObjPoint GetPoint();
	
};

