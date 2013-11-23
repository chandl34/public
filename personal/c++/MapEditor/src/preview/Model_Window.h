#ifndef MODEL_WINDOW_H_
#define MODEL_WINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Gl.H>
#include "../gl/Camera.h"
#include "../containers/MapModelContainer.h"

class Model_Window : public Fl_Gl_Window{
public:
	Model_Window(int, int, int, int, int);
	virtual ~Model_Window(){}
	void loadModel();
	
private:
	static void Timer_CB(void*);
	void init();
	void draw();
	int handle(int);
		
	int type;
	int box, model;
	
};

#endif /*MODEL_WINDOW_H_*/
