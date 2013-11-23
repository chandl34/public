#ifndef COORD_2D_C34_H_
#define COORD_2D_C34_H_

#include "Size2d.h"


template <typename T> 
class Coord2d 
: public Size2d<T>
{
public:
	explicit Coord2d(T = 0, T = 0);

	void rotate(const Coord2d<T>&, float);
};


// Implementation
template <typename T> 
Coord2d<T>::Coord2d(T x, T y) 
: Size2d<T>(x, y)

{

}

template <typename T> 
void Coord2d<T>::rotate(const Coord2d<T>& origin, float rAngle)
{
	float sinTheta = (float)sin(rAngle);
	float cosTheta = (float)cos(rAngle);

	_val[X] -= origin[X];
	_val[Y] -= origin[Y];
	T x = _val[X];
	
	_val[X] = x * cosTheta - _val[Y] * sinTheta + origin[X];
	_val[Y] = x * sinTheta + _val[Y] * cosTheta + origin[Y];
}


#endif

