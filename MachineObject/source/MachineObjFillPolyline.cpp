// MachineObjFillPolyline.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineObjFillPolyline.h"

// CMachineObjPolyline 构造函数
CMachineObjFillPolyline::CMachineObjFillPolyline()
{
	m_ObjType = MachineObj_Type_FillPolyline;
	m_VertexCount = 0;
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_OutlinePrior = 0;
	m_FillPara[0] = FillPara();
	m_FillPara[1] = FillPara();
	m_FillPara[2] = FillPara();
	m_FillPara[3] = FillPara();
	m_ObjBound = ObjRect();
}

CMachineObjFillPolyline::CMachineObjFillPolyline(CMachineObjPolyline* pPolyline, byte OutlinePrior,
	FillPara FillPara1, FillPara FillPara2, FillPara FillPara3, FillPara FillPara4)
{
	m_ObjType = MachineObj_Type_FillPolyline;
	m_VertexCount = pPolyline->GetPolylineVertexCount();
	m_pVectorVPoint = pPolyline->GetPolylineVPointVect();
	m_ObjByLayer = pPolyline->m_ObjByLayer;
	m_bIsObjStatus = pPolyline->m_bIsObjStatus;
	m_OutlinePrior = OutlinePrior;
	m_FillPara[0] = FillPara1;
	m_FillPara[1] = FillPara2;
	m_FillPara[2] = FillPara3;
	m_FillPara[3] = FillPara4;
	m_ObjBound = pPolyline->GetObjBound();
	FillPolyline();

}

CMachineObjFillPolyline::~CMachineObjFillPolyline()
{
//	m_pVectorVPoint.swap(vector<ObjVPoint>(NULL));
}
// 序列化
void CMachineObjFillPolyline::Serialize(CArchive& ar)
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
		ar << m_OutlinePrior;
		for (int i = 0; i < 4; i++)
		{
			ar << m_FillPara[i].Curtail << m_FillPara[i].FillAngle
				<< m_FillPara[i].FillGap << m_FillPara[i].FillMode
				<< m_FillPara[i].GapMode << m_FillPara[i].IsEnable;
		}
	}
	else
	{
		m_ObjType = MachineObj_Type_FillPolyline;
		ar >> m_VertexCount;
		for (int i = 0; i < m_VertexCount; i++)
		{
			ar >> vpoint.x >> vpoint.y >> vpoint.convexity;
			m_pVectorVPoint.push_back(vpoint);
		}
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
		ar >> m_OutlinePrior;
		for (int i = 0; i < 4; i++)
		{
			ar >> m_FillPara[i].Curtail >> m_FillPara[i].FillAngle
				>> m_FillPara[i].FillGap >> m_FillPara[i].FillMode
				>> m_FillPara[i].GapMode >> m_FillPara[i].IsEnable;
		}
		FillPolyline();
	}
}

// CMachineObjPolyline 成员函数
// 私有函数

int CMachineObjFillPolyline::Quadrant(double x, double y)
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

ObjRect CMachineObjFillPolyline::SizeBound(ObjEdge* pEdge)
{
	ObjRect rect;
	if (pEdge->StartOrCircle.x > pEdge->EndOrRadian.x)
	{
		rect.max_x = pEdge->StartOrCircle.x;
		rect.min_x = pEdge->EndOrRadian.x;
	}
	else
	{
		rect.min_x = pEdge->StartOrCircle.x;
		rect.max_x = pEdge->EndOrRadian.x;
	}
	if (pEdge->StartOrCircle.y > pEdge->EndOrRadian.y)
	{
		rect.max_y = pEdge->StartOrCircle.y;
		rect.min_y = pEdge->EndOrRadian.y;
	}
	else
	{
		rect.min_y = pEdge->StartOrCircle.y;
		rect.max_y = pEdge->EndOrRadian.y;
	}
	return rect;
}

