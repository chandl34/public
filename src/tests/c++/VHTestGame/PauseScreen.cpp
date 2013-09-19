#include "PauseScreen.h"

#include <string>

#include "Game.h"

#include "Const.h"


PauseScreen::PauseScreen(Game* game,
								 const Rectangle_c34<int>& rect, 
								 const Color_c34& color,
								 int thickness)
: BaseScreen(rect, color, thickness)
{
	_game = game;
}

PauseScreen::~PauseScreen()
{

}


// Draw
void PauseScreen::draw(HDC hdcBackBuffer)
{
	BaseScreen::draw(hdcBackBuffer);
	
	std::string str;
	char s[256];

	if(_game->getLevel() == 1){
		str = "Welcome to Mathteroids!";
		TextOut(hdcBackBuffer, 215, 260, str.c_str(), str.size());
	}
	else{
		sprintf(s, "%i", _game->getLevel());
		str = "Level ";
		str += s;
		str += " completed!";
		TextOut(hdcBackBuffer, 215, 260, str.c_str(), str.size());
	}

	str = "Press FIRE to continue...";
	TextOut(hdcBackBuffer, 218, 310, str.c_str(), str.size());
}
