// CMachineObj_Comm �ӹ�����ͨ����
//
#pragma once
#include "MachineObjDef.h"
#include <corecrt_math_defines.h>


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
	BOOL m_bIsObjSel;			//ѡ�б�־
	int m_ObjByLayer;

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
