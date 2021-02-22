// MachineObjEllipse.cpp : 实现文件
//
#include "stdafx.h"
#include "MachineObjEllipse.h"

// CMachineObjEllipse 的构造函数
CMachineObjEllipse::CMachineObjEllipse()
{
	m_ObjType = MachineObj_Type_Ellipse;
	m_EllipseCenter = ObjPoint();
	m_EllipseXRadius = 0;
	m_EllipseRatio = 1;
	m_StartNum = 3;
	m_EllipseDir = CCW;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjSel = FALSE;
	m_ObjBound = ObjRect();
}

CMachineObjEllipse::CMachineObjEllipse(ObjPoint EllipseCenter, double EllipseXRadius,
	double EllipseRatio, char StartNum, int EllipseByLayer, ObjDir EllipseDir)
{
	m_ObjType = MachineObj_Type_Ellipse;
	m_EllipseCenter = EllipseCenter;
	m_EllipseXRadius = EllipseXRadius;
	m_EllipseRatio = EllipseRatio;
	m_StartNum = StartNum;
	m_EllipseDir = EllipseDir;
	m_ObjByLayer = EllipseByLayer;
	m_bIsObjSel = FALSE;
	ReSizeBound();
}

CMachineObjEllipse::~CMachineObjEllipse()
{
}
// 序列化
void CMachineObjEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_EllipseCenter.x << m_EllipseCenter.y
			<< m_EllipseXRadius << m_EllipseRatio << m_StartNum
			<< m_EllipseDir
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		int eTemp;
		m_ObjType = MachineObj_Type_Ellipse;
		ar >> m_EllipseCenter.x >> m_EllipseCenter.y
			>> m_EllipseXRadius >> m_EllipseRatio >> m_StartNum;
		ar >> eTemp;
		if (eTemp == CCW)
			m_EllipseDir = CCW;
		else
			m_EllipseDir = CW;
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjSel = FALSE;
	}
}

// CMachineObjEllipse 的成员函数
// 私有函数
void CMachineObjEllipse::ReSizeBound()
{
	m_ObjBound.min_x = m_EllipseCenter.x - m_EllipseXRadius;
	m_ObjBound.max_x = m_EllipseCenter.x + m_EllipseXRadius;
	m_ObjBound.min_y = m_EllipseCenter.y - m_EllipseXRadius * m_EllipseRatio;
	m_ObjBound.max_y = m_EllipseCenter.y + m_EllipseXRadius * m_EllipseRatio;
}

// 公开函数
void CMachineObjEllipse::SetEllipseXradius(double xRadius)
{
	m_EllipseXRadius = xRadius;
	ReSizeBound();
}

void CMachineObjEllipse::SetEllipseRatio(double ratio)
{
	m_EllipseRatio = ratio;
	ReSizeBound();
}

void CMachineObjEllipse::MoveEllipseStart(ObjPoint point)
{
	ObjPoint point1;
	point1 = GetEllipseStart();
	m_EllipseCenter.x = m_EllipseCenter.x + (point.x - point1.x);
	m_EllipseCenter.y = m_EllipseCenter.y + (point.y - point1.y);
	ReSizeBound();
}

void CMachineObjEllipse::MoveEllipseCenter(ObjPoint point)
{
	m_EllipseCenter = point;
	ReSizeBound();
}

ObjPoint CMachineObjEllipse::GetEllipseStart()
{
	ObjPoint StartPoint;
	switch (m_StartNum)
	{
	case 0:
		StartPoint.x = m_EllipseCenter.x + m_EllipseXRadius;
		StartPoint.y = m_EllipseCenter.y;
		break;
	case 1:
		StartPoint.x = m_EllipseCenter.x;
		StartPoint.y = m_EllipseCenter.y + m_EllipseXRadius * m_EllipseRatio;
		break;
	case 2:
		StartPoint.x = m_EllipseCenter.x - m_EllipseXRadius;
		StartPoint.y = m_EllipseCenter.y;
		break;
	default:
		StartPoint.x = m_EllipseCenter.x;
		StartPoint.y = m_EllipseCenter.y - m_EllipseXRadius * m_EllipseRatio;
		break;
	}
	return StartPoint;
}

ObjPoint CMachineObjEllipse::GetEllipseCenter()
{
	return m_EllipseCenter;
}

ObjPoint CMachineObjEllipse::GetEllipsePoint(double Radian)
{
	ObjPoint point;
	point.x = m_EllipseCenter.x + m_EllipseXRadius * cos(Radian);
	point.y = m_EllipseCenter.y + m_EllipseXRadius * m_EllipseRatio * sin(Radian);
	return point;
}

ObjDir CMachineObjEllipse::GetEllipseDir()
{
	return m_EllipseDir;
}

double CMachineObjEllipse::CalDirAngle(double Radian)
{
	double dx = -m_EllipseXRadius * sin(Radian);
	double dy = m_EllipseXRadius * m_EllipseRatio * cos(Radian);
	if (GetEllipseDir() == CCW)
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

void CMachineObjEllipse::ExchangeDirection()
{
	if (m_EllipseDir == CCW)
		m_EllipseDir = CW;
	else
		m_EllipseDir = CCW;
}

void CMachineObjEllipse::SetEllipseStart(char StartNum)
{
	if (StartNum > 3 || StartNum < 0)
		m_StartNum = 3;
	else
		m_StartNum = StartNum;
}

char CMachineObjEllipse::GetEllipseStartNum()
{
	return m_StartNum;
}

double CMachineObjEllipse::GetEllipseXRadius()
{
	return m_EllipseXRadius;
}

double CMachineObjEllipse::GetEllipseRatio()
{
	return m_EllipseRatio;
}

double CMachineObjEllipse::GetEllipseYRadius()
{
	return m_EllipseXRadius * m_EllipseRatio;
}

