/*
 *  Coord2d.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef COORD_2D_H_
#define COORD_2D_H_

#include "Include.h"


template <typename T> class Coord2d{
public:
	Coord2d();	
	explicit Coord2d(T, T);
	
	T& operator[](GLshort);
	const T& operator[](GLshort) const;
	
private:
	T c[2];
};


// Implementation
template <typename T> 
Coord2d<T>::Coord2d()
{
	c[X] = 0;  
	c[Y] = 0;
}

template <typename T> 
Coord2d<T>::Coord2d(T x, T y)
{
	c[X] = x; 
	c[Y] = y;
}

template <typename T> 
T& Coord2d<T>::operator[](GLshort i)
{
	return c[i];
}

template <typename T> 
const T& Coord2d<T>::operator[](GLshort i) const
{
	return c[i];
}

// Non-member functions
template <typename T> 
bool operator<(const Coord2d<T>& lhs, const Coord2d<T>& rhs)
{
	if(lhs[X] < rhs[X])
		return true;
	else if(lhs[X] == rhs[X]){
		if(lhs[Y] < rhs[Y])
			return true;		
	}
	return false;
}

#endif
