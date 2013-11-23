/*
 *  Event.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef EVENT_H_
#define EVENT_H_

#include "Include.h"


class EventHandler{
public:
	EventHandler();
	
	virtual void handleEvent(int, void* = NULL) = 0;
	
protected:
	int _maxEventID;
};


class EventSignaller{
public:
	EventSignaller();
	
	void addEventHandler(int&, EventHandler*);
	
protected:
	int _eventID;
	EventHandler* _eventHandler;
};


/*
#include "Touchable.h"

class Button;
class Image;


class Selectable : public Touchable{
public:
	Selectable();
	virtual ~Selectable();
	
	//--- GENERAL ---//
	GLshort getSelected() const;
	
	virtual Button* getButton(GLshort = 0) = 0;
	
protected:
	GLshort _selected;
};
*/

#endif
