#include "stdafx.h"
#include "PreProcess.h"
#include "CDlgDevCfgTabCamera.h"
#include "CDlgDevCfgTabScanner.h"
#include <math.h>

CPreProcess::CPreProcess()
{
	m_vecProcEntPerGrid.clear();
	m_vecProcEntPerGridTrans.clear();

	//m_ptOrg = Point_T(0.0, 0.0);
	//m_ptOrgDxf = Point_T();
	//m_ptScale = Point_T();
	//m_fRotateDegree = 0;
	m_fMarkArcStep = 0.005;
}

CPreProcess::~CPreProcess()
{

}

//******************************************//
//�ָ�
void CPreProcess::CalculateGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList, std::vector<double> vecGridX, std::vector<double> vecGridY)
{
	ObjRect rectBorder = pObjList->GetObjBound();
	int nCtGridX, nCtGridY;
	nCtGridX = vecGridX.size() - 1;
	nCtGridY = vecGridY.size() - 1;

	for (int j = 0; j < nCtGridY; j++)					//Y�����µ���
	{
		if (0 == j % 2)										//�����У���������
		{
			for (int i = 0; i < nCtGridX; i++)
			{
				ObjRect rectTmp;
				rectTmp.min_x = vecGridX[i] + rectBorder.min_x;
				rectTmp.max_x = vecGridX[(size_t)i + 1] + rectBorder.min_x;
				rectTmp.min_y = vecGridY[j] + rectBorder.min_y;
				rectTmp.max_y = vecGridY[(size_t)j + 1] + rectBorder.min_y;
				vecGridRect.push_back(rectTmp);
			}
		}
		else												//ż���У���������
		{
			for (int i = nCtGridX - 1; i >= 0; i--)
			{
				ObjRect rectTmp;
				rectTmp.min_x = vecGridX[i] + rectBorder.min_x;
				rectTmp.max_x = vecGridX[(size_t)i + 1] + rectBorder.min_x;
				rectTmp.min_y = vecGridY[j] + rectBorder.min_y;
				rectTmp.max_y = vecGridY[(size_t)j + 1] + rectBorder.min_y;
				vecGridRect.push_back(rectTmp);
			}
		}
	}
}
void CPreProcess::CalculateGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList)
{
	ObjRect rectBorder = pObjList->GetObjBound();
	double fScannerRegion, fWktableRegion;
	int nCtGridX, nCtGridY, nCtGridMax;

	fScannerRegion = ReadScannerCaliRegion();
	//fScannerRegion = 140;
	fWktableRegion = 500;

	nCtGridMax = (int)floor(fWktableRegion / fScannerRegion);
	nCtGridX = (int)ceil(abs(rectBorder.max_x - rectBorder.min_x) / fScannerRegion);
	nCtGridY = (int)ceil(abs(rectBorder.max_y - rectBorder.min_y) / fScannerRegion);

	if (nCtGridX > nCtGridMax && nCtGridY > nCtGridMax)
	{
		AfxMessageBox(_T("�ӹ����󳬷���"));
		return;
	}
	else if (nCtGridX <= 1 && nCtGridY <= 1)
	{
		vecGridRect.push_back(rectBorder);
	}
	else
	{
		for (int j = 0; j < nCtGridY; j++)					//Y�����µ���
		{
			if (0 == j % 2)										//�����У���������
			{
				for (int i = 0; i < nCtGridX; i++)
				{
					ObjRect rectTmp;
					rectTmp.min_x = fScannerRegion * i + rectBorder.min_x;
					rectTmp.max_x = fScannerRegion * ((double)i + 1) + rectBorder.min_x;
					rectTmp.min_y = fScannerRegion * j + rectBorder.min_y;
					rectTmp.max_y = fScannerRegion * ((double)j + 1) + rectBorder.min_y;
					vecGridRect.push_back(rectTmp);
				}
			}
			else												//ż���У���������
			{
				for (int i = nCtGridX - 1; i >= 0; i--)
				{
					ObjRect rectTmp;
					rectTmp.min_x = fScannerRegion * i + rectBorder.min_x;
					rectTmp.max_x = fScannerRegion * ((double)i + 1) + rectBorder.min_x;
					rectTmp.min_y = fScannerRegion * j + rectBorder.min_y;
					rectTmp.max_y = fScannerRegion * ((double)j + 1) + rectBorder.min_y;
					vecGridRect.push_back(rectTmp);
				}
			}
		}
	}

}
BOOL CPreProcess::DoSingleGrid(CMachineListContainer* pObjList)
{
	ObjRect rtBorder = pObjList->GetObjBound();
	double fScannerRegion;
	fScannerRegion = ReadScannerCaliRegion();

	if (rtBorder.max_x - rtBorder.min_x > fScannerRegion || rtBorder.max_y - rtBorder.min_y > fScannerRegion)
	{
		AfxMessageBox(_T("�ӹ����󳬷���"));
		return FALSE;
	}

	//����polyGrid�������зָ�����б�
	//std::vector<Polygon_T> vecPolyGrid;
	Polygon_T polyTmp;
	bg::append(polyTmp.outer(), Point_T(rtBorder.min_x, rtBorder.min_y));
	bg::append(polyTmp.outer(), Point_T(rtBorder.min_x, rtBorder.max_y));
	bg::append(polyTmp.outer(), Point_T(rtBorder.max_x, rtBorder.max_y));
	bg::append(polyTmp.outer(), Point_T(rtBorder.max_x, rtBorder.min_y));
	bg::correct(polyTmp);
	//vecPolyGrid.push_back(polyTmp);

	//����vecEntities�������мӹ������б�
	VecEntities vecEntities;
	LoadMachineObjList(vecEntities, pObjList);

	//����vecEntities & vecPolyGrid������m_vecProcEntPerGrid
	//CutEntityByGrid(vecEntities, vecPolyGrid);
	PreProcessEntPerGrid prcEntPerGridTmp;
	prcEntPerGridTmp.polyGrid = polyTmp;
	prcEntPerGridTmp.vecEntitiesPerGrid = vecEntities;
	m_vecProcEntPerGrid.push_back(prcEntPerGridTmp);

	return TRUE;
}

void CPreProcess::DoGrid(std::vector<ObjRect>& vecGridRect, CMachineListContainer* pObjList)
{
	//����polyGrid�������зָ�����б�
	std::vector<Polygon_T> vecPolyGrid;
	for (auto val : vecGridRect)
	{
		Polygon_T polyTmp;
		bg::append(polyTmp.outer(), Point_T(val.min_x, val.min_y));
		bg::append(polyTmp.outer(), Point_T(val.min_x, val.max_y));
		bg::append(polyTmp.outer(), Point_T(val.max_x, val.max_y));
		bg::append(polyTmp.outer(), Point_T(val.max_x, val.min_y));
		bg::correct(polyTmp);
		vecPolyGrid.push_back(polyTmp);
	}

	//����vecEntities�������мӹ������б�
	VecEntities vecEntities;
	LoadMachineObjList(vecEntities, pObjList);


	//std::vector<MLine_T> vecMLineAll;
	//for (auto val : vecEntities)
	//{
	//	vecMLineAll.push_back(val.mlineObj);
	//}


	//����vecEntities & vecPolyGrid������m_vecProcEntPerGrid
	CutEntityByGrid(vecEntities, vecPolyGrid);



	//�����

	//std::vector<MLine_T> vecMLinePerGrid;
	//std::vector<Polygon_T> vecPoly;
	//for (auto valList : m_vecProcEntPerGrid)
	//{
	//	Polygon_T polyTmp;
	//	VecEntities vecEntTmp;
	//	polyTmp = valList.polyGrid;
	//	vecEntTmp = valList.vecEntitiesPerGrid;
	//	vecPoly.push_back(valList.polyGrid);

	//	for (auto val : vecEntTmp)
	//	{
	//		vecMLinePerGrid.push_back(val.mlineObj);
	//	}
	//}
	//if (1) {}

	//double ptOrg[2] = { 100, 100 };
	//double ptScale[2] = { 1, 1 }; 
	//double fRotateDegree = 90;
	//DoTrans(ptOrg, ptScale, fRotateDegree);
	//std::vector<MLine_T> vecMLinePerGridTrans;
	//std::vector<Polygon_T> vecPolyTrans;
	//for (auto valListTrans : m_vecProcEntPerGridTrans)
	//{
	//	Polygon_T polyTmpTrans;
	//	VecEntities vecEntTmp;
	//	polyTmpTrans = valListTrans.polyGrid;
	//	vecEntTmp = valListTrans.vecEntitiesPerGrid;
	//	vecPolyTrans.push_back(valListTrans.polyGrid);

	//	for (auto val : vecEntTmp)
	//	{
	//		vecMLinePerGridTrans.push_back(val.mlineObj);
	//	}
	//}

	//if (1) {}

}

