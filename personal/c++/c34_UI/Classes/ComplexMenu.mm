/*
 *  ComplexMenu.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/26/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "ComplexMenu.h"


ComplexMenu::ComplexMenu()
: Component()
{
	_selected = NULL;
}

ComplexMenu::~ComplexMenu()
{
	for(list<Button*>::iterator iter = _button.begin(); iter != _button.end(); ++iter)
		delete *iter;
}


//--- GENERAL ---//		
void ComplexMenu::addButton(Button* b)
{
	_button.push_back(b);
}

void ComplexMenu::setColor(const Color& color)
{
	for(list<Button*>::iterator iter = _button.begin(); iter != _button.end(); ++iter)
		(*iter)->setColor(color);
}


//---- DRAW ----//
void ComplexMenu::draw(bool step, TexAttr* ta)
{
	for(list<Button*>::iterator iter = _button.begin(); iter != _button.end(); ++iter)
		(*iter)->draw(step, ta);
}


//--- TOUCH ---//
bool ComplexMenu::isTouching(const Coord2d<GLshort>& p)
{
	for(list<Button*>::iterator iter = _button.begin(); iter != _button.end(); ++iter){
		if((*iter)->isTouching(p))
			return true;
	}
	
	return false;
}

bool ComplexMenu::push(GLshort t, const Coord2d<GLshort>& p)
{
	for(list<Button*>::iterator iter = _button.begin(); iter != _button.end(); ++iter){
		if((*iter)->push(t, p)){
			_selected = *iter;
			return true;
		}
	}
	
	return false;
}

bool ComplexMenu::move(GLshort t, const Coord2d<GLshort>& p)
{
	if(_selected && !_selected->move(t, p))
		_selected = NULL;
	
	if(!_selected){
		for(list<Button*>::iterator iter = _button.begin(); iter != _button.end(); ++iter){
			if((*iter)->move(t, p)){
				_selected = *iter;
				return true;
			}
		}
	}
	
	return _selected;
}

bool ComplexMenu::release(GLshort t, const Coord2d<GLshort>& p)
{
	bool ret = false;
	
	if(_selected){
		ret = _selected->release(t, p);
		_selected = NULL;
	}
	
	return ret;
}
