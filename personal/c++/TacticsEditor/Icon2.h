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
	void setImage(Image*);
	GLshort getTexOffset(GLshort);	
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;	
	
	//--- TOUCH ---//
	bool isTouching(const Coord2d<GLshort>&);
	
	virtual void push(GLshort, const Coord2d<GLshort>&);
	virtual void move(GLshort, const Coord2d<GLshort>&);
	virtual bool release(GLshort, const Coord2d<GLshort>&);
	
	//---- DRAW ----//
	virtual void draw(bool);
	
protected:
	//--- GENERAL ---//
	Image* _image;
};

#endif
