/*
 *  LevelMap.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"

#include "CampaignMap.h"
#include "EnemyTeam.h"
#include "Level.h"
#include "Projectile.h"
#include "GridBlock.h"

#include "HitTest.h"
#include "ImageStorage.h"


//--- GENERAL ---//	
LevelMap* LevelMap::_levelMap = NULL;

//---- THREADING ----//
bool LevelMap::_bgActive;
bool LevelMap::_bgKill;
pthread_t LevelMap::_bgthread;
pthread_cond_t LevelMap::_cond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t LevelMap::_mutex = PTHREAD_MUTEX_INITIALIZER;
ViewArgs LevelMap::_viewArgs;


// TEMPORARY
#include "DoorObject.h"
#include "SideObject.h"


LevelMap* LevelMap::getInstance()
{
	if(_levelMap == NULL)
		_levelMap = new LevelMap();
	return _levelMap;
}

LevelMap::LevelMap()
: MapScreen(true)
{
	printf("Building LevelMap...\n");
	
	//---- GRIDBLOCK ----//
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			_gridBlock[i][j] = new GridBlock(Coord2d<GLshort>(i, j));	
	}		
	_sBlock = NULL;
	
	//---- DRAW ----//		
	// Pixel store variables
	_redraw = true;
	_store = true;
	_storeMini = true;
	_resort = true;
	glGenTextures(1, &_screenTex);		
	_screenData = malloc(512*512*4);
	
	
	//---- THREADING ----//
	_bgActive = false;
	_bgKill = false;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
	sched_param sp;
	sp.sched_priority = 47;	
	pthread_attr_setschedparam(&attr, &sp);
	
	if(pthread_create(&_bgthread, &attr, backgroundThread, NULL))
		printf("ERROR: could not open background thread!\n");
	
	//---- UNIT ----//	
	//_team.push_back(new Team());   todo: fix this or won't' be able to open map!
	//_team.push_back(new EnemyTeam());
	_team[PLAYER] = NULL;
	_team[ENEMY] = NULL;
}

LevelMap::~LevelMap(){
	GLshort i, j;
	
	//--- GENERAL ---//
	_levelMap = NULL;
	
	//---- UNIT ----//
	//for(i = 0; i < TEAMS_PER_FIGHT; ++i)  // Note:: for now, units drop items on the ground on deconstruction.  
	//	delete _team[i];				  // ------ this must be called before _gridBlocks are deleted... unless I change that
	
	//---- PROJECTILES ----//	
	for(list<Projectile*>::iterator iter = _proj.begin(); iter != _proj.end(); ++iter)
		delete *iter;
	
	//---- GRIDBLOCK ----//
	for(i = 0; i < MAP_BLOCK[X]; ++i){
		for(j = 0; j < MAP_BLOCK[Y]; ++j)
			delete _gridBlock[i][j];
	}
	
	//---- THREADING ----//
	pthread_mutex_lock(&_mutex);
	_bgActive = true;
	_bgKill = true;
	pthread_cond_signal(&_cond);
	pthread_mutex_unlock(&_mutex);
	
	//---- DRAW ----//
	for(i = 0; i < 2; ++i){
		glDeleteBuffers(MAP_BLOCK[X], _groundStripVert[i]);
		delete [] _groundStripVert[i];
	}
	delete [] _groundStripVert;
	glDeleteBuffers(1, &_groundStripTexCoord);
	
	glDeleteBuffers(1, &_staticObjTexVert);
	glDeleteBuffers(1, &_staticObjTexCoord);
	
	glDeleteTextures(1, &_screenTex);
	free(_screenData);		
}


//--- INIT ---//	
void LevelMap::buildBuffers()
{	
	//--- OBJECT BUFFERS ---//
	{
		for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
			for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
				_gridBlock[i][j]->isoSort(_objList, SORT_STATIC);
		}
		
		// Add static object data to buffers
		glGenBuffers(1, &_staticObjTexVert);	
		glGenBuffers(1, &_staticObjTexCoord);	
		
		vector<GLshort> tempTexVert;
		vector<GLfloat> tempTexCoord;
		for(ObjectList::iterator iter = _objList.begin(); iter != _objList.end(); ++iter)
			(*iter)->buildBuffers(_staticObjTexVert, tempTexVert, _staticObjTexCoord, tempTexCoord);
		cout << "objs: " << _objList.size() << endl;
		_objList.clear();	
		
		// Copy the data to arrays -- C11 gets past this.  maybe I can find that in later versions of XCode?  todo:  check that out
		GLshort sztv = tempTexVert.size();	
		GLshort tempTexVertArray[sztv];
		for(GLshort i = 0; i < sztv; ++i)
			tempTexVertArray[i] = tempTexVert[i];	
		glBindBuffer(GL_ARRAY_BUFFER, _staticObjTexVert);
		glBufferData(GL_ARRAY_BUFFER, sztv * sizeof(GLshort), tempTexVertArray, GL_STATIC_DRAW);
		
		GLshort sztc = tempTexCoord.size();
		GLfloat tempTexCoordArray[sztc];
		for(GLshort i = 0; i < sztc; ++i)
			tempTexCoordArray[i] = tempTexCoord[i];
		glBindBuffer(GL_ARRAY_BUFFER, _staticObjTexCoord);
		glBufferData(GL_ARRAY_BUFFER, sztc * sizeof(GLfloat), tempTexCoordArray, GL_STATIC_DRAW);
		
	}
	
	//--- GROUND BUFFERS ---//
	{
		
		GLshort sz = 8*ceil(MAP_BLOCK[Y]/2.0);
		GLshort sz2 = 8*MAP_BLOCK[Y]/2;
		
		_groundStripVert = new GLuint*[2];// bottom and top overlay
		for(GLshort i = 0; i < 2; ++i){
			_groundStripVert[i] = new GLuint[MAP_BLOCK[X]];
			glGenBuffers(MAP_BLOCK[X], _groundStripVert[i]);	
		}	
		glGenBuffers(1, &_groundStripTexCoord);
		
		GLshort offset;	
		GLshort vertTemp[sz]; 
		GLshort vertTemp2[sz2]; 
		GLfloat texCoordTemp[sz];
		GLshort* blockVert = ImageStorage::getVerts(Size2d<GLshort>(BLOCK_SIZE_ISO[MAX_ZOOM][X], 
																	BLOCK_SIZE_ISO[MAX_ZOOM][Y]));
		
		// This is the default size of ground blocks.  may need to change later
		GLfloat* blockTexCoord = ImageStorage::getTexCoords(Coord2d<GLfloat>(0.625f, 0.375f));		
		
		for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
			offset = 0;
			for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
				if(j % 2 == 0){
					for(GLshort k = 0; k < 8; ++k){
						vertTemp[offset + k] = _gridBlock[i][j]->getOffset(k % 2) + blockVert[k];
						if(i == 0)			// Assume this tajes the same time whether this is there or not, I can change this up kater to save time
							texCoordTemp[offset + k] = blockTexCoord[k];	
					}	
				}
				else{// if(i < MAP_BLOCK[X] - 1){	// Cuts out extra end piece - temporariky removed cause regukar draw doesn't ignore this
					for(GLshort k = 0; k < 8; ++k)					
						vertTemp2[offset + k] = _gridBlock[i][j]->getOffset(k % 2) + blockVert[k];
					offset += 8;
				}		
			}			
			glBindBuffer(GL_ARRAY_BUFFER, _groundStripVert[0][i]);
			glBufferData(GL_ARRAY_BUFFER, sz*sizeof(GLshort), vertTemp, GL_STATIC_DRAW);	
			//	if(i < MAP_BLOCK[X] - 1){				 - temporariky removed cause regukar draw doesn't ignore this										
			glBindBuffer(GL_ARRAY_BUFFER, _groundStripVert[1][i]);
			glBufferData(GL_ARRAY_BUFFER, sz2*sizeof(GLshort), vertTemp2, GL_STATIC_DRAW);		
			//	}
		}
		glBindBuffer(GL_ARRAY_BUFFER, _groundStripTexCoord);
		glBufferData(GL_ARRAY_BUFFER, sz*sizeof(GLfloat), texCoordTemp, GL_STATIC_DRAW);
		
		// Restore the previous state -- may be able to remove when the game is closer to being finished
		glBindBuffer(GL_ARRAY_BUFFER, 0);	
	}
}

void LevelMap::initLevel(bool isNew)
{
	CampaignMap* campaign = CampaignMap::getInstance();
	Level* sLevel = campaign->getSelectedLevel();
	Team* d = sLevel->getTeam(OWNER);
	Team* a = sLevel->getTeam(INTRUDER);
	
	// Determine player faction
	if(a->getFactionID() == PLAYER){
		_team[PLAYER] = a;
		_team[ENEMY] = d;
	}
	else{
		_team[PLAYER] = d;
		_team[ENEMY] = a;
	}
	
	// Place units
	for(GLshort i = 0; i < TEAMS_PER_FIGHT; ++i)
		_team[i]->initLevel(*_team[(i + 1) % 2], isNew);
	
	// Start initial turn -- todo: make this random?
	if(isNew)
		_team[PLAYER]->newTurnLevel(*_team[ENEMY]);
	else 
		_team[PLAYER]->selectNextUnit();		// todo: REMOVE!  temp until I save selection
	
	// Center camera on first unit
	Unit* sUnit = getSelectedUnit();
	if(isNew)
		centerView(sUnit->getOffset(X), sUnit->getOffset(Y));
}


//--- GENERAL ---//	
Camera* LevelMap::getCamera()
{
	return &_camera;
}

void LevelMap::centerView(GLshort x, GLshort y)
{	
	_camera.centerOn(x, y);	
	
	_redraw = true;
	_store = true;
	_resort = true;
}

bool LevelMap::onScreen(const Coord2d<GLshort>& p)
{
	return pointInQuad(p, 
					   Coord2d<double>(_camera.getView(X), 
									   _camera.getView(Y)), 
					   Size2d<GLshort>(MAP_VIEW_SIZE[_camera.getZoom()][X],
									   MAP_VIEW_SIZE[_camera.getZoom()][Y]));																			
}


//---- GRIDBLOCK ----//
GridBlock* LevelMap::getSelectedBlock()
{	
	return _sBlock;
}

GridBlock* LevelMap::getBlockByIso(GLshort i, GLshort j)
{
	if(i < 0 || j < 0 || i >= MAP_BLOCK[X] || j >= MAP_BLOCK[Y])
		return NULL;
	return _gridBlock[i][j];
}

GridBlock* LevelMap::getBlockByPath(GLshort i, GLshort j)
{	
	// 2D path coords
	GLshort x = i;
	GLshort y = j - MAP_SIDE;	
	
	// 2D draw coords
	GLshort bX = (x - y) / 2.0;	
	GLshort bY = x + y;
	
	return getBlockByIso(bX, bY);
}

GridBlock* LevelMap::getBlockBy3D(GLshort i, GLshort j)
{	
	// 2D path coords
	GLshort x = i / BLOCK_SIZE_3D[X];
	GLshort y = j / BLOCK_SIZE_3D[Y] - MAP_SIDE;	
	
	// 2D draw coords
	GLshort bX = (x - y) / 2.0;	
	GLshort bY = x + y;
	
	return getBlockByIso(bX, bY);
}

GridBlock* LevelMap::getBlockByOffset(GLshort px, GLshort py) const
{
	px += _camera.getRelativeView(X);	
	py += _camera.getRelativeView(Y) - MENU_SIZE[Y];
	
	GLshort blockX = px / (BLOCK_SIZE_ISO[_camera.getZoom()][X] / 2);
	GLshort blockY = py / (BLOCK_SIZE_ISO[_camera.getZoom()][Y] / 2);	
	GLshort remX = px % (BLOCK_SIZE_ISO[_camera.getZoom()][X] / 2);
	GLshort remY = py % (BLOCK_SIZE_ISO[_camera.getZoom()][Y] / 2);
	
	if((blockX + blockY) % 2 == 0){  
		if(remY + remX / 2 > BLOCK_SIZE_ISO[_camera.getZoom()][Y] / 2){
			++blockX;
			++blockY;
		}
	}
	else{
		if(remY - remX / 2 > 0)
			++blockY;
		else
			++blockX;
	}	
	blockX /= 2;
	
	///*	
	cout << endl << "ISO:  (" << blockX << ", " << blockY << ")" << endl;
	
	GLshort pathX = blockX + blockY / 2 + blockY % 2;
	GLshort pathY = -blockX + blockY / 2 + MAP_SIDE;	
	cout << "PATH:  (" << pathX << ", " << pathY << ")" << endl;
	cout << "DANGER:  " << _gridBlock[blockX][blockY]->getDangerLevel() << endl;
	//*/
	
	return _gridBlock[blockX][blockY];
}

void LevelMap::selectBlock(GridBlock* gb)
{
	_sBlock = gb;
	selectTarget(_sBlock);
}


//---- PROJECTILES ----//	
void LevelMap::addProjectile(Projectile* p)
{
	_proj.push_back(p);	
}
