// MachineObjArcEll.cpp : 实现文件
// 
#include "stdafx.h"
#include "MachineObjArcEll.h"

// CMachineObjArcEll 的构造函数
CMachineObjArcEll::CMachineObjArcEll()
{
	m_ObjType = MachineObj_Type_ArcEll;
	m_EllipseCenter = ObjPoint();
	m_EllipseXRadius = 0;
	m_EllipseRatio = 1;
	m_ArcStartRadian = 0;
	m_ArcEndRadian = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjArcEll::CMachineObjArcEll(ObjPoint EllipseCenter, double EllipseXRadius,
	double EllipseRatio, double ArcStartRadian, double ArcEndRadian,
	int ArcByLayer,ObjDir dir)
{
	m_ObjType = MachineObj_Type_ArcEll;
	m_EllipseCenter = EllipseCenter;
	m_EllipseXRadius = EllipseXRadius;
	m_EllipseRatio = EllipseRatio;
	m_ArcStartRadian = ArcStartRadian;
	if (dir == CCW)
	{
		if ((ArcEndRadian - ArcStartRadian) <= 0)
			m_ArcEndRadian = ArcEndRadian + 2 * M_PI;
		else
			m_ArcEndRadian = ArcEndRadian;
	}
	else
	{
		if ((ArcEndRadian - ArcStartRadian) > 0)
			m_ArcEndRadian = ArcEndRadian - 2 * M_PI;
		else
			m_ArcEndRadian = ArcEndRadian;
	}
	if (m_ArcStartRadian >= 2 * M_PI || m_ArcEndRadian >= 2 * M_PI)
	{
		m_ArcStartRadian -= 2 * M_PI;
		m_ArcEndRadian -= 2 * M_PI;
	}
	else if (m_ArcStartRadian < -2 * M_PI || m_ArcEndRadian < -2 * M_PI)
	{
		m_ArcStartRadian += 2 * M_PI;
		m_ArcEndRadian += 2 * M_PI;
	}
	if (m_ArcStartRadian < 0 && m_ArcEndRadian < 0)
	{
		m_ArcStartRadian += 2 * M_PI;
		m_ArcEndRadian += 2 * M_PI;
	}
	m_ObjByLayer = ArcByLayer;
	m_bIsObjStatus = IsObjNormal;
	ReSizeBound();
}

CMachineObjArcEll::~CMachineObjArcEll()
{
}
// 序列化
void CMachineObjArcEll::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_EllipseCenter.x << m_EllipseCenter.y
			<< m_EllipseXRadius << m_EllipseRatio
			<< m_ArcStartRadian << m_ArcEndRadian
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		m_ObjType = MachineObj_Type_ArcEll;
		ar >> m_EllipseCenter.x >> m_EllipseCenter.y
			>> m_EllipseXRadius >> m_EllipseRatio
			>> m_ArcStartRadian >> m_ArcEndRadian
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
	}
}


// CMachineObjArcEll 的成员函数
// 私有函数
int CMachineObjArcEll::Quadrant(double x, double y)
{
	if (x >= 0 && y >= 0)
		return 1;
	else if (x < 0 && y >= 0)
		return 2;
	else if (x < 0 && y < 0)
		return 3;
	else
		return 4;
}

