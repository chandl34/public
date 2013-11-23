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

#include "Inventory.h"
#include "Memory.h"
#include "Path.h"
#include "View.h"

class GridBlock;
class Hit;
class ItemSlotType;
class LevelMap;
class Team;
class Unit;


typedef list<Unit*> UnitList;
typedef set<Unit*> UnitSet;
//typedef pair<Unit*, GridBlock*> UnitBlock;


// Combat-related constants
const double IGNORE_RATIO = 0.75;

struct ViewArgs{
	Unit* unit;
	const GridBlock* gb;
	Dir dir;
	GLshort reason;
	bool kneeling;
};


class Unit : public RotateObject{
protected:
	Unit(const ObjType&, const Dir&, GLshort, 
		 const HP&, const TU&);
	
public:
	static Unit* create(const ObjType&, GLshort, 
						const Dir&, GLshort, 
						const HP&, const TU&);
	virtual ~Unit();
	
	//-- GENERAL --//
	double getGlobalLoc(GLshort, const Dimension&, GLshort = -1) const;
	bool isUnit() const;
	
	GLshort getFactionID() const;
	Team* getTeam() const;
	void setTeam(Team*);	
	
	GridBlock* getBlock();	
	void setBlock(GridBlock*);	
	
	bool isTouchingIcon(const Coord2d<GLshort>&);
	void setIconOffset(double, double);
	
	//-- HIT DETECTION --//
	bool detectHit(const Ray&, Hit&);
	
	//--- ACTION ---//
	bool isIdle() const;
	void clearData();
	
	GLshort update(UnitList&);	
	void calculateAction(GLshort, GridBlock*);	
	void act(GLshort);	
	
	bool isKneeling() const;
	void changeStance(UnitList* enemyTeam);
	
	//--- COMBAT ---//
	void takeDamage(GLshort, GLshort);
	bool canAim();
	void aim(GLshort, GLshort, GLshort, GridBlock* = NULL);	
	double getEffectiveCTH() const;
	
	//---- DRAW ----//
	virtual void draw(bool, TexAttr* = NULL);
	void drawInventory(bool);
	void drawPath(bool);
	void drawView(bool);
	void drawIcon(bool);
	
	//--- SIGHT ---//	
	bool canSee(Unit*);	
	bool canSee(GridBlock*);
	bool couldSee(GridBlock*);	
	bool hasBeenSeenBy(Unit*) const;
	bool hasBeenSeen() const;
	bool inViewScope(GridBlock*);
	
	void hideUnseen();
	
	void updateSight(UnitList&, GLshort, GLshort);
	void removeDead(Unit*);
	
	void setBackupView(View*);
	
	void addLOS();	
	void removeLOS();
	
	//--- STATS ---//	
	GLshort getTU() const;
	void setTU(GLshort);
	GLshort getMaxTU() const;	
	GLshort getEstimateTU() const;
	
	//--- INVENTORY ---//
	ItemContainerType* getContainer(GLshort);
	Item* getEquippedItem();
	
	bool moveItem(ItemContainerType*, Coord2d<GLshort>&,
				  ItemContainerType*, Coord2d<GLshort>&);
	bool combine(Item*, Item*, bool);
	bool mustReload();
	
	//---- TOGGLE ----//
	GridBlock* findToggleBlock(GridBlock*, GLshort);
	
	//--- TURN ---//
	virtual void newTurn();
	
	//---- AI ----//	
	static MemoryMap* getUnhandledMemories();
	
	//---- IO ----//	
	void saveData(ofstream&);
	
protected:	
	//-- GENERAL --//
	GridBlock* _currBlock;	
	GridBlock* _goalBlock;	
	GLshort _state;
	bool _kneeling;
	Model* _bodyPart[3];
	
	Icon _uiIcon;
	
	bool _threadActive;
	
	void updateGraphics();
	
	//--- ACTION ---//
	void stop();
	
	//--- COMBAT ---//
	double _chanceToHit;
	GLshort _targetSection;
	
	void shoot();
	void throwItem(GLshort);
	GridBlock* findThrowBlock();
	void randomizeShot(Vertex&, Vertex&);
	void findCTH(Unit* = NULL);
	
	
	//-- PATHING --//
	Path _path;
	GLshort _stepsLeft;
	bool _hadToOpenDoor;
	
	GLshort move(UnitList&);
	void setDir(GLshort);
	
	//--- SIGHT ---//
	View* _view;
	View* _backupView;
	UnitSet _sees;
	UnitSet _seenBy;
	UnitSet _beenSeenBy;
	
	static MemoryMap _unhandled;
	
	bool couldSee(Unit*);	
	void look(UnitList&);
	
	void findLOSThreaded();
	
	//--- STATS ---//	
	Team* _team;
	GLshort _maxTU;
	GLshort _currTU;
	GLshort _estimateTU;
	GLshort _reserveTU;
	
	GLshort getEffectiveTU() const;
	
	//--- INVENTORY ---//
	Inventory _inventory;
	
	void reload();
	
	//---- TOGGLE ----//
	void toggle();
};

#endif


