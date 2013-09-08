/*
 *  PieceData.mm
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "PieceData.h"

#include "Image.h"

#include "ImageStorage.h"


// PieceFlip
bool& PieceFlip::operator[](GLshort i){
	return flip[i];
}



// AxisEdges
const GLshort& AxisEdges::operator[](GLshort i) const{
	return edge[i];
}

GLshort& AxisEdges::operator[](GLshort i){
	return edge[i];
}

bool AxisEdges::isMatch(const AxisEdges& ae, bool& f){
	if(edge[MINIMUM] == ae.edge[MINIMUM] && 
		edge[MAXIMUM] == ae.edge[MAXIMUM]){
		f = false;
		return true;
	}	
	
	if(edge[MINIMUM] == ae.edge[MAXIMUM] && 
		edge[MAXIMUM] == ae.edge[MINIMUM]){
		f = true;
		return true;
	}	
	
	return false;
}



// PieceEdges
PieceEdges::PieceEdges(GLshort l, GLshort d, GLshort r, GLshort u){
	axis[X][MINIMUM] = l;
	axis[X][MAXIMUM] = r;
	axis[Y][MINIMUM] = d;
	axis[Y][MAXIMUM] = u;
}


//---- GENERAL ----//
GLshort PieceEdges::getEdge(GLshort i)
{
	return axis[i % 2][i / 2];
}

const AxisEdges& PieceEdges::operator[](GLshort i) const{
	return axis[i];
}

AxisEdges& PieceEdges::operator[](GLshort i){
	return axis[i];
}

bool PieceEdges::isMatch(const PieceEdges& pe, PieceFlip& pf, bool r){
	if(axis[X].isMatch(pe.axis[(X + r) % 2], pf[X])){
		if(axis[Y].isMatch(pe.axis[(Y + r) % 2], pf[Y])){
			if(r){
				pf[Y] = !pf[Y];
			}			
			return true;
		}
	}
	
	return false;
}