//void CPreProcess::DoGrid(std::vector<double*> &vecGridRect, CMachineListContainer* pObjList)
//{
//	////���vectorΪ�գ��Զ�����ָ�
//	//if (TRUE == vecGridRect.empty())
//	//{
//	//	Polygon_T polyTmp;
//	//	ObjRect objRect = pObjList->GetObjBound();
//	//	bg::append(polyTmp.outer(), Point_T(objRect.min_x, objRect.min_y));
//	//	bg::append(polyTmp.outer(), Point_T(objRect.min_x, objRect.max_y));
//	//	bg::append(polyTmp.outer(), Point_T(objRect.max_x, objRect.max_y));
//	//	bg::append(polyTmp.outer(), Point_T(objRect.max_x, objRect.min_y));
//	//	bg::correct(polyTmp);
//	//	vecPolyGrid.push_back(polyTmp);
//	//}
//
//	//����polyGrid�������зָ�����б�
//	std::vector<Polygon_T> vecPolyGrid;
//	for (auto val : vecGridRect)
//	{
//		Polygon_T polyTmp;
//		bg::append(polyTmp.outer(), Point_T(val[0], val[3]));
//		bg::append(polyTmp.outer(), Point_T(val[0], val[1]));
//		bg::append(polyTmp.outer(), Point_T(val[2], val[1]));
//		bg::append(polyTmp.outer(), Point_T(val[2], val[3]));
//		bg::correct(polyTmp);
//		vecPolyGrid.push_back(polyTmp);
//	}
//
//	//����vecEntities�������мӹ������б�
//	VecEntities vecEntities;
//	LoadMachineObjList(vecEntities, pObjList);
//
//	//����vecEntities & vecPolyGrid������m_vecProcEntPerGrid
//	CutEntityByGrid(vecEntities, vecPolyGrid);
//
//
//	////�����
//	//double ptOrg[2] = { 100, 100 };
//	//double ptScale[2] = { 1, 1 }; 
//	//double fRotateDegree = 90;
//	//DoTrans(ptOrg, ptScale, fRotateDegree);
//
//	//std::vector<MLine_T> vecMLineAll;
//	//for (auto val : vecEntities)
//	//{
//	//	vecMLineAll.push_back(val.mlineObj);
//	//}
//
//	//std::vector<MLine_T> vecMLinePerGrid;
//	//std::vector<Polygon_T> vecPoly;
//	//for (auto valList : m_vecProcEntPerGrid)
//	//{
//	//	Polygon_T polyTmp;
//	//	VecEntities vecEntTmp;
//	//	polyTmp = valList.polyGrid;
//	//	vecEntTmp = valList.vecEntitiesPerGrid;
//	//	vecPoly.push_back(valList.polyGrid);
//
//	//	for (auto val : vecEntTmp)
//	//	{
//	//		vecMLinePerGrid.push_back(val.mlineObj);
//	//	}
//	//}
//
//	//std::vector<MLine_T> vecMLinePerGridTrans;
//	//std::vector<Polygon_T> vecPolyTrans;
//	//for (auto valListTrans : m_vecProcEntPerGridTrans)
//	//{
//	//	Polygon_T polyTmpTrans;
//	//	VecEntities vecEntTmp;
//	//	polyTmpTrans = valListTrans.polyGrid;
//	//	vecEntTmp = valListTrans.vecEntitiesPerGrid;
//	//	vecPolyTrans.push_back(valListTrans.polyGrid);
//
//	//	for (auto val : vecEntTmp)
//	//	{
//	//		vecMLinePerGridTrans.push_back(val.mlineObj);
//	//	}
//	//}
//
//	//if (1) {}
//		
//}


