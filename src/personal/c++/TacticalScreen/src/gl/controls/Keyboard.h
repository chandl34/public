#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "../Camera.h"
#include "../Cursor.h"

class Keyboard{
public:
	Keyboard(){}
	virtual ~Keyboard(){}
	
	static void keyDown(int, int, int);
	static void keyUp(int, int, int);
	
private:
	static int downKey;
};

#endif /*KEYBOARD_H_*/
