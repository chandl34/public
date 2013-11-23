#ifndef CAMERA_H_
#define CAMERA_H_

#include "../Include.h"

class Camera{
public:
	Camera();
	virtual ~Camera();
	
	static int getShift(int i){return shift[i];}
	static float getPan(int i){return pan[i];}
	static float getRotate(int i){return rotation[i];}
	static bool isOrthogonal(){return orthogonal;}
	static int getScroll(int i){return scr[i];}	
	
	static void setShift(int i, int v){shift[i] = v;}
	static void setPan(int i, float f){pan[i] = f;}
	static void setRotate(int i, float f){rotation[i] = f;}	
	static void setOrthogonal(bool orth){orthogonal = orth;}
	static void setScroll(int coord, int s){scr[coord] = s;}
	static void aerialToggle();	
	static void resetView();	
	static void scroll(int, int);
	static void scroll();
	
	enum{NO_SCROLL, SCROLL_LEFT, SCROLL_RIGHT};
	enum{SCROLL_UP = 1, SCROLL_DOWN};
	
private:
	static float* pan;
	static float* rotation;
	static bool orthogonal;
	static int* scr;
	static int* shift;
	static int* shiftCap;
	static float* incr;		
};

#endif /*CAMERA_H_*/
