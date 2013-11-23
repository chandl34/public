#ifndef CONTROLLER_C34_H_
#define CONTROLLER_C34_H_

#include "Drawable.h" 

#include "Game.h"
#include "GameScreen.h"
#include "PauseScreen.h"
#include "StatScreen.h"


class Controller
: public Drawable
{
public:
	Controller();
	~Controller();
	
	// Input
	void input(int);

	// Draw
	void draw(HDC);

private:
	Game _game;

	GameScreen _gameScreen;
	PauseScreen _pauseScreen;
	StatScreen _statScreen;
};

#endif


