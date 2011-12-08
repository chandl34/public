/*
 *  LevelMap.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"
#include "ImageContainer.h"


GridBlock* LevelMap::gridBlock[MAP_BLOCK_X][MAP_BLOCK_Y];
Bullet* LevelMap::bullet;


LevelMap::LevelMap(){
	GLshort i, j, k, sz, sz2;
	
	//--- GENERAL ---//	
	for(i = 0; i < MAP_BLOCK[X]; i++){
		for(j = 0; j < MAP_BLOCK[Y]; j++)
			gridBlock[i][j] = new GridBlock(Coord2d<GLshort>(i, j));		
	}		
	
	///*	TEST MATERIAL
	{
		for(i = 0; i < MAP_BLOCK[X]; i++){
			for(j = 0; j < MAP_BLOCK[Y]; j++)
				gridBlock[i][j]->setGround(Object::create(ObjType(GROUND), 0, HP(10)));
		}
		
		gridBlock[1][5]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0, HP(10)));	 
		gridBlock[2][4]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0, HP(10)));	
		gridBlock[2][3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0, HP(10)));
		
		gridBlock[4][6]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[5][8]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[2][7]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[5][9]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[6][11]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0, HP(10)));
		
		gridBlock[1][6]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0, HP(10)));		
		gridBlock[1][6]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		gridBlock[1][6]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		gridBlock[1][6]->setDoor(DoorObject::create(ObjType(DOOR), Side(LEFT_SIDE), Inner(INNER), Hinge(LEFT_HINGE), 0, HP(10)));
				
		gridBlock[3][6]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0, HP(10)));		
		gridBlock[3][6]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		gridBlock[3][6]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		gridBlock[3][6]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		
		gridBlock[3][7]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0, HP(10)));		
		gridBlock[3][7]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		gridBlock[3][7]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		gridBlock[3][7]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0, HP(10)));
		
		gridBlock[6][10]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0, HP(10)));		
		gridBlock[6][10]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[6][10]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[6][10]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0, HP(10)));
		
		SideObject* so;
		so = SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0, HP(10));		
		
		gridBlock[4][7]->addObject(so);		
		gridBlock[4][7]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[4][7]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0, HP(10)));
		gridBlock[4][7]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0, HP(10)));
		gridBlock[4][7]->toggleDoor();
	}
	// */
	
	
	cursor = new Icon(ImageContainer::getImage(0));
	cursor->setOffset(-100, -100);	// Arbitrary, offscreen location
	sBlock = NULL;
	
	//---- DRAW ----//		
	// Generate buffer data for the ground
	sz = 8*ceil(MAP_BLOCK[Y]/2.0f);
	sz2 = 8*MAP_BLOCK[Y]/2;
	
	groundStripVert = new GLuint*[2];// bottom and top overlay
	for(i = 0; i < 2; i++){
		groundStripVert[i] = new GLuint[MAP_BLOCK[X]];
		glGenBuffers(MAP_BLOCK[X], groundStripVert[i]);	
	}
	
	glGenBuffers(1, &groundStripTexCoord);
	
	GLshort offset;	
	GLshort vertTemp[sz]; 
	GLshort vertTemp2[sz2]; 
	GLfloat texCoordTemp[sz];
	GLshort* blockVert = ImageContainer::getVerts(BLOCK_SIZE_ISO[MAX_ZOOM][X], BLOCK_SIZE_ISO[MAX_ZOOM][Y]);
	GLfloat* blockTexCoord = ImageContainer::getTexCoords(0.625f, 0.375f);	// This is the default size of ground blocks.  may need to change later
		
	for(i = 0; i < MAP_BLOCK[X]; i++){
		offset = 0;
		for(j = 0; j < MAP_BLOCK[Y]; j++){
			if(j%2 == 0){
				for(k = 0; k < 8; k++){
					vertTemp[offset+k] = gridBlock[i][j]->getOffset(k%2) + blockVert[k];
					if(i == 0)			// Assume this tajes the same time whether this is there or not, I can change this up kater to save time
						texCoordTemp[offset+k] = blockTexCoord[k];	
				}	
			}
			else{// if(i < MAP_BLOCK[X] - 1){	// Cuts out extra end piece - temporariky removed cause regukar draw doesn't ignore this
				for(k = 0; k < 8; k++)					
					vertTemp2[offset+k] = gridBlock[i][j]->getOffset(k%2) + blockVert[k];
				offset += 8;
			}		
		}			
		glBindBuffer(GL_ARRAY_BUFFER, groundStripVert[0][i]);
		glBufferData(GL_ARRAY_BUFFER, sz*sizeof(GLshort), vertTemp, GL_STATIC_DRAW);	
	//	if(i < MAP_BLOCK[X] - 1){				 - temporariky removed cause regukar draw doesn't ignore this										
		glBindBuffer(GL_ARRAY_BUFFER, groundStripVert[1][i]);
		glBufferData(GL_ARRAY_BUFFER, sz2*sizeof(GLshort), vertTemp2, GL_STATIC_DRAW);		
	//	}
	}
	glBindBuffer(GL_ARRAY_BUFFER, groundStripTexCoord);
	glBufferData(GL_ARRAY_BUFFER, sz*sizeof(GLfloat), texCoordTemp, GL_STATIC_DRAW);
	
	// Restore the previous state -- may be able to remove when the game is closer to being finished
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	
	// Pixel store variables
	redraw = true;
	store = true;
	glGenTextures(1, &screenTex);		
	screenData = malloc(512*512*4);
				
	
	//- PROJECTILE -//
	bullet = NULL;
	
	
	//--- TOUCH ---//
	touchCount = 0;
	drag = false;	
	actionDelay = 0.5f;
	timePushed = -1;	
	
	
	//---- UNIT ----//	
	sUnit = NULL;
	unitMode = MOVE;	
}

