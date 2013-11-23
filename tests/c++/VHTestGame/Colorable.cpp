#include "Colorable.h"

#include "Color_c34.h"


Colorable::Colorable(const Color_c34& color,	
							int thickness)
{
	_brush = std::shared_ptr<Brush_c34>(new Brush_c34(color));
	if(thickness == 0)
		_pen = std::shared_ptr<Pen_c34>(new Pen_c34(color));
	else
		_pen = std::shared_ptr<Pen_c34>(new Pen_c34(Color_c34(), thickness));
}


Colorable::~Colorable()
{

}


// General
void Colorable::setPen(const Color_c34& color, int thickness)
{
	_pen = std::shared_ptr<Pen_c34>(new Pen_c34(color, thickness));
}


// Draw
void Colorable::setupTools(HDC hdcBackBuffer)
{
	_brush->draw(hdcBackBuffer);
	_pen->draw(hdcBackBuffer);
}