//ƽ��������ת
void CPreProcess::CalculateTrans(int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark, std::vector<ObjRect> vecGridRect,
	double fPosWorktableX, double fPosWorktableY, double ptOrg[2], double ptScale[2], double* fRotateDegree, double ptReal[2], int nScaleDirection)
{

	//CString str111;

	//����ƽ����ת����
	if (0 == nCountMark)	
	{
		//��mark�� ��ͼ�зָ����½�+��ǰλ��������Ϊԭ��
		ptOrg[0] = vecGridRect[0].min_x;
		ptOrg[1] = vecGridRect[0].min_y;
		ptScale[0] = 1;
		ptScale[1] = 1;
		*fRotateDegree = 0;
		ptReal[0] = fPosWorktableX;
		ptReal[1] = fPosWorktableY;
	}
	else
	{
		//��mark�� ���Ե�һ��mark��Ϊ���
		double fPosCameraX, fPosCameraY;
		fPosCameraX = ReadDevCameraPosX();
		fPosCameraY = ReadDevCameraPosY();
		ptOrg[0] = (double)vPtPosDestinedMark[0].x;
		ptOrg[1] = (double)vPtPosDestinedMark[0].y;
		ptReal[0] = (double)vPtPosRealMark[0].x - fPosCameraX;
		ptReal[1] = (double)vPtPosRealMark[0].y - fPosCameraY;

		//����������ת
		if (1 == nCountMark)
		{
			ptScale[0] = 1;
			ptScale[1] = 1;
			*fRotateDegree = 0;
		}
		else if (2 == nCountMark)
		{
			CPointF ptVecReal, ptVecDestined;
			double fLengthOfVecReal, fLengthOfVecDestined;
			ptVecReal = vPtPosRealMark[1] - vPtPosRealMark[0];
			ptVecDestined = vPtPosDestinedMark[1] - vPtPosDestinedMark[0];
			fLengthOfVecReal = sqrt(pow(ptVecReal.x, 2) + pow(ptVecReal.y, 2));
			fLengthOfVecDestined = sqrt(pow(ptVecDestined.x, 2) + pow(ptVecDestined.y, 2));

			//str111.Format(_T("fLengthOfVecReal = %.3f\nfLengthOfVecDestined = %.3f\nptScale = %.3f"), fLengthOfVecReal, fLengthOfVecDestined, fLengthOfVecReal / fLengthOfVecDestined);
			//AfxMessageBox(str111);

			if (0 == nScaleDirection)
			{
				//ͬ������
				ptScale[0] = fLengthOfVecReal / fLengthOfVecDestined;
				ptScale[1] = fLengthOfVecReal / fLengthOfVecDestined;
				*fRotateDegree = atan2((double)ptVecReal.y, (double)ptVecReal.x) - atan2((double)ptVecDestined.y, (double)ptVecDestined.x);	//ccw ����
				*fRotateDegree *= -180 / M_PI;	//cw �Ƕ�
			}
			else if (1 == nScaleDirection)
			{
				//X��������
				double fPreScaleX, fPreScaleY;
				fPreScaleY = ptVecDestined.y;
				fPreScaleX = sqrt(pow(fLengthOfVecReal, 2) - pow(fPreScaleY, 2));
				ptScale[0] = fPreScaleX / ptVecDestined.x;
				ptScale[1] = 1;
				*fRotateDegree = atan2((double)ptVecReal.y, (double)ptVecReal.x) - atan2(fPreScaleY, fPreScaleX);	//ccw ����
				*fRotateDegree *= -180 / M_PI;	//cw �Ƕ�
			}
			else if (2 == nScaleDirection)
			{
				//Y��������
				double fPreScaleX, fPreScaleY;
				fPreScaleX = ptVecDestined.x;
				fPreScaleY = sqrt(pow(fLengthOfVecReal, 2) - pow(fPreScaleX, 2));
				ptScale[0] = 1;
				ptScale[1] = fPreScaleY / ptVecDestined.y;
				*fRotateDegree = atan2((double)ptVecReal.y, (double)ptVecReal.x) - atan2(fPreScaleY, fPreScaleX);	//ccw ����
				*fRotateDegree *= -180 / M_PI;	//cw �Ƕ�
			}
			else
				AfxMessageBox(_T("��λ��������"));

		}
		else if (3 == nCountMark)
		{

		}
		else if (4 == nCountMark)
		{

		}
		else
			AfxMessageBox(_T("��λ��������"));


	}

	//switch (nCountMark)
	//{
	//case 0:
	//	*ptOrg[0] = vecGridRect[0].min_x;
	//	*ptOrg[1] = vecGridRect[0].min_y;
	//	*ptScale[0] = 1;
	//	*ptScale[1] = 1;
	//	*fRotateDegree = 0;
	//	*ptReal[0] = fPosWorktableX;
	//	*ptReal[1] = fPosWorktableY;
	//	break;
	//case 1:
	//	*ptOrg[0] = (double)vPtPosDestinedMark[0].x;
	//	*ptOrg[1] = (double)vPtPosDestinedMark[0].y;
	//	*ptScale[0] = 1;
	//	*ptScale[1] = 1;
	//	*fRotateDegree = 0;
	//	*ptReal[0] = (double)vPtPosRealMark[0].x - fPosCameraX;
	//	*ptReal[1] = (double)vPtPosRealMark[0].y - fPosCameraY;
	//	break;
	//case 2:
	//	*ptOrg[0] = (double)vPtPosDestinedMark[0].x;
	//	*ptOrg[1] = (double)vPtPosDestinedMark[0].y;
	//	//ptScale[0] = (double)((vPtPosRealMark[1] - vPtPosRealMark[0]) / (vPtPosDestinedMark[1] - vPtPosDestinedMark[0])).x;
	//	//ptScale[1] = (double)((vPtPosRealMark[1] - vPtPosRealMark[0]) / (vPtPosDestinedMark[1] - vPtPosDestinedMark[0])).y;
	//	*ptScale[0] = (vPtPosRealMark[1].x - vPtPosRealMark[0].x) / (vPtPosDestinedMark[1].x - vPtPosDestinedMark[0].x);
	//	*ptScale[1] = (vPtPosRealMark[1].y - vPtPosRealMark[0].y) / (vPtPosDestinedMark[1].y - vPtPosDestinedMark[0].y);
	//	*fRotateDegree = atan2((double)vPtPosRealMark[1].y - vPtPosRealMark[0].y, (double)vPtPosRealMark[1].x - vPtPosRealMark[0].x)
	//		- atan2((double)vPtPosDestinedMark[1].y - vPtPosDestinedMark[0].y, (double)vPtPosDestinedMark[1].x - vPtPosDestinedMark[0].x);
	//	*fRotateDegree *= -180 / M_PI;
	//	*ptReal[0] = (double)vPtPosRealMark[0].x - fPosCameraX;
	//	*ptReal[1] = (double)vPtPosRealMark[0].y - fPosCameraY;
	//	break;
	//case 3:
	//	*ptOrg[0] = (double)vPtPosDestinedMark[0].x;
	//	*ptOrg[1] = (double)vPtPosDestinedMark[0].y;
	//	*ptScale[0] = (vPtPosRealMark[1].x - vPtPosRealMark[0].x) / (vPtPosDestinedMark[1].x - vPtPosDestinedMark[0].x);
	//	*ptScale[1] = (vPtPosRealMark[1].y - vPtPosRealMark[0].y) / (vPtPosDestinedMark[1].y - vPtPosDestinedMark[0].y);
	//	*fRotateDegree = atan2((double)vPtPosRealMark[1].y - vPtPosRealMark[0].y, (double)vPtPosRealMark[1].x - vPtPosRealMark[0].x)
	//		- atan2((double)vPtPosDestinedMark[1].y - vPtPosDestinedMark[0].y, (double)vPtPosDestinedMark[1].x - vPtPosDestinedMark[0].x);
	//	*fRotateDegree *= -180 / M_PI;
	//	*ptReal[0] = (double)vPtPosRealMark[0].x - fPosCameraX;
	//	*ptReal[1] = (double)vPtPosRealMark[0].y - fPosCameraY;
	//	break;
	//case 4:
	//	*ptOrg[0] = (double)vPtPosDestinedMark[0].x;
	//	*ptOrg[1] = (double)vPtPosDestinedMark[0].y;
	//	*ptScale[0] = (vPtPosRealMark[1].x - vPtPosRealMark[0].x) / (vPtPosDestinedMark[1].x - vPtPosDestinedMark[0].x);
	//	*ptScale[1] = (vPtPosRealMark[1].y - vPtPosRealMark[0].y) / (vPtPosDestinedMark[1].y - vPtPosDestinedMark[0].y);
	//	*fRotateDegree = atan2((double)vPtPosRealMark[1].y - vPtPosRealMark[0].y, (double)vPtPosRealMark[1].x - vPtPosRealMark[0].x)
	//		- atan2((double)vPtPosDestinedMark[1].y - vPtPosDestinedMark[0].y, (double)vPtPosDestinedMark[1].x - vPtPosDestinedMark[0].x);
	//	*fRotateDegree *= -180 / M_PI;
	//	*ptReal[0] = (double)vPtPosRealMark[0].x - fPosCameraX;
	//	*ptReal[1] = (double)vPtPosRealMark[0].y - fPosCameraY;
	//	break;
	//default:
	//	AfxMessageBox(_T("��λ��������"));
	//	break;
	//}
}

