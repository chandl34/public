/*
 *  OffsetBase.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OFFSET_BASE_H_
#define OFFSET_BASE_H_

#include "Include.h"


class OffsetBase{
public:	
	OffsetBase(const Coord2d<double>& = Coord2d<double>(0.0, 0.0));
	virtual ~OffsetBase();
	
	//---- GENERAL ----//
	const Coord2d<double>& getOffset() const;
	double getOffset(GLshort) const;
	
	virtual void setOffset(double, double);
	
protected:
	Coord2d<double> _offset;
};

#endif