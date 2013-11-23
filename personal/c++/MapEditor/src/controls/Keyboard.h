#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../Include.h"
#include "../gl/Camera.h"
#include "../gl/SelectBox.h"
#include "../map/LevelMap.h"
#include "../preview/Preview_Window.h"

class Keyboard{
public:
	Keyboard(){}
	virtual ~Keyboard(){}
	
	static void keyDown(int, int, int);
	
};

#endif /*KEYBOARD_H_*/
