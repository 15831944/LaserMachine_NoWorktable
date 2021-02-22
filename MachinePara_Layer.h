// CMachinePara_Layer �ӹ���������
//
#pragma once
#include "MachineObjDef.h"

// CMachinePara_Layer ����Ŀ��
class CMachinePara_Layer : public CObject
{
// ����
public:
	CMachinePara_Layer();
	CMachinePara_Layer(CString LayerName, BYTE MachineMode,
		ProcessPara MachinePara, BOOL bIsLayerSel = FALSE);
	virtual ~CMachinePara_Layer();

// ����
public:
	CString m_LayerName;		//����
	BYTE m_MachineMode;			//�ӹ���ʽ 0:�и� 1:����
	ProcessPara m_MachinePara;	//�ӹ�����
	BOOL m_bIsLayerSel;			//ѡ�б�־
// ����
	virtual void Serialize(CArchive& ar);
};
// �ӹ��������б� CMachine_LayerList
typedef CTypedPtrList<CObList, CMachinePara_Layer*> CMachine_LayerList;
