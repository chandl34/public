/*
 *  Section.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/24/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Section.h"


Section::Section(Image* img,
				 const Coord2d<double>& os,
				 const Size2d<GLshort>& size,
				 bool showBar)
: Icon(img, os, size)
{
	//--- GENERAL ---//
	_showBar = showBar;
	
	//--- TOUCH ---//
	_touched = NULL;
	_drag = false;
}

Section::~Section()
{
	for(list<Component*>::iterator iter = _comp.begin(); iter != _comp.end(); ++iter)
		delete *iter;
}


//--- GENERAL ---//
void Section::addComponent(Component* comp)
{
	_comp.push_back(comp);
	
	// Adjust relative offset
	comp->setOffset(_offset[X] + comp->getOffset(X), 
					_offset[Y] + comp->getOffset(Y));
	
	// Set camera bounds
	Coord2d<GLshort> bx;
	bx[MIN] = min((double)_camera.getBound(X, MIN), 
				  _offset[X] + _size[X] - (comp->getOffset(X) + comp->getSize(X)));
	bx[MAX] = max((double)_camera.getBound(X, MAX), 
				  _offset[X] - comp->getOffset(X));
	
	Coord2d<GLshort> by;
	by[MIN] = min((double)_camera.getBound(Y, MIN), 
				  _offset[Y] + _size[Y] - (comp->getOffset(Y) + comp->getSize(Y)));
	by[MAX] = max((double)_camera.getBound(Y, MAX), 
				  _offset[Y] - comp->getOffset(Y));
	
	_camera.setBounds(bx, by);
}


//---- DRAW ----//
void Section::draw(bool step, TexAttr* ta)
{
	Icon::draw(step, ta);
	
	if(_camera.isScrollable()){
		// Scroll components
		glMatrixMode(GL_PROJECTION);
		glTranslatef(_camera.getView(X) + 0.1f, 
					 _camera.getView(Y) + 0.1f, 
					 0.0f);		
		glMatrixMode(GL_MODELVIEW);
		
		// Scissor edges
		glEnable(GL_SCISSOR_TEST);			
		glScissor(_offset[Y], SCREEN_SIZE[X] - (_offset[X] + _size[X]), 
				  _size[Y], _size[X]);	
	}
	
	for(list<Component*>::iterator iter = _comp.begin(); iter != _comp.end(); ++iter)
		(*iter)->draw(step, ta);
	
	if(_camera.isScrollable()){		
		// Scroll back
		glDisable(GL_SCISSOR_TEST);
		
		glMatrixMode(GL_PROJECTION);
		glTranslatef(-(_camera.getView(X) + 0.1f), 
					 -(_camera.getView(Y) + 0.1f), 
					 0.0f);	
		glMatrixMode(GL_MODELVIEW);		
	}	 
}


//--- TOUCH ---//
bool Section::push(GLshort t, const Coord2d<GLshort>& p)
{
	if(!isTouching(p))
		return false;
	
	_startPoint = p;
	_lastPoint = p;
	
	for(list<Component*>::iterator iter = _comp.begin(); iter != _comp.end(); ++iter){
		if((*iter)->push(t, p)){
			_touched = *iter;
			break;
		}
	}
	   
	return true;
}

bool Section::move(GLshort t, const Coord2d<GLshort>& p)
{
	if(_touched && !_drag){
		if(_camera.isScrollable() && 
		   hypot(p[X] - _startPoint[X], p[Y] - _startPoint[Y]) > DRAG_THRESHOLD
		   ){
			_drag = true;
			_touched->release(t, p);
			_touched = NULL;
			//for(list<Component*>::iterator iter = _comp.begin(); iter != _comp.end(); ++iter)
			//	(*iter)->release(t, p);
		}
		else{
			_touched->move(t, p);
		}
	}
	else{	
		for(int i = 0; i < 2; ++i)
			_camera.setView(i, _camera.getView(i) + p[i] - _lastPoint[i]);
	}
	_lastPoint = p;
	
	return _touched != NULL;
}

bool Section::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(_touched){
		_touched->release(t, p);		
		_touched = NULL;
	}
	
    _lastPoint = p;
	_drag = false;
	
	return false;
}

