/*
 *  FuncStep.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "FuncStep.h"

#include "BaseIcon.h"
#include "CompositeIcon.h"



FuncBaseStep::FuncBaseStep(void (*func)(BaseIcon*, void*),
									BaseIcon* icon,
									void* arg)
: AnimStep(icon, 1)
{
	_func = func;
	_arg = arg;
}


//---- DRAW ----//
void FuncBaseStep::draw(bool step)
{
	printf("Activating function\n");
	_func(_icon, _arg);
	--_steps;
}



FuncCompStep::FuncCompStep(void (*func)(CompositeIcon*, void*),
									CompositeIcon* icon,
									void* arg)
: AnimStep(icon, 1)
{
	_func = func;
	_arg = arg;
}


//---- DRAW ----//
void FuncCompStep::draw(bool step)
{
	printf("Activating function\n");
	_func((CompositeIcon*)_icon, _arg);
	--_steps;
}
