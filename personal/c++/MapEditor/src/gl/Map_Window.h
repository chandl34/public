#ifndef GL_WINDOW_H_
#define GL_WINDOW_H_

#include <FL/Fl.H>
#include <FL/Gl.H>
#include <FL/Glu.H>
#include <FL/Fl_Gl_Window.H>
#include "Camera.h"
#include "SelectBox.h"
#include "../map/LevelMap.h"

class Map_Window : public Fl_Gl_Window{
public:
	Map_Window(int, int, int, int);
	virtual ~Map_Window();

	static LevelMap& getMap();
	static LevelMap& getNewMap();
	
private:
	void init();
	static void Timer_CB(void*);
	void draw();
	void view();
	void drawMap();
	int handle(int e);
	
	Camera* camera;
	SelectBox* select;
	static LevelMap* levelMap;
};

#endif /*GL_WINDOW_H_*/
