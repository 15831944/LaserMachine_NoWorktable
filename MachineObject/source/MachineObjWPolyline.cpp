// MachineObjWPolyline.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineObjWPolyline.h"

// MachineObjWArc 构造函数
CMachineObjWPolyline::CMachineObjWPolyline()
{
	m_ObjType = MachineObj_Type_WPolyline;
	m_VertexCount = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_Duplicate = 0;
	m_GapDistance = 0;
	m_pDupList.swap(vector<VectVpoint*>(NULL));
	m_ObjBound = ObjRect();
}

CMachineObjWPolyline::CMachineObjWPolyline(CMachineObjPolyline* pPolyline, int Duplicate, float GapDistance)
{
	m_ObjType = MachineObj_Type_WPolyline;
	m_VertexCount = pPolyline->GetPolylineVertexCount();
	m_pVectorVPoint = pPolyline->GetPolylineVPointVect();
	m_ObjByLayer = pPolyline->m_ObjByLayer;
	m_bIsObjStatus = pPolyline->m_bIsObjStatus;
	m_Duplicate = Duplicate;
	m_GapDistance = GapDistance;
	m_ObjBound = pPolyline->GetObjBound();
	ExtendWPolyline();
}

CMachineObjWPolyline::~CMachineObjWPolyline()
{
	VectVpoint* pVPolyline;
	int Count = m_pDupList.size();
	for (int i = 0; i < Count; i++)
	{
		pVPolyline = m_pDupList[i];
		delete pVPolyline;
	}
	m_pDupList.swap(vector<VectVpoint*>(NULL));
}

// 序列化
void CMachineObjWPolyline::Serialize(CArchive& ar)
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
		ar << m_Duplicate << m_GapDistance;
	}
	else
	{
		m_ObjType = MachineObj_Type_WPolyline;
		ar >> m_VertexCount;
		for (int i = 0; i < m_VertexCount; i++)
		{
			ar >> vpoint.x >> vpoint.y >> vpoint.convexity;
			m_pVectorVPoint.push_back(vpoint);
		}
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		ar >> m_Duplicate >> m_GapDistance;
		ExtendWPolyline();
		m_bIsObjStatus = IsObjNormal;
	}
}

 //MachineObjWArc 成员函数
 //私有函数

