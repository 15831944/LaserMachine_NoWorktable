// MachineObjTiltEllipse.cpp : 实现文件
//
#include "stdafx.h"
#include "MachineObjTiltEllipse.h"

// CMachineObjTiltEllipse 的构造函数
CMachineObjTiltEllipse::CMachineObjTiltEllipse()
{
	m_ObjType = MachineObj_Type_TiltEllipse;
	m_EllipseCenter = ObjPoint();
	m_LongAxisOffset = ObjPoint();
	m_EllipseRatio = 1;
	m_ArcStartRadian = 0;
	m_ArcEndRadian = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjTiltEllipse::CMachineObjTiltEllipse(
	ObjPoint EllipseCenter, ObjPoint LongAxisOffset, double EllipseRatio,
	double ArcStartRadian, double ArcEndRadian, int EllipseByLayer, ObjDir dir)
{
	m_ObjType = MachineObj_Type_TiltEllipse;
	m_EllipseCenter = EllipseCenter;
	m_LongAxisOffset = LongAxisOffset;
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

	m_ObjByLayer = EllipseByLayer;
	m_bIsObjStatus = IsObjNormal;
	ReSizeBound();
}

CMachineObjTiltEllipse::~CMachineObjTiltEllipse()
{
}

void CMachineObjTiltEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_EllipseCenter.x << m_EllipseCenter.y
			<< m_LongAxisOffset.x << m_LongAxisOffset.y
			<< m_EllipseRatio << m_ArcStartRadian << m_ArcEndRadian
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		m_ObjType = MachineObj_Type_TiltEllipse;
		ar >> m_EllipseCenter.x >> m_EllipseCenter.y
			>> m_LongAxisOffset.x >> m_LongAxisOffset.y
			>> m_EllipseRatio >> m_ArcStartRadian >> m_ArcEndRadian
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
	}
}

// CMachineObjEllipse 的成员函数
// 私有函数
void CMachineObjTiltEllipse::ReSizeBound()
{
	double a = GetTiltEllipseXRadius();
	double b = GetTiltEllipseYRadius();
	double theta, t3, t4;
	double u1, u2, u3, u4;
	theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	t3 = atan(-b * tan(theta) / a);
	t4 = M_PI + t3;
	u1 = a*cos(m_ArcStartRadian)*cos(theta) - b*sin(m_ArcStartRadian)*sin(theta);
	u2 = a*cos(m_ArcEndRadian)*cos(theta) - b*sin(m_ArcEndRadian)*sin(theta);
	u3 = u2;
	u4 = u2;
	if ((t3 > m_ArcStartRadian && t3 < m_ArcEndRadian) ||
		(t3>(m_ArcStartRadian + 2 * M_PI) && t3<(m_ArcEndRadian + 2 * M_PI)) ||
		(t3>(m_ArcStartRadian - 2 * M_PI) && t3 < (m_ArcEndRadian - 2 * M_PI)))
	{
		u3 = a*cos(t3)*cos(theta) - b*sin(t3)*sin(theta);
	}
	if ((t4 > m_ArcStartRadian && t4 < m_ArcEndRadian) ||
		(t4>(m_ArcStartRadian + 2 * M_PI) && t4<(m_ArcEndRadian + 2 * M_PI)) ||
		(t4>(m_ArcStartRadian - 2 * M_PI) && t4 < (m_ArcEndRadian - 2 * M_PI)))
	{
		u4 = a*cos(t4)*cos(theta) - b*sin(t4)*sin(theta);
	}
	m_ObjBound.min_x = u1;
	m_ObjBound.max_x = u1;
	if (m_ObjBound.min_x > u2)
		m_ObjBound.min_x = u2;
	if (m_ObjBound.max_x < u2)
		m_ObjBound.max_x = u2;
	if (m_ObjBound.min_x > u3)
		m_ObjBound.min_x = u3;
	if (m_ObjBound.max_x < u3)
		m_ObjBound.max_x = u3;
	if (m_ObjBound.min_x > u4)
		m_ObjBound.min_x = u4;
	if (m_ObjBound.max_x < u4)
		m_ObjBound.max_x = u4;

	t3 = atan(b / tan(theta) / a);
	t4 = M_PI + t3;
	u1 = b*sin(m_ArcStartRadian)*cos(theta) + a*cos(m_ArcStartRadian)*sin(theta);
	u2 = b*sin(m_ArcEndRadian)*cos(theta) + a*cos(m_ArcEndRadian)*sin(theta);
	u3 = u2;
	u4 = u2;
	if ((t3 > m_ArcStartRadian && t3 < m_ArcEndRadian) ||
		(t3>(m_ArcStartRadian + 2 * M_PI) && t3<(m_ArcEndRadian + 2 * M_PI)) ||
		(t3>(m_ArcStartRadian - 2 * M_PI) && t3 < (m_ArcEndRadian - 2 * M_PI)))
	{
		u3 = b*sin(t3)*cos(theta) + a*cos(t3)*sin(theta);
	}
	if ((t4 > m_ArcStartRadian && t4 < m_ArcEndRadian) ||
		(t4>(m_ArcStartRadian + 2 * M_PI) && t4<(m_ArcEndRadian + 2 * M_PI)) ||
		(t4>(m_ArcStartRadian - 2 * M_PI) && t4 < (m_ArcEndRadian - 2 * M_PI)))
	{
		u4 = b*sin(t4)*cos(theta) + a*cos(t4)*sin(theta);
	}
	m_ObjBound.min_y = u1;
	m_ObjBound.max_y = u1;
	if (m_ObjBound.min_y > u2)
		m_ObjBound.min_y = u2;
	if (m_ObjBound.max_y < u2)
		m_ObjBound.max_y = u2;
	if (m_ObjBound.min_y > u3)
		m_ObjBound.min_y = u3;
	if (m_ObjBound.max_y < u3)
		m_ObjBound.max_y = u3;
	if (m_ObjBound.min_y > u4)
		m_ObjBound.min_y = u4;
	if (m_ObjBound.max_y < u4)
		m_ObjBound.max_y = u4;
	m_ObjBound.min_x += m_EllipseCenter.x;
	m_ObjBound.max_x += m_EllipseCenter.x;
	m_ObjBound.min_y += m_EllipseCenter.y;
	m_ObjBound.max_y += m_EllipseCenter.y;
}

