// MachineObjWArc.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineObjWArc.h"

// MachineObjWArc 构造函数
CMachineObjWArc::CMachineObjWArc()
{
	m_ObjType = MachineObj_Type_WArc;
	m_ArcCenter = ObjPoint();
	m_ArcRadius = 0;
	m_StartAngle = 0;
	m_EndAngle = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_Duplicate = 0;
	m_GapDistance = 0;
	m_pDupList.swap(vector<VectPoint*>(NULL));
	m_ObjBound = ObjRect();
}

CMachineObjWArc::CMachineObjWArc(CMachineObjArc* pArc, int Duplicate, float GapDistance)
{
	m_ObjType = MachineObj_Type_WArc;
	m_ArcCenter = pArc->GetArcCenter();
	m_ArcRadius = pArc->GetArcRadius();
	m_StartAngle = pArc->GetStartAngle();
	m_EndAngle = pArc->GetEndAngle();
	m_ObjByLayer = pArc->m_ObjByLayer;
	m_bIsObjStatus = pArc->m_bIsObjStatus;
	m_Duplicate = Duplicate;
	m_GapDistance = GapDistance;
	CMachineObjArc::ReSizeBound();
	ExtendWArc();
}

CMachineObjWArc::~CMachineObjWArc()
{
	VectPoint* pArc;
	int Count = m_pDupList.size();
	for (int i = 0; i < Count; i++)
	{
		pArc = m_pDupList[i];
		delete pArc;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
}

// 序列化
void CMachineObjWArc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_ArcCenter.x << m_ArcCenter.y
			<< m_ArcRadius << m_StartAngle << m_EndAngle
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer
			<< m_Duplicate << m_GapDistance;
	}
	else
	{
		m_ObjType = MachineObj_Type_WArc;
		ar >> m_ArcCenter.x >> m_ArcCenter.y
			>> m_ArcRadius >> m_StartAngle >> m_EndAngle
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer
			>> m_Duplicate >> m_GapDistance;
		ExtendWArc();
		m_bIsObjStatus = IsObjNormal;
	}
}

 //MachineObjWArc 成员函数
 //私有函数

void CMachineObjWArc::ExtendWArc()
{
	ObjPoint point1, point2, point3;
	VectPoint* pWArc;
	ObjDir dir;
	double radius;
	for (int i = 1; i <= m_Duplicate; i++)
	{
		dir = GetArcDir();
		if (dir == CW)
		{
			point1 = m_ArcCenter;
			point2.x = m_StartAngle;
			point2.y = m_EndAngle;
			radius = m_ArcRadius - i*m_GapDistance;
			if (radius <= 0)
				break;
			point3.x = radius;
			point3.y = 0;
			pWArc = new VectPoint;
			pWArc->push_back(point1);
			pWArc->push_back(point2);
			pWArc->push_back(point3);
			m_pDupList.push_back(pWArc);
		}
		else
		{
			point1 = m_ArcCenter;
			point2.x = m_StartAngle;
			point2.y = m_EndAngle;
			radius = m_ArcRadius + i*m_GapDistance;
			point3.x = radius;
			point3.y = 0;
			pWArc = new VectPoint;
			pWArc->push_back(point1);
			pWArc->push_back(point2);
			pWArc->push_back(point3);
			m_pDupList.push_back(pWArc);
		}
	}
	for (int i = 1; i <= m_Duplicate; i++)
	{
		dir = GetArcDir();
		if (dir == CCW)
		{
			point1 = m_ArcCenter;
			point2.x = m_StartAngle;
			point2.y = m_EndAngle;
			radius = m_ArcRadius - i*m_GapDistance;
			if (radius <= 0)
				break;
			point3.x = radius;
			point3.y = 0;
			pWArc = new VectPoint;
			pWArc->push_back(point1);
			pWArc->push_back(point2);
			pWArc->push_back(point3);
			m_pDupList.push_back(pWArc);
		}
		else
		{
			point1 = m_ArcCenter;
			point2.x = m_StartAngle;
			point2.y = m_EndAngle;
			radius = m_ArcRadius + i*m_GapDistance;
			point3.x = radius;
			point3.y = 0;
			pWArc = new VectPoint;
			pWArc->push_back(point1);
			pWArc->push_back(point2);
			pWArc->push_back(point3);
			m_pDupList.push_back(pWArc);
		}
	}

}

// 公开函数
CMachineObjArc* CMachineObjWArc::DegenerateToArc()
{
	int Count = m_pDupList.size();
	VectPoint* pWArc;
	for (int i = 0; i < Count; i++)
	{
		pWArc = m_pDupList[i];
		delete pWArc;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ObjDir dir = GetArcDir();
	CMachineObjArc* pArc = new CMachineObjArc(m_ArcCenter, m_ArcRadius,
		m_StartAngle, m_EndAngle, m_ObjByLayer, dir);
	pArc->m_bIsObjStatus = m_bIsObjStatus;
	return pArc;
}

void CMachineObjWArc::MoveWArc(double X_shift, double Y_shift)
{
	m_ArcCenter.x += X_shift;
	m_ArcCenter.y += Y_shift;
	ObjPoint point;
	int nCount1 = m_pDupList.size();
	for (int i = 0; i < nCount1; i++)
	{
		VectPoint &pointlist = *m_pDupList[i];
		pointlist[0].x += X_shift;
		pointlist[0].y += Y_shift;
	}
	m_ObjBound.max_x += X_shift;
	m_ObjBound.min_x += X_shift;
	m_ObjBound.max_y += Y_shift;
	m_ObjBound.min_y += Y_shift;
}

int CMachineObjWArc::GetDupNumber()
{
	return m_Duplicate;
}

float CMachineObjWArc::GetGapDistance()
{
	return m_GapDistance;
}

void CMachineObjWArc::SetDupNumber(int DupNumber)
{
	m_Duplicate = DupNumber;
	int Count = m_pDupList.size();
	VectPoint* pWArc;
	for (int i = 0; i < Count; i++)
	{
		pWArc = m_pDupList[i];
		delete pWArc;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ExtendWArc();
}

void CMachineObjWArc::SetGapDistance(float GapDistance)
{
	m_GapDistance = GapDistance;
	int Count = m_pDupList.size();
	VectPoint* pWArc;
	for (int i = 0; i < Count; i++)
	{
		pWArc = m_pDupList[i];
		delete pWArc;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ExtendWArc();
}

void CMachineObjWArc::ReCreatWArc(int DupNumber, float GapDistance)
{
	m_Duplicate = DupNumber;
	m_GapDistance = GapDistance;
	int Count = m_pDupList.size();
	VectPoint* pWArc;
	for (int i = 0; i < Count; i++)
	{
		pWArc = m_pDupList[i];
		delete pWArc;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ExtendWArc();
}
