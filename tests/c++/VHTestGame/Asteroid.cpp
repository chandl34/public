#include "Asteroid.h"

#include "Math_c34.h"


Asteroid::Asteroid(int level,
						 const Color_c34& color,	
						 int thickness)
: GameObject(color, thickness)
{
	// Setting random location
	_rect.setCoord(random(GAME_SCREEN_SIZE[X]), 
						random(GAME_SCREEN_SIZE[Y]));

	// Random movement speed
	_moveSpeed = random(6) / 10.0f + 0.5f * level;
	if(random(1) == 0)
		_moveSpeed *= -1;

	// Random rotation
	rotate(M_PI / 360.0f * (float)random(360));
	_rotSpeed = random(21) / 10.0f - 1.0f;
}

Asteroid::~Asteroid()
{

}


// General
int Asteroid::getType() const
{
	return _type;
}

int Asteroid::getValue() const
{
	return _value;
}

bool Asteroid::isVulnerable(int total) const
{
	return true;
}


// Draw
void Asteroid::draw(HDC hdcBackBuffer)
{
	GameObject::draw(hdcBackBuffer);

	TextOut(hdcBackBuffer, 
			  _center[X] - _str.size() * 2.5f, 
			  _center[Y] - 5, 
			  _str.c_str(), 
			  _str.size());
}
