#ifndef KEYBOARD_H_
#define KEYBOARD_H_

class Keyboard{
public:
	Keyboard(){}
	virtual ~Keyboard(){}
	
	static void keyDown(int, int, int);
	static void keyUp(int, int, int);
	
};

#endif /*KEYBOARD_H_*/
