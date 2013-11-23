#ifndef MATHTEROID_C34_H_
#define MATHTEROID_C34_H_

#include "Asteroid.h"


class Mathteroid
: public Asteroid
{
public:
	Mathteroid(int);
	~Mathteroid();

	// General
	bool isVulnerable(int) const;
};

#endif
