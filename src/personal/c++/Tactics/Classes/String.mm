/*
 *  String.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/31/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "String.h"


string numToString(GLshort num, GLshort digits)
{
	string ret;
	bool started = false;
	for(GLshort i = digits - 1; i >= 0; --i){
		GLshort comp = num / pow(10, i);
		if(comp == 0 && !started && i != 0)
			;//ret += "  "; // disabled
		else{
			ret += comp + CHAR_NUM_OFFSET;
			num -= comp * pow(10, i);
			started = true;
		}
	}
	
	return ret;
}