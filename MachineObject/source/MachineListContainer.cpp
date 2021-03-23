// MachineListContainer.cpp : 实现文件
//

#include "stdafx.h"
#include "MachineListContainer.h"


// MachineListContainer 构造函数
CMachineListContainer::CMachineListContainer()
{
	m_MachineParaDefault = ProcessPara();
	m_MachineModeDefault = 0;
	m_MachineWaitTimeDefault = 0;
	m_MachineLayerList = new CMachine_LayerList();
	CMachinePara_Layer* pLayer = 
		new CMachinePara_Layer(LayerName_Border, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Mark, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Group, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Reserve1, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Reserve2, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	m_LayerCount = LayerNum_Default;
	m_MachineObjList = new CMachineObjList();
	m_ObjBound.min_x = 0;
	m_ObjBound.max_x = 0;
	m_ObjBound.min_y = 0;
	m_ObjBound.max_y = 0;
	m_BorderEmpty = TRUE;
}

CMachineListContainer::~CMachineListContainer()
{
	POSITION pos;
	pos = m_MachineLayerList->GetHeadPosition();
	while (pos != NULL)
	{
		delete m_MachineLayerList->GetNext(pos);
	}
	m_MachineLayerList->RemoveAll();
	delete m_MachineLayerList;
	m_MachineLayerList = NULL;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos != NULL)
	{
		delete m_MachineObjList->GetNext(pos);
	}
	m_MachineObjList->RemoveAll();
	delete m_MachineObjList;
	m_MachineObjList = NULL;
}
// 序列化
void CMachineListContainer::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_LayerCount;
		ar << m_ObjBound.min_x << m_ObjBound.max_x
			<< m_ObjBound.min_y << m_ObjBound.max_y;
		ar << m_BorderEmpty;
		POSITION pos;
		pos = m_MachineLayerList->GetHeadPosition();
		while (pos)
		{
			m_MachineLayerList->GetNext(pos)->Serialize(ar);
		}
		CMachineObj_Comm* pObj;
		pos = m_MachineObjList->GetHeadPosition();
		while (pos)
		{
			pObj = m_MachineObjList->GetNext(pos);
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
		ar << MachineObj_Type_Invaild;
	}
	else
	{
		CMachinePara_Layer* pLayer;
		ar >> m_LayerCount;
		ar >> m_ObjBound.min_x >> m_ObjBound.max_x
			>> m_ObjBound.min_y >> m_ObjBound.max_y;
		ar >> m_BorderEmpty;

		for (int i = 0; i < m_LayerCount; i++)
		{
			pLayer = new CMachinePara_Layer;
			pLayer->Serialize(ar);
			m_MachineLayerList->AddTail(pLayer);
		}
		CMachineObj_Comm* pObj;
		BOOL bValid = TRUE;
		int ObjTyte;
		while (bValid)
		{
			ar >> ObjTyte;
			switch (ObjTyte)
			{
			case MachineObj_Type_Point:
				pObj = new CMachineObjPoint;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Line:
				pObj = new CMachineObjLine;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Circle:
				pObj = new CMachineObjCircle;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Ellipse:
				pObj = new CMachineObjEllipse;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Arc:
				pObj = new CMachineObjArc;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_ArcEll:
				pObj = new CMachineObjArcEll;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_TiltEllipse:
				pObj = new CMachineObjTiltEllipse;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Polyline:
				pObj = new CMachineObjPolyline;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Group:
				pObj = new CMachineObjGroup;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_WLine:
				pObj = new CMachineObjWLine;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_WArc:
				pObj = new CMachineObjWArc;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_WPolyline:
				pObj = new CMachineObjWPolyline;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_FillPolyline:
				pObj = new CMachineObjFillPolyline;
				pObj->Serialize(ar);
				m_MachineObjList->AddTail(pObj);
				break;
			case MachineObj_Type_Invaild:
				bValid = FALSE;
			default:
				bValid = FALSE;
				break;
			}
		}
	}
}


