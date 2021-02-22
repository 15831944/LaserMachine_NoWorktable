#pragma once
#include <afx.h>
#include"DeviceCardMark.h"
#include "PointF.h"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/strategies/transform/matrix_transformers.hpp>
#include <boost/foreach.hpp>

//#include <boost/variant.hpp> 

namespace bg = boost::geometry;
namespace bgm = bg::model;
namespace bgt = bg::strategy::transform;

typedef  bgm::d2::point_xy<double> Point_T;
typedef  bgm::linestring<Point_T> Line_T;
typedef  bgm::polygon<Point_T> Polygon_T;
typedef  bgm::multi_linestring<Line_T> MLine_T;
//typedef  bgm::multi_point<Point_T> MPoint_T;
//typedef  bgm::multi_polygon<Polygon_T> MPolygon_T;

struct PreProcessEntity
{
	MLine_T  mlineObj;	//加工对象
	int		nPenNo;		//笔号
};
typedef std::vector<PreProcessEntity> VecEntities;	//加工对象列表

struct PreProcessEntPerGrid
{
	Polygon_T			polyGrid;					//单个分格参数
	VecEntities			vecEntitiesPerGrid;			//单个分格内的加工对象
};

class CPreProcess :
    public CObject
{

	// Construction
public:
	CPreProcess();
	virtual ~CPreProcess();

	// Attribute
public:
	std::vector<PreProcessEntPerGrid> m_vecProcEntPerGrid;
	std::vector<PreProcessEntPerGrid> m_vecProcEntPerGridTrans;
		
	Point_T	m_ptOrg;			//原点坐标，即第一个mark点的图形坐标
	//Point_T	m_ptOrgReal;		//原点坐标，即第一个mark点的工作台坐标
	//Point_T	m_ptTranslate;	//平移参数
	//Point_T m_ptScale;			//缩放参数
	//double	m_fRotateDegree;	//旋转参数，CW为正

	double	m_fMarkArcStep ;	//弧长步长


	
	// Operation
public:
	//分格
	void CalculateGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList, std::vector<double> vecGridX, std::vector<double> vecGridY);
	void CalculateGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList);
	void DoGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList);
	//void DoGrid(std::vector<double*> &vecGridRect, CMachineListContainer* pObjList);
	//平移缩放旋转
	void CalculateTrans(int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark, std::vector<ObjRect> vecGridRect,
		double fPosWorktableX, double fPosWorktableY, double ptOrg[2], double ptScale[2], double *fRotateDegree, double ptReal[2], int nScaleDirection = 0);
	void DoTrans(double ptOrg[2], double ptScale[2], double fRotateDegree, double ptReal[2]);

	//获得分格中心坐标，相对ptOrg的坐标
	void GetGridCenter(int nGridIndex, double* pGridCenterX, double* pGridCenterY);

	//将单个分格中的加工对象写入板卡
	BOOL WriteEntitiesPerGridToBuffer(int nGridIndex, CDeviceCardMark* pDevCardMark, CMachineListContainer* pObjList = NULL);

//protected:
	void CutEntityByGrid(VecEntities &vecEntities, std::vector<Polygon_T> &vecPolyGrid);
	void CutEntityByGrid1(VecEntities& vecEntities, std::vector<Polygon_T>& vecPolyGrid);
	void CutEntityByGridOverlap(VecEntities& vecEntities, std::vector<Polygon_T>& vecPolyGrid, double fOverlapLength);
	void LoadMachineObjList(VecEntities &vecEntities, CMachineListContainer* pObjList);
	void LoadMachineObj(VecEntities& vecEntities, CMachineObj_Comm* pObj);
	void AddEntityLines(VecEntities& vecEntities, int nCount, double ptPos[][2], int nPenNo);
	void AddEntityCircle(VecEntities& vecEntities, double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo);
	void AddEntityArc(VecEntities& vecEntities, double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo);
	BOOL WriteEntitiesToBuffer(VecEntities& vecEntities);
};

