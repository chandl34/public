#ifndef STAT_SCREEN_C34_H_
#define STAT_SCREEN_C34_H_

#include "BaseScreen.h"

class Game;

class StatScreen
: public BaseScreen
{
public:
	StatScreen(Game*, 
				  const Rectangle_c34<int>&,
				  const Color_c34&,
				  int = 0);
	~StatScreen();

	// Draw
	void draw(HDC);

private:
	Game* _game;
};

#endif
