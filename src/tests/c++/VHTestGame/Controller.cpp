#include "Controller.h"

#include "Const.h"


Controller::Controller()
: _gameScreen(&_game,
				  Rectangle_c34<int>(Coord2d<int>(0, 0),
									      Size2d<int>(GAME_SCREEN_SIZE[X], GAME_SCREEN_SIZE[Y])),
				  Color_c34(225, 225, 255),
				  3)
, _pauseScreen(&_game,
					Rectangle_c34<int>(Coord2d<int>((GAME_SCREEN_SIZE[X] - PAUSE_SCREEN_SIZE[X]) / 2, 
															  (GAME_SCREEN_SIZE[Y] - PAUSE_SCREEN_SIZE[Y]) / 2),
											 Size2d<int>(PAUSE_SCREEN_SIZE[X], PAUSE_SCREEN_SIZE[Y])),
					Color_c34(200, 200, 200),
					3)
, _statScreen(&_game,
				  Rectangle_c34<int>(Coord2d<int>(GAME_SCREEN_SIZE[X], 0),
									      Size2d<int>(STAT_SCREEN_SIZE[X], STAT_SCREEN_SIZE[Y])),
				  Color_c34(200, 200, 200),
				  3)
{
	srand(0);
}


Controller::~Controller()
{

}



// Input
void Controller::input(int in)
{
	_game.input(in);
}


// Draw
void Controller::draw(HDC hdcBackBuffer)
{
	if(!_game.isLocked())
		_game.update();	

	_gameScreen.draw(hdcBackBuffer);
	_statScreen.draw(hdcBackBuffer);

	if(_game.isLocked())
		_pauseScreen.draw(hdcBackBuffer);
}