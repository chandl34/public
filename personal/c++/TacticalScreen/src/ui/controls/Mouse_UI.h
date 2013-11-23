#ifndef MOUSE_UI_H_
#define MOUSE_UI_H_

#include "../../Include.h"

class Mouse_UI{
public:
	Mouse_UI(){}
	virtual ~Mouse_UI(){}

#ifdef SCROLLING
	static void leave(int, int);	
	static void move(int, int);
#endif //SCROLLING
	
private:	
	enum{LMB = 1, MMB, RMB};
};

#endif /*MOUSE_UI_H_*/
