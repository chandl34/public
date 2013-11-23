/*
 *  Sequence.h
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "Drawable.h"

class SeqStep;


class Sequence : public Drawable{
public:
	virtual ~Sequence();
	
	//--- GENERAL ---//
	bool isFinished();
	void addStep(SeqStep*);
	
	//---- DRAW ----//
	void draw(bool);
	
protected:
	list<SeqStep*> _seqStep;
};

#endif