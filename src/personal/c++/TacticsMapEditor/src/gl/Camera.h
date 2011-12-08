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
	
	static void aerialToggle();	
	static void resetView();	
	
private:
	static float* pan;
	static float* rotation;
	static bool orthogonal;
};

#endif /*CAMERA_H_*/
