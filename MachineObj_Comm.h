// CMachineObj_Comm 加工对象通用类
//
#pragma once
#include "MachineObjDef.h"
#include <corecrt_math_defines.h>


// CMachineObj_Comm 命令目标
class CMachineObj_Comm : public CObject
{
// 构造
public:
	CMachineObj_Comm();
	virtual ~CMachineObj_Comm();

// 特性
protected:
	int m_ObjType;				//对象类型
	ObjRect m_ObjBound;			//对象外框
public:
	BOOL m_bIsObjSel;			//选中标志
	int m_ObjByLayer;

// 实现
public:
	int GetObjType();
	ObjRect GetObjBound();
	ObjPoint GetObjStart(CMachineObj_Comm* pObj);
	ObjPoint GetObjEnd(CMachineObj_Comm* pObj);
	CMachineObj_Comm* ExchangeStartAndEnd(CMachineObj_Comm* pObj);
};
// 加工对象列表 CMachineObjList
typedef CTypedPtrList<CObList, CMachineObj_Comm*> CMachineObjList;
