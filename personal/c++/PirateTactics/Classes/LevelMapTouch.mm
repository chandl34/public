/*
 *  LevelMapTouch.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"


bool LevelMap::isLocked() const{
	if(sUnit != NULL)
		return sUnit->isMoving();
	return false;
}

bool LevelMap::push(GLshort t, const Coord2d<GLshort>& p){
	for(GLshort i = 0; i < 2; i++){
		startPoint[t][i] = p[i];
		lastPoint[t][i] = p[i];
	}
	
	if(touchCount == 0){
		selectBlock(getBlockByOffset(p[X], p[Y]));
		
		// Calculate potential action, so that it represents costs and paths on the screen
		if(sUnit != NULL)							
			sUnit->calculateAction(unitMode, sBlock);
	}	
	
	touchCount++;	
	
	
	/*
	// Find the selected block and select it
	GridBlock* lastBlock = sBlock;	
	sBlock = getBlockAtPoint(p[X], p[Y]);
	// Deselect previous block
	if(lastBlock != NULL && sBlock != lastBlock)
		lastBlock->select(false);
	sBlock->select(true);
	
	if(sBlock->getUnit() != NULL){							// start a timer to select/deselect the character
		timePushed = [[NSDate date] timeIntervalSince1970];	// would also need to check if the unit is on the right team
	}
	
	// Calculate potential action, so that it represents costs and paths on the screen
	if(sUnit != NULL)							
		sUnit->calculateAction(unitMode, sBlock);
	*/
	
	return true;
}

void LevelMap::move(GLshort t, const Coord2d<GLshort>& p){	
	if(touchCount == 1){
		if(!drag){	
			// Prevent camera movement if you barely move your finger on a touch
			if(hypot(p[X] - startPoint[t][X], p[Y] - startPoint[t][Y]) > DRAG_THRESHOLD){	
				//timePushed = -1;
				drag = true;		
			}
		}		
		else{
			redraw = true;
			camera.setView(X, camera.getView(X) + lastPoint[t][X] - p[X]);
			camera.setView(Y, camera.getView(Y) + lastPoint[t][Y] - p[Y]);
		}
	}	
	lastPoint[t][X] = p[X];
	lastPoint[t][Y] = p[Y];	
	
	/*
	if(!drag){		
		// Prevent camera movement if you barely move your finger on a touch
		if(hypot(p[X] - startTouchPoint[X], p[Y] - startTouchPoint[Y]) > DRAG_THRESHOLD){			
			timePushed = -1;
			drag = true;		
		}
	}
	else{		
		// Otherise move camera around your finger
		redraw = true;
		camera.setView(X, camera.getView(X) + lastTouchPoint[X] - p[X]);
		camera.setView(Y, camera.getView(Y) + lastTouchPoint[Y] - p[Y]);
	}
	lastTouchPoint[X] = p[X];
	lastTouchPoint[Y] = p[Y];	
	 */
}

void LevelMap::release(GLshort t, const Coord2d<GLshort>& p){		
	if(touchCount == 2){	// End of a multi-touch
		GLshort x0d = lastPoint[0][X] - startPoint[0][X];
		GLshort y0d = lastPoint[0][Y] - startPoint[0][Y];		
		GLshort x1d = lastPoint[1][X] - startPoint[1][X];
		GLshort y1d = lastPoint[1][Y] - startPoint[1][Y];
		
		if(hypot(x0d, y0d) > DRAG_THRESHOLD && hypot(x1d, y1d) > DRAG_THRESHOLD){	// Both fingers moved more than threshold
			if(x0d*x1d + y0d*y1d < 0){												// Fingers are moving in opposite directions
				if(hypot(startPoint[0][X] - startPoint[1][X], startPoint[0][Y] - startPoint[1][Y]) <
				   hypot(lastPoint[0][X] - lastPoint[1][X], lastPoint[0][Y] - lastPoint[1][Y])){	// Got further apart
					if(Camera::getZoom() < 2){
						camera.setZoom(Camera::getZoom() + 1);
						redraw = true;
						store = true;
					}					
				}
				else if(Camera::getZoom() > 0){
					camera.setZoom(Camera::getZoom() - 1);
					redraw = true;
					store = true;
				}
			}
		}
		// Reset other touch, so that it delays its drag again
		GLshort o = (t+1)%2;	
		for(GLshort i = 0; i < 2; i++)
			startPoint[o][i] = lastPoint[o][i];
	}
	else{				// End of a single-touch
		if(drag)
			store = true;
	}	
	drag = false;	
	touchCount--;
	
	
	//timePushed = -1;
}
