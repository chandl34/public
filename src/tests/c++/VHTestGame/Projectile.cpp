#include "Projectile.h"


Projectile::Projectile(const Coord2d<float>& orig, 
							  const Coord2d<float>& vect)
: GameObject(Color_c34(225, 225, 255), 1)
{
	// Setting random location
	_rect.setCoord(orig[X], orig[Y]);

	// Adding shape's points
	_point.push_back(Coord2d<float>(0.0f, 0.0f));
	_point.push_back(Coord2d<float>(2.0f, 0.0f));
	_point.push_back(Coord2d<float>(2.0f, 2.0f));
	_point.push_back(Coord2d<float>(0.0f, 2.0f));

	// Setting hitbox
	_rect.setSize(2, 2);
	for(int i = 0; i < 2; ++i)
		_center[i] =  _rect.getCoord(i) + _rect.getSize(i) / 2.0f;
	
	// Set vector
	_vect = vect;
	_moveSpeed = 3.0f; 

	// Pen
	setPen(Color_c34(0, 0, 0), 1);
}
	

// Draw
bool Projectile::update()
{
	// Update location
	_rect.setCoord(_rect.getCoord(X) + _vect[X] * _moveSpeed, 
						_rect.getCoord(Y) + _vect[Y] * _moveSpeed);

	for(int i = 0; i < 2; ++i)
		_center[i] = _rect.getCoord(i) + _rect.getSize(i) / 2.0f;

	for(int i = 0; i < 2; ++i){
		if(_center[i] < 0 || _center[i] >= GAME_SCREEN_SIZE[i])
			return false;
	}
	
	return true;
}