ObjVPoint CMachineObjWPolyline::CalCrossPoint(ObjVPoint VP_Last, ObjVPoint VP_Now, ObjVPoint VP_Next,
	double *Angle_Last, double *Convexity_Lsat, float Offset, 
	ObjVPoint *vpoint_last, VectVpoint* pList)
{
	ObjVPoint vpoint;
	ObjPoint point1, point2, point3;
	double K1, K2, radius, sangle, eangle;
	double delta, x0, y0, x1, y1, x2, y2, d1, d2;
	ObjDir dir;
	bool X_Priority;
	if ((VP_Last.convexity == 0) && (VP_Now.convexity == 0))
	{
		//Line-->Line
		if (VP_Now.x == VP_Last.x)
		{
			//lastline is vertical
			K2 = (VP_Next.y - VP_Now.y) / (VP_Next.x - VP_Now.x);
			if (VP_Now.y > VP_Last.y)
			{
				//lastline is upward
				vpoint.x = VP_Last.x + Offset;
				if (VP_Next.x > VP_Now.x)
					vpoint.y = VP_Now.y + (K2 - sqrt(1 + K2*K2))*Offset;	//nextline to the right
				else
					vpoint.y = VP_Now.y + (K2 + sqrt(1 + K2*K2))*Offset;	//nextline to the left
			}
			else
			{
				//lastline is downward
				vpoint.x = VP_Last.x - Offset;
				if (VP_Next.x > VP_Now.x)
					vpoint.y = VP_Now.y - (K2 + sqrt(1 + K2*K2))*Offset;	//nextline to the right
				else
					vpoint.y = VP_Now.y - (K2 - sqrt(1 + K2*K2))*Offset;	//nextline to the lest
			}
		}
		else if (VP_Next.x == VP_Now.x)
		{
			//nextline is vertical
			K1 = (VP_Now.y - VP_Last.y) / (VP_Now.x - VP_Last.x);
			if (VP_Next.y > VP_Now.y)
			{
				//nextline is upward
				vpoint.x = VP_Now.x + Offset;
				if (VP_Now.x > VP_Last.x)
					vpoint.y = VP_Now.y + (K1 - sqrt(1 + K1*K1))*Offset;
				else
					vpoint.y = VP_Now.y + (K1 + sqrt(1 + K1*K1))*Offset;
			}
			else
			{
				//nextline is downward
				vpoint.x = VP_Now.x - Offset;
				if (VP_Now.x > VP_Last.x)
					vpoint.y = VP_Now.y - (K1 + sqrt(1 + K1*K1))*Offset;
				else
					vpoint.y = VP_Now.y - (K1 - sqrt(1 + K1*K1))*Offset;
			}
		}
		else
		{
			//all line is not vertical
			K1 = (VP_Now.y - VP_Last.y) / (VP_Now.x - VP_Last.x);
			K2 = (VP_Next.y - VP_Now.y) / (VP_Next.x - VP_Now.x);
			if ((VP_Now.x > VP_Last.x) && (VP_Next.x > VP_Now.x))
			{
				vpoint.x = VP_Now.x + Offset*(sqrt(1 + K1*K1) - sqrt(1 + K2*K2)) / (K1 - K2);
				vpoint.y = VP_Now.y + Offset*(K2*sqrt(1 + K1*K1) - K1*sqrt(1 + K2*K2)) / (K1 - K2);
			}
			else if ((VP_Now.x > VP_Last.x) && (VP_Next.x < VP_Now.x))
			{
				vpoint.x = VP_Now.x + Offset*(sqrt(1 + K1*K1) + sqrt(1 + K2*K2)) / (K1 - K2);
				vpoint.y = VP_Now.y + Offset*(K2*sqrt(1 + K1*K1) + K1*sqrt(1 + K2*K2)) / (K1 - K2);
			}
			else if ((VP_Now.x <  VP_Last.x) && (VP_Next.x > VP_Now.x))
			{
				vpoint.x = VP_Now.x - Offset*(sqrt(1 + K1*K1) + sqrt(1 + K2*K2)) / (K1 - K2);
				vpoint.y = VP_Now.y - Offset*(K2*sqrt(1 + K1*K1) + K1*sqrt(1 + K2*K2)) / (K1 - K2);
			}
			else
			{
				vpoint.x = VP_Now.x - Offset*(sqrt(1 + K1*K1) - sqrt(1 + K2*K2)) / (K1 - K2);
				vpoint.y = VP_Now.y - Offset*(K2*sqrt(1 + K1*K1) - K1*sqrt(1 + K2*K2)) / (K1 - K2);
			}
			vpoint.convexity = 0;
		}
		*Angle_Last = 0;
		*Convexity_Lsat = 0;
	}
	else if ((VP_Last.convexity == 0) && (VP_Now.convexity != 0))
	{
		//Line-->Arc
		if (abs(VP_Now.x - VP_Last.x)<Zero)
		{
			//vertical line->Arc
			if (VP_Now.y > VP_Last.y)
			{
				//line is upward
				vpoint.x = VP_Last.x + Offset;
				point1.x = VP_Now.x;
				point1.y = VP_Now.y;
				point2.x = VP_Next.x;
				point2.y = VP_Next.y;
				TranPolylineToArc(point1, point2, VP_Now.convexity, &point3, &radius, &sangle, &eangle);
				if (eangle > sangle)
				{
					dir = CCW;
					radius = radius + Offset;
				}
				else
				{
					dir = CW;
					radius = radius - Offset;
				}
				delta = radius*radius - (vpoint.x - point3.x)*(vpoint.x - point3.x);
				if (abs(delta) < Zero)
				{
					//single point
					vpoint.y = point3.y;
					*Angle_Last = sangle;
					*Convexity_Lsat = 0;
				}
				else if (delta > 0)
				{
					//double point
					y1 = point3.y + sqrt(delta);
					y2 = point3.y - sqrt(delta);
					y0 = point3.y + radius* sin(2 * M_PI* sangle / 360);
					if (abs(abs(y1 - y0) - abs(y2 - y0)) > Zero)
					{
						if (abs(y1 - y0) < abs(y2 - y0))
							vpoint.y = y1;
						else
							vpoint.y = y2;
					}
					else
					{
						vpoint.y = y2;
					}
					delta = (vpoint.x - point3.x) / radius;
					if (delta < -1)
						delta = -1;
					else if (delta > 1)
						delta = 1;
					if (vpoint.y > point3.y)
						sangle = acos(delta) / M_PI * 180;
					else
						sangle = -acos(delta) / M_PI * 180;
					if ((dir == CW) && (eangle > sangle))
						sangle += 360;
					else if ((dir == CCW) && (eangle < sangle))
						sangle -= 360;
					if ((eangle - sangle)>360)
						sangle += 360;
					if (eangle - sangle < -360)
						sangle -= 360;
					*Angle_Last = sangle;
					*Convexity_Lsat = 0;
				}
				else
				{
					//no cross point,add a extra arc
					(*vpoint_last).convexity = 0;
					pList->push_back(*vpoint_last);
					vpoint.y = VP_Now.y;
					*vpoint_last = vpoint;
					vpoint.x = VP_Now.x - Offset;
					if (Offset > 0)
						*Convexity_Lsat = tan(M_PI / 4);
					else
						*Convexity_Lsat = tan(-M_PI / 4);

					*Angle_Last = sangle;
				}
			}
			else
			{
				//line is downward
				vpoint.x = VP_Last.x - Offset;
				point1.x = VP_Now.x;
				point1.y = VP_Now.y;
				point2.x = VP_Next.x;
				point2.y = VP_Next.y;
				TranPolylineToArc(point1, point2, VP_Now.convexity, &point3, &radius, &sangle, &eangle);
				if (eangle > sangle)
				{
					dir = CCW;
					radius = radius + Offset;
				}
				else
				{
					dir = CW;
					radius = radius - Offset;
				}
				delta = radius*radius - (vpoint.x - point3.x)*(vpoint.x - point3.x);
				if (abs(delta) < Zero)
				{
					//single point
					vpoint.y = point3.y;
					*Angle_Last = sangle;
					*Convexity_Lsat = 0;
				}
				else if (delta > 0)
				{
					//double point
					y1 = point3.y + sqrt(delta);
					y2 = point3.y - sqrt(delta);
					y0 = point3.y + radius* sin(2 * M_PI* sangle / 360);
					if (abs(abs(y1 - y0) - abs(y2 - y0)) > Zero)
					{
						if (abs(y1 - y0) < abs(y2 - y0))
							vpoint.y = y1;
						else
							vpoint.y = y2;
					}
					else
					{
						vpoint.y = y1;
					}
					delta = (vpoint.x - point3.x) / radius;
					if (delta < -1)
						delta = -1;
					else if (delta > 1)
						delta = 1;
					if (vpoint.y > point3.y)
						sangle = acos(delta) / M_PI * 180;
					else
						sangle = -acos(delta) / M_PI * 180;
					if ((dir == CW) && (eangle > sangle))
						sangle += 360;
					else if ((dir == CCW) && (eangle < sangle))
						sangle -= 360;
					if ((eangle - sangle)>360)
						sangle += 360;
					if (eangle - sangle < -360)
						sangle -= 360;
					*Angle_Last = sangle;
					*Convexity_Lsat = 0;
				}
				else
				{
					//no cross point,add a extra arc
					(*vpoint_last).convexity = 0;
					pList->push_back(*vpoint_last);
					vpoint.y = VP_Now.y;
					*vpoint_last = vpoint;
					vpoint.x = VP_Now.x + Offset;
					if (Offset > 0)
						*Convexity_Lsat = tan(M_PI / 4);
					else
						*Convexity_Lsat = tan(-M_PI / 4);
					*Angle_Last = sangle;
				}
			}
		}
		else
		{
			//normal line->Arc
			K1 = (VP_Now.y - VP_Last.y) / (VP_Now.x - VP_Last.x);
			X_Priority = true;
			if ((K1 != 0) && (abs(K1) > abs(1 / K1)))
			{
				K1 = (VP_Now.x - VP_Last.x) / (VP_Now.y - VP_Last.y);
				X_Priority = false;
			}
			point1.x = VP_Now.x;
			point1.y = VP_Now.y;
			point2.x = VP_Next.x;
			point2.y = VP_Next.y;
			TranPolylineToArc(point1, point2, VP_Now.convexity, &point3, &radius, &sangle, &eangle);
			if (eangle > sangle)
			{
				dir = CCW;
				radius = radius + Offset;
			}
			else
			{
				dir = CW;
				radius = radius - Offset;
			}
			if (X_Priority)
			{
				if (VP_Now.x > VP_Last.x)
					K2 = VP_Now.y - point3.y - K1*(VP_Now.x - point3.x) - sqrt(1 + K1*K1)*Offset;
				else
					K2 = VP_Now.y - point3.y - K1*(VP_Now.x - point3.x) + sqrt(1 + K1*K1)*Offset;
			}
			else
			{
				if (VP_Now.x > VP_Last.x)
					K2 = -(VP_Now.y - point3.y)*K1 + (VP_Now.x - point3.x) + sqrt(1 + K1*K1)*Offset;
				else
					K2 = -(VP_Now.y - point3.y)*K1 + (VP_Now.x - point3.x) - sqrt(1 + K1*K1)*Offset;
			}
			delta = (1 + K1*K1)*radius*radius - K2*K2;
			if (abs(delta) < Zero)
			{
				//single cross
				if (X_Priority)
				{
					vpoint.x = point3.x - K1*K2 / sqrt(1 + K1*K1);
					vpoint.y = point3.y + K1*(vpoint.x - point3.x) + K2;
				}
				else
				{
					vpoint.y = point3.y - K1*K2 / sqrt(1 + K1*K1);
					vpoint.x = point3.x + K1*(vpoint.x - point3.x) + K2;
				}
				*Angle_Last = sangle;
				*Convexity_Lsat = 0;
			}
			else if (delta>Zero)
			{
				//double cross point
				if (X_Priority)
				{
					x1 = point3.x + (-K1*K2 + sqrt(delta)) / sqrt(1 + K1*K1);
					y1 = point3.y + K1*(x1 - point3.x) + K2;
					x2 = point3.x + (-K1*K2 - sqrt(delta)) / sqrt(1 + K1*K1);
					y2 = point3.y + K1*(x2 - point3.x) + K2;
				}
				else
				{
					y1 = point3.y + (-K1*K2 + sqrt(delta)) / sqrt(1 + K1*K1);
					x1 = point3.x + K1*(y1 - point3.x) + K2;
					y2 = point3.y + (-K1*K2 - sqrt(delta)) / sqrt(1 + K1*K1);
					x2 = point3.x + K1*(y2 - point3.x) + K2;
				}
				x0 = point3.x + radius*cos(2 * M_PI* sangle / 360);
				y0 = point3.y + radius*sin(2 * M_PI* sangle / 360);
				d1 = sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
				d2 = sqrt((x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0));
				if (abs(d1 - d2) > Zero)
				{
					if (d1 < d2)
					{
						vpoint.x = x1;
						vpoint.y = y1;
					}
					else
					{
						vpoint.x = x2;
						vpoint.y = y2;
					}
				}
				else
				{
					///////////
					vpoint.x = x1;
					vpoint.y = y1;
				}
				delta = (vpoint.x - point3.x) / radius;
				if (delta < -1)
					delta = -1;
				else if (delta > 1)
					delta = 1;
				if (vpoint.y > point3.y)
					sangle = acos(delta) / M_PI * 180;
				else
					sangle = -acos(delta) / M_PI * 180;
				if ((dir == CW) && (eangle > sangle))
					sangle += 360;
				else if ((dir == CCW) && (eangle < sangle))
					sangle -= 360;
				if ((eangle - sangle)>360)
					sangle += 360;
				if (eangle - sangle < -360)
					sangle -= 360;
				*Angle_Last = sangle;
				*Convexity_Lsat = 0;
			}
			else
			{
				//no corss point//////////////////////////////////////////////
				int l = 0;
			}
		}
	}
	else if ((VP_Last.convexity != 0) && (VP_Now.convexity == 0))
	{
		//Arc-->Line
		if (abs(VP_Next.x - VP_Now.x)<Zero)
		{
			//Arc->vertical line
			if (VP_Next.y > VP_Now.y)
			{
				//line is upward
				vpoint.x = VP_Now.x + Offset;
				point1.x = VP_Last.x;
				point1.y = VP_Last.y;
				point2.x = VP_Now.x;
				point2.y = VP_Now.y;
				TranPolylineToArc(point1, point2, VP_Last.convexity, &point3, &radius, &sangle, &eangle);
				if (eangle > sangle)
				{
					dir = CCW;
					radius = radius + Offset;
				}
				else
				{
					dir = CW;
					radius = radius - Offset;
				}
				delta = radius*radius - (vpoint.x - point3.x)*(vpoint.x - point3.x);
				if (abs(delta) < Zero)
				{
					//single point
					vpoint.y = point3.y;
					*Convexity_Lsat = tan((eangle - *Angle_Last) * M_PI / 720);
					*Angle_Last = eangle;
				}
				else if (delta > 0)
				{
					//double point
					y1 = point3.y + sqrt(delta);
					y2 = point3.y - sqrt(delta);
					y0 = point3.y + radius* sin(2 * M_PI* eangle / 360);
					if (abs(abs(y1 - y0) - abs(y2 - y0)) > Zero)
					{
						if (abs(y1 - y0) < abs(y2 - y0))
							vpoint.y = y1;
						else
							vpoint.y = y2;
					}
					else
					{
						vpoint.y = y1;
					}
					delta = (vpoint.x - point3.x) / radius;
					if (delta < -1)
						delta = -1;
					else if (delta > 1)
						delta = 1;
					if (vpoint.y > point3.y)
						eangle = acos(delta) / M_PI * 180;
					else
						eangle = -acos(delta) / M_PI * 180;
					if ((dir == CW) && (eangle > *Angle_Last))
						eangle -= 360;
					else if ((dir == CCW) && (eangle < *Angle_Last))
						eangle += 360;
					if ((eangle - *Angle_Last)>360)
						eangle -= 360;
					if ((eangle - *Angle_Last) < -360)
						eangle += 360;
					*Convexity_Lsat = tan((eangle - *Angle_Last) * M_PI / 720);
					*Angle_Last = eangle;
				}
				else
				{
					//no cross point,add a extra arc
					eangle = 0;
					if (eangle > sangle)
						eangle -= 360;
					(*vpoint_last).convexity = tan((eangle - *Angle_Last)*M_PI / 720);
					pList->push_back(*vpoint_last);
					vpoint.x = VP_Now.x - Offset;
					vpoint.y = VP_Now.y;
					*vpoint_last = vpoint;
					vpoint.x = VP_Now.x + Offset;
					if (Offset > 0)
						*Convexity_Lsat = tan(M_PI / 4);
					else
						*Convexity_Lsat = tan(-M_PI / 4);
					*Angle_Last = eangle;
				}
			}
			else
			{
				//line is downward
				vpoint.x = VP_Now.x - Offset;
				point1.x = VP_Last.x;
				point1.y = VP_Last.y;
				point2.x = VP_Now.x;
				point2.y = VP_Now.y;
				TranPolylineToArc(point1, point2, VP_Last.convexity, &point3, &radius, &sangle, &eangle);
				if (eangle > sangle)
				{
					dir = CCW;
					radius = radius + Offset;
				}
				else
				{
					dir = CW;
					radius = radius - Offset;
				}
				delta = radius*radius - (vpoint.x - point3.x)*(vpoint.x - point3.x);
				if (abs(delta) < Zero)
				{
					//single point
					vpoint.y = point3.y;
					*Convexity_Lsat = tan((eangle - *Angle_Last) * M_PI / 720);
					*Angle_Last = eangle;
				}
				else if (delta > 0)
				{
					//double point
					y1 = point3.y + sqrt(delta);
					y2 = point3.y - sqrt(delta);
					y0 = point3.y + radius* sin(2 * M_PI* eangle / 360);
					if (abs(abs(y1 - y0) - abs(y2 - y0)) > Zero)
					{
						if (abs(y1 - y0) < abs(y2 - y0))
							vpoint.y = y1;
						else
							vpoint.y = y2;
					}
					else
					{
						vpoint.y = y2;
					}
					delta = (vpoint.x - point3.x) / radius;
					if (delta < -1)
						delta = -1;
					else if (delta > 1)
						delta = 1;
					if (vpoint.y > point3.y)
						eangle = acos(delta) / M_PI * 180;
					else
						eangle = -acos(delta) / M_PI * 180;
					if ((dir == CW) && (eangle > *Angle_Last))
						eangle -= 360;
					else if ((dir == CCW) && (eangle < *Angle_Last))
						eangle += 360;
					if ((eangle - *Angle_Last)>360)
						eangle -= 360;
					if ((eangle - *Angle_Last) < -360)
						eangle += 360;
					*Convexity_Lsat = tan((eangle - *Angle_Last) * M_PI / 720);
					*Angle_Last = eangle;
				}
				else
				{
					//no cross point,add a extra arc
					eangle = 180;
					if (eangle > sangle)
						eangle -= 360;
					(*vpoint_last).convexity = tan((eangle - *Angle_Last)*M_PI / 720);
					pList->push_back(*vpoint_last);
					vpoint.x = VP_Now.x + Offset;
					vpoint.y = VP_Now.y;
					*vpoint_last = vpoint;
					vpoint.x = VP_Now.x - Offset;
					if (Offset > 0)
						*Convexity_Lsat = tan(M_PI / 4);
					else
						*Convexity_Lsat = tan(-M_PI / 4);
					*Angle_Last = eangle;
				}
			}
		}
		else
		{
			//Arc->normal line
			K1 = (VP_Next.y - VP_Now.y) / (VP_Next.x - VP_Now.x);
			X_Priority = true;
			if ((K1 != 0) && (abs(K1) > abs(1 / K1)))
			{
				K1 = (VP_Next.x - VP_Now.x) / (VP_Next.y - VP_Now.y);
				X_Priority = false;
			}
			point1.x = VP_Last.x;
			point1.y = VP_Last.y;
			point2.x = VP_Now.x;
			point2.y = VP_Now.y;
			TranPolylineToArc(point1, point2, VP_Last.convexity, &point3, &radius, &sangle, &eangle);
			if (eangle > sangle)
			{
				dir = CCW;
				radius = radius + Offset;
			}
			else
			{
				dir = CW;
				radius = radius - Offset;
			}
			if (X_Priority)
			{
				if (VP_Next.x > VP_Now.x)
					K2 = VP_Now.y - point3.y - K1*(VP_Now.x - point3.x) - sqrt(1 + K1*K1)*Offset;
				else
					K2 = VP_Now.y - point3.y - K1*(VP_Now.x - point3.x) + sqrt(1 + K1*K1)*Offset;
			}
			else
			{
				if (VP_Next.x > VP_Now.x)
					K2 = -(VP_Now.y - point3.y)*K1 + (VP_Now.x - point3.x) + sqrt(1 + K1*K1)*Offset;
				else
					K2 = -(VP_Now.y - point3.y)*K1 + (VP_Now.x - point3.x) - sqrt(1 + K1*K1)*Offset;
			}
			delta = (1 + K1*K1)*radius*radius - K2*K2;
			if (abs(delta) < Zero)
			{
				//single cross
				if (X_Priority)
				{
					vpoint.x = point3.x - K1*K2 / sqrt(1 + K1*K1);
					vpoint.y = point3.y + K1*(vpoint.x - point3.x) + K2;
				}
				else
				{
					vpoint.y = point3.y - K1*K2 / sqrt(1 + K1*K1);
					vpoint.x = point3.x + K1*(vpoint.x - point3.x) + K2;
				}
				*Convexity_Lsat = tan((eangle - *Angle_Last) * M_PI / 720);
				*Angle_Last = eangle;
			}
			else if (delta>Zero)
			{
				//double cross point
				if (X_Priority)
				{
					x1 = point3.x + (-K1*K2 + sqrt(delta)) / sqrt(1 + K1*K1);
					y1 = point3.y + K1*(x1 - point3.x) + K2;
					x2 = point3.x + (-K1*K2 - sqrt(delta)) / sqrt(1 + K1*K1);
					y2 = point3.y + K1*(x2 - point3.x) + K2;
				}
				else
				{
					y1 = point3.y + (-K1*K2 + sqrt(delta)) / sqrt(1 + K1*K1);
					x1 = point3.x + K1*(y1 - point3.x) + K2;
					y2 = point3.y + (-K1*K2 - sqrt(delta)) / sqrt(1 + K1*K1);
					x2 = point3.x + K1*(y2 - point3.x) + K2;
				}
				x0 = point3.x + radius*cos(2 * M_PI* eangle / 360);
				y0 = point3.y + radius*sin(2 * M_PI* eangle / 360);
				d1 = sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0));
				d2 = sqrt((x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0));
				if (abs(d1 - d2) > Zero)
				{
					if (d1 < d2)
					{
						vpoint.x = x1;
						vpoint.y = y1;
					}
					else
					{
						vpoint.x = x2;
						vpoint.y = y2;
					}
				}
				else
				{
					///////////
					vpoint.x = x1;
					vpoint.y = y1;
				}
				delta = (vpoint.x - point3.x) / radius;
				if (delta < -1)
					delta = -1;
				else if (delta > 1)
					delta = 1;
				if (vpoint.y > point3.y)
					eangle = acos(delta) / M_PI * 180;
				else
					eangle = -acos(delta) / M_PI * 180;
				if ((dir == CW) && (eangle > *Angle_Last))
					eangle -= 360;
				else if ((dir == CCW) && (eangle < *Angle_Last))
					eangle += 360;
				if ((eangle - *Angle_Last)>360)
					eangle -= 360;
				if ((eangle - *Angle_Last) < -360)
					eangle += 360;
				*Convexity_Lsat = tan((eangle - *Angle_Last) * M_PI / 720);
				*Angle_Last = eangle;
			}
			else
			{
				//no corss point
				int l = 0;

			}
		}
	}
	else
	{
		//Arc-->Arc
		//
	}
	return vpoint;
}

