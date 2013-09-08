#include "Digitroid.h"

#include "Math_c34.h"


Digitroid::Digitroid(int level)
: Asteroid(level, Color_c34(225, 225, 255), 1)
{
	// Class specific
	_type = DIGITROID;
	
	_value = 1 + random(9);
	
	char s[16];
	sprintf(s, "%i", _value);
	_str = s;

	// Adding shape's points
	_point.push_back(Coord2d<float>(10.0f, 0.0f));
	_point.push_back(Coord2d<float>(28.0f, 3.0f));
	_point.push_back(Coord2d<float>(30.0f, 27.0f));
	_point.push_back(Coord2d<float>(8.0f, 30.0f));
	_point.push_back(Coord2d<float>(0.0f, 16.0f));

	// Setting hitbox
	_rect.setSize(30, 30);
	for(int i = 0; i < 2; ++i)
		_center[i] =  _rect.getCoord(i) + _rect.getSize(i) / 2.0f;
}


Digitroid::~Digitroid()
{

}
