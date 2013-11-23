/*
 *  FuncStep.h
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef FUNC_STEP_H_
#define FUNC_STEP_H_

#include "AnimStep.h"

class BaseIcon;
class CompositeIcon;



class FuncBaseStep : public AnimStep{
public:
	FuncBaseStep(void (*)(BaseIcon*, void*),
					 BaseIcon*,
					 void* = NULL);
	
	//---- DRAW ----//
	void draw(bool);
	
protected:
	void (*_func)(BaseIcon*, void*);
	void* _arg;
};


class FuncCompStep : public AnimStep{
public:
	FuncCompStep(void (*)(CompositeIcon*, void*),
					 CompositeIcon*,
					 void* = NULL);
	
	//---- DRAW ----//
	void draw(bool);
	
protected:
	void (*_func)(CompositeIcon*, void*);
	void* _arg;
};

#endif
