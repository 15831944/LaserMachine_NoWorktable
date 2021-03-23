// MachineObj_Comm.cpp : 实现文件
//
#include "stdafx.h"
#include "MachineObj_Comm.h"
#include "MachineObjPoint.h"
#include "MachineObjLine.h"
#include "MachineObjCircle.h"
#include "MachineObjEllipse.h"
#include "MachineObjArc.h"
#include "MachineObjArcEll.h"
#include "MachineObjTiltEllipse.h"
#include "MachineObjPolyline.h"
#include "MachineObjGroup.h"
#include "MachineObjWLine.h"


// CMachineObj_Comm 构造函数
CMachineObj_Comm::CMachineObj_Comm()
{
	m_bIsObjStatus = IsObjNormal;
}

CMachineObj_Comm::~CMachineObj_Comm()
{
}

// CMachineObj_Comm 成员函数
// 公开函数
int CMachineObj_Comm::GetObjType()
{
	return m_ObjType;
}

ObjRect CMachineObj_Comm::GetObjBound()
{
	return m_ObjBound;
}

ObjPoint CMachineObj_Comm::GetObjStart(CMachineObj_Comm* pObj)
{
	ObjPoint point;
	switch (pObj->m_ObjType)
	{
	case MachineObj_Type_Point:
		CMachineObjPoint* pPoint;
		pPoint = (CMachineObjPoint*)pObj;
		return pPoint->GetPoint();
	case MachineObj_Type_Line:
		CMachineObjLine* pLine;
		pLine = (CMachineObjLine*)pObj;
		return pLine->GetLineStart();
	case MachineObj_Type_Circle:
		CMachineObjCircle* pCircle;
		pCircle = (CMachineObjCircle*)pObj;
		return pCircle->GetCircleStart();
	case MachineObj_Type_Arc:
		CMachineObjArc* pArc;
		pArc = (CMachineObjArc*)pObj;
		return pArc->GetArcStart();
	case MachineObj_Type_Ellipse:
		CMachineObjEllipse* pEllipse;
		pEllipse = (CMachineObjEllipse*)pObj;
		return pEllipse->GetEllipseStart();
	case MachineObj_Type_ArcEll:
		CMachineObjArcEll* pArcEll;
		pArcEll = (CMachineObjArcEll*)pObj;
		return pArcEll->GetArcStart();
	case MachineObj_Type_TiltEllipse:
		CMachineObjTiltEllipse* pTiltEll;
		pTiltEll = (CMachineObjTiltEllipse*)pObj;
		return pTiltEll->GetTiltEllipseStart();
	case MachineObj_Type_Polyline:
		CMachineObjPolyline* pPolyline;
		pPolyline = (CMachineObjPolyline*)pObj;
		point.x = pPolyline->GetPolylineStart().x;
		point.y = pPolyline->GetPolylineStart().y;
		return point;
	default:
		break;
	}
	return ObjPoint(0, 0);
}

ObjPoint CMachineObj_Comm::GetObjEnd(CMachineObj_Comm* pObj)
{
	ObjPoint point;
	switch (pObj->m_ObjType)
	{
	case MachineObj_Type_Line:
		CMachineObjLine* pLine;
		pLine = (CMachineObjLine*)pObj;
		return pLine->GetLineEnd();
	case MachineObj_Type_Circle:
		CMachineObjCircle* pCircle;
		pCircle = (CMachineObjCircle*)pObj;
		return pCircle->GetCircleStart();
	case MachineObj_Type_Arc:
		CMachineObjArc* pArc;
		pArc = (CMachineObjArc*)pObj;
		return pArc->GetArcEnd();
	case MachineObj_Type_Ellipse:
		CMachineObjEllipse* pEllipse;
		pEllipse = (CMachineObjEllipse*)pObj;
		return pEllipse->GetEllipseStart();
	case MachineObj_Type_ArcEll:
		CMachineObjArcEll* pArcEll;
		pArcEll = (CMachineObjArcEll*)pObj;
		return pArcEll->GetArcEnd();
	case MachineObj_Type_TiltEllipse:
		CMachineObjTiltEllipse* pTiltEll;
		pTiltEll = (CMachineObjTiltEllipse*)pObj;
		return pTiltEll->GetTiltEllipseEnd();
	case MachineObj_Type_Polyline:
		CMachineObjPolyline* pPolyline;
		pPolyline = (CMachineObjPolyline*)pObj;
		point.x = pPolyline->GetPolylineEnd().x;
		point.y = pPolyline->GetPolylineEnd().y;
		return point;
	default:
		break;
	}
	return ObjPoint(0, 0);
}

CMachineObj_Comm* CMachineObj_Comm::ExchangeStartAndEnd(CMachineObj_Comm* pObj)
{
	int Number;
	int nType = pObj->GetObjType();
	switch (nType)
	{
	case MachineObj_Type_Line:
		CMachineObjLine* pLine;
		pLine = (CMachineObjLine*)pObj;
		pLine->ExchangeStartAndEnd(pLine);
		break;
	case MachineObj_Type_Circle:
		CMachineObjCircle* pCircle;
		pCircle = (CMachineObjCircle*)pObj;
		Number = pCircle->GetCircleStartNum();
		Number++;
		if (Number > 3)
			Number = 0;
		pCircle->SetCircleStart(Number);
		break;
	case MachineObj_Type_Arc:
		CMachineObjArc* pArc;
		pArc = (CMachineObjArc*)pObj;
		pArc->ExchangeStartAndEnd(pArc);
		break;
	case MachineObj_Type_Ellipse:
		CMachineObjEllipse* pEllipse;
		pEllipse = (CMachineObjEllipse*)pObj;
		Number = pEllipse->GetEllipseStartNum();
		Number++;
		if (Number > 3)
			Number = 0;
		pEllipse->SetEllipseStart(Number);
		break;
	case MachineObj_Type_ArcEll:
		CMachineObjArcEll* pArcEll;
		pArcEll = (CMachineObjArcEll*)pObj;
		pArcEll->ExchangeStartAndEnd(pArcEll);
		break;
	case MachineObj_Type_TiltEllipse:
		CMachineObjTiltEllipse* pTiltEllArc;
		pTiltEllArc = (CMachineObjTiltEllipse*)pObj;
		pTiltEllArc->ExchangeStartAndEnd(pTiltEllArc);
		break;
	case MachineObj_Type_Polyline:
		CMachineObjPolyline* pPolyline;
		pPolyline = (CMachineObjPolyline*)pObj;
		pPolyline->ExchangeStartAndEnd(pPolyline);
		break;
	default:
		break;
	}
	return pObj;
}
