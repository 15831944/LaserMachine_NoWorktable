// CMachineObjLine �ӹ�����ֱ����
//
#pragma once
#include "MachineObj_Comm.h"

// CMachineObjLine ����Ŀ��
class CMachineObjLine :public CMachineObj_Comm
{
// ����
public:
	CMachineObjLine();
	CMachineObjLine(ObjPoint LineStart, ObjPoint LineEnd,
		int LineByLayer = LayerNum_Default);
	~CMachineObjLine();
	virtual void Serialize(CArchive& ar);

// ����
protected:
	ObjPoint m_LineStart;
	ObjPoint m_LineEnd;

// ����
protected:
	void ReSizeBound();
public:
	void SetLineStart(ObjPoint LineStart);
	void SetLineEnd(ObjPoint LineEnd);
	void SetLine(ObjPoint LineStart, ObjPoint LineEnd);
	void MoveLineStart(ObjPoint LineStart);
	void MoveLineEnd(ObjPoint LineEnd);
	void MoveLine(double X_shift, double Y_shift);
	void ExchangeStartAndEnd(CMachineObjLine* pObj);
	ObjPoint GetLineStart();
	ObjPoint GetLineEnd();

	
};

