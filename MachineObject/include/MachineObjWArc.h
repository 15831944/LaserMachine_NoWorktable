// CMachineObjWArc �ӹ�����չ��Բ����
//
#pragma once
#include "MachineObjArc.h"

// CMachineObjWArc ����Ŀ��
class CMachineObjWArc :public CMachineObjArc
{
// ����
public:
	CMachineObjWArc();
	CMachineObjWArc(CMachineObjArc* pArc, int Duplicate, float GapDistance);
	~CMachineObjWArc();
	virtual void Serialize(CArchive& ar);

// ����
private:
	int m_Duplicate;
	float m_GapDistance;
public:
	vector<VectPoint*> m_pDupList;


// ����
private:
	void ExtendWArc();
public:
	CMachineObjArc* DegenerateToArc();
	void MoveWArc(double X_shift, double Y_shift);
	int GetDupNumber();
	float GetGapDistance();
	void SetDupNumber(int DupNumber);
	void SetGapDistance(float GapDistance);
	void ReCreatWArc(int DupNumber, float GapDistance);
	
};

