// CMachineObjWArc 加工对象展宽圆弧类
//
#pragma once
#include "MachineObjArc.h"

// CMachineObjWArc 命令目标
class CMachineObjWArc :public CMachineObjArc
{
// 构造
public:
	CMachineObjWArc();
	CMachineObjWArc(CMachineObjArc* pArc, int Duplicate, float GapDistance);
	~CMachineObjWArc();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	int m_Duplicate;
	float m_GapDistance;
public:
	vector<VectPoint*> m_pDupList;


// 操作
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

