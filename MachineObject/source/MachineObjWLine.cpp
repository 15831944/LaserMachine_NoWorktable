// MachineObjWLine.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineObjWLine.h"

// CMachineObjLine 构造函数
CMachineObjWLine::CMachineObjWLine()
{
	m_ObjType = MachineObj_Type_WLine;
	m_LineStart = ObjPoint();
	m_LineEnd = ObjPoint();
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_Duplicate = 0;
	m_GapDistance = 0;
	m_pDupList.swap(vector<VectPoint*>(NULL));
	m_ObjBound = ObjRect();
}

CMachineObjWLine::CMachineObjWLine(CMachineObjLine* pLine, int Duplicate, float GapDistance)
{
	m_ObjType = MachineObj_Type_WLine;
	m_LineStart = pLine->GetLineStart();
	m_LineEnd = pLine->GetLineEnd();
	m_ObjByLayer = pLine->m_ObjByLayer;
	m_bIsObjStatus = pLine->m_bIsObjStatus;
	m_Duplicate = Duplicate;
	m_GapDistance = GapDistance;
	CMachineObjLine::ReSizeBound();
	ExtendWLine();
}

CMachineObjWLine::~CMachineObjWLine()
{
	VectPoint* pWLine;
	int Count = m_pDupList.size();
	for (int i = 0; i < Count; i++)
	{
		pWLine = m_pDupList[i];
		delete pWLine;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
}

// 序列化
void CMachineObjWLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_LineStart.x << m_LineStart.y
			<< m_LineEnd.x << m_LineEnd.y
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer
			<< m_Duplicate << m_GapDistance;
	}
	else
	{
		m_ObjType = MachineObj_Type_WLine;
		ar >> m_LineStart.x >> m_LineStart.y
			>> m_LineEnd.x >> m_LineEnd.y
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer
			>> m_Duplicate >> m_GapDistance;
		ExtendWLine();
		m_bIsObjStatus = IsObjNormal;
	}
}

 //CMachineObjWLine 成员函数
 //私有函数

void CMachineObjWLine::ExtendWLine()
{
	ObjPoint point1, point2;
	ObjRect bound;
	VectPoint* pWLine;
	double K1, K2;
	for (int i = 1; i <= m_Duplicate; i++)
	{
		if (m_LineEnd.x == m_LineStart.x)
		{
			if (m_LineEnd.y > m_LineStart.y)
			{
				point1.x = m_LineStart.x + i*m_GapDistance;
				point1.y = m_LineStart.y;
				point2.x = m_LineEnd.x + i*m_GapDistance;
				point2.y = m_LineEnd.y;
			}
			else
			{
				point1.x = m_LineStart.x - i*m_GapDistance;
				point1.y = m_LineStart.y;
				point2.x = m_LineEnd.x - i*m_GapDistance;
				point2.y = m_LineEnd.y;
			}
		}
		else
		{
			K1 = (m_LineEnd.y - m_LineStart.y) / (m_LineEnd.x - m_LineStart.x);
			K2 = 1 / sqrt(1 + K1*K1);
			K1 = K1*K2;
			if (m_LineEnd.x > m_LineStart.x)
			{
				point1.x = m_LineStart.x + i*K1*m_GapDistance;
				point1.y = m_LineStart.y - i*K2*m_GapDistance;
				point2.x = m_LineEnd.x + i*K1*m_GapDistance;
				point2.y = m_LineEnd.y - i*K2*m_GapDistance;
			}
			else
			{
				point1.x = m_LineStart.x - i*K1*m_GapDistance;
				point1.y = m_LineStart.y + i*K2*m_GapDistance;
				point2.x = m_LineEnd.x - i*K1*m_GapDistance;
				point2.y = m_LineEnd.y + i*K2*m_GapDistance;
			}
		}
		pWLine = new VectPoint;
		pWLine->push_back(point1);
		pWLine->push_back(point2);
		m_pDupList.push_back(pWLine);
	}
	for (int i = 1; i <= m_Duplicate; i++)
	{
		if (m_LineEnd.x == m_LineStart.x)
		{
			if (m_LineEnd.y < m_LineStart.y)
			{
				point1.x = m_LineStart.x + i*m_GapDistance;
				point1.y = m_LineStart.y;
				point2.x = m_LineEnd.x + i*m_GapDistance;
				point2.y = m_LineEnd.y;
			}
			else
			{
				point1.x = m_LineStart.x - i*m_GapDistance;
				point1.y = m_LineStart.y;
				point2.x = m_LineEnd.x - i*m_GapDistance;
				point2.y = m_LineEnd.y;
			}
		}
		else
		{
			K1 = (m_LineEnd.y - m_LineStart.y) / (m_LineEnd.x - m_LineStart.x);
			K2 = 1 / sqrt(1 + K1*K1);
			K1 = K1*K2;
			if (m_LineEnd.x < m_LineStart.x)
			{
				point1.x = m_LineStart.x + i*K1*m_GapDistance;
				point1.y = m_LineStart.y - i*K2*m_GapDistance;
				point2.x = m_LineEnd.x + i*K1*m_GapDistance;
				point2.y = m_LineEnd.y - i*K2*m_GapDistance;
			}
			else
			{
				point1.x = m_LineStart.x - i*K1*m_GapDistance;
				point1.y = m_LineStart.y + i*K2*m_GapDistance;
				point2.x = m_LineEnd.x - i*K1*m_GapDistance;
				point2.y = m_LineEnd.y + i*K2*m_GapDistance;
			}
		}
		pWLine = new VectPoint;
		pWLine->push_back(point1);
		pWLine->push_back(point2);
		m_pDupList.push_back(pWLine);
	}
	return;
}

