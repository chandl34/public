#include "GameObject.h"

#include "Math_c34.h"


GameObject::GameObject(const Color_c34& color,	
							  int thickness)
: Colorable(color, thickness)
{
	_vect = Coord2d<float>(1, 0);
	_moveSpeed = 0;

	_rotSpeed = 0;
	_rotIncr = 0;
	
	_canCollide = false;
	_startTime = GetTickCount();
	setPen(Color_c34(180, 180, 180), 1);
}

GameObject::~GameObject()
{
	//OutputDebugString("Destroyed object\n");
}


// General
const Coord2d<float>& GameObject::getCenter() const
{
	return _center;
}

const Coord2d<float>& GameObject::getVector() const
{
	return _vect;
}

bool GameObject::canCollide() const
{
	return _canCollide;
}

bool GameObject::detectHit(const GameObject& ot) const
{
	return rectInRect(_rect, ot._rect);
}

void GameObject::rotate(float rAngle)
{
	_vect.rotate(Coord2d<float>(0, 0), rAngle);

	Coord2d<float> orig(_rect.getSize(X) / 2.0f, 
		                 _rect.getSize(Y) / 2.0f);
	for(PointList::iterator iter = _point.begin(); iter != _point.end(); ++iter)
		iter->rotate(orig, rAngle);
}


// Draw
void GameObject::draw(HDC hdcBackBuffer)
{
	if(!_point.empty()){
		setupTools(hdcBackBuffer);	

		PointList::reverse_iterator riter = _point.rbegin();
		
		MoveToEx(hdcBackBuffer, 
					_rect.getCoord(X) + (*riter)[X], 
					_rect.getCoord(Y) + (*riter)[Y], 
					NULL);

		for(PointList::iterator iter = _point.begin(); iter != _point.end(); ++iter){
				LineTo(hdcBackBuffer, 
						 _rect.getCoord(X) + (*iter)[X], 
						 _rect.getCoord(Y) + (*iter)[Y]);
		}
	}
}

bool GameObject::update()
{
	// Check collide cooldown
	if(!_canCollide){
		if(GetTickCount() - _startTime > COLLIDE_DELAY){
			_canCollide = true;
			setPen(Color_c34(0, 0, 0), 1);
		}
	}

	// Update location
	Coord2d<int> coord;
	Coord2d<float> os;
	for(int i = 0; i < 2; ++i){
			os[i] = _rect.getCoord(i) + _vect[i] * _moveSpeed;
			coord[i] = os[i];
			os[i] -= coord[i];

			// Loop around
			coord[i] = (coord[i] + GAME_SCREEN_SIZE[i]) % GAME_SCREEN_SIZE[i];
	}
	_rect.setCoord(coord[X] + os[X], coord[Y] + os[Y]);
	
	for(int i = 0; i < 2; ++i)
		_center[i] = _rect.getCoord(i) + _rect.getSize(i) / 2.0f;

	//  Update rotation
	_rotSpeed = clamp(_rotSpeed + _rotIncr, -1.0f, 1.0f);
	rotate(ROT_MAX * _rotSpeed);	

	return true;
}
