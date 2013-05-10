/*
 *  LevelMapTouch.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"

#include "GridBlock.h"
#include "DoorObject.h"
#include "SideObject.h"

#include "ObjectScreen.h"


void LevelMap::keyDown(GLshort k)
{
	
}

void LevelMap::push(GLshort t, const Coord2d<GLshort>& p)
{
	for(GLshort i = 0; i < 2; ++i){
		startPoint[t][i] = p[i];
		lastPoint[t][i] = p[i];
	}
	
	if(touchCount == 0){
		selectBlock(getBlockByOffset(p[X], p[Y]));
	}	
	
	++touchCount;	
}

void LevelMap::move(GLshort t, const Coord2d<GLshort>& p)
{	
	if(touchCount == 1){
		if(!drag){	
			// Prevent camera movement if you barely move your finger on a touch
			if(hypot(p[X] - startPoint[t][X], p[Y] - startPoint[t][Y]) > DRAG_THRESHOLD){	
				timePushed = -1;
				drag = true;		
			}
		}		
		else{
			redraw = true;
			resort = true;
			camera.setView(X, camera.getView(X) + lastPoint[t][X] - p[X]);
			camera.setView(Y, camera.getView(Y) + lastPoint[t][Y] - p[Y]);
		}
	}	
	lastPoint[t][X] = p[X];
	lastPoint[t][Y] = p[Y];	
}

bool LevelMap::release(GLshort t, const Coord2d<GLshort>& p)
{		
	if(touchCount == 2){	// End of a multi-touch
		GLshort x0d = lastPoint[0][X] - startPoint[0][X];
		GLshort y0d = lastPoint[0][Y] - startPoint[0][Y];		
		GLshort x1d = lastPoint[1][X] - startPoint[1][X];
		GLshort y1d = lastPoint[1][Y] - startPoint[1][Y];
		
		if(hypot(x0d, y0d) > DRAG_THRESHOLD && hypot(x1d, y1d) > DRAG_THRESHOLD){	// Both fingers moved more than threshold
			if(x0d*x1d + y0d*y1d < 0){												// Fingers are moving in opposite directions
				if(hypot(startPoint[0][X] - startPoint[1][X], startPoint[0][Y] - startPoint[1][Y]) <
				   hypot(lastPoint[0][X] - lastPoint[1][X], lastPoint[0][Y] - lastPoint[1][Y])){	// Got further apart
					if(camera.getZoom() < MAX_ZOOM){
						camera.setZoom(camera.getZoom() + 1);
						refresh();
					}					
				}
				else if(camera.getZoom() > 0){
					camera.setZoom(camera.getZoom() - 1);
					refresh();
				}
			}
		}
		// Reset other touch, so that it delays its drag again
		GLshort o = (t+1)%2;	
		for(GLshort i = 0; i < 2; ++i)
			startPoint[o][i] = lastPoint[o][i];
	}
	else{				// End of a single-touch
		if(drag)
			store = true;
	}	
	drag = false;	
	--touchCount;
	
	timePushed = -1;
	
	return true;
}