// 公开函数
CMachineObjLine* CMachineObjWLine::DegenerateToLine()
{
	int Count = m_pDupList.size();
	VectPoint* pWLine;
	for (int i = 0; i < Count; i++)
	{
		pWLine = m_pDupList[i];
		delete pWLine;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	CMachineObjLine* pLine = new CMachineObjLine(this->m_LineStart, this->m_LineEnd, this->m_ObjByLayer);
	pLine->m_bIsObjStatus = this->m_bIsObjStatus;
	return pLine;
}

void CMachineObjWLine::MoveWLine(double X_shift, double Y_shift)
{
	m_LineStart.x += X_shift;
	m_LineStart.y += Y_shift;
	m_LineEnd.x += X_shift;
	m_LineEnd.y += Y_shift;
	ObjPoint point;
	int nCount1 = m_pDupList.size();
	for (int i = 0; i < nCount1; i++)
	{
		VectPoint &pointlist = *m_pDupList[i];
		pointlist[0].x += X_shift;
		pointlist[0].y += Y_shift;
		pointlist[1].x += X_shift;
		pointlist[1].y += Y_shift;
	}
	m_ObjBound.max_x += X_shift;
	m_ObjBound.min_x += X_shift;
	m_ObjBound.max_y += Y_shift;
	m_ObjBound.min_y += Y_shift;
}

void CMachineObjWLine::ExchangeStartAndEnd()
{
	ObjPoint point;
	point = m_LineStart;
	m_LineStart = m_LineEnd;
	m_LineEnd = point;
	int nCount1 = m_pDupList.size();
	for (int i = 0; i < nCount1; i++)
	{
		VectPoint &pointlist = *m_pDupList[i];
		point = pointlist[0];
		pointlist[0] = pointlist[1];
		pointlist[1] = point;
	}
}

int CMachineObjWLine::GetDupNumber()
{
	return m_Duplicate;
}

float CMachineObjWLine::GetGapDistance()
{
	return m_GapDistance;
}

void CMachineObjWLine::SetDupNumber(int DupNumber)
{
	m_Duplicate = DupNumber;
	int Count = m_pDupList.size();
	VectPoint* pWLine;
	for (int i = 0; i < Count; i++)
	{
		pWLine = m_pDupList[i];
		delete pWLine;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ExtendWLine();
}

void CMachineObjWLine::SetGapDistance(float GapDistance)
{
	m_GapDistance = GapDistance;
	int Count = m_pDupList.size();
	VectPoint* pWLine;
	for (int i = 0; i < Count; i++)
	{
		pWLine = m_pDupList[i];
		delete pWLine;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ExtendWLine(); 
}

void CMachineObjWLine::ReCreatWLine(int DupNumber, float GapDistance)
{
	m_Duplicate = DupNumber;
	m_GapDistance = GapDistance;
	int Count = m_pDupList.size();
	VectPoint* pWLine;
	for (int i = 0; i < Count; i++)
	{
		pWLine = m_pDupList[i];
		delete pWLine;
	}
	m_pDupList.swap(vector<VectPoint*>(NULL));
	ExtendWLine();
}
