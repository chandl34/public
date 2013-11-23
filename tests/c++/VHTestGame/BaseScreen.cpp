#include "BaseScreen.h"


BaseScreen::BaseScreen(const Rectangle_c34<int>& rect,
							  const Color_c34& color,
							  int thickness)
: Colorable(color, thickness)
, _rect(rect)
{

}


BaseScreen::~BaseScreen()
{

}


// Draw
void BaseScreen::draw(HDC hdcBackBuffer)
{
	// Draw background
	setupTools(hdcBackBuffer);
	_rect.draw(hdcBackBuffer);

}
