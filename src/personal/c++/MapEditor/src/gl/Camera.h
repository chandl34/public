#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Include.h"

class Camera{
public:
	Camera();
	virtual ~Camera();
	
	static float getPan(int i){return pan[i];}
	static float getRotate(int i){return rotation[i];}
	static bool isOrthogonal(){return orthogonal;}
	
	static void setPan(int i, float f){pan[i] = f;}
	static void setRotate(int i, float f){rotation[i] = f;}	
	static void setOrthogonal(bool orth){orthogonal = orth;}
	static void setScroll(int coord, int s){scr[coord] = s;}
	static void aerialToggle();	
	static void resetView();	
	void scroll();
	
	enum{NO_SCROLL, SCROLL_LEFT, SCROLL_RIGHT};
	enum{SCROLL_UP = 1, SCROLL_DOWN};
	
private:
	static float* pan;
	static float* rotation;
	static bool orthogonal;
	static int* scr;
	
};

#endif /*CAMERA_H_*/
