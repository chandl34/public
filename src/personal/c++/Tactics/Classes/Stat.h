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
	explicit Stat(GLshort s = 0){stat = s;}

	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
	
protected:
	GLshort stat;
};


// Children - Model related
class Dimension : public Stat{
public:
	explicit Dimension(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};


// Children - Object related
class ObjType : public Stat{
public:
	explicit ObjType(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class Dir : public Stat{
public:
	explicit Dir(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class Side : public Stat{
public:
	explicit Side(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class Inner : public Stat{
public:
	explicit Inner(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class Hinge : public Stat{
public:
	explicit Hinge(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class Open : public Stat{
public:
	explicit Open(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};


// Children - Unit related
class HP : public Stat{
public:
	explicit HP(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator--(){return --stat;}
	const GLshort& operator-= (const GLshort& rhs){return stat -= rhs;}
	const GLshort& operator++(){return ++stat;}
	const GLshort& operator+=(const GLshort& rhs){return stat += rhs;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class TU : public Stat{
public:
	explicit TU(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator--(){return --stat;}
	const GLshort& operator-= (const GLshort& rhs){return stat -= rhs;}
	const GLshort& operator++(){return ++stat;}
	const GLshort& operator+=(const GLshort& rhs){return stat += rhs;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};


// Children - Item related
class ItemType : public Stat{
public:
	explicit ItemType(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

// Children - Gun related
class Speed : public Stat{
public:
	explicit Speed(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class Accuracy : public Stat{
public:
	explicit Accuracy(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class AmmoCount : public Stat{
public:
	explicit AmmoCount(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator--(){return --stat;}
	const GLshort& operator-= (const GLshort& rhs){return stat -= rhs;}
	const GLshort& operator++(){return ++stat;}
	const GLshort& operator+=(const GLshort& rhs){return stat += rhs;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

class AmmoType : public Stat{
public:
	explicit AmmoType(GLshort s = 0) : Stat(s){}
	operator GLshort() const{return stat;}
	const GLshort& operator=(const GLshort& rhs){return stat = rhs;}
};

#endif

