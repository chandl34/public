#ifndef MOUSE_H_
#define MOUSE_H_

#include "../Include.h"
#include "../gl/Camera.h"

class Mouse{
public:
	Mouse(){}
	virtual ~Mouse(){}

#ifdef SCROLLING
	static void enter(int, int);
	static void leave(int, int);
#endif //SCROLLING
	
	static void push(int, int, int);
	static void release(int, int, int);
	static void drag(int, int, int);
	static void mouseWheel(int, int, int);
	
private:
	enum{LMB = 1, MMB, RMB};
	static int prevX, prevY;
	
};

#endif /*MOUSE_H_*/
