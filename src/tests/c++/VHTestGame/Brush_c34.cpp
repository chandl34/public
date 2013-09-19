#include "Brush_c34.h"

#include "Color_c34.h"

#include "Const.h"


Brush_c34::Brush_c34(const Color_c34& color)
{
	_brush = CreateSolidBrush(RGB(color[R], color[G], color[B]));
}

Brush_c34::~Brush_c34()
{
	DeleteObject(_brush);
}


// Draw
void Brush_c34::draw(HDC hdcBackBuffer)
{
	SelectObject(hdcBackBuffer, _brush);
}
