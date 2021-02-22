// CMachineObjGroup �ӹ��������
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
#include "MachineObjGroup.h"

// CMachineObjGroup ����Ŀ��
class CMachineObjGroup :public CMachineObj_Comm
{
// ����
public:
	CMachineObjGroup();
	~CMachineObjGroup();
	virtual void Serialize(CArchive& ar);

// ����
protected:
	CMachineObjList* m_pList;	//������private,�����޷�������*****


// ����
private:
	void ReSizeBound(CMachineObj_Comm* MachineObj);

public:
	CMachineObjList* GetObjList();
	void AddGroupObj(CMachineObj_Comm* MachineObj);
	CMachineObj_Comm* GetAndMoveGroupObj();
};

