/*
 *  InfiniteItemContainer.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/8/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "InfiniteItemContainer.h"

#include "Item.h"

#include "HitTest.h"



InfiniteItemContainer::~InfiniteItemContainer(){
	for(set<ItemPtr>::iterator iter = _item.begin(); iter != _item.end(); ++iter)
		delete iter->_item;
}


//--- GENERAL ---//
bool InfiniteItemContainer::setItem(Item* it, GLshort x, GLshort y){
	// Remove
	if(it == NULL){
		Item* tempItem = getItem(x, y);
		if(tempItem == NULL){
			printf("ERROR:  Could not find item at location!\n");
			return false;
		}
		_item.erase(tempItem);
	}
	else{
		_item.insert(it);
		//pair<set<ItemPtr>::iterator, bool> b = item.insert(it);
		//if(b.second == false)
		//	cout << "did not push to set\n";
	}
	
	return true;
}

Item* InfiniteItemContainer::getItem(GLshort x, GLshort y){
	Coord2d<GLshort> p(x, y);
	for(set<ItemPtr>::iterator iter = _item.begin(); iter != _item.end(); ++iter){
		if(iter->_item->isTouching(p))
			return iter->_item;
	}
	return false;
}

void InfiniteItemContainer::getAllItems(ItemMap& is, bool null){
	for(set<ItemPtr>::iterator iter = _item.begin(); iter != _item.end(); ++iter)
		is[(*iter)._item] = Coord2d<GLshort>(0, 0);
	if(null)
		_item.clear();
}

void InfiniteItemContainer::resetOffsets(double x, double y){
	for(set<ItemPtr>::iterator iter = _item.begin(); iter != _item.end(); ++iter){
		iter->_item->setOffset(x, y);
		x += iter->_item->getSize(X);
	}
}

Item* InfiniteItemContainer::findCombine(Item* it, Coord2d<GLshort>& loc){
	return NULL;	// disabled this function, because auto-reloading should not happen from the ground
}

bool InfiniteItemContainer::isEmpty() const{
	return _item.empty();
}


//---- DRAW ----//	
void InfiniteItemContainer::draw(bool step){
	for(set<ItemPtr>::iterator iter = _item.begin(); iter != _item.end(); ++iter)
		iter->_item->draw(step);
}


//---- IO ----//	
void InfiniteItemContainer::saveData(ofstream& file, const Coord2d<GLshort>* coord)
{
	for(set<ItemPtr>::iterator iter = _item.begin(); iter != _item.end(); ++iter){
		file << "i ";
		if(coord != NULL)
			file << (*coord)[X] << " " << (*coord)[Y] << " ";
		iter->_item->saveData(file);
		file << "\n";
	}
}
