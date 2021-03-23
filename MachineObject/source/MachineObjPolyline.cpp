// MachineObjPolyline.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineObjPolyline.h"

// CMachineObjPolyline 构造函数
CMachineObjPolyline::CMachineObjPolyline()
{
	m_ObjType = MachineObj_Type_Polyline;
	m_VertexCount = 0;
//	m_pVectorVPoint.swap(vector<ObjVPoint>(NULL));
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjPolyline::~CMachineObjPolyline()
{
//	m_pVectorVPoint.swap(vector<ObjVPoint>(NULL));
	m_pVectorVPoint.clear();
}
// 序列化
void CMachineObjPolyline::Serialize(CArchive& ar)
{
	ObjVPoint vpoint;
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_VertexCount;
		for (int i = 0; i < m_VertexCount; i++)
		{
			vpoint = m_pVectorVPoint[i];
			ar << vpoint.x << vpoint.y << vpoint.convexity;
		}
		ar << m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		m_ObjType = MachineObj_Type_Polyline;
		ar >> m_VertexCount;
		for (int i = 0; i < m_VertexCount; i++)
		{
			ar >> vpoint.x >> vpoint.y >> vpoint.convexity;
			m_pVectorVPoint.push_back(vpoint);
		}
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
	}
}

// CMachineObjPolyline 成员函数
// 私有函数
int CMachineObjPolyline::Quadrant(double x, double y)
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

