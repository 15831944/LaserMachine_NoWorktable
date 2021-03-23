// MachineObjArc.cpp : 实现文件
// 
#include "stdafx.h"
#include "MachineObjArc.h"

// CMachineObjArc 的构造函数
CMachineObjArc::CMachineObjArc()
{
	m_ObjType = MachineObj_Type_Arc;
	m_ArcCenter = ObjPoint();
	m_ArcRadius = 0;
	m_StartAngle = 0;
	m_EndAngle = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjArc::CMachineObjArc(ObjPoint ArcCenter, double ArcRadius,
	double StartAngle, double EndAngle, int ArcByLayer, ObjDir dir)
{
	m_ObjType = MachineObj_Type_Arc;
	m_ArcCenter = ArcCenter;
	m_ArcRadius = ArcRadius;
	m_StartAngle = StartAngle;
	if (dir == CCW)
	{
		if ((EndAngle - StartAngle) <= 0)
			m_EndAngle = EndAngle + 360;
		else
			m_EndAngle = EndAngle;
	}
	else
	{
		if ((EndAngle - StartAngle) > 0)
			m_EndAngle = EndAngle - 360;
		else
			m_EndAngle = EndAngle;
	}
	if (m_StartAngle >= 360 || m_EndAngle >= 360)
	{
		m_StartAngle -= 360;
		m_EndAngle -= 360;
	}
	else if (m_StartAngle < -360 || m_EndAngle < -360)
	{
		m_StartAngle += 360;
		m_EndAngle += 360;
	}
	if (m_StartAngle < 0 && m_EndAngle < 0)
	{
		m_StartAngle += 360;
		m_EndAngle += 360;
	}
	m_ObjByLayer = ArcByLayer;
	m_bIsObjStatus = IsObjNormal;
	ReSizeBound();
}

CMachineObjArc::~CMachineObjArc()
{
}
// 序列化
void CMachineObjArc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_ArcCenter.x << m_ArcCenter.y
			<< m_ArcRadius << m_StartAngle << m_EndAngle
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		m_ObjType = MachineObj_Type_Arc;
		ar >> m_ArcCenter.x >> m_ArcCenter.y
			>> m_ArcRadius >> m_StartAngle >> m_EndAngle
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
	}
}


// CMachineObjArc 的成员函数
// 私有函数
int CMachineObjArc::Quadrant(double x, double y)
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

