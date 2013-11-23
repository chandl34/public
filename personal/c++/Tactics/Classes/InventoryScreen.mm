/*
 *  InventoryScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/3/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "InventoryScreen.h"

#include "Button.h"
#include "GridBlock.h"
#include "Icon.h"
#include "Image.h"
#include "Item.h"
#include "ItemContainerType.h"
#include "LevelMap.h"
#include "StandardMenu.h"

#include "ImageStorage.h"


InventoryScreen::InventoryScreen() 
: SubScreen(false)
, _itemInfo(35, 125, 250)
, _unitInfo(35, 125, 250)
{		
	printf("Building Inventory Screen...\n");
	
	Image* img = new Image(Size2d<GLshort>(SUBSCREEN_SIZE[X], 
										   SUBSCREEN_SIZE[Y]), 
						   0);
	ImageStorage::addImage(img);
	_background.setImage(img);
	
	// Stat display background
	img = new Image(Size2d<GLshort>(100, 120), 0);
	ImageStorage::addImage(img);
	_statsBackground.setImage(img);	
	_statsBackground.setOffset(_background.getOffset(X) + 10, 
							   _background.getOffset(Y) + 100);
	
	// Unit picture
	img = new Image(Size2d<GLshort>(40, 120), 0);
	ImageStorage::addImage(img);
	_unitBackground.setImage(img);	
	_unitBackground.setOffset(_background.getOffset(X) + 170, 
							  _background.getOffset(Y) + 100);
	
	// Weapon
	Button* b = new Button(ImageStorage::getItemSlotImage(IS_2_4), 
						   Coord2d<double>(_background.getOffset(X) + 120, 
										   _background.getOffset(Y) + 120));	
	_itemSlot.addSelectable(b);
	
	
	// Armor
	StandardMenu* sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 220, 
														_background.getOffset(Y) + 100),
										Size2d<GLshort>(1, 3),
										Size2d<GLshort>(40, 40));
	for(GLshort j = 0; j < 3; ++j){
		b = sm->getButton(j);
		b->setImage(ImageStorage::getItemSlotImage(IS_2_2));
	}
	
	_itemSlot.addSelectable(sm);
	
	
	// Left Holster
	sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 270, 
										  _background.getOffset(Y) + 165),
						  Size2d<GLshort>(2, 2),
						  Size2d<GLshort>(20, 20));
	for(GLshort j = 0; j < 4; ++j){
		b = sm->getButton(j);
		b->setImage(ImageStorage::getItemSlotImage(IS_1_1));
	}
	
	b = sm->getButton(1);
	b->enable(false);
	
	_itemSlot.addSelectable(sm);
	
	// Left Pocket
	sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 270, 
										  _background.getOffset(Y) + 115),
						  Size2d<GLshort>(2, 2),
						  Size2d<GLshort>(20, 20));
	for(GLshort j = 0; j < 4; ++j){
		b = sm->getButton(j);
		b->setImage(ImageStorage::getItemSlotImage(IS_1_1));
	}
	
	_itemSlot.addSelectable(sm);
	
	
	// Right Holster
	sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 320, 
										  _background.getOffset(Y) + 165),
						  Size2d<GLshort>(2, 2),
						  Size2d<GLshort>(20, 20));
	for(GLshort j = 0; j < 4; ++j){
		b = sm->getButton(j);
		b->setImage(ImageStorage::getItemSlotImage(IS_1_1));
	}
	
	b = sm->getButton(0);
	b->enable(false);
	
	_itemSlot.addSelectable(sm);
	
	// Right Pocket
	sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 320, 
										  _background.getOffset(Y) + 115),
						  Size2d<GLshort>(2, 2),
						  Size2d<GLshort>(20, 20));
	for(GLshort j = 0; j < 4; ++j){
		b = sm->getButton(j);
		b->setImage(ImageStorage::getItemSlotImage(IS_1_1));
	}
	
	_itemSlot.addSelectable(sm);
	
	
	// Backpack
	sm = new StandardMenu(Coord2d<double>(_background.getOffset(X) + 370, 
										  _background.getOffset(Y) + 120),
						  Size2d<GLshort>(3, 4),
						  Size2d<GLshort>(20, 20));
	for(GLshort j = 0; j < 12; ++j){
		b = sm->getButton(j);
		b->setImage(ImageStorage::getItemSlotImage(IS_1_1));
	}
	
	_itemSlot.addSelectable(sm);
	
	
	// Ground buttons
	// Left button
	img = new Image(Size2d<GLshort>(20, 80), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 10, 
										_background.getOffset(Y) + 10));
	_itemSlot.addSelectable(b);
	
	// Ground
	img = new Image(Size2d<GLshort>(380, 80), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 30, 
										_background.getOffset(Y) + 10));
	_itemSlot.addSelectable(b);
	
	// Right button
	img = new Image(Size2d<GLshort>(20, 80), 0);
	ImageStorage::addImage(img);
	b = new Button(img, Coord2d<double>(_background.getOffset(X) + 410, 
										_background.getOffset(Y) + 10));
	_itemSlot.addSelectable(b);
}


//-- GENERAL --//
void InventoryScreen::open()
{
	LevelMap* levelMap = LevelMap::getInstance();
	
	Unit* u = levelMap->getSelectedUnit();
	_unitInfo.update(u);
	
	// Set item coordinates
	Item* item;	
	ItemContainerType* cont;
	Button* b;
	
	// Weapon
	item = u->getEquippedItem();
	if(item != NULL){
		b = _itemSlot.getButton(0, 0);
		// Place in middle
		item->setOffset(b->getOffset(X) + (b->getSize(X) - item->getSize(X)) / 2,
						b->getOffset(Y) + (b->getSize(Y) - item->getSize(Y)) / 2);		
	}
	
	// Pockets and Holsters and Backpack
	for(GLshort c = 1; c < UNIT_CONTAINERS; ++c){
		cont = u->getContainer(c);		
		for(GLshort i = cont->getSize(X) - 1; i >= 0; --i){		
			for(GLshort j = cont->getSize(Y) - 1; j >= 0; --j){			
				item = cont->getItem(i, j);
				if(item != NULL){ 
					b = _itemSlot.getButton(c, i + j * cont->getSize(X));
					item->setOffset(b->getOffset(X), b->getOffset(Y));
				}
			}
		}
	}
	
	// Ground
	GridBlock* gb = u->getBlock();
	cont = gb->getContainer();
	b = _itemSlot.getButton(GROUND_CONTAINER, 0);
	cont->resetOffsets(b->getOffset(X), b->getOffset(Y));
	
	
	_sItem = NULL;
	_sContainer = NULL;
}

void InventoryScreen::close()
{
	//return _levelMap;
}


//---- DRAW ----//
void InventoryScreen::draw(bool step)
{	
	glColor4f(0.8, 0.8, 0.8, 1.0);
	_background.draw(step);
	
	glColor4f(0.9, 0.9, 0.9, 1.0);
	_statsBackground.draw(step);
	_unitBackground.draw(step);
	
	glColor4f(0.0, 0.0, 0.0, 1.0);
	if(_sItem == NULL)
		_unitInfo.draw(step);
	else
		_itemInfo.draw(step);
	
	glColor4f(1.0, 1.0, 1.0, 1.0);	
	_itemSlot.draw(step);	
	
	LevelMap* levelMap = LevelMap::getInstance();
	Unit* u = levelMap->getSelectedUnit();
	u->drawInventory(step);
	
	GridBlock* gb = u->getBlock();
	gb->drawItems(step);
}


//---- TOUCH ----//
void InventoryScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	_itemSlot.push(t, p);
}

void InventoryScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	_itemSlot.move(t, p);
}

bool InventoryScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(_itemSlot.release(t, p)){			
		GLshort s = _itemSlot.getSelected();	
		GLshort tempSlot = _itemSlot.getSelectedOption();
		
		ItemContainerType* tempCont = NULL;
		Coord2d<GLshort> tempLoc;
		Item* tempItem = NULL;
		
		LevelMap* levelMap = LevelMap::getInstance();
		Unit* u = levelMap->getSelectedUnit();
		GridBlock* gb = u->getBlock();
		
		if(s < UNIT_CONTAINERS){
			tempCont = u->getContainer(s);
			tempLoc[X] = tempSlot % tempCont->getSize(X);
			tempLoc[Y] = tempSlot / tempCont->getSize(X);
			tempItem = tempCont->getItem(tempLoc[X], tempLoc[Y]);
		}
		else if(s == GROUND_CONTAINER){
			tempCont = gb->getContainer();
			tempLoc = p;
			tempItem = tempCont->getItem(tempLoc[X], tempLoc[Y]);
		}
		else{
			cout << "Touched one of the ground shift buttons (unimplemented)" << endl;
		}
		
		if(_sItem == NULL){
			if(tempItem != NULL){
				cout << "Selected: " << tempItem->getName() << endl;
				_sLoc = tempLoc;
				_sContainer = tempCont;
				_sItem = tempItem;
				_itemInfo.update(_sItem);
			}
		}
		else if(tempCont != NULL){
			if(tempItem != NULL){
				if(tempItem == _sItem){
					cout << "Deselected: " << _sItem->getName() << endl;
					_sContainer = NULL;
					_sItem = NULL;
				}				
				else{
					if(tempItem->canCombine(_sItem)){
						// Charge pickup cost if item going from ground to inventory or vice versa
						bool pickUp	= _sContainer == gb->getContainer() || tempCont == gb->getContainer();
						pickUp = pickUp && _sContainer != tempCont;
						
						if(u->combine(tempItem, _sItem, pickUp)){
							printf("Fully combined item\n");
							delete _sItem;
							_sContainer->setItem(NULL, _sLoc[X], _sLoc[Y]);;
							open();	// basically a reset
						}
						else{
							printf("Partially combined item\n");
							_itemInfo.update(_sItem);	
						}
					}
					else{			
						cout << "Selected: " << tempItem->getName() << endl;	
						_sLoc = tempLoc;
						_sContainer = tempCont;
						_sItem = tempItem;
						_itemInfo.update(_sItem);
					}
				}	
			}
			else{ 
				if(u->moveItem(_sContainer, _sLoc, tempCont, tempLoc)){
					printf("Item placed\n");
					open();	// basically a reset
				}
				else
					cout << _sItem->getName() << " can't move there" << endl;
			}
		}
	}
	
	return false;
}