void CMachineObjWPolyline::ExtendWPolyline()
{
	ObjVPoint vpoint, vpoint_last, Vpoint1, Vpoint2;
	ObjPoint point1, point2, point3;
	VectVpoint* pVPointList;
	ObjDir dir;
	double convexity, radius, sangle, eangle, secondangle, lastangle = 0;
	double K1, K2;
	for (int i = 1; i <= m_Duplicate; i++)
	{
   //****Right_ahead****Inside_CW****
		pVPointList = new VectVpoint;
		Vpoint1 = m_pVectorVPoint[0];
		Vpoint2 = m_pVectorVPoint[1];
		if (Vpoint1.convexity == 0)
		{
			//****Line****
			if (Vpoint2.x == Vpoint1.x)
			{	
				//Line is Vertical
				if (Vpoint2.y > Vpoint1.y)
				{
					//Up
					vpoint.x = Vpoint1.x + i*m_GapDistance;
					vpoint.y = Vpoint1.y;
				}
				else
				{
					//Down
					vpoint.x = Vpoint1.x - i*m_GapDistance;
					vpoint.y = Vpoint1.y;
				}
			}
			else
			{
				//line is not Vertical
				K1 = (Vpoint2.y - Vpoint1.y) / (Vpoint2.x - Vpoint1.x);
				K2 = 1 / sqrt(1 + K1*K1);
				K1 = K1*K2;
				if (Vpoint2.x > Vpoint1.x)
				{
					//line is to right
					vpoint.x = Vpoint1.x + i*K1*m_GapDistance;
					vpoint.y = Vpoint1.y - i*K2*m_GapDistance;
				}
				else
				{
					//line is to left
					vpoint.x = Vpoint1.x - i*K1*m_GapDistance;
					vpoint.y = Vpoint1.y + i*K2*m_GapDistance;
				}
			}
		}
		else
		{
			//****Arc****
			point1.x = Vpoint1.x;
			point1.y = Vpoint1.y;
			point2.x = Vpoint2.x;
			point2.y = Vpoint2.y;
			TranPolylineToArc(point1, point2, Vpoint1.convexity, &point3, &radius, &sangle, &eangle);
			if (eangle > sangle)
				dir = CCW;
			else
				dir = CW;
			if (dir == CW)
			{
				radius = radius - i*m_GapDistance;
				vpoint.x = point3.x + radius* cos(2 * M_PI* sangle / 360);
				vpoint.y = point3.y + radius* sin(2 * M_PI* sangle / 360);
			}
			else
			{
				radius = radius + i*m_GapDistance;
				vpoint.x = point3.x + radius* cos(2 * M_PI* sangle / 360);
				vpoint.y = point3.y + radius* sin(2 * M_PI* sangle / 360);
			}
			lastangle = sangle;
		}
		vpoint_last = vpoint;
	  //****first point End****
		for (int j = 1; j < m_VertexCount - 1; j++)
		{
			vpoint = CalCrossPoint(m_pVectorVPoint[j - 1], m_pVectorVPoint[j], m_pVectorVPoint[j + 1],
				&lastangle, &convexity, i*m_GapDistance, &vpoint_last, pVPointList);
			if (j == 1)
				secondangle = lastangle;
			vpoint_last.convexity = convexity;
			pVPointList->push_back(vpoint_last);
			vpoint_last = vpoint;
		}
	  //****mid poinr End
		Vpoint1 = m_pVectorVPoint[m_VertexCount - 2];
		Vpoint2 = m_pVectorVPoint[m_VertexCount - 1];
		vpoint = m_pVectorVPoint[0];
		if ((abs(vpoint.x - Vpoint2.x) < Zero) && (abs(vpoint.y - Vpoint2.y) < Zero))
		{
			vpoint = CalCrossPoint(Vpoint1, m_pVectorVPoint[0], m_pVectorVPoint[1], &lastangle, &convexity,
				i*m_GapDistance, &vpoint_last, pVPointList);
			vpoint_last.convexity = convexity;
			pVPointList->push_back(vpoint_last);
			vpoint.convexity = 0;
			pVPointList->push_back(vpoint);
			VectVpoint &pList = *pVPointList;
			pList[0].x = vpoint.x;
			pList[0].y = vpoint.y;
			if (pList[0].convexity != 0)
				pList[0].convexity = tan((secondangle - lastangle) * M_PI / 720);
		}
		else
		{
			if (Vpoint1.convexity == 0)
			{
				//****Line****
				if (Vpoint2.x == Vpoint1.x)
				{
					if (Vpoint2.y > Vpoint1.y)
					{
						vpoint.x = Vpoint2.x + i*m_GapDistance;
						vpoint.y = Vpoint2.y;
					}
					else
					{
						vpoint.x = Vpoint2.x - i*m_GapDistance;
						vpoint.y = Vpoint2.y;
					}
				}
				else
				{
					K1 = (Vpoint2.y - Vpoint1.y) / (Vpoint2.x - Vpoint1.x);
					K2 = 1 / sqrt(1 + K1*K1);
					K1 = K1*K2;
					if (Vpoint2.x > Vpoint1.x)
					{
						vpoint.x = Vpoint2.x + i*K1*m_GapDistance;
						vpoint.y = Vpoint2.y - i*K2*m_GapDistance;
					}
					else
					{
						vpoint.x = Vpoint2.x - i*K1*m_GapDistance;
						vpoint.y = Vpoint2.y + i*K2*m_GapDistance;
					}
				}
				vpoint_last.convexity = 0;
			}
			else
			{
				//****Arc****
				point1.x = Vpoint1.x;
				point1.y = Vpoint1.y;
				point2.x = Vpoint2.x;
				point2.y = Vpoint2.y;
				TranPolylineToArc(point1, point2, Vpoint1.convexity, &point3, &radius, &sangle, &eangle);
				if (eangle > sangle)
					dir = CCW;
				else
					dir = CW;
				if (dir == CW)
				{
					radius = radius - i*m_GapDistance;
					vpoint.x = point3.x + radius* cos(2 * M_PI* eangle / 360);
					vpoint.y = point3.y + radius* sin(2 * M_PI* eangle / 360);
				}
				else
				{
					radius = radius + i*m_GapDistance;
					vpoint.x = point3.x + radius* cos(2 * M_PI* eangle / 360);
					vpoint.y = point3.y + radius* sin(2 * M_PI* eangle / 360);
				}
				vpoint_last.convexity = tan((eangle - lastangle) * M_PI / 720);
			}
			pVPointList->push_back(vpoint_last);
			vpoint.convexity = 0;
			pVPointList->push_back(vpoint);
		}
		m_pDupList.push_back(pVPointList);
	  //****last point End****
   //****Right_ahead****Inside_CW End

   //****Left_ahead****Outside_CW****
		pVPointList = new VectVpoint;
		Vpoint1 = m_pVectorVPoint[0];
		Vpoint2 = m_pVectorVPoint[1];
		if (Vpoint1.convexity == 0)
		{
			//****Line****
			if (Vpoint2.x == Vpoint1.x)
			{
				//Line is Vertical
				if (Vpoint2.y > Vpoint1.y)
				{
					//Up
					vpoint.x = Vpoint1.x - i*m_GapDistance;
					vpoint.y = Vpoint1.y;
				}
				else
				{
					//Down
					vpoint.x = Vpoint1.x + i*m_GapDistance;
					vpoint.y = Vpoint1.y;
				}
			}
			else
			{
				//line is not Vertical
				K1 = (Vpoint2.y - Vpoint1.y) / (Vpoint2.x - Vpoint1.x);
				K2 = 1 / sqrt(1 + K1*K1);
				K1 = K1*K2;
				if (Vpoint2.x > Vpoint1.x)
				{
					//line is to right
					vpoint.x = Vpoint1.x - i*K1*m_GapDistance;
					vpoint.y = Vpoint1.y + i*K2*m_GapDistance;
				}
				else
				{
					//line is to left
					vpoint.x = Vpoint1.x + i*K1*m_GapDistance;
					vpoint.y = Vpoint1.y - i*K2*m_GapDistance;
				}
			}
		}
		else
		{
			//****Arc****
			point1.x = Vpoint1.x;
			point1.y = Vpoint1.y;
			point2.x = Vpoint2.x;
			point2.y = Vpoint2.y;
			TranPolylineToArc(point1, point2, Vpoint1.convexity, &point3, &radius, &sangle, &eangle);
			if (eangle > sangle)
				dir = CCW;
			else
				dir = CW;
			if (dir == CW)
			{
				radius = radius + i*m_GapDistance;
				vpoint.x = point3.x + radius* cos(2 * M_PI* sangle / 360);
				vpoint.y = point3.y + radius* sin(2 * M_PI* sangle / 360);
			}
			else
			{
				radius = radius - i*m_GapDistance;
				vpoint.x = point3.x + radius* cos(2 * M_PI* sangle / 360);
				vpoint.y = point3.y + radius* sin(2 * M_PI* sangle / 360);
			}
			lastangle = sangle;
		}
		vpoint_last = vpoint;
		//****first point End****
		for (int j = 1; j < m_VertexCount - 1; j++)
		{
			vpoint = CalCrossPoint(m_pVectorVPoint[j - 1], m_pVectorVPoint[j], m_pVectorVPoint[j + 1],
				&lastangle, &convexity, -i*m_GapDistance, &vpoint_last, pVPointList);
			if (j == 1)
				secondangle = lastangle;
			vpoint_last.convexity = convexity;
			pVPointList->push_back(vpoint_last);
			vpoint_last = vpoint;
		}
		//****mid poinr End
		Vpoint1 = m_pVectorVPoint[m_VertexCount - 2];
		Vpoint2 = m_pVectorVPoint[m_VertexCount - 1];
		vpoint = m_pVectorVPoint[0];
		if ((abs(vpoint.x - Vpoint2.x) < Zero) && (abs(vpoint.y - Vpoint2.y) < Zero))
		{
			vpoint = CalCrossPoint(Vpoint1, m_pVectorVPoint[0], m_pVectorVPoint[1], &lastangle, &convexity,
				-i*m_GapDistance, &vpoint_last, pVPointList);
			vpoint_last.convexity = convexity;
			pVPointList->push_back(vpoint_last);
			vpoint.convexity = 0;
			pVPointList->push_back(vpoint);
			VectVpoint &pList = *pVPointList;
			pList[0].x = vpoint.x;
			pList[0].y = vpoint.y;
			if (pList[0].convexity != 0)
				pList[0].convexity = tan((secondangle - lastangle) * M_PI / 720);
		}
		else
		{
			if (Vpoint1.convexity == 0)
			{
				//****Line****
				if (Vpoint2.x == Vpoint1.x)
				{
					if (Vpoint2.y > Vpoint1.y)
					{
						vpoint.x = Vpoint2.x - i*m_GapDistance;
						vpoint.y = Vpoint2.y;
					}
					else
					{
						vpoint.x = Vpoint2.x + i*m_GapDistance;
						vpoint.y = Vpoint2.y;
					}
				}
				else
				{
					K1 = (Vpoint2.y - Vpoint1.y) / (Vpoint2.x - Vpoint1.x);
					K2 = 1 / sqrt(1 + K1*K1);
					K1 = K1*K2;
					if (Vpoint2.x > Vpoint1.x)
					{
						vpoint.x = Vpoint2.x - i*K1*m_GapDistance;
						vpoint.y = Vpoint2.y + i*K2*m_GapDistance;
					}
					else
					{
						vpoint.x = Vpoint2.x + i*K1*m_GapDistance;
						vpoint.y = Vpoint2.y - i*K2*m_GapDistance;
					}
				}
				vpoint_last.convexity = 0;
			}
			else
			{
				//****Arc****
				point1.x = Vpoint1.x;
				point1.y = Vpoint1.y;
				point2.x = Vpoint2.x;
				point2.y = Vpoint2.y;
				TranPolylineToArc(point1, point2, Vpoint1.convexity, &point3, &radius, &sangle, &eangle);
				if (eangle > sangle)
					dir = CCW;
				else
					dir = CW;
				if (dir == CW)
				{
					radius = radius + i*m_GapDistance;
					vpoint.x = point3.x + radius* cos(2 * M_PI* eangle / 360);
					vpoint.y = point3.y + radius* sin(2 * M_PI* eangle / 360);
				}
				else
				{
					radius = radius - i*m_GapDistance;
					vpoint.x = point3.x + radius* cos(2 * M_PI* eangle / 360);
					vpoint.y = point3.y + radius* sin(2 * M_PI* eangle / 360);
				}
				vpoint_last.convexity = tan((eangle - lastangle) * M_PI / 720);
			}
			pVPointList->push_back(vpoint_last);
			vpoint.convexity = 0;
			pVPointList->push_back(vpoint);
		}
		m_pDupList.push_back(pVPointList);
		//****last point End****
	//****Left_ahead****Outside_CW End
	}
}

