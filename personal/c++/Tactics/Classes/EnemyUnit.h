/*
 *  EnemyUnit.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/10/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ENEMY_UNIT_H_
#define ENEMY_UNIT_H_

#include "Memory.h"
#include "Plan.h"
#include "Unit.h"

class GridBlock;


const GLshort PATROL_MAX = 5;
const GLshort APPROACH_MAX = 3;
const GLshort RUN_MAX = 3;
enum{S_AMMO, S_FIND, S_APPROACH, S_ATTACK, S_COVER, S_TURN, S_END}; 
typedef pair<GridBlock*, GLshort> BlockEst;


class EnemyUnit : public Unit{	
protected:
	EnemyUnit(const ObjType&, const Dir&, GLshort, 
			  const HP&, const TU&);
	friend class Unit;
	
public:
	//--- AI ---//
	bool isFinished();
	
	static void findNewData(UnitSet&, MemoryMap&);
	
	void findPlan(UnitSet&, MemoryMap&);
	void workPlan();
	
	//--- TURN ---//
	void newTurn();
	
private:
	//--- AI ---//
	GLshort _stage;	
	list<Plan> _plan;
	
	// Stages
	void checkAmmo();
	void findEnemy(UnitSet&, MemoryMap&);
	void approach();
	void attackEnemy();
	void runOrKneel();
	void turn(UnitSet&, MemoryMap&);
	
	// Helper methods
	GridBlock* getClosestEnemyLoc(UnitSet&, MemoryMap* = NULL);
	GridBlock* getEmptyLocNear(Unit*, GLshort);
	BlockEst getSaferLocInRange(GLshort);				// This finds the best combination of safeness and distance
};

#endif