void CMachineObjPolyline::ReSizeBound(ObjVPoint Vpoint)
{
	if (m_VertexCount == 1)		//以第一点坐标初始化Ployline外框
	{
		m_ObjBound.min_x = Vpoint.x;
		m_ObjBound.max_x = Vpoint.x;
		m_ObjBound.min_y = Vpoint.y;
		m_ObjBound.max_y = Vpoint.y;
		m_LastVpoint = Vpoint;
		return;
	}

	if (m_LastVpoint.convexity == 0)
	{
		if (m_ObjBound.max_x < Vpoint.x)
			m_ObjBound.max_x = Vpoint.x;
		if (m_ObjBound.max_y < Vpoint.y)
			m_ObjBound.max_y = Vpoint.y;
		if (m_ObjBound.min_x > Vpoint.x)
			m_ObjBound.min_x = Vpoint.x;
		if (m_ObjBound.min_y > Vpoint.y)
			m_ObjBound.min_y = Vpoint.y;
	}
	else
	{
		ObjPoint ArcStart, ArcEnd, ArcCenter;
		double x1, y1, x2, y2, ArcRadius, StartAngle, EndAngle;
		int qx1, qx2;
		ObjRect rect;
		ArcStart.x = m_LastVpoint.x;
		ArcStart.y = m_LastVpoint.y;
		ArcEnd.x = Vpoint.x;
		ArcEnd.y = Vpoint.y;
		TranPolylineToArc(ArcStart, ArcEnd, m_LastVpoint.convexity,
			&ArcCenter, &ArcRadius, &StartAngle, &EndAngle);
		x1 = ArcStart.x - ArcCenter.x;
		y1 = ArcStart.y - ArcCenter.y;
		x2 = ArcEnd.x - ArcCenter.x;
		y2 = ArcEnd.y - ArcCenter.y;
		qx1 = Quadrant(x1, y1);
		qx2 = Quadrant(x2, y2);
		if (EndAngle > StartAngle)
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}
				}
				else if (qx2 == 2)
				{
					rect.max_x = x1;
					rect.min_x = x2;
					rect.max_y = ArcRadius;
					rect.min_y = min(y1, y2);
				}
				else if (qx2 == 3)
				{
					rect.max_x = x1;
					rect.min_x = -ArcRadius;
					rect.max_y = ArcRadius;
					rect.min_y = y2;
				}
				else if (qx2 == 4)
				{
					rect.max_x = max(x1, x2);
					rect.min_x = -ArcRadius;
					rect.max_y = ArcRadius;
					rect.min_y = -ArcRadius;
				}

			}
			else if (qx1 == 2)
			{
				if (qx2 == 1)
				{
					rect.max_x = ArcRadius;
					rect.min_x = -ArcRadius;
					rect.max_y = max(y1, y2);
					rect.min_y = -ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}

				}
				else if (qx2 == 3)
				{
					rect.max_x = max(x1, x2);
					rect.min_x = -ArcRadius;
					rect.max_y = y1;
					rect.min_y = y2;
				}
				else if (qx2 == 4)
				{
					rect.max_x = x2;
					rect.min_x = -ArcRadius;
					rect.max_y = y1;
					rect.min_y = -ArcRadius;
				}
			}
			else if (qx1 == 3)
			{
				if (qx2 == 1)
				{
					rect.max_x = ArcRadius;
					rect.min_x = x1;
					rect.max_y = y2;
					rect.min_y = -ArcRadius;
				}
				else if (qx2 == 2)
				{
					rect.max_x = ArcRadius;
					rect.min_x = min(x1, x2);
					rect.max_y = ArcRadius;
					rect.min_y = -ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}
				}
				else if (qx2 == 4)
				{
					rect.max_x = x2;
					rect.min_x = x1;
					rect.max_y = max(y1, y2);
					rect.min_y = -ArcRadius;
				}
			}
			else if (qx1 == 4)
			{
				if (qx2 == 1)
				{
					rect.max_x = ArcRadius;
					rect.min_x = min(x1, x2);
					rect.max_y = y2;
					rect.min_y = y1;
				}
				else if (qx2 == 2)
				{
					rect.max_x = ArcRadius;
					rect.min_x = x2;
					rect.max_y = ArcRadius;
					rect.min_y = y1;
				}
				else if (qx2 == 3)
				{
					rect.max_x = ArcRadius;
					rect.min_x = -ArcRadius;
					rect.max_y = ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}
				}
				else if (qx2 == 2)
				{
					rect.max_x = ArcRadius;
					rect.min_x = -ArcRadius;
					rect.max_y = max(y1, y2);
					rect.min_y = -ArcRadius;
				}
				else if (qx2 == 3)
				{
					rect.max_x = ArcRadius;
					rect.min_x = x2;
					rect.max_y = y1;
					rect.min_y = -ArcRadius;
				}
				else if (qx2 == 4)
				{
					rect.max_x = ArcRadius;
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
					rect.max_y = ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}
				}
				else if (qx2 == 3)
				{
					rect.max_x = ArcRadius;
					rect.min_x = min(x1, x2);
					rect.max_y = ArcRadius;
					rect.min_y = -ArcRadius;
				}
				else if (qx2 == 4)
				{
					rect.max_x = ArcRadius;
					rect.min_x = x1;
					rect.max_y = ArcRadius;
					rect.min_y = y1;
				}
			}
			else if (qx1 == 3)
			{
				if (qx2 == 1)
				{
					rect.max_x = x2;
					rect.min_x = -ArcRadius;
					rect.max_y = ArcRadius;
					rect.min_y = y1;
				}
				else if (qx2 == 2)
				{
					rect.max_x = max(x1, x2);
					rect.min_x = -ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}
				}
				else if (qx2 == 4)
				{
					rect.max_x = ArcRadius;
					rect.min_x = -ArcRadius;
					rect.max_y = ArcRadius;
					rect.min_y = min(y1, y2);
				}
			}
			else if (qx1 == 4)
			{
				if (qx2 == 1)
				{
					rect.max_x = max(x1, x2);
					rect.min_x = -ArcRadius;
					rect.max_y = ArcRadius;
					rect.min_y = -ArcRadius;
				}
				else if (qx2 == 2)
				{
					rect.max_x = x1;
					rect.min_x = -ArcRadius;
					rect.max_y = y2;
					rect.min_y = -ArcRadius;
				}
				else if (qx2 == 3)
				{
					rect.max_x = x1;
					rect.min_x = x2;
					rect.max_y = max(y1, y2);
					rect.min_y = -ArcRadius;
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
						rect.max_x = ArcRadius;
						rect.min_x = -ArcRadius;
						rect.max_y = ArcRadius;
						rect.min_y = -ArcRadius;
					}
				}
			}
		}
		rect.max_x = rect.max_x + ArcCenter.x;
		rect.min_x = rect.min_x + ArcCenter.x;
		rect.max_y = rect.max_y + ArcCenter.y;
		rect.min_y = rect.min_y + ArcCenter.y;
		if (m_ObjBound.max_x < rect.max_x)
			m_ObjBound.max_x = rect.max_x;
		if (m_ObjBound.max_y < rect.max_y)
			m_ObjBound.max_y = rect.max_y;
		if (m_ObjBound.min_x > rect.min_x)
			m_ObjBound.min_x = rect.min_x;
		if (m_ObjBound.min_y > rect.min_y)
			m_ObjBound.min_y = rect.min_y;
	}
	m_LastVpoint = Vpoint;
}
	

// 公开函数
VectVpoint CMachineObjPolyline::GetPolylineVPointVect()
{
	return m_pVectorVPoint;
}

void CMachineObjPolyline::AddObjVpoint(ObjVPoint Vpoint)
{
	m_pVectorVPoint.push_back(Vpoint);
	m_VertexCount++;
	ReSizeBound(Vpoint);
}

void CMachineObjPolyline::ChangeLastVpoint(ObjVPoint Vpoint)
{
	m_pVectorVPoint.pop_back();
	m_pVectorVPoint.push_back(Vpoint);
	ReSizeBound(Vpoint);
}

