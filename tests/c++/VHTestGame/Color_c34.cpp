#include "Color_c34.h"

#include "Const.h"


Color_c34::Color_c34(int r, int g, int b)
{
	_val[R] = r;
	_val[G] = g;
	_val[B] = b;
}



int& Color_c34::operator[](size_t c)
{
	return _val[c];
}

const int& Color_c34::operator[](size_t c) const
{
	return _val[c];
}
