/*
 *  Stat.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef STAT_H_
#define STAT_H_

#include "Include.h"

// Base
class Stat{
public:
	explicit Stat(GLshort s){stat = s;}

	operator GLshort() const{return stat;}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
	
protected:
	GLshort stat;
};


// Children - Object related
class ObjType : public Stat{
public:
	explicit ObjType(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class Dir : public Stat{
public:
	explicit Dir(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class Side : public Stat{
public:
	explicit Side(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class Inner : public Stat{
public:
	explicit Inner(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class Hinge : public Stat{
public:
	explicit Hinge(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class Open : public Stat{
public:
	explicit Open(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};


// Children - Unit related
class Team : public Stat{
public:
	explicit Team(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class HP : public Stat{
public:
	explicit HP(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

class TU : public Stat{
public:
	explicit TU(GLshort s) : Stat(s){}
	const GLshort& operator= (const GLshort& rhs){stat = rhs; return stat;}
};

#endif