void CMachineObjArcEll::ReSizeBound()
{
	double x1, y1, x2, y2, a, b;
	int qx1, qx2;
	ObjRect rect;
	ObjPoint point;
	a = m_EllipseXRadius;
	b = m_EllipseXRadius * m_EllipseRatio;
	point = GetArcStart();
	x1 = point.x - m_EllipseCenter.x;
	y1 = point.y - m_EllipseCenter.y;
	point = GetArcEnd();
	x2 = point.x - m_EllipseCenter.x;
	y2 = point.y - m_EllipseCenter.y;
	qx1 = Quadrant(x1, y1);
	qx2 = Quadrant(x2, y2);
	if ( GetArcDir()== CCW)
	{
		if (qx1 == 1)
		{
			if (qx2 == 1)
			{
				if (x1 > x2)
				{
					rect.max_x = x1;
					rect.min_x = x2;
					rect.max_y = y2;
					rect.min_y = y1;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}
			}
			else if (qx2 == 2)
			{
				rect.max_x = x1;
				rect.min_x = x2;
				rect.max_y = b;
				rect.min_y = min(y1, y2);
			}
			else if (qx2 == 3)
			{
				rect.max_x = x1;
				rect.min_x = -a;
				rect.max_y = b;
				rect.min_y = y2;
			}
			else if (qx2 == 4)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -a;
				rect.max_y = b;
				rect.min_y = -b;
			}

		}
		else if (qx1 == 2)
		{
			if (qx2 == 1)
			{
				rect.max_x = a;
				rect.min_x = -a;
				rect.max_y = max(y1, y2);
				rect.min_y = -b;
			}
			else if (qx2 == 2)
			{
				if (x1 > x2)
				{
					rect.max_x = x1;
					rect.min_x = x2;
					rect.max_y = y1;
					rect.min_y = y2;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}

			}
			else if (qx2 == 3)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -a;
				rect.max_y = y1;
				rect.min_y = y2;
			}
			else if (qx2 == 4)
			{
				rect.max_x = x2;
				rect.min_x = -a;
				rect.max_y = y1;
				rect.min_y = -b;
			}
		}
		else if (qx1 == 3)
		{
			if (qx2 == 1)
			{
				rect.max_x = a;
				rect.min_x = x1;
				rect.max_y = y2;
				rect.min_y = -b;
			}
			else if (qx2 == 2)
			{
				rect.max_x = a;
				rect.min_x = min(x1, x2);
				rect.max_y = b;
				rect.min_y = -b;
			}
			else if (qx2 == 3)
			{
				if (x1 < x2)
				{
					rect.max_x = x2;
					rect.min_x = x1;
					rect.max_y = y1;
					rect.min_y = y2;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = --b;
				}
			}
			else if (qx2 == 4)
			{
				rect.max_x = x2;
				rect.min_x = x1;
				rect.max_y = max(y1, y2);
				rect.min_y = -b;
			}
		}
		else if (qx1 == 4)
		{
			if (qx2 == 1)
			{
				rect.max_x = a;
				rect.min_x = min(x1, x2);
				rect.max_y = y2;
				rect.min_y = y1;
			}
			else if (qx2 == 2)
			{
				rect.max_x = a;
				rect.min_x = x2;
				rect.max_y = b;
				rect.min_y = y1;
			}
			else if (qx2 == 3)
			{
				rect.max_x = a;
				rect.min_x = -a;
				rect.max_y = b;
				rect.min_y = min(y1, y2);
			}
			else if (qx2 == 4)
			{
				if (x1 < x2)
				{
					rect.max_x = x2;
					rect.min_x = x1;
					rect.max_y = y2;
					rect.min_y = y1;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}
			}
		}
	}
	if (GetArcDir() == CW)
	{
		if (qx1 == 1)
		{
			if (qx2 == 1)
			{
				if (x1 < x2)
				{
					rect.max_x = x2;
					rect.min_x = x1;
					rect.max_y = y1;
					rect.min_y = y2;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}
			}
			else if (qx2 == 2)
			{
				rect.max_x = a;
				rect.min_x = -a;
				rect.max_y = max(y1, y2);
				rect.min_y = -b;
			}
			else if (qx2 == 3)
			{
				rect.max_x = a;
				rect.min_x = x2;
				rect.max_y = y1;
				rect.min_y = -b;
			}
			else if (qx2 == 4)
			{
				rect.max_x = a;
				rect.min_x = min(x1, x2);
				rect.max_y = y1;
				rect.min_y = y2;
			}
		}
		else if (qx1 == 2)
		{
			if (qx2 == 1)
			{
				rect.max_x = x2;
				rect.min_x = x1;
				rect.max_y = b;
				rect.min_y = min(y1, y2);
			}
			else if (qx2 == 2)
			{
				if (x1 < x2)
				{
					rect.max_x = x2;
					rect.min_x = x1;
					rect.max_y = y2;
					rect.min_y = y1;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}
			}
			else if (qx2 == 3)
			{
				rect.max_x = a;
				rect.min_x = min(x1, x2);
				rect.max_y = b;
				rect.min_y = -b;
			}
			else if (qx2 == 4)
			{
				rect.max_x = a;
				rect.min_x = x1;
				rect.max_y = b;
				rect.min_y = y1;
			}
		}
		else if (qx1 == 3)
		{
			if (qx2 == 1)
			{
				rect.max_x = x2;
				rect.min_x = -a;
				rect.max_y = b;
				rect.min_y = y1;
			}
			else if (qx2 == 2)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -a;
				rect.max_y = y2;
				rect.min_y = y1;
			}
			else if (qx2 == 3)
			{
				if (x1 > x2)
				{
					rect.max_x = x1;
					rect.min_x = x2;
					rect.max_y = y2;
					rect.min_y = y1;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}
			}
			else if (qx2 == 4)
			{
				rect.max_x = a;
				rect.min_x = -a;
				rect.max_y = b;
				rect.min_y = min(y1, y2);
			}
		}
		else if (qx1 == 4)
		{
			if (qx2 == 1)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -a;
				rect.max_y = b;
				rect.min_y = -b;
			}
			else if (qx2 == 2)
			{
				rect.max_x = x1;
				rect.min_x = -a;
				rect.max_y = y2;
				rect.min_y = -b;
			}
			else if (qx2 == 3)
			{
				rect.max_x = x1;
				rect.min_x = x2;
				rect.max_y = max(y1, y2);
				rect.min_y = -b;
			}
			else if (qx2 == 4)
			{
				if (x1 > x2)
				{
					rect.max_x = x1;
					rect.min_x = x2;
					rect.max_y = y1;
					rect.min_y = y2;
				}
				else
				{
					rect.max_x = a;
					rect.min_x = -a;
					rect.max_y = b;
					rect.min_y = -b;
				}
			}
		}
	}
	m_ObjBound.max_x = rect.max_x + m_EllipseCenter.x;
	m_ObjBound.min_x = rect.min_x + m_EllipseCenter.x;
	m_ObjBound.max_y = rect.max_y + m_EllipseCenter.y;
	m_ObjBound.min_y = rect.min_y + m_EllipseCenter.y;
}

