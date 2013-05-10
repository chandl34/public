/*
 *  MainScreenTemp.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainScreen.h"

#include "Ammo.h"
#include "AmmoData.h"
#include "Grenade.h"
#include "Gun.h"
#include "Image.h"
#include "GrenadeData.h"
#include "GunData.h"
#include "Model.h"

#include "ModelIO.h"
#include "TextureIO.h"


void MainScreen::tempInit()
{
	// todo: make all of these loaded from a text file in the future
	//---- BUILD STORAGES ----//	
	printf("\n//--- Loading Images ---//\n");
	Image* tempImg;
	vector<Image*> tempImgs;
	ImageSet* tempImgSet;
	GLshort i, j, k, l;				// Lot of repitition here.  Should find a better storage method
	
	// Cursors
	_imageStorage.setCursorImage(MOVE, loadPNG("moveCursor", Size2d<GLshort>(80, 41)));
	
	// Sight Indicators
	_imageStorage.setSightIndicatorImage(FULL_LOS, loadPNG("green", Size2d<GLshort>(80, 40)));
	_imageStorage.setSightIndicatorImage(MID_LOS, loadPNG("yellow", Size2d<GLshort>(80, 40)));
	_imageStorage.setSightIndicatorImage(LOW_LOS, loadPNG("orange", Size2d<GLshort>(80, 40)));
	_imageStorage.setSightIndicatorImage(NO_LOS, loadPNG("red", Size2d<GLshort>(80, 40)));
	
	// Footsteps
	_imageStorage.setFootstepImage(DOWN_LEFT, loadPNG("downLeftArrow", Size2d<GLshort>(80, 40), Coord2d<double>(-20, -10)));
	_imageStorage.setFootstepImage(LEFT, loadPNG("leftArrow", Size2d<GLshort>(80, 40), Coord2d<double>(-40, 0)));
	_imageStorage.setFootstepImage(UP_LEFT, loadPNG("upLeftArrow", Size2d<GLshort>(80, 40), Coord2d<double>(-20, 10)));
	_imageStorage.setFootstepImage(UP, loadPNG("upArrow", Size2d<GLshort>(80, 40), Coord2d<double>(0, 20)));
	_imageStorage.setFootstepImage(UP_RIGHT, loadPNG("upRightArrow", Size2d<GLshort>(80, 40), Coord2d<double>(20, 10)));
	_imageStorage.setFootstepImage(RIGHT, loadPNG("rightArrow", Size2d<GLshort>(80, 40), Coord2d<double>(40, 0)));
	_imageStorage.setFootstepImage(DOWN_RIGHT, loadPNG("downRightArrow", Size2d<GLshort>(80, 40), Coord2d<double>(20, -10)));
	_imageStorage.setFootstepImage(DOWN, loadPNG("downArrow", Size2d<GLshort>(80, 40), Coord2d<double>(0, -20)));	
	
	// ConstObject
	_imageStorage.addConstImage(ObjType(GROUND), loadPNG("ground", Size2d<GLshort>(80, 40)));	
	_imageStorage.addConstImage(ObjType(BULLET), new Image(Size2d<GLshort>(2, 2), 0));	
	_imageStorage.addConstImage(ObjType(THROWN_ITEM), new Image(Size2d<GLshort>(2, 2), 0));
	
	// SideObject
	_imageStorage.addSideImage(ObjType(WALL), Side(LEFT_SIDE), loadPNG("wall0", Size2d<GLshort>(44, 124)));
	_imageStorage.addSideImage(ObjType(WALL), Side(RIGHT_SIDE), loadPNG("wall1", Size2d<GLshort>(44, 124)));
	_imageStorage.addSideImage(ObjType(TOP_FRAME), Side(LEFT_SIDE), loadPNG("topFrame0", Size2d<GLshort>(44, 29)));
	_imageStorage.addSideImage(ObjType(TOP_FRAME), Side(RIGHT_SIDE), loadPNG("topFrame1", Size2d<GLshort>(44, 29)));
	_imageStorage.addSideImage(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), loadPNG("bottomFrame0", Size2d<GLshort>(40, 64)));
	_imageStorage.addSideImage(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), loadPNG("bottomFrame1", Size2d<GLshort>(40, 64)));
	_imageStorage.addSideImage(ObjType(FRONT_FRAME), Side(LEFT_SIDE), loadPNG("cornerFrame0", Size2d<GLshort>(6, 103)));
	_imageStorage.addSideImage(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), loadPNG("cornerFrame1", Size2d<GLshort>(6, 103)));
	_imageStorage.addSideImage(ObjType(SIDE_FRAME), Side(LEFT_SIDE), loadPNG("cornerFrame0", Size2d<GLshort>(6, 103)));
	_imageStorage.addSideImage(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), loadPNG("cornerFrame1", Size2d<GLshort>(6, 103)));	
	
	// RotateObject
	tempImgSet = _imageStorage.addImageSet();
	tempImgSet->addImage(loadPNG("unit_kneel_down_left", Size2d<GLshort>(38, 68), Coord2d<double>(8, 4)));
	for(GLshort i = 0; i < PATH_DIRS; ++i)
		tempImgSet->addAnimation(AnimDesc(KNEEL_ANIM, i), 0, 1);	// Kneel
	
	tempImgSet->addImage(loadPNG("unit_down_left", Size2d<GLshort>(31, 94), Coord2d<double>(-2, -2)));	
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, DOWN_LEFT), 1, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, DOWN_LEFT), 1, 1);	// Move
	
	tempImgSet->addImage(loadPNG("unitDownLeft", Size2d<GLshort>(28, 91)));	
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, UP_RIGHT), 2, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, UP_RIGHT), 2, 1);	// Move
	
	tempImgSet->addImage(loadPNG("unitDownRight", Size2d<GLshort>(28, 91)));
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, UP_LEFT), 3, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, UP_LEFT), 3, 1);	// Move	
	
	tempImgSet->addImage(loadPNG("unitDown", Size2d<GLshort>(22, 86), Coord2d<double>(2, 0)));
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, DOWN), 4, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, DOWN), 4, 1);	// Move	
	
	tempImgSet->addImage(loadPNG("unitDown", Size2d<GLshort>(22, 86), Coord2d<double>(2, 0)));
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, UP), 5, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, UP), 5, 1);	// Move	
	
	tempImgSet->addImage(loadPNG("unitLeft", Size2d<GLshort>(10, 86), Coord2d<double>(2, 0)));	
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, LEFT), 6, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, LEFT), 6, 1);	// Move	
	
	tempImgSet->addImage(loadPNG("unitLeft", Size2d<GLshort>(10, 86), Coord2d<double>(2, 0)));
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, RIGHT), 7, 1);	// Idle
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, RIGHT), 7, 1);	// Move	
	
	tempImgSet->addImage(loadPNG("unit_stand", Size2d<GLshort>(50, 93), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_1", Size2d<GLshort>(50, 94), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_2", Size2d<GLshort>(50, 94), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_3", Size2d<GLshort>(50, 95), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_4", Size2d<GLshort>(50, 95), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_5", Size2d<GLshort>(50, 94), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_6", Size2d<GLshort>(50, 93), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_walk_7", Size2d<GLshort>(50, 92), Coord2d<double>(-14, 0)));
	tempImgSet->addImage(loadPNG("unit_kneel_down_left", Size2d<GLshort>(38, 68), Coord2d<double>(8, 4)));	
	tempImgSet->addAnimation(AnimDesc(IDLE_ANIM, DOWN_RIGHT), 8, 1);	// Stand
	tempImgSet->addAnimation(AnimDesc(MOVE_ANIM, DOWN_RIGHT), 8, 8);	// Walk
	
	// DoorObject
	for(i = 0; i < 2; ++i){
		for(j = 0; j < 2; ++j){
			for(k = 0; k < 2; ++k){
				for(l = 0; l < 2; ++l){
					if((i + l)%2 == 0)
						_imageStorage.addDoorImage(ObjType(DOOR), Side(i), Inner(j), Hinge(k), Open(l), loadPNG("door0", Size2d<GLshort>(38, 113)));
					else
						_imageStorage.addDoorImage(ObjType(DOOR), Side(i), Inner(j), Hinge(k), Open(l), loadPNG("door1", Size2d<GLshort>(38, 113)));		
				}
			}
		}		
	}	
	
	// UI Icons
	_imageStorage.setUIImage(UNIT_ICON, loadPNG("icon_unit", Size2d<GLshort>(90, 30)));
	
	
	// Backgrounds
	_imageStorage.addBGImage(loadPNG("the_great_wave_off_kanagawa", Size2d<GLshort>(480, 320)));
	_imageStorage.addBGImage(loadPNG("risk", Size2d<GLshort>(480, 320)));
	
	// Build Font Storage
	tempImgs = loadPNG("font");
	for(GLshort i = 0; i < tempImgs.size(); ++i)
		_imageStorage.setFontImage(i, tempImgs[i]);
	tempImgs.clear();
	
	// Build Interface container
	tempImgs = loadPNG("itemSlots");
	for(GLshort i = 0; i < ITEM_SLOT_SIZES; ++i)
		_imageStorage.setItemSlotImage(i, tempImgs[i]);
	tempImgs.clear();	
	
	
	printf("\n//--- Loading Item Data ---//\n"); // todo: fix this so Images are decoupled from ItemData
	// Build Items Storage
	tempImgs = loadPNG("items");
	AmmoData* ammo = new AmmoData(ItemType(AMMO), 0,
								  tempImgs[0], "Grenade", 
								  AmmoType(AMMO_9MM), AmmoCount(40));	
	_itemDataStorage.addItemData(ammo);
	
	GunData* gun = new GunData(ItemType(GUN), 0,
							   tempImgs[1], "Colt 45",
							   Speed(300), Accuracy(85), 
							   AmmoType(AMMO_9MM), AmmoCount(40));	
	_itemDataStorage.addItemData(gun);
	
	GrenadeData* gren = new GrenadeData(ItemType(GRENADE), 0,
										tempImgs[2], "Med Kit");	
	_itemDataStorage.addItemData(gren);
	
	ItemData* item = new ItemData(ItemType(ITEM), 0,
								  tempImgs[3], "Bullet-proof Vest");	
	_itemDataStorage.addItemData(item);
	
	gun = new GunData(ItemType(GUN), 1,
					  tempImgs[4], "AK 69",
					  Speed(650), Accuracy(100), 
					  AmmoType(AMMO_7_62), AmmoCount(30));
	_itemDataStorage.addItemData(gun);
	
	tempImgs.clear();	
	
	
	printf("\n//--- Loading Models ---//\n");
	// One ring to rule them all
	Model* m;
	
	// ConstObject
	_modelStorage.setConstModel(ObjType(GROUND), loadOBJ("ground"));	
	_modelStorage.setConstModel(ObjType(BULLET), loadOBJ("blank"));
	_modelStorage.setConstModel(ObjType(THROWN_ITEM), loadOBJ("blank"));
	
	// SideObject
	m = loadOBJ("wall");
	m->addBlockedDir(LEFT);
	m->addBlockedDir(DOWN_LEFT);
	m->addBlockedDir(DOWN);
	_modelStorage.setSideModel(ObjType(WALL), m);	
	
	// wall frames
	_modelStorage.setSideModel(ObjType(TOP_FRAME), loadOBJ("topFrame"));
	
	m = loadOBJ("bottomFrame");
	m->addBlockedDir(DOWN_LEFT);
	_modelStorage.setSideModel(ObjType(BOTTOM_FRAME), m);
	
	m = loadOBJ("frontFrame");
	m->addBlockedDir(DOWN);
	_modelStorage.setSideModel(ObjType(FRONT_FRAME), m);
	
	m = loadOBJ("sideFrame");
	m->addBlockedDir(LEFT);
	_modelStorage.setSideModel(ObjType(SIDE_FRAME), m);
	
	// RotateObject
	_modelStorage.setRotateModel(ObjType(HEAD), false, loadOBJ("head"));
	_modelStorage.setRotateModel(ObjType(TORSO), false, loadOBJ("torso"));
	_modelStorage.setRotateModel(ObjType(LEGS), false, loadOBJ("legs"));	
	_modelStorage.setRotateModel(ObjType(UNIT), false, loadOBJ("unit"));
	
	_modelStorage.setRotateModel(ObjType(HEAD), true, loadOBJ("unit_kneel_head"));
	_modelStorage.setRotateModel(ObjType(TORSO), true, loadOBJ("unit_kneel_torso"));
	_modelStorage.setRotateModel(ObjType(LEGS), true, loadOBJ("unit_kneel_legs"));	
	_modelStorage.setRotateModel(ObjType(UNIT), true, loadOBJ("unit_kneel"));
	
	// DoorObject
	_modelStorage.setDoorModel(ObjType(DOOR), loadOBJ("door"));
}



/*
 printf("Loading %s.obj...\n", filename);
 NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithCString:filename] ofType:@"obj"];
 
 ifstream file;
 file.open([path UTF8String]);
 
 if(file.fail()){
 printf("Failed to load %s.obj!\n", filename);
 return NULL;
 }
 */
/*
 const char* filename = "test";
 NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithCString:filename] ofType:@"sav"];
 ofstream file;
 file.open([path UTF8String]);
 
 if(file.fail()){
 printf("Failed to load %s.sav!\n", filename);
 }
 file.close();
 */
/*
 NSArray *searchPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
 NSUserDomainMask, YES);
 
 NSString *documentsPath = [searchPaths objectAtIndex:0];
 
 string respath( [ documentsPath UTF8String ] ) ;
 
 string filename = respath + "/" + "test.sav";
 
 ofstream ofile;
 ofile.open(filename.c_str());
 
 if(ofile.fail())
 printf("Failed to load %s!\n", filename.c_str());
 else{
 ofile << "Hello, World!" << endl;
 
 ofile.close();
 }
 
 ifstream ifile;
 ifile.open(filename.c_str());
 
 if(ifile.fail())
 printf("Failed to load %s!\n", filename.c_str());
 else{
 string word1, word2;
 ifile >> word1;
 ifile >> word2;
 
 cout << "word1 = " << word1 << '\n' << "word2 = " << word2 << '\n';
 
 ifile.close();
 }
 */