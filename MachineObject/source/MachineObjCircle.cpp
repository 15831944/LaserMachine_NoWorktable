// MachineObjCircle.cpp : 实现文件
//
#include "stdafx.h"
#include "MachineObjCircle.h"

// CMachineObjCircle 的构造函数
CMachineObjCircle::CMachineObjCircle()
{
	m_ObjType = MachineObj_Type_Circle;
	m_CircleCenter = ObjPoint();
	m_CircleRadius = 0;
	m_StartNum = 3;
	m_CircleDir = CCW;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjCircle::CMachineObjCircle(ObjPoint CircleCenter, double CircleRadius, char StartNum,
	int CircleByLayer, ObjDir CircleDir)
{
	m_ObjType = MachineObj_Type_Circle;
	m_CircleCenter = CircleCenter;
	m_CircleRadius = CircleRadius;
	if (StartNum > 3 || StartNum < 0)
		m_StartNum = 3;
	else
		m_StartNum = StartNum;
	m_CircleDir = CircleDir;
	m_ObjByLayer = CircleByLayer;
	m_bIsObjStatus = IsObjNormal;
	ReSizeBound();
}

CMachineObjCircle::~CMachineObjCircle()
{
}
// 序列化
void CMachineObjCircle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_CircleCenter.x << m_CircleCenter.y
			<< m_CircleRadius << m_StartNum << m_CircleDir
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		int eTemp;
		m_ObjType = MachineObj_Type_Circle;
		ar >> m_CircleCenter.x >> m_CircleCenter.y
			>> m_CircleRadius >> m_StartNum;
		ar >> eTemp;
		if (eTemp == CCW)
			m_CircleDir = CCW;
		else
			m_CircleDir = CW;
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
	}
}


// CMachineObjCircle 的成员函数
// 私有函数
void CMachineObjCircle::ReSizeBound()
{
	m_ObjBound.min_x = m_CircleCenter.x - m_CircleRadius;
	m_ObjBound.max_x = m_CircleCenter.x + m_CircleRadius;
	m_ObjBound.min_y = m_CircleCenter.y - m_CircleRadius;
	m_ObjBound.max_y = m_CircleCenter.y + m_CircleRadius;
}

// 公开函数
ObjPoint CMachineObjCircle::GetCircleCenter()
{
	return m_CircleCenter;
}

ObjPoint CMachineObjCircle::GetCircleStart()
{
	ObjPoint point;
	switch (m_StartNum)
	{
	case 0:
		point.x = m_CircleCenter.x + m_CircleRadius;
		point.y = m_CircleCenter.y;
		break;
	case 1:
		point.x = m_CircleCenter.x;
		point.y = m_CircleCenter.y + m_CircleRadius;
		break;
	case 2:
		point.x = m_CircleCenter.x - m_CircleRadius;
		point.y = m_CircleCenter.y;
		break;
	default:
		point.x = m_CircleCenter.x;
		point.y = m_CircleCenter.y - m_CircleRadius;
		break;
	}
	return point;
}

ObjPoint CMachineObjCircle::GetCirclePoint(double Angle)
{
	ObjPoint point;
	
	point.x = m_CircleCenter.x + m_CircleRadius*cos(M_PI * Angle / 180);
	point.y = m_CircleCenter.y + m_CircleRadius*sin(M_PI * Angle / 180);
	return point;
}

void CMachineObjCircle::ExchangeDirection()
{
	if (m_CircleDir == CCW)
		m_CircleDir = CW;
	else
		m_CircleDir = CCW;
}

void CMachineObjCircle::MoveCircleCenter(ObjPoint CircleCenter)
{
	m_CircleCenter = CircleCenter;
	ReSizeBound();
}

void CMachineObjCircle::SetCircleStart(char StartNum)
{
	if (StartNum > 3 || StartNum < 0)
		m_StartNum = 3;
	else
		m_StartNum = StartNum;
}

void CMachineObjCircle::SetCircleRadius(double radius)
{
	m_CircleRadius = radius;
	ReSizeBound();
}

char CMachineObjCircle::GetCircleStartNum()
{
	return m_StartNum;
}

void CMachineObjCircle::MoveCircleStart(ObjPoint CircleStart)
{
	double x_offset, y_offset;
	ObjPoint point = GetCircleStart();
	x_offset = CircleStart.x - point.x;
	y_offset = CircleStart.y - point.y;
	m_CircleCenter.x += x_offset;
	m_CircleCenter.y += y_offset;
	ReSizeBound();
}

void CMachineObjCircle::MoveCircle(double X_shift, double Y_shift)
{
	m_CircleCenter.x += X_shift;
	m_CircleCenter.y += Y_shift;
	ReSizeBound();
}

double CMachineObjCircle::GetCircleRadius()
{
	return m_CircleRadius;
}

ObjDir CMachineObjCircle::GetCircleDir()
{
	return m_CircleDir;
}

double CMachineObjCircle::CalDirAngle(double Angle)
{
	double dx = -m_CircleRadius * sin(M_PI * Angle / 180);
	double dy = m_CircleRadius * cos(M_PI * Angle / 180);
	if (m_CircleDir == CCW)
	{
		if (dx > 0)
		{
			return atan(dy / dx);
		}
		else if (dx < 0)
		{
			return atan(dy / dx) + M_PI;
		}
		else
		{
			if (dy > 0)
				return M_PI_2;
			else
				return M_PI + M_PI_2;
		}
	}
	else
	{
		if (dx > 0)
		{
			return atan(dy / dx) + M_PI;
		}
		else if (dx < 0)
		{
			return atan(dy / dx);
		}
		else
		{
			if (dy < 0)
				return M_PI_2;
			else
				return M_PI + M_PI_2;
		}
	}

}

