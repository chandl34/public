#ifndef GAME_OBJECT_C34_H_
#define GAME_OBJECT_C34_H_

#include "Colorable.h"
#include "Drawable.h"

#define _USE_MATH_DEFINES
#include <list>
#include <math.h>

#include "Rectangle_c34.h"

class GameObject;

typedef std::shared_ptr<GameObject> GameObjectPtr;
typedef std::list<GameObjectPtr> GameObjectList;

typedef std::list<Coord2d<float> > PointList;


const float ROT_MAX = M_PI / 180.0f;
const int COLLIDE_DELAY = 5000;


class GameObject
: public Colorable
, public Drawable
{
public:
	GameObject(const Color_c34&,	
				  int = 0);
	virtual ~GameObject();

	// General
	const Coord2d<float>& getCenter() const;
	const Coord2d<float>& getVector() const;

	bool canCollide() const;
	bool detectHit(const GameObject&) const;
	
	void rotate(float);

	// Draw
	virtual void draw(HDC);
	virtual bool update();

protected:
	PointList _point;

	Rectangle_c34<float> _rect;
	Coord2d<float> _center;

	Coord2d<float> _vect;
	float _moveSpeed;
	
	float _rotSpeed;
	float _rotIncr;
	
	bool _canCollide;
	long _startTime;
};

#endif