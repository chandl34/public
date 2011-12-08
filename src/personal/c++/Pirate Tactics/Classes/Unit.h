/*
 *  Unit.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef UNIT_H_
#define UNIT_H_

#include "RotateObject.h"
#include "Directions.h"


class GridBlock;


class Unit : public RotateObject{
public:
	static Unit* create(const ObjType&, const Dir&, GLshort, 
						const Team&, const HP&, const TU&);
	virtual ~Unit();
	
	//-- GENERAL --//
	GridBlock* getBlock() const;	
	void setBlock(GridBlock*);	
	
	bool isUnit();
	const Team& getTeam() const;
					
	//--- ACTION ---//
	GLshort update();	
	void calculateAction(GLshort, GridBlock*);	
	void act(GLshort);	
	
	//---- DRAW ----//
	virtual void draw(bool);
	
	//--- COMBAT ---//
	void shoot();
	
	//-- PATHING --//
	bool isMoving() const;
	
	//--- SIGHT ---//	
	bool hasBeenSeen();
	void updateSight(vector<Unit*>&);
	
	//--- TURN ---//	
	void newTurn();
		
private:	
	Unit(const ObjType&, const Dir&, GLshort, 
		 const Team&, const HP&, const TU&);
	
	//-- GENERAL --//
	GridBlock* currBlock;	
	GridBlock* goalBlock;	
	GLshort state;
	bool looking;
	
	//-- PATHING --//
	Directions* directions;
	GLshort stepsLeft;
	
	GLshort move();
	void stop();
	
	//--- SIGHT ---//
	set<Unit*> sees;
	set<Unit*> seenBy;
	bool beenSeen;
	
	bool canSee(const Unit*) const;	
	GLfloat getSightAngle(GridBlock*) const;
	GLshort look();
		
	//--- STATS ---//	
	Team team;
	TU maxTU;
	TU currTU;
		
	//---- USE ----//
	GLshort use();
};

#endif


