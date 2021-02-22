//CMachineListContainer 加工物件列表容器类（包含加工物件的完整信息）
//
#pragma once
#include "MachinePara_Layer.h"
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

// MachineListContainer 命令目标
class CMachineListContainer : public CObject
{
// 构造
public:
	CMachineListContainer();
	virtual ~CMachineListContainer();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	int m_LayerCount;
	CStdioFile file;
protected:
	CMachine_LayerList* m_MachineLayerList;
	CMachineObjList* m_MachineObjList;
	ObjRect m_ObjBound;
	BOOL m_BorderEmpty;
public:
	ProcessPara m_MachineParaDefault;	//默认的加工参数
	float m_MachineWaitTimeDefault;			//默认打点时间
	BYTE m_MachineModeDefault;				//默认的加工模式

// 操作
private:
	void ReSizeBound(CMachineObj_Comm* MachineObj);
	void ReSizeBound();
	BOOL IsObjInLayer(CMachineObj_Comm* pObj, int Index);
	void ReduceObjLayerAtIndex(CMachineObj_Comm* pObj, int Index);
	void ModifyObjLayerAtIndex(CMachineObj_Comm* pObj, int Index,int Index0);
	//***dxf解析用
	BOOL Parsedxf_Find(CString GroupCode, CString GroupName);
	BOOL Parsedxf_Find(CString GroupCode);
	CString Parsedxf_FindExlt();
	BOOL Parsedxf_FindEns();
	BOOL Parsedxf_Header();
	BOOL Parsedxf_Classed();
	BOOL Parsedxf_Tables();
	BOOL Parsedxf_Blocks();
	BOOL Parsedxf_Entities();
	BOOL Parsedxf_Objects();
	BOOL Parsedxf_Thumbnail();
	BOOL Parsedxf_GetValue(CString Code, double* value);
	int  Parsedxf_GetValue(CString Code1, CString Code2, double* value1, double* value2);
	//***********

	//*****绘图用
	CPoint TransRPtoLP(ObjPoint ptObj);
	CRect  TransRBdtoLBd(ObjRect ObjBound, long Offset = 0);
	BOOL GetStartAndEnd(CMachineObj_Comm* pObj, ObjPoint* point1, ObjPoint* point2);
	double CalArcConvex(CMachineObjArc* pObj, BOOL Exchange);
	BOOL ParallelCheck(ObjPoint point1, ObjPoint point2, ObjPoint point3, ObjPoint point4);
	CMachineObjPolyline* PolymerObj(CMachineObj_Comm* pObj1, CMachineObj_Comm* pObj2, BOOL EnNew);
	double CalDirAngle(ObjPoint point1, ObjPoint point2);
	void CalArrow(ObjPoint point, double dirAngle, float ZoomFactor,
		ObjPoint* point1, ObjPoint* point2);
	void DrawObjList(CDC* pDC, CMachineListContainer* pObjList,float ZoomFactor,BOOL DrawSel);
	void DrawObject(CDC* pDC, CMachineObj_Comm* pObj, int LayerMax, float ZoomFactor, BOOL DrawSel);
	BOOL IntersectBound(ObjRect bound1, ObjRect bound2);
	BOOL PickObjPoint(CMachineObjPoint* pPoint, ObjPoint point, float BoxSize);
	BOOL PickObjLine(CMachineObjLine* pLine, ObjPoint point, float BoxSize);
	BOOL PickObjCircle(CMachineObjCircle* pCircle, ObjPoint point, float BoxSize);
	BOOL PickObjArc(CMachineObjArc* pArc, ObjPoint point, float BoxSize);
	double CalRadianPointToPoint(ObjPoint point1, ObjPoint point2);
	BOOL PickObjEllipse(CMachineObjEllipse* pEllipse, ObjPoint point, float BoxSize);
	BOOL PickObjArcEll(CMachineObjArcEll* pArcEll, ObjPoint point, float BoxSize);
	BOOL PickObjTiltEllArc(CMachineObjTiltEllipse* pTiltEllArc, ObjPoint point, float BoxSize);
	BOOL PickObjPolyline(CMachineObjPolyline* pPolyline, ObjPoint point, float BoxSize);
	BOOL PickObjGroup(CMachineObjGroup* pGroup, ObjPoint point, float BoxSize);

	BOOL PickObject(CMachineObj_Comm* pObj, ObjPoint point, float BoxSize, BOOL Sel = FALSE);



public:
	void ClearAllObj();
	void ClearAll();
	void ClearNullLayer();
	void SetObjSelect(int nIndex, BOOL sel = TRUE);
	void SetObjUnSelectAll();
	void SetLayerUnSelectAll();
	BOOL MoveObjUp(int nIndex);
	BOOL MoveObjDown(int nIndex);
	BOOL IsEmptyLayer();
	BOOL IsEmptyObj();
	BOOL ISEmptyBorder();
	int GetLayerCount();
	int GetObjCount();
	void RefeshBound();
	ObjRect GetObjBound(BOOL refresh = FALSE);
	int FindLayerByName(CString Name);
	int FindLayerByPara(ProcessPara para, int mode);
	void FindLayerByParaAddOrChange(ProcessPara para, int mode, vector<int> nList);
	void ClearRedundLayer();
	POSITION AddLayer(CMachinePara_Layer* MachineLayer);
	POSITION AddObjTail(CMachineObj_Comm* MachineObj);
	POSITION InsertObjBefore(POSITION pos, CMachineObj_Comm* MachineObj);
	POSITION InsertObjAfter(POSITION pos, CMachineObj_Comm* MachineObj);
	BOOL DeleteLayerOfNumber(int Number);
	BOOL DeleteLayerOfName(CString Name);
	CMachinePara_Layer* GetLayerOfNumber(int Number);
	CMachinePara_Layer* GetLayerOfName(CString Name);
	POSITION GetObjHeadPosition();
	CMachineObj_Comm* GetObjAtIndex(int Index);
	BOOL DeleteObjAtIndex(int Index);
	BOOL InsertObjAtIndex(int Index, CMachineObj_Comm* pObj);
	BOOL RemoveObjAtIndex(int Index);
	BOOL PolymerObjAtIndex(vector<int> nList);
	BOOL GroupObjAtIndex(vector<int> nList);
	BOOL ExplodeObjAtIndex(int Index);
	BOOL ExchangeObjStartAndEnd(vector<int> nList);
	CMachineObj_Comm* GetObjHead();
	CMachineObj_Comm* GetObjTail();
	CMachineObj_Comm*& GetObjNext(POSITION& pos);
	CMachineObj_Comm*& GetObjPrev(POSITION& pos);
	void LayerRename();
	void DrawObjList(CDC* pDC, CMachineListContainer* pObjList,
		float ZoomFactor);
	int PickObjectList(CMachineListContainer* pObjlist, ObjPoint point, ObjRect rect, float BoxSize);
	vector<int> PickMultObjList(CMachineListContainer* pObjlist, ObjRect rect, ObjRect rect1);

	BOOL Parsedxf(LPCTSTR lpszPathName);

	


};


