/*
 *  LevelMapDraw.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"

#include "GridBlock.h"

#include "ImageStorage.h"
#include "Options.h"


void LevelMap::draw(bool step)
{		
	//----- CHECK FOR PRESSES -----//
	if(timePushed > 0 && time(0) - timePushed > actionDelay){
		timePushed = -1;
		
	}	
	
	//----- FIND BOTTOMLEFT BLOCK -----//
	bl[X] = (camera.getView(X) - 1)/(BLOCK_SIZE_ISO[camera.getZoom()][X]/2);	// -1 pixel to prevent buffer bounds issues (since map stops evenly on a block)
	bl[Y] = (camera.getView(Y) - 1)/(BLOCK_SIZE_ISO[camera.getZoom()][Y]/2); 	
	
	
	//----- DRAW GROUND -----//
	if(!redraw)
		drawScreenTex();
	
	resetView(VIEW_SIZE[camera.getZoom()][X], VIEW_SIZE[camera.getZoom()][Y]);
	glMatrixMode(GL_PROJECTION);	
	glTranslatef((-camera.getView(X) + 0.1) * pow(2, 2 - camera.getZoom()), 
					 (-camera.getView(Y) + 0.1) * pow(2, 2 - camera.getZoom()), 
					 0);	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	
	if(redraw){		
		if(USE_BUFFERS)
			drawWithBuffers(step);
		else
			drawWithHalfBlend(step);
	/*
		if(store){
			redraw = false;	
			store = false;
			storeMini = true;	
			glFinish();
			createScreenTex();		
		}*/
	}
	
	//----- DRAW GROUND OVERLAYS -----//
	drawOverlays(step);
	
	
	//----- DRAW OBJECTS -----//
	drawObjects(step);
}


void LevelMap::drawOverlays(bool step)
{
	cursor.draw(step);		
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
	glBindTexture(GL_TEXTURE_2D, 2);					// THIS NEEDS TO BE CHANGED!#!#@!#@##@!!!!
	glBindBuffer(GL_ARRAY_BUFFER, groundStripTexCoord);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	for(i = 0; i < 2; ++i){
		tempXs = ceil(bl[X]/2.0) - i*(bl[X]%2);
		tempXb = tempXs + SCREEN_BLOCK[camera.getZoom()][X];
		for(j = tempXs; j <= tempXb; ++j){			// culling along X direction															
			glBindBuffer(GL_ARRAY_BUFFER, groundStripVert[i][j]);
			glVertexPointer(2, GL_SHORT, 0, NULL);
			glDrawArrays(GL_TRIANGLE_STRIP,			// culling along Y direction
							 4*(ceil(bl[Y]/2.0) - i*(bl[Y]%2)), 
							 4*(SCREEN_BLOCK[camera.getZoom()][Y]/2 + 1 + (SCREEN_BLOCK[camera.getZoom()][Y]%2)*(1 - abs(bl[Y]%2 - i))));		
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
	tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));
	tempXb = tempXs + SCREEN_BLOCK[camera.getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[camera.getZoom()][Y] + 1; j >= bl[Y]; j -= 2){
		for(i = tempXs; i <= tempXb; ++i)
			gridBlock[i][j]->draw(step);		
	}	
	
	// Second overlay pass
	glEnable(GL_BLEND);
	tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));
	tempXb = tempXs + SCREEN_BLOCK[camera.getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[camera.getZoom()][Y]; j >= bl[Y]; j -= 2){
		for(i = tempXs; i <= tempXb; ++i)
			gridBlock[i][j]->draw(step);		
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
	tempXb = SCREEN_BLOCK[camera.getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[camera.getZoom()][Y] + 1; j >= bl[Y]; j -= 2){
		tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));				
		for(i = tempXs; i <= tempXs + tempXb; ++i)
			gridBlock[i][j]->draw(step);			
		if(j - 1 >= bl[Y]){
			tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));
			for(i = tempXs; i <= tempXs + tempXb; ++i)
				gridBlock[i][j - 1]->draw(step);
		}
	}			
}

void LevelMap::createScreenTex()
{	
	glBindTexture(GL_TEXTURE_2D, screenTex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, DRAW_METHOD);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, DRAW_METHOD);
	
	glReadPixels(0, 0, 512, 512, GL_RGBA, GL_UNSIGNED_BYTE, screenData);		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, screenData);	
}

void LevelMap::drawScreenTex()
{
//	resetView();
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	//glTranslatef(-32, 0, 0);		// This is 480 (screen width) - 512 (image width)
	
	//glDisable(GL_BLEND);	
	glBindTexture(GL_TEXTURE_2D, screenTex);	
	glVertexPointer(2, GL_SHORT, 0, SCREEN_TEX_VERT);
	glTexCoordPointer(2, GL_FLOAT, 0, ImageStorage::getTexCoords(Coord2d<GLfloat>(1.0f, 0.0f)));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);	
	//glEnable(GL_BLEND);	
}

void LevelMap::drawObjects(bool step)
{
	if(resort){
		resort = false;
		objList.clear();
		
		GLshort yBound = bl[Y] + SCREEN_BLOCK[camera.getZoom()][Y];
		GLshort tempXb = SCREEN_BLOCK[camera.getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2);
		for(GLshort j = bl[Y]; j < yBound; j += 2){
			GLshort tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));	
			for(GLshort i = tempXs; i <= tempXs + tempXb; ++i)
				gridBlock[i][j]->isoSort(objList);
			if(j + 1 < yBound){
				tempXs = ceil(bl[X]/2.0) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[camera.getZoom()][Y]%2));
				for(GLshort i = tempXs; i <= tempXs + tempXb; ++i)
					gridBlock[i][j + 1]->isoSort(objList);
			}
		}
		
	}
	
	GLuint currTexName;
	GLuint currTexVertName;
	GLuint currTexCoordName;	
	
	ObjectList rem;	// todo: use a quicker way to remove these.  maybe two lists, one with static, one with both
	for(ObjectList::iterator iter = objList.begin(); iter != objList.end(); ++iter)
		(*iter)->draw(step, true, &currTexName, &currTexVertName, &currTexCoordName);	
}

void LevelMap::refresh()
{
	resort = true;
	redraw = true;
	store = true;
}
