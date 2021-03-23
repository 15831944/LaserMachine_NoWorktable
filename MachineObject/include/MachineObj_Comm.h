// CMachineObj_Comm �ӹ�����ͨ����
//
#pragma once
#include "MachineObjDef.h"
#include <vector>
using namespace std;

// CMachineObj_Comm ����Ŀ��
class CMachineObj_Comm : public CObject
{
// ����
public:
	CMachineObj_Comm();
	virtual ~CMachineObj_Comm();

// ����
protected:
	int m_ObjType;				//��������
	ObjRect m_ObjBound;			//�������
public:
	byte m_bIsObjStatus;			//����״̬
	int m_ObjByLayer;			//��������ͼ��

// ʵ��
public:
	int GetObjType();
	ObjRect GetObjBound();
	ObjPoint GetObjStart(CMachineObj_Comm* pObj);
	ObjPoint GetObjEnd(CMachineObj_Comm* pObj);
	CMachineObj_Comm* ExchangeStartAndEnd(CMachineObj_Comm* pObj);
};
// �ӹ������б� CMachineObjList
typedef CTypedPtrList<CObList, CMachineObj_Comm*> CMachineObjList;
// ������,�����������ߺͶ����
typedef vector<ObjPoint> VectPoint;
// ��������,��������Polyline
typedef vector<ObjVPoint> VectVpoint;
// ��,�����ϵ�ֱ��
typedef struct TagGeometryLine
{
	ObjPoint  StartPoint;
	ObjPoint  EndPoint;
} GeometryLine;

typedef vector<GeometryLine> VectLine;
