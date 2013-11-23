#include "Mathteroid.h"

#include "Math_c34.h"


Mathteroid::Mathteroid(int level)
: Asteroid(level, Color_c34(225, 225, 255), 1)
{
	// Class specific
	_type = MATHTEROID;
	
	_value = -50 * level + random(100 * level + 1);
	
	char s[16];
	sprintf(s, "%i", _value);
	_str = s;

	// Adding shape's points
	_point.push_back(Coord2d<float>(0.0f, 2.0f));		
	_point.push_back(Coord2d<float>(22.0f, 0.0f));
	_point.push_back(Coord2d<float>(48.0f, 1.0f));
	_point.push_back(Coord2d<float>(60.0f, 5.0f));		
	_point.push_back(Coord2d<float>(55.0f, 11.0f));
	_point.push_back(Coord2d<float>(60.0f, 42.0f));
	_point.push_back(Coord2d<float>(57.0f, 60.0f));		
	_point.push_back(Coord2d<float>(33.0f, 58.0f));
	_point.push_back(Coord2d<float>(12.0f, 42.0f));
	_point.push_back(Coord2d<float>(8.0f, 40.0f));
	_point.push_back(Coord2d<float>(6.0f, 15.0f));

	// Setting hitbox
	_rect.setSize(60, 60);
	for(int i = 0; i < 2; ++i)
		_center[i] =  _rect.getCoord(i) + _rect.getSize(i) / 2.0f;
}


Mathteroid::~Mathteroid()
{

}

	
// General
bool Mathteroid::isVulnerable(int total) const
{
	return total == _value;
}
