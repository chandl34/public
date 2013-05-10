/*
 *  Geometry.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 2/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Include.h"


class Geometry{
public:
	virtual ~Geometry();
	
	//--- GENERAL ---//	
	double dot(const Geometry&) const;
	double dot(double, double, double) const;
	
	//--- MORPH ---//
	void rotateX(double);
	void rotateY(double);
	void rotateZ(double);
	
protected:	
	Geometry(double x = 0.0, double y = 0.0, double z = 0.0);
	
	//--- GENERAL ---//	
	double val[3];	
	
	void setValue(double, double, double);	
};

#endif