#pragma once
/*************************************************
Copyright:	mlizhi.com
Author:		Juncheng Lin
Date:		2018-01-05
Description:CPoint��CSize�ĸ������汾
**************************************************/
#include <ocidl.h>

template<typename T>
inline int Round(T f)
{
	return (int)(f < 0 ? f - 0.5f : f + 0.5f);
}
/**
������	CPointF
���ܣ�	�ṩ������������CPoint���Ƶ����������
*/
class CPointF :
	public tagPOINTF
{
public:
	CPointF(FLOAT _x = 0, FLOAT _y = 0)
	{
		x = _x;
		y = _y;
	}
	CPointF(const POINTF& pt)
	{
		x = pt.x;
		y = pt.y;
	}
	CPointF(const POINT& pt);
	~CPointF(void);
	operator POINT () const;
	//��Ŀ������ĺ꣬����oprΪ������
#define OPERATE_RIGHT_DEF(opr) const CPointF & operator opr (const CPointF &pt) { \
		x opr pt.x; \
		y opr pt.y; \
		return *this; \
	}
//˫Ŀ������ĺ꣬oprpΪҪʵ�ֵ������������oprΪ�õ��ĵ�Ŀ������
#define OPERATE_PAIR_DEF(oprp, opr)  inline CPointF operator oprp (const CPointF &_1st, const CPointF &_2nd) { \
		CPointF ptRet(_1st); \
		ptRet opr _2nd; \
		return ptRet; \
	}
	OPERATE_RIGHT_DEF(+= );
	OPERATE_RIGHT_DEF(-= );
	OPERATE_RIGHT_DEF(*= );
	OPERATE_RIGHT_DEF(/= );

	bool operator == (const CPointF& other) const
	{
		return x == other.x && y == other.y;
	}
	bool operator != (const CPointF& other) const
	{
		return !(*this == (other));
	}
};

/**
������	CSizeF
���ܣ�	�ṩ������������CSize���Ƶ����������
*/
class CSizeF :
	public CPointF
{
public:
	CSizeF(FLOAT _x = 0, FLOAT _y = 0) : CPointF(_x, _y), cx(x), cy(y) {}
	CSizeF(const POINTF& pt) : CPointF(pt), cx(x), cy(y) {}
	CSizeF(const SIZE& size) : CPointF((FLOAT)size.cx, (FLOAT)size.cy), cx(x), cy(y) {};
	CSizeF(const CPointF& pt) : CPointF(pt), cx(x), cy(y) {};
	CSizeF(const CSizeF& size) : CPointF((const CPointF&)size), cx(x), cy(y) {}
	const CSizeF& operator = (const CPointF& pt)
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}
	FLOAT& cx;
	FLOAT& cy;
};
OPERATE_PAIR_DEF(+, +=);
OPERATE_PAIR_DEF(-, -=);
OPERATE_PAIR_DEF(*, *=);
OPERATE_PAIR_DEF(/ , /=);