// 公开函数
CMachineObjPolyline* CMachineObjWPolyline::DegenerateToPolyline()
{
	int Count = m_pDupList.size();
	VectVpoint* pVPolyline;
	for (int i = 0; i < Count; i++)
	{
		pVPolyline = m_pDupList[i];
		delete pVPolyline;
	}
	m_pDupList.swap(vector<VectVpoint*>(NULL));
	CMachineObjPolyline *pPolyline = new CMachineObjPolyline();
//	Count = m_pVectorVPoint.size();
	Count = m_VertexCount;
	ObjVPoint vpoint;
	for (int i = 0; i < Count; i++)
	{
		vpoint = m_pVectorVPoint[i];
		pPolyline->AddObjVpoint(vpoint);
	}
	pPolyline->m_ObjByLayer = m_ObjByLayer;
	pPolyline->m_bIsObjStatus = m_bIsObjStatus;
	return pPolyline;
}

void CMachineObjWPolyline::MoveWPolyline(double X_shift, double Y_shift)
{
	MovePolyline(X_shift, Y_shift);
	int nCount1 = m_pDupList.size();
	for (int j = 0; j < nCount1; j++)
	{
		VectVpoint &Vpointlist = *m_pDupList[j];
		int Count = Vpointlist.size();
		for (int i = 0; i < Count; i++)
		{
			Vpointlist[i].x += X_shift;
			Vpointlist[i].y += Y_shift;
		}
	}
}

