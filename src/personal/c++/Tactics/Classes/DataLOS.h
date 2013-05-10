/*
 *  DataLOS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/12/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DATA_LOS_H_
#define DATA_LOS_H_

#include "Include.h"


class DataLOS{
public:
	void add(GLshort, GLshort);
	void remove(GLshort, GLshort);
	GLshort get(GLshort, GLshort);
	
private:
	GLshort _losData[2][3];
};

#endif