LevelMap::~LevelMap(){
	GLshort i, j;
	
	//--- GENERAL ---//
	for(i = 0; i < MAP_BLOCK[X]; i++){
		for(j = 0; j < MAP_BLOCK[Y]; j++)
			delete gridBlock[i][j];
	}
	delete cursor;
		
	//---- DRAW ----//
	for(i = 0; i < 2; j++)
		delete [] groundStripVert[i];
	delete [] groundStripVert;	
	free(screenData);	
			
	//- PROJECTILE -//
	delete bullet;	
		
	//---- UNIT ----//	
	for(int i = 0; i < unit.size(); i++)
		delete unit[i];
}


GridBlock* LevelMap::getSelectedBlock() const{	
	return sBlock;
}

GridBlock* LevelMap::getBlockByIso(GLshort i, GLshort j){
	if(i < 0 || j < 0 || i >= MAP_BLOCK[X] || j >= MAP_BLOCK[Y])
		return NULL;
	return gridBlock[i][j];
}

GridBlock* LevelMap::getBlockBy3D(GLshort i, GLshort j){	
	// 2D path coords
	GLshort x = i/BLOCK_SIZE_3D[X];
	GLshort y = j/BLOCK_SIZE_3D[Y] - MAP_SIDE;	
	
	// 2D draw coords
	GLshort bX = (x - y)/2.0f;	
	GLshort bY = x + y;
	
	return getBlockByIso(bX, bY);
}

GridBlock* LevelMap::getBlockByOffset(GLshort px, GLshort py) const{
	px += camera.getView(X);	
	py += camera.getView(Y) - MENU_SIZE[Y];
	
	GLshort blockX = px/(BLOCK_SIZE_ISO[Camera::getZoom()][X]/2);
	GLshort blockY = py/(BLOCK_SIZE_ISO[Camera::getZoom()][Y]/2);	
	GLshort remX = px%(BLOCK_SIZE_ISO[Camera::getZoom()][X]/2);
	GLshort remY = py%(BLOCK_SIZE_ISO[Camera::getZoom()][Y]/2);
	
	if((blockX + blockY)%2 == 0){  
		if(remY + remX/2 > BLOCK_SIZE_ISO[Camera::getZoom()][Y]/2){
			blockX++;
			blockY++;
		}
	}
	else{
		if(remY - remX/2 > 0)
			blockY++;
		else
			blockX++;
	}	
	blockX /= 2;
	
	cout << blockX << ", " << blockY << endl;
	
	return getBlockByIso(blockX, blockY);
}


void LevelMap::selectBlock(GridBlock* gb){
	if(sBlock != gb){
		if(sBlock != NULL)
			sBlock->select(false);
		sBlock = gb;
		if(sBlock == NULL)
			cursor->setOffset(-100, -100);	// Arbitrary, offscreen location
		else{
			cursor->setOffset(sBlock->getOffset(X), sBlock->getOffset(Y));	
			sBlock->select(true);
		}
	}	
}
