#ifndef PEN_C34_H_
#define PEN_C34_H_

#include "Drawable.h"

#include "Color_c34.h"


class Pen_c34 
: public Drawable
{
public:
	Pen_c34(const Color_c34&, int = 0);
	~Pen_c34();

	// General
	int getThickness() const;	

	// Draw
	void draw(HDC);

private:
	HPEN _pen;
	int _thickness;
};

#endif