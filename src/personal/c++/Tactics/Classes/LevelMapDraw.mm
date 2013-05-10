/*
 *  LevelMapDraw.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"

#include "EnemyTeam.h"
#include "Projectile.h"
#include "GridBlock.h"

#include "ImageStorage.h"
#include "Options.h"


void LevelMap::draw(bool step)
{		
	//----- CHECK FOR PRESSES -----//
	if(_timePushed > 0 && [[NSDate date] timeIntervalSince1970] - _timePushed > _actionDelay){
		_timePushed = -1;
		selectUnit(_sBlock->getUnit());
	}	
	
	
	//----- CENTER ON IMPORTANT EVENTS -----//
	if(_turnOwner != PLAYER){
		if(!_proj.empty()){
			Projectile* proj = *_proj.begin();
			Coord2d<GLshort> os(proj->getOffset(X), proj->getOffset(Y));
			if(!onScreen(os)){
				printf("Centering on projectile\n");
				centerView(os[X], os[Y]);
			}
		}
		else{
			Unit* sUnit = _team[ENEMY]->getSelectedUnit();
			if(sUnit != NULL && sUnit->hasBeenSeen()){
				Coord2d<GLshort> os(sUnit->getOffset(X), sUnit->getOffset(Y));
				if(!onScreen(os)){
					printf("Centering on enemy\n");
					centerView(os[X], os[Y]);
				}
			}
		}
	}
	
	
	//----- FIND BOTTOMLEFT BLOCK -----//
	_bl[X] = (_camera.getRelativeView(X) - 1)/(BLOCK_SIZE_ISO[_camera.getZoom()][X]/2);	// -1 pixel to prevent buffer bounds issues (since map stops evenly on a block)
	_bl[Y] = (_camera.getRelativeView(Y) - 1)/(BLOCK_SIZE_ISO[_camera.getZoom()][Y]/2); 	
	
	
	//----- DRAW GROUND -----//
	if(!_redraw)
		drawScreenTex();
	
	resetView(_camera.getZoom());
	glMatrixMode(GL_PROJECTION);	
	glTranslatef(-_camera.getView(X) + 0.1f * pow(2, 2 - _camera.getZoom()), 
				 -_camera.getView(Y) + (MENU_SIZE[Y] + 0.1f) * pow(2, 2 - _camera.getZoom()), 
				 0);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	
	if(_redraw){		
		if(USE_BUFFERS)
			drawWithBuffers(step);
		else
			drawWithHalfBlend(step);
		
		if(_store){
			_redraw = false;	
			_store = false;
			_storeMini = true;	
			
			createScreenTex();		
		}
	}
	
	//----- DRAW OVERLAYS -----//
	drawOverlays(step);
	
	
	//----- DRAW OBJECTS -----//
	drawObjects(step);
	
	
	//----- STEP OBJECT ACTIONS -----//
	// Projectiles
	GLshort action;
	for(list<Projectile*>::iterator iter = _proj.begin(); iter != _proj.end();){
		action = (*iter)->update();
		if(action == DIED){
			delete *iter;
			iter = _proj.erase(iter);
		}
		else
			++iter;
	}
	
	// Unit
	for(GLshort i = 0; i < TEAMS_PER_FIGHT; ++i){
		action = _team[i]->update(*_team[(i + 1) % TEAMS_PER_FIGHT], _dead);
		if(action == DESELECT)
			selectBlock(NULL);
	}	
	removeDead();
	
	// Objects
	//BlockSet bs;
	bool update = false;
	/*	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
	 for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
	 if(gridBlock[i][j]->update())
	 update = true;
	 //	bs.insert(gridBlock[i][j]);
	 }
	 }*/
	
	// Update all unit's sight if there was a map change
	//	if(!bs.empty()){
	if(update){
		GLshort otherTeam = (_turnOwner + 1) % TEAMS_PER_FIGHT;
		double timer = [[NSDate date] timeIntervalSince1970];
		printf("\nMap changed.  Updating sight.\n");
		_team[otherTeam]->updateSight(*_team[_turnOwner], INT_ON_NONE, MAP_CHANGED);
		_team[_turnOwner]->updateSight(*_team[otherTeam], INT_ON_ANY, MAP_CHANGED);		
		
		timer = [[NSDate date] timeIntervalSince1970] - timer;
		printf("All unit's views found in %f seconds\n", timer);
	}	
	
	//----- AI PLANNING -----//
	if(_turnOwner != PLAYER && _proj.empty()){
		EnemyTeam* bt = (EnemyTeam*)_team[ENEMY];
		if(!bt->plan())
			endTurn();
	}
	//*/
}


