/*
 *  GameScreen.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GameScreen.h"

#include "AnimStep.h"
#include "FuncStep.h"

#include "ImageStorage.h"
#include "Math.h"


GameScreen::GameScreen()
: BaseScreen(false)
{
	//bgImage = ImageStorage::getBGImage(0);
	
	// Setup Baloons
	Image* tempImg;
	tempImg = new Image(0, Size2d<GLshort>(60, 80)); // todo: remove... only for testing
	ImageStorage::addImage(tempImg);
	_balloon[BALLOON_1].setImage(tempImg);
	_balloon[BALLOON_1].setOffset(60, 220);
	
	ImageStorage::addImage(tempImg);
	_balloon[BALLOON_2].setImage(tempImg);
	_balloon[BALLOON_2].setOffset(140, 220);
	
	// Setup Boxes	
	tempImg = new Image(0, Size2d<GLshort>(180, 80)); // todo: remove... only for testing
	ImageStorage::addImage(tempImg);
	_box[CHANGE_BOX].setImage(tempImg);
	_box[CHANGE_BOX].setOffset(40, 20);
	
	_box[ANSWER_BOX_1].setImage(tempImg);
	_box[ANSWER_BOX_1].setOffset(260, 20);
	
	_box[ANSWER_BOX_2].setImage(tempImg);
	_box[ANSWER_BOX_2].setOffset(260, 120);
	
	// todo: remove!
	test1 = new Icon();
	test2 = new CompositeIcon();
	
	reset();
	
	_currSequence = NULL;
}

GameScreen::~GameScreen()
{
	// todo: remove!
	delete test1;
	delete test2;
}


void GameScreen::reset()
{
	// Init options
	_state = NOT_STARTED;
	
	for(GLshort i = 0; i < BALLOONS; ++i)
		_balloon[i].enable(true);
	_box[ANSWER_BOX_2].enable(false);	
	
	test1->setImage(ImageStorage::getItemImage(0));
	test1->setOffset(_balloon[BALLOON_1].getOffset(X) + _balloon[BALLOON_1].getSize(X) / 2, 
						  _balloon[BALLOON_1].getOffset(Y) + _balloon[BALLOON_1].getSize(Y) / 2);
	
	test2->clear();
	test2->setOffset(_balloon[BALLOON_2].getOffset(X) + _balloon[BALLOON_2].getSize(X) / 2, 
						  _balloon[BALLOON_2].getOffset(Y) + _balloon[BALLOON_2].getSize(Y) / 2);
	
	
	//----- CHANGE_SEQ -----//
	// First balloon
	_seq[CHANGE_SEQ].addStep(new FuncBaseStep(enable, 
															&_balloon[BALLOON_1], (void*)false));
	
	Coord2d<double> inBox(_box[CHANGE_BOX].getOffset(X) + _box[CHANGE_BOX].getSize(X) / 2, 
								 _box[CHANGE_BOX].getOffset(Y) + _box[CHANGE_BOX].getSize(Y) / 2);	
	
	_seq[CHANGE_SEQ].addStep(new MoveStep(test1, inBox));
	
	
	// Second balloon
	_seq[CHANGE_SEQ].addStep(new FuncBaseStep(enable, 
															&_balloon[BALLOON_2], (void*)false));
	// Add
	if(roll(50)){		
		test2->addIcon(ImageStorage::getItemImage(0));		
		_seq[CHANGE_SEQ].addStep(new MoveStep(test2, inBox));		
		
	}
	// Subtract
	else{		
		test2->addIcon(ImageStorage::getItemImage(2));		
		_seq[CHANGE_SEQ].addStep(new MoveStep(test2, inBox));		
		
		_seq[CHANGE_SEQ].addStep(new FuncCompStep(addIcon, 
																test2, (void*)ImageStorage::getItemImage(0)));
		
		Coord2d<double> offScreen(480, 150);
		_seq[CHANGE_SEQ].addStep(new MoveStep(test2, offScreen));		
	}
	

	// Show options
	_seq[CHANGE_SEQ].addStep(new FuncBaseStep(enable, 
															&_box[ANSWER_BOX_2], (void*)true));
	
	
	
	//----- ANSWER_SEQ -----//
}


//---- DRAW ----//
void GameScreen::draw(bool step)
{
	BaseScreen::draw(step);
	
	for(GLshort i = 0; i < BALLOONS; ++i)
		_balloon[i].draw(step);
	
	for(GLshort i = 0; i < BOXES; ++i)
		_box[i].draw(step);
	
	if(_currSequence != NULL){
		if(_currSequence->isFinished())
			_currSequence = NULL;
		else
			_currSequence->draw(step);
	}
}
