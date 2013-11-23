#ifndef DRAWABLE_C34_H_
#define DRAWABLE_C34_H_

#include <windows.h>  


class Drawable
{
public:
	// Draw
	virtual void draw(HDC) = 0;
};

#endif