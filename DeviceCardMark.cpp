#include "stdafx.h"
#include "DeviceCardMark.h"
#include "MainFrm.h"
#include "LaserMachineDoc.h"
#include "PointF.h"

CDeviceCardMark::CDeviceCardMark()
{
	m_bMarkOrRedIsRunning = FALSE;
	m_fMarkArcStep = 0.1;
}

CDeviceCardMark::~CDeviceCardMark()
{

}

void CDeviceCardMark::LoadMachineObjList(CMachineListContainer* pObjList)
{
	//����մ�꿨������
	if (!DeleteALLEntities())
		return;

	//д�ӹ�����
	SetPensFromAllLayers(pObjList);

	//��list
	CMachineObj_Comm* pObj;
	POSITION pos;
	pos = pObjList->GetObjHeadPosition();
	while (pos)
	{
		pObj = pObjList->GetObjNext(pos);
		LoadMachineObj(pObj);
	}

	//�������ݿ⵽�ļ���
	if (!SaveEntityToFile())
		return;
}

void CDeviceCardMark::LoadMachineObj(CMachineObj_Comm* pObj)
{
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

		AddEntityLines(2, ptPos, nLayer);
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
		nCircleDir = (int) pCircle->GetCircleDir();

		AddEntityCircle(ptCircleCenterPos, fCircleRadius, fCircleAngleStart, nCircleDir, nLayer);
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
		nArcDir = (int) pArc->GetArcDir();

		AddEntityArc(ptArcCenterPos, fArcRadius, fArcAngleStart, fArcAngleEnd, nArcDir, nLayer);
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
				//AddEntityLines(2, ptPos, nLayer);
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

				//AddEntityArc(ptArcCenterPos, fArcRadius, fArcAngleStart, fArcAngleEnd, nArcDir, nLayer);

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
		AddEntityLines(nCountPtPolyline, ptBuf, nLayer);
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
			LoadMachineObj(pObj);
		}
		break;
		//*****�����ʹ���****
	default:
		break;
	}

}
