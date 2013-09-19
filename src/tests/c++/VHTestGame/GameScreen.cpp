#include "GameScreen.h"

#include "Game.h"
#include "GameObject.h"

#include "Const.h"


GameScreen::GameScreen(Game* game,
							  const Rectangle_c34<int>& rect, 
							  const Color_c34& color,
							  int thickness)
: BaseScreen(rect, color, thickness)
{
	_game = game;
}

GameScreen::~GameScreen()
{

}


// Draw
void GameScreen::draw(HDC hdcBackBuffer)
{
	BaseScreen::draw(hdcBackBuffer);

	_game->drawObjects(hdcBackBuffer);
}
