/*
 *  Hit.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef HIT_H_
#define HIT_H_

#include "Include.h"

class Object;


class Hit{
public:
	Hit();
	
	void setObjectHit(Object*);
	Object* getObjectHit();
	
	void setSectionHit(GLshort);
	GLshort getSectionHit();
	
	void setTimeLeft(double);
	double getTimeLeft();
	
private:
	Object* _objHit;
	GLshort _sectionHit;
	double _timeLeft;	
};

#endif 

