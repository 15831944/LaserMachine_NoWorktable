// MachineObjDef.h
// ����,�������ͼ�����
//
//* �������� *
// ���
#pragma once
typedef struct TagObjRect
{
	double    min_x;
	double    max_x;
	double    min_y;
	double    max_y;
	TagObjRect() :min_x(0), max_x(0), min_y(0), max_y(0){}
} ObjRect;

// ��
typedef struct TagObjPoint
{
	double   x;
	double   y;
	TagObjPoint() :x(0), y(0){}
	TagObjPoint(double x, double y) :x(x), y(y){}
} ObjPoint;

// ����
typedef struct TagObjVPoint
{
	double   x;
	double   y;
	double convexity;
	TagObjVPoint() :x(0), y(0), convexity(1){}
	TagObjVPoint(double x, double y, int cv) :x(x), y(y), convexity(cv){}
} ObjVPoint;

// �ӹ�����
typedef struct TagProcessPara
{
	UINT  Times;		//�ӹ�����
	float Speed;		//�ӹ��ٶ� ��λmm/s
	float Power;		//���⹦�� 0-100%
	UINT  Frequncy;		//Ƶ�� ��λHz
	float PulseWidth;	//���� ��λus
	float LaserOnDelay;		//������ʱ
	float LaserOffDelay;	//�ع���ʱ
	float BeforMarkDelay;	//���ǰ��ʱ
	float AfterMarkDelay;	//��Ǻ���ʱ
	float PolylineDelay;	//�ս���ʱ
	TagProcessPara() :Times(0), Speed(0), Power(0), Frequncy(0), PulseWidth(0),
		LaserOnDelay(0), LaserOffDelay(0), BeforMarkDelay(0), AfterMarkDelay(0),
		PolylineDelay(0){}
	TagProcessPara(UINT  Times, float Speed, float Power, UINT  Frequncy,
		float PulseWidth, float LaserOnDelay, float LaserOffDelay,
		float BeforMarkDelay, float AfterMarkDelay, float PolylineDelay) :Times(Times),
		Speed(Speed), Power(Power), Frequncy(Frequncy), PulseWidth(PulseWidth),
		LaserOnDelay(LaserOnDelay), LaserOffDelay(LaserOffDelay), BeforMarkDelay(BeforMarkDelay),
		AfterMarkDelay(AfterMarkDelay), PolylineDelay(PolylineDelay){}
} ProcessPara;

#define InvalidLength	0.00001
#define RectIsNull(Rect)\
	(abs(Rect.max_x - Rect.min_x) < InvalidLength)\
	&& (abs(Rect.max_y - Rect.min_y) < InvalidLength)

#define Para_Equal(Para1,Para2)\
	Para1.Times == Para2.Times \
	&& Para1.Speed == Para2.Speed \
	&& Para1.Power == Para2.Power \
	&& Para1.Frequncy == Para2.Frequncy \
	&& Para1.PulseWidth == Para2.PulseWidth \
	&& Para1.LaserOnDelay == Para2.LaserOnDelay \
	&& Para1.LaserOffDelay == Para2.LaserOffDelay \
	&& Para1.BeforMarkDelay == Para2.BeforMarkDelay \
	&& Para1.AfterMarkDelay == Para2.AfterMarkDelay \
	&& Para1.PolylineDelay == Para2.PolylineDelay 






// ���߼ӹ�����
typedef enum TagObjDir { CW = 0, CCW = 1 } ObjDir;

// ����״̬
#define	IsObjNormal		0	//����
#define IsObjSel		1	//ѡ��
#define IsObjChange		2	//�Ѿ��ı�
#define	IsObjLocked		4	//����
#define IsObjClosed		8	//�ر�

//* �Զ���ӹ���������ID *
#define  MachineObj_Type_Invaild		0xffff			//��Ч����
#define  MachineObj_Type_Point			100				//��
#define  MachineObj_Type_Line			101				//ֱ��
#define  MachineObj_Type_Circle			102				//Բ
#define  MachineObj_Type_Ellipse		103				//��Բ(����Բ)
#define  MachineObj_Type_Arc			104				//Բ��
#define  MachineObj_Type_ArcEll			105				//��Բ��(����Բ��)
#define  MachineObj_Type_TiltEllipse	106				//б��Բ����
#define  MachineObj_Type_Polyline		120				//�����
#define  MachineObj_Type_Group			130				//Ⱥ��
#define  MachineObj_Type_WLine			140				//չ��ֱ��
#define  MachineObj_Type_WArc			141				//չ��Բ��
#define  MachineObj_Type_WPolyline		150				//չ������
#define  MachineObj_Type_FillPolyline	170				//����ն��������



//* ����ͼ�� *
#define  LayerName_Border				_T("Border")	//��Զλ��ͼ��0,�ò���󲻼ӹ�
#define  LayerName_Mark					_T("Mark")		//��Զ����ͼ��1,��ѡ�ӹ�,�����Ϊ��λģ��
#define  LayerName_Group				_T("Mix")		//��Զ����ͼ��2,�޿��üӹ���Ϣ
#define  LayerName_Reserve1				_T("Resv1")		//����1
#define  LayerName_Reserve2				_T("Resv2")		//����2
#define  LayerName_Default				_T("Default")	//ȱʡͼ����Ϊ"Default"
#define  LayerNum_Border				0				//���ͼ��Ϊ��0
#define  LayerNum_Mark					1				//Markͼ��Ϊ��1
#define  LayerNum_Group					2				//Groupͼ��Ϊ2,��Group�ڶ�����ͬ��ʱ
#define  LayerNum_Reserve1				3				//����1
#define  LayerNum_Reserve2				4				//����2
#define  LayerNum_Default				5				//ȱʡͼ��Ϊ��5,�ӹ��������ʼ��


//* ͼ����ʾ�û�����ɫ *
#define	 PenColor_Sel			RGB(255, 0, 0)		//�컭��-������ʾѡ�ж���
#define	 PenColor_Normal		RGB(0, 0, 0)		//�ڻ���-������ʾһ�����
#define	 PenColor_Mark			RGB(0, 255, 0)		//�̻���-������ʾMark�����
#define  PenColor_Border		RGB(0, 206, 209)	//���̱�ʯ����-������ʾ������
#define  PenColor_Start			RGB(255, 0, 255)	//��컭��-������ʾָ������յ�ļ�ͷ
#define  PenColor_Point			RGB(0, 0, 255)		//��ɫ����-��������ʾ�����
#define  PenColor_Coord			RGB(128, 128, 0)		//��ɫ����-������ʾ������
#define  PenColor_Grid			RGB(0, 255, 255)		//���̻���-������ʾ������


//* ���� *
#define MultipeObjToLP			1000	//1mm ����1000�߼���λ
#define OffsetBound				0		//�Ӵ�ƫ�Ƴ���
#define DotSize					2		//��ʾͼ���е�Ĵ�С,ʵ��ֵ�������ű����ӳ�
#define ArrowLen				80		//������ʾ�ü�ͷ����,ʵ��ֵ�������ű����ӳ�
#define ArrowAngle				20		//������ʾ�ü�ͷƫ��,��λ�� 
#define DrawArcStep				5		//��ʾ��ʱ�ĽǶ����� ��λ��
#define PickBoxSize				3		//ʰȡ��� 2*PickBosSize �� 2*PickBosSize

#define filesheadflag	0x763ef045
#define fileshead1		".wls////////"
#define fileshead2		"LaserMachineList"
#define fileshead3		"ver 1.0.0.1 by C"
#define fileshead4		"Reserves########"

#define filesendflag	0x01300406c5e87632

#define Zero			0.000000001

//* ���� *