void CPreProcess::CalculateSingleTrans(CMachineListContainer* pObjList, int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark,
	double ptOrg[2], double ptScale[2], double* fRotateDegree, double ptReal[2], int nScaleDirection)
{
	ObjRect rtBound = pObjList->GetObjBound();

	//����ƽ����ת����
	if (0 == nCountMark)
	{
		//��mark�� ��ͼ�зָ����½�+��ǰλ��������Ϊԭ��
		ptOrg[0] = (rtBound.max_x - rtBound.min_x) / 2;
		ptOrg[1] = (rtBound.max_y - rtBound.min_y) / 2;
		ptScale[0] = 1;
		ptScale[1] = 1;
		*fRotateDegree = 0;
		ptReal[0] = 0;
		ptReal[1] = 0;
	}
	else
	{
		//��mark�� ���Ե�һ��mark��Ϊ���
		double fPosCameraX, fPosCameraY;
		fPosCameraX = ReadDevCameraPosX();
		fPosCameraY = ReadDevCameraPosY();
		ptOrg[0] = (double)vPtPosDestinedMark[0].x;
		ptOrg[1] = (double)vPtPosDestinedMark[0].y;
		ptReal[0] = (double)vPtPosRealMark[0].x - fPosCameraX;
		ptReal[1] = (double)vPtPosRealMark[0].y - fPosCameraY;

		//����������ת
		if (1 == nCountMark)
		{
			ptScale[0] = 1;
			ptScale[1] = 1;
			*fRotateDegree = 0;
		}
		else if (2 == nCountMark)
		{
			CPointF ptVecReal, ptVecDestined;
			double fLengthOfVecReal, fLengthOfVecDestined;
			ptVecReal = vPtPosRealMark[1] - vPtPosRealMark[0];
			ptVecDestined = vPtPosDestinedMark[1] - vPtPosDestinedMark[0];
			fLengthOfVecReal = sqrt(pow(ptVecReal.x, 2) + pow(ptVecReal.y, 2));
			fLengthOfVecDestined = sqrt(pow(ptVecDestined.x, 2) + pow(ptVecDestined.y, 2));

			//str111.Format(_T("fLengthOfVecReal = %.3f\nfLengthOfVecDestined = %.3f\nptScale = %.3f"), fLengthOfVecReal, fLengthOfVecDestined, fLengthOfVecReal / fLengthOfVecDestined);
			//AfxMessageBox(str111);

			if (0 == nScaleDirection)
			{
				//ͬ������
				ptScale[0] = fLengthOfVecReal / fLengthOfVecDestined;
				ptScale[1] = fLengthOfVecReal / fLengthOfVecDestined;
				*fRotateDegree = atan2((double)ptVecReal.y, (double)ptVecReal.x) - atan2((double)ptVecDestined.y, (double)ptVecDestined.x);	//ccw ����
				*fRotateDegree *= -180 / M_PI;	//cw �Ƕ�
			}
			else if (1 == nScaleDirection)
			{
				//X��������
				double fPreScaleX, fPreScaleY;
				fPreScaleY = ptVecDestined.y;
				fPreScaleX = sqrt(pow(fLengthOfVecReal, 2) - pow(fPreScaleY, 2));
				ptScale[0] = fPreScaleX / ptVecDestined.x;
				ptScale[1] = 1;
				*fRotateDegree = atan2((double)ptVecReal.y, (double)ptVecReal.x) - atan2(fPreScaleY, fPreScaleX);	//ccw ����
				*fRotateDegree *= -180 / M_PI;	//cw �Ƕ�
			}
			else if (2 == nScaleDirection)
			{
				//Y��������
				double fPreScaleX, fPreScaleY;
				fPreScaleX = ptVecDestined.x;
				fPreScaleY = sqrt(pow(fLengthOfVecReal, 2) - pow(fPreScaleX, 2));
				ptScale[0] = 1;
				ptScale[1] = fPreScaleY / ptVecDestined.y;
				*fRotateDegree = atan2((double)ptVecReal.y, (double)ptVecReal.x) - atan2(fPreScaleY, fPreScaleX);	//ccw ����
				*fRotateDegree *= -180 / M_PI;	//cw �Ƕ�
			}
			else
				AfxMessageBox(_T("��λ��������"));

		}
		else if (3 == nCountMark)
		{

		}
		else if (4 == nCountMark)
		{

		}
		else
			AfxMessageBox(_T("��λ��������"));

	}
}


void CPreProcess::DoTrans(double ptOrg[2], double ptScale[2], double fRotateDegree, double ptReal[2])
{

	for (auto valList : m_vecProcEntPerGrid)
	{
		PreProcessEntPerGrid prcEntPerGridTmp;
		Polygon_T polyTmp;
		VecEntities vecEntTmp, vecEntTransTmp;
		polyTmp = valList.polyGrid;
		vecEntTmp = valList.vecEntitiesPerGrid;

		//��ÿ��grid����
		Polygon_T polyTranslate, polyScale, polyRotate, polyReal;
		bgt::translate_transformer<double, 2, 2> translate(-ptOrg[0], -ptOrg[1]);
		bg::transform(polyTmp, polyTranslate, translate);
		bgt::scale_transformer<double, 2, 2> scale(ptScale[0], ptScale[1]);
		bg::transform(polyTranslate, polyScale, scale);
		bgt::rotate_transformer<boost::geometry::degree, double, 2, 2> rotate(fRotateDegree);
		bg::transform(polyScale, polyRotate, rotate);
		bgt::translate_transformer<double, 2, 2> translateReal(ptReal[0], ptReal[1]);
		bg::transform(polyRotate, polyReal, translateReal);
		prcEntPerGridTmp.polyGrid = polyReal;

		//��ÿ��grid�еĶ������
		for (auto valEnt : vecEntTmp)
		{
			PreProcessEntity myEntity;
			MLine_T mlineTmp;
			mlineTmp = valEnt.mlineObj;

			MLine_T mlineTranslate, mlineScale, mlineRotate, mlineReal;
			bgt::translate_transformer<double, 2, 2> translate(-ptOrg[0], -ptOrg[1]);
			bg::transform(mlineTmp, mlineTranslate, translate);
			bgt::scale_transformer<double, 2, 2> scale(ptScale[0], ptScale[1]);
			bg::transform(mlineTranslate, mlineScale, scale);
			bgt::rotate_transformer<boost::geometry::degree, double, 2, 2> rotate(fRotateDegree);
			bg::transform(mlineScale, mlineRotate, rotate);
			bgt::translate_transformer<double, 2, 2> translateReal(ptReal[0], ptReal[1]);
			bg::transform(mlineRotate, mlineReal, translateReal);
			myEntity.mlineObj = mlineReal;
			myEntity.nPenNo = valEnt.nPenNo;
			vecEntTransTmp.push_back(myEntity);
		}
		prcEntPerGridTmp.vecEntitiesPerGrid = vecEntTransTmp;

		m_vecProcEntPerGridTrans.push_back(prcEntPerGridTmp);
	}
}

void CPreProcess::DoSingleTrans(CMachineListContainer* pObjList, int nCountMark, std::vector <CPointF> vPtPosDestinedMark, std::vector <CPointF> vPtPosRealMark, int nScaleDirection)
{
	double ptOrg[2], ptScale[2], fRotateDegree, ptReal[2];
	CalculateSingleTrans(pObjList, nCountMark, vPtPosDestinedMark, vPtPosRealMark, ptOrg, ptScale, &fRotateDegree, ptReal, nScaleDirection);
	DoTrans(ptOrg, ptScale, fRotateDegree, ptReal);
}


void CPreProcess::GetGridCenter(int nGridIndex, double* pGridCenterX, double* pGridCenterY)
{
	if (nGridIndex >= m_vecProcEntPerGridTrans.size())
	{
		*pGridCenterX = 0;
		*pGridCenterY = 0;
		return;
	}

	//ȡ�ָ����ģ���m_vecProcEntPerGridTrans��˵ptOrg��ƽ��Ϊ����Բ��
	Polygon_T polyGrid;
	Point_T	ptCenter;
	polyGrid = m_vecProcEntPerGridTrans.at(nGridIndex).polyGrid;
	bg::centroid(polyGrid, ptCenter);

	*pGridCenterX = ptCenter.x();
	*pGridCenterY = ptCenter.y();
	return;
}

