/*
 *  Unit.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/20/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Unit.h"

#include "Bullet.h"
#include "EnemyUnit.h"
#include "GridBlock.h"
#include "Hit.h"
#include "Model.h"
#include "Team.h"

#include "ImageStorage.h"
#include "ModelStorage.h"


MemoryMap Unit::_unhandled;


Unit* Unit::create(const ObjType& ot, GLshort fid, 
				   const Dir& d, GLshort is, 
				   const HP& mhp, const TU& mtu)
{
	Unit* u;
	
	if(fid == PLAYER)
		u = new Unit(ot, d, is, mhp, mtu);	
	else 
		u = new EnemyUnit(ot, d, is, mhp, mtu);
	u->updateGraphics();
	
	return u;
}

Unit::Unit(const ObjType& ot, const Dir& d, GLshort is, 
		   const HP& mhp, const TU& mtu) 
: RotateObject(ot, d, is, mhp)
, _maxTU(mtu)
, _currTU(mtu)
{
	//-- GENERAL --//		
	_currBlock = NULL;
	_goalBlock = NULL;
	_state = IDLE;
	_kneeling = false;
	_threadActive = false;
	_currAnim = IDLE_ANIM;
	_uiIcon.setImage(ImageStorage::getUIImage(UNIT_ICON));
	
	//--- COMBAT ---//
	_targetSection = HEAD;
	
	//-- PATHING --//
	_stepsLeft = 0;
	_hadToOpenDoor = false;
	
	//--- SIGHT ---//
	_view = new View();
	_backupView = NULL;
	
	//--- STATS ---//	
	_estimateTU = 0;
	_reserveTU = 0;
}

Unit::~Unit()
{	
	// todo:  add something about animation, etc here later...
	
	if(_currBlock != NULL){
		//--- AI ---//
		_unhandled.erase(this);
		
		//--- INVENTORY ---//
		_currBlock->addOverlay(_image);
		_currBlock->setUnit(NULL);
		_inventory.dropAll(_currBlock);
		
		//--- SIGHT ---//
		if(getFactionID() == PLAYER)
			removeLOS();
	}
	
	delete _view;
}


//-- GENERAL --//
double Unit::getGlobalLoc(GLshort c, const Dimension& m, GLshort sect) const
{
	if(sect == -1)
		return Object::getGlobalLoc(c, m);
	return _bodyPart[sect]->getRelativeLoc(c, m) + getCoord3D(c);
}

bool Unit::isUnit() const
{
	return true;
}

GLshort Unit::getFactionID() const
{
	return _team->getFactionID();
}

Team* Unit::getTeam() const
{
	return _team;
}

void Unit::setTeam(Team* team)
{
	_team = team;
}

GridBlock* Unit::getBlock()
{
	return _currBlock;
}

void Unit::setBlock(GridBlock* gb)
{	
	_currBlock = gb;
	setCoord3D(gb->getCoord3D(X), 
			   gb->getCoord3D(Y), 
			   gb->getCoord3D(Z));
}

bool Unit::isTouchingIcon(const Coord2d<GLshort>& p)
{
	return _uiIcon.isTouching(p);
}

void Unit::setIconOffset(double x, double y)
{
	_uiIcon.setOffset(x, y);
}

void Unit::updateGraphics()
{
	_animSet.setAnimation(AnimDesc(_currAnim, _dir));
	_image = _animSet.getNextImage();
	_model = ModelStorage::getRotateModel(_objectType, _kneeling, Dir(_dir));
	for(GLshort i = 0; i < BODY_PARTS; ++i)
		_bodyPart[i] = ModelStorage::getRotateModel(ObjType(i), _kneeling, Dir(_dir));
	resetCoord3D();
}


//-- HIT DETECTION --//
bool Unit::detectHit(const Ray& r, Hit& hit)
{
	double time = hit.getTimeLeft();
	GLshort best = -1;
	for(GLshort i = 0; i < BODY_PARTS; ++i){
		if(_bodyPart[i]->detectHit(r, _ray.getLoc(), hit)){
			if(hit.getTimeLeft() < time || time < 0){
				time = hit.getTimeLeft();
				best = i;
			}
		}
	}
	
	if(best >= 0){
		hit.setSectionHit(best);
		hit.setObjectHit(this);
		return true;
	}	
	return false;
}


//--- STATS ---//	
GLshort Unit::getTU() const
{
	return _currTU;
}

void Unit::setTU(GLshort tu)
{
	_currTU = tu;
}

GLshort Unit::getMaxTU() const
{
	return _maxTU;
}

GLshort Unit::getEstimateTU() const
{
	return _estimateTU;
}

GLshort Unit::getEffectiveTU() const
{
	if(getFactionID() != PLAYER)
		return _currTU - _reserveTU;
	return _currTU;
}


//--- INVENTORY ---//
ItemContainerType* Unit::getContainer(GLshort i)
{
	return _inventory.getContainer(i);
}

Item* Unit::getEquippedItem()
{
	return _inventory.getEquippedItem();
}


//--- TURN ---//
void Unit::newTurn()
{
	_currTU = _maxTU;
	hideUnseen();
}
