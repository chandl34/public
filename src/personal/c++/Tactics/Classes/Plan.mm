/*
 *  Plan.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Plan.h"


Plan::Plan(GLshort a, GridBlock* gb)
{
	_action = a;
	_goal = gb;
}

GLshort Plan::getAction()
{
	return _action;
}

GridBlock* Plan::getGoal()
{
	return _goal;
}
