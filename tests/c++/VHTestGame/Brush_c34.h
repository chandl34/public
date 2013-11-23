#ifndef BRUSH_C34_H_
#define BRUSH_C34_H_

#include "Drawable.h"

#include "Color_c34.h"


class Brush_c34 
: public Drawable
{
public:
	Brush_c34(const Color_c34&);
	~Brush_c34();

	// Draw
	void draw(HDC);

private:
	HBRUSH _brush;
};

#endif