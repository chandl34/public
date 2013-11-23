/*
 *  GridItemContainer.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridItemContainer.h"

#include "Heap.h"
#include "Item.h"
#include "RangeNode.h"


GridItemContainer::GridItemContainer(GLshort x, GLshort y) 
: _itemSlot(x)
, _size(x, y)
{
	for(GLshort i = 0; i < x; ++i){
		for(GLshort j = 0; j < y; ++j)
			_itemSlot[i].push_back(GridItemSlot(i, j));
	}		
}


bool GridItemContainer::canFit(Item* it, GLshort x, GLshort y, const Size2d<GLshort>& s)
{
	if(x < 0 || x + s[X] > _size[X])
		return false;
	if(y < 0 || y + s[Y] > _size[Y])
		return false;
	
	Item* item;
	for(GLshort i = x; i < x + s[X]; ++i){
		for(GLshort j = y; j < y + s[Y]; ++j){
			if(!_itemSlot[i][j].isEnabled())
				return false;
			
			item = _itemSlot[i][j].getItem();
			if(item != NULL)
				return false;
		}		
	}		
	return true;
}

bool GridItemContainer::setItem(Item* it, GLshort x, GLshort y)
{
	if(it == NULL){
		Item* temp = getItem(x, y);
		Size2d<GLshort> s(temp->getSize(X) / 20, temp->getSize(Y) / 20);		
		
		setItemSub(it,
				   _itemSlot[x][y].getBase(X), 
				   _itemSlot[x][y].getBase(Y), 
				   s);
		return true;
	}
	else{
		Size2d<GLshort> s(it->getSize(X) / 20, it->getSize(Y) / 20);
		
		// Sort all possible base locations
		Heap heap(true);	
		Coord2d<GLshort> orig(x, y);
		for(GLshort i = 1 - s[X]; i <= 0; ++i){			
			for(GLshort j = 1 - s[Y]; j <= 0; ++j)
				heap.push(new RangeNode(Coord2d<GLshort>(x + i, y + j), orig));
		}
		
		// Find nearest location where item can fit
		bool found = false;
		while(!heap.isEmpty()){
			RangeNode* rn = (RangeNode*)heap.pop();
			if(!found){
				if(canFit(it, rn->getCoord(X), rn->getCoord(Y), s)){
					setItemSub(it, rn->getCoord(X), rn->getCoord(Y), s);
					found = true;
				}
			}	
			delete rn;
		}				
		return found;
	}	
}

void GridItemContainer::setItemSub(Item* it, GLshort x, GLshort y, const Size2d<GLshort>& s)
{
	for(GLshort i = x; i < x + s[X]; ++i){
		for(GLshort j = y; j < y + s[Y]; ++j)
			_itemSlot[i][j].setItem(it, Coord2d<GLshort>(x, y));
	}
}

Item* GridItemContainer::getItem(GLshort x, GLshort y)
{
	return _itemSlot[x][y].getItem();
}

void GridItemContainer::getAllItems(ItemMap& is, bool null)
{
	Item* item;
	for(GLshort i = 0; i < _size[X]; ++i){
		for(GLshort j = 0; j < _size[Y]; ++j){
			item = _itemSlot[i][j].getItem();
			if(item != NULL && _itemSlot[i][j].isBase()){
				is[item] = Coord2d<GLshort>(_itemSlot[i][j].getBase(X),
											_itemSlot[i][j].getBase(Y));
				if(null)
					setItem(NULL, i, j);
			}
		}
	}
}

void GridItemContainer::getBase(GLshort& x, GLshort& y)
{
	GLshort oX = x;
	GLshort oY = y;
	
	x = _itemSlot[oX][oY].getBase(X);
	y = _itemSlot[oX][oY].getBase(Y);
}

GLshort GridItemContainer::getSize(GLshort i)
{
	return _size[i];
}

void GridItemContainer::enable(bool e, GLshort x, GLshort y)
{
	_itemSlot[x][y].enable(e);
}

Item* GridItemContainer::findCombine(Item* it, Coord2d<GLshort>& loc)
{
	for(GLshort i = 0; i < _size[X]; ++i){
		for(GLshort j = 0; j < _size[Y]; ++j){
			Item* tempItem = _itemSlot[i][j].getItem();
			if(it->canCombine(tempItem)){
				loc[X] = i;
				loc[Y] = j;
				return tempItem;
			}
		}
	}
	return NULL;
}


//---- DRAW ----//	
void GridItemContainer::draw(bool step)
{
	for(GLshort i = 0; i < _size[X]; ++i){
		for(GLshort j = 0; j < _size[Y]; ++j)
			_itemSlot[i][j].draw(step);
	}
}

//---- IO ----//	
void GridItemContainer::saveData(ofstream& file, GLshort cont)
{
	Item* item;
	for(GLshort i = 0; i < _size[X]; ++i){
		for(GLshort j = 0; j < _size[Y]; ++j){
			item = _itemSlot[i][j].getItem();
			if(item != NULL && _itemSlot[i][j].isBase()){
				file << "i " << cont << " ";
				file << i << " " << j << " ";
				item->saveData(file);
				file << "\n";
			}				
		}
	}
}
