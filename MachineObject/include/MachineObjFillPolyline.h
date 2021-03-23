// CMachineObjFillPolyline �ӹ������ն���������
//
#pragma once
#include "MachineObjPolyline.h"

typedef struct TagObjEdge
{
	ObjPoint  StartOrCircle;
	ObjPoint  EndOrRadian;
	double    radius;
	ObjRect	  bound;
} ObjEdge;
typedef vector<ObjEdge*> ObjEdgeList;
typedef struct TagFillPara
{
	bool	IsEnable;
	double	FillAngle;
	double	FillGap;
	byte	GapMode;	//0:����,1:����
	byte	FillMode;	//0:����,1:˫��
	double	Curtail;
	TagFillPara() :IsEnable(false), FillAngle(0), FillGap(0), GapMode(0), FillMode(0), Curtail(0){}
}FillPara;


// CMachineObjFillPolyline ����Ŀ��
class CMachineObjFillPolyline :public CMachineObjPolyline
{
// ����
public:
	CMachineObjFillPolyline();
	CMachineObjFillPolyline(CMachineObjPolyline* pPolyline, byte OutlinePrior,
		FillPara FillPara1, FillPara FillPara2, FillPara FillPara3, FillPara FillPara4);
	~CMachineObjFillPolyline();
	virtual void Serialize(CArchive& ar);

// ����
private:
	byte	m_OutlinePrior;	//0:������,1:����������,2:�����������
	FillPara m_FillPara[4]; 
public:
	VectLine m_FillLine;

// ����
private:
	int Quadrant(double x, double y);
	ObjRect SizeBound(ObjEdge* pEdge);
	ObjRect SizeBound(ObjEdge* pEdge, ObjPoint point1, ObjPoint point2);
	ObjEdgeList CreatEdgelist(double *Ymax, double *Ymin, double SinRotate = 0, double CosRotate = 1);
	void Remove(ObjEdgeList* EdgeList, int Index);
	void FillPolyline();

public:
	CMachineObjPolyline* DegenerateToPolyline();
	void MoveFillPolyline(double X_shift, double Y_shift);
	byte GetOutlinePrior();
	FillPara GetFillPolylinePara(int Group);
	void ReCreatFillPolyline(byte OutlinePrior, FillPara* pPara);
};