void CMachineObjArc::ReSizeBound()
{
	double x1, y1, x2, y2;
	int qx1, qx2;
	ObjRect rect;
	ObjPoint m_ArcStart, m_ArcEnd;
	m_ArcStart = GetArcStart();
	m_ArcEnd = GetArcEnd();
	x1 = m_ArcStart.x - m_ArcCenter.x;
	y1 = m_ArcStart.y - m_ArcCenter.y;
	x2 = m_ArcEnd.x - m_ArcCenter.x;
	y2 = m_ArcEnd.y - m_ArcCenter.y;
	qx1 = Quadrant(x1, y1);
	qx2 = Quadrant(x2, y2);
	if (m_EndAngle > m_StartAngle)
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
			else if (qx2 == 2)
			{
				rect.max_x = x1;
				rect.min_x = x2;
				rect.max_y = m_ArcRadius;
				rect.min_y = min(y1, y2);
			}
			else if (qx2 == 3)
			{
				rect.max_x = x1;
				rect.min_x = -m_ArcRadius;
				rect.max_y = m_ArcRadius;
				rect.min_y = y2;
			}
			else if (qx2 == 4)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -m_ArcRadius;
				rect.max_y = m_ArcRadius;
				rect.min_y = -m_ArcRadius;
			}

		}
		else if (qx1 == 2)
		{
			if (qx2 == 1)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = -m_ArcRadius;
				rect.max_y = max(y1, y2);
				rect.min_y = -m_ArcRadius;
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}

			}
			else if (qx2 == 3)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -m_ArcRadius;
				rect.max_y = y1;
				rect.min_y = y2;
			}
			else if (qx2 == 4)
			{
				rect.max_x = x2;
				rect.min_x = -m_ArcRadius;
				rect.max_y = y1;
				rect.min_y = -m_ArcRadius;
			}
		}
		else if (qx1 == 3)
		{
			if (qx2 == 1)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = x1;
				rect.max_y = y2;
				rect.min_y = -m_ArcRadius;
			}
			else if (qx2 == 2)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = min(x1, x2);
				rect.max_y = m_ArcRadius;
				rect.min_y = -m_ArcRadius;
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
			else if (qx2 == 4)
			{
				rect.max_x = x2;
				rect.min_x = x1;
				rect.max_y = max(y1, y2);
				rect.min_y = -m_ArcRadius;
			}
		}
		else if (qx1 == 4)
		{
			if (qx2 == 1)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = min(x1, x2);
				rect.max_y = y2;
				rect.min_y = y1;
			}
			else if (qx2 == 2)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = x2;
				rect.max_y = m_ArcRadius;
				rect.min_y = y1;
			}
			else if (qx2 == 3)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = -m_ArcRadius;
				rect.max_y = m_ArcRadius;
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
		}
	}
	else
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
			else if (qx2 == 2)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = -m_ArcRadius;
				rect.max_y = max(y1, y2);
				rect.min_y = -m_ArcRadius;
			}
			else if (qx2 == 3)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = x2;
				rect.max_y = y1;
				rect.min_y = -m_ArcRadius;
			}
			else if (qx2 == 4)
			{
				rect.max_x = m_ArcRadius;
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
				rect.max_y = m_ArcRadius;
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
			else if (qx2 == 3)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = min(x1, x2);
				rect.max_y = m_ArcRadius;
				rect.min_y = -m_ArcRadius;
			}
			else if (qx2 == 4)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = x1;
				rect.max_y = m_ArcRadius;
				rect.min_y = y1;
			}
		}
		else if (qx1 == 3)
		{
			if (qx2 == 1)
			{
				rect.max_x = x2;
				rect.min_x = -m_ArcRadius;
				rect.max_y = m_ArcRadius;
				rect.min_y = y1;
			}
			else if (qx2 == 2)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -m_ArcRadius;
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
			else if (qx2 == 4)
			{
				rect.max_x = m_ArcRadius;
				rect.min_x = -m_ArcRadius;
				rect.max_y = m_ArcRadius;
				rect.min_y = min(y1, y2);
			}
		}
		else if (qx1 == 4)
		{
			if (qx2 == 1)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -m_ArcRadius;
				rect.max_y = m_ArcRadius;
				rect.min_y = -m_ArcRadius;
			}
			else if (qx2 == 2)
			{
				rect.max_x = x1;
				rect.min_x = -m_ArcRadius;
				rect.max_y = y2;
				rect.min_y = -m_ArcRadius;
			}
			else if (qx2 == 3)
			{
				rect.max_x = x1;
				rect.min_x = x2;
				rect.max_y = max(y1, y2);
				rect.min_y = -m_ArcRadius;
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
					rect.max_x = m_ArcRadius;
					rect.min_x = -m_ArcRadius;
					rect.max_y = m_ArcRadius;
					rect.min_y = -m_ArcRadius;
				}
			}
		}
	}
	m_ObjBound.max_x = rect.max_x + m_ArcCenter.x;
	m_ObjBound.min_x = rect.min_x + m_ArcCenter.x;
	m_ObjBound.max_y = rect.max_y + m_ArcCenter.y;
	m_ObjBound.min_y = rect.min_y + m_ArcCenter.y;
}

// 公开函数
void CMachineObjArc::MoveArcCenter(ObjPoint point)
{
	m_ArcCenter = point;
	ReSizeBound();
}

void CMachineObjArc::MoveArcStart(ObjPoint point)
{
	ObjPoint point1 = GetArcStart();
	m_ArcCenter.x = m_ArcCenter.x + point.x - point1.x;
	m_ArcCenter.y = m_ArcCenter.y + point.y - point1.y;
	ReSizeBound();
}

void CMachineObjArc::MoveArcEnd(ObjPoint point)
{
	ObjPoint point1 = GetArcEnd();
	m_ArcCenter.x = m_ArcCenter.x + point.x - point1.x;
	m_ArcCenter.y = m_ArcCenter.y + point.y - point1.y;
	ReSizeBound();
}