void LevelMap::drawMinimap(bool step)
{		
	//----- DRAW GROUND -----//
	if(!_storeMini)
		drawScreenTex();
	
	resetView(MINIMAP_VIEW_SIZE[X], MINIMAP_VIEW_SIZE[Y]);
	glMatrixMode(GL_PROJECTION);
	glTranslatef(MINIMAP_OFFSET[X], MINIMAP_OFFSET[Y], 0.0f);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	
	if(_storeMini){
		_redraw = true;
		_resort = true;
		_store = true;
		_storeMini = false;
		
		if(USE_BUFFERS){			
			glDisable(GL_BLEND);	
			glBindTexture(GL_TEXTURE_2D, 14);					// THIS NEEDS TO BE CHANGED!#!#@!#@##@!!!!
			glBindBuffer(GL_ARRAY_BUFFER, _groundStripTexCoord);
			glTexCoordPointer(2, GL_FLOAT, 0, NULL);
			
			for(GLshort i = 0; i < 2; ++i){
				for(GLshort j = 0; j < MAP_BLOCK[X] - i; ++j){														
					glBindBuffer(GL_ARRAY_BUFFER, _groundStripVert[i][j]);
					glVertexPointer(2, GL_SHORT, 0, NULL);
					glDrawArrays(GL_TRIANGLE_STRIP, 0, 4*(80 + 1 - i));		
				}
				glEnable(GL_BLEND);			// Enables for the second overlay pass
			}	
			
			// Restore the previous state -- may be able to remove when the game is closer to being finished
			glBindBuffer(GL_ARRAY_BUFFER, 0);	
		}
		else{
			glDisable(GL_BLEND);
			for(GLshort j = MAP_BLOCK[Y] - 1; j >= 0; j -= 2){
				for(GLshort i = 0; i < MAP_BLOCK[X]; ++i)
					_gridBlock[i][j]->draw(step);		
			}	
			
			// Second overlay pass
			glEnable(GL_BLEND);
			for(GLshort j = MAP_BLOCK[Y] - 2; j >= 0; j -= 2){
				for(GLshort i = 0; i < MAP_BLOCK[X] - 1; ++i)
					_gridBlock[i][j]->draw(step);	
			}
		}	
		
		//----- DRAW OBJECTS -----//
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
			for(GLshort i = 0; i < MAP_BLOCK[X]; ++i)
				_gridBlock[i][j]->isoSort(_objList);
		}
		
		for(ObjectList::iterator iter = _objList.begin(); iter != _objList.end(); ++iter)
			(*iter)->draw(step);	
		
		_objList.clear();
		
		// Store Minimap
		createScreenTex();	
	}
	
	
	//----- DRAW OUTLINE -----//
	glLoadIdentity();
	glTranslatef(_camera.getView(X), _camera.getView(Y), 0.0f);
	Size2d<GLshort> sz(MAP_VIEW_SIZE[_camera.getZoom()][X], 
							 MAP_VIEW_SIZE[_camera.getZoom()][Y]);	
	GLshort* vert = ImageStorage::getBoxVerts(sz);
	
	glBindTexture(GL_TEXTURE_2D, 0);	
	glVertexPointer(2, GL_SHORT, 0, vert);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}