ObjRect CMachineObjFillPolyline::SizeBound(ObjEdge* pEdge, ObjPoint point1, ObjPoint point2)
{
	ObjRect rect;
	double x1, y1, x2, y2;
	int qx1, qx2;
	x1 = point1.x - pEdge->StartOrCircle.x;
	y1 = point1.y - pEdge->StartOrCircle.y;
	x2 = point2.x - pEdge->StartOrCircle.x;
	y2 = point2.y - pEdge->StartOrCircle.y;
	qx1 = Quadrant(x1, y1);
	qx2 = Quadrant(x2, y2);
	if (pEdge->EndOrRadian.y > pEdge->EndOrRadian.x)
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}
			}
			else if (qx2 == 2)
			{
				rect.max_x = x1;
				rect.min_x = x2;
				rect.max_y = pEdge->radius;
				rect.min_y = min(y1, y2);
			}
			else if (qx2 == 3)
			{
				rect.max_x = x1;
				rect.min_x = -pEdge->radius;
				rect.max_y = pEdge->radius;
				rect.min_y = y2;
			}
			else if (qx2 == 4)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -pEdge->radius;
				rect.max_y = pEdge->radius;
				rect.min_y = -pEdge->radius;
			}

		}
		else if (qx1 == 2)
		{
			if (qx2 == 1)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = -pEdge->radius;
				rect.max_y = max(y1, y2);
				rect.min_y = -pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}

			}
			else if (qx2 == 3)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -pEdge->radius;
				rect.max_y = y1;
				rect.min_y = y2;
			}
			else if (qx2 == 4)
			{
				rect.max_x = x2;
				rect.min_x = -pEdge->radius;
				rect.max_y = y1;
				rect.min_y = -pEdge->radius;
			}
		}
		else if (qx1 == 3)
		{
			if (qx2 == 1)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = x1;
				rect.max_y = y2;
				rect.min_y = -pEdge->radius;
			}
			else if (qx2 == 2)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = min(x1, x2);
				rect.max_y = pEdge->radius;
				rect.min_y = -pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}
			}
			else if (qx2 == 4)
			{
				rect.max_x = x2;
				rect.min_x = x1;
				rect.max_y = max(y1, y2);
				rect.min_y = -pEdge->radius;
			}
		}
		else if (qx1 == 4)
		{
			if (qx2 == 1)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = min(x1, x2);
				rect.max_y = y2;
				rect.min_y = y1;
			}
			else if (qx2 == 2)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = x2;
				rect.max_y = pEdge->radius;
				rect.min_y = y1;
			}
			else if (qx2 == 3)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = -pEdge->radius;
				rect.max_y = pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}
			}
			else if (qx2 == 2)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = -pEdge->radius;
				rect.max_y = max(y1, y2);
				rect.min_y = -pEdge->radius;
			}
			else if (qx2 == 3)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = x2;
				rect.max_y = y1;
				rect.min_y = -pEdge->radius;
			}
			else if (qx2 == 4)
			{
				rect.max_x = pEdge->radius;
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
				rect.max_y = pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}
			}
			else if (qx2 == 3)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = min(x1, x2);
				rect.max_y = pEdge->radius;
				rect.min_y = -pEdge->radius;
			}
			else if (qx2 == 4)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = x1;
				rect.max_y = pEdge->radius;
				rect.min_y = y1;
			}
		}
		else if (qx1 == 3)
		{
			if (qx2 == 1)
			{
				rect.max_x = x2;
				rect.min_x = -pEdge->radius;
				rect.max_y = pEdge->radius;
				rect.min_y = y1;
			}
			else if (qx2 == 2)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}
			}
			else if (qx2 == 4)
			{
				rect.max_x = pEdge->radius;
				rect.min_x = -pEdge->radius;
				rect.max_y = pEdge->radius;
				rect.min_y = min(y1, y2);
			}
		}
		else if (qx1 == 4)
		{
			if (qx2 == 1)
			{
				rect.max_x = max(x1, x2);
				rect.min_x = -pEdge->radius;
				rect.max_y = pEdge->radius;
				rect.min_y = -pEdge->radius;
			}
			else if (qx2 == 2)
			{
				rect.max_x = x1;
				rect.min_x = -pEdge->radius;
				rect.max_y = y2;
				rect.min_y = -pEdge->radius;
			}
			else if (qx2 == 3)
			{
				rect.max_x = x1;
				rect.min_x = x2;
				rect.max_y = max(y1, y2);
				rect.min_y = -pEdge->radius;
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
					rect.max_x = pEdge->radius;
					rect.min_x = -pEdge->radius;
					rect.max_y = pEdge->radius;
					rect.min_y = -pEdge->radius;
				}
			}
		}
	}
	rect.max_x = rect.max_x + pEdge->StartOrCircle.x;
	rect.min_x = rect.min_x + pEdge->StartOrCircle.x;
	rect.max_y = rect.max_y + pEdge->StartOrCircle.y;
	rect.min_y = rect.min_y + pEdge->StartOrCircle.y;
	return rect;
}

