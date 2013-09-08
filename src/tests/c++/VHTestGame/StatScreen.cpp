#include "StatScreen.h"

#include <string>

#include "Game.h"

#include "Const.h"


StatScreen::StatScreen(Game* game,
							  const Rectangle_c34<int>& rect, 
							  const Color_c34& color,
							  int thickness)
: BaseScreen(rect, color, thickness)
{
	_game = game;
}

StatScreen::~StatScreen()
{

}


// Draw
void StatScreen::draw(HDC hdcBackBuffer)
{
	BaseScreen::draw(hdcBackBuffer);
	
	std::string str;
	char s[256];

	// Level
	sprintf(s, "%i", _game->getLevel());
	str = "Level: ";
	str += s;
	TextOut(hdcBackBuffer, 675, 175, str.c_str(), str.size());

	// Score
	sprintf(s, "%i", _game->getScore());
	str = "Score: ";
	str += s;	
	TextOut(hdcBackBuffer, 675, 225, str.c_str(), str.size());
	
	// Total
	sprintf(s, "%i", _game->getTotal());
	str = "Current Total: ";
	str += s;	
	TextOut(hdcBackBuffer, 650, 275, str.c_str(), str.size());
	
	// Lives
	sprintf(s, "%i", _game->getLives());
	str = "Ships Left: ";
	str += s;	
	TextOut(hdcBackBuffer, 660, 325, str.c_str(), str.size());
}
