/*
 *  ObjectIsoSorting.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/23/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Object.h"


//--- ISO SORTING ---//
GLfloat Object::getRange(GLshort c, GLshort m) const{
	return model->getRange(c, m);
}


void Object::isoSort(list<Object*>& objList){
	for(list<Object*>::iterator iter = objList.begin(); iter != objList.end(); iter++){
		// Behind in X direction
		if(getRange(X, MIN_C) + getCoord3D(X) > (*iter)->getRange(X, MIN_C) + (*iter)->getCoord3D(X)){		
			// Contained or beyond in Y direction	
			if(getRange(Y, MAX_C) + getCoord3D(Y) > (*iter)->getRange(Y, MIN_C) + (*iter)->getCoord3D(Y)){
				// Hack job in the Z direction?
			//	if(getRange(Z, MAX_C) + getCoord3D(Z) <= (*iter)->getRange(Z, MAX_C) + (*iter)->getCoord3D(Z)){
					objList.insert(iter, this);
					return;
			//	}
			}			
		}		
		// Behind in Y direction
		else if(getRange(Y, MIN_C) + getCoord3D(Y) > (*iter)->getRange(Y, MIN_C) + (*iter)->getCoord3D(Y)){		
			// Contained or beyond in X direction				
			if(getRange(X, MAX_C) + getCoord3D(X) > (*iter)->getRange(X, MIN_C) + (*iter)->getCoord3D(X)){	// +10 fixes problems with "too wide" characters
				// Hack job in the Z direction?
			//	if(getRange(Z, MAX_C) + getCoord3D(Z) <= (*iter)->getRange(Z, MAX_C) + (*iter)->getCoord3D(Z)){
					objList.insert(iter, this);
					return;
			//	}
			}	
		}
		/*
		// Behind in X direction
		if(getRange(X, MIN_C) + getCoord3D(X) > (*iter)->getRange(X, MIN_C) + (*iter)->getCoord3D(X)){		
			// Contained or beyond in Y direction			
			if(getRange(Y, MAX_C) + getCoord3D(Y) > (*iter)->getRange(Y, MIN_C) + (*iter)->getCoord3D(Y)){
				objList.insert(iter, this);
				return;
			}			
		}		
		// Behind in Y direction
		else if(getRange(Y, MIN_C) + getCoord3D(Y) > (*iter)->getRange(Y, MIN_C) + (*iter)->getCoord3D(Y)){		
			// Contained or beyond in X direction				
			if(getRange(X, MAX_C) + getCoord3D(X) + 5 > (*iter)->getRange(X, MIN_C) + (*iter)->getCoord3D(X)){	// +5 fixes problems with "too wide" characters
				objList.insert(iter, this);
				return;
			}	
		}
		 */
	}
	objList.push_back(this);
}

