/*
 *  TitleScreen.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "TitleScreen.h"

#include "MainScreen.h"

#include "ImageStorage.h"

#include "Button.h"
#include "ComplexMenu.h"
#include "Menu.h"
#include "PopupMenu.h"


TitleScreen::TitleScreen()
: BaseScreen(false)
{
	printf("Building Title Screen...\n");
	_base.setImage(ImageStorage::getBGImage(0));
	
	
	// TESTING !~~~~
	// adding some components
	Icon* icon;
	Image* image;
	Section* section;
	Button* button;
	Menu* menu;
	PopupMenu* popupMenu;
	ComplexMenu* complexMenu;
	GLshort buttons;
	
	// Section 1
	image = new Image();
	ImageStorage::addImage(image);	
	section = new Section(image,
						  Coord2d<double>(50, 20),
						  Size2d<GLshort>(100, 100),
						  false);
	section->setColor(Color(0.8, 0.8, 0.8, 1));
	_base.addComponent(section);
	
	image = new Image();
	ImageStorage::addImage(image);		
	icon = new Icon(image, Coord2d<double>(5, 5), Size2d<GLshort>(40, 20));
	icon->setColor(Color(0.2, 0.2, 0.2, 1));
	section->addComponent(icon);
	
	image = new Image();
	ImageStorage::addImage(image);		
	icon = new Icon(image, Coord2d<double>(-10, 90), Size2d<GLshort>(40, 20));
	icon->setColor(Color(0.2, 0.2, 0.2, 1));
	section->addComponent(icon);
	
	image = new Image();
	ImageStorage::addImage(image);		
	icon = new Icon(image, Coord2d<double>(90, -10), Size2d<GLshort>(40, 20));
	icon->setColor(Color(0.2, 0.2, 0.2, 1));
	section->addComponent(icon);
	
	
	// Section 2
	image = new Image();
	ImageStorage::addImage(image);	
	section = new Section(image,
						  Coord2d<double>(300, 150),
						  Size2d<GLshort>(120, 120),
						  false);
	section->setColor(Color(0.8, 0.8, 0.8, 1));
	_base.addComponent(section);
	
	image = new Image();
	ImageStorage::addImage(image);		
	icon = new Icon(image, Coord2d<double>(5, 5), Size2d<GLshort>(40, 20));
	icon->setColor(Color(0.2, 0.2, 0.2, 1));
	section->addComponent(icon);
	
	image = new Image();
	ImageStorage::addImage(image);		
	icon = new Icon(image, Coord2d<double>(-10, 90), Size2d<GLshort>(40, 20));
	icon->setColor(Color(0.2, 0.2, 0.2, 1));
	section->addComponent(icon);
	
	image = new Image();
	ImageStorage::addImage(image);		
	icon = new Icon(image, Coord2d<double>(90, -10), Size2d<GLshort>(40, 20));
	icon->setColor(Color(0.2, 0.2, 0.2, 1));
	section->addComponent(icon);
	
	// ComplexMenu 1
	complexMenu = new ComplexMenu();
	_base.addComponent(complexMenu);
	
	// Button 1
	image = new Image();
	ImageStorage::addImage(image);
	button = new Button(image, Coord2d<double>(30, 260), Size2d<GLshort>(40, 40));
	button->setColor(Color(0.7, 0.7, 0.7, 1));
	complexMenu->addButton(button);
	
	// Button 1 -- events
	button->addEventHandler(_maxEventID, this);
	
	
	// Menu 1
	menu = new Menu(Coord2d<double>(300, 10), Size2d<GLshort>(40, 40), Size2d<GLshort>(3, 2));
	menu->setColor(Color(1, 0.7, 0.7, 1));
	_base.addComponent(menu);
	
	// Menu 1 -- events
	buttons = 3 * 2;
	for(GLshort i = 0; i < buttons; ++i){
		button = menu->getButton(i);
		button->addEventHandler(_maxEventID, this);
	}
	
	
	// PopupMenu 1
	image = new Image();
	ImageStorage::addImage(image);
	popupMenu = new PopupMenu(image, 
							  Coord2d<double>(170, 60), 
							  Size2d<GLshort>(60, 40), 
							  Size2d<GLshort>(60, 40),
							  Size2d<GLshort>(1, 5));
	popupMenu->setColor(Color(0.7, 1, 0.7, 1));
	complexMenu->addButton(popupMenu);
	
	// PopupMenu 1 -- events
	buttons = 1 * 5;
	popupMenu->addEventHandler(_maxEventID, this);
	for(GLshort i = 0; i < buttons; ++i){
		button = popupMenu->getButton(i);
		button->addEventHandler(_maxEventID, this);
	}
}

TitleScreen::~TitleScreen()
{
	
}

//---- DRAW ----//
void TitleScreen::draw(bool step, TexAttr* ta)
{
	BaseScreen::draw(step, ta);
}

//--- TOUCH ---//
bool TitleScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	_base.push(t, p);
	
	return true;
}

bool TitleScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	_base.move(t, p);
	
	return true;
}

bool TitleScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	_base.release(t, p);
	
	return true;
}


//--- EVENT ---//
void TitleScreen::handleEvent(int eid, void* arg)
{
	cout << "event " << eid << endl;
}