BOOL CPreProcess::WriteEntitiesPerGridToBuffer(int nGridIndex, CDeviceCardMark* pDevCardMark, CMachineListContainer* pObjList)
{

	if (NULL == pDevCardMark)
		return FALSE;

	//����մ�꿨������
	if (!pDevCardMark->DeleteALLEntities())
		return FALSE;

	if (nGridIndex >= m_vecProcEntPerGridTrans.size())
		return FALSE;

	//ȡ�ָ�����,m_vecProcEntPerGridTrans�е�һ��mark��������ͼ������ԭ��
	Polygon_T polyGrid;
	Point_T	ptCenter;
	polyGrid = m_vecProcEntPerGridTrans.at(nGridIndex).polyGrid;
	bg::centroid(polyGrid, ptCenter);

	//�������򣬼ӹ�ģʽʶ��	//LayerNum_Default �ӹ���ʼ��
	int nCtProcLayer = pObjList->GetLayerCount() - LayerNum_Default;
	std::vector<VecEntities> vecEntSortByLayer;
	vecEntSortByLayer.resize(nCtProcLayer);
	for (auto valEnt : m_vecProcEntPerGridTrans.at(nGridIndex).vecEntitiesPerGrid)
	{
		//�ݴ�ʺŲ�š�����
		int nPenNo = valEnt.nPenNo;
		PreProcessEntity entTmp;

		//���������Էָ���������,�൱��ƽ��
		MLine_T mlineTmp, mlineTrans;
		mlineTmp = valEnt.mlineObj;
		bgt::translate_transformer<double, 2, 2> translate(-ptCenter.x(), -ptCenter.y());
		bg::transform(mlineTmp, mlineTrans, translate);

		//����������Ӧ��ŵ�vecEntSortByLayer
		entTmp.mlineObj = mlineTrans;
		entTmp.nPenNo = nPenNo;
		vecEntSortByLayer[nPenNo - (int)LayerNum_Default].push_back(entTmp);
	}

	//����ÿһ��
	for (int nIndexLayer = 0; nIndexLayer < nCtProcLayer; nIndexLayer++)
	{
		//�ݴ�ʺţ��жϼӹ�ģʽ�ͼӹ�����
		int nPenNo = nIndexLayer + LayerNum_Default;
		CMachinePara_Layer* pMachineParaLayerTmp = pObjList->GetLayerOfNumber(nPenNo);

		if (0 == pMachineParaLayerTmp->m_MachineMode)								//�и�ģʽ
		{
			if (FALSE == WriteEntitiesToBuffer(vecEntSortByLayer[nIndexLayer]))
				return FALSE;
		}
		else																		//����ģʽ
		{
			////����һ
			////�ֱ����ò����ж����ptBuf
			//std::vector<double (*)[2]> vecPtBuf;
			//std::vector<int> vecCtPt;;
			//for (auto valEnt : vecEntSortByLayer[nIndexLayer])
			//{
			//	int nPenNo = valEnt.nPenNo;

			//	//����ptBuf��д��
			//	BOOST_FOREACH(Line_T const& line, valEnt.mlineObj)
			//	{
			//		int nCountPt;
			//		double(*ptBuf)[2];
			//		nCountPt = (int)line.size();
			//		ptBuf = new double[nCountPt][2];
			//		for (int i = 0; i < nCountPt; i++)
			//		{
			//			ptBuf[i][0] = line[i].x();
			//			ptBuf[i][1] = line[i].y();
			//		}

			//		vecPtBuf.push_back(ptBuf);
			//		vecCtPt.push_back(nCountPt);
			//	}
			//}

			////���ε���ÿ�������ptBuf���ù����ظ�n��
			//int nMarkLoop = pMachineParaLayerTmp->m_MachinePara.Times;
			//while (nMarkLoop--)
			//{
			//	for (int i; i < vecPtBuf.size(); i++)
			//	{
			//		if (FALSE == pDevCardMark->AddEntityLines(vecCtPt[i], vecPtBuf[i], nPenNo))
			//		{
			//			//delete[] ptBuf;
			//			return FALSE;
			//		}
			//	}
			//}

			//������
			int nMarkLoop = pMachineParaLayerTmp->m_MachinePara.Times;
			while (nMarkLoop--)
			{
				if (FALSE == WriteEntitiesToBuffer(vecEntSortByLayer[nIndexLayer]))
					return FALSE;
			}
		}
	}

	return TRUE;

	/*

	//�ָ������ж�����Էָ���������,�൱��ƽ��
	VecEntities vecEntities;
	vecEntities = m_vecProcEntPerGridTrans.at(nGridIndex).vecEntitiesPerGrid;
	for (auto valEnt : vecEntities)
	{
		int nPenNo = valEnt.nPenNo;

		MLine_T mlineTmp, mlineTrans;
		mlineTmp = valEnt.mlineObj;
		bgt::translate_transformer<double, 2, 2> translate(-ptCenter.x(), -ptCenter.y());
		bg::transform(mlineTmp, mlineTrans, translate);

		BOOST_FOREACH(Line_T const& line, mlineTrans)
		{
		   	int nCountPt;
			double(*ptBuf)[2];
			nCountPt = (int)line.size();
			ptBuf = new double[nCountPt][2];

			for (int i = 0; i < nCountPt; i++)
			{
				ptBuf[i][0] = line[i].x();
				ptBuf[i][1] = line[i].y();
			}

			//������д��忨������
			if (FALSE == pDevCardMark->AddEntityLines(nCountPt, ptBuf, nPenNo))
			{
				delete[] ptBuf;
				return FALSE;
			}
		}
	}

	*/
}

BOOL CPreProcess::WriteEntitiesToBuffer(VecEntities& vecEntities)
{
	for (auto valEnt : vecEntities)
	{
		int nPenNo = valEnt.nPenNo;

		//����ptBuf��д��
		BOOST_FOREACH(Line_T const& line, valEnt.mlineObj)
		{
			int nCountPt = (int)line.size();
			double(*ptBuf)[2] = new double[nCountPt][2];
			for (int i = 0; i < nCountPt; i++)
			{
				ptBuf[i][0] = line[i].x();
				ptBuf[i][1] = line[i].y();
			}

			//������д��忨������
			if (FALSE == pDevCardMark->AddEntityLines(nCountPt, ptBuf, nPenNo))
			{
				//AfxMessageBox(_T("�и�ģʽreturn flase"));
				delete[] ptBuf;
				return FALSE;
			}
			delete[] ptBuf;
		}
	}
	return TRUE;
}


void CPreProcess::CutEntityByGrid1(VecEntities& vecEntities, std::vector<Polygon_T>& vecPolyGrid)
{
	//CString strTime;
	//long t1 = GetTickCount();//����ο�ʼǰȡ��ϵͳ����ʱ��(ms)            

	for (auto valGrid : vecPolyGrid)
	{
		PreProcessEntPerGrid prcEntPerGridTmp;
		VecEntities vecEntitiesPerGrid;

		for (auto iter = vecEntities.begin(); iter != vecEntities.end(); /*iter++*/)
		{
			//mlineObj -> mlineTmp�������������ཻ�󣬿����ѱ�Ϊ�����߶�
			PreProcessEntity myEntityTmp;
			MLine_T mlineTmp, mlineDiffer;

			//�ж϶�����ָ�Ԫ��λ�ù�ϵ
			if (TRUE == bg::covered_by((*iter).mlineObj, valGrid))
			{
				//����
				vecEntitiesPerGrid.push_back((*iter));
				iter = vecEntities.erase(iter);
			}
			else
			{
				//������ཻ
				if(bg::intersects((*iter).mlineObj, valGrid))
				{
					bg::intersection((*iter).mlineObj, valGrid, mlineTmp);
					bg::difference((*iter).mlineObj, mlineTmp, mlineDiffer);
					myEntityTmp.mlineObj = mlineTmp;
					myEntityTmp.nPenNo = (*iter).nPenNo;
					vecEntitiesPerGrid.push_back(myEntityTmp);
					(*iter).mlineObj = mlineDiffer;
				}
				iter++;
			}
		}
		prcEntPerGridTmp.polyGrid = valGrid;
		prcEntPerGridTmp.vecEntitiesPerGrid = vecEntitiesPerGrid;
		m_vecProcEntPerGrid.push_back(prcEntPerGridTmp);
	}

	//long t2 = GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms) 
	//long nCtSize = 0;
	//for (auto val1 : m_vecProcEntPerGrid)
	//{
	//	for (auto val2 : val1.vecEntitiesPerGrid)
	//	{
	//		for (auto val3 : val2.mlineObj)
	//		{
	//			nCtSize += val3.size();
	//		}
	//	}
	//}
	//strTime.Format(_T("Size: %d\ntime:%dms"), nCtSize, t2 - t1);//ǰ��֮���������ʱ��        
	//AfxMessageBox(strTime);

}

