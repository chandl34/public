#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

#include "controls/Keyboard.h"
#include "controls/Mouse.h"
#include "../world/World.h"

class Game_Window : public Fl_Gl_Window{
public:
	Game_Window(int, int, int, int);
	virtual ~Game_Window();
		
	static void view();
	static void drawMap();
	static void drawDoors();
	static void drawCharacters();
	
	static int width();
	static int height();
	
private:
	void init();
	static void Timer_CB(void*);
	void draw();
	int handle(int e);
	
	static Camera* camera;
	static Cursor* cursor;
	static World* world;
	static int _width, _height;
	bool loaded;
};


#endif /*GAME_WINDOW_H_*/
