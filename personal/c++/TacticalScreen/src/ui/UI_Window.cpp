#include "UI_Window.h"

int UI_Window::_width;
int UI_Window::_height;

UI_Window::UI_Window(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	loaded = false;
	Fl::add_timeout(1.0, Timer_CB, (void*)this);       // 24fps timer
	_width = w;
	_height = h;
}

UI_Window::~UI_Window(){}

void UI_Window::init(){
	glClearColor(0.75f, 0.9f, 1.0f, 0.0f);
	glClearDepth(1.0f);		
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);		
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	loaded = true;
}

void UI_Window::Timer_CB(void *userdata){
	UI_Window *glwin = (UI_Window*)userdata;
	glwin->redraw();
	Fl::repeat_timeout(1.0/20.0, Timer_CB, userdata);
}

void UI_Window::draw(){
	if (!valid()) {
		valid(1);
		init();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int UI_Window::width(){return _width;}
int UI_Window::height(){return _height;}