int CMachineObjPolyline::GetPolylineVertexCount()
{
	return m_VertexCount;
}

void CMachineObjPolyline::MovePolylinePoint(ObjVPoint point, int count)
{
	double dx, dy;
	if (count < 0 || count >= m_VertexCount)
		return;
	dx = point.x - m_pVectorVPoint[count].x;
	dy = point.y - m_pVectorVPoint[count].y;
	for (int i = 0; i < m_VertexCount; i++)
	{
		m_pVectorVPoint[i].x = m_pVectorVPoint[i].x + dx;
		m_pVectorVPoint[i].y = m_pVectorVPoint[i].y + dy;
	}
	m_ObjBound.max_x += dx;
	m_ObjBound.min_x += dx;
	m_ObjBound.max_y += dy;
	m_ObjBound.min_y += dy;
}

void CMachineObjPolyline::MovePolylineStart(ObjPoint point)
{
	ObjVPoint vpoint = GetPolylineStart();
	vpoint.x = point.x;
	vpoint.y = point.y;
	MovePolylinePoint(vpoint, 0);
	return;
}

void CMachineObjPolyline::MovePolylineEnd(ObjPoint point)
{
	ObjVPoint vpoint = GetPolylineEnd();
	vpoint.x = point.x;
	vpoint.y = point.y;
	MovePolylinePoint(vpoint, m_VertexCount - 1);
	return;
}

void CMachineObjPolyline::MovePolyline(double X_shift, double Y_shift)
{
	for (int i = 0; i < m_VertexCount; i++)
	{
		m_pVectorVPoint[i].x += X_shift;
		m_pVectorVPoint[i].y += Y_shift;
	}
	m_ObjBound.max_x += X_shift;
	m_ObjBound.min_x += X_shift;
	m_ObjBound.max_y += Y_shift;
	m_ObjBound.min_y += Y_shift;
}

void CMachineObjPolyline::ExchangeStartAndEnd(CMachineObjPolyline* pObj)
{
	int Count;
	ObjVPoint vpoint;
	CMachineObjPolyline* pObj1;
	pObj1 = new CMachineObjPolyline;
	pObj1->m_VertexCount = pObj->m_VertexCount;
	Count = pObj->m_VertexCount;
	for (int i = 0; i < Count - 1; i++)
	{
		vpoint = pObj->m_pVectorVPoint[Count - 1 - i];
		vpoint.convexity = -pObj->m_pVectorVPoint[Count - 2 - i].convexity;
		pObj1->m_pVectorVPoint.push_back(vpoint);
	}
	vpoint = pObj->m_pVectorVPoint[0];
	vpoint.convexity = 0;
	pObj1->m_pVectorVPoint.push_back(vpoint);
	for (int i = 0; i < Count; i++)
	{
		pObj->m_pVectorVPoint[i] = pObj1->m_pVectorVPoint[i];
	}
	delete pObj1;
}

void CMachineObjPolyline::ModifyPolylineVpoint(ObjVPoint Vpoint, int Vertex_Num)
{
	if (Vertex_Num >= 0 && Vertex_Num < m_VertexCount)
	{
		VectVpoint pTemp;
		int nCount = m_VertexCount;
		m_VertexCount = 0;
		for (int i = 0; i < nCount; i++)
		{
			ObjVPoint vpoint = m_pVectorVPoint[i];
			if (Vertex_Num == i)
				vpoint = Vpoint;
			pTemp.push_back(vpoint);
			m_VertexCount++;
			ReSizeBound(vpoint);
		}
		m_pVectorVPoint = pTemp;
	}
}


ObjVPoint CMachineObjPolyline::GetPolylineStart()
{
	return m_pVectorVPoint[0];
}

ObjVPoint CMachineObjPolyline::GetPolylineEnd()
{
	return m_pVectorVPoint[m_VertexCount - 1];
}

ObjVPoint CMachineObjPolyline::GetPolylinePoint(int Num)
{
	return m_pVectorVPoint[Num];
}


