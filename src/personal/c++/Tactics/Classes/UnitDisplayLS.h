/*
 *  UnitDisplayLS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/31/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef UNIT_DISPLAY_L_S_H_
#define UNIT_DISPLAY_L_S_H_

#include "StatDisplay.h"

class Unit;


class UnitDisplayLS : public StatDisplay<Unit>{
public:
	UnitDisplayLS(GLshort, GLshort, GLshort);
	
	//--- GENERAL ---//	
	void update(Unit*);
	
private:
	//--- GENERAL ---//
	Unit* _prevUnit;
	GLshort _prevHP;
	GLshort _prevTU;
	
	enum{NAME_STR, HP_STR, TU_STR, EN_STR};
};

#endif