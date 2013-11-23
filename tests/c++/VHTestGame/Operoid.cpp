#include "Operoid.h"

#include "Math_c34.h"


Operoid::Operoid(int level)
: Asteroid(level, Color_c34(225, 225, 255), 1)
{
	// Class specific
	_type = OPEROID;
	
	int r = random(4);
	if(r == 0)
		_value = '+';
	else if(r == 1)
		_value = '-';
	else if(r == 2)
		_value = 'x';
	else
		_value = '/';

	char s[16];
	sprintf(s, "%c", _value);
	_str = s;
	
	// Adding shape's points
	_point.push_back(Coord2d<float>(8.0f, 2.0f));
	_point.push_back(Coord2d<float>(18.0f, 3.0f));
	_point.push_back(Coord2d<float>(25.0f, 1.0f));
	_point.push_back(Coord2d<float>(30.0f, 25.0f));
	_point.push_back(Coord2d<float>(8.0f, 30.0f));
	_point.push_back(Coord2d<float>(0.0f, 18.0f));

	// Setting hitbox
	_rect.setSize(30, 30);
	for(int i = 0; i < 2; ++i)
		_center[i] =  _rect.getCoord(i) + _rect.getSize(i) / 2.0f;
}


Operoid::~Operoid()
{

}