// 公开函数
void CMachineObjTiltEllipse::ExchangeStartAndEnd(CMachineObjTiltEllipse* pObj)
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

void CMachineObjTiltEllipse::MoveTiltEllipseCenter(ObjPoint point)
{
	m_EllipseCenter = point;
	ReSizeBound();
}

void CMachineObjTiltEllipse::MoveTiltEllipseStart(ObjPoint point)
{
	ObjPoint point1 = GetTiltEllipseStart();
	m_EllipseCenter.x = m_EllipseCenter.x + point.x - point1.x;
	m_EllipseCenter.y = m_EllipseCenter.y + point.y - point1.y;
	ReSizeBound();
}

void CMachineObjTiltEllipse::MoveTiltEllipseEnd(ObjPoint point)
{
	ObjPoint point1 = GetTiltEllipseEnd();
	m_EllipseCenter.x = m_EllipseCenter.x + point.x - point1.x;
	m_EllipseCenter.y = m_EllipseCenter.y + point.y - point1.y;
	ReSizeBound();
}

void CMachineObjTiltEllipse::MoveTileEllipse(double X_shift, double Y_shift)
{
	m_EllipseCenter.x += X_shift;
	m_EllipseCenter.y += Y_shift;
	ReSizeBound();
}

void CMachineObjTiltEllipse::SetTiltEllipseXRadius(double radius)
{
	double theta = GetRotateRadian();
	m_LongAxisOffset.x = radius * cos(theta);
	m_LongAxisOffset.y = radius * sin(theta);
	ReSizeBound();
}

void CMachineObjTiltEllipse::SetTiltEllipseRatio(double ratio)
{
	m_EllipseRatio = ratio;
	ReSizeBound();
}

void CMachineObjTiltEllipse::SetStartAndEndRadian(double radian1, double radian2, ObjDir dir)
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

void CMachineObjTiltEllipse::SetRotateRadian(double radian)
{
	double r = GetTiltEllipseXRadius();
	m_LongAxisOffset.x = r * cos(radian);
	m_LongAxisOffset.y = r * sin(radian);
	ReSizeBound();
}

ObjPoint CMachineObjTiltEllipse::GetTiltEllipseCenter()
{
	return m_EllipseCenter;
}

