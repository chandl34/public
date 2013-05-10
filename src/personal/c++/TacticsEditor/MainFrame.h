/*
 *  MainFrame.h
 *  TacticsMapEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MAIN_FRAME_H_
#define MAIN_FRAME_H_

#include "MainScreen.h"


class MainFrame : public Fl_Gl_Window{
public:
	MainFrame(int, int, int, int);
	virtual ~MainFrame();
	
private:
	void init();		
	static void File_CB(Fl_Widget*, void*);
	static void Timer_CB(void*);
	
	
	//---- GENERAL ----//	
	static MainScreen* mainScreen;
	static Fl_Menu_Bar* menubar;
	static Fl_File_Chooser* fileChooser;
	
	//---- DRAW ----//
	void draw();	
	
	//---- CONTROLS ----//
	int handle(int e);
	GLshort key;
};

#endif 
