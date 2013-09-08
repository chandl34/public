#include "Ship.h"

#include "Const.h"
#include "Math_c34.h"


Ship::Ship()
: GameObject(Color_c34(), 1)
{
	// Setting default location
	_rect.setCoord(GAME_SCREEN_SIZE[X] / 2,
						GAME_SCREEN_SIZE[Y] - 50);

	// Adding shape's points
	_point.push_back(Coord2d<float>(15.0f, 6.0f));
	_point.push_back(Coord2d<float>(0.0f, 0.0f));
	_point.push_back(Coord2d<float>(4.0f, 6.0f));
	_point.push_back(Coord2d<float>(0.0f, 12.0f));

	// Setting hitbox
	_rect.setSize(15, 15);
	for(int i = 0; i < 2; ++i)
		_center[i] =  _rect.getCoord(i) + _rect.getSize(i) / 2.0f;

	// Rotate
	rotate(-M_PI_2);
}


// Draw
void Ship::input(int in)
{
	switch(in){
	case DOWN:
		if(compare(_moveSpeed, -1) == 1)
			_moveSpeed -= 0.1f;
		break;

	case UP:
		if(compare(_moveSpeed, 1) == -1)
			_moveSpeed += 0.1f;
		break;

	case CCW_ROT:
		_rotIncr = -0.1f;
		break;

	case CC_ROT:
		_rotIncr = 0.1f;
		break;
		
	case STOP_ROT:
		_rotSpeed = 0;
		_rotIncr = 0;
		break;
	};
}