// 公共函数
void CMachineObjArcEll::MoveArcEllCenter(ObjPoint point)
{
	m_EllipseCenter = point;
	ReSizeBound();
}

void CMachineObjArcEll::MoveArcEllStart(ObjPoint point)
{
	ObjPoint point1 = GetArcStart();
	m_EllipseCenter.x = m_EllipseCenter.x + point.x - point1.x;
	m_EllipseCenter.y = m_EllipseCenter.y + point.y - point1.y;
	ReSizeBound();
}

void CMachineObjArcEll::MoveArcEllEnd(ObjPoint point)
{
	ObjPoint point1 = GetArcEnd();
	m_EllipseCenter.x = m_EllipseCenter.x + point.x - point1.x;
	m_EllipseCenter.y = m_EllipseCenter.y + point.y - point1.y;
	ReSizeBound();
}

void CMachineObjArcEll::MoveArcEll(double X_shift, double Y_shift)
{
	m_EllipseCenter.x += X_shift;
	m_EllipseCenter.y += Y_shift;
	ReSizeBound();
}

void CMachineObjArcEll::SetArcEllXradius(double radius)
{
	m_EllipseXRadius = radius;
	ReSizeBound();
}

void CMachineObjArcEll::SetArcEllRatio(double ratio)
{
	m_EllipseRatio = ratio;
	ReSizeBound();
}

