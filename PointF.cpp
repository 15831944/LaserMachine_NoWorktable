#include "stdafx.h"
#include "PointF.h"

CPointF::~CPointF(void)
{
}

CPointF::CPointF(const POINT& pt)
{
	x = (FLOAT)(pt.x);
	y = (FLOAT)(pt.y);
}

CPointF::operator POINT () const
{
	POINT ptRet = { Round(x), Round(y) };
	return ptRet;
}