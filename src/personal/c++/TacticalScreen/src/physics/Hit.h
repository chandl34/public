#ifndef HIT_H_
#define HIT_H_

#include "WindowHit.h"

class Hit{
public:
	Hit(bool);
	virtual ~Hit();

	bool isProjectile();
	float getDuration();
	void setDuration(float);
	int getType();
	void setType(int);
	int getSide();
	void setSide(int);
	Coordinate* getCoord();
	void setCoord(Coordinate*);
	void addWindow(int, Coordinate*, BreakableModel*);
	size_t windowsLeft();
	int getWindowTime();
	Vertex* getWindowCenter();
	void breakWindow();
	
private:
	float duration;
	bool projectile;
	int type;
	int side;
	Coordinate* coord;
	list<WindowHit*> window;
};

#endif /*HIT_H_*/
