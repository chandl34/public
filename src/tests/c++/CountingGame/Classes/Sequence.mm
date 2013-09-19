/*
 *  Sequence.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Sequence.h"

#include "SeqStep.h"


Sequence::~Sequence()
{
	for(list<SeqStep*>::iterator iter = _seqStep.begin(); iter != _seqStep.end(); ++iter)
		delete *iter;
}


//--- GENERAL ---//
bool Sequence::isFinished()
{
	return _seqStep.empty();
}

void Sequence::addStep(SeqStep* seqStep)
{
	_seqStep.push_back(seqStep);
}


//---- DRAW ----//
void Sequence::draw(bool step){
	if(_seqStep.front()->isFinished()){
		delete _seqStep.front();
		_seqStep.pop_front();
		
		if(!isFinished())
			cout << "Getting next step" << endl;
	}
	
	if(!isFinished()){
		_seqStep.front()->draw(step);
	}
}
