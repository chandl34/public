#ifndef PAUSE_SCREEN_C34_H_
#define PAUSE_SCREEN_C34_H_

#include "BaseScreen.h"

class Game;

class PauseScreen
: public BaseScreen
{
public:
	PauseScreen(Game*, 
					const Rectangle_c34<int>&,
					const Color_c34&,
					int = 0);
	~PauseScreen();

	// Draw
	void draw(HDC);

private:
	Game* _game;
};

#endif