void CPreProcess::CutEntityByGrid(VecEntities& vecEntities, std::vector<Polygon_T>& vecPolyGrid)
{
	//CString strTime;
	//long t1 = GetTickCount();//����ο�ʼǰȡ��ϵͳ����ʱ��(ms)            

	for (auto valGrid : vecPolyGrid)
	{
		PreProcessEntPerGrid prcEntPerGridTmp;
		VecEntities vecEntitiesPerGrid;

		for (auto iter = vecEntities.begin(); iter != vecEntities.end(); /*iter++*/)
		{
			//mlineObj -> mlineTmp�������������ཻ�󣬿����ѱ�Ϊ�����߶�
			PreProcessEntity myEntityTmp;
			MLine_T mlineTmp, mlineDiffer;

			//�ж϶�����ָ�Ԫ��λ�ù�ϵ
			bg::intersection((*iter).mlineObj, valGrid, mlineTmp);
			if (TRUE == mlineTmp.empty())				//����ڿ��⣬ɶҲ����
			{
				iter++;
			}
			else
			{
				myEntityTmp.mlineObj = mlineTmp;
				myEntityTmp.nPenNo = (*iter).nPenNo;
				vecEntitiesPerGrid.push_back(myEntityTmp);

				bg::difference((*iter).mlineObj, mlineTmp, mlineDiffer);
				if (TRUE == mlineDiffer.empty())		//�����������ԭ����ɾ���ö���
				{
					iter = vecEntities.erase(iter);
				}
				else									//����ཻ���зֱ�gridѡ�еĶ���
				{
					(*iter).mlineObj = mlineDiffer;
					iter++;
				}
			}
		}
		prcEntPerGridTmp.polyGrid = valGrid;
		prcEntPerGridTmp.vecEntitiesPerGrid = vecEntitiesPerGrid;
		m_vecProcEntPerGrid.push_back(prcEntPerGridTmp);
	}

	//long t2 = GetTickCount();//����ν�����ȡ��ϵͳ����ʱ��(ms) 
	//long nCtSize = 0;
	//for (auto val1 : m_vecProcEntPerGrid)
	//{
	//	for (auto val2 : val1.vecEntitiesPerGrid)
	//	{
	//		for (auto val3 : val2.mlineObj)
	//		{
	//			nCtSize += val3.size();
	//		}
	//	}
	//}
	//strTime.Format(_T("Size: %d\ntime:%dms"), nCtSize, t2 - t1);//ǰ��֮���������ʱ��        
	//AfxMessageBox(strTime);

}

void CPreProcess::CutEntityByGridOverlap(VecEntities& vecEntities, std::vector<Polygon_T>& vecPolyGrid, double fOverlapLength)
{
	//double fUltralimit = 1;

	////����ÿ���ָ�
	//for (auto valGrid : vecPolyGrid)
	//{
	//	PreProcessEntPerGrid prcEntPerGridTmp;		//��valGrid�ָ������еĶ���+valGrid
	//	VecEntities vecEntitiesPerGrid;				//��valGrid�ָ������еĶ���
	//	//�����ָ��е�ÿ������
	//	for (auto& valEntity : vecEntities)
	//	{
	//		//mlineObj -> mlineTmp�������������ཻ�󣬿����ѱ�Ϊ�����߶�
	//		PreProcessEntity myEntityTmp;
	//		MLine_T mlineTmp, mlineDiffer;

	//		//����ÿ�������е�
	//		BOOST_FOREACH(Line_T const& line, valEntity.mlineObj)
	//		{
	//			//
	//			for (auto valPt : line)
	//			{
	//				//���valPt�����һ���㣬���˳�ѭ��
	//				if (bg::equals(valPt, line.end()))
	//					break;
	//			}


	//			MLine_T mlineIntersect;
	//			bg::intersection(line, valGrid, mlineIntersect);

	//			if (TRUE == mlineTmp.empty())
	//				continue;


	//		}

	//		bg::intersection(valEntity.mlineObj, valGrid, mlineTmp);
	//		
	//		//�ཻ�����ɸѡ�߶�
	//		//1. û�б��зֵ� -> ���ù�
	//		//2. ���зֵ���û�г��޵� -> ѡ���grid��vecEntities��ɾ�����߶�
	//		//3. ���зֵ��ҳ��޵� -> //�зֵ������ߣ��ֱ��ڽ��㴦���ӳ��ص����ȣ�
	//								 //һ��ѡ���grid��һ�����뵽vecEntities�У�
	//								 //vecEntities��ɾ��ԭ�߶�


	//		myEntityTmp.mlineObj = mlineTmp;
	//		myEntityTmp.nPenNo = valEntity.nPenNo;
	//		vecEntitiesPerGrid.push_back(myEntityTmp);

	//		//�зֱ�gridѡ�еĶ���
	//		if (FALSE == mlineTmp.empty())
	//		{
	//			bg::difference(valEntity.mlineObj, mlineTmp, mlineDiffer);
	//			valEntity.mlineObj = mlineDiffer;
	//		}

	//	}
	//	prcEntPerGridTmp.polyGrid = valGrid;
	//	prcEntPerGridTmp.vecEntitiesPerGrid = vecEntitiesPerGrid;
	//	m_vecProcEntPerGrid.push_back(prcEntPerGridTmp);
	//}
}


void CPreProcess::LoadMachineObjList(VecEntities& vecEntities, CMachineListContainer* pObjList)
{
	//����ն����
	vecEntities.clear();

	////д�ӹ�����
	//SetPensFromAllLayers(pObjList);

	//��list
	CMachineObj_Comm* pObj;
	POSITION pos;
	pos = pObjList->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjList->GetObjNext(pos);
		LoadMachineObj(vecEntities, pObj);
	}

	////�������ݿ⵽�ļ���
	//if (!SaveEntityToFile())
	//	return;
}

