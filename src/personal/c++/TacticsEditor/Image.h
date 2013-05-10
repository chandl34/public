/*
 *  Image.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/18/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef IMAGE_H_
#define IMAGE_H_

#include "Include.h"


class Image{	
public:
	Image(const Size2d<GLshort>&, GLuint, 
			const Coord2d<double>& = Coord2d<double>(0, 0));
	Image(const Size2d<GLshort>&, const Size2d<GLshort>&, GLuint, 
			const Coord2d<double>& = Coord2d<double>(0, 0));
	Image(const Size2d<GLshort>&, const Size2d<GLshort>&, const Size2d<GLshort>&, GLuint, 
			const Coord2d<double>& = Coord2d<double>(0, 0));
	~Image();
	
	//--- GENERAL ---//
	const Size2d<GLshort>& getSize() const;
	GLshort getSize(GLshort) const;
	
	virtual void setOffset(double, double);
	const Coord2d<double>& getOffset() const;
	double getOffset(GLshort) const;	
	
	GLuint getTexName() const;
	
	//---- DRAW ----//
	void draw(bool, GLuint* = NULL);	
	void buildBuffers(vector<GLshort>&, vector<GLfloat>&);
	
private:	
	//--- GENERAL ---//
	GLuint _texName;
	
	Size2d<GLshort> _size;
	Coord2d<double> _offset;
	const GLshort* _texVert;
	const GLfloat* _texCoord;
};

#endif