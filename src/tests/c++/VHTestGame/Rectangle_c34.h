#ifndef RECTANGLE_C34_H_
#define RECTANGLE_C34_H_

#include "Drawable.h"

#include "Coord2d.h"
#include "Size2d.h"

#include "Const.h"


template <typename T> 
class Rectangle_c34
: public Drawable
{
public:
	Rectangle_c34(const Coord2d<T>& = Coord2d<T>(), 
				     const Size2d<T>& = Size2d<T>());
	~Rectangle_c34();

	// General
	T getCoord(size_t) const;
	T getSize(size_t) const;

	void setCoord(T, T);
	void setSize(T, T);

	// Draw
	void draw(HDC);

private:
	Coord2d<T> _coord;
	Size2d<T> _size;
};


// Implementation
template <typename T> 
Rectangle_c34<T>::Rectangle_c34(const Coord2d<T>& coord, 
								        const Size2d<T>& size)
: _coord(coord)
, _size(size)
{

}

template <typename T> 
Rectangle_c34<T>::~Rectangle_c34()
{

}


// General
template <typename T> 
T Rectangle_c34<T>::getCoord(size_t c) const
{
	return _coord[c];
}

template <typename T> 
T Rectangle_c34<T>::getSize(size_t c) const
{
	return _size[c];
}

template <typename T> 
void Rectangle_c34<T>::setCoord(T x, T y)
{
	_coord[X] = x;
	_coord[Y] = y;
}

template <typename T> 
void Rectangle_c34<T>::setSize(T x, T y)
{
	_size[X] = x;
	_size[Y] = y;
}


// Draw
template <typename T> 
void Rectangle_c34<T>::draw(HDC hdcBackBuffer)
{
	Rectangle(hdcBackBuffer, 
				 _coord[X], 
		       _size[Y] + _coord[Y],
				 _size[X] + _coord[X], 
		       _coord[Y]);
}

#endif