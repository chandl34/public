/*
 *  AStarNode.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "AStarNode.h"


AStarNode::AStarNode(const Coord2d<GLshort>& c) : coord(c){	
	// all this is identical to the gridblock data.  could just alias to that gridblock	
	pathCoord[X] = coord[X] + coord[Y]/2 + coord[Y]%2;
	pathCoord[Y] = -coord[X] + coord[Y]/2 + MAP_SIDE;
}


double AStarNode::getValue() const{return priority;}

double AStarNode::getEstimate() const{return _estimate;}
void AStarNode::setEstimate(double e){_estimate = e;}
double AStarNode::getDistance() const{return distance;}												
void AStarNode::setDistance(double d){distance = d;}
double AStarNode::getPriority() const{return priority;}
void AStarNode::setPriority(double p){priority = p;}	
void AStarNode::findPriority(){priority = _estimate + distance;}	


AStarNode* AStarNode::getParent() const{return parent;}
void AStarNode::setParent(AStarNode* a){parent = a;}
GLshort AStarNode::getDirection() const{return dir;}
void AStarNode::setDirection(GLshort d){dir = d;}
const Coord2d<GLshort>& AStarNode::getCoord() const{return coord;}
GLshort AStarNode::getCoord(GLshort c) const{return coord[c];}
GLshort AStarNode::getPathCoord(GLshort c) const{return pathCoord[c];}
const Coord2d<GLshort>& AStarNode::getPathCoord() const{return pathCoord;}


GLshort AStarNode::getStatus() const{return status;}
void AStarNode::setStatus(GLshort s){status = s;}

bool AStarNode::equals(GLshort x, GLshort y) const{return coord[X] == x && coord[Y] == y;}

