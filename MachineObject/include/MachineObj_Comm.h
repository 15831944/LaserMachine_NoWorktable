// CMachineObj_Comm 加工对象通用类
//
#pragma once
#include "MachineObjDef.h"
#include <vector>
using namespace std;

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
	byte m_bIsObjStatus;			//对象状态
	int m_ObjByLayer;			//对象所在图层

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
// 点向量,用以描述折线和多边形
typedef vector<ObjPoint> VectPoint;
// 顶点向量,用以描述Polyline
typedef vector<ObjVPoint> VectVpoint;
// 线,几何上的直线
typedef struct TagGeometryLine
{
	ObjPoint  StartPoint;
	ObjPoint  EndPoint;
} GeometryLine;

typedef vector<GeometryLine> VectLine;
