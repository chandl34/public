/*
 *  UnitDisplayLS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/31/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "UnitDisplayLS.h"

#include "Unit.h"

#include "String.h"


UnitDisplayLS::UnitDisplayLS(GLshort lx, GLshort rx, GLshort ty) 
: StatDisplay<Unit>(lx, rx, ty){
	_prevUnit = NULL;
	GLshort y = _topY;
	
	_text.push_back(TextLine());
	_text[NAME_STR].addString(" ", Coord2d<double>(_centerX, y), CENTERED);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[HP_STR].addString("HP:", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[HP_STR].addString(" ", Coord2d<double>(_rightX -  HUNDRED_WIDTH - SLASH_WIDTH, y), ALIGN_RIGHT);
	_text[HP_STR].addString(" / ", Coord2d<double>(_rightX - HUNDRED_WIDTH, y), ALIGN_RIGHT);
	_text[HP_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[TU_STR].addString("TU:", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[TU_STR].addString(" ", Coord2d<double>(_rightX -  HUNDRED_WIDTH - SLASH_WIDTH, y), ALIGN_RIGHT);
	_text[TU_STR].addString(" / ", Coord2d<double>(_rightX - HUNDRED_WIDTH, y), ALIGN_RIGHT);
	_text[TU_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[EN_STR].addString("EN:", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[EN_STR].addString("100", Coord2d<double>(_rightX -  HUNDRED_WIDTH - SLASH_WIDTH, y), ALIGN_RIGHT);
	_text[EN_STR].addString(" / ", Coord2d<double>(_rightX - HUNDRED_WIDTH, y), ALIGN_RIGHT);
	_text[EN_STR].addString("100", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
}


void UnitDisplayLS::update(Unit* sUnit){
	if(sUnit != _prevUnit)
		_text[NAME_STR].setString("The Man");
	
	if(sUnit != _prevUnit || _prevHP != sUnit->getHP()){
		_prevHP = sUnit->getHP();
		_text[HP_STR].setString(numToString(_prevHP, 3), 1);
		_text[HP_STR].setString(numToString(sUnit->getMaxHP(), 3), 3);
	}
	
	if(sUnit != _prevUnit || _prevTU != sUnit->getTU()){
		_prevTU = sUnit->getTU();
		_text[TU_STR].setString(numToString(_prevTU, 3), 1);
		_text[TU_STR].setString(numToString(sUnit->getMaxTU(), 3), 3);
	}
	
	_prevUnit = sUnit;
}
