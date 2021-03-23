// CMachineObjWLine �ӹ�����չ��ֱ����
//
#pragma once
#include "MachineObjLine.h"

// CMachineObjWLine ����Ŀ��
class CMachineObjWLine :public CMachineObjLine
{
// ����
public:
	CMachineObjWLine();
	CMachineObjWLine(CMachineObjLine* pLine, int Duplicate, float GapDistance);
	~CMachineObjWLine();
	virtual void Serialize(CArchive& ar);

// ����
private:
	int m_Duplicate;
	float m_GapDistance;
public:
	vector<VectPoint*> m_pDupList;


// ����
private:
//	ObjRect LineBound(ObjPoint point1, ObjPoint point2);
	void ExtendWLine();
//	void ReSizeBound(ObjRect Bound);
public:
	CMachineObjLine* DegenerateToLine();
	void MoveWLine(double X_shift, double Y_shift);
	void ExchangeStartAndEnd();
	int GetDupNumber();
	float GetGapDistance();
	void SetDupNumber(int DupNumber);
	void SetGapDistance(float GapDistance);
	void ReCreatWLine(int DupNumber, float GapDistance);
};