ObjPoint CMachineObjTiltEllipse::GetTiltEllipseStart()
{
	return GetTiltEllipsePoint(m_ArcStartRadian);
}

ObjPoint CMachineObjTiltEllipse::GetTiltEllipseEnd()
{
	return GetTiltEllipsePoint(m_ArcEndRadian);
}

ObjPoint CMachineObjTiltEllipse::GetTiltEllipsePoint(double radian)
{
	ObjPoint point;
	double a = GetTiltEllipseXRadius();
	double b = GetTiltEllipseYRadius();
	double theta;
	theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	point.x = m_EllipseCenter.x +
		a*cos(radian)*cos(theta) - b*sin(radian)*sin(theta);
	point.y = m_EllipseCenter.y +
		b*sin(radian)*cos(theta) + a*cos(radian)*sin(theta);
	return point;
}

double CMachineObjTiltEllipse::GetTiltEllipseXRadius()
{
	return sqrt(m_LongAxisOffset.x * m_LongAxisOffset.x
		+ m_LongAxisOffset.y * m_LongAxisOffset.y);
}

double CMachineObjTiltEllipse::GetTiltEllipseRatio()
{
	return m_EllipseRatio;
}

double CMachineObjTiltEllipse::GetTiltEllipseYRadius()
{
	return GetTiltEllipseXRadius() * m_EllipseRatio;
}

double CMachineObjTiltEllipse::GetRotateRadian()
{
	double theta;
	theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	return theta;
}

double CMachineObjTiltEllipse::GetStartRadian()
{
	return m_ArcStartRadian;
}

double CMachineObjTiltEllipse::GetEndRadian()
{
	return m_ArcEndRadian;
}

ObjDir CMachineObjTiltEllipse::GetArcDir()
{
	if (m_ArcEndRadian > m_ArcStartRadian)
		return CCW;
	else
		return CW;
}

double CMachineObjTiltEllipse::CalDirAngle(double Radian)
{
	double a = GetTiltEllipseXRadius();
	double b = GetTiltEllipseYRadius();
	double theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	double dx = -a*sin(Radian)*cos(theta) - b*cos(Radian)*sin(theta);
	double dy = b*cos(Radian)*cos(theta) - a*sin(Radian)*sin(theta);
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

double CMachineObjTiltEllipse::CalDistance(ObjPoint point)
{
	double Radian;
	if (point.x == m_EllipseCenter.x)
	{
		if (point.y >= m_EllipseCenter.y)
			Radian = M_PI_2;
		else
			Radian = M_PI + M_PI_2;
	}
	else
	{
		Radian = atan((point.y - m_EllipseCenter.y) / (point.x - m_EllipseCenter.x));
		if (point.x < m_EllipseCenter.x)
			Radian += M_PI;
	}
	if (Radian < 0)
		Radian += 2 * M_PI;
	double theta;
	theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	double a = GetTiltEllipseXRadius();
	double b = GetTiltEllipseYRadius();
	double k = tan(Radian - theta);
	double r = a*b*sqrt((1 + k*k) / (b*b + k*a*k*a));
	double d = sqrt((point.x - m_EllipseCenter.x)*(point.x - m_EllipseCenter.x)
		+ (point.y - m_EllipseCenter.y)*(point.y - m_EllipseCenter.y));
	return abs(d - r);
}

double CMachineObjTiltEllipse::CalAbsStartRadian()
{
	double theta;
	theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	if (theta < 0)
		theta = theta + 2 * M_PI;
	theta = GetStartRadian() + theta;
	if (theta > (2 * M_PI))
		theta -= 2 * M_PI;
	if (theta < 0)
		theta += 2 * M_PI;
	return theta;
}

double CMachineObjTiltEllipse::CalAbsEndRadian()
{
	double theta;
	theta = atan(m_LongAxisOffset.y / m_LongAxisOffset.x);	//仅对非正椭圆
	if (m_LongAxisOffset.y < 0)
		theta = theta + M_PI;
	if (theta < 0)
		theta = theta + 2 * M_PI;
	theta = GetEndRadian() + theta;
	if (theta >(2 * M_PI))
		theta -= 2 * M_PI;
	if (theta < 0)
		theta += 2 * M_PI;
	return theta;
}




