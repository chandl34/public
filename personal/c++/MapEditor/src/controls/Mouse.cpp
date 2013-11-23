#include "Mouse.h"

int Mouse::prevX = 0, Mouse::prevY = 0;

#ifdef SCROLLING
void Mouse::enter(int x, int y){
	if(x > 0 && x < WIDTH)
		Camera::setScroll(X, Camera::NO_SCROLL);
	if(y > 0 && y < HEIGHT)
		Camera::setScroll(Y, Camera::NO_SCROLL);
}

void Mouse::leave(int x, int y){
	if(x < 50)
		Camera::setScroll(X, Camera::SCROLL_LEFT);
	else if(x > WIDTH - 50)
		Camera::setScroll(X, Camera::SCROLL_RIGHT);
	if(y < 50)
		Camera::setScroll(Y, Camera::SCROLL_UP);
	else if(y > HEIGHT - 50)
		Camera::setScroll(Y, Camera::SCROLL_DOWN);		
}
#endif //SCROLLING

void Mouse::push(int button, int x, int y){
	prevX = x;
	prevY = y;
}

void Mouse::release(int button, int x, int y){
	// To be used for selection later
}

void Mouse::drag(int button, int x, int y){
#ifdef PANNING
	if(button == LMB){ 
		Camera::setPan(X, Camera::getPan(X) - (prevX - x));
		Camera::setPan(Y, Camera::getPan(Y) + (prevY - y));
	}
#endif //PANNING
	
#ifdef ROTATING 
	else if(button == RMB){
		float rot = Camera::getAngle(X);
		rot -= 360.0f * ((float)(prevY - y) / (float)HEIGHT);
		if(rot < 0)
			rot += 360.0f;
		else if(rot > 360.0f)
			rot -= 360.0f;
		Camera::setRotate(X, rot);

		rot = Camera::getAngle(Y);
		rot += 360.0f * ((float)(x - prevX) / (float)WIDTH);
		if(rot < 0)
			rot += 360.0f;
		else if(rot > 360.0f)
			rot -= 360.0f;
		Camera::setRotate(Y, rot);			
	}
#endif //ROTATING
	prevX = x;
	prevY = y;	
}

void Mouse::mouseWheel(int direction, int x, int y){
#ifdef ZOOMING	
	Camera::setPan(Z, Camera::getPan(Z) - direction);
#endif //ZOOMING
}