// GROUND //
void LevelMap::drawWithBuffers(bool step)
{	
	// Speed while dragging -- otherwise 60 fps
	// 42 fps far
	// 50 fps medium
	// 60 fps close
	
	GLshort i, j, tempXs, tempXb;
	glDisable(GL_BLEND);	
	glBindTexture(GL_TEXTURE_2D, 14);					// THIS NEEDS TO BE CHANGED!#!#@!#@##@!!!!
	glBindBuffer(GL_ARRAY_BUFFER, _groundStripTexCoord);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	for(i = 0; i < 2; ++i){
		tempXs = ceil(_bl[X]/2.0) - i*(_bl[X]%2);
		tempXb = tempXs + SCREEN_BLOCK[_camera.getZoom()][X];
		for(j = tempXs; j <= tempXb; ++j){			// culling along X direction															
			glBindBuffer(GL_ARRAY_BUFFER, _groundStripVert[i][j]);
			glVertexPointer(2, GL_SHORT, 0, NULL);
			glDrawArrays(GL_TRIANGLE_STRIP,			// culling along Y direction
							 4*(ceil(_bl[Y]/2.0) - i*(_bl[Y]%2)), 
							 4*(SCREEN_BLOCK[_camera.getZoom()][Y]/2 + 1 + (SCREEN_BLOCK[_camera.getZoom()][Y]%2)*(1 - abs(_bl[Y]%2 - i))));		
		}
		glEnable(GL_BLEND);			// Enables for the second overlay pass
	}	
	
	// Restore the previous state -- may be able to remove when the game is closer to being finished
	glBindBuffer(GL_ARRAY_BUFFER, 0);		
}

void LevelMap::drawWithHalfBlend(bool step)
{
	// Speed while dragging -- otherwise 60 fps
	// 19 fps far 
	// 43 fps medium
	// 58 fps close
	
	GLshort i, j, tempXs, tempXb;
	glDisable(GL_BLEND);
	tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((_bl[Y]%2) + (1 - _bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));
	tempXb = tempXs + SCREEN_BLOCK[_camera.getZoom()][X] + (_bl[X]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2);
	for(j = _bl[Y] + SCREEN_BLOCK[_camera.getZoom()][Y] + 1; j >= _bl[Y]; j -= 2){
		for(i = tempXs; i <= tempXb; ++i)
			_gridBlock[i][j]->draw(step);		
	}	
	
	// Second overlay pass
	glEnable(GL_BLEND);
	tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((1 - _bl[Y]%2) + (_bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));
	tempXb = tempXs + SCREEN_BLOCK[_camera.getZoom()][X] + (_bl[X]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2);
	for(j = _bl[Y] + SCREEN_BLOCK[_camera.getZoom()][Y]; j >= _bl[Y]; j -= 2){
		for(i = tempXs; i <= tempXb; ++i)
			_gridBlock[i][j]->draw(step);		
	}	
}

void LevelMap::drawWithFullBlend(bool step)
{	
	// Speed while dragging -- otherwise 60 fps
	// 19 fps far 
	// 42 fps medium
	// 52 fps close
	
	GLshort i, j, tempXs, tempXb;
	glEnable(GL_BLEND);		
	tempXb = SCREEN_BLOCK[_camera.getZoom()][X] + (_bl[X]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2);
	for(j = _bl[Y] + SCREEN_BLOCK[_camera.getZoom()][Y] + 1; j >= _bl[Y]; j -= 2){
		tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((_bl[Y]%2) + (1 - _bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));				
		for(i = tempXs; i <= tempXs + tempXb; ++i)
			_gridBlock[i][j]->draw(step);			
		if(j - 1 >= _bl[Y]){
			tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((1 - _bl[Y]%2) + (_bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));
			for(i = tempXs; i <= tempXs + tempXb; ++i)
				_gridBlock[i][j - 1]->draw(step);
		}
	}			
}

void LevelMap::createScreenTex()
{	
	glBindTexture(GL_TEXTURE_2D, _screenTex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glReadPixels(0, 0, 512, 512, GL_RGBA, GL_UNSIGNED_BYTE, _screenData);		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, _screenData);	
}

void LevelMap::drawScreenTex()
{
	resetView();
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	glTranslatef(-32, 0, 0);		// This is 480 (screen width) - 512 (image width)
	
	//	glDisable(GL_BLEND);	
	glBindTexture(GL_TEXTURE_2D, _screenTex);	
	glVertexPointer(2, GL_SHORT, 0, SCREEN_TEX_VERT);
	glTexCoordPointer(2, GL_FLOAT, 0, ImageStorage::getTexCoords(Coord2d<GLfloat>(1.0f, 0.0f)));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	
	//	glEnable(GL_BLEND);	
}

