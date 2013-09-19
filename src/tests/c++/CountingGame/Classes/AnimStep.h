/*
 *  AnimStep.h
 *  CountingGame
 *
 *  Created by Jonathan Chandler on 11/26/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ANIM_STEP_H_
#define ANIM_STEP_H_


#include "SeqStep.h"

class BaseIcon;


class AnimStep : public SeqStep{
public:
	AnimStep(BaseIcon*,
				GLshort = 1);
	virtual ~AnimStep();
	
protected:
	BaseIcon* _icon;	
};


// Movement
class MoveStep : public AnimStep{
public:
	MoveStep(BaseIcon*,
				const Coord2d<double>&,
				GLshort = 1);
	
	//---- DRAW ----//
	void draw(bool);
	
private:
	Coord2d<double> _vec;
};



/*
 
 
 template<class T, class F>
 class AnimStepBase : public AnimStep{
 public:
 AnimStepBase(const Icon& icon, 
 AnimType<T>* animType,
 AnimFinish<F>* animFinish)
 : AnimStep(icon)
 {
 _animType = animType;
 _animFinish = animFinish;
 }
 
 public:
 
 static AnimStepBase<T, F>* create(const Icon&, 
 AnimType<T>*,
 AnimFinish<F>*);
 
 virtual ~AnimStepBase()
 {
 delete _animType;
 delete _animFinish;
 }
 
 //--- GENERAL ---//
 bool isFinished()
 {
 return _animFinish->isFinished();
 }
 
 //---- DRAW ----//
 void draw(bool step)
 {
 _icon.draw(step);
 _animType->step();
 }
 
 
 private:
 AnimType<T>* _animType;
 AnimFinish<F>* _animFinish;					  
 };
 */

#endif