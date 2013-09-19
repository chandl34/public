/*
 *  Icon.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ICON_H_
#define ICON_H_

#include "BaseIcon.h"


class Icon : public BaseIcon{
public:
	Icon(Image* = NULL, 
		  const Coord2d<double>& = Coord2d<double>(0, 0));
	virtual ~Icon();	
	
	//--- GENERAL ---//
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;	
	
	void setImage(Image*);
	
	//--- TOUCH ---//
	bool isTouching(const Coord2d<GLshort>&);
	
	//---- DRAW ----//
	virtual void draw(bool);
	
protected:
	//--- GENERAL ---//
	Image* _image;
};

#endif
