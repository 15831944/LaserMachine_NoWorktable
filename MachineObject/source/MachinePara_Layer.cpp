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
	m_bIsLayerStatus = IsObjNormal;
}
CMachinePara_Layer::CMachinePara_Layer(CString LayerName, BYTE MachineMode,
	ProcessPara MachinePara, byte bIsLayerStatus)
{
	m_LayerName = LayerName;
	m_MachineMode = MachineMode;
	m_MachinePara = MachinePara;
	m_bIsLayerStatus = bIsLayerStatus;
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
		ar << m_MachinePara.LaserOnDelay;
		ar << m_MachinePara.LaserOffDelay;
		ar << m_MachinePara.BeforMarkDelay;
		ar << m_MachinePara.AfterMarkDelay;
		ar << m_MachinePara.PolylineDelay;
	}
	else
	{	
		ar >> m_LayerName >> m_MachineMode;
		ar >> m_MachinePara.Frequncy;
		ar >> m_MachinePara.Power;
		ar >> m_MachinePara.PulseWidth;
		ar >> m_MachinePara.Speed;
		ar >> m_MachinePara.Times;
		ar >> m_MachinePara.LaserOnDelay;
		ar >> m_MachinePara.LaserOffDelay;
		ar >> m_MachinePara.BeforMarkDelay;
		ar >> m_MachinePara.AfterMarkDelay;
		ar >> m_MachinePara.PolylineDelay;
	}
}
