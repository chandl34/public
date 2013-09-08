/*
 *  PopupMenu.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "PopupMenu.h"


PopupMenu::PopupMenu(Image* image,
					 const Coord2d<double>& os,
					 const Size2d<GLshort>& size,
					 const Size2d<GLshort>& bsize,
					 const Size2d<GLshort>& dim)
: Button(image, os, size)
, _menu(Coord2d<double>(os[X], os[Y] + size[Y]), bsize, dim, true)
{
	//--- GENERAL ---//
	_expanded = false;
	
	//---- TOUCH ----//
	_timePushed = -1;
	_actionDelay = 0.25f;	
}

PopupMenu::~PopupMenu()
{
	
}



//--- GENERAL ---//		// todo: remove... TEMP!
Button* PopupMenu::getButton(GLshort i)
{
	return _menu.getButton(i);
}

void PopupMenu::setColor(const Color& color)
{
	Button::setColor(color);
	_menu.setColor(color);
}


//---- DRAW ----//
void PopupMenu::draw(bool step, TexAttr* ta)
{
	if(_timePushed > 0 && [[NSDate date] timeIntervalSince1970] - _timePushed > _actionDelay){
		_timePushed = -1;
		_expanded = true;
	}
	
	Button::draw(step, ta);
	if(_expanded)
		_menu.draw(step, ta);
}


//--- TOUCH ---//
bool PopupMenu::push(GLshort t, const Coord2d<GLshort>& p)
{
	bool ret = Button::push(t, p);
	
	if(ret)
		_timePushed = [[NSDate date] timeIntervalSince1970];
	
	return ret;
}

bool PopupMenu::move(GLshort t, const Coord2d<GLshort>& p)
{
	bool ret = push(t, p);
	
	if(_expanded){
		if(_menu.move(t, p))
			ret = true;
		
		if(!ret){
			_expanded = false;			
			_timePushed = -1;
		}
	}
	
	return ret;
}

bool PopupMenu::release(GLshort t, const Coord2d<GLshort>& p)
{
	bool ret = Button::release(t, p);
	if(_expanded){
		if(_menu.release(t, p))
			ret = true;
		
		_expanded = false;
	}
	
	_timePushed = -1;
	
	return ret;
}	