void CPreProcess::LoadMachineObj(VecEntities& vecEntities, CMachineObj_Comm* pObj)
{
	//�˹�mark��
	if (LayerNum_Mark == pObj->m_ObjByLayer)
		return;

	//��ǰ��ʼ����case MachineObj_Type_Polylineʹ��
	ObjPoint ptPolylineLast, ptPolyline;
	int nLayer = pObj->m_ObjByLayer;
	std::vector<ObjPoint> vecPolylinePtBuf;

	switch (pObj->GetObjType())
	{
	case MachineObj_Type_Point:
		//***DrawPoint***
		CMachineObjPoint* pPoint;
		pPoint = (CMachineObjPoint*)pObj;
		break;
	case MachineObj_Type_Line:
		//***DrawLine***
		CMachineObjLine* pLine;
		pLine = (CMachineObjLine*)pObj;

		double ptPos[2][2];
		ptPos[0][0] = pLine->GetLineStart().x;
		ptPos[0][1] = pLine->GetLineStart().y;
		ptPos[1][0] = pLine->GetLineEnd().x;
		ptPos[1][1] = pLine->GetLineEnd().y;

		AddEntityLines(vecEntities, 2, ptPos, nLayer);
		break;
	case MachineObj_Type_Circle:
		//***DrawCircle***
		CMachineObjCircle* pCircle;
		pCircle = (CMachineObjCircle*)pObj;

		double ptCircleCenterPos[2], fCircleRadius, fCircleAngleStart;
		int nCircleDir;
		ptCircleCenterPos[0] = pCircle->GetCircleCenter().x;
		ptCircleCenterPos[1] = pCircle->GetCircleCenter().y;
		fCircleRadius = pCircle->GetCircleRadius();
		fCircleAngleStart = 90 * (double)pCircle->GetCircleStartNum();
		nCircleDir = (int)pCircle->GetCircleDir();

		AddEntityCircle(vecEntities, ptCircleCenterPos, fCircleRadius, fCircleAngleStart, nCircleDir, nLayer);
		break;
	case MachineObj_Type_Arc:
		//***DrawArc***
		CMachineObjArc* pArc;
		pArc = (CMachineObjArc*)pObj;

		double ptArcCenterPos[2], fArcRadius, fArcAngleStart, fArcAngleEnd;
		int nArcDir;
		ptArcCenterPos[0] = pArc->GetArcCenter().x;
		ptArcCenterPos[1] = pArc->GetArcCenter().y;
		fArcRadius = pArc->GetArcRadius();
		fArcAngleStart = pArc->GetStartAngle();
		fArcAngleEnd = pArc->GetEndAngle();
		nArcDir = (int)pArc->GetArcDir();

		AddEntityArc(vecEntities, ptArcCenterPos, fArcRadius, fArcAngleStart, fArcAngleEnd, nArcDir, nLayer);
		break;
	case MachineObj_Type_Ellipse:
		//***DrawEllipse***
		CMachineObjEllipse* pEllipse;
		pEllipse = (CMachineObjEllipse*)pObj;
		break;
	case MachineObj_Type_ArcEll:
		//***DrawArcEll***
		CMachineObjArcEll* pArcEll;
		pArcEll = (CMachineObjArcEll*)pObj;
		break;
	case MachineObj_Type_TiltEllipse:
		//***DrawTiltEllipse***
		CMachineObjTiltEllipse* pTiltEllArc;
		pTiltEllArc = (CMachineObjTiltEllipse*)pObj;
		break;
	case MachineObj_Type_Polyline:
		//***DrawPolyline***
		CMachineObjPolyline* pPolyline;
		pPolyline = (CMachineObjPolyline*)pObj;

		int nVertCount;
		double fConvexityLast;
		//ObjPoint ptPolylineLast, ptPolyline;

		nVertCount = pPolyline->GetPolylineVertexCount();
		ptPolylineLast.x = pPolyline->GetPolylineStart().x;
		ptPolylineLast.y = pPolyline->GetPolylineStart().y;
		fConvexityLast = pPolyline->GetPolylineStart().convexity;

		vecPolylinePtBuf.clear();
		vecPolylinePtBuf.push_back(ObjPoint(ptPolylineLast.x, ptPolylineLast.y));

		for (int i = 1; i < nVertCount; i++)
		{
			//����ǰ����i
			ptPolyline.x = pPolyline->GetPolylinePoint(i).x;
			ptPolyline.y = pPolyline->GetPolylinePoint(i).y;

			//�����һ������i-1��͹��
			if (0 == fConvexityLast)
			{
				//����i-1 to ����i ��ֱ��
				//double ptPos[2][2];
				//ptPos[0][0] = ptPolylineLast.x;
				//ptPos[0][1] = ptPolylineLast.y;
				//ptPos[1][0] = ptPolyline.x;
				//ptPos[1][1] = ptPolyline.y;
				//AddEntityLines(vecEntities, 2, ptPos, nLayer);
				vecPolylinePtBuf.push_back(ObjPoint(ptPolyline.x, ptPolyline.y));
			}
			else
			{
				//����i-1 to ����i ��Բ��
				ObjPoint ArcCenter;
				double /*ptArcCenterPos[2],*/ fArcRadius, fArcAngleStart, fArcAngleEnd;
				int nArcDir;

				pPolyline->TranPolylineToArc(
					ptPolylineLast, ptPolyline, fConvexityLast,
					&ArcCenter, &fArcRadius, &fArcAngleStart, &fArcAngleEnd);
				//ptArcCenterPos[0] = ArcCenter.x;
				//ptArcCenterPos[1] = ArcCenter.y;
				nArcDir = (fArcAngleStart > fArcAngleEnd) ? (int)CW : (int)CCW;

				//AddEntityArc(vecEntities, ptArcCenterPos, fArcRadius, fArcAngleStart, fArcAngleEnd, nArcDir, nLayer);

				//����Բ���ϲ岹����
				int nCountPt;
				double fAngleDelt = fArcAngleEnd - fArcAngleStart;
				double fMarkArcStepAngle;
				fMarkArcStepAngle = m_fMarkArcStep / fArcRadius * 180 / M_PI;
				ObjPoint ptTmp;

				if (0 == nArcDir)//˳ʱ��
				{
					if (0 <= fAngleDelt)//�ӻ�
						nCountPt = (int)(((M_PI * (360 - fAngleDelt) / 180) * fArcRadius) / m_fMarkArcStep) + 1;
					else//�Ż�
						nCountPt = (int)(((M_PI * abs(fAngleDelt) / 180) * fArcRadius) / m_fMarkArcStep) + 1;

					//ptBuf = new double[nCountPt][2];

					for (int i = 0; i < nCountPt - 1; i++)
					{
						//ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
						//ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);

						fArcAngleStart -= fMarkArcStepAngle;
						ptTmp.x = ArcCenter.x + fArcRadius * cos(M_PI * fArcAngleStart / 180);
						ptTmp.y = ArcCenter.y + fArcRadius * sin(M_PI * fArcAngleStart / 180);
						vecPolylinePtBuf.push_back(ptTmp);
					}

					//ptBuf[nCountPt - 1][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleEnd / 180);
					//ptBuf[nCountPt - 1][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleEnd / 180);
					ptTmp.x = ArcCenter.x + fArcRadius * cos(M_PI * fArcAngleEnd / 180);
					ptTmp.y = ArcCenter.y + fArcRadius * sin(M_PI * fArcAngleEnd / 180);
					vecPolylinePtBuf.push_back(ptTmp);
				}
				else if (1 == nArcDir)//��ʱ��
				{
					if (0 <= fAngleDelt)//�Ż�
						nCountPt = (int)(((M_PI * fAngleDelt / 180) * fArcRadius) / m_fMarkArcStep) + 1;
					else//�ӻ�
						nCountPt = (int)(((M_PI * (360 - abs(fAngleDelt)) / 180) * fArcRadius) / m_fMarkArcStep) + 1;

					//ptBuf = new double[nCountPt][2];

					for (int i = 0; i < nCountPt - 1; i++)
					{
						//ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
						//ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
						fArcAngleStart += fMarkArcStepAngle;
						ptTmp.x = ArcCenter.x + fArcRadius * cos(M_PI * fArcAngleStart / 180);
						ptTmp.y = ArcCenter.y + fArcRadius * sin(M_PI * fArcAngleStart / 180);
						vecPolylinePtBuf.push_back(ptTmp);
					}

					//ptBuf[nCountPt - 1][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleEnd / 180);
					//ptBuf[nCountPt - 1][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleEnd / 180);
					ptTmp.x = ArcCenter.x + fArcRadius * cos(M_PI * fArcAngleEnd / 180);
					ptTmp.y = ArcCenter.y + fArcRadius * sin(M_PI * fArcAngleEnd / 180);
					vecPolylinePtBuf.push_back(ptTmp);

				}


			}

			//����ptPolylineLast��fConvexityLast
			if (i < nVertCount - 1)
			{
				ptPolylineLast = ptPolyline;
				fConvexityLast = pPolyline->GetPolylinePoint(i).convexity;
			}
		}

		//���ж���߶�ȡ���,һ��д�뻺����
		int nCountPtPolyline;
		double(*ptBuf)[2];

		nCountPtPolyline = (int)vecPolylinePtBuf.size();
		ptBuf = new double[nCountPtPolyline][2];
		for (int i = 0; i < nCountPtPolyline; i++)
		{
			ptBuf[i][0] = vecPolylinePtBuf[i].x;
			ptBuf[i][1] = vecPolylinePtBuf[i].y;
		}
		AddEntityLines(vecEntities, nCountPtPolyline, ptBuf, nLayer);
		delete[] ptBuf;

		break;
	case MachineObj_Type_Group:
		//***DrawGroup***
		CMachineObjGroup* pGroup;
		CMachineObjList* pList;
		pGroup = (CMachineObjGroup*)pObj;
		pList = pGroup->GetObjList();
		POSITION pos;
		pos = pList->GetHeadPosition();
		while (pos)
		{
			CMachineObj_Comm* pObj;
			pObj = pList->GetNext(pos);
			LoadMachineObj(vecEntities, pObj);
		}
		break;
		//*****�����ʹ���****
	default:
		break;
	}

}

