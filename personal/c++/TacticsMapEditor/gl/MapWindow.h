#ifndef MAPWINDOW_H_
#define MAPWINDOW_H_

#include "Camera.h"
#include "../map/Map.h"

class MapWindow : public Fl_Gl_Window{
public:
	MapWindow(int, int, int, int);
	virtual ~MapWindow();
	
private:	
	void init();
	static void Timer_CB(void*);
	void view();
	void draw();
	int handle(int e);	
	
	Camera* camera;
	Map* map;
};

#endif /*MAPWINDOW_H_*/
