/*
 *  AnimStep.mm
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "AnimStep.h"

#include "BaseIcon.h"


// Base
AnimStep::AnimStep(BaseIcon* icon,
						 GLshort steps)
: SeqStep(steps)
{
	_icon = icon;
}

AnimStep::~AnimStep()
{
	
}



// Movement
MoveStep::MoveStep(BaseIcon* icon, 
						 const Coord2d<double>& goal,
						 GLshort steps)
: AnimStep(icon, steps)
, _vec(goal)
{
	
}


//---- DRAW ----//
void MoveStep::draw(bool step)
{
	if(!init){		
		init = true;
		
		// Setup vector
		_vec[X] -= _icon->getOffset(X);
		_vec[Y] -= _icon->getOffset(Y);
		double size = hypot(_vec[X], _vec[Y]);
		_steps = size + 0.5;
		_vec[X] = _vec[X] / size;
		_vec[Y] = _vec[Y] / size;
		printf("Starting move function\n");
		cout << _vec[X] << ", " << _vec[Y] << endl;
	}
	
	_icon->draw(step);
	_icon->setOffset(_icon->getOffset(X) + _vec[X], 
						  _icon->getOffset(Y) + _vec[Y]);
	--_steps;
}

/*
 // Template
 template<class T, class F>
 AnimStepBase<T, F>::AnimStepBase(const Icon& icon, 
 AnimType<T>* animType,
 AnimFinish<F>* animFinish)
 : AnimStep(icon)
 {
 _animType = animType;
 _animFinish = animFinish;
 }
 /*
 template<class T, class F>
 AnimStepBase<T, F>* AnimStepBase<T, F>::create(const Icon& icon, 
 AnimType<T>* animType,
 AnimFinish<F>* animFinish)
 {
 AnimStepBase* ast = new AnimStepBase<T, F>(icon, animType, animFinish);
 return ast;
 }
 *//*
	 template<class T, class F>
	 AnimStepBase<T, F>::~AnimStepBase()
	 {
	 delete _animType;
	 delete _animFinish;
	 }
	 
	 
	 //--- GENERAL ---//
	 template<class T, class F>
	 bool AnimStepBase<T, F>::isFinished()
	 {
	 return _animFinish->isFinished();
	 }
	 
	 //---- DRAW ----//
	 template<class T, class F>
	 void AnimStepBase<T, F>::draw(bool step)
	 {
	 _icon.draw(step);
	 _animType->step();
	 }
	 */