void CPreProcess::AddEntityLines(VecEntities& vecEntities, int nCount, double ptPos[][2], int nPenNo)
{
	//��objList����ʱ��mlineTmpֻ�ܿ��������������
	//���ڷָ����忨������ʱ��mlineTmp�����ѱ�Ϊ���������

	PreProcessEntity myEntity;
	myEntity.nPenNo = nPenNo;

	MLine_T	mlineTmp;
	mlineTmp.resize(1);
	for (int i = 0; i < nCount; i++)
	{
		bg::append(mlineTmp[0], Point_T(ptPos[i][0], ptPos[i][1]));
	}
	myEntity.mlineObj = mlineTmp;

	vecEntities.push_back(myEntity);
}
void CPreProcess::AddEntityCircle(VecEntities& vecEntities, double ptCenterPos[2], double fRadius, double fAngleStart, int nDir, int nPenNo)
{
	//����Բ�ϲ岹����
	int nCountPt;
	double(*ptBuf)[2];
	double fMarkArcStepAngle;

	fMarkArcStepAngle = m_fMarkArcStep / fRadius * 180 / M_PI;
	nCountPt = (int)((2 * M_PI * fRadius) / m_fMarkArcStep) + 2;
	ptBuf = new double[nCountPt][2];

	if (0 == nDir)//˳ʱ��
	{
		for (int i = 0; i < nCountPt - 1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart -= fMarkArcStepAngle;
		}

		ptBuf[nCountPt - 1][0] = ptBuf[0][0];
		ptBuf[nCountPt - 1][1] = ptBuf[0][1];
	}
	else if (1 == nDir)//��ʱ��
	{
		for (int i = 0; i < nCountPt - 1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart += fMarkArcStepAngle;
		}

		ptBuf[nCountPt - 1][0] = ptBuf[0][0];
		ptBuf[nCountPt - 1][1] = ptBuf[0][1];
	}
	else
	{
		return;
	}


	AddEntityLines(vecEntities, nCountPt, ptBuf, nPenNo);

}


void CPreProcess::AddEntityArc(VecEntities& vecEntities, double ptCenterPos[2], double fRadius, double fAngleStart, double fAngleEnd, int nDir, int nPenNo)
{
	//����Բ���ϲ岹����
	int nCountPt;
	double(*ptBuf)[2];
	double fAngleDelt = fAngleEnd - fAngleStart;
	double fMarkArcStepAngle;
	fMarkArcStepAngle = m_fMarkArcStep / fRadius * 180 / M_PI;

	if (0 == nDir)//˳ʱ��
	{
		if (0 <= fAngleDelt)//�ӻ�
			nCountPt = (int)(((M_PI * (360 - fAngleDelt) / 180) * fRadius) / m_fMarkArcStep) + 2;
		else//�Ż�
			nCountPt = (int)(((M_PI * abs(fAngleDelt) / 180) * fRadius) / m_fMarkArcStep) + 2;

		ptBuf = new double[nCountPt][2];

		for (int i = 0; i < nCountPt - 1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart -= fMarkArcStepAngle;
		}

		ptBuf[nCountPt - 1][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleEnd / 180);
		ptBuf[nCountPt - 1][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleEnd / 180);
	}
	else if (1 == nDir)//��ʱ��
	{
		if (0 <= fAngleDelt)//�Ż�
			nCountPt = (int)(((M_PI * fAngleDelt / 180) * fRadius) / m_fMarkArcStep) + 2;
		else//�ӻ�
			nCountPt = (int)(((M_PI * (360 - abs(fAngleDelt)) / 180) * fRadius) / m_fMarkArcStep) + 2;

		ptBuf = new double[nCountPt][2];

		for (int i = 0; i < nCountPt - 1; i++)
		{
			ptBuf[i][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleStart / 180);
			ptBuf[i][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleStart / 180);
			fAngleStart += fMarkArcStepAngle;
		}

		ptBuf[nCountPt - 1][0] = ptCenterPos[0] + fRadius * cos(M_PI * fAngleEnd / 180);
		ptBuf[nCountPt - 1][1] = ptCenterPos[1] + fRadius * sin(M_PI * fAngleEnd / 180);
	}
	else
	{
		return;
	}


	AddEntityLines(vecEntities, nCountPt, ptBuf, nPenNo);

}

//ץ�����
int CPreProcess::GenMarkPoints(std::vector <CPointF> vPtPosDestinedMark, std::vector <HalconModel> vMarkPointModel, CMachineListContainer* pObjList)
{
	vPtPosDestinedMark.resize(0);
	vMarkPointModel.resize(0);

	POSITION pos;
	CMachineObj_Comm* pObj;
	ObjRect objRectTmp;
	int nLayerMark, nLayerTmp;
	int nIndexMarkPoint = 0;

	nLayerMark = pObjList->FindLayerByName(LayerName_Mark);
	if (0 > nLayerMark)
		return FALSE;

	pos = pObjList->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjList->GetObjNext(pos);
		nLayerTmp = pObj->m_ObjByLayer;
		if (nLayerTmp != nLayerMark)
			continue;

		//�ҵ�һ��mark�㣬���mark����������
		objRectTmp = pObj->GetObjBound();
		CPointF ptTmp((FLOAT)(objRectTmp.max_x + objRectTmp.min_x) / 2,
			(FLOAT)(objRectTmp.max_y + objRectTmp.min_y) / 2);
		vPtPosDestinedMark.push_back(ptTmp);

		//����mark��ģ��
		HalconModel hModelTmp;
		if (FALSE == GenMarkPointModel(&hModelTmp, pObj))
		{
			continue;
		}
		vMarkPointModel.push_back(hModelTmp);

		nIndexMarkPoint++;
		if (2 <= nIndexMarkPoint)
			break;
	}

	if (2 != nIndexMarkPoint)
	{
		AfxMessageBox(_T("��������������mark��\nMark������ΪԲ��ʮ�ֲ�"));
		return 0;
	}

	return nIndexMarkPoint;
}
BOOL CPreProcess::GenMarkPointModel(HalconModel* pHalconModel, CMachineObj_Comm* pObj, double fCrossWidthPixel)
{
	if (MachineObj_Type_Circle == pObj->GetObjType())
	{
		CMachineObjCircle* pObjCircle = (CMachineObjCircle*)pObj;
		double fRadius = pObjCircle->GetCircleRadius();
		double fPixelSize = ReadDevCameraPixelSize();

		HalconModel hModelTmp(_T("Բ"), fRadius, fPixelSize);
		*pHalconModel = hModelTmp;
	}
	else if (MachineObj_Type_Group == pObj->GetObjType())
	{

	}

	return TRUE;
}