// MachineListContainer 成员函数
// 私有函数
void CMachineListContainer::ReSizeBound(CMachineObj_Comm* MachineObj)
{
	ObjRect ObjBound = MachineObj->GetObjBound();
	if (m_MachineObjList->GetCount() == 1)
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

void CMachineListContainer::ReSizeBound()
{
	CMachineObj_Comm* pObj;
	POSITION pos;
	pos = m_MachineObjList->GetHeadPosition();
	if (!pos)
	{
		m_ObjBound.min_x = 0;
		m_ObjBound.max_x = 0;
		m_ObjBound.min_y = 0;
		m_ObjBound.max_y = 0;
		return;
	}
	pObj = m_MachineObjList->GetNext(pos);
	m_ObjBound = pObj->GetObjBound();
	while (pos)
	{
		pObj = m_MachineObjList->GetNext(pos);
		ReSizeBound(pObj);
	}
	return;
}

BOOL CMachineListContainer::IsObjInLayer(CMachineObj_Comm* pObj, int Layer_Index)
{
	int nLayer = pObj->m_ObjByLayer;
	if (nLayer == Layer_Index)
		return TRUE;
	else if (nLayer != LayerNum_Group)
		return FALSE;
	if (pObj->GetObjType() != MachineObj_Type_Group)
		return TRUE;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	while (pos)
	{
		CMachineObj_Comm* pObj1 = pList->GetNext(pos);
		if (IsObjInLayer(pObj1, Layer_Index))
			return TRUE;
	}
	return FALSE;
}

void CMachineListContainer::ReduceObjLayerAfterIndex(CMachineObj_Comm* pObj, int Lyaer_Index)
{
	if (Lyaer_Index < LayerNum_Default || Lyaer_Index >= m_LayerCount)
		return;
	if (pObj->GetObjType() != MachineObj_Type_Group)
	{
		if (pObj->m_ObjByLayer > Lyaer_Index)
			pObj->m_ObjByLayer--;
		return;
	}
	CMachineObj_Comm* pObj1;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	bool bSingleLayer = true;
	int Count_obj = 0;
	int Old_layer = 0;
	while (pos)
	{
		pObj1 = pList->GetNext(pos);
		ReduceObjLayerAfterIndex(pObj1, Lyaer_Index);
		if (Count_obj == 0)
			Old_layer = pObj1->m_ObjByLayer;
		else if (Old_layer != pObj1->m_ObjByLayer)
			bSingleLayer = false;
		Count_obj++;
	}
	if (bSingleLayer)
#pragma warning(suppress: 6001)
		pObj->m_ObjByLayer = Old_layer;
	return;
}

void CMachineListContainer::ModifyObjByLayer(CMachineObj_Comm* pObj, int Source_Layer, int Dest_Layer)
{
	if (pObj->GetObjType() != MachineObj_Type_Group)
	{
		if (pObj->m_ObjByLayer == Source_Layer)
		{
			pObj->m_ObjByLayer = Dest_Layer;
			return;
		}
		else
			return;
	}
	CMachineObj_Comm* pObj1;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	bool bSingleLayer = true;
	int Count_obj = 0;
	int Old_layer = 0;
	while (pos)
	{
		pObj1 = pList->GetNext(pos);
		ModifyObjByLayer(pObj1, Source_Layer, Dest_Layer);
		if (Count_obj == 0)
			Old_layer = pObj1->m_ObjByLayer;
		else if (Old_layer != pObj1->m_ObjByLayer)
			bSingleLayer = false;
		Count_obj++;
	}
	if (bSingleLayer)
		pObj->m_ObjByLayer = Old_layer;
	return;
}

void CMachineListContainer::ExchangeObjInLayer(CMachineObj_Comm* pObj, int Layer_Index1, int Layer_Index2)
{
	if (pObj->GetObjType() != MachineObj_Type_Group)
	{
		if (pObj->m_ObjByLayer == Layer_Index1)
		{
			pObj->m_ObjByLayer = Layer_Index2;
			return;
		}
		else if (pObj->m_ObjByLayer == Layer_Index2)
		{
			pObj->m_ObjByLayer = Layer_Index1;
			return;
		}
		return;
	}
	CMachineObj_Comm* pObj1;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	bool bSingleLayer = true;
	int Count_obj = 0;
	int Old_layer = 0;
	while (pos)
	{
		pObj1 = pList->GetNext(pos);
		ExchangeObjInLayer(pObj1, Layer_Index1, Layer_Index2);
		if (Count_obj == 0)
			Old_layer = pObj1->m_ObjByLayer;
		else if (Old_layer != pObj1->m_ObjByLayer)
			bSingleLayer = false;
		Count_obj++;
	}
	if (bSingleLayer)
		pObj->m_ObjByLayer = Old_layer;
	return;
}

BOOL CMachineListContainer::DeleteObjInLayer(CMachineObj_Comm* pObj, int Layer_Index)
{
	if (pObj->m_ObjByLayer == Layer_Index)
	{
		delete pObj;
		return TRUE;
	}
	else if (pObj->m_ObjByLayer != LayerNum_Group)
		return FALSE;
	CMachineObj_Comm* pObj1;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	bool bSingleLayer = true;
	int Count_obj = 0;
	int Old_layer = 0;
	while (pos)
	{
		POSITION pos1 = pos;
		pObj1 = pList->GetNext(pos);
		if (DeleteObjInLayer(pObj1, Layer_Index))
		{
			pList->RemoveAt(pos1);
		}
		else
		{
			if (Count_obj == 0)
				Old_layer = pObj1->m_ObjByLayer;
			else if (Old_layer != pObj1->m_ObjByLayer)
				bSingleLayer = false;
			Count_obj++;
		}
	}
	if (bSingleLayer)
		pObj->m_ObjByLayer = Old_layer;
	return FALSE;
}

BOOL CMachineListContainer::DeleteNullObject(CMachineObj_Comm* pObj, int Layer_Index)
{
	int nLayer = pObj->m_ObjByLayer;
	int nType = pObj->GetObjType();
	if (nType != MachineObj_Type_Group)
	{
		if (RectIsNull(pObj->GetObjBound())
			&& (nType != MachineObj_Type_Point)
			&& (nLayer == Layer_Index))
		{
			delete pObj;
			return TRUE;
		}
		else
			return FALSE;
	}
	else if ((nLayer == Layer_Index) && (RectIsNull(pObj->GetObjBound())))
	{
		delete pObj;
		return TRUE;
	}
	else if ((nLayer != Layer_Index) && (nLayer != LayerNum_Group))
		return FALSE;
	CMachineObj_Comm* pObj1;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	bool bSingleLayer = true;
	int Count_obj = 0;
	int Old_layer = 0;
	while (pos)
	{
		POSITION pos1 = pos;
		pObj1 = pList->GetNext(pos);
		if (DeleteNullObject(pObj1, Layer_Index))
		{
			pList->RemoveAt(pos1);
		}
		else
		{
			if (Count_obj == 0)
				Old_layer = pObj1->m_ObjByLayer;
			else if (Old_layer != pObj1->m_ObjByLayer)
				bSingleLayer = false;
			Count_obj++;
		}
	}
	if (pList->IsEmpty())
	{
		delete pObj;
		return TRUE;
	}
	if (bSingleLayer)
		pObj->m_ObjByLayer = Old_layer;
	return FALSE;
}



BOOL CMachineListContainer::GetStartAndEnd(CMachineObj_Comm* pObj,
	ObjPoint* point1, ObjPoint* point2)
{
	if (pObj->GetObjType() == MachineObj_Type_Line)
	{
		CMachineObjLine* pLine = (CMachineObjLine*)pObj;
		*point1 = pLine->GetLineStart();
		*point2 = pLine->GetLineEnd();
		return TRUE;
	}
	if (pObj->GetObjType() == MachineObj_Type_Arc)
	{
		CMachineObjArc* pArc = (CMachineObjArc*)pObj;
		*point1 = pArc->GetArcStart();
		*point2 = pArc->GetArcEnd();
		return TRUE;
	}
	else if(pObj->GetObjType() == MachineObj_Type_Polyline)
	{
		CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj;
		ObjPoint point;
		point.x = pPolyline->GetPolylineStart().x;
		point.y = pPolyline->GetPolylineStart().y;
		*point1 = point;
		point.x = pPolyline->GetPolylineEnd().x;
		point.y = pPolyline->GetPolylineEnd().y;
		*point2 = point;
		return TRUE;
	}
	else
		return FALSE;
}

double CMachineListContainer::CalArcConvex(CMachineObjArc* pObj, BOOL Exchange)
{
	ObjDir dir = pObj->GetArcDir();
	double Angel = (pObj->GetEndAngle() - pObj->GetStartAngle());
	
	if (!Exchange)
		return tan(Angel * M_PI / 720);
	else
		return -tan(Angel * M_PI / 720);
	return 0;
}

BOOL CMachineListContainer::ParallelCheck(ObjPoint point1, ObjPoint point2, ObjPoint point3, ObjPoint point4)
{
	if (abs(point2.x - point1.x) < Zero && abs(point4.x - point3.x) < Zero)
		return TRUE;
	if (abs(abs((point2.y - point1.y) / (point2.x - point1.x)) - abs((point4.y - point3.y) / (point4.x - point3.x))) < Zero)
		return TRUE;
	else
		return FALSE;
}

CMachineObjPolyline* CMachineListContainer::PolymerObj(CMachineObj_Comm* pObj1,
	CMachineObj_Comm* pObj2, BOOL EnNew)
{
	CMachineObjPolyline* pObj;
	ObjVPoint vpoint;
	ObjPoint point1, point2, point11, point12;
	if (!GetStartAndEnd(pObj1, &point1, &point2))
		return FALSE;
	if (!GetStartAndEnd(pObj2, &point11, &point12))
		return FALSE;
	//新建Polyline
	if (EnNew)
	{
		//尾接头 不变向
		if (abs(point2.x - point11.x) < Zero && abs(point2.y - point11.y) < Zero)
		{
			pObj = new CMachineObjPolyline;
			pObj->m_ObjByLayer = pObj1->m_ObjByLayer;
			if (pObj1->GetObjType() == MachineObj_Type_Line)	//Line
			{
				//Line-->Polyline
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Line+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的起终点,Obj2的起终点
					if (!ParallelCheck(point1, point2, point11, point12))
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Line+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Line+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的起终点,Obj2的起点和Obj2的第2节点(顺序号为1)
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					vpoint = pPolyline->GetPolylinePoint(1);
					point12.x = vpoint.x;
					point12.y = vpoint.y;
					if (pPolyline->GetPolylineStart().convexity == 0)
					{
						if (!ParallelCheck(point1, point2, point11, point12))
						{
							vpoint = pPolyline->GetPolylinePoint(0);
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint = pPolyline->GetPolylinePoint(0);
						pObj->AddObjVpoint(vpoint);
					}
					for (int i = 1; i < Count; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(i);
						pObj->AddObjVpoint(vpoint);
					}
					return pObj;
				}
				//Line+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Line end
			else if (pObj1->GetObjType() == MachineObj_Type_Arc)	//Arc
			{
				//Arc-->Polyline
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj1, FALSE);
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Arc+Line
				{
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Arc+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Arc+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					for (int i = 0; i < Count; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(i);
						pObj->AddObjVpoint(vpoint);
					}
					return pObj;
				}
				//Arc+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Arc end
			else if (pObj1->GetObjType() == MachineObj_Type_Polyline)	//Polyline
			{
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj1;
				int Count;
				Count = pPolyline->GetPolylineVertexCount();
				for (int i = 0; i < Count - 1; i++)
				{
					vpoint = pPolyline->GetPolylinePoint(i);
					pObj->AddObjVpoint(vpoint);
				}
				vpoint = pPolyline->GetPolylinePoint(Count - 1);
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Polyline+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的起终点
					point1.x = pPolyline->GetPolylinePoint(Count - 2).x;
					point1.y = pPolyline->GetPolylinePoint(Count - 2).y;
					if (pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
					{
						if (!ParallelCheck(point1, point2, point11, point12))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Polyline+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Polyline+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的起点和第2节点（顺序号为1）
					point1.x = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(Count - 2).x;
					point1.y = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(Count - 2).y;
					if (((CMachineObjPolyline*)pObj1)->GetPolylinePoint(Count - 2).convexity == 0
						&& pPolyline->GetPolylineStart().convexity == 0)
					{
						point12.x = pPolyline->GetPolylinePoint(1).x;
						point12.y = pPolyline->GetPolylinePoint(1).y;
						if (!ParallelCheck(point1, point2, point11, point12))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint = pPolyline->GetPolylineStart();
						pObj->AddObjVpoint(vpoint);
					}
					Count = pPolyline->GetPolylineVertexCount();
					for (int i = 1; i < Count; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(i);
						pObj->AddObjVpoint(vpoint);
					}
					return pObj;
				}
				//Polyline+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Polyline end
			else
			{
				delete pObj;
				return NULL;
			}
			//Invalid
		}
		//尾接尾 第2对象变向
		else if (abs(point2.x - point12.x) < Zero && abs(point2.y - point12.y) < Zero)
		{
			pObj = new CMachineObjPolyline;
			pObj->m_ObjByLayer = pObj1->m_ObjByLayer;
			if (pObj1->GetObjType() == MachineObj_Type_Line)	//Line
			{
				//Line-->Polyline
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Line+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的起终点,Obj2的终起点
					if (!ParallelCheck(point1, point2, point12, point11))
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Line+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Line+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的起终点,Obj2的终点和倒数第2节点
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					point11.x = pPolyline->GetPolylinePoint(Count - 2).x;
					point11.y = pPolyline->GetPolylinePoint(Count - 2).y;
					if (pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
					{
						if (!ParallelCheck(point1, point2, point12, point11))
						{
							vpoint = pPolyline->GetPolylinePoint(Count - 1);
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					for (int i = 1; i < Count - 1; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint = pPolyline->GetPolylinePoint(0);
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Line end
			else if (pObj1->GetObjType() == MachineObj_Type_Arc)	//Arc
			{
				//Arc-->Polyline
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj1, FALSE);
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Arc+Line
				{
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Arc+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Arc+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					for (int i = 0; i < Count - 1; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Arc end
			else if (pObj1->GetObjType() == MachineObj_Type_Polyline)	//Polyline
			{
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj1;
				int Count, Count1;
				Count = pPolyline->GetPolylineVertexCount();
				for (int i = 0; i < Count - 1; i++)
				{
					vpoint = pPolyline->GetPolylinePoint(i);
					pObj->AddObjVpoint(vpoint);
				}
				vpoint = pPolyline->GetPolylinePoint(Count - 1);
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Polyline+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的终起点
					point1.x = pPolyline->GetPolylinePoint(Count - 2).x;
					point1.y = pPolyline->GetPolylinePoint(Count - 2).y;
					if (pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
					{
						if (!ParallelCheck(point1, point2, point12, point11))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Polyline+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Polyline+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的终点和倒数第2节点
					point1.x = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(Count - 2).x;
					point1.y = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(Count - 2).y;
					Count1 = Count;
					Count = pPolyline->GetPolylineVertexCount();
					if (((CMachineObjPolyline*)pObj1)->GetPolylinePoint(Count1 - 2).convexity == 0
						&& pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
					{
						point11.x = pPolyline->GetPolylinePoint(Count - 2).x;
						point11.y = pPolyline->GetPolylinePoint(Count - 2).y;
						if (!ParallelCheck(point1, point2, point12, point11))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					for (int i = 1; i < Count - 1; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint = pPolyline->GetPolylinePoint(0);
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Polyline end
			else
			{
				delete pObj;
				return NULL;
			}
			//Invalid
		}
		//头接头 第1对象变向
		else if (abs(point1.x - point11.x) < Zero && abs(point1.y - point11.y) < Zero)
		{
			pObj = new CMachineObjPolyline;
			pObj->m_ObjByLayer = pObj1->m_ObjByLayer;
			if (pObj1->GetObjType() == MachineObj_Type_Line)	//Line
			{
				//Line-->Polyline
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Line+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的终起点,Obj2的起终点
					if (!ParallelCheck(point2, point1, point11, point12))
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Line+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Line+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的终起点,Obj2的起点和Obj2的第2节点(顺序号为1)
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					vpoint = pPolyline->GetPolylinePoint(1);
					point12.x = vpoint.x;
					point12.y = vpoint.y;
					if (pPolyline->GetPolylineStart().convexity == 0)
					{
						if (!ParallelCheck(point2, point1, point11, point12))
						{
							vpoint = pPolyline->GetPolylineStart();
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint = pPolyline->GetPolylineStart();
						pObj->AddObjVpoint(vpoint);
					}
					Count = pPolyline->GetPolylineVertexCount();
					for (int i = 1; i < Count; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(i);
						pObj->AddObjVpoint(vpoint);
					}
					return pObj;
				}
				//Line+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Line end
			else if (pObj1->GetObjType() == MachineObj_Type_Arc)	//Arc
			{
				//Arc-->Polyline
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj1, TRUE);
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Arc+Line
				{
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Arc+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Arc+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					for (int i = 0; i < Count; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(i);
						pObj->AddObjVpoint(vpoint);
					}
					return pObj;
				}
				//Arc+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Arc end
			else if (pObj1->GetObjType() == MachineObj_Type_Polyline)	//Polyline
			{
				//Polyline 换向
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj1;
				int Count;
				Count = pPolyline->GetPolylineVertexCount();
				for (int i = 0; i < Count - 1; i++)
				{
					vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
					vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
					pObj->AddObjVpoint(vpoint);
				}
				vpoint = pPolyline->GetPolylinePoint(0);
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Polyline+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的第2点和起点,Obj2的起终点
					point2.x = pPolyline->GetPolylinePoint(1).x;
					point2.y = pPolyline->GetPolylinePoint(1).y;
					if (pPolyline->GetPolylineStart().convexity == 0)
					{
						if (!ParallelCheck(point2, point1, point11, point12))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Polyline+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Polyline+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的第2点和起点,Obj2的起点和第2点
					point2.x = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(1).x;
					point2.y = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(1).y;
					Count = pPolyline->GetPolylineVertexCount();
					if (((CMachineObjPolyline*)pObj1)->GetPolylineStart().convexity == 0
						&& pPolyline->GetPolylineStart().convexity == 0)
					{
						point12.x = pPolyline->GetPolylinePoint(1).x;
						point12.y = pPolyline->GetPolylinePoint(1).y;
						if (!ParallelCheck(point2, point1, point11, point12))
						{
							vpoint = pPolyline->GetPolylineStart();
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint = pPolyline->GetPolylineStart();
						pObj->AddObjVpoint(vpoint);
					}
					for (int i = 1; i < Count; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(i);
						pObj->AddObjVpoint(vpoint);
					}
					return pObj;
				}
				//Polyline+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Polyline end
			else
			{
				delete pObj;
				return NULL;
			}
			//Invalid
		}
		//头接尾 全换向
		else if (abs(point1.x - point12.x) < Zero && abs(point1.y - point12.y) < Zero)
		{
			pObj = new CMachineObjPolyline;
			pObj->m_ObjByLayer = pObj1->m_ObjByLayer;
			if (pObj1->GetObjType() == MachineObj_Type_Line)	//Line
			{
				//Line-->Polyline
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Line+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的终起点,Obj2的终起点
					if (!ParallelCheck(point2, point1, point12, point11))
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Line+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Line+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的终起点,Obj2的终点和倒数第2节点
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					point11.x = pPolyline->GetPolylinePoint(Count - 2).x;
					point11.y = pPolyline->GetPolylinePoint(Count - 2).y;
					if (pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
					{
						if (!ParallelCheck(point2, point1, point12, point11))
						{
							vpoint = pPolyline->GetPolylinePoint(Count - 1);
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					for (int i = 1; i < Count - 1; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint = pPolyline->GetPolylinePoint(0);
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Line+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Line end
			else if (pObj1->GetObjType() == MachineObj_Type_Arc)	//Arc
			{
				//Arc-->Polyline
				vpoint.x = point2.x;
				vpoint.y = point2.y;
				vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj1, TRUE);
				pObj->AddObjVpoint(vpoint);
				vpoint.x = point1.x;
				vpoint.y = point1.y;
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Arc+Line
				{
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Arc+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Arc+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					int Count;
					Count = pPolyline->GetPolylineVertexCount();
					for (int i = 0; i < Count - 1; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint = pPolyline->GetPolylinePoint(0);
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Arc+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Arc end
			else if (pObj1->GetObjType() == MachineObj_Type_Polyline)	//Polyline
			{
				//Polyline 换向
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj1;
				int Count;
				Count = pPolyline->GetPolylineVertexCount();
				for (int i = 0; i < Count - 1; i++)
				{
					vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
					vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
					pObj->AddObjVpoint(vpoint);
				}
				vpoint = pPolyline->GetPolylinePoint(0);
				if (pObj2->GetObjType() == MachineObj_Type_Line)	//Polyline+Line
				{
					//消掉同向直线上的中间点,被检测点为Obj1的第2点和起点,Obj2的终起点
					point2.x = pPolyline->GetPolylinePoint(1).x;
					point2.y = pPolyline->GetPolylinePoint(1).y;
					if (pPolyline->GetPolylineStart().convexity == 0)
					{
						if (!ParallelCheck(point2, point1, point12, point11))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					///////////////////////////////////
					//					vpoint.convexity = 0;
					//					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Line end
				else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//Polyline+Arc
				{
					vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
					pObj->AddObjVpoint(vpoint);
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Arc end
				else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//Polyline+Polyline
				{
					CMachineObjPolyline* pPolyline;
					pPolyline = (CMachineObjPolyline*)pObj2;
					//消掉同向直线上的中间点,被检测点为Obj1的第2点和起点,Obj2的终点和倒数第2点
					point2.x = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(1).x;
					point2.y = ((CMachineObjPolyline*)pObj1)->GetPolylinePoint(1).y;
					Count = pPolyline->GetPolylineVertexCount();
					if (((CMachineObjPolyline*)pObj1)->GetPolylinePoint(0).convexity == 0
						&& pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
					{
						point11.x = pPolyline->GetPolylinePoint(Count - 2).x;
						point11.y = pPolyline->GetPolylinePoint(Count - 2).y;
						if (!ParallelCheck(point2, point1, point12, point11))
						{
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					for (int i = 1; i < Count - 1; i++)
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
						pObj->AddObjVpoint(vpoint);
					}
					vpoint = pPolyline->GetPolylinePoint(0);
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
					return pObj;
				}
				//Polyline+Polyline end
				else
				{
					delete pObj;
					return NULL;
				}
				//Invalid
			}
			//Polyline end
			else
			{
				delete pObj;
				return NULL;
			}
			//Invalid
		}
		//不相连
		else
			return NULL;
	}
	//在原Polyline后加对象
	else
	{
		if (pObj1->GetObjType() != MachineObj_Type_Polyline)
			return NULL;
		//尾接头
		if (abs(point2.x - point11.x) < Zero && abs(point2.y - point11.y) < Zero)
		{
			pObj = (CMachineObjPolyline*)pObj1;
			int Count;
			Count = pObj->GetPolylineVertexCount();
			if (pObj2->GetObjType() == MachineObj_Type_Line)	//pPolyline+Line
			{
				//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的起终点
				point1.x = pObj->GetPolylinePoint(Count - 2).x;
				point1.y = pObj->GetPolylinePoint(Count - 2).y;
				if (pObj->GetPolylinePoint(Count - 2).convexity == 0)
				{
					if (!ParallelCheck(point1, point2, point11, point12))
					{
						vpoint.x = point12.x;
						vpoint.y = point12.y;
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					else
					{
						vpoint = pObj->GetPolylineEnd();
						vpoint.x = point12.x;
						vpoint.y = point12.y;
						vpoint.convexity = 0;
						pObj->ChangeLastVpoint(vpoint);
					}
				}
				else
				{
					vpoint.x = point12.x;
					vpoint.y = point12.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
				}
				return pObj;
			}
			//pPolyline+Line end
			else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//pPolyline+Arc
			{
				vpoint = pObj->GetPolylineEnd();
				vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, FALSE);
				pObj->ChangeLastVpoint(vpoint);
				vpoint.x = point12.x;
				vpoint.y = point12.y;
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				return pObj;
			}
			//pPolyline+Arc end
			else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//pPolyline+Polyline
			{
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj2;
				//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的起点和第2节点
				point1.x = pObj->GetPolylinePoint(Count - 2).x;
				point1.y = pObj->GetPolylinePoint(Count - 2).y;
				if (pObj->GetPolylinePoint(Count - 2).convexity == 0
					&& pPolyline->GetPolylineStart().convexity == 0)
				{
					point12.x = pPolyline->GetPolylinePoint(1).x;
					point12.y = pPolyline->GetPolylinePoint(1).y;
					if (!ParallelCheck(point1, point2, point11, point12))
					{
						vpoint = pPolyline->GetPolylineStart();
						pObj->ChangeLastVpoint(vpoint);
						vpoint = pPolyline->GetPolylinePoint(1);
						pObj->AddObjVpoint(vpoint);
					}
					else
					{
						vpoint = pPolyline->GetPolylinePoint(1);
						pObj->ChangeLastVpoint(vpoint);
					}
				}
				else
				{
					vpoint = pPolyline->GetPolylineStart();
					pObj->ChangeLastVpoint(vpoint);
					vpoint = pPolyline->GetPolylinePoint(1);
					pObj->AddObjVpoint(vpoint);
				}
				Count = pPolyline->GetPolylineVertexCount();
				for (int i = 2; i < Count; i++)
				{
					vpoint = pPolyline->GetPolylinePoint(i);
					pObj->AddObjVpoint(vpoint);
				}
				return pObj;
			}
			//pPolyline+Polyline end
			else
			{
				return NULL;
			}
			//Invalid
		}
		//尾接尾
		else if (abs(point2.x - point12.x) < Zero && abs(point2.y - point12.y) < Zero)
		{
			pObj = (CMachineObjPolyline*)pObj1;
			int Count;
			Count = pObj->GetPolylineVertexCount();
			if (pObj2->GetObjType() == MachineObj_Type_Line)	//pPolyline+Line
			{
				//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的终起点
				point1.x = pObj->GetPolylinePoint(Count - 2).x;
				point1.y = pObj->GetPolylinePoint(Count - 2).y;
				if (pObj->GetPolylinePoint(Count - 2).convexity == 0)
				{
					if (!ParallelCheck(point1, point2, point12, point11))
					{
						vpoint.x = point11.x;
						vpoint.y = point11.y;
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
					}
					else
					{
						vpoint.x = point11.x;
						vpoint.y = point11.y;
						vpoint.convexity = 0;
						pObj->ChangeLastVpoint(vpoint);
					}
				}
				else
				{
					vpoint.x = point11.x;
					vpoint.y = point11.y;
					vpoint.convexity = 0;
					pObj->AddObjVpoint(vpoint);
				}
				return pObj;
			}
			//pPolyline+Line end
			else if (pObj2->GetObjType() == MachineObj_Type_Arc)	//pPolyline+Arc
			{
				vpoint = pObj->GetPolylinePoint(Count - 1);
				vpoint.convexity = CalArcConvex((CMachineObjArc*)pObj2, TRUE);
				pObj->ChangeLastVpoint(vpoint);
				vpoint.x = point11.x;
				vpoint.y = point11.y;
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				return pObj;
			}
			//pPolyline+Arc end
			else if (pObj2->GetObjType() == MachineObj_Type_Polyline)	//pPolyline+Polyline
			{
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj2;
				//消掉同向直线上的中间点,被检测点为Obj1的倒数第2节点和终点,Obj2的终点和倒数第2节点
				point1.x = pObj->GetPolylinePoint(Count - 2).x;
				point1.y = pObj->GetPolylinePoint(Count - 2).y;
				Count = pPolyline->GetPolylineVertexCount();
				if (pObj->GetPolylinePoint(Count - 2).convexity == 0
					&& pPolyline->GetPolylinePoint(Count - 2).convexity == 0)
				{
					point11.x = pPolyline->GetPolylinePoint(Count - 2).x;
					point11.y = pPolyline->GetPolylinePoint(Count - 2).y;
					if (!ParallelCheck(point1, point2, point12, point11))
					{
						vpoint = pPolyline->GetPolylineEnd();
						vpoint.convexity = 0;
						pObj->ChangeLastVpoint(vpoint);
						if (Count < 3)
						{
							vpoint = pPolyline->GetPolylinePoint(0);
							vpoint.convexity = 0;
							pObj->AddObjVpoint(vpoint);
							return pObj;
						}
						else
						{
							vpoint = pPolyline->GetPolylinePoint(Count - 2);
							vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 3).convexity;
							pObj->AddObjVpoint(vpoint);
						}
					}
					else
					{
						if (Count < 3)
						{
							vpoint = pPolyline->GetPolylinePoint(0);
							vpoint.convexity = 0;
							pObj->ChangeLastVpoint(vpoint);
							return pObj;
						}
						else
						{
							vpoint = pPolyline->GetPolylinePoint(Count - 2);
							vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 3).convexity;
							pObj->ChangeLastVpoint(vpoint);
						}
					}
				}
				else
				{
					vpoint = pPolyline->GetPolylineEnd();
					vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2).convexity;
					pObj->ChangeLastVpoint(vpoint);
					if (Count < 3)
					{
						vpoint = pPolyline->GetPolylinePoint(0);
						vpoint.convexity = 0;
						pObj->AddObjVpoint(vpoint);
						return pObj;
					}
					else
					{
						vpoint = pPolyline->GetPolylinePoint(Count - 2);
						vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 3).convexity;
						pObj->AddObjVpoint(vpoint);
					}
				}
				for (int i = 2; i < Count - 1; i++)
				{
					vpoint = pPolyline->GetPolylinePoint(Count - 1 - i);
					vpoint.convexity = -pPolyline->GetPolylinePoint(Count - 2 - i).convexity;
					pObj->AddObjVpoint(vpoint);
				}
				vpoint = pPolyline->GetPolylinePoint(0);
				vpoint.convexity = 0;
				pObj->AddObjVpoint(vpoint);
				return pObj;
			}
			//pPolyline+Polyline
			else
			{
				return NULL;
			}
			//Invalid
		}
		//不相连
		else
			return NULL;
	}
	return NULL;
}

double CMachineListContainer::CalDirAngle(ObjPoint point1, ObjPoint point2)
{
	if (point2.x - point1.x > 0)
	{
		return atan((point2.y - point1.y) / (point2.x - point1.x));
	}
	else if(point2.x - point1.x < 0)
	{
		return atan((point2.y - point1.y) / (point2.x - point1.x)) + M_PI;
	}
	else
	{
		if (point2.y > point1.y)
			return M_PI_2;
		else
			return M_PI + M_PI_2;
	}
}

void CMachineListContainer::CalArrow(ObjPoint point, double dirAngle, float ZoomFactor,
	ObjPoint* point1, ObjPoint* point2)
{
	double radian = (double)ArrowAngle / 180 * M_PI;
	float len = ArrowLen / sqrt(ZoomFactor) / 1000;
	(*point1).x = point.x - len * cos(dirAngle - radian);
	(*point1).y = point.y - len * sin(dirAngle - radian);
	(*point2).x = point.x - len * cos(dirAngle + radian);
	(*point2).y = point.y - len * sin(dirAngle + radian);
}

BOOL CMachineListContainer::IntersectBound(ObjRect bound1, ObjRect bound2)
{
	if (bound1.max_x<bound2.min_x
		|| bound1.min_x>bound2.max_x
		|| bound1.max_y<bound2.min_y
		|| bound1.min_y>bound2.max_y)
		return FALSE;
	else
		return TRUE;
}

BOOL CMachineListContainer::ISIncludeBound(ObjRect bound1, ObjRect bound2)
{
	if (bound1.max_x >= bound2.max_x
		&& bound1.min_x <= bound2.min_x
		&& bound1.max_y >= bound2.max_y
		&& bound1.min_y <= bound2.min_y)
		return TRUE;
	else
		return FALSE;
}

BOOL CMachineListContainer::IsObjActive(CMachineObj_Comm* pObj)
{
	byte status = pObj->m_bIsObjStatus;
	if ((status & IsObjClosed) != 0 || (status & IsObjLocked) != 0)
		return FALSE;
	int nLayer = pObj->m_ObjByLayer;
	status = GetLayerOfNumber(nLayer)->m_bIsLayerStatus;
	if ((status & IsObjClosed) != 0 || (status & IsObjLocked) != 0)
		return FALSE;
	return TRUE;
}

byte CMachineListContainer::PickObjPoint(CMachineObjPoint* pPoint, ObjPoint point, float BoxSize)
{
	
	if (abs(pPoint->GetPoint().x - point.x) <= BoxSize
		&& abs(pPoint->GetPoint().y - point.y) <= BoxSize)
	{
		pPoint->m_bIsObjStatus = pPoint->m_bIsObjStatus | IsObjSel;
		return IsObjSel;
	}
	else
		return IsObjNormal;
}

byte CMachineListContainer::PickObjLine(CMachineObjLine* pLine, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pLine->GetObjBound(), rc1))
		return IsObjNormal;
	ObjPoint point1, point2;
	point1 = pLine->GetLineStart();
	point2 = pLine->GetLineEnd();
	if (point1.x == point2.x)
	{
		if (abs(point.x - point1.x) <= BoxSize)
		{
			pLine->m_bIsObjStatus = pLine->m_bIsObjStatus | IsObjSel;
			return IsObjSel;
		}
		else
			return IsObjNormal;
	}
	else if (point1.y == point2.y)
	{
		if (abs(point.y - point1.y) <= BoxSize)
		{
			pLine->m_bIsObjStatus = pLine->m_bIsObjStatus | IsObjSel;
			return IsObjSel;
		}
		else
			return IsObjNormal;
	}
	else
	{
		double A = (point2.y - point1.y) / (point2.x - point1.x);
		double d = abs(A * point.x - point.y + point1.y - A * point1.x) / sqrt(A*A + 1);
		if (d <= BoxSize)
		{
			pLine->m_bIsObjStatus = pLine->m_bIsObjStatus | IsObjSel;
			return IsObjSel;
		}
		else
			return IsObjNormal;
	}
}

byte CMachineListContainer::PickObjCircle(CMachineObjCircle* pCircle, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pCircle->GetObjBound(), rc1))
		return IsObjNormal;
	ObjPoint point1;
	point1 = pCircle->GetCircleCenter();
	double d = sqrt((point.x - point1.x)*(point.x - point1.x) + (point.y - point1.y)*(point.y - point1.y));
	double r = pCircle->GetCircleRadius();
	if (abs(d - r) <= BoxSize)
	{
		pCircle->m_bIsObjStatus = pCircle->m_bIsObjStatus | IsObjSel;
		return IsObjSel;
	}
	else
		return IsObjNormal;
}

byte CMachineListContainer::PickObjArc(CMachineObjArc* pArc, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pArc->GetObjBound(), rc1))
		return IsObjNormal;
	ObjPoint point1;
	double Angle, Angle1, Angle2;
	point1 = pArc->GetArcCenter();
	Angle1 = pArc->GetStartAngle();
	Angle2 = pArc->GetEndAngle();
	if (point.x == point1.x)
	{
		if (point.y >= point1.y)
			Angle = 90;
		else
			Angle = 270;
	}
	else
	{
		Angle = atan((point.y - point1.y) / (point.x - point1.x)) / M_PI * 180;
		if (point.x < point1.x)
			Angle += 180;
	}
	if (pArc->GetArcDir() == CCW)
	{
		if (Angle<Angle1 && Angle>Angle2)
			return IsObjNormal;
	}
	else
	{
		if (Angle>Angle1 && Angle < Angle2)
			return IsObjNormal;
	}
	double d = sqrt((point.x - point1.x)*(point.x - point1.x) + (point.y - point1.y)*(point.y - point1.y));
	double r = pArc->GetArcRadius();
	if (abs(d - r) <= BoxSize)
	{
		pArc->m_bIsObjStatus = pArc->m_bIsObjStatus | IsObjSel;
		return IsObjSel;
	}
	else
		return IsObjNormal;
}

double CMachineListContainer::CalRadianPointToPoint(ObjPoint point1, ObjPoint point2)
{
	double Radian;
	if (point2.x == point1.x)
	{
		if (point2.y >= point1.y)
			Radian = M_PI_2;
		else
			Radian = M_PI + M_PI_2;
	}
	else
	{
		Radian = atan((point2.y - point1.y) / (point2.x - point1.x));
		if (point2.x < point1.x)
			Radian += M_PI;
	}
	if (Radian < 0)
		Radian += 2 * M_PI;
	return Radian;
}

byte CMachineListContainer::PickObjEllipse(CMachineObjEllipse* pEllipse, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pEllipse->GetObjBound(), rc1))
		return IsObjNormal;
	ObjPoint point1;
	double Radian, a, b, r;
	point1 = pEllipse->GetEllipseCenter();
	Radian = CalRadianPointToPoint(point1, point);
	a = pEllipse->GetEllipseXRadius();
	b = pEllipse->GetEllipseYRadius();
	if (Radian == M_PI_2 || Radian == (M_PI + M_PI_2))
	{
		if ((abs(point.y - point1.y) - b) <= BoxSize)
		{
			pEllipse->m_bIsObjStatus = pEllipse->m_bIsObjStatus | IsObjSel;
			return IsObjSel;
		}
		else
			return IsObjNormal;
	}
	r = tan(Radian);
	r = a*b*sqrt((1 + r*r) / (b*b + r*a*r*a));
	double d = sqrt((point.x - point1.x)*(point.x - point1.x) + (point.y - point1.y)*(point.y - point1.y));
	if (abs(d - r) <= BoxSize)
	{
		pEllipse->m_bIsObjStatus = pEllipse->m_bIsObjStatus | IsObjSel;
		return IsObjSel;
	}
	else
		return IsObjNormal;
}

byte CMachineListContainer::PickObjArcEll(CMachineObjArcEll* pArcEll, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pArcEll->GetObjBound(), rc1))
		return IsObjNormal;
	ObjPoint point1, point2;
	double Radian, a, b, r;
	point1 = pArcEll->GetEllipseCenter();
	Radian = CalRadianPointToPoint(point1, point);
	point2 = pArcEll->GetArcStart();
	a = CalRadianPointToPoint(point1, point2);
	point2 = pArcEll->GetArcEnd();
	b = CalRadianPointToPoint(point1, point2);
	if (pArcEll->GetArcDir() == CCW)
	{
		if (b < a)
			a -= 2 * M_PI;
		if (a <= 0 && b <= 0)
		{
			a += 2 * M_PI;
			b += 2 * M_PI;
		}
		if (Radian < a && Radian > b)
			return IsObjNormal;
	}
	else
	{
		if (b > a)
			b -= 2 * M_PI;
		if (a <= 0 && b <= 0)
		{
			a += 2 * M_PI;
			b += 2 * M_PI;
		}
		if (Radian > a && Radian < b)
			return IsObjNormal;
	}
	a = pArcEll->GetEllipseXRadius();
	b = pArcEll->GetEllipseYRadius();
	if (Radian == M_PI_2 || Radian == (M_PI + M_PI_2))
	{
		if ((abs(point.y - point1.y) - b) <= BoxSize)
		{
			pArcEll->m_bIsObjStatus = pArcEll->m_bIsObjStatus | IsObjSel;
			return IsObjSel;
		}
		else
			return IsObjNormal;
	}
	r = tan(Radian);
	r = a*b*sqrt((1 + r*r) / (b*b + r*a*r*a));
	double d = sqrt((point.x - point1.x)*(point.x - point1.x) + (point.y - point1.y)*(point.y - point1.y));
	if (abs(d - r) <= BoxSize)
	{
		pArcEll->m_bIsObjStatus = pArcEll->m_bIsObjStatus | IsObjSel;
		return IsObjSel;
	}
	else
		return IsObjNormal;
}

byte CMachineListContainer::PickObjTiltEllArc(CMachineObjTiltEllipse* pTiltEllArc, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pTiltEllArc->GetObjBound(), rc1))
		return IsObjNormal;
	double Radian, a, b;
	ObjPoint point1;
	point1 = pTiltEllArc->GetTiltEllipseCenter();
	Radian = CalRadianPointToPoint(point1, point);
	a = pTiltEllArc->CalAbsStartRadian();
	b = pTiltEllArc->CalAbsEndRadian();
	if (pTiltEllArc->GetArcDir() == CCW)
	{
		if (b < a)
			a -= 2 * M_PI;
		if (a <= 0 && b <= 0)
		{
			a += 2 * M_PI;
			b += 2 * M_PI;
		}
		if (Radian < a && Radian > b)
			return IsObjNormal;
	}
	else
	{
		if (b > a)
			b -= 2 * M_PI;
		if (a <= 0 && b <= 0)
		{
			a += 2 * M_PI;
			b += 2 * M_PI;
		}
		if (Radian > a && Radian < b)
			return IsObjNormal;
	}
	double d = pTiltEllArc->CalDistance(point);
	if (d <= BoxSize)
	{
		pTiltEllArc->m_bIsObjStatus = pTiltEllArc->m_bIsObjStatus | IsObjSel;
		return IsObjSel;
	}
	else
		return IsObjNormal;
}

byte CMachineListContainer::PickObjPolyline(CMachineObjPolyline* pPolyline, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pPolyline->GetObjBound(), rc1))
		return IsObjNormal;
	ObjPoint point1, point2;
	ObjVPoint vpoint1, vpoint2;
	CMachineObjLine* pLine;
	CMachineObjArc* pArc;
	double convexity;
	BOOL IsSelected;
	int Count = pPolyline->GetPolylineVertexCount();
	vpoint1 = pPolyline->GetPolylineStart();
	for (int i = 1; i < Count; i++)
	{
		vpoint2 = pPolyline->GetPolylinePoint(i);
		if (vpoint1.convexity == 0)
		{
			point1.x = vpoint1.x;
			point1.y = vpoint1.y;
			point2.x = vpoint2.x;
			point2.y = vpoint2.y;
			pLine = new CMachineObjLine(point1, point2);
			IsSelected = PickObjLine(pLine, point, BoxSize);
			delete pLine;
			if (IsSelected)
			{
				pPolyline->m_bIsObjStatus = pPolyline->m_bIsObjStatus | IsObjSel;
				return IsObjSel;
			}
			vpoint1 = vpoint2;
		}
		else
		{
			point1.x = vpoint1.x;
			point1.y = vpoint1.y;
			point2.x = vpoint2.x;
			point2.y = vpoint2.y;
			convexity = vpoint1.convexity;
			pArc = pPolyline->TranPolylineToArc(point1, point2, convexity);
			IsSelected = PickObjArc(pArc, point, BoxSize);
			delete pArc;
			if (IsSelected)
			{
				pPolyline->m_bIsObjStatus = pPolyline->m_bIsObjStatus | IsObjSel;
				return IsObjSel;
			}
			vpoint1 = vpoint2;
		}
	}
	return IsObjNormal;
}

byte CMachineListContainer::PickObjGroup(CMachineObjGroup* pGroup, ObjPoint point, float BoxSize)
{
	ObjRect rc1;
	rc1.min_x = point.x - BoxSize;
	rc1.max_x = point.x + BoxSize;
	rc1.min_y = point.y - BoxSize;
	rc1.max_y = point.y + BoxSize;
	if (!IntersectBound(pGroup->GetObjBound(), rc1))
		return IsObjNormal;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos;
	pos = pList->GetHeadPosition();
	BOOL select;
	while (pos)
	{
		CMachineObj_Comm* pObj;
		pObj = pList->GetNext(pos);
		select = PickObject(pObj, point, BoxSize);
		if (select)
		{
			pObj->m_bIsObjStatus &= ~IsObjSel;
			pGroup->m_bIsObjStatus |= IsObjSel;
			return IsObjSel;
		}
	}
	return IsObjNormal;
}

byte CMachineListContainer::PickObject(CMachineObj_Comm* pObj, ObjPoint point, float BoxSize, byte Sel)
{
	int type = pObj->GetObjType();
	BOOL select = IsObjNormal;
	////2021.02.03新加
	//byte status = pObj->m_bIsObjStatus;
	//if ((status & IsObjClosed) != 0 || (status & IsObjLocked) != 0)
	//	return IsObjNormal;
	//int nLayer = pObj->m_ObjByLayer;
	//status = GetLayerOfNumber(nLayer)->m_bIsLayerStatus;
	//if ((status & IsObjClosed) != 0 || (status & IsObjLocked) != 0)
	//	return IsObjNormal;
	////*****
	if (!IsObjActive(pObj))
		return IsObjNormal;
	switch (type)
	{
	case MachineObj_Type_Point:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjPoint((CMachineObjPoint*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_Line:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjLine((CMachineObjLine*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_Circle:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjCircle((CMachineObjCircle*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_Arc:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjArc((CMachineObjArc*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_Ellipse:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjEllipse((CMachineObjEllipse*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_ArcEll:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjArcEll((CMachineObjArcEll*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_TiltEllipse:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjTiltEllArc((CMachineObjTiltEllipse*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_Polyline:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjPolyline((CMachineObjPolyline*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_Group:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjGroup((CMachineObjGroup*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_WLine:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjLine((CMachineObjLine*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_WArc:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjArc((CMachineObjArc*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_WPolyline:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjPolyline((CMachineObjPolyline*)pObj, point, BoxSize);
		break;
	case MachineObj_Type_FillPolyline:
		select = pObj->m_bIsObjStatus | Sel;
		if (select)
			return IsObjNormal;
		select = PickObjPolyline((CMachineObjPolyline*)pObj, point, BoxSize);
		break;
	default:
		select = IsObjNormal;
		break;
	}
	return select;
}


// 公开函数
void CMachineListContainer::ClearAllObj()
{
	ClearAll();
	CMachinePara_Layer* pLayer =
		new CMachinePara_Layer(LayerName_Border, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Mark, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Group, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Reserve1, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	pLayer = new CMachinePara_Layer(LayerName_Reserve2, -1, m_MachineParaDefault, 0);
	m_MachineLayerList->AddTail(pLayer);
	m_LayerCount = LayerNum_Default;
}

void CMachineListContainer::ClearAll()
{
	POSITION pos;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		delete m_MachineObjList->GetNext(pos);
	}
	m_MachineObjList->RemoveAll();
	while (m_LayerCount > 0)
	{
		delete m_MachineLayerList->GetTail();
		m_MachineLayerList->RemoveTail();
		m_LayerCount--;
	}
	m_ObjBound.min_x = 0;
	m_ObjBound.max_x = 0;
	m_ObjBound.min_y = 0;
	m_ObjBound.max_y = 0;
}

void CMachineListContainer::ClearNullLayer()
{
	POSITION pos;
	CMachineObj_Comm* pObj;
	CMachinePara_Layer* pLayer;
	BOOL bEmpty;
	for (int i = LayerNum_Default; i < m_LayerCount; i++)
	{
		pos = m_MachineObjList->GetHeadPosition();
		bEmpty = TRUE;
		while (pos)
		{
			pObj = m_MachineObjList->GetNext(pos);
			if (IsObjInLayer(pObj, i))
				bEmpty = FALSE;
		}
		if (bEmpty)
		{
			pos = m_MachineObjList->GetHeadPosition();
			while (pos)
			{
				pObj = m_MachineObjList->GetNext(pos);
				ReduceObjLayerAfterIndex(pObj, i);
			}
			pos = m_MachineLayerList->FindIndex(i);
			pLayer = m_MachineLayerList->GetAt(pos);
			delete pLayer;
			m_MachineLayerList->RemoveAt(pos);
			m_LayerCount--;
		}
	}
}

void CMachineListContainer::ClearNullObject(int Layer_Index)
{
	POSITION pos;
	CMachineObj_Comm* pObj;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		POSITION pos1 = pos;
		pObj = m_MachineObjList->GetNext(pos);
		if (DeleteNullObject(pObj, Layer_Index))
		{
			m_MachineObjList->RemoveAt(pos1);
		}
	}
}

void CMachineListContainer::ClearNullObject()
{
	int nCount = this->m_LayerCount;
	for (int i = 0; i < nCount; i++)
	{
		ClearNullObject(i);
	}
}

void CMachineListContainer::SetObjSelect(int nIndex, bool sel)
{
	POSITION pos;
	if (nIndex >= m_MachineObjList->GetCount())
		return;
	pos = m_MachineObjList->FindIndex(nIndex);
	if (sel)
		m_MachineObjList->GetAt(pos)->m_bIsObjStatus |= IsObjSel;
	else
		m_MachineObjList->GetAt(pos)->m_bIsObjStatus &= ~IsObjSel;
}

void CMachineListContainer::SetObjUnSelectAll()
{
	POSITION pos;
	CMachineObj_Comm* pObj;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		pObj = m_MachineObjList->GetNext(pos);
		pObj->m_bIsObjStatus &= ~IsObjSel;
	}
	SetLayerUnSelectAll();
}

void CMachineListContainer::SetLayerUnSelectAll()
{
	POSITION pos;
	CMachinePara_Layer* pLayer;
	pos = m_MachineLayerList->GetHeadPosition();
	while (pos)
	{
		pLayer = m_MachineLayerList->GetNext(pos);
		byte LayerStatus = pLayer->m_bIsLayerStatus;
		pLayer->m_bIsLayerStatus = LayerStatus & ~IsObjSel;
	}
}

BOOL CMachineListContainer::MoveObjUp(int nIndex)
{
	POSITION pos, pos1;
	CMachineObj_Comm* pObj;
	int bordermax, markmax;
	bordermax = 0;
	markmax = 0;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		int n = m_MachineObjList->GetNext(pos)->m_ObjByLayer;
		if (n == 0)
			bordermax++;
		else if (n == 1)
			markmax++;
		else
			break;
	}
	if (nIndex == 0 || nIndex == bordermax || nIndex == (markmax + bordermax))
		return FALSE;
	pos = m_MachineObjList->FindIndex(nIndex - 1);
	pos1 = m_MachineObjList->FindIndex(nIndex);
	pObj = m_MachineObjList->GetAt(pos1);
	m_MachineObjList->RemoveAt(pos1);
	m_MachineObjList->InsertBefore(pos, pObj);
	return TRUE;
}

BOOL CMachineListContainer::MoveObjDown(int nIndex)
{
	POSITION pos, pos1;
	CMachineObj_Comm* pObj;
	int bordermax, markmax, objmax;
	bordermax = 0;
	markmax = 0;
	objmax = -1;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		int n = m_MachineObjList->GetNext(pos)->m_ObjByLayer;
		if (n == 0)
			bordermax++;
		else if (n == 1)
			markmax++;
		objmax++;	
	}
	if (nIndex == bordermax - 1 || nIndex == (markmax + bordermax - 1) || nIndex >= objmax)
		return FALSE;
	pos = m_MachineObjList->FindIndex(nIndex + 1);
	pos1 = m_MachineObjList->FindIndex(nIndex);
	pObj = m_MachineObjList->GetAt(pos1);
	m_MachineObjList->InsertAfter(pos, pObj);
	m_MachineObjList->RemoveAt(pos1);
	return TRUE;
}

BOOL CMachineListContainer::ExchangeObjAtIndex(int Index1, int Index2)
{
	POSITION pos1, pos2;
	CMachineObj_Comm* pObj;
	int nLayer1, nLayer2;
	nLayer1 = GetObjAtIndex(Index1)->m_ObjByLayer;
	nLayer2 = GetObjAtIndex(Index2)->m_ObjByLayer;
	if ((nLayer1 != nLayer2) && ((nLayer1 < LayerNum_Group) || (nLayer2 < LayerNum_Group) 
		|| ((nLayer1 < LayerNum_Default) && (nLayer1 > LayerNum_Group)) 
		|| ((nLayer2 < LayerNum_Default) && (nLayer2 > LayerNum_Group))))
		return FALSE;
	pos1 = m_MachineObjList->FindIndex(Index1);
	pos2 = m_MachineObjList->FindIndex(Index2);
	if (Index1 > Index2)
	{
		pObj = m_MachineObjList->GetAt(pos1);
		m_MachineObjList->RemoveAt(pos1);
		m_MachineObjList->InsertBefore(pos2, pObj);
	}
	else
	{
		pObj = m_MachineObjList->GetAt(pos2);
		m_MachineObjList->RemoveAt(pos2);
		m_MachineObjList->InsertBefore(pos1, pObj);
	}
	return TRUE;
}

BOOL CMachineListContainer::IsEmptyLayer()
{
	return(m_MachineLayerList->IsEmpty());
}

BOOL CMachineListContainer::IsEmptyObj()
{
	return(m_MachineObjList->IsEmpty());
}

BOOL CMachineListContainer::ISEmptyBorder()
{
	return m_BorderEmpty;
}

int CMachineListContainer::GetLayerCount()
{
	return(m_MachineLayerList->GetCount());
}

void CMachineListContainer::RefeshBound()
{
	ReSizeBound();
}

int CMachineListContainer::GetObjCount()
{
	return(m_MachineObjList->GetCount());
}

ObjRect CMachineListContainer::GetObjBound(BOOL refresh)
{
	if (refresh)
		ReSizeBound();
	return m_ObjBound;
}

int CMachineListContainer::FindLayerByName(CString Name)
{
	CString str;
	int layerCount = 0;
	POSITION pos = m_MachineLayerList->GetHeadPosition();
	while (pos)
	{
		str = m_MachineLayerList->GetNext(pos)->m_LayerName;
		str.MakeLower();
		if (Name.MakeLower() == str)
			return layerCount;
		layerCount++;
	}
	return -1;
}

int CMachineListContainer::FindLayerByPara(ProcessPara para, int mode)
{
	ProcessPara para1;
	int mode1, layerCount;
	CMachinePara_Layer* pLayer;
	POSITION pos = m_MachineLayerList->GetHeadPosition();
	layerCount = 0;
	while (pos)
	{
		pLayer = m_MachineLayerList->GetNext(pos);
		para1 = pLayer->m_MachinePara;
		mode1 = pLayer->m_MachineMode;
		if (Para_Equal(para, para1)
			&& mode == mode1)
			return layerCount;
		layerCount++;
	}
	return -1;
}

void CMachineListContainer::ClearRedundLayer()
{
	ProcessPara para, para1;
	int mode, mode1;
	POSITION pos;
	CMachineObj_Comm* pObj;
	CMachinePara_Layer* pLayer;
	for (int i = LayerNum_Default; i < m_LayerCount; i++)
	{
		pLayer = GetLayerOfNumber(i);
		para = pLayer->m_MachinePara;
		mode = pLayer->m_MachineMode;
		for (int j = i + 1; j < m_LayerCount; j++)
		{
			pLayer = GetLayerOfNumber(j);
			para1 = pLayer->m_MachinePara;
			mode1 = pLayer->m_MachineMode;
			if (Para_Equal(para, para1)
				&& mode1 == mode)
			{
				pos = m_MachineObjList->GetHeadPosition();
				while (pos)
				{
					pObj = GetObjNext(pos);
					ModifyObjByLayer(pObj, j, i);
				}
			}
		}
	}
	ClearNullLayer();
}

void CMachineListContainer::LayerMoveUpAtIndex(int Index)
{
	if (Index <= LayerNum_Default || Index>= m_MachineLayerList->GetCount())
		return;
	POSITION pos = m_MachineLayerList->FindIndex(Index);
	CMachinePara_Layer* pLayer = m_MachineLayerList->GetAt(pos);
	m_MachineLayerList->RemoveAt(pos);
	pos = m_MachineLayerList->FindIndex(Index - 1);
	m_MachineLayerList->InsertBefore(pos, pLayer);
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		CMachineObj_Comm* pObj = m_MachineObjList->GetNext(pos);
		ExchangeObjInLayer(pObj, Index, Index - 1);
	}
}

void CMachineListContainer::LayerMoveDownAtIndex(int Index)
{
	if (Index < LayerNum_Default || Index >= m_MachineLayerList->GetCount())
		return;
	POSITION pos = m_MachineLayerList->FindIndex(Index);
	CMachinePara_Layer* pLayer = m_MachineLayerList->GetAt(pos);
	m_MachineLayerList->RemoveAt(pos);
	pos = m_MachineLayerList->FindIndex(Index);
	m_MachineLayerList->InsertAfter(pos, pLayer);
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		CMachineObj_Comm* pObj = m_MachineObjList->GetNext(pos);
		ExchangeObjInLayer(pObj, Index, Index + 1);
	}
}

POSITION CMachineListContainer::AddLayer(CMachinePara_Layer* MachineLayer)
{
	POSITION pos;
	if (FindLayerByName(MachineLayer->m_LayerName) > 0)
	{
		delete MachineLayer;
		return NULL;
	}
	pos = m_MachineLayerList->AddTail(MachineLayer);
	if (pos == NULL)
		return NULL;
	m_LayerCount++;
	return pos;
}

POSITION CMachineListContainer::AddObjTail(CMachineObj_Comm* MachineObj)
{
	POSITION pos, pos1;
	CMachineObj_Comm* pObjTemp;
	if (MachineObj->m_ObjByLayer > m_LayerCount)
		return NULL;
	if (MachineObj->m_ObjByLayer == 0)
	{
		pos = m_MachineObjList->GetHeadPosition();
		if (!pos)
			pos = m_MachineObjList->AddTail(MachineObj);
		else
		while (pos)
		{
			pos1 = pos;
			pObjTemp = m_MachineObjList->GetNext(pos);
			if (pObjTemp->m_ObjByLayer != 0)
			{
				InsertObjBefore(pos1, MachineObj);
				break;
			}
		}
	}
	else if (MachineObj->m_ObjByLayer == 1)
	{
		pos = m_MachineObjList->GetHeadPosition();
		if (!pos)
			pos = m_MachineObjList->AddTail(MachineObj);
		else
		while (pos)
		{
			pos1 = pos;
			pObjTemp = m_MachineObjList->GetNext(pos);
			if (pObjTemp->m_ObjByLayer != 1 && pObjTemp->m_ObjByLayer != 0)
			{
				InsertObjBefore(pos1, MachineObj);
				break;
			}
		}
	}
	else
		pos = m_MachineObjList->AddTail(MachineObj);
	if (pos == NULL)
		return NULL;
	ReSizeBound(MachineObj);
	return pos;
}

POSITION CMachineListContainer::InsertObjBefore(POSITION pos, CMachineObj_Comm* MachineObj)
{
	POSITION pos_t;
	if (pos == NULL)
		return NULL;
	if (MachineObj->m_ObjByLayer > m_LayerCount)
		return NULL;
	pos_t = m_MachineObjList->InsertBefore(pos, MachineObj);
	if (pos_t == NULL)
		return NULL;
	ReSizeBound(MachineObj);
	return pos_t;
}

POSITION CMachineListContainer::InsertObjAfter(POSITION pos, CMachineObj_Comm* MachineObj)
{
	POSITION pos_t;
	if (pos == NULL)
		return NULL;
	if (MachineObj->m_ObjByLayer > m_LayerCount)
		return NULL;
	pos_t = m_MachineObjList->InsertAfter(pos, MachineObj);
	if (pos_t == NULL)
		return NULL;
	ReSizeBound(MachineObj);
	return pos_t;
}

BOOL CMachineListContainer::DeleteLayerOfNumber(int Number)
{
	CMachinePara_Layer* pLayer;
	CMachineObj_Comm* pObj;
	POSITION pos, pos1;
	int nLayer;
	if (Number <= 0 || Number > m_LayerCount)
		return FALSE;
	pos = m_MachineLayerList->FindIndex(Number);
	pLayer = m_MachineLayerList->GetAt(pos);
	delete pLayer;
	m_MachineLayerList->RemoveAt(pos);
	m_LayerCount--;
	pos = m_MachineObjList->GetHeadPosition();
	while (pos)
	{
		pos1 = pos;
		pObj = m_MachineObjList->GetNext(pos);
		nLayer = pObj->m_ObjByLayer;
		if (nLayer == Number)
		{
			m_MachineObjList->RemoveAt(pos1);
			delete pObj;
		}
		else if ((nLayer > Number) || (nLayer == LayerNum_Group))
		{
			DeleteObjInLayer(pObj, Number);
			ReduceObjLayerAfterIndex(pObj, Number);
		}
	}
	ReSizeBound();
	return TRUE;
}

BOOL CMachineListContainer::DeleteLayerOfName(CString Name)
{
	if (Name == LayerName_Border || Name == LayerName_Mark)
		return FALSE;
	return DeleteLayerOfNumber(FindLayerByName(Name));
}

void CMachineListContainer::ChangeObjByLayer(CMachineObj_Comm* pObj, int Layer_Index)
{
	if (Layer_Index < 0 || Layer_Index >= m_LayerCount)
		return;
	int nType = pObj->GetObjType();
	if (nType != MachineObj_Type_Group)
	{
		pObj->m_ObjByLayer = Layer_Index;
		return;
	}
	CMachineObj_Comm* pObj1;
	CMachineObjGroup* pGroup = (CMachineObjGroup*)pObj;
	CMachineObjList* pList = pGroup->GetObjList();
	POSITION pos = pList->GetHeadPosition();
	while (pos)
	{
		pObj1 = pList->GetNext(pos);
		ChangeObjByLayer(pObj1, Layer_Index);
	}
	pObj->m_ObjByLayer = Layer_Index;
	return;
}


CMachinePara_Layer* CMachineListContainer::GetLayerOfNumber(int Number)
{
	if (Number < 0 || Number >= m_LayerCount)
		return NULL;
	return m_MachineLayerList->GetAt(m_MachineLayerList->FindIndex(Number));
}

CMachinePara_Layer* CMachineListContainer::GetLayerOfName(CString Name)
{
	return m_MachineLayerList->GetAt(m_MachineLayerList->FindIndex(FindLayerByName(Name)));
}

POSITION CMachineListContainer::GetObjHeadPosition()
{
	return m_MachineObjList->GetHeadPosition();
}

CMachineObj_Comm* CMachineListContainer::GetObjAtIndex(int Index)
{
	return m_MachineObjList->GetAt(m_MachineObjList->FindIndex(Index));
}

BOOL CMachineListContainer::DeleteObjAtIndex(int Index)
{
	if (Index > m_MachineObjList->GetCount())
		return FALSE;
	POSITION pos;
	CMachineObj_Comm* pObj;
	pos = m_MachineObjList->FindIndex(Index);
	pObj = m_MachineObjList->GetAt(pos);
	m_MachineObjList->RemoveAt(pos);
	delete pObj;
	return TRUE;
}

BOOL CMachineListContainer::InsertObjAtIndex(int Index, CMachineObj_Comm* pObj)
{
	if (Index < 0)
		return FALSE;
	if (Index >= m_MachineObjList->GetCount())
	{
		m_MachineObjList->AddTail(pObj);
		return TRUE;
	}
	else
	{
		POSITION pos;
		pos = m_MachineObjList->FindIndex(Index);
		InsertObjBefore(pos, pObj);
		return TRUE;
	}
}

BOOL CMachineListContainer::RemoveObjAtIndex(int Index)
{
	if (Index > m_MachineObjList->GetCount())
		return FALSE;
	POSITION pos;
	pos = m_MachineObjList->FindIndex(Index);
	m_MachineObjList->RemoveAt(pos);
	return TRUE;
}

BOOL CMachineListContainer::PolymerObjAtIndex(int Index)
{
	if (Index > m_MachineObjList->GetCount())
		return FALSE;
	POSITION pos = m_MachineObjList->FindIndex(Index);
	CMachineObj_Comm* pObj = m_MachineObjList->GetAt(pos);
	int ObjType = pObj->GetObjType();
	if ((ObjType != MachineObj_Type_Line) && (ObjType != MachineObj_Type_Arc))
		return FALSE;
	ObjVPoint vpoint;
	ObjPoint point;
	CMachineObjPolyline* pObj1 = new CMachineObjPolyline;
	if (ObjType == MachineObj_Type_Line)
	{
		CMachineObjLine* pLine = (CMachineObjLine*)pObj;
		point = pLine->GetLineStart();
		vpoint.x = point.x;
		vpoint.y = point.y;
		vpoint.convexity = 0;
		pObj1->AddObjVpoint(vpoint);
		point = pLine->GetLineEnd();
		vpoint.x = point.x;
		vpoint.y = point.y;
		pObj1->AddObjVpoint(vpoint);
	}
	else
	{
		CMachineObjArc* pArc = (CMachineObjArc*)pObj;
		point = pArc->GetArcStart();
		vpoint.x = point.x;
		vpoint.y = point.y;
		vpoint.convexity = CalArcConvex(pArc);
		pObj1->AddObjVpoint(vpoint);
		point = pArc->GetArcEnd();
		vpoint.x = point.x;
		vpoint.y = point.y;
		vpoint.convexity = 0;
		pObj1->AddObjVpoint(vpoint);
	}
	pObj1->m_ObjByLayer = pObj->m_ObjByLayer;
	pObj1->m_bIsObjStatus = pObj->m_bIsObjStatus;
	InsertObjBefore(pos, pObj1);
	pos = m_MachineObjList->FindIndex(Index + 1);
	m_MachineObjList->RemoveAt(pos);
	delete pObj;
	return TRUE;
}

BOOL CMachineListContainer::PolymerObjAtIndex(vector<int> nList)
{
	POSITION pos, pos_old;
	CMachineObj_Comm *pObj, *pObj1;
	BOOL EnNew;
	vector<CMachineObj_Comm*> pObjectList;
	int Count = nList.size();
	vector<BOOL> bList(Count, 1);
	for (int i = 0; i < Count; i++)
	{
		if (bList[i])
		{
			bList[i] = FALSE;
			EnNew = TRUE;
			pObj = m_MachineObjList->GetAt(m_MachineObjList->FindIndex(nList[i]));
			for (int j = 0; j < Count; j++)
			{
				if (bList[j])
				{
					pObj1 = m_MachineObjList->GetAt(m_MachineObjList->FindIndex(nList[j]));
					CMachineObj_Comm* pTemp;
					pTemp = PolymerObj(pObj, pObj1, EnNew);
					if (!(pTemp == NULL))
					{
						EnNew = FALSE;
						bList[j] = FALSE;
						pObj = pTemp;
						j = -1;
					}
				}
			}
			if (EnNew)
				bList[i] = TRUE;
			else
				pObjectList.push_back(pObj);
		}
	}
	if (pObjectList.size() == 0)
	{
		bList.clear();
		vector<BOOL>(bList).swap(bList);
		pObjectList.clear();
		vector<CMachineObj_Comm*>(pObjectList).swap(pObjectList);
		return FALSE;
	}
	pos_old = NULL;
	for (int i = 0; i < Count; i++)
	{
		if (!bList[i])
		{
			pos_old = m_MachineObjList->FindIndex(nList[i]);
			break;
		}
	}
	for (int i = 0; i < Count; i++)
	{
		if (!bList[Count - i - 1])
		{
			pos = m_MachineObjList->FindIndex(nList[Count - i - 1]);
			if (pos_old != pos)
			{
				pObj = m_MachineObjList->GetAt(pos);
				m_MachineObjList->RemoveAt(pos);
				delete pObj;
			}
			else
				break;
		}
	}
	pos = pos_old;
	Count = pObjectList.size();
	for (int i = 0; i < Count; i++)
	{
		pos = m_MachineObjList->InsertAfter(pos, pObjectList[i]);
	}
	pObj = m_MachineObjList->GetAt(pos_old);
	m_MachineObjList->RemoveAt(pos_old);
	delete pObj;
	bList.clear();
	vector<BOOL>(bList).swap(bList);
	pObjectList.clear();
	vector<CMachineObj_Comm*>(pObjectList).swap(pObjectList);
	return TRUE;
}

BOOL CMachineListContainer::GroupObjAtIndex(vector<int> nList)
{
	CMachineObjGroup* pGroup;
	CMachineObj_Comm* pObj;
	POSITION pos0, pos;
	int nlistmax, nLayer;
	pos0 = m_MachineObjList->FindIndex(nList[0]);
	nLayer = m_MachineObjList->GetAt(pos0)->m_ObjByLayer;
	nlistmax = nList.size();
	if (nLayer == LayerNum_Border)
	{
		for (int i = 1; i < nlistmax; i++)
		{
			if (nLayer != m_MachineObjList->GetAt(m_MachineObjList->FindIndex(nList[i]))->m_ObjByLayer)
				return FALSE;
		}
	}
	else if (nLayer == LayerNum_Mark)
	{
		for (int i = 1; i < nlistmax; i++)
		{
			if (nLayer != m_MachineObjList->GetAt(m_MachineObjList->FindIndex(nList[i]))->m_ObjByLayer)
				return FALSE;
		}
	}
	else
	{
		for (int i = 1; i < nlistmax; i++)
		{
			if (nLayer != m_MachineObjList->GetAt(m_MachineObjList->FindIndex(nList[i]))->m_ObjByLayer)
				nLayer = LayerNum_Group;
		}
	}
	pGroup = new CMachineObjGroup();
	for (int i = 0; i < nlistmax; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[i]);
		pObj = m_MachineObjList->GetNext(pos);
		pObj->m_bIsObjStatus = pObj->m_bIsObjStatus & IsObjNormal;
		pGroup->AddGroupObj(pObj);
	}
	//移去除第一选中对象后的所有选中对象
	for (int i = 0; i < nlistmax - 1; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[nlistmax - 1 - i]);
		m_MachineObjList->RemoveAt(pos);
	}
	//在选中的第一对象前插入群组对象
	pGroup->m_ObjByLayer = nLayer;
	m_MachineObjList->InsertBefore(pos0, pGroup);
	//移去选中的第一对象
	m_MachineObjList->RemoveAt(pos0);
	return TRUE;
}

BOOL CMachineListContainer::ExplodeObjAtIndex(int Index)
{
	CMachineObj_Comm* pObj_old;
	CMachineObjLine* pLine;
	CMachineObjArc* pArc;
	POSITION pos, pos_old;
	pos = m_MachineObjList->FindIndex(Index);
	pos_old = pos;
	pObj_old = m_MachineObjList->GetAt(pos);
	if (pObj_old->GetObjType() == MachineObj_Type_Polyline)
	{
		//多段线则分解
		ObjPoint Opoint1, Opointlast;
		ObjVPoint Ovpoint1;
		double convexity;
		CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj_old;
		int VertCount = pPolyline->GetPolylineVertexCount();
		int nLayer = pPolyline->m_ObjByLayer;
		Ovpoint1 = pPolyline->GetPolylineStart();
		Opointlast.x = Ovpoint1.x;
		Opointlast.y = Ovpoint1.y;
		convexity = Ovpoint1.convexity;
		for (int i = 1; i < VertCount; i++)
		{
			Ovpoint1 = pPolyline->GetPolylinePoint(i);
			Opoint1.x = Ovpoint1.x;
			Opoint1.y = Ovpoint1.y;
			if (convexity == 0)
			{
				//直线
				pLine = new CMachineObjLine(Opointlast, Opoint1, nLayer);
				pos = m_MachineObjList->InsertAfter(pos, pLine);
				Opointlast = Opoint1;
				convexity = Ovpoint1.convexity;
			}
			else
			{
				//圆弧
				pArc = pPolyline->TranPolylineToArc(Opointlast, Opoint1, convexity, nLayer);
				pos = m_MachineObjList->InsertAfter(pos, pArc);
				Opointlast = Opoint1;
				convexity = Ovpoint1.convexity;
			}
		}
		m_MachineObjList->RemoveAt(pos_old);
		delete pObj_old;
	}
	else if (pObj_old->GetObjType() == MachineObj_Type_Group)
	{
		//群组则打散
		CMachineObjGroup* pGroup;
		CMachineObj_Comm* pObj;
		pGroup = (CMachineObjGroup*)pObj_old;
		pObj = pGroup->GetAndMoveGroupObj();
		while (pObj)
		{
			pos = m_MachineObjList->InsertAfter(pos, pObj);
			pObj = pGroup->GetAndMoveGroupObj();
		}
		m_MachineObjList->RemoveAt(pos_old);
		delete pGroup;
	}
	else
		return FALSE;
	return TRUE;
}

BOOL CMachineListContainer::ChangeObjNode(vector<int> nList)
{
	int Count,nType;
	char Number;
	POSITION pos;
	CMachineObj_Comm* pObj;
	Count = nList.size();
	for (int i = 0; i < Count; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[i]);
		pObj = m_MachineObjList->GetAt(pos);
		nType = pObj->GetObjType();
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
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CMachineListContainer::ReverseObj(vector<int> nList)
{
	int Count, nType;
	POSITION pos;
	CMachineObj_Comm* pObj;
	Count = nList.size();
	for (int i = 0; i < Count; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[i]);
		pObj = m_MachineObjList->GetAt(pos);
		nType = pObj->GetObjType();
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
			pCircle->ExchangeDirection();
			break;
		case MachineObj_Type_Arc:
			CMachineObjArc* pArc;
			pArc = (CMachineObjArc*)pObj;
			pArc->ExchangeStartAndEnd(pArc);
			break;
		case MachineObj_Type_Ellipse:
			CMachineObjEllipse* pEllipse;
			pEllipse = (CMachineObjEllipse*)pObj;
			pEllipse->ExchangeDirection();
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
			return FALSE;
		}
	}
	return TRUE;
}



CMachineObj_Comm* CMachineListContainer::GetObjHead()
{
	return m_MachineObjList->GetHead();
}

CMachineObj_Comm* CMachineListContainer::GetObjTail()
{
	return m_MachineObjList->GetTail();
}

CMachineObj_Comm*& CMachineListContainer::GetObjNext(POSITION& pos)
{
	return m_MachineObjList->GetNext(pos);
}

CMachineObj_Comm*& CMachineListContainer::GetObjPrev(POSITION& pos)
{
	return m_MachineObjList->GetPrev(pos);
}



//****显示相关****
CPoint CMachineListContainer::TransRPtoLP(ObjPoint ptObj)
{
	CPoint point;
	point.x = (long)(ptObj.x * MultipeObjToLP);
	point.y = (long)(-ptObj.y * MultipeObjToLP);
	return point;
}

CRect CMachineListContainer::TransRBdtoLBd(ObjRect ObjBound, long Offset)
{
	CRect rect;
	rect.left = (long)(ObjBound.min_x * MultipeObjToLP) - Offset;
	rect.right = (long)(ObjBound.max_x * MultipeObjToLP) + Offset;
	rect.top = -(long)(ObjBound.max_y * MultipeObjToLP) - Offset;
	rect.bottom = -(long)(ObjBound.min_y * MultipeObjToLP) + Offset;
	return rect;
}

int CMachineListContainer::PickObjectList(CMachineListContainer* pObjlist,
	ObjPoint point, ObjRect rect, float BoxSize)
{
	if (pObjlist->IsEmptyObj())
		return -2;
	CMachineObj_Comm* pObj;
	POSITION pos;
	int Count = 0;
	
	pos = pObjlist->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjlist->GetObjNext(pos);
		if (IntersectBound(rect, pObj->GetObjBound()))
		{
			if (PickObject(pObj, point, BoxSize))
				return Count;
		}
		Count++;
	}
	return -1;
}

vector<int> CMachineListContainer::PickMultObjList(CMachineListContainer* pObjlist,	ObjRect rect, ObjRect rect1)
{
	vector<int> nList;
	if (pObjlist->IsEmptyObj())
		return nList;
	CMachineObj_Comm* pObj;
	POSITION pos;
	ObjPoint point;
	float BoxSize;
	int Count = 0;
	point.x = (rect1.max_x + rect1.min_x) / 2;
	point.y = (rect1.max_y + rect1.min_y) / 2;
	BoxSize = (float)max(abs(rect1.max_x - rect1.min_x), abs(rect1.max_y - rect1.min_y)) / 2;
	pos = pObjlist->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjlist->GetObjNext(pos);
		if (IsObjActive(pObj))
		{
			if (ISIncludeBound(rect1, pObj->GetObjBound()))
			{
				pObj->m_bIsObjStatus |= IsObjSel;
				nList.push_back(Count);
			}
			else if (IntersectBound(rect, pObj->GetObjBound()) && IntersectBound(rect1, pObj->GetObjBound()))
			{
				if (PickObject(pObj, point, BoxSize))
					nList.push_back(Count);
			}
		}
	/*	if (IntersectBound(rect, pObj->GetObjBound()) && IntersectBound(rect1, pObj->GetObjBound()))
		{
			if (PickObject(pObj, point, BoxSize))
				nList.push_back(Count);
		}*/
		Count++;
	}
	return nList;
}

void CMachineListContainer::DrawObjList(CDC* pDC, CMachineListContainer* pObjList, float ZoomFactor, ObjRect Disprc, bool Dispdir)
{
	if (pObjList->IsEmptyObj())
		return;
	CPen Pen;
	Pen.CreatePen(PS_DASH, 1, PenColor_Border);
	CPen* pOldPen = pDC->SelectObject(&Pen);
	//绘制虚拟外框
	CRect rect = TransRBdtoLBd(pObjList->GetObjBound(), OffsetBound);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.left, rect.top);
	pDC->SelectObject(pOldPen);

	ObjPoint Opoint1, Opoint2, Opointlast;
	ObjVPoint Ovpoint1;
	CPoint point, point1;
	int LayerNum;
	double x, y, dirAngle;
	double sAngle, eAngle, dAngle;
	CPen* pNewPen;
	CPen Pen1, Pen2, Pen3, Pen4, Pen5, Pen6;
	CBrush* pBrush;
	CBrush Brush1, Brush2;
	Pen1.CreatePen(PS_SOLID, 1, PenColor_Sel);
	Pen2.CreatePen(PS_SOLID, 1, PenColor_Border);
	Pen3.CreatePen(PS_SOLID, 1, PenColor_Mark);
	Pen4.CreatePen(PS_SOLID, 1, PenColor_Normal);
	Pen5.CreatePen(PS_SOLID, 1, PenColor_Point);
	Pen6.CreatePen(PS_SOLID, 1, PenColor_Start);
	Brush1.CreateSolidBrush(PenColor_Sel);		//红刷子
	Brush2.CreateSolidBrush(PenColor_Point);	//蓝刷子

	CMachineObj_Comm* pObj;
	POSITION pos;
	ObjRect Objrc;
	CMachineObjList* ObjDispList;
	byte bLayerStatus;
	ObjDir dir;
	VectPoint pVect;
	VectLine FillLine;
	ObjPoint Opointlast_old, Opoint1_old;
	CPoint point_old;
	int nCount;
	int VertCount;
	double x0, y0, r, convexity;
	pos = pObjList->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjList->GetObjNext(pos);
		Objrc = pObj->GetObjBound();
		LayerNum = pObj->m_ObjByLayer;
		bLayerStatus = pObjList->GetLayerOfNumber(LayerNum)->m_bIsLayerStatus;
		//判定对象区域与显示区域是否相交 判定该对象及图层是否关闭
		if (((pObj->m_bIsObjStatus & IsObjClosed) == 0) &&
			((bLayerStatus & IsObjClosed) == 0) &&
			(!(Objrc.max_x<Disprc.min_x
			|| Objrc.max_y<Disprc.min_y
			|| Objrc.min_x>Disprc.max_x
			|| Objrc.min_y>Disprc.max_y)))
		{
			//相交或对象区域包含显示区域则显示
			bool Sel = false;
			if (((bLayerStatus & IsObjSel) == 1) || (pObj->m_bIsObjStatus & IsObjSel) == 1)
				Sel = true;

			switch (pObj->GetObjType())
			{
			case MachineObj_Type_Point:
				//***DrawPoint***
				CMachineObjPoint* pPoint;
				pPoint = (CMachineObjPoint*)pObj;
				long radius;
				if (Sel)
				{
					pNewPen = &Pen1;	//选中的点为红边界红填充	
					pBrush = &Brush1;
				}
				else
				{
					pNewPen = &Pen5;	//为选中的点为蓝边界蓝填充
					pBrush = &Brush2;
				}
				point = TransRPtoLP(pPoint->GetPoint());

				radius = long(DotSize / ZoomFactor);
				if (radius < 100)
					radius = 100;
				rect.left = point.x - radius;
				rect.top = point.y - radius;
				rect.right = point.x + radius;
				rect.bottom = point.y + radius;
				point.x = rect.left;
				point.y = point.y;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				pDC->SelectObject(pBrush);					//选刷子
				pDC->Pie(rect, point, point);
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
        //*****************Point End*******************//
			case MachineObj_Type_Line:
				//***DrawLine***
				CMachineObjLine* pLine;
				pLine = (CMachineObjLine*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);
				Opoint1 = pLine->GetLineStart();
				point = TransRPtoLP(Opoint1);
				pDC->MoveTo(point);
				Opoint2 = pLine->GetLineEnd();
				point = TransRPtoLP(Opoint2);
				pDC->LineTo(point);
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = CalDirAngle(Opoint1, Opoint2);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);			//恢复老画笔
				break;
		//*****************Line End*******************//
			case MachineObj_Type_Circle:
				//***DrawCircle***
				CMachineObjCircle* pCircle;
				pCircle = (CMachineObjCircle*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);			//选专用画笔并保存老画笔
				sAngle = 90 * pCircle->GetCircleStartNum();
				dAngle = DrawArcStep;
				if (pCircle->GetCircleDir() == CCW)
				{
					eAngle = sAngle + 360;
					point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
					pDC->MoveTo(point);
					sAngle += dAngle;
					while (sAngle < eAngle)
					{
						point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
						sAngle += dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pCircle->GetCirclePoint(eAngle);
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				else
				{
					eAngle = sAngle - 360;
					point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
					pDC->MoveTo(point);
					sAngle -= dAngle;
					while (sAngle > eAngle)
					{
						point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
						sAngle -= dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pCircle->GetCirclePoint(eAngle);
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = pCircle->CalDirAngle(eAngle);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
     	//*****************Circle End*******************//
			case MachineObj_Type_Arc:
				//***DrawArc***
				CMachineObjArc* pArc;
				pArc = (CMachineObjArc*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				sAngle = pArc->GetStartAngle();
				eAngle = pArc->GetEndAngle();
				dAngle = abs((eAngle - sAngle) / 3);		//**圆弧至少画4点**//
				if (dAngle>DrawArcStep)
					dAngle = DrawArcStep;
				if (pArc->GetArcDir() == CCW)
				{
					point = TransRPtoLP(pArc->GetArcStart());
					pDC->MoveTo(point);
					sAngle += dAngle;
					while (sAngle < eAngle)
					{
						point = TransRPtoLP(pArc->GetArcPoint(sAngle));
						sAngle += dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pArc->GetArcEnd();
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				else
				{
					point = TransRPtoLP(pArc->GetArcStart());
					pDC->MoveTo(point);
					sAngle -= dAngle;
					while (sAngle > eAngle)
					{
						point = TransRPtoLP(pArc->GetArcPoint(sAngle));
						sAngle -= dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pArc->GetArcEnd();
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = pArc->CalDirAngle(eAngle);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************Arc End*******************//
			case MachineObj_Type_Ellipse:
				//***DrawEllipse***
				CMachineObjEllipse* pEllipse;
				pEllipse = (CMachineObjEllipse*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);			//选专用画笔并保存老画笔
				sAngle = M_PI_2*pEllipse->GetEllipseStartNum();
				dAngle = M_PI* DrawArcStep / 180;
				if (pEllipse->GetEllipseDir() == CCW)
				{
					eAngle = sAngle + 2 * M_PI;
					point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
					pDC->MoveTo(point);
					sAngle += dAngle;
					while (sAngle < eAngle)
					{
						point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
						sAngle += dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pEllipse->GetEllipsePoint(eAngle);
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				else
				{
					eAngle = sAngle - 2 * M_PI;
					point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
					pDC->MoveTo(point);
					sAngle -= dAngle;
					while (sAngle > eAngle)
					{
						point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
						sAngle -= dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pEllipse->GetEllipsePoint(eAngle);
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = pEllipse->CalDirAngle(eAngle);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************Ellipse End*******************//
			case MachineObj_Type_ArcEll:
				//***DrawArcEll***
				CMachineObjArcEll* pArcEll;
				pArcEll = (CMachineObjArcEll*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				sAngle = pArcEll->GetStartRadian();
				eAngle = pArcEll->GetEndRadian();
				dAngle = M_PI* DrawArcStep / 180;
				if (pArcEll->GetArcDir() == CCW)
				{
					point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
					pDC->MoveTo(point);
					sAngle += dAngle;
					while (sAngle < eAngle)
					{
						point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
						sAngle += dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pArcEll->GetEllipseArcPoint(eAngle);
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				else
				{
					point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
					pDC->MoveTo(point);
					sAngle -= dAngle;
					while (sAngle > eAngle)
					{
						point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
						sAngle -= dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pArcEll->GetEllipseArcPoint(eAngle);
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = pArcEll->CalDirAngle(eAngle);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************Ellipse End*******************//
			case MachineObj_Type_TiltEllipse:
				//***DrawTiltEllipse***
				CMachineObjTiltEllipse* pTiltEllArc;
				pTiltEllArc = (CMachineObjTiltEllipse*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				sAngle = pTiltEllArc->GetStartRadian();
				eAngle = pTiltEllArc->GetEndRadian();
				dAngle = M_PI * DrawArcStep / 180;
				if (pTiltEllArc->GetArcDir() == CCW)
				{
					point = TransRPtoLP(pTiltEllArc->GetTiltEllipseStart());
					pDC->MoveTo(point);
					sAngle += dAngle;
					while (sAngle < eAngle)
					{
						point = TransRPtoLP(pTiltEllArc->GetTiltEllipsePoint(sAngle));
						pDC->LineTo(point);
						sAngle += dAngle;
					}
					Opoint2 = pTiltEllArc->GetTiltEllipseEnd();
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				else
				{
					point = TransRPtoLP(pTiltEllArc->GetTiltEllipseStart());
					pDC->MoveTo(point);
					sAngle -= dAngle;
					while (sAngle > eAngle)
					{
						point = TransRPtoLP(pTiltEllArc->GetTiltEllipsePoint(sAngle));
						pDC->LineTo(point);
						sAngle -= dAngle;
					}
					Opoint2 = pTiltEllArc->GetTiltEllipseEnd();
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = pTiltEllArc->CalDirAngle(eAngle);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************TiltEllipse End*******************//
			case MachineObj_Type_Polyline:
				//***DrawPolyline***
				CMachineObjPolyline* pPolyline;
				pPolyline = (CMachineObjPolyline*)pObj;
				
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				VertCount = pPolyline->GetPolylineVertexCount();
				Ovpoint1 = pPolyline->GetPolylineStart();
				Opoint1.x = Ovpoint1.x;
				Opoint1.y = Ovpoint1.y;
				Opointlast = Opoint1;
				convexity = Ovpoint1.convexity;
				point = TransRPtoLP(Opoint1);
				pDC->MoveTo(point);
				for (int i = 1; i < VertCount; i++)
				{
					Ovpoint1 = pPolyline->GetPolylinePoint(i);
					Opoint1.x = Ovpoint1.x;
					Opoint1.y = Ovpoint1.y;
					if (convexity == 0)
					{
						point = TransRPtoLP(Opoint1);
						pDC->LineTo(point);
						if (i < VertCount - 1)
						{
							Opointlast = Opoint1;
							convexity = Ovpoint1.convexity;
						}
					}
					else
					{
						ObjPoint ArcCenter;
						pPolyline->TranPolylineToArc(
							Opointlast, Opoint1, convexity,
							&ArcCenter, &r, &sAngle, &eAngle);
						x0 = ArcCenter.x;
						y0 = ArcCenter.y;
						dAngle = DrawArcStep;
						if (eAngle > sAngle)
						{
							dir = CCW;
							point = TransRPtoLP(Opointlast);
							pDC->MoveTo(point);
							sAngle += dAngle;
							while (sAngle < eAngle)
							{
								x = x0 + r*cos(sAngle / 180 * M_PI);
								y = y0 + r*sin(sAngle / 180 * M_PI);
								sAngle += dAngle;
								point = TransRPtoLP(ObjPoint(x, y));
								pDC->LineTo(point);
							}
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
						}
						else
						{
							dir = CW;
							point = TransRPtoLP(Opointlast);
							pDC->MoveTo(point);
							sAngle -= dAngle;
							while (sAngle > eAngle)
							{
								x = x0 + r*cos(sAngle / 180 * M_PI);
								y = y0 + r*sin(sAngle / 180 * M_PI);
								sAngle -= dAngle;
								point = TransRPtoLP(ObjPoint(x, y));
								pDC->LineTo(point);
							}
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
						}
						if (i < VertCount - 1)
						{
							Opointlast = Opoint1;
							convexity = Ovpoint1.convexity;
						}
					}
					point = TransRPtoLP(Opoint1);
					pDC->LineTo(point);
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					if (convexity == 0)
						dirAngle = CalDirAngle(Opointlast, Opoint1);
					else
					{
						double dx = -r * sin(M_PI * eAngle / 180);
						double dy = r * cos(M_PI * eAngle / 180);
						if (dir == CCW)
						{
							if (dx > 0)
							{
								dirAngle = atan(dy / dx);
							}
							else if (dx < 0)
							{
								dirAngle = atan(dy / dx) + M_PI;
							}
							else
							{
								if (dy > 0)
									dirAngle = M_PI_2;
								else
									dirAngle = M_PI + M_PI_2;
							}
						}
						else
						{
							if (dx > 0)
							{
								dirAngle = atan(dy / dx) + M_PI;
							}
							else if (dx < 0)
							{
								dirAngle = atan(dy / dx);
							}
							else
							{
								if (dy < 0)
									dirAngle = M_PI_2;
								else
									dirAngle = M_PI + M_PI_2;
							}
						}
					}
					Opointlast = Opoint1;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************Polyline End*******************//
			case MachineObj_Type_Group:
				//***DrawGroup***
				ObjDispList = new CMachineObjList();
				ObjToDispList(pObj, ObjDispList);
				POSITION posDisp;
				CMachineObj_Comm* pObj1;
				posDisp = ObjDispList->GetHeadPosition();
				while (posDisp)
				{
					pObj1 = ObjDispList->GetNext(posDisp);
					if (!(Objrc.max_x<Disprc.min_x
						|| Objrc.max_y<Disprc.min_y
						|| Objrc.min_x>Disprc.max_x
						|| Objrc.min_y>Disprc.max_y))
					{
						//相交或对象区域包含显示区域则显示
						LayerNum = pObj1->m_ObjByLayer;
						switch (pObj1->GetObjType())
						{
						case MachineObj_Type_Point:
							//***DrawPoint***
							CMachineObjPoint* pPoint;
							pPoint = (CMachineObjPoint*)pObj1;
							long radius;
							if (Sel)
							{
								pNewPen = &Pen1;	//选中的点为红边界红填充	
								pBrush = &Brush1;
							}
							else
							{
								pNewPen = &Pen5;	//为选中的点为蓝边界蓝填充
								pBrush = &Brush2;
							}
							point = TransRPtoLP(pPoint->GetPoint());

							radius = long(DotSize / ZoomFactor);
							if (radius < 100)
								radius = 100;
							rect.left = point.x - radius;
							rect.top = point.y - radius;
							rect.right = point.x + radius;
							rect.bottom = point.y + radius;
							point.x = rect.left;
							point.y = point.y;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							pDC->SelectObject(pBrush);					//选刷子
							pDC->Pie(rect, point, point);
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_Line:
							//***DrawLine***
							CMachineObjLine* pLine;
							pLine = (CMachineObjLine*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);
							Opoint1 = pLine->GetLineStart();
							point = TransRPtoLP(Opoint1);
							pDC->MoveTo(point);
							Opoint2 = pLine->GetLineEnd();
							point = TransRPtoLP(Opoint2);
							pDC->LineTo(point);
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = CalDirAngle(Opoint1, Opoint2);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);			//恢复老画笔
							break;
						case MachineObj_Type_Circle:
							//***DrawCircle***
							CMachineObjCircle* pCircle;
							pCircle = (CMachineObjCircle*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);			//选专用画笔并保存老画笔
							sAngle = 90 * pCircle->GetCircleStartNum();
							dAngle = DrawArcStep;
							if (pCircle->GetCircleDir() == CCW)
							{
								eAngle = sAngle + 360;
								point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
									sAngle += dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pCircle->GetCirclePoint(eAngle);
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							else
							{
								eAngle = sAngle - 360;
								point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									point = TransRPtoLP(pCircle->GetCirclePoint(sAngle));
									sAngle -= dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pCircle->GetCirclePoint(eAngle);
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = pCircle->CalDirAngle(eAngle);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_Arc:
							//***DrawArc***
							CMachineObjArc* pArc;
							pArc = (CMachineObjArc*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							sAngle = pArc->GetStartAngle();
							eAngle = pArc->GetEndAngle();
							dAngle = abs((eAngle - sAngle) / 3);		//**圆弧至少画4点**//
							if (dAngle>DrawArcStep)
								dAngle = DrawArcStep;
							if (pArc->GetArcDir() == CCW)
							{
								point = TransRPtoLP(pArc->GetArcStart());
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									point = TransRPtoLP(pArc->GetArcPoint(sAngle));
									sAngle += dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pArc->GetArcEnd();
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							else
							{
								point = TransRPtoLP(pArc->GetArcStart());
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									point = TransRPtoLP(pArc->GetArcPoint(sAngle));
									sAngle -= dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pArc->GetArcEnd();
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = pArc->CalDirAngle(eAngle);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_Ellipse:
							//***DrawEllipse***
							CMachineObjEllipse* pEllipse;
							pEllipse = (CMachineObjEllipse*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);			//选专用画笔并保存老画笔
							sAngle = M_PI_2*pEllipse->GetEllipseStartNum();
							dAngle = M_PI* DrawArcStep / 180;
							if (pEllipse->GetEllipseDir() == CCW)
							{
								eAngle = sAngle + 2 * M_PI;
								point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
									sAngle += dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pEllipse->GetEllipsePoint(eAngle);
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							else
							{
								eAngle = sAngle - 2 * M_PI;
								point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									point = TransRPtoLP(pEllipse->GetEllipsePoint(sAngle));
									sAngle -= dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pEllipse->GetEllipsePoint(eAngle);
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = pEllipse->CalDirAngle(eAngle);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_ArcEll:
							//***DrawArcEll***
							CMachineObjArcEll* pArcEll;
							pArcEll = (CMachineObjArcEll*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							sAngle = pArcEll->GetStartRadian();
							eAngle = pArcEll->GetEndRadian();
							dAngle = M_PI* DrawArcStep / 180;
							if (pArcEll->GetArcDir() == CCW)
							{
								point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
									sAngle += dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pArcEll->GetEllipseArcPoint(eAngle);
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							else
							{
								point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									point = TransRPtoLP(pArcEll->GetEllipseArcPoint(sAngle));
									sAngle -= dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pArcEll->GetEllipseArcPoint(eAngle);
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = pArcEll->CalDirAngle(eAngle);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_TiltEllipse:
							//***DrawTiltEllipse***
							CMachineObjTiltEllipse* pTiltEllArc;
							pTiltEllArc = (CMachineObjTiltEllipse*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							sAngle = pTiltEllArc->GetStartRadian();
							eAngle = pTiltEllArc->GetEndRadian();
							dAngle = M_PI * DrawArcStep / 180;
							if (pTiltEllArc->GetArcDir() == CCW)
							{
								point = TransRPtoLP(pTiltEllArc->GetTiltEllipseStart());
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									point = TransRPtoLP(pTiltEllArc->GetTiltEllipsePoint(sAngle));
									pDC->LineTo(point);
									sAngle += dAngle;
								}
								Opoint2 = pTiltEllArc->GetTiltEllipseEnd();
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							else
							{
								point = TransRPtoLP(pTiltEllArc->GetTiltEllipseStart());
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									point = TransRPtoLP(pTiltEllArc->GetTiltEllipsePoint(sAngle));
									pDC->LineTo(point);
									sAngle -= dAngle;
								}
								Opoint2 = pTiltEllArc->GetTiltEllipseEnd();
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = pTiltEllArc->CalDirAngle(eAngle);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_Polyline:
							//***DrawPolyline***
							CMachineObjPolyline* pPolyline;
							pPolyline = (CMachineObjPolyline*)pObj1;
							ObjDir dir;
							int VertCount;
							double x0, y0, r, convexity;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							VertCount = pPolyline->GetPolylineVertexCount();
							Ovpoint1 = pPolyline->GetPolylineStart();
							Opoint1.x = Ovpoint1.x;
							Opoint1.y = Ovpoint1.y;
							Opointlast = Opoint1;
							convexity = Ovpoint1.convexity;
							point = TransRPtoLP(Opoint1);
							pDC->MoveTo(point);
							for (int i = 1; i < VertCount; i++)
							{
								Ovpoint1 = pPolyline->GetPolylinePoint(i);
								Opoint1.x = Ovpoint1.x;
								Opoint1.y = Ovpoint1.y;
								if (convexity == 0)
								{
									point = TransRPtoLP(Opoint1);
									pDC->LineTo(point);
									if (i < VertCount - 1)
									{
										Opointlast = Opoint1;
										convexity = Ovpoint1.convexity;
									}
								}
								else
								{
									ObjPoint ArcCenter;
									pPolyline->TranPolylineToArc(
										Opointlast, Opoint1, convexity,
										&ArcCenter, &r, &sAngle, &eAngle);
									x0 = ArcCenter.x;
									y0 = ArcCenter.y;
									dAngle = DrawArcStep;
									if (eAngle > sAngle)
									{
										dir = CCW;
										point = TransRPtoLP(Opointlast);
										pDC->MoveTo(point);
										sAngle += dAngle;
										while (sAngle < eAngle)
										{
											x = x0 + r*cos(sAngle / 180 * M_PI);
											y = y0 + r*sin(sAngle / 180 * M_PI);
											sAngle += dAngle;
											point = TransRPtoLP(ObjPoint(x, y));
											pDC->LineTo(point);
										}
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
									}
									else
									{
										dir = CW;
										point = TransRPtoLP(Opointlast);
										pDC->MoveTo(point);
										sAngle -= dAngle;
										while (sAngle > eAngle)
										{
											x = x0 + r*cos(sAngle / 180 * M_PI);
											y = y0 + r*sin(sAngle / 180 * M_PI);
											sAngle -= dAngle;
											point = TransRPtoLP(ObjPoint(x, y));
											pDC->LineTo(point);
										}
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
									}
									if (i < VertCount - 1)
									{
										Opointlast = Opoint1;
										convexity = Ovpoint1.convexity;
									}
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								if (convexity == 0)
									dirAngle = CalDirAngle(Opointlast, Opoint1);
								else
								{
									double dx = -r * sin(M_PI * eAngle / 180);
									double dy = r * cos(M_PI * eAngle / 180);
									if (dir == CCW)
									{
										if (dx > 0)
										{
											dirAngle = atan(dy / dx);
										}
										else if (dx < 0)
										{
											dirAngle = atan(dy / dx) + M_PI;
										}
										else
										{
											if (dy > 0)
												dirAngle = M_PI_2;
											else
												dirAngle = M_PI + M_PI_2;
										}
									}
									else
									{
										if (dx > 0)
										{
											dirAngle = atan(dy / dx) + M_PI;
										}
										else if (dx < 0)
										{
											dirAngle = atan(dy / dx);
										}
										else
										{
											if (dy < 0)
												dirAngle = M_PI_2;
											else
												dirAngle = M_PI + M_PI_2;
										}
									}
								}
								Opointlast = Opoint1;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_WLine:
							//***DrawWLine***
							CMachineObjWLine* pWLine;
							pWLine = (CMachineObjWLine*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);
							Opoint1 = pWLine->GetLineStart();
							point = TransRPtoLP(Opoint1);
							pDC->MoveTo(point);
							Opoint2 = pWLine->GetLineEnd();
							point = TransRPtoLP(Opoint2);
							pDC->LineTo(point);
							nCount = pWLine->m_pDupList.size();
							for (int i = 0; i < nCount; i++)
							{
								pVect = *pWLine->m_pDupList[i];
								pDC->MoveTo(TransRPtoLP(pVect[0]));
								pDC->LineTo(TransRPtoLP(pVect[1]));
							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = CalDirAngle(Opoint1, Opoint2);
								Opointlast = Opoint2;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);			//恢复老画笔
							break;
						case MachineObj_Type_WArc:
							//***DrawWArc***
							CMachineObjWArc* pWArc;
							pWArc = (CMachineObjWArc*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							sAngle = pWArc->GetStartAngle();
							eAngle = pWArc->GetEndAngle();
							dAngle = abs((eAngle - sAngle) / 3);		//**圆弧至少画4点**//
							if (dAngle > DrawArcStep)
								dAngle = DrawArcStep;
							dir = pWArc->GetArcDir();
							if (dir == CCW)
							{
								point = TransRPtoLP(pWArc->GetArcStart());
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									point = TransRPtoLP(pWArc->GetArcPoint(sAngle));
									sAngle += dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pWArc->GetArcEnd();
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							else
							{
								point = TransRPtoLP(pWArc->GetArcStart());
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									point = TransRPtoLP(pWArc->GetArcPoint(sAngle));
									sAngle -= dAngle;
									pDC->LineTo(point);
								}
								Opoint2 = pWArc->GetArcEnd();
								point = TransRPtoLP(Opoint2);
								pDC->LineTo(point);
							}
							Opointlast = Opoint2;
							point1 = point;
							nCount = pWArc->m_pDupList.size();
							Opoint1 = pWArc->GetArcCenter();
							for (int i = 0; i < nCount; i++)
							{
								pVect = *pWArc->m_pDupList[i];
								float r = (float)pVect[2].x;
								sAngle = pVect[1].x;
								eAngle = pVect[1].y;
								if (dir == CCW)
								{
									Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
									Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
									point = TransRPtoLP(Opoint2);
									pDC->MoveTo(point);
									sAngle += dAngle;
									while (sAngle < eAngle)
									{
										Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
										Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
										point = TransRPtoLP(Opoint2);
										sAngle += dAngle;
										pDC->LineTo(point);
									}
									Opoint2.x = Opoint1.x + r*cos(M_PI*eAngle / 180);
									Opoint2.y = Opoint1.y + r*sin(M_PI*eAngle / 180);
									point = TransRPtoLP(Opoint2);
									pDC->LineTo(point);
								}
								else
								{
									Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
									Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
									point = TransRPtoLP(Opoint2);
									pDC->MoveTo(point);
									sAngle -= dAngle;
									while (sAngle > eAngle)
									{
										Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
										Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
										point = TransRPtoLP(Opoint2);
										sAngle -= dAngle;
										pDC->LineTo(point);
									}
									Opoint2.x = Opoint1.x + r*cos(M_PI*eAngle / 180);
									Opoint2.y = Opoint1.y + r*sin(M_PI*eAngle / 180);
									point = TransRPtoLP(Opoint2);
									pDC->LineTo(point);
								}

							}
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								dirAngle = pWArc->CalDirAngle(eAngle);
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point = point1;
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_WPolyline:
							//***DrawWPolyline***
							CMachineObjWPolyline* pWPolyline;
							pWPolyline = (CMachineObjWPolyline*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
							VertCount = pWPolyline->GetPolylineVertexCount();
							Ovpoint1 = pWPolyline->GetPolylineStart();
							Opoint1.x = Ovpoint1.x;
							Opoint1.y = Ovpoint1.y;
							Opointlast = Opoint1;
							convexity = Ovpoint1.convexity;
							point = TransRPtoLP(Opoint1);
							pDC->MoveTo(point);
							for (int i = 1; i < VertCount; i++)
							{
								Ovpoint1 = pWPolyline->GetPolylinePoint(i);
								Opoint1.x = Ovpoint1.x;
								Opoint1.y = Ovpoint1.y;
								if (convexity == 0)
								{
									point = TransRPtoLP(Opoint1);
									pDC->LineTo(point);
									if (i < VertCount - 1)
									{
										Opointlast = Opoint1;
										convexity = Ovpoint1.convexity;
									}
								}
								else
								{
									ObjPoint ArcCenter;
									pWPolyline->TranPolylineToArc(
										Opointlast, Opoint1, convexity,
										&ArcCenter, &r, &sAngle, &eAngle);
									x0 = ArcCenter.x;
									y0 = ArcCenter.y;
									dAngle = DrawArcStep;
									if (eAngle > sAngle)
									{
										dir = CCW;
										point = TransRPtoLP(Opointlast);
										pDC->MoveTo(point);
										sAngle += dAngle;
										while (sAngle < eAngle)
										{
											x = x0 + r*cos(sAngle / 180 * M_PI);
											y = y0 + r*sin(sAngle / 180 * M_PI);
											sAngle += dAngle;
											point = TransRPtoLP(ObjPoint(x, y));
											pDC->LineTo(point);
										}
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
									}
									else
									{
										dir = CW;
										point = TransRPtoLP(Opointlast);
										pDC->MoveTo(point);
										sAngle -= dAngle;
										while (sAngle > eAngle)
										{
											x = x0 + r*cos(sAngle / 180 * M_PI);
											y = y0 + r*sin(sAngle / 180 * M_PI);
											sAngle -= dAngle;
											point = TransRPtoLP(ObjPoint(x, y));
											pDC->LineTo(point);
										}
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
									}
									if (i < VertCount - 1)
									{
										Opointlast = Opoint1;
										convexity = Ovpoint1.convexity;
									}
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							Opointlast_old = Opointlast;
							Opoint1_old = Opoint1;
							point_old = point;
							nCount = pWPolyline->m_pDupList.size();
							for (int j = 0; j < nCount; j++)
							{
								VectVpoint pVpoint = *pWPolyline->m_pDupList[j];
								VertCount = pVpoint.size();
								Ovpoint1 = pVpoint[0];
								Opoint1.x = Ovpoint1.x;
								Opoint1.y = Ovpoint1.y;
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
								point = TransRPtoLP(Opoint1);
								pDC->MoveTo(point);
								for (int i = 1; i < VertCount; i++)
								{
									Ovpoint1 = pVpoint[i];
									Opoint1.x = Ovpoint1.x;
									Opoint1.y = Ovpoint1.y;
									if (convexity == 0)
									{
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
										if (i < VertCount - 1)
										{
											Opointlast = Opoint1;
											convexity = Ovpoint1.convexity;
										}
									}
									else
									{
										ObjPoint ArcCenter;
										pWPolyline->TranPolylineToArc(
											Opointlast, Opoint1, convexity,
											&ArcCenter, &r, &sAngle, &eAngle);
										x0 = ArcCenter.x;
										y0 = ArcCenter.y;
										dAngle = DrawArcStep;
										if (eAngle > sAngle)
										{
											dir = CCW;
											point = TransRPtoLP(Opointlast);
											pDC->MoveTo(point);
											sAngle += dAngle;
											while (sAngle < eAngle)
											{
												x = x0 + r*cos(sAngle / 180 * M_PI);
												y = y0 + r*sin(sAngle / 180 * M_PI);
												sAngle += dAngle;
												point = TransRPtoLP(ObjPoint(x, y));
												pDC->LineTo(point);
											}
											point = TransRPtoLP(Opoint1);
											pDC->LineTo(point);
										}
										else
										{
											dir = CW;
											point = TransRPtoLP(Opointlast);
											pDC->MoveTo(point);
											sAngle -= dAngle;
											while (sAngle > eAngle)
											{
												x = x0 + r*cos(sAngle / 180 * M_PI);
												y = y0 + r*sin(sAngle / 180 * M_PI);
												sAngle -= dAngle;
												point = TransRPtoLP(ObjPoint(x, y));
												pDC->LineTo(point);
											}
											point = TransRPtoLP(Opoint1);
											pDC->LineTo(point);
										}
										if (i < VertCount - 1)
										{
											Opointlast = Opoint1;
											convexity = Ovpoint1.convexity;
										}
									}
									point = TransRPtoLP(Opoint1);
									pDC->LineTo(point);
								}
							}
							point = point_old;
							Opoint1 = Opoint1_old;
							Opointlast = Opointlast_old;
							if (Dispdir)
							{
								pDC->SelectObject(&Pen6);
								if (convexity == 0)
									dirAngle = CalDirAngle(Opointlast, Opoint1);
								else
								{
									double dx = -r * sin(M_PI * eAngle / 180);
									double dy = r * cos(M_PI * eAngle / 180);
									if (dir == CCW)
									{
										if (dx > 0)
										{
											dirAngle = atan(dy / dx);
										}
										else if (dx < 0)
										{
											dirAngle = atan(dy / dx) + M_PI;
										}
										else
										{
											if (dy > 0)
												dirAngle = M_PI_2;
											else
												dirAngle = M_PI + M_PI_2;
										}
									}
									else
									{
										if (dx > 0)
										{
											dirAngle = atan(dy / dx) + M_PI;
										}
										else if (dx < 0)
										{
											dirAngle = atan(dy / dx);
										}
										else
										{
											if (dy < 0)
												dirAngle = M_PI_2;
											else
												dirAngle = M_PI + M_PI_2;
										}
									}
								}
								Opointlast = Opoint1;
								CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
								point1 = TransRPtoLP(Opoint1);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
								point1 = TransRPtoLP(Opoint2);
								pDC->MoveTo(point1);
								pDC->LineTo(point);
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;
						case MachineObj_Type_FillPolyline:
							//***DrawWPolyline***
							CMachineObjFillPolyline* pFillPolyline;
							pFillPolyline = (CMachineObjFillPolyline*)pObj1;
							if (Sel)
								pNewPen = &Pen1;
							else if (LayerNum == 0)
								pNewPen = &Pen2;
							else if (LayerNum == 1)
								pNewPen = &Pen3;
							else
								pNewPen = &Pen4;
							pOldPen = pDC->SelectObject(pNewPen);
							if (pFillPolyline->GetOutlinePrior() == 0)
							{
								FillLine = pFillPolyline->m_FillLine;
								nCount = FillLine.size();
								for (int i = 0; i < nCount; i++)
								{
									Opoint1 = FillLine[i].StartPoint;
									point = TransRPtoLP(Opoint1);
									pDC->MoveTo(point);
									Opoint2 = FillLine[i].EndPoint;
									point = TransRPtoLP(Opoint2);
									pDC->LineTo(point);
								}
							}
							else if (pFillPolyline->GetOutlinePrior() == 1)
							{
								FillLine = pFillPolyline->m_FillLine;
								nCount = FillLine.size();
								for (int i = 0; i < nCount; i++)
								{
									Opoint1 = FillLine[i].StartPoint;
									point = TransRPtoLP(Opoint1);
									pDC->MoveTo(point);
									Opoint2 = FillLine[i].EndPoint;
									point = TransRPtoLP(Opoint2);
									pDC->LineTo(point);
								}
								VertCount = pFillPolyline->GetPolylineVertexCount();
								Ovpoint1 = pFillPolyline->GetPolylineStart();
								Opoint1.x = Ovpoint1.x;
								Opoint1.y = Ovpoint1.y;
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
								point = TransRPtoLP(Opoint1);
								pDC->MoveTo(point);
								for (int i = 1; i < VertCount; i++)
								{
									Ovpoint1 = pFillPolyline->GetPolylinePoint(i);
									Opoint1.x = Ovpoint1.x;
									Opoint1.y = Ovpoint1.y;
									if (convexity == 0)
									{
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
										if (i < VertCount - 1)
										{
											Opointlast = Opoint1;
											convexity = Ovpoint1.convexity;
										}
									}
									else
									{
										ObjPoint ArcCenter;
										pFillPolyline->TranPolylineToArc(
											Opointlast, Opoint1, convexity,
											&ArcCenter, &r, &sAngle, &eAngle);
										x0 = ArcCenter.x;
										y0 = ArcCenter.y;
										dAngle = DrawArcStep;
										if (eAngle > sAngle)
										{
											dir = CCW;
											point = TransRPtoLP(Opointlast);
											pDC->MoveTo(point);
											sAngle += dAngle;
											while (sAngle < eAngle)
											{
												x = x0 + r*cos(sAngle / 180 * M_PI);
												y = y0 + r*sin(sAngle / 180 * M_PI);
												sAngle += dAngle;
												point = TransRPtoLP(ObjPoint(x, y));
												pDC->LineTo(point);
											}
											point = TransRPtoLP(Opoint1);
											pDC->LineTo(point);
										}
										else
										{
											dir = CW;
											point = TransRPtoLP(Opointlast);
											pDC->MoveTo(point);
											sAngle -= dAngle;
											while (sAngle > eAngle)
											{
												x = x0 + r*cos(sAngle / 180 * M_PI);
												y = y0 + r*sin(sAngle / 180 * M_PI);
												sAngle -= dAngle;
												point = TransRPtoLP(ObjPoint(x, y));
												pDC->LineTo(point);
											}
											point = TransRPtoLP(Opoint1);
											pDC->LineTo(point);
										}
										if (i < VertCount - 1)
										{
											Opointlast = Opoint1;
											convexity = Ovpoint1.convexity;
										}
									}
									point = TransRPtoLP(Opoint1);
									pDC->LineTo(point);
								}
								if (Dispdir)
								{
									pDC->SelectObject(&Pen6);
									if (convexity == 0)
										dirAngle = CalDirAngle(Opointlast, Opoint1);
									else
									{
										double dx = -r * sin(M_PI * eAngle / 180);
										double dy = r * cos(M_PI * eAngle / 180);
										if (dir == CCW)
										{
											if (dx > 0)
											{
												dirAngle = atan(dy / dx);
											}
											else if (dx < 0)
											{
												dirAngle = atan(dy / dx) + M_PI;
											}
											else
											{
												if (dy > 0)
													dirAngle = M_PI_2;
												else
													dirAngle = M_PI + M_PI_2;
											}
										}
										else
										{
											if (dx > 0)
											{
												dirAngle = atan(dy / dx) + M_PI;
											}
											else if (dx < 0)
											{
												dirAngle = atan(dy / dx);
											}
											else
											{
												if (dy < 0)
													dirAngle = M_PI_2;
												else
													dirAngle = M_PI + M_PI_2;
											}
										}
									}
									Opointlast = Opoint1;
									CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
									point1 = TransRPtoLP(Opoint1);
									pDC->MoveTo(point1);
									pDC->LineTo(point);
									point1 = TransRPtoLP(Opoint2);
									pDC->MoveTo(point1);
									pDC->LineTo(point);
								}
							}
							else
							{
								VertCount = pFillPolyline->GetPolylineVertexCount();
								Ovpoint1 = pFillPolyline->GetPolylineStart();
								Opoint1.x = Ovpoint1.x;
								Opoint1.y = Ovpoint1.y;
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
								point = TransRPtoLP(Opoint1);
								pDC->MoveTo(point);
								for (int i = 1; i < VertCount; i++)
								{
									Ovpoint1 = pFillPolyline->GetPolylinePoint(i);
									Opoint1.x = Ovpoint1.x;
									Opoint1.y = Ovpoint1.y;
									if (convexity == 0)
									{
										point = TransRPtoLP(Opoint1);
										pDC->LineTo(point);
										if (i < VertCount - 1)
										{
											Opointlast = Opoint1;
											convexity = Ovpoint1.convexity;
										}
									}
									else
									{
										ObjPoint ArcCenter;
										pFillPolyline->TranPolylineToArc(
											Opointlast, Opoint1, convexity,
											&ArcCenter, &r, &sAngle, &eAngle);
										x0 = ArcCenter.x;
										y0 = ArcCenter.y;
										dAngle = DrawArcStep;
										if (eAngle > sAngle)
										{
											dir = CCW;
											point = TransRPtoLP(Opointlast);
											pDC->MoveTo(point);
											sAngle += dAngle;
											while (sAngle < eAngle)
											{
												x = x0 + r*cos(sAngle / 180 * M_PI);
												y = y0 + r*sin(sAngle / 180 * M_PI);
												sAngle += dAngle;
												point = TransRPtoLP(ObjPoint(x, y));
												pDC->LineTo(point);
											}
											point = TransRPtoLP(Opoint1);
											pDC->LineTo(point);
										}
										else
										{
											dir = CW;
											point = TransRPtoLP(Opointlast);
											pDC->MoveTo(point);
											sAngle -= dAngle;
											while (sAngle > eAngle)
											{
												x = x0 + r*cos(sAngle / 180 * M_PI);
												y = y0 + r*sin(sAngle / 180 * M_PI);
												sAngle -= dAngle;
												point = TransRPtoLP(ObjPoint(x, y));
												pDC->LineTo(point);
											}
											point = TransRPtoLP(Opoint1);
											pDC->LineTo(point);
										}
										if (i < VertCount - 1)
										{
											Opointlast = Opoint1;
											convexity = Ovpoint1.convexity;
										}
									}
									point = TransRPtoLP(Opoint1);
									pDC->LineTo(point);
								}
								Opointlast_old = Opointlast;
								Opoint1_old = Opoint1;
								point_old = point;
								FillLine = pFillPolyline->m_FillLine;
								nCount = FillLine.size();
								for (int i = 0; i < nCount; i++)
								{
									Opoint1 = FillLine[i].StartPoint;
									point = TransRPtoLP(Opoint1);
									pDC->MoveTo(point);
									Opoint2 = FillLine[i].EndPoint;
									point = TransRPtoLP(Opoint2);
									pDC->LineTo(point);
								}
								point = point_old;
								Opoint1 = Opoint1_old;
								Opointlast = Opointlast_old;
								if (Dispdir)
								{
									pDC->SelectObject(&Pen6);
									if (convexity == 0)
										dirAngle = CalDirAngle(Opointlast, Opoint1);
									else
									{
										double dx = -r * sin(M_PI * eAngle / 180);
										double dy = r * cos(M_PI * eAngle / 180);
										if (dir == CCW)
										{
											if (dx > 0)
											{
												dirAngle = atan(dy / dx);
											}
											else if (dx < 0)
											{
												dirAngle = atan(dy / dx) + M_PI;
											}
											else
											{
												if (dy > 0)
													dirAngle = M_PI_2;
												else
													dirAngle = M_PI + M_PI_2;
											}
										}
										else
										{
											if (dx > 0)
											{
												dirAngle = atan(dy / dx) + M_PI;
											}
											else if (dx < 0)
											{
												dirAngle = atan(dy / dx);
											}
											else
											{
												if (dy < 0)
													dirAngle = M_PI_2;
												else
													dirAngle = M_PI + M_PI_2;
											}
										}
									}
									Opointlast = Opoint1;
									CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
									point1 = TransRPtoLP(Opoint1);
									pDC->MoveTo(point1);
									pDC->LineTo(point);
									point1 = TransRPtoLP(Opoint2);
									pDC->MoveTo(point1);
									pDC->LineTo(point);
								}
							}
							pDC->SelectObject(pOldPen);					//恢复老画笔
							break;

						default:
							break;
						}
					}
				}
				ObjDispList->RemoveAll();
				delete ObjDispList;
				break;
		//*****************Group End*******************//
			case MachineObj_Type_WLine:
				//***DrawWLine***
				CMachineObjWLine* pWLine;
				pWLine = (CMachineObjWLine*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);
				Opoint1 = pWLine->GetLineStart();
				point = TransRPtoLP(Opoint1);
				pDC->MoveTo(point);
				Opoint2 = pWLine->GetLineEnd();
				point = TransRPtoLP(Opoint2);
				pDC->LineTo(point);
				nCount = pWLine->m_pDupList.size();
				for (int i = 0; i < nCount; i++)
				{
					pVect = *pWLine->m_pDupList[i];
					pDC->MoveTo(TransRPtoLP(pVect[0]));
					pDC->LineTo(TransRPtoLP(pVect[1]));
				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = CalDirAngle(Opoint1, Opoint2);
					Opointlast = Opoint2;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);			//恢复老画笔
				break;
		//*****************WLine End*******************//
			case MachineObj_Type_WArc:
				//***DrawWArc***
				CMachineObjWArc* pWArc;
				pWArc = (CMachineObjWArc*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				sAngle = pWArc->GetStartAngle();
				eAngle = pWArc->GetEndAngle();
				dAngle = abs((eAngle - sAngle) / 3);		//**圆弧至少画4点**//
				if (dAngle > DrawArcStep)
					dAngle = DrawArcStep;
				dir = pWArc->GetArcDir();
				if (dir == CCW)
				{
					point = TransRPtoLP(pWArc->GetArcStart());
					pDC->MoveTo(point);
					sAngle += dAngle;
					while (sAngle < eAngle)
					{
						point = TransRPtoLP(pWArc->GetArcPoint(sAngle));
						sAngle += dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pWArc->GetArcEnd();
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				else
				{
					point = TransRPtoLP(pWArc->GetArcStart());
					pDC->MoveTo(point);
					sAngle -= dAngle;
					while (sAngle > eAngle)
					{
						point = TransRPtoLP(pWArc->GetArcPoint(sAngle));
						sAngle -= dAngle;
						pDC->LineTo(point);
					}
					Opoint2 = pWArc->GetArcEnd();
					point = TransRPtoLP(Opoint2);
					pDC->LineTo(point);
				}
				Opointlast = Opoint2;
				point1 = point;
				nCount = pWArc->m_pDupList.size();
				Opoint1 = pWArc->GetArcCenter();
				for (int i = 0; i < nCount; i++)
				{
					pVect = *pWArc->m_pDupList[i];
					float r = (float)pVect[2].x;
					sAngle = pVect[1].x;
					eAngle = pVect[1].y;
					if (dir == CCW)
					{
						Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
						Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
						point = TransRPtoLP(Opoint2);
						pDC->MoveTo(point);
						sAngle += dAngle;
						while (sAngle < eAngle)
						{
							Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
							Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
							point = TransRPtoLP(Opoint2);
							sAngle += dAngle;
							pDC->LineTo(point);
						}
						Opoint2.x = Opoint1.x + r*cos(M_PI*eAngle / 180);
						Opoint2.y = Opoint1.y + r*sin(M_PI*eAngle / 180);
						point = TransRPtoLP(Opoint2);
						pDC->LineTo(point);
					}
					else
					{
						Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
						Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
						point = TransRPtoLP(Opoint2);
						pDC->MoveTo(point);
						sAngle -= dAngle;
						while (sAngle > eAngle)
						{
							Opoint2.x = Opoint1.x + r*cos(M_PI*sAngle / 180);
							Opoint2.y = Opoint1.y + r*sin(M_PI*sAngle / 180);
							point = TransRPtoLP(Opoint2);
							sAngle -= dAngle;
							pDC->LineTo(point);
						}
						Opoint2.x = Opoint1.x + r*cos(M_PI*eAngle / 180);
						Opoint2.y = Opoint1.y + r*sin(M_PI*eAngle / 180);
						point = TransRPtoLP(Opoint2);
						pDC->LineTo(point);
					}

				}
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					dirAngle = pWArc->CalDirAngle(eAngle);
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point = point1;
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************WArc End*******************//
			case MachineObj_Type_WPolyline:
				//***DrawWPolyline***
				CMachineObjWPolyline* pWPolyline;
				pWPolyline = (CMachineObjWPolyline*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);		//选画笔并保存老画笔
				VertCount = pWPolyline->GetPolylineVertexCount();
				Ovpoint1 = pWPolyline->GetPolylineStart();
				Opoint1.x = Ovpoint1.x;
				Opoint1.y = Ovpoint1.y;
				Opointlast = Opoint1;
				convexity = Ovpoint1.convexity;
				point = TransRPtoLP(Opoint1);
				pDC->MoveTo(point);
				for (int i = 1; i < VertCount; i++)
				{
					Ovpoint1 = pWPolyline->GetPolylinePoint(i);
					Opoint1.x = Ovpoint1.x;
					Opoint1.y = Ovpoint1.y;
					if (convexity == 0)
					{
						point = TransRPtoLP(Opoint1);
						pDC->LineTo(point);
						if (i < VertCount - 1)
						{
							Opointlast = Opoint1;
							convexity = Ovpoint1.convexity;
						}
					}
					else
					{
						ObjPoint ArcCenter;
						pWPolyline->TranPolylineToArc(
							Opointlast, Opoint1, convexity,
							&ArcCenter, &r, &sAngle, &eAngle);
						x0 = ArcCenter.x;
						y0 = ArcCenter.y;
						dAngle = DrawArcStep;
						if (eAngle > sAngle)
						{
							dir = CCW;
							point = TransRPtoLP(Opointlast);
							pDC->MoveTo(point);
							sAngle += dAngle;
							while (sAngle < eAngle)
							{
								x = x0 + r*cos(sAngle / 180 * M_PI);
								y = y0 + r*sin(sAngle / 180 * M_PI);
								sAngle += dAngle;
								point = TransRPtoLP(ObjPoint(x, y));
								pDC->LineTo(point);
							}
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
						}
						else
						{
							dir = CW;
							point = TransRPtoLP(Opointlast);
							pDC->MoveTo(point);
							sAngle -= dAngle;
							while (sAngle > eAngle)
							{
								x = x0 + r*cos(sAngle / 180 * M_PI);
								y = y0 + r*sin(sAngle / 180 * M_PI);
								sAngle -= dAngle;
								point = TransRPtoLP(ObjPoint(x, y));
								pDC->LineTo(point);
							}
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
						}
						if (i < VertCount - 1)
						{
							Opointlast = Opoint1;
							convexity = Ovpoint1.convexity;
						}
					}
					point = TransRPtoLP(Opoint1);
					pDC->LineTo(point);
				}
				Opointlast_old = Opointlast;
				Opoint1_old = Opoint1;
				point_old = point;
				nCount = pWPolyline->m_pDupList.size();
				for (int j = 0; j < nCount; j++)
				{
					VectVpoint pVpoint = *pWPolyline->m_pDupList[j];
					VertCount = pVpoint.size();
					Ovpoint1 = pVpoint[0];
					Opoint1.x = Ovpoint1.x;
					Opoint1.y = Ovpoint1.y;
					Opointlast = Opoint1;
					convexity = Ovpoint1.convexity;
					point = TransRPtoLP(Opoint1);
					pDC->MoveTo(point);
					for (int i = 1; i < VertCount; i++)
					{
						Ovpoint1 = pVpoint[i];
						Opoint1.x = Ovpoint1.x;
						Opoint1.y = Ovpoint1.y;
						if (convexity == 0)
						{
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
							if (i < VertCount - 1)
							{
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
							}
						}
						else
						{
							ObjPoint ArcCenter;
							pWPolyline->TranPolylineToArc(
								Opointlast, Opoint1, convexity,
								&ArcCenter, &r, &sAngle, &eAngle);
							x0 = ArcCenter.x;
							y0 = ArcCenter.y;
							dAngle = DrawArcStep;
							if (eAngle > sAngle)
							{
								dir = CCW;
								point = TransRPtoLP(Opointlast);
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									x = x0 + r*cos(sAngle / 180 * M_PI);
									y = y0 + r*sin(sAngle / 180 * M_PI);
									sAngle += dAngle;
									point = TransRPtoLP(ObjPoint(x, y));
									pDC->LineTo(point);
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							else
							{
								dir = CW;
								point = TransRPtoLP(Opointlast);
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									x = x0 + r*cos(sAngle / 180 * M_PI);
									y = y0 + r*sin(sAngle / 180 * M_PI);
									sAngle -= dAngle;
									point = TransRPtoLP(ObjPoint(x, y));
									pDC->LineTo(point);
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							if (i < VertCount - 1)
							{
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
							}
						}
						point = TransRPtoLP(Opoint1);
						pDC->LineTo(point);
					}
				}
				point = point_old;
				Opoint1 = Opoint1_old;
				Opointlast = Opointlast_old;
				if (Dispdir)
				{
					pDC->SelectObject(&Pen6);
					if (convexity == 0)
						dirAngle = CalDirAngle(Opointlast, Opoint1);
					else
					{
						double dx = -r * sin(M_PI * eAngle / 180);
						double dy = r * cos(M_PI * eAngle / 180);
						if (dir == CCW)
						{
							if (dx > 0)
							{
								dirAngle = atan(dy / dx);
							}
							else if (dx < 0)
							{
								dirAngle = atan(dy / dx) + M_PI;
							}
							else
							{
								if (dy > 0)
									dirAngle = M_PI_2;
								else
									dirAngle = M_PI + M_PI_2;
							}
						}
						else
						{
							if (dx > 0)
							{
								dirAngle = atan(dy / dx) + M_PI;
							}
							else if (dx < 0)
							{
								dirAngle = atan(dy / dx);
							}
							else
							{
								if (dy < 0)
									dirAngle = M_PI_2;
								else
									dirAngle = M_PI + M_PI_2;
							}
						}
					}
					Opointlast = Opoint1;
					CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
					point1 = TransRPtoLP(Opoint1);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
					point1 = TransRPtoLP(Opoint2);
					pDC->MoveTo(point1);
					pDC->LineTo(point);
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************WPolyline End*******************//
			case MachineObj_Type_FillPolyline:
				CMachineObjFillPolyline* pFillPolyline;
				pFillPolyline = (CMachineObjFillPolyline*)pObj;
				if (Sel)
					pNewPen = &Pen1;
				else if (LayerNum == 0)
					pNewPen = &Pen2;
				else if (LayerNum == 1)
					pNewPen = &Pen3;
				else
					pNewPen = &Pen4;
				pOldPen = pDC->SelectObject(pNewPen);
				if (pFillPolyline->GetOutlinePrior() == 0)
				{
					FillLine = pFillPolyline->m_FillLine;
					nCount = FillLine.size();
					for (int i = 0; i < nCount; i++)
					{
						Opoint1 = FillLine[i].StartPoint;
						point = TransRPtoLP(Opoint1);
						pDC->MoveTo(point);
						Opoint2 = FillLine[i].EndPoint;
						point = TransRPtoLP(Opoint2);
						pDC->LineTo(point);
					}
				}
				else if (pFillPolyline->GetOutlinePrior() == 1)
				{
					FillLine = pFillPolyline->m_FillLine;
					nCount = FillLine.size();
					for (int i = 0; i < nCount; i++)
					{
						Opoint1 = FillLine[i].StartPoint;
						point = TransRPtoLP(Opoint1);
						pDC->MoveTo(point);
						Opoint2 = FillLine[i].EndPoint;
						point = TransRPtoLP(Opoint2);
						pDC->LineTo(point);
					}
					VertCount = pFillPolyline->GetPolylineVertexCount();
					Ovpoint1 = pFillPolyline->GetPolylineStart();
					Opoint1.x = Ovpoint1.x;
					Opoint1.y = Ovpoint1.y;
					Opointlast = Opoint1;
					convexity = Ovpoint1.convexity;
					point = TransRPtoLP(Opoint1);
					pDC->MoveTo(point);
					for (int i = 1; i < VertCount; i++)
					{
						Ovpoint1 = pFillPolyline->GetPolylinePoint(i);
						Opoint1.x = Ovpoint1.x;
						Opoint1.y = Ovpoint1.y;
						if (convexity == 0)
						{
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
							if (i < VertCount - 1)
							{
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
							}
						}
						else
						{
							ObjPoint ArcCenter;
							pFillPolyline->TranPolylineToArc(
								Opointlast, Opoint1, convexity,
								&ArcCenter, &r, &sAngle, &eAngle);
							x0 = ArcCenter.x;
							y0 = ArcCenter.y;
							dAngle = DrawArcStep;
							if (eAngle > sAngle)
							{
								dir = CCW;
								point = TransRPtoLP(Opointlast);
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									x = x0 + r*cos(sAngle / 180 * M_PI);
									y = y0 + r*sin(sAngle / 180 * M_PI);
									sAngle += dAngle;
									point = TransRPtoLP(ObjPoint(x, y));
									pDC->LineTo(point);
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							else
							{
								dir = CW;
								point = TransRPtoLP(Opointlast);
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									x = x0 + r*cos(sAngle / 180 * M_PI);
									y = y0 + r*sin(sAngle / 180 * M_PI);
									sAngle -= dAngle;
									point = TransRPtoLP(ObjPoint(x, y));
									pDC->LineTo(point);
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							if (i < VertCount - 1)
							{
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
							}
						}
						point = TransRPtoLP(Opoint1);
						pDC->LineTo(point);
					}
					if (Dispdir)
					{
						pDC->SelectObject(&Pen6);
						if (convexity == 0)
							dirAngle = CalDirAngle(Opointlast, Opoint1);
						else
						{
							double dx = -r * sin(M_PI * eAngle / 180);
							double dy = r * cos(M_PI * eAngle / 180);
							if (dir == CCW)
							{
								if (dx > 0)
								{
									dirAngle = atan(dy / dx);
								}
								else if (dx < 0)
								{
									dirAngle = atan(dy / dx) + M_PI;
								}
								else
								{
									if (dy > 0)
										dirAngle = M_PI_2;
									else
										dirAngle = M_PI + M_PI_2;
								}
							}
							else
							{
								if (dx > 0)
								{
									dirAngle = atan(dy / dx) + M_PI;
								}
								else if (dx < 0)
								{
									dirAngle = atan(dy / dx);
								}
								else
								{
									if (dy < 0)
										dirAngle = M_PI_2;
									else
										dirAngle = M_PI + M_PI_2;
								}
							}
						}
						Opointlast = Opoint1;
						CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
						point1 = TransRPtoLP(Opoint1);
						pDC->MoveTo(point1);
						pDC->LineTo(point);
						point1 = TransRPtoLP(Opoint2);
						pDC->MoveTo(point1);
						pDC->LineTo(point);
					}
				}
				else
				{
					VertCount = pFillPolyline->GetPolylineVertexCount();
					Ovpoint1 = pFillPolyline->GetPolylineStart();
					Opoint1.x = Ovpoint1.x;
					Opoint1.y = Ovpoint1.y;
					Opointlast = Opoint1;
					convexity = Ovpoint1.convexity;
					point = TransRPtoLP(Opoint1);
					pDC->MoveTo(point);
					for (int i = 1; i < VertCount; i++)
					{
						Ovpoint1 = pFillPolyline->GetPolylinePoint(i);
						Opoint1.x = Ovpoint1.x;
						Opoint1.y = Ovpoint1.y;
						if (convexity == 0)
						{
							point = TransRPtoLP(Opoint1);
							pDC->LineTo(point);
							if (i < VertCount - 1)
							{
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
							}
						}
						else
						{
							ObjPoint ArcCenter;
							pFillPolyline->TranPolylineToArc(
								Opointlast, Opoint1, convexity,
								&ArcCenter, &r, &sAngle, &eAngle);
							x0 = ArcCenter.x;
							y0 = ArcCenter.y;
							dAngle = DrawArcStep;
							if (eAngle > sAngle)
							{
								dir = CCW;
								point = TransRPtoLP(Opointlast);
								pDC->MoveTo(point);
								sAngle += dAngle;
								while (sAngle < eAngle)
								{
									x = x0 + r*cos(sAngle / 180 * M_PI);
									y = y0 + r*sin(sAngle / 180 * M_PI);
									sAngle += dAngle;
									point = TransRPtoLP(ObjPoint(x, y));
									pDC->LineTo(point);
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							else
							{
								dir = CW;
								point = TransRPtoLP(Opointlast);
								pDC->MoveTo(point);
								sAngle -= dAngle;
								while (sAngle > eAngle)
								{
									x = x0 + r*cos(sAngle / 180 * M_PI);
									y = y0 + r*sin(sAngle / 180 * M_PI);
									sAngle -= dAngle;
									point = TransRPtoLP(ObjPoint(x, y));
									pDC->LineTo(point);
								}
								point = TransRPtoLP(Opoint1);
								pDC->LineTo(point);
							}
							if (i < VertCount - 1)
							{
								Opointlast = Opoint1;
								convexity = Ovpoint1.convexity;
							}
						}
						point = TransRPtoLP(Opoint1);
						pDC->LineTo(point);
					}
					Opointlast_old = Opointlast;
					Opoint1_old = Opoint1;
					point_old = point;
					FillLine = pFillPolyline->m_FillLine;
					nCount = FillLine.size();
					for (int i = 0; i < nCount; i++)
					{
						Opoint1 = FillLine[i].StartPoint;
						point = TransRPtoLP(Opoint1);
						pDC->MoveTo(point);
						Opoint2 = FillLine[i].EndPoint;
						point = TransRPtoLP(Opoint2);
						pDC->LineTo(point);
					}
					point = point_old;
					Opoint1 = Opoint1_old;
					Opointlast = Opointlast_old;
					if (Dispdir)
					{
						pDC->SelectObject(&Pen6);
						if (convexity == 0)
							dirAngle = CalDirAngle(Opointlast, Opoint1);
						else
						{
							double dx = -r * sin(M_PI * eAngle / 180);
							double dy = r * cos(M_PI * eAngle / 180);
							if (dir == CCW)
							{
								if (dx > 0)
								{
									dirAngle = atan(dy / dx);
								}
								else if (dx < 0)
								{
									dirAngle = atan(dy / dx) + M_PI;
								}
								else
								{
									if (dy > 0)
										dirAngle = M_PI_2;
									else
										dirAngle = M_PI + M_PI_2;
								}
							}
							else
							{
								if (dx > 0)
								{
									dirAngle = atan(dy / dx) + M_PI;
								}
								else if (dx < 0)
								{
									dirAngle = atan(dy / dx);
								}
								else
								{
									if (dy < 0)
										dirAngle = M_PI_2;
									else
										dirAngle = M_PI + M_PI_2;
								}
							}
						}
						Opointlast = Opoint1;
						CalArrow(Opointlast, dirAngle, ZoomFactor, &Opoint1, &Opoint2);
						point1 = TransRPtoLP(Opoint1);
						pDC->MoveTo(point1);
						pDC->LineTo(point);
						point1 = TransRPtoLP(Opoint2);
						pDC->MoveTo(point1);
						pDC->LineTo(point);
					}
				}
				pDC->SelectObject(pOldPen);					//恢复老画笔
				break;
		//*****************FillPolyline End*******************//
			default:
				break;
			}
		}
	}
}

void CMachineListContainer::ObjToDispList(CMachineObj_Comm* pObj, CMachineObjList* DispList)
{
	CMachineObj_Comm* pObj1;
	CMachineObjList* pList;
	POSITION pos;
	pList = ((CMachineObjGroup*)pObj)->GetObjList();
	pos = pList->GetHeadPosition();
	while (pos)
	{
		pObj1 = pList->GetNext(pos);
		if (pObj1->GetObjType() != MachineObj_Type_Group)
			DispList->AddTail(pObj1);
		else
			ObjToDispList(pObj1, DispList);
	}
}


//****************


//*******************以下是dxf文件的解析****************
BOOL CMachineListContainer::Parsedxf(LPCTSTR lpszPathName)
{
	CString CADVer;
	if (!Parsedxf(lpszPathName, &CADVer))
		return FALSE;
	LayerRename(CADVer);
	return TRUE;
}

BOOL CMachineListContainer::Parsedxf(LPCTSTR lpszPathName, CString* CADVer)
{
	int nFileCount = 0;
	CString strLine, str;
	if (!file.Open(lpszPathName, CFile::modeRead))
		return FALSE;
	while (file.ReadString(strLine))
	{
		if (strLine == "EOF")
		{
			file.Close();	//异常结束
			return FALSE;	//dxf文件解析错误
		}
		if (strLine == "$ACADVER")
		{
			file.ReadString(strLine);
			strLine.Remove(' ');
			if (strLine != '1')
			{
				file.Close();		
				return FALSE;	//dxf文件解析错误
			}
			file.ReadString(strLine);
			*CADVer = strLine;	//dxf版本信息
			break;
		}
	}
	file.SeekToBegin();
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine != "0")		//段起始组码"0"(第一行)
		{
			file.Close();		//错误文件格式
			return FALSE;
		}
		if (!file.ReadString(strLine))
		{
			file.Close();		//非正常结尾
			return FALSE;
		}
		strLine.Remove(' ');
		if (strLine == "EOF")
		{
			file.Close();		//dxf文件结束
			if (IsEmptyObj())
				return FALSE;	//空文件
			return TRUE;	//dxf文件正确解析
		}
		if (strLine != _T("SECTION"))	//段标识"SECTION"(第二行)
		{
			file.Close();	//错误文件格式
			return FALSE;
		}
		if (!file.ReadString(strLine))
		{
			file.Close();	//非正常结尾
			return FALSE;
		}
		strLine.Remove(' ');
		if (strLine != "2")		//段名组码"2"
		{
			file.Close();	//错误文件格式
			return FALSE;
		}
		if (!file.ReadString(strLine))
		{
			file.Close();	//非正常结尾
			return FALSE;
		}
		strLine.Remove(' ');
		if (strLine == "HEADER")	//HEADER段
		{
			if(!Parsedxf_Header())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else if (strLine == "CLASSES")	//CLASSES段
		{
			if (!Parsedxf_Classed())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else if (strLine == "TABLES")	//TABLES段
		{
			if (!Parsedxf_Tables())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else if (strLine == "BLOCKS")	//BLOCKS段
		{
			if (!Parsedxf_Blocks())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else if (strLine == "ENTITIES")	//ENTITIES段
		{
			if (!Parsedxf_Entities())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else if (strLine == "OBJECTS")	//OBJECTS段
		{
			if (!Parsedxf_Objects())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else if (strLine == "THUMBNAILIMAGE")	//THUMBNAILIMAGE段
		{
			if (!Parsedxf_Thumbnail())
			{
				file.Close();	//错误文件格式
				return FALSE;
			}
		}
		else
		{
			file.Close();	//错误文件格式
			return FALSE;
		}
	}
	file.Close();
	if (IsEmptyObj())
		return FALSE;
	return TRUE;
}

BOOL CMachineListContainer::Parsedxf_Find(CString GroupCode, CString GroupName)
{
	CString strLine;
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine == GroupCode)
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return FALSE;
			}
			strLine.Remove(' ');
			if (strLine == GroupName)
				return TRUE;
		}
//		else if (strLine == _T("0"))
//			return FALSE;			//出现组码"0",直接返回
	}
	return FALSE;
}

BOOL CMachineListContainer::Parsedxf_Find(CString GroupCode)
{
	CString strLine;
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine == GroupCode)
			return TRUE;
	}
	return FALSE;
}

CString  CMachineListContainer::Parsedxf_FindExlt()
{
	CString strLine;
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine == _T("10") || strLine == _T("42")
			|| strLine == _T("0"))
		{
			return strLine;
		}
		else
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return _T(" ");
			}
		}
	}
	return _T(" ");
}

BOOL CMachineListContainer::Parsedxf_FindEns()
{
	CString strLine;
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine == _T("ENDSEC"))
			return TRUE;
	}
	return FALSE;
}

BOOL CMachineListContainer::Parsedxf_Header()
{
	if (Parsedxf_FindEns())
		return TRUE;
	else
		return FALSE;
}

BOOL CMachineListContainer::Parsedxf_Classed()
{
	if (Parsedxf_FindEns())
		return TRUE;
	else
		return FALSE;
}

BOOL CMachineListContainer::Parsedxf_Tables()
{
	if (Parsedxf_FindEns())
		return TRUE;
	else
		return FALSE;
}

BOOL CMachineListContainer::Parsedxf_Blocks()
{
	if (Parsedxf_FindEns())
		return TRUE;
	else
		return FALSE;
}

BOOL CMachineListContainer::Parsedxf_GetValue(CString Code, double* value)
{
	CString strLine;
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine == Code)
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return FALSE;
			}
			strLine.Remove(' ');
			*value = _ttof(strLine);
			return TRUE;
		}
	}
	return FALSE;	//文件格式错误
}

int  CMachineListContainer::Parsedxf_GetValue(CString Code1, CString Code2, double* value1, double* value2)
{
	CString strLine;
	int nRtn = 0;
	while (file.ReadString(strLine))
	{
		strLine.Remove(' ');
		if (strLine == Code2)
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return -1;
			}
			strLine.Remove(' ');
			*value2 = _ttof(strLine);
			return nRtn;
		}
		else if (strLine == Code1)
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return -1;
			}
			strLine.Remove(' ');
			*value1 = _ttof(strLine);
			nRtn++;
		}
	}
	return -1;
}

BOOL CMachineListContainer::Parsedxf_Objects()
{
	CString strLine;
	while (file.ReadString(strLine))
	{
		//		strLine.Remove(' ');
		if (strLine == _T("ENDSEC"))
			return TRUE;
	}
	return TRUE;
}

BOOL CMachineListContainer::Parsedxf_Thumbnail()
{
	if (Parsedxf_FindEns())
		return TRUE;
	else
		return FALSE;
}

BOOL CMachineListContainer::Parsedxf_Entities()
{
	CMachinePara_Layer* pLayer;
	CString LayerName;		//层名
	int nLayerCount;
	CString strLine;
	file.ReadString(strLine);
	while (1)
	{
		strLine.Remove(' ');
		if (strLine == "0")
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return FALSE;
			}
			strLine.Remove(' ');
			if (strLine == "POINT")
			{
				CMachineObjPoint* pObjPoint;
				ObjPoint point;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEntity")))	//搜图层
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				if (strLine != _T("8"))
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				LayerName = strLine;
				if (!Parsedxf_Find(_T("100"), _T("AcDbPoint")))	//搜图元
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("10"), &point.x))	//读点x坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("20"), &point.y))	//读点y坐标
					break;	//文件格式错误
				nLayerCount = FindLayerByName(LayerName);
				if (nLayerCount < 0)
				{
					//无同名图层则添加新层
					pLayer = new CMachinePara_Layer(LayerName,		
						m_MachineModeDefault, m_MachineParaDefault);
					nLayerCount = m_LayerCount;
					AddLayer(pLayer);
				}
				pObjPoint = new CMachineObjPoint(point, 
					m_MachineWaitTimeDefault, nLayerCount);
				AddObjTail(pObjPoint);

				if (!file.ReadString(strLine))	//读下一行
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
			}
			else if (strLine == "LINE")
			{
				CMachineObjLine* pObjLine;
				ObjPoint point1, point2;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEntity")))	//搜图层
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				if (strLine != _T("8"))
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				 strLine.Remove(' ');
				 LayerName = strLine;
				 if (!Parsedxf_Find(_T("100"), _T("AcDbLine")))	//搜图元
					 break;	//文件格式错误
				 if (!Parsedxf_GetValue(_T("10"), &point1.x))	//读起点x坐标
					 break;	//文件格式错误
				 if (!Parsedxf_GetValue(_T("20"), &point1.y))	//读起点y坐标
					 break;	//文件格式错误
				 if (!Parsedxf_GetValue(_T("11"), &point2.x))	//读终点x坐标
					 break;	//文件格式错误
				 if (!Parsedxf_GetValue(_T("21"), &point2.y))	//读终点y坐标
					 break;	//文件格式错误
				 nLayerCount = FindLayerByName(LayerName);
				 if (nLayerCount < 0)
				 {
					 //无同名图层则添加新层
					 pLayer = new CMachinePara_Layer(LayerName, 
						 m_MachineModeDefault, m_MachineParaDefault);
					 nLayerCount = m_LayerCount;
					 AddLayer(pLayer);
				 }
				 pObjLine = new CMachineObjLine(point1, point2, nLayerCount);
				 AddObjTail(pObjLine);

			}
			else if (strLine == "CIRCLE")
			{
				CMachineObjCircle* pObjCircle;
				ObjPoint pointcenter;
				char startnumber = 3;
				double radius;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEntity")))	//搜图层
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				if (strLine != _T("8"))
					break;	//文件格式错误
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				LayerName = strLine;
				if (!Parsedxf_Find(_T("100"), _T("AcDbCircle")))	//搜图元
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("10"), &pointcenter.x))	//读圆心x坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("20"), &pointcenter.y))	//读圆心x坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("40"), &radius))	//读圆的半径
					break;	//文件格式错误
				nLayerCount = FindLayerByName(LayerName);
				if (nLayerCount < 0)
				{
					pLayer = new CMachinePara_Layer(LayerName,
						m_MachineModeDefault, m_MachineParaDefault);
					nLayerCount = m_LayerCount;
					AddLayer(pLayer);
				}
				pObjCircle = new CMachineObjCircle(pointcenter,
					radius, startnumber, nLayerCount, CCW);	//默认圆的方向为"CCW",起点为圆心正下
				AddObjTail(pObjCircle);

				if (!file.ReadString(strLine))	//读下一行
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
			}
			else if (strLine == "ARC")
			{
				CMachineObjArc* pObjArc;
				ObjPoint pointcenter;
				double radius;
				double startangle, endangle;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEntity")))	//搜图层
					break;	//文件格式错误
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				if (strLine != _T("8"))
					break;	//文件格式错误
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				LayerName = strLine;
				if (!Parsedxf_Find(_T("100"), _T("AcDbCircle")))	//搜图元
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("10"), &pointcenter.x))	//读圆心x坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("20"), &pointcenter.y))	//读圆心y坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("40"), &radius))	//读圆的半径
					break;	//文件格式错误
				//下面为圆弧必须跟随内容
				if (!Parsedxf_Find(_T("100"), _T("AcDbArc")))	//搜图元
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("50"), &startangle))	//读圆弧的起始角度
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("51"), &endangle))	//读圆弧的终止角度
					break;	//文件格式错误
				nLayerCount = FindLayerByName(LayerName);
				if (nLayerCount < 0)
				{
					pLayer = new CMachinePara_Layer(LayerName,
						m_MachineModeDefault, m_MachineParaDefault);
					nLayerCount = m_LayerCount;
					AddLayer(pLayer);
				}
				pObjArc = new CMachineObjArc(pointcenter, radius,
					startangle, endangle, nLayerCount);
				AddObjTail(pObjArc);

				if (!file.ReadString(strLine))	//读下一行
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
			}
			else if (strLine == "ELLIPSE")
			{
				CMachineObjEllipse* pObjEllipse;
				CMachineObjArcEll* pObjArcEll;
				CMachineObjTiltEllipse* pObjTiltEllipse;
				ObjPoint pointcenter, offsetlongaxis;
				double ratio, startradian, endradian;
				double xradius;
				char startnumber;
				double ddir = 1;
				ObjDir dir = CCW;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEntity")))	//搜图层
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				if (strLine != _T("8"))
					break;	//文件格式错误
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				LayerName = strLine;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEllipse")))	//搜图元
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("10"), &pointcenter.x))	//读圆心x坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("20"), &pointcenter.y))	//读圆心x坐标
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("11"), &offsetlongaxis.x))	//读长轴x偏移
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("21"), &offsetlongaxis.y))	//读长轴y偏移
					break;	//文件格式错误
				if (Parsedxf_GetValue(_T("230"), _T("40"), &ddir, &ratio) < 0)	//读方向和短长轴比例
					break;	//文件格式错误
				if (ddir < 0)
					dir = CW;
				if (!Parsedxf_GetValue(_T("41"), &startradian))	//读起点弧度
					break;	//文件格式错误
				if (!Parsedxf_GetValue(_T("42"), &endradian))	//读终点弧度
					break;	//文件格式错误
				nLayerCount = FindLayerByName(LayerName);
				if (nLayerCount < 0)
				{
					pLayer = new CMachinePara_Layer(LayerName,
						m_MachineModeDefault, m_MachineParaDefault);
					nLayerCount = m_LayerCount;
					AddLayer(pLayer);
				}
				if (offsetlongaxis.x == 0 || offsetlongaxis.y == 0)
				{
					if ((float)(endradian - startradian) == (float)(2 * M_PI))
					{
						//正椭圆
						if (offsetlongaxis.x > 0 && offsetlongaxis.y == 0)
							startnumber = 0;
						else if (offsetlongaxis.x == 0 && offsetlongaxis.y > 0)
							startnumber = 1;
						else if (offsetlongaxis.y == 0 && offsetlongaxis.x < 0)
							startnumber = 2;
						else
							startnumber = 3;
						
						if (offsetlongaxis.y == 0)		//长轴在X方向
							xradius = abs(offsetlongaxis.x);
						else
						{
							xradius = abs(offsetlongaxis.y * ratio);	//长轴在Y方向
							ratio = 1 / ratio;
						}

						pObjEllipse = new CMachineObjEllipse(pointcenter, xradius,
							ratio, startnumber, nLayerCount, dir);
						AddObjTail(pObjEllipse);
					}
					else
					{
						//正椭圆弧
						if (offsetlongaxis.y == 0)		//长轴在X方向
						{
							xradius = abs(offsetlongaxis.x);
							if (offsetlongaxis.x < 0)
							{
								startradian += M_PI;	
								endradian += M_PI;
							}
						}
						else			//长轴在Y方向
						{		
							xradius = abs(offsetlongaxis.y * ratio);
							ratio = 1 / ratio;
							if (offsetlongaxis.y >= 0)
							{
								startradian += M_PI_2;
								endradian += M_PI_2;
							}
							else
							{
								startradian += M_PI_2 + M_PI;
								endradian += M_PI_2 + M_PI;
							}
						}
						pObjArcEll = new CMachineObjArcEll(pointcenter, xradius,
							ratio, startradian, endradian, nLayerCount, dir);
						AddObjTail(pObjArcEll);

					}
				}
				else
				{	//斜椭圆
					pObjTiltEllipse = new CMachineObjTiltEllipse(pointcenter,
						offsetlongaxis, ratio, startradian, endradian, nLayerCount);
					AddObjTail(pObjTiltEllipse);
				}


				if (!file.ReadString(strLine))	//读下一行
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
			}
			else if (strLine == "LWPOLYLINE")
			{
				CMachineObjPolyline* pObjPolyline;
				ObjVPoint vpoint, vpointfirst;
				int vertexcount;
				char closeflag;
				if (!Parsedxf_Find(_T("100"), _T("AcDbEntity")))	//搜图层
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				if (strLine != _T("8"))
					break;
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				LayerName = strLine;
				if (!Parsedxf_Find(_T("100"), _T("AcDbPolyline")))	//搜图元
					break;	//文件格式错误
				if (!Parsedxf_Find(_T("90")))	//搜顶点数组码
					break;	//文件格式错误
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				vertexcount = _ttoi(strLine);	//顶点数
				if (!Parsedxf_Find(_T("70")))	//搜标志
					break;	//文件格式错误
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
				strLine.Remove(' ');
				closeflag = _ttoi(strLine);	//闭合标志 0不闭合 1闭合
				if (!Parsedxf_Find(_T("10")))	//搜第一点X坐标标志
					break;	//文件格式错误
				
				pObjPolyline = new CMachineObjPolyline;
				for (int i = 1; i <= vertexcount; i++)
				{
					if (!file.ReadString(strLine))
					{
						file.Close();		//非正常结尾
						return FALSE;
					}
					strLine.Remove(' ');
					vpoint.x = _ttof(strLine);
					if (!file.ReadString(strLine))
					{
						file.Close();		//非正常结尾
						return FALSE;
					}
					strLine.Remove(' ');
					if (strLine != _T("20"))
						break;
					if (!file.ReadString(strLine))
					{
						file.Close();		//非正常结尾
						return FALSE;
					}
					strLine.Remove(' ');
					vpoint.y = _ttof(strLine);
					strLine = Parsedxf_FindExlt();
					if (strLine == _T(" "))
						return FALSE;
					else if (strLine == _T("42"))
					{
						if (!file.ReadString(strLine))
						{
							file.Close();		//非正常结尾
							return FALSE;
						}
						strLine.Remove(' ');
						vpoint.convexity = _ttof(strLine);
						if (!file.ReadString(strLine))
						{
							file.Close();		//非正常结尾
							return FALSE;
						}
					}
					else if (strLine == _T("10") || strLine == _T("0"))
					{
						vpoint.convexity = 0;
					}
					if (i == 1)
						vpointfirst = vpoint;
					pObjPolyline->AddObjVpoint(vpoint);
				}
				if (closeflag == 1)		//封闭线在最后加上起点
				{
					pObjPolyline->AddObjVpoint(vpointfirst);
				}
				nLayerCount = FindLayerByName(LayerName);
				if (nLayerCount < 0)
				{
					//无同名图层则添加新层
					pLayer = new CMachinePara_Layer(LayerName,
						m_MachineModeDefault, m_MachineParaDefault);
					nLayerCount = m_LayerCount;
					AddLayer(pLayer);
				}
				pObjPolyline->m_ObjByLayer = nLayerCount;
				AddObjTail(pObjPolyline);

			}

			else if (strLine == "ENDSEC")
			{
				return TRUE;
			}
			else
			{
				if (!file.ReadString(strLine))
				{
					file.Close();		//非正常结尾
					return FALSE;
				}
			}
		}
		else if (strLine == "ENDSEC")
		{
			return TRUE;
		}
		else
		{
			if (!file.ReadString(strLine))
			{
				file.Close();		//非正常结尾
				return FALSE;
			}
		}
	}
	return FALSE;
}

void CMachineListContainer::LayerRename(CString CADVer)
{
	POSITION pos;
	CString str;
	CMachinePara_Layer* pLayer;
	pos = m_MachineLayerList->FindIndex(LayerNum_Default);
	for (int i = 1; i <= m_LayerCount - LayerNum_Default; i++)
	{
		pLayer = m_MachineLayerList->GetNext(pos);
		str = pLayer->m_LayerName;
		//将图层名中的汉字转为CSTring
		const size_t strsize = (str.GetLength() + 1) * 2; // 宽字符的长度;
		char * pstr = new char[strsize]; //分配空间;
		size_t sz = 0;
		wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);
		if ((CADVer == "AC1021") || (CADVer == "AC1024"))		//2007版是AC1021,2010版是AC1024
		{
			//autocad2007和2010版本汉字是UTF8
			int wcsLen = MultiByteToWideChar(CP_UTF8, NULL, pstr, strlen(pstr), NULL, 0);
			wchar_t* wszString = new wchar_t[wcsLen + 1];
			MultiByteToWideChar(CP_UTF8, NULL, pstr, strlen(pstr), wszString, wcsLen);
			wszString[wcsLen] = '\0';
			CString unicodeString(wszString);
			delete[] wszString;
			wszString = NULL;
			pLayer->m_LayerName = unicodeString;
		}
		else
		{
			//早期版本汉族是Unicode
			pLayer->m_LayerName = pstr;
		}
		delete[] pstr;
		pstr = NULL;
	}
}
//*****************dxf文件解析部分结束********************

void CMachineListContainer::MoveObjectListCoordinate(double X_shift, double Y_shift)
{
	CMachineObj_Comm* pObj;
	POSITION pos;
	pos = this->GetObjHeadPosition();
	while (pos)
	{
		pObj = this->GetObjNext(pos);
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
	m_ObjBound.min_x += X_shift;
	m_ObjBound.max_x += X_shift;
	m_ObjBound.min_y += Y_shift;
	m_ObjBound.max_y += Y_shift;
}

void CMachineListContainer::ExtendObjAtIndex(vector<int> nList, int Dup, float Gap)
{
	int Count = nList.size();
	if (Count < 1)
		return;
	CMachineObj_Comm* pObj_old;
	POSITION pos;
	for (int i = 0; i < Count; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[i]);
		pObj_old = m_MachineObjList->GetAt(pos);
		int nType = pObj_old->GetObjType();
		if (nType== MachineObj_Type_Line)
		{
			CMachineObjWLine* pWLine = new CMachineObjWLine((CMachineObjLine*)pObj_old, Dup, Gap);
			m_MachineObjList->InsertBefore(pos, pWLine);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
		else if (nType == MachineObj_Type_Arc)
		{
			CMachineObjWArc* pWArc = new CMachineObjWArc((CMachineObjArc*)pObj_old, Dup, Gap);
			m_MachineObjList->InsertBefore(pos, pWArc);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
		else if (nType == MachineObj_Type_Polyline)
		{
			CMachineObjWPolyline* pWPolyline = new CMachineObjWPolyline
				((CMachineObjPolyline*)pObj_old, Dup, Gap);
			m_MachineObjList->InsertBefore(pos, pWPolyline);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
	}
}

void CMachineListContainer::Degenerate(vector<int> nList)
{
	int Count = nList.size();
	if (Count < 1)
		return;
	CMachineObj_Comm* pObj_old;
	POSITION pos;
	for (int i = 0; i < Count; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[i]);
		pObj_old = m_MachineObjList->GetAt(pos);
		int nType = pObj_old->GetObjType();
		if (nType == MachineObj_Type_WLine)
		{
			CMachineObjLine* pLine = ((CMachineObjWLine*)pObj_old)->DegenerateToLine();
			m_MachineObjList->InsertBefore(pos, pLine);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
		else if (nType == MachineObj_Type_WArc)
		{
			CMachineObjArc* pArc = ((CMachineObjWArc*)pObj_old)->DegenerateToArc();
			m_MachineObjList->InsertBefore(pos, pArc);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
		else if (nType == MachineObj_Type_WPolyline)
		{
			CMachineObjPolyline* pWPolyline = ((CMachineObjWPolyline*)pObj_old)->DegenerateToPolyline();
			m_MachineObjList->InsertBefore(pos, pWPolyline);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
		else if (nType == MachineObj_Type_FillPolyline)
		{
			CMachineObjPolyline* pWPolyline = ((CMachineObjFillPolyline*)pObj_old)->DegenerateToPolyline();
			m_MachineObjList->InsertBefore(pos, pWPolyline);
			m_MachineObjList->RemoveAt(pos);
			delete pObj_old;
		}
	}
}

void CMachineListContainer::FillObjAtIndex(vector<int> nList, byte	OutlinePrior,
	FillPara FillPara1, FillPara FillPara2, FillPara FillPara3, FillPara FillPara4)
{
	int Count = nList.size();
	if (Count < 1)
		return;
	CMachineObj_Comm* pObj_old;
	POSITION pos;
	for (int i = 0; i < Count; i++)
	{
		pos = m_MachineObjList->FindIndex(nList[i]);
		pObj_old = m_MachineObjList->GetAt(pos);
		int nType = pObj_old->GetObjType();
		if (nType == MachineObj_Type_Polyline)
		{
			double x1, x2, y1, y2;
			CMachineObjPolyline* pPolyline = (CMachineObjPolyline*)pObj_old;
			x1 = pPolyline->GetPolylineStart().x;
			y1 = pPolyline->GetPolylineStart().y;
			x2 = pPolyline->GetPolylineEnd().x;
			y2 = pPolyline->GetPolylineEnd().y;
			if ((abs(x1 - x2) < Zero) && (abs(y1 - y2) < Zero))
			{
				CMachineObjFillPolyline* pFillPolyline = new CMachineObjFillPolyline(pPolyline, OutlinePrior,
					FillPara1, FillPara2, FillPara3, FillPara4);
				m_MachineObjList->InsertBefore(pos, pFillPolyline);
				m_MachineObjList->RemoveAt(pos);
				delete pObj_old;
			}
			
		}
	}

}