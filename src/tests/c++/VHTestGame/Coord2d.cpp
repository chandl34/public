#include "Point2d.h"

#include "Const.h"


Point2d::Point2d(float x, float y)
{
	_val[X] = x;
	_val[Y] = y;
}

	
float& Point2d::operator[](size_t c)
{
	return _val[c];
}

const float& Point2d::operator[](size_t c) const
{
	return _val[c];
}

