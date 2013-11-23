/*
 *  BaseIcon.h
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef BASE_ICON_H_
#define BASE_ICON_H_

#include "Touchable.h"

class Image;


class BaseIcon : public Touchable{
public:
	BaseIcon(const Coord2d<double>& = Coord2d<double>(0, 0));
	virtual ~BaseIcon();	
	
	//--- GENERAL ---//
	const Coord2d<double>& getOffset() const;
	double getOffset(GLshort) const;
	virtual void setOffset(double, double);	
	
	void enable(bool);
	
protected:
	//--- GENERAL ---//
	Coord2d<double> _offset;
	bool _enabled;
};


// Non-member Functions
void enable(BaseIcon*, void*);


#endif