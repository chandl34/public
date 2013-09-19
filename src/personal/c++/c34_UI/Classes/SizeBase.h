/*
 *  SizeBase.h
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/24/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SIZE_BASE_H_
#define SIZE_BASE_H_

#include "Include.h"


class SizeBase{
public:	
	SizeBase(const Size2d<GLshort>& = Size2d<GLshort>(0.0, 0.0));
	virtual ~SizeBase();
	
	//---- GENERAL ----//
	const Size2d<GLshort>& getSize() const;
	double getSize(GLshort) const;
	
	virtual void setSize(GLshort, GLshort);
	
protected:
	Size2d<GLshort> _size;
};

#endif