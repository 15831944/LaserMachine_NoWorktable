// CMachinePara_Layer 加工参数层类
//
#pragma once
#include "MachineObjDef.h"

// CMachinePara_Layer 命令目标
class CMachinePara_Layer : public CObject
{
// 构造
public:
	CMachinePara_Layer();
	CMachinePara_Layer(CString LayerName, BYTE MachineMode,
		ProcessPara MachinePara, BOOL bIsLayerSel = FALSE);
	virtual ~CMachinePara_Layer();

// 特性
public:
	CString m_LayerName;		//层名
	BYTE m_MachineMode;			//加工方式 0:切割 1:遍历
	ProcessPara m_MachinePara;	//加工参数
	BOOL m_bIsLayerSel;			//选中标志
// 操作
	virtual void Serialize(CArchive& ar);
};
// 加工参数层列表 CMachine_LayerList
typedef CTypedPtrList<CObList, CMachinePara_Layer*> CMachine_LayerList;
