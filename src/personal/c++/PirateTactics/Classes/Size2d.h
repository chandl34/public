/*
 *  Size2d.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SIZE_2D_H_
#define SIZE_2D_H_

#include "Coord2d.h"

template <typename T> class Size2d : public Coord2d<T>{
public:
	Size2d();
	explicit Size2d(T, T);
};


// Implementation
template <typename T> Size2d<T>::Size2d(){}
template <typename T> Size2d<T>::Size2d(T x, T y) : Coord2d<T>(x, y){}

#endif

