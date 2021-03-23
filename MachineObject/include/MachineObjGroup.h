// CMachineObjGroup 加工对象群组类
//
#pragma once
#include "MachineObj_Comm.h"
#include "MachineObjPoint.h"
#include "MachineObjLine.h"
#include "MachineObjCircle.h"
#include "MachineObjEllipse.h"
#include "MachineObjArc.h"
#include "MachineObjArcEll.h"
#include "MachineObjTiltEllipse.h"
#include "MachineObjPolyline.h"
//#include "MachineObjGroup.h"
#include "MachineObjWLine.h"
#include "MachineObjWArc.h"
#include "MachineObjWPolyline.h"
#include "MachineObjFillPolyline.h"


// CMachineObjGroup 命令目标
class CMachineObjGroup :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjGroup();
	~CMachineObjGroup();
	virtual void Serialize(CArchive& ar);

// 特性
protected:
	CMachineObjList* m_pList;	//不可用private,否则无法被加入*****


// 操作
private:
	void ReSizeBound(CMachineObj_Comm* MachineObj);
public:
	CMachineObjList* GetObjList();
	void AddGroupObj(CMachineObj_Comm* MachineObj);
	CMachineObj_Comm* GetAndMoveGroupObj();
	void MoveGroup(double X_shift, double Y_shift);
};