BOOL CMachineObjPolyline::TranPolylineToArc(ObjPoint StartPoint, ObjPoint EndPoint, double Convexity,
	ObjPoint* ArcCenter, double* Radius, double* StartAngle, double* EndAngle)
{
	if (Convexity == 0)
		return FALSE;	//凸度为0,直线
	double Phi, Alpha;
	double x0, x, y0, y;
	double r, L1;
	x = (StartPoint.x - EndPoint.x) / 2;
	y = (StartPoint.y - EndPoint.y) / 2;
	Phi = 2 * atan(Convexity);
	r = sqrt(x * x + y * y) / sin(Phi);
	*Radius = abs(r);
	if (y == 0)
	{
		if (x > 0)
		{
			y0 = -r * cos(Phi);
			if (Convexity > 0)
				*StartAngle = 90 - 180 * Phi* M_1_PI;
			else
				*StartAngle = -90 - 180 * Phi* M_1_PI;
		}
		else
		{
			y0 = r * cos(Phi);
			if (Convexity < 0)
				*StartAngle = 90 - 180 * Phi* M_1_PI;
			else
				*StartAngle = -90 - 180 * Phi* M_1_PI;
		}
		*EndAngle = *StartAngle + 360 * Phi * M_1_PI;
		if (abs(*StartAngle) < 0.0000000000001)
			*StartAngle = 0;
		if (abs(*EndAngle) < 0.0000000000001)
			*EndAngle = 0;
		(*ArcCenter).x = (StartPoint.x + EndPoint.x) / 2;
		(*ArcCenter).y = y0 + (StartPoint.y + EndPoint.y) / 2;
	}
	// y!=0;
	else if (y < 0)
	{
		if (Convexity > 0)
		{
			Alpha = -atan(x / y);
			L1 = -r * cos(Phi);
			x0 = L1 * cos(Alpha);
			y0 = L1 * sin(Alpha);
			*StartAngle = 180 * (Alpha - Phi) * M_1_PI;
			*EndAngle = *StartAngle + 360 * Phi * M_1_PI;
			(*ArcCenter).x = x0 + (StartPoint.x + EndPoint.x) / 2;
			(*ArcCenter).y = y0 + (StartPoint.y + EndPoint.y) / 2;
		}
		else
		{
			Alpha = -atan(x / y);
			L1 = -r * cos(Phi);
			x0 = L1 * cos(Alpha);
			y0 = L1 * sin(Alpha);
			*StartAngle = -180 + 180 * (Alpha - Phi) * M_1_PI;
			*EndAngle = *StartAngle + 360 * Phi * M_1_PI;
			(*ArcCenter).x = x0 + (StartPoint.x + EndPoint.x) / 2;
			(*ArcCenter).y = y0 + (StartPoint.y + EndPoint.y) / 2;
		}
	}
	else
	{
		if (Convexity > 0)
		{
			Alpha = -atan(x / y);
			L1 = r * cos(Phi);
			x0 = L1 * cos(Alpha);
			y0 = L1 * sin(Alpha);
			*StartAngle = -180 + 180 * (Alpha - Phi) * M_1_PI;
			*EndAngle = *StartAngle + 360 * Phi * M_1_PI;
			(*ArcCenter).x = x0 + (StartPoint.x + EndPoint.x) / 2;
			(*ArcCenter).y = y0 + (StartPoint.y + EndPoint.y) / 2;
		}
		else
		{
			Alpha = -atan(x / y);
			L1 = r * cos(Phi);
			x0 = L1 * cos(Alpha);
			y0 = L1 * sin(Alpha);
			*StartAngle = 180 * (Alpha - Phi) * M_1_PI;
			*EndAngle = *StartAngle + 360 * Phi * M_1_PI;
			(*ArcCenter).x = x0 + (StartPoint.x + EndPoint.x) / 2;
			(*ArcCenter).y = y0 + (StartPoint.y + EndPoint.y) / 2;
		}
	}
	/*if ((*StartAngle < 0) && (*EndAngle < 0))
	{
		*StartAngle += 360;
		*EndAngle += 360;
	}
	else if ((*StartAngle >360) && (*EndAngle >360))
	{
		*StartAngle -= 360;
		*EndAngle -= 360;
	}*/
	return TRUE;
}

CMachineObjArc* CMachineObjPolyline::TranPolylineToArc(ObjPoint StartPoint, ObjPoint EndPoint,
	double Convexity, int nLayer)
{
	CMachineObjArc* pArc;
	ObjPoint pCenter;
	ObjDir dir;
	double radius, startAngle, endAngle;
	TranPolylineToArc(StartPoint, EndPoint, Convexity, &pCenter, &radius, &startAngle, &endAngle);
	if (endAngle > startAngle)
		dir = CCW;
	else
		dir = CW;
	pArc = new CMachineObjArc(pCenter, radius, startAngle, endAngle, nLayer, dir);
	return pArc;
}

void CMachineObjPolyline::ClosePolylineEndToStart()
{
	ObjVPoint vpoint1, vpoint2;
	vpoint1 = m_pVectorVPoint[m_VertexCount - 1];
	vpoint2 = m_pVectorVPoint[0];
	if (abs(vpoint1.x - vpoint2.x) < Zero && abs(vpoint1.y - vpoint2.y) < Zero)
	{
		m_pVectorVPoint[m_VertexCount - 1].x = m_pVectorVPoint[0].x;
		m_pVectorVPoint[m_VertexCount - 1].y = m_pVectorVPoint[0].y;
	}
	else
	{
		vpoint2.convexity = 0;
		AddObjVpoint(vpoint2);
	}
}

