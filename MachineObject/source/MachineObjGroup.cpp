// MachineObjGroup.cpp : 实现文件
//
#include "stdafx.h"
#include "MachineObjGroup.h"

// CMachineObjGroup 构造函数
CMachineObjGroup::CMachineObjGroup()
{
	m_ObjType = MachineObj_Type_Group;
	m_pList = new CMachineObjList();
	m_bIsObjStatus = IsObjNormal;
	m_ObjByLayer = LayerNum_Group;
}

CMachineObjGroup::~CMachineObjGroup()
{
	POSITION pos;
	pos = m_pList->GetHeadPosition();
	while (pos)
	{
		delete m_pList->GetNext(pos);
	}
	m_pList->RemoveAll();
	delete m_pList;
	m_pList = NULL;
}

// 序列化
void CMachineObjGroup::Serialize(CArchive& ar)
{
	CMachineObj_Comm* pObj;
	int Count;
	if (ar.IsStoring())
	{
		POSITION pos;
		ar << m_ObjType << m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y << m_ObjByLayer;
		Count = m_pList->GetCount();
		ar << Count;
		pos = m_pList->GetHeadPosition();
		for (int i = 0; i < Count; i++)
		{
			pObj = m_pList->GetNext(pos);
			switch (pObj->GetObjType())
			{
			case MachineObj_Type_Point:
				((CMachineObjPoint*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_Line:
				((CMachineObjLine*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_Circle:
				((CMachineObjCircle*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_Ellipse:
				((CMachineObjEllipse*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_Arc:
				((CMachineObjArc*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_ArcEll:
				((CMachineObjArcEll*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_TiltEllipse:
				((CMachineObjTiltEllipse*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_Polyline:
				((CMachineObjPolyline*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_Group:
				((CMachineObjGroup*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_WLine:
				((CMachineObjWLine*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_WArc:
				((CMachineObjWArc*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_WPolyline:
				((CMachineObjWPolyline*)pObj)->Serialize(ar);
				break;
			case MachineObj_Type_FillPolyline:
				((CMachineObjFillPolyline*)pObj)->Serialize(ar);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		CMachineObjList* pList;
		pList = m_pList;
		int ObjType;
		m_ObjType = MachineObj_Type_Group;
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y >> m_ObjByLayer;
		ar >> Count;
		for (int i = 0; i < Count; i++)
		{
			ar >> ObjType;
			switch (ObjType)
			{
			case MachineObj_Type_Point:
				pObj = new CMachineObjPoint;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_Line:
				pObj = new CMachineObjLine;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_Circle:
				pObj = new CMachineObjCircle;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_Ellipse:
				pObj = new CMachineObjEllipse;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_Arc:
				pObj = new CMachineObjArc;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_ArcEll:
				pObj = new CMachineObjArcEll;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_TiltEllipse:
				pObj = new CMachineObjTiltEllipse;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_Polyline:
				pObj = new CMachineObjPolyline;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_Group:
				pObj = new CMachineObjGroup;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_WLine:
				pObj = new CMachineObjWLine;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_WArc:
				pObj = new CMachineObjWArc;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_WPolyline:
				pObj = new CMachineObjWPolyline;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			case MachineObj_Type_FillPolyline:
				pObj = new CMachineObjFillPolyline;
				pObj->Serialize(ar);
				pList->AddTail(pObj);
				break;
			default:
				break;
			}
		}
		m_pList = pList;
		pList = NULL;
	}
}

// CMachineObjGroup 成员函数
// 私有函数
void CMachineObjGroup::ReSizeBound(CMachineObj_Comm* MachineObj)
{
	ObjRect ObjBound = MachineObj->GetObjBound();
	if (m_pList->GetCount() == 1)
	{
		m_ObjBound = ObjBound;
		return;
	}
	if (m_ObjBound.min_x > ObjBound.min_x)
		m_ObjBound.min_x = ObjBound.min_x;
	if (m_ObjBound.max_x < ObjBound.max_x)
		m_ObjBound.max_x = ObjBound.max_x;
	if (m_ObjBound.min_y > ObjBound.min_y)
		m_ObjBound.min_y = ObjBound.min_y;
	if (m_ObjBound.max_y < ObjBound.max_y)
		m_ObjBound.max_y = ObjBound.max_y;
}

// 公开函数 
CMachineObjList* CMachineObjGroup::GetObjList()
{
	return m_pList;
}


void CMachineObjGroup::AddGroupObj(CMachineObj_Comm* MachineObj)
{
	m_pList->AddTail(MachineObj);
	ReSizeBound(MachineObj);
}

CMachineObj_Comm* CMachineObjGroup::GetAndMoveGroupObj()
{
	if (m_pList->GetCount() <= 0)
		return NULL;
	CMachineObj_Comm* pObj;
	pObj=m_pList->GetHead();
	m_pList->RemoveHead();
	return pObj;
}

void CMachineObjGroup::MoveGroup(double X_shift, double Y_shift)
{
	CMachineObj_Comm* pObj;
	int Count;
	POSITION pos;
	Count = m_pList->GetCount();
	pos = m_pList->GetHeadPosition();
	for (int i = 0; i < Count; i++)
	{
		pObj = m_pList->GetNext(pos);
		switch (pObj->GetObjType())
		{
		case MachineObj_Type_Point:
			((CMachineObjPoint*)pObj)->MovePoint(X_shift, Y_shift);
			break;
		case MachineObj_Type_Line:
			((CMachineObjLine*)pObj)->MoveLine(X_shift, Y_shift);
			break;
		case MachineObj_Type_Circle:
			((CMachineObjCircle*)pObj)->MoveCircle(X_shift, Y_shift);
			break;
		case MachineObj_Type_Ellipse:
			((CMachineObjEllipse*)pObj)->MoveEllipse(X_shift, Y_shift);
			break;
		case MachineObj_Type_Arc:
			((CMachineObjArc*)pObj)->MoveArc(X_shift, Y_shift);
			break;
		case MachineObj_Type_ArcEll:
			((CMachineObjArcEll*)pObj)->MoveArcEll(X_shift, Y_shift);
			break;
		case MachineObj_Type_TiltEllipse:
			((CMachineObjTiltEllipse*)pObj)->MoveTileEllipse(X_shift, Y_shift);
			break;
		case MachineObj_Type_Polyline:
			((CMachineObjPolyline*)pObj)->MovePolyline(X_shift, Y_shift);
			break;
		case MachineObj_Type_Group:
			((CMachineObjGroup*)pObj)->MoveGroup(X_shift, Y_shift);
			break;
		case MachineObj_Type_WLine:
			((CMachineObjWLine*)pObj)->MoveWLine(X_shift, Y_shift);
			break;
		case MachineObj_Type_WArc:
			((CMachineObjWArc*)pObj)->MoveWArc(X_shift, Y_shift);
			break;
		case MachineObj_Type_WPolyline:
			((CMachineObjWPolyline*)pObj)->MoveWPolyline(X_shift, Y_shift);
			break;
		case MachineObj_Type_FillPolyline:
			((CMachineObjFillPolyline*)pObj)->MoveFillPolyline(X_shift, Y_shift);
			break;
		default:
			break;
		}
	}
	m_ObjBound.max_x += X_shift;
	m_ObjBound.min_x += X_shift;
	m_ObjBound.max_y += Y_shift;
	m_ObjBound.min_y += Y_shift;
}
