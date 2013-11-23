#ifndef ASTEROID_C34_H_
#define ASTEROID_C34_H_

#include "GameObject.h"

#include <list>
#include <string>

class Asteroid;

typedef std::shared_ptr<Asteroid> AsteroidPtr;
typedef std::list<AsteroidPtr> AsteroidList;


const int ASTEROID_TYPES = 3;
enum{DIGITROID, OPEROID, MATHTEROID};


class Asteroid
: public GameObject
{
public:
	Asteroid(int,
				const Color_c34&,	
				int = 0);
	virtual ~Asteroid();

	// General
	int getType() const;
	int getValue() const;
	virtual bool isVulnerable(int) const;
	
	// Draw
	void draw(HDC);

protected:
	int _type;
	int _value;
	std::string _str;
};

#endif