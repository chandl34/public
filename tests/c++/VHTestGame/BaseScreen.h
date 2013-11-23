#ifndef BASE_SCREEN_C34_H_
#define BASE_SCREEN_C34_H_

#include "Colorable.h"
#include "Drawable.h"

#include "Rectangle_c34.h"


class BaseScreen
: public Colorable
, public Drawable
{
public:
	BaseScreen(const Rectangle_c34<int>&,
				  const Color_c34&,
				  int = 0);
	virtual ~BaseScreen();

	// Draw
	void draw(HDC);

protected:
	Rectangle_c34<int> _rect;
};

#endif

