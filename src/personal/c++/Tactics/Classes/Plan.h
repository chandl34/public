/*
 *  Plan.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PLAN_H_
#define PLAN_H_

#include "Include.h"

class GridBlock;


class Plan{
public:
	Plan(GLshort, GridBlock*);
	
	GLshort getAction();
	GridBlock* getGoal();
	
private:
	GLshort _action;
	GridBlock* _goal;
};

#endif