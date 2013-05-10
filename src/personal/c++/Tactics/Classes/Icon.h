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

#include "Movable.h"

#include "Image.h"


class Icon : public Movable{
public:
	Icon(Image* = NULL, const Coord2d<double>& = Coord2d<double>(0, 0));
	virtual ~Icon();	
	
	//--- GENERAL ---//
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;	
	
	void setImage(Image*);
	
	//---- DRAW ----//
	virtual void draw(bool, TexAttr* = NULL);
	void buildBuffers(GLuint, vector<GLshort>&, GLuint, vector<GLfloat>&);
	
	//--- TOUCH ---//
	bool isTouching(const Coord2d<GLshort>&);
	
protected:
	//--- GENERAL ---//
	Image* _image;
	
	// SCREEN OFFSET //
	GLuint _texVertName;
	GLuint _texCoordName;
	GLint _texPos;
};

#endif
