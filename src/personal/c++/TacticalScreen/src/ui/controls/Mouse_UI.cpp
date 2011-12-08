#include "Mouse_UI.h"
#include "../UI_Window.h"
#include "../../gl/Camera.h"

#ifdef SCROLLING
void Mouse_UI::move(int x, int y){
	if(x < 20)
		Camera::setScroll(X, Camera::SCROLL_LEFT);
	else if(x > UI_Window::width() - 20)
		Camera::setScroll(X, Camera::SCROLL_RIGHT);
	else 
		Camera::setScroll(X, Camera::NO_SCROLL);

	if(y > UI_Window::height() - 20)
		Camera::setScroll(Y, Camera::SCROLL_DOWN);
	else 
		Camera::setScroll(Y, Camera::NO_SCROLL);

	if(Camera::getScroll(X) != Camera::NO_SCROLL || 
			Camera::getScroll(Y) != Camera::NO_SCROLL)
		return;	
}

void Mouse_UI::leave(int x, int y){
	Camera::setScroll(X, Camera::NO_SCROLL);
	Camera::setScroll(Y, Camera::NO_SCROLL);
}
#endif	
