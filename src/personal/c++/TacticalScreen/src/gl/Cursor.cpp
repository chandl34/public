#include "Cursor.h"
#include "Game_Window.h"
#include "controls/Mouse.h"

int Cursor::mode;
int Cursor::prevMode;
int* Cursor::id;
Coordinate* Cursor::sCoord;
Model* Cursor::cursor;
Model* Cursor::cursor2;
	
Cursor::Cursor(){
	id = new int[3];
	mode = MOVE;	
	sCoord = NULL;

	cursor = Reader::readOBJ("obj/UI/cursors/move.obj");
	cursor2 = Reader::readOBJ("obj/UI/cursors/shoot.obj");
	/*
	Model* temp = Reader::readOBJ("obj/UI/cursors/move.obj");
	id[MOVE] = glGenLists(1);
	glNewList(id[MOVE], GL_COMPILE);
	temp->draw(0, 0, 0);
	glEndList();
	delete temp;
	*/
}

Cursor::~Cursor(){
	delete [] id;
	delete cursor;
	delete cursor2;
}

void Cursor::toggleMoveShootMode(){
	if(mode == MOVE)
		mode = SHOOT;
	else if (mode == SHOOT)
		mode = MOVE;
}

void Cursor::toggleUseMode(){
	if(mode == USE)
		mode = prevMode;
	else if(mode != LOOK){
		prevMode = mode;
		mode = USE;
	}
}

void Cursor::toggleLookMode(){
	if(mode == LOOK)
		mode = prevMode;
	else if(mode != USE){
		prevMode = mode;
		mode = LOOK;
	}
}


int Cursor::getMode(){return mode;}

void Cursor::selectCoord(Coordinate* c){sCoord = c;}
Coordinate* Cursor::getSelectedCoord(){return sCoord;}
int Cursor::getCursor(){return id[mode];}
void Cursor::revertMode(){mode = prevMode;}

void Cursor::draw(){
	if(mode == MOVE){
		if(sCoord != NULL)
			cursor->draw(sCoord->get(X), 0, sCoord->get(Y));
	}
	else{
		glPushMatrix();				
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();						
		glOrtho(0 ,Game_Window::width(), 0, Game_Window::height(), -10, 10);
		glMatrixMode(GL_MODELVIEW);		
		glLoadIdentity();			
		cursor2->draw(Mouse::get(X), Game_Window::height() - Mouse::get(Y), 0);
		glPopMatrix();		
	}
		
}
