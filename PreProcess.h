#pragma once
#include <afx.h>
#include"DeviceCardMark.h"
#include "PointF.h"
#include "HalconModel.h"
#include "Model.h"
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
	MLine_T  mlineObj;	//�ӹ�����
	int		nPenNo;		//�ʺ�
};
typedef std::vector<PreProcessEntity> VecEntities;	//�ӹ������б�

struct PreProcessEntPerGrid
{
	Polygon_T			polyGrid;					//�����ָ����
	VecEntities			vecEntitiesPerGrid;			//�����ָ��ڵļӹ�����
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
		
	//Point_T	m_ptOrg;			//ԭ�����꣬����һ��mark���ͼ������
	//Point_T	m_ptOrgReal;		//ԭ�����꣬����һ��mark��Ĺ���̨����
	//Point_T	m_ptTranslate;	//ƽ�Ʋ���
	//Point_T m_ptScale;			//���Ų���
	//double	m_fRotateDegree;	//��ת������CWΪ��

	double	m_fMarkArcStep ;	//��������


	
	// Operation
public:
	//�ָ�
	void CalculateGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList, std::vector<double> vecGridX, std::vector<double> vecGridY);
	void CalculateGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList);
	void DoGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList);
	//void DoGrid(std::vector<double*> &vecGridRect, CMachineListContainer* pObjList);
	//ƽ��������ת
	void CalculateTrans(int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark, std::vector<ObjRect> vecGridRect,
		double fPosWorktableX, double fPosWorktableY, double ptOrg[2], double ptScale[2], double* fRotateDegree, double ptReal[2], int nScaleDirection = 0);
	void DoTrans(double ptOrg[2], double ptScale[2], double fRotateDegree, double ptReal[2]);
	//�޹���ʱ�ָ���㷽ʽ
	BOOL DoSingleGrid(CMachineListContainer* pObjList);
	void CalculateSingleTrans(CMachineListContainer* pObjList, int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark,
		double ptOrg[2], double ptScale[2], double* fRotateDegree, double ptReal[2], int nScaleDirection = 0);
	void DoSingleTrans(CMachineListContainer* pObjList, int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark, int nScaleDirection = 0);

	//��÷ָ��������꣬���ptOrg������
	void GetGridCenter(int nGridIndex, double* pGridCenterX, double* pGridCenterY);

	//�������ָ��еļӹ�����д��忨
	BOOL WriteEntitiesPerGridToBuffer(int nGridIndex, CMachineListContainer* pObjList = NULL);

	//ץ�����
	int GenMarkPoints(std::vector <CPointF> vPtPosDestinedMark, std::vector <HalconModel> vMarkPointModel, CMachineListContainer* pObjList);
	int GenMarkPoints(std::vector <CPointF>& vPtPosDestinedMark, std::vector <ModelBase>& vModelBase, CMachineListContainer* pObjList);
	int FindMarkPoints(std::vector <CPointF>& vPtPosRealMark, std::vector <ModelBase>& vModelBase);

	//�Զ����ӹ�׼��
	BOOL AutoPreProcess1(CMachineListContainer* pList, BOOL bLocate);

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

	//ץ�����
	BOOL GenMarkPointModel(HalconModel* pHalconModel, CMachineObj_Comm* pObj, double fCrossWidth = 0.25);
	BOOL GenMarkPointModel(ModelBase **ppModel, CMachineObj_Comm* pObj, CMachineListContainer* pList);

};

