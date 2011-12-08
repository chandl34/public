#ifndef UI_WINDOW_H_
#define UI_WINDOW_H_

#include "../Include.h"

class UI_Window : public Fl_Gl_Window{
public:
	UI_Window(int, int, int, int);
	virtual ~UI_Window();
	
	static int width();
	static int height();
	
private:
	void init();
	static void Timer_CB(void*);
	void draw();
	int handle(int e);
	
	bool loaded;
	static int _width, _height;
};


#endif /*UI_WINDOW_H_*/
