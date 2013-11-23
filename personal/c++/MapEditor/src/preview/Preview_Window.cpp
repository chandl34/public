#include "Preview_Window.h"

string Preview_Window::relativePath;	
string Preview_Window::mapFolder, Preview_Window::objFolder;	

Fl_File_Chooser* Preview_Window::fileChooser; 
Fl_Menu_Bar* Preview_Window::menubar;
vector<Model_Window*> Preview_Window::mWin;
MapModelContainer* Preview_Window::mapModels;

Preview_Window::Preview_Window(int w, int h, char* t) : Fl_Window(w, h, t){
	mapModels = new MapModelContainer();
	Data::load(*mapModels, "data/mapModels.mmc");
	Camera::resetView();

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
}

Preview_Window::~Preview_Window(){
	delete mapModels;
	delete fileChooser;
	delete menubar; 
	for(size_t i = 0; i < mWin.size(); i++)
		delete mWin.at(i);
}

void Preview_Window::toggleMirror(){
	MapModelContainer::toggleMirror();
	for(size_t i = 0; i < mWin.size(); i++){
		mWin.at(i)->loadModel();
		mWin.at(i)->redraw();		
	}
}

void Preview_Window::toggleInvert(){
	MapModelContainer::toggleInvert();
	for(size_t i = 0; i < mWin.size(); i++){
		mWin.at(i)->loadModel();
		mWin.at(i)->redraw();		
	}
}

void Preview_Window::toggleShift(){
	MapModelContainer::toggleShift();
	for(size_t i = 0; i < mWin.size(); i++){
		mWin.at(i)->loadModel();
		mWin.at(i)->redraw();		
	}
}

void Preview_Window::setRotate(int r){
	MapModelContainer::setRotate(r);
	for(size_t i = 0; i < mWin.size(); i++){
		mWin.at(i)->loadModel();
		mWin.at(i)->redraw();		
	}
}

void Preview_Window::toggleCondition(int c){
	switch(c){
	case WALL: case OBJECT: case FENCE: case WINDOWFRAME: case DOORFRAME: case WINDOW:
		MapModelContainer::setCondition(c);
		for(size_t i = 0; i < mWin.size(); i++){
			mWin.at(i)->loadModel();
			mWin.at(i)->redraw();		
		}
	}
}

void Preview_Window::File_CB(Fl_Widget*w, void*data) {
	if(fileChooser == NULL){
		fileChooser = new Fl_File_Chooser("", "", Fl_File_Chooser::SINGLE, "");	
		fileChooser->preview(false);
		fileChooser->filter("*.map");
	}

	bool save = strcmp(menubar->text(), "Save") == 0;	

	if(save)
		fileChooser->type(Fl_File_Chooser::CREATE);
	else
		fileChooser->type(Fl_File_Chooser::SINGLE);	

	fileChooser->directory(mapFolder.c_str());	

	fileChooser->show();
	while(fileChooser->shown())
		Fl::wait();
	if(fileChooser->value() == NULL)
		return;

	findRelativePath();	
	if(save)
		Data::save(Map_Window::getMap(), relativePath.c_str());
	else
		Data::load(Map_Window::getNewMap(), relativePath.c_str());
}

void Preview_Window::Toggle_CB(Fl_Widget* w, void* data){
	if(strcmp(menubar->text(), "Mirror") == 0)
		toggleMirror();
	else if(strcmp(menubar->text(), "Hinge") == 0)
		toggleInvert();
	else if(strcmp(menubar->text(), "Shift") == 0)
		toggleShift();
	else if(strcmp(menubar->text(), "Wall") == 0)
		toggleCondition(WALL);
	else if(strcmp(menubar->text(), "Object") == 0)
		toggleCondition(OBJECT);
	else if(strcmp(menubar->text(), "Fence") == 0)
		toggleCondition(FENCE);
	else if(strcmp(menubar->text(), "WindowFrame") == 0)
		toggleCondition(WINDOWFRAME);
	else if(strcmp(menubar->text(), "Window") == 0)
		toggleCondition(WINDOW);
	else if(strcmp(menubar->text(), "DoorFrame") == 0)
		toggleCondition(DOORFRAME);
	else if(strcmp(menubar->text(), "Open") == 0)
		setRotate(OPEN);
	else if(strcmp(menubar->text(), "Half-Open") == 0)
		setRotate(HALFOPEN);
	else if(strcmp(menubar->text(), "Closed") == 0)
		setRotate(CLOSED);
}

void Preview_Window::findRelativePath(){
	int s = strlen(fileChooser->directory()) + 1;
	relativePath = fileChooser->value();		
	relativePath = mapFolder + relativePath.substr(s);

	string filter = ".map";
	if(relativePath.substr(relativePath.size() - 4) != filter)
		relativePath += filter;	
}
