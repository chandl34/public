/*
 *  MainFrame.mm
 *  TacticsMapEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainFrame.h"


MainScreen* MainFrame::mainScreen = NULL;
Fl_Menu_Bar* MainFrame::menubar;
Fl_File_Chooser* MainFrame::fileChooser;


MainFrame::MainFrame(int x, int y, int w, int h) 
: Fl_Gl_Window(x, y, w, h)
{   
	Fl::add_timeout(1.0 / FRAMES_PER_SECOND, Timer_CB, (void*)this);
	
	fileChooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "");
	fileChooser->preview(false);
	fileChooser->filter("*.map");
	
	menubar = new Fl_Menu_Bar(0, 0, MAIN_FRAME_SIZE[X] + INFO_FRAME_SIZE[X] + 30, MENU_HEIGHT);
	menubar->add("File/Save", 0, File_CB, (void*)this);  
	menubar->add("File/Load", 0, File_CB, (void*)this);
}

MainFrame::~MainFrame(){
	delete mainScreen;
	
	delete menubar;
	delete fileChooser;
}

void MainFrame::init(){
	mainScreen = new MainScreen();
}


//---- GENERAL ----//
void MainFrame::File_CB(Fl_Widget* w, void* data) {
	bool save = strcmp(menubar->text(), "Save") == 0;	
	
	if(save)
		fileChooser->type(Fl_File_Chooser::CREATE);
	else
		fileChooser->type(Fl_File_Chooser::SINGLE);	
	
	string mapFolder = mainScreen->getFolder();
	fileChooser->directory(mapFolder.c_str());	
	
	fileChooser->show();
	while(fileChooser->shown())
		Fl::wait();
	if(fileChooser->value() == NULL)
		return;
	
	
	int s = strlen(fileChooser->directory()) + 1;
	string relativePath = fileChooser->value();		
	relativePath = mapFolder + relativePath.substr(s);
	
	string filter = mainScreen->getFilter();
	if(relativePath.substr(relativePath.size() - 4) != filter)
		relativePath += filter;	
		
	if(save)
		mainScreen->save(relativePath.c_str());
	else
		mainScreen->load(relativePath.c_str());
}

void MainFrame::Timer_CB(void* userdata)
{
	MainFrame *glwin = (MainFrame*)userdata;
	glwin->redraw();
	Fl::repeat_timeout(1.0 / FRAMES_PER_SECOND, Timer_CB, userdata);
}


//---- DRAW ----//
void MainFrame::draw(){
	if (!valid()) {
		valid(1);
		init();
	}
	
	mainScreen->draw();
}

/*
 
 mapFolder = "data/maps/"; objFolder = "obj/";
 
 menubar = new Fl_Menu_Bar(0, 0, this->w(), 20);        
 menubar->add("File/Save", 0, File_CB, (void*)this);  
 menubar->add("File/Load", 0, File_CB, (void*)this);
 
 menubar->add("Toggle/Mirror", 0, Toggle_CB, (void*)this);
 menubar->add("Toggle/Door/Shift", 0, Toggle_CB, (void*)this);	
 menubar->add("Toggle/Door/Hinge", 0, Toggle_CB, (void*)this);	
 menubar->add("Toggle/Door/Open", 0, Toggle_CB, (void*)this);	
 menubar->add("Toggle/Door/Half-Open", 0, Toggle_CB, (void*)this);	
 menubar->add("Toggle/Door/Closed", 0, Toggle_CB, (void*)this);
 menubar->add("Toggle/Condition/Wall", 0, Toggle_CB, (void*)this);	
 menubar->add("Toggle/Condition/Object", 0, Toggle_CB, (void*)this);
 menubar->add("Toggle/Condition/Fence", 0, Toggle_CB, (void*)this);	
 menubar->add("Toggle/Condition/WindowFrame", 0, Toggle_CB, (void*)this);
 menubar->add("Toggle/Condition/Window", 0, Toggle_CB, (void*)this);
 menubar->add("Toggle/Condition/DoorFrame", 0, Toggle_CB, (void*)this);
 */