ObjEdgeList CMachineObjFillPolyline::CreatEdgelist(double *Ymax, double *Ymin,
	double SinRotate, double CosRotate)
{
	ObjEdgeList edgelist;
	ObjEdge *pEdge;
	ObjPoint point1, point2, point3;
	double convexity, radius, sangle, eangle;
	if ((SinRotate == 0) && (CosRotate == 1))
	{
		point1.x = m_pVectorVPoint[0].x;
		point1.y = m_pVectorVPoint[0].y;
		convexity = m_pVectorVPoint[0].convexity;
		*Ymax = point1.y;
		*Ymin = point1.y;
		for (int i = 1; i < m_VertexCount; i++)
		{
			point2.x = m_pVectorVPoint[i].x;
			point2.y = m_pVectorVPoint[i].y;
			pEdge = new ObjEdge();
			if (convexity == 0)
			{
				pEdge->StartOrCircle = point1;
				pEdge->EndOrRadian = point2;
				pEdge->radius = 0;
				pEdge->bound = SizeBound(pEdge);
			}
			else
			{
				TranPolylineToArc(point1, point2, convexity,
					&point3, &radius, &sangle, &eangle);
				pEdge->StartOrCircle = point3;
				pEdge->EndOrRadian.x = M_PI*sangle / 180;
				pEdge->EndOrRadian.y = M_PI*eangle / 180;
				pEdge->radius = radius;
				pEdge->bound = SizeBound(pEdge, point1, point2);
			}
			convexity = m_pVectorVPoint[i].convexity;
			point1 = point2;
			edgelist.push_back(pEdge);
			if (pEdge->bound.max_y > *Ymax)
				*Ymax = pEdge->bound.max_y;
			if (pEdge->bound.min_y < *Ymin)
				*Ymin = pEdge->bound.min_y;
		}
	}
	else
	{
		point1.x = CosRotate*m_pVectorVPoint[0].x - SinRotate*m_pVectorVPoint[0].y;
		point1.y = SinRotate*m_pVectorVPoint[0].x + CosRotate*m_pVectorVPoint[0].y;
		convexity = m_pVectorVPoint[0].convexity;
		*Ymax = point1.y;
		*Ymin = point1.y;
		for (int i = 1; i < m_VertexCount; i++)
		{
			point2.x = CosRotate*m_pVectorVPoint[i].x - SinRotate*m_pVectorVPoint[i].y;
			point2.y = SinRotate*m_pVectorVPoint[i].x + CosRotate*m_pVectorVPoint[i].y;
			pEdge = new ObjEdge();
			if (convexity == 0)
			{
				pEdge->StartOrCircle = point1;
				pEdge->EndOrRadian = point2;
				pEdge->radius = 0;
				pEdge->bound = SizeBound(pEdge);
			}
			else
			{
				TranPolylineToArc(point1, point2, convexity,
					&point3, &radius, &sangle, &eangle);
				pEdge->StartOrCircle = point3;
				pEdge->EndOrRadian.x = M_PI*sangle / 180;
				pEdge->EndOrRadian.y = M_PI*eangle / 180;
				pEdge->radius = radius;
				pEdge->bound = SizeBound(pEdge, point1, point2);
			}
			convexity = m_pVectorVPoint[i].convexity;
			point1 = point2;
			edgelist.push_back(pEdge);
			if (pEdge->bound.max_y > *Ymax)
				*Ymax = pEdge->bound.max_y;
			if (pEdge->bound.min_y < *Ymin)
				*Ymin = pEdge->bound.min_y;
		}
	}
	return edgelist;
}

