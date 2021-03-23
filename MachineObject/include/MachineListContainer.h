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
#include "MachineObjWLine.h"
#include "MachineObjWArc.h"
#include "MachineObjWPolyline.h"
#include "MachineObjFillPolyline.h"


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
	BOOL IsObjInLayer(CMachineObj_Comm* pObj, int Layer_Index);
	void ReduceObjLayerAfterIndex(CMachineObj_Comm* pObj, int Layer_Index);
	void ModifyObjByLayer(CMachineObj_Comm* pObj, int Source_Layer, int Dest_Layer);
	BOOL DeleteObjInLayer(CMachineObj_Comm* pObj, int Layer_Index);
	void ExchangeObjInLayer(CMachineObj_Comm* pObj, int Layer_Index1, int Layer_Index2);
	BOOL DeleteNullObject(CMachineObj_Comm* pObj, int Layer_Index);
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
	BOOL Parsedxf(LPCTSTR lpszPathName, CString* CADVer);
	void LayerRename(CString CADVer);
	//***********

	//*****绘图用
	CPoint TransRPtoLP(ObjPoint ptObj);
	CRect  TransRBdtoLBd(ObjRect ObjBound, long Offset = 0);
	BOOL GetStartAndEnd(CMachineObj_Comm* pObj, ObjPoint* point1, ObjPoint* point2);
	double CalArcConvex(CMachineObjArc* pObj, BOOL Exchange = FALSE);
	BOOL ParallelCheck(ObjPoint point1, ObjPoint point2, ObjPoint point3, ObjPoint point4);
	CMachineObjPolyline* PolymerObj(CMachineObj_Comm* pObj1, CMachineObj_Comm* pObj2, BOOL EnNew);
	double CalDirAngle(ObjPoint point1, ObjPoint point2);
	void CalArrow(ObjPoint point, double dirAngle, float ZoomFactor,
		ObjPoint* point1, ObjPoint* point2);
	void ObjToDispList(CMachineObj_Comm* pObj, CMachineObjList* DispList);
	BOOL IntersectBound(ObjRect bound1, ObjRect bound2);
	BOOL ISIncludeBound(ObjRect bound1, ObjRect bound2);
	BOOL IsObjActive(CMachineObj_Comm* pObj);
	byte PickObjPoint(CMachineObjPoint* pPoint, ObjPoint point, float BoxSize);
	byte PickObjLine(CMachineObjLine* pLine, ObjPoint point, float BoxSize);
	byte PickObjCircle(CMachineObjCircle* pCircle, ObjPoint point, float BoxSize);
	byte PickObjArc(CMachineObjArc* pArc, ObjPoint point, float BoxSize);
	double CalRadianPointToPoint(ObjPoint point1, ObjPoint point2);
	byte PickObjEllipse(CMachineObjEllipse* pEllipse, ObjPoint point, float BoxSize);
	byte PickObjArcEll(CMachineObjArcEll* pArcEll, ObjPoint point, float BoxSize);
	byte PickObjTiltEllArc(CMachineObjTiltEllipse* pTiltEllArc, ObjPoint point, float BoxSize);
	byte PickObjPolyline(CMachineObjPolyline* pPolyline, ObjPoint point, float BoxSize);
	byte PickObjGroup(CMachineObjGroup* pGroup, ObjPoint point, float BoxSize);
	byte PickObject(CMachineObj_Comm* pObj, ObjPoint point, float BoxSize, byte Sel = IsObjNormal);



public:
	void ClearAllObj();
	void ClearAll();
	void ClearNullLayer();
	void ClearNullObject(int LayerIndex);
	void ClearNullObject();
	void SetObjSelect(int nIndex, bool sel = TRUE);
	void SetObjUnSelectAll();
	void SetLayerUnSelectAll();
	BOOL MoveObjUp(int nIndex);
	BOOL MoveObjDown(int nIndex);
	BOOL ExchangeObjAtIndex(int Index1, int Index2);
	BOOL IsEmptyLayer();
	BOOL IsEmptyObj();
	BOOL ISEmptyBorder();
	int GetLayerCount();
	int GetObjCount();
	void RefeshBound();
	ObjRect GetObjBound(BOOL refresh = FALSE);
	int FindLayerByName(CString Name);
	int FindLayerByPara(ProcessPara para, int mode);
	void ClearRedundLayer();
	void LayerMoveUpAtIndex(int Index);
	void LayerMoveDownAtIndex(int Index);
	POSITION AddLayer(CMachinePara_Layer* MachineLayer);
	POSITION AddObjTail(CMachineObj_Comm* MachineObj);
	POSITION InsertObjBefore(POSITION pos, CMachineObj_Comm* MachineObj);
	POSITION InsertObjAfter(POSITION pos, CMachineObj_Comm* MachineObj);
	BOOL DeleteLayerOfNumber(int Number);
	BOOL DeleteLayerOfName(CString Name);
	void ChangeObjByLayer(CMachineObj_Comm* pObj, int LayerIndex);
	CMachinePara_Layer* GetLayerOfNumber(int Number);
	CMachinePara_Layer* GetLayerOfName(CString Name);
	POSITION GetObjHeadPosition();
	CMachineObj_Comm* GetObjAtIndex(int Index);
	BOOL DeleteObjAtIndex(int Index);
	BOOL InsertObjAtIndex(int Index, CMachineObj_Comm* pObj);
	BOOL RemoveObjAtIndex(int Index);
	BOOL PolymerObjAtIndex(int Index);
	BOOL PolymerObjAtIndex(vector<int> nList);
	BOOL GroupObjAtIndex(vector<int> nList);
	BOOL ExplodeObjAtIndex(int Index);
	BOOL ChangeObjNode(vector<int> nList);
	BOOL ReverseObj(vector<int> nList);
	CMachineObj_Comm* GetObjHead();
	CMachineObj_Comm* GetObjTail();
	CMachineObj_Comm*& GetObjNext(POSITION& pos);
	CMachineObj_Comm*& GetObjPrev(POSITION& pos);
	void DrawObjList(CDC* pDC, CMachineListContainer* pObjList, float ZoomFactor, ObjRect Disprc, bool Dispdir);
	int PickObjectList(CMachineListContainer* pObjlist, ObjPoint point, ObjRect rect, float BoxSize);
	vector<int> PickMultObjList(CMachineListContainer* pObjlist, ObjRect rect, ObjRect rect1);
	BOOL Parsedxf(LPCTSTR lpszPathName);

	//20210115新增加
	void MoveObjectListCoordinate(double X_shift, double Y_shift);
	void ExtendObjAtIndex(vector<int> nList, int Dup, float Gap);
	void Degenerate(vector<int> nList);
	void FillObjAtIndex(vector<int> nList, byte	OutlinePrior,
		FillPara FillPara1, FillPara FillPara2, FillPara FillPara3, FillPara FillPara4);

	
	
};


