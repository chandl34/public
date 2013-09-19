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

#include "Component.h"

#include "Color.h"
#include "Image.h"


class Icon 
: public Component
{
public:
	Icon(Image* = NULL, 
		 const Coord2d<double>& = Coord2d<double>(0, 0),
		 const Size2d<GLshort>& = Size2d<GLshort>(0, 0));
	virtual ~Icon();	
	
	//--- GENERAL ---//
	void setImage(Image*);
	virtual void setColor(const Color&);
	
	//---- DRAW ----//
	virtual void draw(bool, TexAttr* = NULL);
	void buildBuffers(GLuint, vector<GLshort>&, GLuint, vector<GLfloat>&);
	
protected:
	//--- GENERAL ---//
	Image* _image;
	Color _color;
	Color _colorMod;
	
	// SCREEN OFFSET //
	GLuint _texVertName;
	GLuint _texCoordName;
	GLint _texPos;
};

#endif