void CMachineObjArc::MoveArc(double X_shift, double Y_shift)
{
	m_ArcCenter.x += X_shift;
	m_ArcCenter.y += Y_shift;
	ReSizeBound();
}

void CMachineObjArc::SetArcRadius(double radius)
{
	m_ArcRadius = radius;
	ReSizeBound();
}

void CMachineObjArc::SetStartAndEndAngle(double angle1, double angle2, ObjDir dir)
{
	m_StartAngle = angle1;
	if (dir == CCW)
	{
		if ((angle2 - angle1) <= 0)
			m_EndAngle = angle2 + 360;
		else
			m_EndAngle = angle2;
	}
	else
	{
		if ((angle2 - angle1) > 0)
			m_EndAngle = angle2 - 360;
		else
			m_EndAngle = angle2;
	}
	if (m_StartAngle >= 360 || m_EndAngle >= 360)
	{
		m_StartAngle -= 360;
		m_EndAngle -= 360;
	}
	else if (m_StartAngle < -360 || m_EndAngle < -360)
	{
		m_StartAngle += 360;
		m_EndAngle += 360;
	}
	if (m_StartAngle < 0 && m_EndAngle < 0)
	{
		m_StartAngle += 360;
		m_EndAngle += 360;
	}
	ReSizeBound();
}

void CMachineObjArc::ExchangeStartAndEnd(CMachineObjArc* pObj)
{
	double StartAngle, EndAngle;
	ObjDir dir;
	if (GetArcDir() == CW)
		dir = CCW;
	else
		dir = CW;
	StartAngle = m_EndAngle;
	EndAngle = m_StartAngle;
	m_StartAngle = StartAngle;
	if (dir == CCW)
	{
		if ((EndAngle - StartAngle) <= 0)
			m_EndAngle = EndAngle + 360;
		else
			m_EndAngle = EndAngle;
	}
	else
	{
		if ((EndAngle - StartAngle) > 0)
			m_EndAngle = EndAngle - 360;
		else
			m_EndAngle = EndAngle;
	}
	if (m_StartAngle >= 360 || m_EndAngle >= 360)
	{
		m_StartAngle -= 360;
		m_EndAngle -= 360;
	}
	else if (m_StartAngle < -360 || m_EndAngle < -360)
	{
		m_StartAngle += 360;
		m_EndAngle += 360;
	}
}

ObjPoint CMachineObjArc::GetArcCenter()
{
	return m_ArcCenter;
}

ObjPoint CMachineObjArc::GetArcStart()
{
	double x, y;
	ObjPoint point;
	x = m_ArcRadius* cos(2 * M_PI* m_StartAngle / 360);
	y = m_ArcRadius* sin(2 * M_PI* m_StartAngle / 360);
	point.x = m_ArcCenter.x + x;
	point.y = m_ArcCenter.y + y;
	return point;
}

ObjPoint CMachineObjArc::GetArcEnd()
{
	double x, y;
	ObjPoint point;
	x = m_ArcRadius* cos(2 * M_PI* m_EndAngle / 360);
	y = m_ArcRadius* sin(2 * M_PI* m_EndAngle / 360);
	point.x = m_ArcCenter.x + x;
	point.y = m_ArcCenter.y + y;
	return point;
}

double CMachineObjArc::GetStartAngle()
{
	return m_StartAngle;
}

double CMachineObjArc::GetEndAngle()
{
	return m_EndAngle;
}

ObjPoint CMachineObjArc::GetArcPoint(double Angle)
{
	ObjPoint point;
	point.x = m_ArcCenter.x + m_ArcRadius*cos(M_PI* Angle / 180);
	point.y = m_ArcCenter.y + m_ArcRadius*sin(M_PI* Angle / 180);
	return point;
}

double CMachineObjArc::GetArcRadius()
{
	return m_ArcRadius;
}

ObjDir CMachineObjArc::GetArcDir()
{
	if ((m_EndAngle - m_StartAngle) > 0)
		return CCW;
	else
		return CW;
}

double CMachineObjArc::CalDirAngle(double Angle)
{
	double dx = -m_ArcRadius * sin(M_PI * Angle / 180);
	double dy = m_ArcRadius * cos(M_PI * Angle / 180);
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