void CMachineObjFillPolyline::Remove(ObjEdgeList* EdgeList, int Index)
{
	int Count = EdgeList->size();
	if (Index >= Count)
		return;
	ObjEdge *pEdge1;
	if (Index < Count - 1)
	{
		pEdge1 = (*EdgeList)[Index];
		for (int i = Index; i < Count - 1; i++)
		{
			(*EdgeList)[i] = (*EdgeList)[i + 1];
		}
	}
	EdgeList->pop_back();
}

void CMachineObjFillPolyline::FillPolyline()
{
	
	ObjEdgeList pEdgelist;
	GeometryLine line;
	double	Step, Curtail, y0, ymin, ymax; 
	byte	GapMode, FillMode;
	int stepcount, nCount;
	ObjRect rect;
	ObjEdgeList ActiveEdgeList;
	ObjEdge *ActivepEdge;
	ObjPoint point0, point1, point2, point3;

	for (int num = 0; num < 4; num++)
	{
		if (m_FillPara[num].IsEnable)
		{
			VectLine FillLine;
			double CosRotate = cos(m_FillPara[num].FillAngle*M_PI / 180);
			double SinRotate = sin(m_FillPara[num].FillAngle*M_PI / 180);
			Step = m_FillPara[num].FillGap;
			Curtail = m_FillPara[num].Curtail;
			GapMode = m_FillPara[num].GapMode;
			FillMode = m_FillPara[num].FillMode;
			pEdgelist = CreatEdgelist(&ymax, &ymin, -SinRotate, CosRotate);
			y0 = ymax - ymin - Curtail * 2;
			stepcount = (int)(y0 / Step);
			if (GapMode == 0)
			{
				y0 = ymin + Curtail + (y0 - stepcount*Step) / 2;
				stepcount++;
				if (m_OutlinePrior != 0)
				{
					y0 += Step;
					stepcount -= 2;
				}
			}
			else
			{
				Step = y0 / stepcount;
				y0 = ymin + Curtail;
				stepcount++;
				if (m_OutlinePrior != 0)
				{
					y0 += Step;
					stepcount -= 2;
				}
			}
			bool dir_line = true;
			for (int i = 0; i < stepcount; i++)
			{
				nCount = ActiveEdgeList.size();
				for (int j = 0; j < nCount; j++)
				{
					rect = ActiveEdgeList[j]->bound;
					rect.max_y += Zero;
					rect.min_y -= Zero;
					if ((rect.max_y < y0) || (rect.min_y > y0))
					{
						ActivepEdge = ActiveEdgeList[j];
						Remove(&ActiveEdgeList, j);
						delete ActivepEdge;
						j--;
						nCount--;
					}
				} 
				nCount = pEdgelist.size();
				for (int j = 0; j<nCount; j++)
				{
					rect = pEdgelist[j]->bound;
					rect.max_y += Zero;
					rect.min_y -= Zero;
					if ((rect.max_y >= y0) && (rect.min_y <= y0))
					{
						ActiveEdgeList.push_back(pEdgelist[j]);
						Remove(&pEdgelist, j);
						j--;
						nCount--;
					}
				}
				//find cross point
				struct CrossX
				{
					double x;
					int status;
				};
				CrossX cpoint;
				vector<CrossX> cpointlist;
				nCount = ActiveEdgeList.size();
				for (int j = 0; j < nCount; j++)
				{
					ActivepEdge = ActiveEdgeList[j];
					if (ActivepEdge->radius == 0)
					{
						//line
						point1 = ActivepEdge->StartOrCircle;
						point2 = ActivepEdge->EndOrRadian;
						if (abs(point1.y - point2.y) < Zero)
						{
							cpoint.x = point1.x;
							cpoint.status = 0;		//horizon point
							cpointlist.push_back(cpoint);
							cpoint.x = point2.x;
							cpointlist.push_back(cpoint);
						}
						else
						{
							rect = ActivepEdge->bound;
							cpoint.x = point1.x + (y0 - point1.y)*(point2.x - point1.x) / (point2.y - point1.y);
							if (abs(y0 - rect.max_y) < Zero)
								cpoint.status = 1;	//up terminal point
							else if (abs(y0 - rect.min_y) < Zero)
								cpoint.status = 2;		//down terminal point
							else
								cpoint.status = -1;		//mid point
							cpointlist.push_back(cpoint);
						}
					}
					else
					{
						//Arc
						double x1, x2, delta;
						rect = ActivepEdge->bound;
						delta = ActivepEdge->radius*ActivepEdge->radius - 
							(y0 - ActivepEdge->StartOrCircle.y)*(y0 - ActivepEdge->StartOrCircle.y);
						if (delta > Zero)
						{
							//double cross point
							x1 = ActivepEdge->StartOrCircle.x - sqrt(delta);
							x2 = ActivepEdge->StartOrCircle.x + sqrt(delta);
							if ((x1 >= (ActivepEdge->bound.min_x - Zero)) 
								&& (x1 <= (ActivepEdge->bound.max_x + Zero)))
							{
								//first cross point in bound
								cpoint.x = x1;
								if (abs(y0 - rect.max_y) < Zero)
									cpoint.status = 1;	//up terminal point
								else if (abs(y0 - rect.min_y) < Zero)
									cpoint.status = 2;		//down terminal point
								else
									cpoint.status = -1;		//mid point
								cpointlist.push_back(cpoint);
							}
							if ((x2 >= (ActivepEdge->bound.min_x - Zero))
								&& (x2 <= (ActivepEdge->bound.max_x + Zero)))
							{
								//second cross point in bound
								cpoint.x = x2;
								if (abs(y0 - rect.max_y) < Zero)
									cpoint.status = 1;	//up terminal point
								else if (abs(y0 - rect.min_y) < Zero)
									cpoint.status = 2;		//down terminal point
								else
									cpoint.status = -1;		//mid point
								cpointlist.push_back(cpoint);
							}
						}
						else if (abs(delta) <= Zero)
						{
							//single cross point
							cpoint.x = ActivepEdge->StartOrCircle.x;
							if (abs(y0 - rect.max_y) < Zero)
								cpoint.status = 1;	//up terminal point
							else if (abs(y0 - rect.min_y) < Zero)
								cpoint.status = 2;		//down terminal point
							else
								cpoint.status = -1;		//mid point
							cpointlist.push_back(cpoint);
						}
					}
				}
				//cross point sort
				nCount = cpointlist.size();
				for (int j = 0; j < nCount - 1; j++)
				{
					for (int k = 0; k < nCount - 1 - j; k++)
					{
						if (cpointlist[k].x > cpointlist[k + 1].x)
						{   
							cpoint = cpointlist[k + 1];
							cpointlist[k + 1] = cpointlist[k];
							cpointlist[k] = cpoint;
						}
					}
				}
				//fill line
				bool flag_sp = true;
				double x_last = cpointlist[0].x;
				int status_last = cpointlist[0].status;
				for (int j = 1; j < nCount; j++)
				{
					cpoint = cpointlist[j];
					if (flag_sp)
					{
						//last point is start point
						if (abs(cpoint.x - x_last) < Zero)
						{
							//overlap point 
							if (cpoint.status == status_last)
								flag_sp = false;
							else if (cpoint.status == 0)
								status_last = cpoint.status;
						}
						else
						{
							//normal point
							point1.x = x_last + Curtail;	
							point1.y = y0;
							point2.x = cpoint.x - Curtail;
							point2.y = y0;
							if ((point2.x - point1.x) > Zero)
							{
								if (dir_line)
								{
									line.StartPoint = point1;
									line.EndPoint = point2;
								}
								else
								{
									line.StartPoint = point2;
									line.EndPoint = point1;
								}
								if ((SinRotate != 0) && (CosRotate != 1))
								{
									point1.x = CosRotate*line.StartPoint.x - SinRotate*line.StartPoint.y;
									point1.y = SinRotate*line.StartPoint.x + CosRotate*line.StartPoint.y;
									line.StartPoint = point1;
									point1.x = CosRotate*line.EndPoint.x - SinRotate*line.EndPoint.y;
									point1.y = SinRotate*line.EndPoint.x + CosRotate*line.EndPoint.y;
									line.EndPoint = point1;
								}
								if ((m_OutlinePrior == 0) || (status_last != 0) || (cpoint.status != 0))
									FillLine.push_back(line);
							}
							x_last = cpoint.x;
							status_last = cpoint.status;
							flag_sp = false;
						}
					}
					else
					{
						//last point is end point
						if (abs(cpoint.x - x_last) < Zero)
						{
							//overlap point
							if (cpoint.status == status_last)
								flag_sp = true;
							else if (cpoint.status == 0)
								status_last = cpoint.status;
						}
						else
						{
							//normal point
							x_last = cpoint.x;
							status_last = cpoint.status;
							flag_sp = true;
						}
					}
				}
				y0 += Step;
				if (FillMode == 1)
					dir_line = !dir_line;
			}
			nCount = FillLine.size();
			for (int i = 0; i < nCount; i++)
			{
				line = FillLine[i];
				m_FillLine.push_back(line);
			}
			nCount = ActiveEdgeList.size();
			for (int i = 0; i < nCount; i++)
			{
				ActivepEdge = ActiveEdgeList[nCount - i - 1];
				ActiveEdgeList.pop_back();
				delete ActivepEdge;
			}
			nCount = pEdgelist.size();
			for (int i = 0; i < nCount; i++)
			{
				ActivepEdge = pEdgelist[nCount - i - 1];
				pEdgelist.pop_back();
				delete ActivepEdge;
			}
		}
	}
}

