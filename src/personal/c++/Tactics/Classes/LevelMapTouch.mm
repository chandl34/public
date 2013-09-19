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


bool LevelMap::isLocked()
{
	if(_turnOwner != PLAYER)
		return true;
	
	if(!_proj.empty())
		return true;
	
	Unit* u = getSelectedUnit();
	if(u != NULL)
		return !u->isIdle();
	
	return false;
}

void LevelMap::push(GLshort t, const Coord2d<GLshort>& p)
{
	for(GLshort i = 0; i < 2; ++i){
		_startPoint[t][i] = p[i];
		_lastPoint[t][i] = p[i];
	}
	
	if(_touchCount == 0){
		selectBlock(getBlockByOffset(p[X], p[Y]));
		
		// Start a timer for selecting another character
		Unit* su = _sBlock->getUnit();
		Unit* sUnit = getSelectedUnit();
		if(su != NULL && su != sUnit && su->getFactionID() == PLAYER)	
			_timePushed = [[NSDate date] timeIntervalSince1970];	
		
		// Calculate potential action, so that it represents costs and paths on the screen
		if(sUnit != NULL)							
			sUnit->calculateAction(_mode, _sBlock);
	}	
	
	++_touchCount;	
}

void LevelMap::move(GLshort t, const Coord2d<GLshort>& p)
{	
	if(_touchCount == 1){
		if(!_drag){	
			// Prevent camera movement if you barely move your finger on a touch
			if(hypot(p[X] - _startPoint[t][X], p[Y] - _startPoint[t][Y]) > DRAG_THRESHOLD){	
				_timePushed = -1;
				_drag = true;		
			}
		}		
		else{
			_redraw = true;
			_resort = true;
			_camera.setView(X, _camera.getRelativeView(X) + _lastPoint[t][X] - p[X]);
			_camera.setView(Y, _camera.getRelativeView(Y) + _lastPoint[t][Y] - p[Y]);
		}
	}	
	_lastPoint[t][X] = p[X];
	_lastPoint[t][Y] = p[Y];	
}

bool LevelMap::release(GLshort t, const Coord2d<GLshort>& p)
{		
	if(_touchCount == 2){	// End of a multi-touch
		GLshort x0d = _lastPoint[0][X] - _startPoint[0][X];
		GLshort y0d = _lastPoint[0][Y] - _startPoint[0][Y];		
		GLshort x1d = _lastPoint[1][X] - _startPoint[1][X];
		GLshort y1d = _lastPoint[1][Y] - _startPoint[1][Y];
		
		if(hypot(x0d, y0d) > DRAG_THRESHOLD && hypot(x1d, y1d) > DRAG_THRESHOLD){	// Both fingers moved more than threshold
			if(x0d*x1d + y0d*y1d < 0){												// Fingers are moving in opposite directions
				if(hypot(_startPoint[0][X] - _startPoint[1][X], _startPoint[0][Y] - _startPoint[1][Y]) <
				   hypot(_lastPoint[0][X] - _lastPoint[1][X], _lastPoint[0][Y] - _lastPoint[1][Y])){	// Got further apart
					if(_camera.getZoom() < MAX_ZOOM){
						_camera.setZoom(_camera.getZoom() + 1);
						_redraw = true;
						_store = true;
						_resort = true;
					}					
				}
				else if(_camera.getZoom() > 0){
					_camera.setZoom(_camera.getZoom() - 1);
					_redraw = true;
					_store = true;
					_resort = true;
				}
			}
		}
		// Reset other touch, so that it delays its drag again
		GLshort o = (t+1)%2;	
		for(GLshort i = 0; i < 2; ++i)
			_startPoint[o][i] = _lastPoint[o][i];
	}
	else{				// End of a single-touch
		if(_drag)
			_store = true;
	}	
	
	_drag = false;	
	_timePushed = -1;
	--_touchCount;		
	
	return true;
}
