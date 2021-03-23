// MachineObjPoint.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "MachineObjPoint.h"

// CMachineObjPoint ���캯��
CMachineObjPoint::CMachineObjPoint()
{
	m_ObjType = MachineObj_Type_Point;
	m_Point = ObjPoint();
	m_MachineWaitTime = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjPoint::CMachineObjPoint(ObjPoint Point, float MachineWaitTime, int PointByLayer)
{
	m_ObjType = MachineObj_Type_Point;
	m_Point = Point;
	m_MachineWaitTime = MachineWaitTime;
	m_ObjByLayer = PointByLayer;
	m_bIsObjStatus = IsObjNormal;
	ReSizeBound();
}

CMachineObjPoint::~CMachineObjPoint()
{
}
// ���л�
void CMachineObjPoint::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_Point.x << m_Point.y << m_MachineWaitTime
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		m_ObjType = MachineObj_Type_Point;
		ar >> m_Point.x >> m_Point.y >> m_MachineWaitTime
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
	}
}

// CMachineObjPoint ��Ա����
// ˽�к���
void CMachineObjPoint::ReSizeBound()
{
	m_ObjBound.min_x = m_Point.x;
	m_ObjBound.max_x = m_Point.x;
	m_ObjBound.min_y = m_Point.y;
	m_ObjBound.max_y = m_Point.y;
}

// �������� 
void CMachineObjPoint::SetPoint(ObjPoint Point)
{
	m_Point = ObjPoint(Point.x, Point.y);
	ReSizeBound();
}

void CMachineObjPoint::MovePoint(double X_shift, double Y_shift)
{
	m_Point.x += X_shift;
	m_Point.y += Y_shift;
	ReSizeBound();
}

ObjPoint CMachineObjPoint::GetPoint()
{
	return m_Point;
}