// 公开函数

CMachineObjPolyline* CMachineObjFillPolyline::DegenerateToPolyline()
{
	int Count = m_FillLine.size();
	for (int i = 0; i < Count; i++)
	{
		GeometryLine line;
		line = m_FillLine[Count - i - 1];
//		delete &pline;
		m_FillLine.pop_back();
	}
	CMachineObjPolyline* pPolyline = new CMachineObjPolyline;
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

byte CMachineObjFillPolyline::GetOutlinePrior()
{
	return m_OutlinePrior;
}

void CMachineObjFillPolyline::MoveFillPolyline(double X_shift, double Y_shift)
{
	MovePolyline(X_shift, Y_shift);
	GeometryLine line;
	int nCount = m_FillLine.size();
	for (int i = 0; i < nCount; i++)
	{
		m_FillLine[i].StartPoint.x += X_shift;
		m_FillLine[i].StartPoint.y += Y_shift;
		m_FillLine[i].EndPoint.x += X_shift;
		m_FillLine[i].EndPoint.y += Y_shift;
	}
}

FillPara CMachineObjFillPolyline::GetFillPolylinePara(int Group)
{
	return m_FillPara[Group];
}

void CMachineObjFillPolyline::ReCreatFillPolyline(byte OutlinePrior, FillPara* pPara)
{
	int nCount;
	nCount = m_FillLine.size();
	for (int i = 0; i < nCount; i++)
	{
		GeometryLine line;
		line = m_FillLine[nCount - i - 1];
		m_FillLine.pop_back();
	}
	m_OutlinePrior = OutlinePrior;
	for (int i = 0; i < 4; i++)
	{
		m_FillPara[i].FillAngle = pPara->FillAngle;
		m_FillPara[i].FillGap = pPara->FillGap;
		m_FillPara[i].Curtail = pPara->Curtail;
		m_FillPara[i].GapMode = pPara->GapMode;
		m_FillPara[i].FillMode = pPara->FillMode;
		m_FillPara[i].IsEnable = pPara->IsEnable;
		pPara++;
	}
	FillPolyline();
}