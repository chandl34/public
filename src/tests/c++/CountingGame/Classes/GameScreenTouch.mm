/*
 *  GameScreenTouch.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */



#include "GameScreen.h"

#include "MainScreen.h"



//--- TOUCH ---//
void GameScreen::push(GLshort t, const Coord2d<GLshort>& p)
{	
	if(_currSequence == NULL){
		if(_state == NOT_STARTED){
			if(_balloon[BALLOON_1].isTouching(p)){
				printf("Game started\n");
				_currSequence = &_seq[CHANGE_SEQ];
				_state = CHOOSE_ANSWER;
			}
		}
		else if(_state == CHOOSE_ANSWER){
			if(_box[ANSWER_BOX_1].isTouching(p)){
				printf("Chose box 1\n");
				reset();
			}
			else if(_box[ANSWER_BOX_2].isTouching(p)){
				printf("Chose box 2\n");
				reset();		
			}	
		}
	}
}

void GameScreen::move(GLshort t, const Coord2d<GLshort>& p)
{	
	
}

bool GameScreen::release(GLshort t, const Coord2d<GLshort>& p)
{	
	return false;
}
