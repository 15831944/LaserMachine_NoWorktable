// CMachineObjLine 加工对象直线类
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjLine 命令目标
class CMachineObjLine :public CMachineObj_Comm
{
// 构造
public:
	CMachineObjLine();
	CMachineObjLine(ObjPoint LineStart, ObjPoint LineEnd,
		int LineByLayer = LayerNum_Default);
	~CMachineObjLine();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	ObjPoint m_LineStart;
	ObjPoint m_LineEnd;

// 操作
private:
	void ReSizeBound();
public:
	void SetLineStart(ObjPoint LineStart);
	void SetLineEnd(ObjPoint LineEnd);
	void SetLine(ObjPoint LineStart, ObjPoint LineEnd);
	void MoveLineStart(ObjPoint LineStart);
	void MoveLineEnd(ObjPoint LineEnd);
	void ExchangeStartAndEnd(CMachineObjLine* pObj);
	ObjPoint GetLineStart();
	ObjPoint GetLineEnd();

	
};

