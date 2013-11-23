/*
 *  LevelMapDraw.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/31/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"
#include "ImageContainer.h"


void LevelMap::draw(bool step){	
	GLshort i;
	GLfloat x, y;
	
	// Select/Deselect unit if it has been touched for too long
	if(timePushed > 0 && [[NSDate date] timeIntervalSince1970] - timePushed > actionDelay){
		timePushed = -1;
		if(sBlock->getUnit() == sUnit){
			printf("Deselected %i\n", sUnit);
			sUnit = NULL;			
		}
		else{
			sUnit = (Unit*)sBlock->getUnit();
			printf("Selected %i\n", sUnit);
		}
	}	
	
	//----- RESET VIEW -----//
	resetView(Camera::getZoom());	
	x = (-camera.getView(X) + 0.1f)*pow(2, 2 - Camera::getZoom());
	y = (MENU_SIZE[Y] - camera.getView(Y) + 0.1f)*pow(2, 2 - Camera::getZoom());
	glTranslatef(x, y, 0);	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	glDisable(GL_BLEND);
	
	// Find bottom-left position for culling purposes
	bl[X] = (camera.getView(X) - 1)/(BLOCK_SIZE_ISO[Camera::getZoom()][X]/2);	// -1 pixel to prevent buffer bounds issues (since map stops evenly on a block)
	bl[Y] = (camera.getView(Y) - 1)/(BLOCK_SIZE_ISO[Camera::getZoom()][Y]/2); 
	
	if(redraw){	
		if(USE_BUFFERS)
			drawWithBuffers(step);
		else
			drawWithHalfBlend(step);
			//drawWithFullBlend(step);
		
		// Store pixels on screen
		if(store)
			createScreenTex();
	}
	else		
		drawScreenTex();
	
	//----- RESET VIEW -----//
	resetView(Camera::getZoom());
	glTranslatef(x, y, 0);	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	glEnable(GL_BLEND);
	
	// draw selection box and path steps - add later
	cursor->draw(step);
	
	drawObjects(step);
	
	// Step Unit Actions
	for(i = 0; i < unit.size(); i++){
		switch(unit[i]->update()){
			case DEAD:
				printf("Unit died\n");
				break;
			case UPDATE_SIGHT:
				unit[i]->updateSight(unit);
				break;					 
		}
	}
	
	if(bullet != NULL){
		if(bullet->update() == DEAD){
			printf("Hit detection works like a charm!\n");
			delete bullet;
			bullet = NULL;
		}
	}
}

void LevelMap::drawWithBuffers(bool step){	
	// Speed while dragging -- otherwise 60 fps
	// 42 fps far
	// 50 fps medium
	// 60 fps close
	
	GLshort i, j, tempXs, tempXb;
	glDisable(GL_BLEND);	
	glBindTexture(GL_TEXTURE_2D, 2);
	glBindBuffer(GL_ARRAY_BUFFER, groundStripTexCoord);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	for(i = 0; i < 2; i++){
		tempXs = ceil(bl[X]/2.0f) - i*(bl[X]%2);
		tempXb = tempXs + SCREEN_BLOCK[Camera::getZoom()][X];
		for(j = tempXs; j <= tempXb; j++){			// culling along X direction															
			glBindBuffer(GL_ARRAY_BUFFER, groundStripVert[i][j]);
			glVertexPointer(2, GL_SHORT, 0, NULL);
			glDrawArrays(GL_TRIANGLE_STRIP,			// culling along Y direction
						 4*(ceil(bl[Y]/2.0f) - i*(bl[Y]%2)), 
						 4*(SCREEN_BLOCK[Camera::getZoom()][Y]/2 + 1 + (SCREEN_BLOCK[Camera::getZoom()][Y]%2)*(1 - abs(bl[Y]%2 - i))));		
		}
		glEnable(GL_BLEND);			// Enables for the second overlay pass
	}	
	
	// Restore the previous state -- may be able to remove when the game is closer to being finished
	glBindBuffer(GL_ARRAY_BUFFER, 0);		
}

void LevelMap::drawWithHalfBlend(bool step){
	// Speed while dragging -- otherwise 60 fps
	// 19 fps far 
	// 43 fps medium
	// 58 fps close
	
	GLshort i, j, tempXs, tempXb;
	glDisable(GL_BLEND);
	tempXs = ceil(bl[X]/2.0f) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2));
	tempXb = tempXs + SCREEN_BLOCK[Camera::getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[Camera::getZoom()][Y] + 1; j >= bl[Y]; j -= 2){
		for(i = tempXs; i <= tempXb; i++)
			gridBlock[i][j]->draw(step);		
	}	
	
	// Second overlay pass
	glEnable(GL_BLEND);
	tempXs = ceil(bl[X]/2.0f) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2));
	tempXb = tempXs + SCREEN_BLOCK[Camera::getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[Camera::getZoom()][Y]; j >= bl[Y]; j -= 2){
		for(i = tempXs; i <= tempXb; i++)
			gridBlock[i][j]->draw(step);		
	}	
}

void LevelMap::drawWithFullBlend(bool step){	
	// Speed while dragging -- otherwise 60 fps
	// 19 fps far 
	// 42 fps medium
	// 52 fps close
	
	GLshort i, j, tempXs, tempXb;
	glEnable(GL_BLEND);		
	tempXb = SCREEN_BLOCK[Camera::getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[Camera::getZoom()][Y] + 1; j >= bl[Y]; j -= 2){
		tempXs = ceil(bl[X]/2.0f) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2));				
		for(i = tempXs; i <= tempXs + tempXb; i++)
			gridBlock[i][j]->draw(step);			
		if(j - 1 >= bl[Y]){
			tempXs = ceil(bl[X]/2.0f) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2));
			for(i = tempXs; i <= tempXs + tempXb; i++)
				gridBlock[i][j - 1]->draw(step);
		}
	}			
}

void LevelMap::drawObjects(bool step){
	GLshort i, j, tempXs, tempXb;
	
	// Push all objects to list for isometric sorting -- use masking on walls seen behind -- change later
	tempXb = SCREEN_BLOCK[Camera::getZoom()][X] + (bl[X]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2);
	for(j = bl[Y] + SCREEN_BLOCK[Camera::getZoom()][Y] + 1; j >= bl[Y]; j -= 2){
		tempXs = ceil(bl[X]/2.0f) - (bl[X]%2)*((bl[Y]%2) + (1 - bl[Y]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2));				
		for(i = tempXs; i <= tempXs + tempXb; i++)
			gridBlock[i][j]->isoSort(objList);
		if(j - 1 >= bl[Y]){
			tempXs = ceil(bl[X]/2.0f) - (bl[X]%2)*((1 - bl[Y]%2) + (bl[Y]%2)*(1 - SCREEN_BLOCK[Camera::getZoom()][Y]%2));
			for(i = tempXs; i <= tempXs + tempXb; i++)
				gridBlock[i][j-1]->isoSort(objList);
		}
	}		
	
	// Draw all seen units -- change this later
	for(i = 0; i < unit.size(); i++)
		unit[i]->isoSort(objList);
	
	if(bullet != NULL)
		bullet->isoSort(objList);
	
	//cout << "order" << endl;	
	//for(list<Object*>::reverse_iterator iter = objList.rbegin(); iter != objList.rend(); iter++)
	for(list<Object*>::iterator iter = objList.begin(); iter != objList.end(); iter++){
		(*iter)->draw(step);
	//	(*iter)->report();
	}
	//cout << "end" << endl << endl;
	
	objList.clear();
}


void LevelMap::createScreenTex(){	
	store = false;
	redraw = false;		
	
	glBindTexture(GL_TEXTURE_2D, screenTex);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glReadPixels(0, 0, 512, 512, GL_RGBA, GL_UNSIGNED_BYTE, screenData);		
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, screenData);				
	//cout << "Screen stored" << endl;		
}

void LevelMap::drawScreenTex(){
	resetView(MAX_ZOOM);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();	
	glDisable(GL_BLEND);
	
	glTranslatef(-32, 0, 0);		// This is 480 (screen width) - 512 (image width)
		
	glBindTexture(GL_TEXTURE_2D, screenTex);	
	glVertexPointer(2, GL_SHORT, 0, SCREEN_TEX_VERT);
	glTexCoordPointer(2, GL_FLOAT, 0, ImageContainer::getTexCoords(1, 0));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);		
}
