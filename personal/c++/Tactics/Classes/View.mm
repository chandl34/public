/*
 *  View.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 9/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "View.h"

#include "GridBlock.h"
#include "Unit.h"

#include "HitTest.h"
#include "ImageStorage.h"
#include "LevelMap.h"
#include "Math.h"
#include "Options.h"


list<Coord2d<GLshort> > View::_viewTemplate;
Coord2d<GLshort> View::_templateBase;


View::View()
{
	if(_viewTemplate.empty()){
		LevelMap* levelMap = LevelMap::getInstance();
		GridBlock* base = levelMap->getBlockByIso(20, 20);
		BlockSet bs;
		find360Scope(bs, base, SIGHT_RANGE[FRONTAL]);
		
		for(BlockSet::iterator iter = bs.begin(); iter != bs.end(); ++iter)
			_viewTemplate.push_back(Coord2d<GLshort>((*iter)->getCoordPath(X),
																  (*iter)->getCoordPath(Y)));		
		_templateBase[X] = base->getCoordPath(X);
		_templateBase[Y] = base->getCoordPath(Y);
	}
}


//--- GENERAL ---//
void View::findLOS(const GridBlock* gb, Dir dir, GLshort updateReason, bool kneeling)
{
	double timer = [[NSDate date] timeIntervalSince1970];
	
	// MOVED requires new 360 scope
	if(updateReason == MOVED){
		//	double timer2 = [[NSDate date] timeIntervalSince1970];
		_viewLOS[VIEWABLE].clear();
		_viewLOS[DOOR_VIEW].clear();
		
		// Find all viewable blocks		
		GLshort diff[2];
		for(GLshort i = 0; i < 2; ++i)
			diff[i] = _templateBase[i] - gb->getCoordPath(i);
		
		GridBlock* temp;
		LevelMap* levelMap = LevelMap::getInstance();		
		for(list<Coord2d<GLshort> >::iterator iter = _viewTemplate.begin(); iter != _viewTemplate.end(); ++iter){
			temp = levelMap->getBlockByPath((*iter)[X] - diff[X], 
													  (*iter)[Y] - diff[Y]);
			if(temp != NULL){
				_viewLOS[VIEWABLE][temp] = FULL_LOS;
				_viewLOS[DOOR_VIEW][temp] = FULL_LOS;			
			}
		}			
		//	timer2 = [[NSDate date] timeIntervalSince1970] - timer2;
		//	printf("Full scope found in %f seconds\n", timer2);
		
		//	double timer4 = [[NSDate date] timeIntervalSince1970];	
		
		
		for(BlockLOS::iterator iter = _viewLOS[VIEWABLE].begin(); iter != _viewLOS[VIEWABLE].end(); ++iter)
			findBlockLOS(iter->first, gb, WALLS_AND_DOORS, kneeling);
		
		//	timer4 = [[NSDate date] timeIntervalSince1970] - timer4;
		//	printf("LOS found in %f seconds\n", timer4);
	}
	
	// Door change required new view through doors.  Same 360 scope and vision cone.
	else if(updateReason == MAP_CHANGED){		
		for(BlockLOS::iterator iter = _viewLOS[DOOR_VIEW].begin(); iter != _viewLOS[DOOR_VIEW].end(); ++iter)
			_viewLOS[DOOR_VIEW][iter->first] = FULL_LOS;
		
		for(BlockLOS::iterator iter = _viewLOS[VIEWABLE].begin(); iter != _viewLOS[VIEWABLE].end(); ++iter)
			findBlockLOS(iter->first, gb, DOORS_ONLY, kneeling);
	}
	
	// Stance change requires new view through windows.  Same 360 scope and vision cone.
	else if(updateReason == STANCE_CHANGED){
		for(BlockLOS::iterator iter = _viewLOS[VIEWABLE].begin(); iter != _viewLOS[VIEWABLE].end(); ++iter)
			_viewLOS[VIEWABLE][iter->first] = FULL_LOS;
		
		for(BlockLOS::iterator iter = _viewLOS[VIEWABLE].begin(); iter != _viewLOS[VIEWABLE].end(); ++iter)
			findBlockLOS(iter->first, gb, WALLS_ONLY, kneeling);
		
		// Copy LOS of viewable blocks
		for(BlockLOS::iterator iter = _viewLOS[VIEWED].begin(); iter != _viewLOS[VIEWED].end(); ++iter)
			_viewLOS[VIEWED][iter->first] = _viewLOS[VIEWABLE][iter->first];
	}
	
	// TURNED and MOVED require new vision cone
	if(updateReason < MAP_CHANGED){		
		//double timer3 = [[NSDate date] timeIntervalSince1970];	
		// Find all viewed blocks
		GLshort periIncr = 20;					// 5 * 20 = 100 degrees in each direction = full view scope
		GLshort frontalIncr = 12;				// 5 * 12 = 60 degrees in each direction = frontal view scope
		
		Size2d<GLshort> sightRange(SIGHT_RANGE[FRONTAL], SIGHT_RANGE[PERIPHERAL]);
		Size2d<GLshort> viewIncr(frontalIncr, periIncr);
		double angle = M_PI / 36;			// 5 degree change
		BlockSet viewedBlock;
		findScope(viewedBlock, gb, dir, sightRange, viewIncr, angle);
		//timer3 = [[NSDate date] timeIntervalSince1970] - timer3;
		//printf("View scope found in %f seconds\n", timer3);
		
		// Copy LOS of viewable blocks
		_viewLOS[VIEWED].clear();
		for(BlockSet::iterator iter = viewedBlock.begin(); iter != viewedBlock.end(); ++iter)
			_viewLOS[VIEWED][*iter] = _viewLOS[VIEWABLE][*iter];
	}
	
	if(SHOW_LOS){
		// Set indicators
		_view.clear();
		for(BlockLOS::iterator iter = _viewLOS[VIEW_360].begin(); iter != _viewLOS[VIEW_360].end(); ++iter)
			_view.push_back(Icon(ImageStorage::getSightIndicatorImage(getLOS(VIEW_360, iter->first)), iter->first->getOffset()));
	}
	
	timer = [[NSDate date] timeIntervalSince1970] - timer;
	printf("View found in %f seconds\n", timer);
}

void View::findBlockLOS(const GridBlock* targ, const GridBlock* orig, GLshort testObj, bool kneeling)
{	
	LevelMap* levelMap = LevelMap::getInstance();
	for(GLshort i = 0; i < 2; ++i){
		//enum{WALLS_ONLY, DOORS_ONLY, WALLS_AND_DOORS};
		//enum{VIEWED, VIEWABLE, DOOR_VIEW};
		GLshort test; 
		GLshort los = FULL_LOS;
		
		if(testObj != DOORS_ONLY){
			test = VIEWABLE;
			los = targ->viewBlocked(i, WALLS_ONLY);		
		}
		
		if(testObj != WALLS_ONLY && los == FULL_LOS){
			test = DOOR_VIEW;
			los = targ->viewBlocked(i, DOORS_ONLY);				
		}
		
		if(los == FULL_LOS)
			continue;
		
		GLshort side = i;
		GLshort otherSide = (side + 1) % 2;		
		
		double fDim[2][2];
		double fSlope[2];
		double fConst[2];
		
		for(GLshort j = 0; j < 2; ++j){
			fDim[0][j] = targ->getCoordPath(j) - orig->getCoordPath(j) - 0.5;
			fDim[1][j] = fDim[0][j];
		}
		++fDim[1][otherSide];
		
		// Find line formulas
		for(GLshort j = 0; j < 2; ++j){
			fSlope[j] = fDim[j][otherSide] / fDim[j][side];
			fConst[j] = -orig->getCoordPath(side) * fSlope[j] + orig->getCoordPath(otherSide);
		}
		
		// Get distance between target and origin
		Vertex origVert(orig->getCoordPath(X), orig->getCoordPath(Y));
		Vector toTarg(Vertex(targ->getCoordPath(X), targ->getCoordPath(Y)), origVert);
		double size = toTarg.size();
		
		GLshort edgeLOS1 = -1;
		GLshort edgeLOS2 = -1;
		
		// Remove LOS from blocks between two lines
		for(BlockLOS::iterator iter = _viewLOS[test].begin(); iter != _viewLOS[test].end(); ++iter){
			if(_viewLOS[VIEWABLE][iter->first] < los && _viewLOS[DOOR_VIEW][iter->first] < los){				
				// Check if this block is beyond the occluding object
				Vector thisVect(Vertex(iter->first->getCoordPath(X), iter->first->getCoordPath(Y)), origVert);	
				double thisSize = thisVect.size();
				if((iter->first == targ && orig->getCoordPath(side) < targ->getCoordPath(side)) || size < thisSize){					
					GLshort comp1 = compare(iter->first->getCoordPath(otherSide), 
													fSlope[0] * iter->first->getCoordPath(side) + fConst[0]);	
					if(comp1 != -1){								
						GLshort comp2 = compare(iter->first->getCoordPath(otherSide), 
														fSlope[1] * iter->first->getCoordPath(side) + fConst[1]);
						if(comp2 != 1){
							GLshort thisLOS;
							if(comp1 == 0){
								if(edgeLOS1 == -1){
									GLshort coord[2];
									for(GLshort j = 0; j < 2; ++j)
										coord[j] = targ->getCoordPath(j);
									--coord[otherSide];				
									
									GridBlock* compBlock = levelMap->getBlockByPath(coord[X], coord[Y]);
									if(compBlock != NULL){
										edgeLOS1 = compBlock->viewBlocked(side, WALLS_AND_DOORS);
										
										// Check for corner
										if(edgeLOS1 != NO_LOS && side == LEFT_SIDE){
											++coord[otherSide];
											if(orig->getCoordPath(otherSide) >= targ->getCoordPath(otherSide)){	// looks like   																		   
												if(orig->getCoordPath(side) < targ->getCoordPath(side))				//		      |     
													--coord[side];																	//		   ___|___  						
											}		
											else if(orig->getCoordPath(side) >= targ->getCoordPath(side))
												--coord[side];
											
											compBlock = levelMap->getBlockByPath(coord[X], coord[Y]);
											if(compBlock != NULL)	
												edgeLOS1 = max(edgeLOS1, compBlock->viewBlocked(otherSide, WALLS_AND_DOORS));	
										}
										
										edgeLOS1 = min(edgeLOS1, los);
									}
								}				
								
								thisLOS = edgeLOS1;
							}
							else if(comp2 == 0){		
								if(edgeLOS2 == -1){
									GLshort coord[2];
									for(GLshort j = 0; j < 2; ++j)
										coord[j] = targ->getCoordPath(j);
									++coord[otherSide];		
									
									GridBlock* compBlock = levelMap->getBlockByPath(coord[X], coord[Y]);
									if(compBlock != NULL){
										edgeLOS2 = compBlock->viewBlocked(side, WALLS_AND_DOORS);
										
										// Check for corner
										if(edgeLOS2 != NO_LOS && side == LEFT_SIDE){
											if(orig->getCoordPath(otherSide) <= targ->getCoordPath(otherSide)){	// looks like   _______
												if(orig->getCoordPath(side) < targ->getCoordPath(side))				//						 |     
													--coord[side];																	//		             | 
											}
											else if(orig->getCoordPath(side) >= targ->getCoordPath(side))
												--coord[side];
											
											compBlock = levelMap->getBlockByPath(coord[X], coord[Y]);
											if(compBlock != NULL)	
												edgeLOS2 = max(edgeLOS2, compBlock->viewBlocked(otherSide, WALLS_AND_DOORS));	
										}	
										
										edgeLOS2 = min(edgeLOS2, los);		 
									}
								}				
								
								thisLOS = edgeLOS2;
							}
							else
								thisLOS = los;
							
							// Adjust LOS based on distance
							if(thisLOS == LOW_LOS){	
								// Avoid repeats -- could be done outside this block, but would increase workload
								if(los != thisLOS)
									continue;
								
								double wallCoord[2];
								wallCoord[side] = targ->getCoordPath(side) - 0.5;																
								double t = (wallCoord[side] - orig->getCoordPath(side)) / thisVect.getDir(side);
								wallCoord[otherSide] = orig->getCoordPath(otherSide) + thisVect.getDir(otherSide) * t;
								
								Vector vectToWindow(Vertex(wallCoord[X], wallCoord[Y]), origVert);
								
								double windowReduction = (HEIGHT[kneeling][TORSO] - WINDOW_FRAME_HEIGHT) / vectToWindow.size();										
								double height = HEIGHT[kneeling][TORSO] - windowReduction * thisSize;
								if(height < LOS_MIN_HEIGHT[MID_LOS])
									continue;
								else if(height < LOS_MIN_HEIGHT[LOW_LOS])
									thisLOS = MID_LOS;
							}
							
							_viewLOS[test][iter->first] = max(thisLOS, _viewLOS[test][iter->first]);
						}
					}
				}
			}
		}
	}
}

bool View::canSee(GridBlock* gb)
{
	return getLOS(VIEWED, gb) != NO_LOS;
}

bool View::couldSee(GridBlock* gb)
{
	return getLOS(VIEWABLE, gb) != NO_LOS;
}

bool View::inScope(GridBlock* gb)
{
	return _viewLOS[VIEWABLE].count(gb);
}

GLshort View::getLOS(GLshort i, GridBlock* gb)
{
	if(!_viewLOS[i].count(gb))
		return NO_LOS;
	
	return max(_viewLOS[i][gb], _viewLOS[DOOR_VIEW][gb]);
}

void View::addLOS()
{
	for(GLshort i = 0; i < 2; ++i){
		for(BlockLOS::iterator iter = _viewLOS[i].begin(); iter != _viewLOS[i].end(); ++iter)
			(*iter).first->addLOS(i, getLOS(i, iter->first));
	}
}

void View::removeLOS()
{
	for(GLshort i = 0; i < 2; ++i){
		for(BlockLOS::iterator iter = _viewLOS[i].begin(); iter != _viewLOS[i].end(); ++iter)
			(*iter).first->removeLOS(i, getLOS(i, iter->first));
	}
}

//---- DRAW ----//	
void View::draw(bool step)
{	
	for(list<Icon>::iterator iter = _view.begin(); iter != _view.end(); ++iter)
		iter->draw(step);
}
