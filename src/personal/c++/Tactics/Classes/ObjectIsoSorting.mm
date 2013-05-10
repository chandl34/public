/*
 *  ObjectIsoSorting.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"

#include "Model.h"


//--- ISO SORTING ---//
double Object::getGlobalLoc(GLshort c, const Dimension& m, GLshort s) const
{
	return _model->getRelativeLoc(c, m) + getCoord3D(c);
}


void Object::isoSort(ObjectList& objList){
	for(ObjectList::iterator iter = objList.begin(); iter != objList.end(); ++iter)
	{
		// Behind in X direction
		if(getGlobalLoc(X, Dimension(MINIMUM)) > (*iter)->getGlobalLoc(X, Dimension(MINIMUM))){		
			// Contained or beyond in Y direction	
			if(getGlobalLoc(Y, Dimension(MAXIMUM)) > (*iter)->getGlobalLoc(Y, Dimension(MINIMUM))){
				objList.insert(iter, this);
				return;
			}			
		}		
		// Behind in Y direction
		else if(getGlobalLoc(Y, Dimension(MINIMUM)) > (*iter)->getGlobalLoc(Y, Dimension(MINIMUM))){		
			// Contained or beyond in X direction				
			if(getGlobalLoc(X, Dimension(MAXIMUM)) > (*iter)->getGlobalLoc(X, Dimension(MINIMUM))){	
				objList.insert(iter, this);
				return;
			}	
		}
	}
	objList.push_back(this);
}

