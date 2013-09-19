/*
 *  Menu.mm
 *  c34_UI
 *
 *  Created by Jonathan Chandler on 1/25/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Menu.h"

#include "ImageStorage.h"


Menu::Menu(const Coord2d<double>& os,
		   const Size2d<GLshort>& bsize,
		   const Size2d<GLshort>& dim,
		   bool mobile)
: Component(os, Size2d<GLshort>(bsize[X] * dim[X], bsize[Y] * dim[Y]))
, _button(dim[X])
, _dim(dim)
{
	Image* image;
	Coord2d<double> bos;
	
	bos[X] = _offset[X];
	for(GLshort i = 0; i < _dim[X]; ++i){
		bos[Y] = _offset[Y];	
		for(GLshort j = 0; j < _dim[Y]; ++j){
			image = new Image();
			ImageStorage::addImage(image);
			
			_button[i].push_back(Button(image, bos, bsize));
			
			bos[Y] += bsize[Y];
		}		
		bos[X] += bsize[X];
	}
	
	_selected = NULL;
	
	_mobile = mobile;
}

Menu::~Menu()
{
	
}


//--- GENERAL ---//
Button* Menu::getButton(GLshort i)
{
	if(i < 0 || i >= _dim[X] * _dim[Y])
		return NULL;
	
	return &_button[i % _dim[X]][i / _dim[X]];
}

void Menu::setColor(const Color& color)
{
	for(GLshort i = 0; i < _button.size(); ++i){
		for(GLshort j = 0; j < _button[i].size(); ++j)
			_button[i][j].setColor(color);;
	}
}


//---- DRAW ----//
void Menu::draw(bool step, TexAttr* ta)
{
	for(GLshort i = 0; i < _button.size(); ++i){
		for(GLshort j = 0; j < _button[i].size(); ++j)
			_button[i][j].draw(step, ta);
	}
}


//--- TOUCH ---//
bool Menu::push(GLshort t, const Coord2d<GLshort>& p)
{
	if(isTouching(p)){
		for(GLshort i = 0; i < _button.size(); ++i){
			for(GLshort j = 0; j < _button[i].size(); ++j){
				if(_button[i][j].push(t, p)){
					_selected = &_button[i][j];
					return true;
				}
			}
		}
	}
	
	return false;
}

bool Menu::move(GLshort t, const Coord2d<GLshort>& p)
{
	if(_selected && !_selected->move(t, p)){
		if(_mobile)
			_selected = NULL;			
	}
	
	if(!_selected){			
		for(GLshort i = 0; i < _button.size(); ++i){
			for(GLshort j = 0; j < _button[i].size(); ++j){
				if(_button[i][j].move(t, p)){
					_selected = &_button[i][j];
					return true;
				}
			}
		}
	}
	
	return _selected;
}

bool Menu::release(GLshort t, const Coord2d<GLshort>& p)
{
	bool ret = false;
	
	if(_selected){
		ret = _selected->release(t, p);
		_selected = NULL;
	}
	
	return ret;
}
