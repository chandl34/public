#include "Pen_c34.h"

#include "Color_c34.h"

#include "Const.h"


Pen_c34::Pen_c34(const Color_c34& color, int thickness)
{
	_pen = CreatePen(PS_SOLID, thickness, RGB(color[R], color[G], color[B]));
	_thickness = thickness;
}

Pen_c34::~Pen_c34()
{
	DeleteObject(_pen);
}


// General
int Pen_c34::getThickness() const
{
	return _thickness;
}


// Draw
void Pen_c34::draw(HDC hdcBackBuffer)
{
	SelectObject(hdcBackBuffer, _pen);
}

