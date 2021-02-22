// CMachinePara_Layer.cpp : 实现文件
//
#include "stdafx.h"
#include "MachinePara_Layer.h"

// CMachinePara_Layer 构造函数
CMachinePara_Layer::CMachinePara_Layer()
{
	m_LayerName = _T("");
	m_MachineMode = 0;
	m_MachinePara = ProcessPara();
	m_bIsLayerSel = FALSE;
}
CMachinePara_Layer::CMachinePara_Layer(CString LayerName, BYTE MachineMode,
	ProcessPara MachinePara, BOOL bIsLayerSel)
{
	m_LayerName = LayerName;
	m_MachineMode = MachineMode;
	m_MachinePara = MachinePara;
	m_bIsLayerSel = bIsLayerSel;
}

CMachinePara_Layer::~CMachinePara_Layer()
{
}

// CMachinePara_Layer 成员函数


void CMachinePara_Layer::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	
		ar << m_LayerName << m_MachineMode;
		ar << m_MachinePara.Frequncy;
		ar << m_MachinePara.Power;
		ar << m_MachinePara.PulseWidth;
		ar << m_MachinePara.Speed;
		ar << m_MachinePara.Times;
	}
	else
	{	
		ar >> m_LayerName >> m_MachineMode;
		ar >> m_MachinePara.Frequncy;
		ar >> m_MachinePara.Power;
		ar >> m_MachinePara.PulseWidth;
		ar >> m_MachinePara.Speed;
		ar >> m_MachinePara.Times;
	}
}
