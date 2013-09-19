/*
 *  MainScreen.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MAIN_SCREEN_H_
#define MAIN_SCREEN_H_

#include "Screen.h"

#include "ImageStorage.h"
#include "ModelStorage.h"


class MainScreen : public SaveableScreen{
public:
	MainScreen();
	~MainScreen();
	
	//---- GENERAL ----//
	static void setScreen(GLshort);
	
	//---- IO ----//
	string getFolder();
	string getFilter();
	void save(const string&);
	void load(const string&);
	
	//---- DRAW ----//
	void draw();
	
	//--- CONTROLS ---//
	void keyDown(GLshort);
	void push(GLshort, const Coord2d<GLshort>&);
	void move(GLshort, const Coord2d<GLshort>&);
	bool release(GLshort, const Coord2d<GLshort>&);	
	 
private:
	//---- GENERAL ----//
	// Data Storage
	ImageStorage imageStorage;
	ModelStorage modelStorage;
	
	// Screens
	static SaveableScreen* currentScreen;
	static vector<SaveableScreen*> screen;
	
	// FPS
	GLuint frames;
	GLuint totalFrames;
	double lastTime;
	double timeElapsed;
	
	//---- DRAW ----//
	void draw(bool);		 
};


#endif