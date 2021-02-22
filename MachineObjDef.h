// MachineObjDef.h
// 常数,数据类型及其他
//
//* 数据类型 *
// 外框
#pragma once
typedef struct TagObjRect
{
	double    min_x;
	double    max_x;
	double    min_y;
	double    max_y;
	TagObjRect() :min_x(0), max_x(0), min_y(0), max_y(0){}
} ObjRect;

// 点
typedef struct TagObjPoint
{
	double   x;
	double   y;
	TagObjPoint() :x(0), y(0){}
	TagObjPoint(double x, double y) :x(x), y(y){}
} ObjPoint;

// 顶点
typedef struct TagObjVPoint
{
	double   x;
	double   y;
	double convexity;
	TagObjVPoint() :x(0), y(0), convexity(1){}
	TagObjVPoint(double x, double y, int cv) :x(x), y(y), convexity(cv){}
} ObjVPoint;

// 加工参数
typedef struct TagProcessPara
{
	BYTE  Times;		//加工次数
	float Speed;		//加工速度 单位mm/s
	float Power;		//激光功率 0-100%
	UINT  Frequncy;		//频率 单位Hz
	float PulseWidth;	//脉宽 单位us
	TagProcessPara() :Times(0), Speed(0), Power(0), Frequncy(0), PulseWidth(0){}
	TagProcessPara(BYTE  Times, float Speed, float Power,
		UINT  Frequncy, float PulseWidth) :Times(Times), Speed(Speed), Power(Power),
		Frequncy(Frequncy), PulseWidth(PulseWidth){}
} ProcessPara;

// 弧线加工方向
typedef enum TagObjDir { CW = 0, CCW = 1 } ObjDir;

//* 自定义加工对象类型ID *
#define  MachineObj_Type_Invaild		0xffff			//无效对象
#define  MachineObj_Type_Point			100				//点
#define  MachineObj_Type_Line			101				//直线
#define  MachineObj_Type_Circle			102				//圆
#define  MachineObj_Type_Ellipse		103				//椭圆(正椭圆)
#define  MachineObj_Type_Arc			104				//圆弧
#define  MachineObj_Type_ArcEll			105				//椭圆弧(正椭圆弧)
#define  MachineObj_Type_TiltEllipse	106				//斜椭圆及弧
#define  MachineObj_Type_Polyline		120				//多段线
#define  MachineObj_Type_Group			130				//群组

//* 特殊图层 *
#define  LayerName_Border				_T("Border")	//永远位于图层0,该层对象不加工
#define  LayerName_Mark					_T("Mark")		//永远处于图层1,可选加工,对象可为定位模板
#define  LayerName_Group				_T("Mix")		//永远处于图层2,无可用加工信息
#define  LayerName_Reserve1				_T("Resv1")		//保留1
#define  LayerName_Reserve2				_T("Resv2")		//保留2
#define  LayerName_Default				_T("Default")	//缺省图层名为"Default"
#define  LayerNum_Border				0				//外框图层为层0
#define  LayerNum_Mark					1				//Mark图层为层1
#define  LayerNum_Group					2				//Group图层为2,当Group内对象不在同层时
#define  LayerNum_Reserve1				3				//保留1
#define  LayerNum_Reserve2				4				//保留2
#define  LayerNum_Default				5				//缺省图层为层5,加工物件的起始层

//* 图形显示用画笔颜色 *
#define	 PenColor_Sel			RGB(255, 0, 0)		//红画笔-用于显示选中对象
#define	 PenColor_Normal		RGB(0, 0, 0)		//黑画笔-用于显示一般对象
#define	 PenColor_Mark			RGB(0, 255, 0)		//绿画笔-用于显示Mark层对象
#define  PenColor_Border		RGB(0, 206, 209)	//暗绿宝石画笔-用于显示外框对象
#define  PenColor_Start			RGB(255, 0, 255)	//洋红画笔-用于显示指向对象终点的箭头
#define  PenColor_Point			RGB(0, 0, 255)		//蓝色画笔-仅用于显示点对象
#define  PenColor_Coord			RGB(128, 128, 0)		//橙色画笔-用于显示坐标轴
#define  PenColor_Grid			RGB(0, 255, 255)		//蓝绿画笔-用于显示坐标轴

//* 常数 *
#define MultipeObjToLP			1000	//1mm 等于1000逻辑单位
#define OffsetBound				0		//视窗偏移常数
#define DotSize					2		//显示图像中点的大小,实际值会受缩放比例加成
#define ArrowLen				150		//方向显示用箭头长度,实际值会受缩放比例加成
#define ArrowAngle				20		//方向显示用箭头偏角,单位度 
#define DrawArcStep				5		//显示弧时的角度增量 单位度
#define PickBoxSize				3		//拾取框宽 2*PickBosSize 高 2*PickBosSize

#define filesheadflag	0x763ef045
#define fileshead1		".wls////////"
#define fileshead2		"LaserMachineList"
#define fileshead3		"ver 1.0.0.1 by C"
#define fileshead4		"Reserves########"

#define filesendflag	0x01300406c5e87632

#define Zero			0.000000001