void CMachineObjArcEll::SetStartAndEndRadian(double radian1, double radian2, ObjDir dir)
{
	m_ArcStartRadian = radian1;
	if (dir == CCW)
	{
		if ((radian2 - radian1) <= 0)
			m_ArcEndRadian = radian2 + 2 * M_PI;
		else
			m_ArcEndRadian = radian2;
	}
	else
	{
		if ((radian2 - radian1) > 0)
			m_ArcEndRadian = radian2 - 2 * M_PI;
		else
			m_ArcEndRadian = radian2;
	}
	if (m_ArcStartRadian >= 2 * M_PI || m_ArcEndRadian >= 2 * M_PI)
	{
		m_ArcStartRadian -= 2 * M_PI;
		m_ArcEndRadian -= 2 * M_PI;
	}
	else if (m_ArcStartRadian < -2 * M_PI || m_ArcEndRadian < -2 * M_PI)
	{
		m_ArcStartRadian += 2 * M_PI;
		m_ArcEndRadian += 2 * M_PI;
	}
	if (m_ArcStartRadian < 0 && m_ArcEndRadian < 0)
	{
		m_ArcStartRadian += 2 * M_PI;
		m_ArcEndRadian += 2 * M_PI;
	}
	ReSizeBound();
}

void CMachineObjArcEll::ExchangeStartAndEnd(CMachineObjArcEll* pObj)
{
	double ArcStartRadian, ArcEndRadian;
	ObjDir dir;
	if (GetArcDir() == CW)
		dir = CCW;
	else
		dir = CW;
	ArcStartRadian = m_ArcEndRadian;
	ArcEndRadian = m_ArcStartRadian;
	m_ArcStartRadian = ArcStartRadian;
	if (dir == CCW)
	{
		if ((ArcEndRadian - ArcStartRadian) <= 0)
			m_ArcEndRadian = ArcEndRadian + 2 * M_PI;
		else
			m_ArcEndRadian = ArcEndRadian;
	}
	else
	{
		if ((ArcEndRadian - ArcStartRadian) > 0)
			m_ArcEndRadian = ArcEndRadian - 2 * M_PI;
		else
			m_ArcEndRadian = ArcEndRadian;
	}
	if (m_ArcStartRadian >= 2 * M_PI || m_ArcEndRadian >= 2 * M_PI)
	{
		m_ArcStartRadian -= 2 * M_PI;
		m_ArcEndRadian -= 2 * M_PI;
	}
	else if (m_ArcStartRadian < -2 * M_PI || m_ArcEndRadian < -2 * M_PI)
	{
		m_ArcStartRadian += 2 * M_PI;
		m_ArcEndRadian += 2 * M_PI;
	}
}

ObjPoint CMachineObjArcEll::GetEllipseCenter()
{
	return m_EllipseCenter;
}

ObjPoint CMachineObjArcEll::GetArcStart()
{
	return GetEllipseArcPoint(m_ArcStartRadian);
}

ObjPoint CMachineObjArcEll::GetArcEnd()
{
	return GetEllipseArcPoint(m_ArcEndRadian);
}

ObjPoint CMachineObjArcEll::GetEllipseArcPoint(double Radian)
{
	ObjPoint point;
	point.x = m_EllipseCenter.x + m_EllipseXRadius * cos(Radian);
	point.y = m_EllipseCenter.y + m_EllipseXRadius * m_EllipseRatio * sin(Radian);
	return point;
}

double CMachineObjArcEll::GetEllipseXRadius()
{
	return m_EllipseXRadius;
}

double CMachineObjArcEll::GetEllipseRatio()
{
	return m_EllipseRatio;
}

double CMachineObjArcEll::GetEllipseYRadius()
{
	return m_EllipseXRadius*m_EllipseRatio;
}

double CMachineObjArcEll::GetStartRadian()
{
	return m_ArcStartRadian;
}

double CMachineObjArcEll::GetEndRadian()
{
	return m_ArcEndRadian;
}

ObjDir CMachineObjArcEll::GetArcDir()
{
	if (m_ArcEndRadian > m_ArcStartRadian)
		return CCW;
	else
		return CW;
}

double CMachineObjArcEll::CalDirAngle(double Radian)
{
	double dx = -m_EllipseXRadius * sin(Radian);
	double dy = m_EllipseXRadius * m_EllipseRatio * cos(Radian);
	if (GetArcDir() == CCW)
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