int CMachineObjWPolyline::GetDupNumber()
{
	return m_Duplicate;
}

float CMachineObjWPolyline::GetGapDistance()
{
	return m_GapDistance;
}

void CMachineObjWPolyline::SetDupNumber(int DupNumber)
{
	m_Duplicate = DupNumber;
	int Count = m_pDupList.size();
	VectVpoint* pVPolyline;
	for (int i = 0; i < Count; i++)
	{
		pVPolyline = m_pDupList[i];
		delete pVPolyline;
	}
	m_pDupList.swap(vector<VectVpoint*>(NULL));
	ExtendWPolyline();
}

void CMachineObjWPolyline::SetGapDistance(float GapDistance)
{
	m_GapDistance = GapDistance;
	int Count = m_pDupList.size();
	VectVpoint* pVPolyline;
	for (int i = 0; i < Count; i++)
	{
		pVPolyline = m_pDupList[i];
		delete pVPolyline;
	}
	m_pDupList.swap(vector<VectVpoint*>(NULL));
	ExtendWPolyline();
}

void CMachineObjWPolyline::ReCreatWPolyline(int DupNumber, float GapDistance)
{
	m_Duplicate = DupNumber;
	m_GapDistance = GapDistance;
	int Count = m_pDupList.size();

	VectVpoint* pVPolyline;
	for (int i = 0; i < Count; i++)
	{
		pVPolyline = m_pDupList[i];
		delete pVPolyline;
	}
	m_pDupList.swap(vector<VectVpoint*>(NULL));
	ExtendWPolyline();
}
