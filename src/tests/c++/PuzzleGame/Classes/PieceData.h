/*
 *  PieceData.h
 *  PuzzleGame
 *
 *  Created by Jonathan Chandler on 11/25/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef PIECE_DATA_H_
#define PIECE_DATA_H_

#include "Include.h"


struct PieceFlip{
	bool& operator[](GLshort);
	
private:
	bool flip[2];
};


struct AxisEdges{	
	bool isMatch(const AxisEdges&, bool&);
	
	const GLshort& operator[](GLshort) const;
	GLshort& operator[](GLshort);
	
private:
	GLshort edge[2];	
};


struct PieceEdges{	
	PieceEdges(GLshort, GLshort, GLshort, GLshort);
	
	GLshort getEdge(GLshort);
	
	bool isMatch(const PieceEdges&, PieceFlip&, bool);
	
private:
	AxisEdges axis[2];
	
	const AxisEdges& operator[](GLshort) const;
	AxisEdges& operator[](GLshort);
};



#endif