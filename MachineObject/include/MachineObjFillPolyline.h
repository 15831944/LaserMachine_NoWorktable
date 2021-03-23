// CMachineObjFillPolyline 加工对象封闭多段线填充类
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
	byte	GapMode;	//0:居中,1:均布
	byte	FillMode;	//0:单向,1:双向
	double	Curtail;
	TagFillPara() :IsEnable(false), FillAngle(0), FillGap(0), GapMode(0), FillMode(0), Curtail(0){}
}FillPara;


// CMachineObjFillPolyline 命令目标
class CMachineObjFillPolyline :public CMachineObjPolyline
{
// 构造
public:
	CMachineObjFillPolyline();
	CMachineObjFillPolyline(CMachineObjPolyline* pPolyline, byte OutlinePrior,
		FillPara FillPara1, FillPara FillPara2, FillPara FillPara3, FillPara FillPara4);
	~CMachineObjFillPolyline();
	virtual void Serialize(CArchive& ar);

// 特性
private:
	byte	m_OutlinePrior;	//0:无轮廓,1:先填充后轮廓,2:先轮廓后填充
	FillPara m_FillPara[4]; 
public:
	VectLine m_FillLine;

// 操作
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

