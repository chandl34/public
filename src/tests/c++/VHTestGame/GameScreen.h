#ifndef GAME_SCREEN_C34_H_
#define GAME_SCREEN_C34_H_

#include "BaseScreen.h"

class Game;

class GameScreen
: public BaseScreen
{
public:
	GameScreen(Game*, 
				  const Rectangle_c34<int>&,
				  const Color_c34&,
				  int = 0);
	~GameScreen();

	// Draw
	void draw(HDC);

private:
	Game* _game;
};

#endif
