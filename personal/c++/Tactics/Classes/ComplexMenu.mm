/*
 *  ComplexMenu.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ComplexMenu.h"


ComplexMenu::~ComplexMenu(){
	for(GLshort i = 0; i < selectable.size(); ++i)
		delete selectable[i];
}


//--- GENERAL ---//
GLshort ComplexMenu::getSelectedOption() const{
	if(_selected == -1)
		return -1;
	else
		return selectable[_selected]->getSelected();
}

void ComplexMenu::addSelectable(Selectable* m){
	selectable.push_back(m);
}

Button* ComplexMenu::getButton(GLshort o, GLshort s){
	if(o >= 0 && o < selectable.size())
		return selectable[o]->getButton(s);	
	return NULL;
}

Button* ComplexMenu::getButton(GLshort s){
	printf("ERROR:  ComplexMenu::getButton(GLshort) should not be called!\n"); // todo:  make this workable?
	return NULL;
}

//---- DRAW ----//
void ComplexMenu::draw(bool step){
	for(GLshort i = 0; i < selectable.size(); ++i)
		selectable[i]->draw(step);
}


//---- TOUCH ----//
bool ComplexMenu::isTouching(const Coord2d<GLshort>& p){	
	for(GLshort i = 0; i < selectable.size(); ++i){
		if(selectable[i]->isTouching(p))
			return true;
	}
	return false;
}

void ComplexMenu::push(GLshort t, const Coord2d<GLshort>& p){	
	_selected = -1;
	for(GLshort i = 0; i < selectable.size(); ++i){
		if(selectable[i]->isTouching(p)){
			_selected = i;
			selectable[_selected]->push(t, p);
			break;
		}
	}
}

void ComplexMenu::move(GLshort t, const Coord2d<GLshort>& p){	
	if(_selected == -1)
		push(t, p);
	else if(selectable[_selected]->isTouching(p))
		selectable[_selected]->move(t, p);
	else{
		selectable[_selected]->release(t, p);
		_selected = -1;
		push(t, p);
	}
}

bool ComplexMenu::release(GLshort t, const Coord2d<GLshort>& p){
	if(_selected == -1)
		return false;
	return selectable[_selected]->release(t, p);
}
