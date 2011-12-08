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
template <typename T> Coord2d<T>::Coord2d(){}
template <typename T> Coord2d<T>::Coord2d(T x, T y){c[X] = x; c[Y] = y;}
template <typename T> T& Coord2d<T>::operator[](GLshort i){return c[i];}
template <typename T> const T& Coord2d<T>::operator[](GLshort i) const{return c[i];}

#endif
