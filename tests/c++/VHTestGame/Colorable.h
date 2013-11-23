#ifndef COLORABLE_C34_H_
#define COLORABLE_C34_H_

#include <memory>

#include "Brush_c34.h"
#include "Pen_c34.h"

class Color_c34;


class Colorable
{
public:
	Colorable(const Color_c34& = Color_c34(),	
				 int = 0);
	virtual ~Colorable();
	
	// General
	void setPen(const Color_c34&, int);

	// Draw
	void setupTools(HDC);

protected:
	std::shared_ptr<Brush_c34> _brush;
	std::shared_ptr<Pen_c34> _pen;
};

#endif


