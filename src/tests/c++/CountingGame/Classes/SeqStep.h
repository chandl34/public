/*
 *  SeqStep.h
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SEQ_STEP_H_
#define SEQ_STEP_H_


#include "Drawable.h"



class SeqStep : public Drawable{
public:
	SeqStep(GLshort = 1);
	virtual ~SeqStep();
	
	//--- GENERAL ---//
	bool isFinished();
	
protected:	
	bool init;
	GLshort _steps;
};

#endif