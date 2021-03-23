// MachineObjLine.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineObjLine.h"

// CMachineObjLine 构造函数
CMachineObjLine::CMachineObjLine()
{
	m_ObjType = MachineObj_Type_Line;
	m_LineStart = ObjPoint();
	m_LineEnd = ObjPoint();
	m_ObjByLayer = LayerNum_Default;
	m_bIsObjStatus = IsObjNormal;
	m_ObjBound = ObjRect();
}

CMachineObjLine::CMachineObjLine(ObjPoint LineStart, ObjPoint LineEnd, int LineByLayer)
{
	
	m_ObjType = MachineObj_Type_Line;
	m_LineStart= LineStart;
	m_LineEnd = LineEnd;
	m_ObjByLayer = LineByLayer;
	m_bIsObjStatus = IsObjNormal;
	ReSizeBound();
}

CMachineObjLine::~CMachineObjLine()
{
}
// 序列化
void CMachineObjLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_ObjType << m_LineStart.x << m_LineStart.y
			<< m_LineEnd.x << m_LineEnd.y
			<< m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
	}
	else
	{
		m_ObjType = MachineObj_Type_Line;
		ar >> m_LineStart.x >> m_LineStart.y
			>> m_LineEnd.x >> m_LineEnd.y
			>> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		m_bIsObjStatus = IsObjNormal;
	}
}

// CMachineObjLine 成员函数
// 私有函数

// Protected函数
void CMachineObjLine::ReSizeBound()
{
	if (m_LineStart.x > m_LineEnd.x)
	{
		m_ObjBound.min_x = m_LineEnd.x;
		m_ObjBound.max_x = m_LineStart.x;
	}
	else
	{
		m_ObjBound.min_x = m_LineStart.x;
		m_ObjBound.max_x = m_LineEnd.x;
	}
	if (m_LineStart.y > m_LineEnd.y)
	{
		m_ObjBound.min_y = m_LineEnd.y;
		m_ObjBound.max_y = m_LineStart.y;
	}
	else
	{
		m_ObjBound.min_y = m_LineStart.y;
		m_ObjBound.max_y = m_LineEnd.y;
	}
}

// 公开函数
void CMachineObjLine::SetLineStart(ObjPoint LineStart)
{
	m_LineStart = LineStart;
	ReSizeBound();
}

void CMachineObjLine::SetLineEnd(ObjPoint LineEnd)
{
	m_LineEnd = LineEnd;
	ReSizeBound();
}

void CMachineObjLine::SetLine(ObjPoint LineStart, ObjPoint LineEnd)
{
	m_LineStart = LineStart;
	m_LineEnd = LineEnd;
	ReSizeBound();
}

void CMachineObjLine::MoveLineStart(ObjPoint LineStart)
{
	m_LineStart = LineStart;
	m_LineEnd.x = m_LineEnd.x + (LineStart.x - m_LineStart.x);
	m_LineEnd.y = m_LineEnd.y + (LineStart.y - m_LineStart.y);
	ReSizeBound();
}

void CMachineObjLine::MoveLineEnd(ObjPoint LineEnd)
{
	m_LineEnd = LineEnd;
	m_LineStart.x = m_LineStart.x + (LineEnd.x - m_LineEnd.x);
	m_LineStart.y = m_LineStart.y + (LineEnd.y - m_LineEnd.y);
	ReSizeBound();
}

void CMachineObjLine::MoveLine(double X_shift, double Y_shift)
{
	m_LineStart.x += X_shift;
	m_LineStart.y += Y_shift;
	m_LineEnd.x += X_shift;
	m_LineEnd.y += Y_shift;
	ReSizeBound();
}

void CMachineObjLine::ExchangeStartAndEnd(CMachineObjLine* pObj)
{
	ObjPoint point;
	point = m_LineStart;
	m_LineStart = m_LineEnd;
	m_LineEnd = point;
}

ObjPoint CMachineObjLine::GetLineStart()
{
	return m_LineStart;
}

ObjPoint CMachineObjLine::GetLineEnd()
{
	return m_LineEnd;
}



