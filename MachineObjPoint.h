// CMachineObjPoint 加工对象点类
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjPoint 命令目标
class CMachineObjPoint :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjPoint();
	CMachineObjPoint(ObjPoint Point, float MachineWaitTime = 0,
		int PointByLayer = LayerNum_Default);
	~CMachineObjPoint();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjPoint m_Point;
public:
	float m_MachineWaitTime;	//停留时间 单位ms

// 操作
private:
	void ReSizeBound();
public:
	void SetPoint(ObjPoint Point);
	ObjPoint GetPoint();
	
};

