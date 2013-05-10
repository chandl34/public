/*
 *  UnitDisplayIS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/4/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef UNIT_DISPLAY_I_S_H_
#define UNIT_DISPLAY_I_S_H_

#include "StatDisplay.h"

class Unit;


class UnitDisplayIS : public StatDisplay<Unit>{
public:
	UnitDisplayIS(GLshort, GLshort, GLshort);
	
	//--- GENERAL ---//	
	void update(Unit*);
	
private:
	//--- GENERAL ---//	
	enum{NAME_STR, STR_STR, AGI_STR, ACC_STR, REA_STR, 
		 STAT_STR, BATTLE_STR, KILL_STR, RATE_STR, IMP_STR};
};

#endif
