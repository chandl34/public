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

#include "Include.h"

class Image;


class Icon{
public:
	Icon(Image* = NULL, const Coord2d<double>& = Coord2d<double>(0, 0));
	virtual ~Icon();	
	
	//--- GENERAL ---//
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;	
	
	virtual void setOffset(double, double);
	const Coord2d<double>& getOffset() const;
	double getOffset(GLshort) const;
	
	bool isTouching(const Coord2d<GLshort>&);
	
	void setImage(Image*);
	
	//---- DRAW ----//
	virtual void draw(bool, GLuint* = NULL, GLuint* = NULL, GLuint* = NULL);
	void buildBuffers(GLuint, vector<GLshort>&, GLuint, vector<GLfloat>&);
	
protected:
	//--- GENERAL ---//
	Image* image;
	
	// SCREEN OFFSET //
	Coord2d<double> offset;
	GLuint _texVertName;
	GLuint _texCoordName;
	GLint _texPos;
};

#endif
