/*
 *  Event.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Event.h"


EventHandler::EventHandler()
{
	_maxEventID = 0;
}



EventSignaller::EventSignaller()
{
	_eventHandler = NULL;
}


void EventSignaller::addEventHandler(int& eid, EventHandler* eh)
{
	_eventID = eid;
	_eventHandler = eh;
	++eid;
}


/*
Selectable::Selectable()
: Touchable(false)
{
	_selected = -1;
}

Selectable::~Selectable()
{

}


//--- GENERAL ---//
GLshort Selectable::getSelected() const
{
	return _selected;
}
*/