void LevelMap::drawOverlays(bool step)
{
	GLshort i, j, tempXs, tempXb;
	
	Unit* sUnit = getSelectedUnit();
	if(sUnit != NULL)
		sUnit->drawView(step);
	
	// todo: check this for errors.  i just copied this from drawObjects
	tempXb = SCREEN_BLOCK[_camera.getZoom()][X] + (_bl[X]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2);
	for(j = _bl[Y] + SCREEN_BLOCK[_camera.getZoom()][Y] + 1; j >= _bl[Y]; j -= 2){
		tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((_bl[Y]%2) + (1 - _bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));				
		for(i = tempXs; i <= tempXs + tempXb; ++i)
			_gridBlock[i][j]->drawOverlays(step);
		if(j - 1 >= _bl[Y]){
			tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((1 - _bl[Y]%2) + (_bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));
			for(i = tempXs; i <= tempXs + tempXb; ++i)
				_gridBlock[i][j-1]->drawOverlays(step);
		}
	}		
	
	if(sUnit != NULL)
		sUnit->drawPath(step);
	
	_cursor.draw(step);		
}

void LevelMap::drawObjects(bool step){
	//double timer = [[NSDate date] timeIntervalSince1970];
	
	GLshort sortRule = SORT_DYNAMIC;
	if(_resort){
		_resort = false;
		sortRule = SORT_ALL;
		_objList.clear();
	}	
	
	GLshort yBound = _bl[Y] + SCREEN_BLOCK[_camera.getZoom()][Y];
	GLshort tempXb = SCREEN_BLOCK[_camera.getZoom()][X] + (_bl[X]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2);
	for(GLshort j = _bl[Y]; j < yBound; j += 2){
		GLshort tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((_bl[Y]%2) + (1 - _bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));	
		for(GLshort i = tempXs; i <= tempXs + tempXb; ++i){
			//	cout << "gb: " << i << ", " << j << endl;
			_gridBlock[i][j]->isoSort(_objList, sortRule);
		}
		if(j + 1 < yBound){
			tempXs = ceil(_bl[X]/2.0) - (_bl[X]%2)*((1 - _bl[Y]%2) + (_bl[Y]%2)*(1 - SCREEN_BLOCK[_camera.getZoom()][Y]%2));
			for(GLshort i = tempXs; i <= tempXs + tempXb; ++i){
				//		cout << "gb: " << i << ", " << j + 1 << endl;
				_gridBlock[i][j + 1]->isoSort(_objList, sortRule);
			}
		}
	}
	
	for(list<Projectile*>::iterator iter = _proj.begin(); iter != _proj.end(); ++iter)
		(*iter)->isoSort(_objList);
	
	//timer = [[NSDate date] timeIntervalSince1970] - timer;
	//printf("isoSort() took %f seconds\n", timer);
	
	/*
	 // Push all objects to list for isometric sorting -- use masking on walls seen behind -- change later
	 tempXb = SCREEN_BLOCK[camera.getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2);
	 for(j = bl[Y] + SCREEN_BLOCK[camera.getZoom()][Y] + 1; j >= bl[Y]; j -= 2){
	 tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));				
	 for(i = tempXs; i <= tempXs + tempXb; ++i)
	 gridBlock[i][j]->isoSort(objList);
	 if(j - 1 >= bl[Y]){
	 tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));
	 for(i = tempXs; i <= tempXs + tempXb; ++i)
	 gridBlock[i][j-1]->isoSort(objList);
	 }
	 }		
	 */
	
	TexAttr ta;
	for(ObjectList::iterator iter = _objList.begin(); iter != _objList.end(); ){
		(*iter)->draw(step, &ta);	
		if((*iter)->isDynamic())
			iter = _objList.erase(iter);
		else
			++iter;
	}
	
	//timer = [[NSDate date] timeIntervalSince1970] - timer;
	//printf("drawObjects() took %f seconds\n", timer);
}
