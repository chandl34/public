#ifndef GAME_C34_H_
#define GAME_C34_H_

#include <list>
#include <memory>

#include "GameObject.h"
#include "Asteroid.h"
#include "Projectile.h"
#include "Ship.h"


const int STARTING_LIVES = 4;

const size_t UPDATE_DELAY = 500;
const size_t SHOT_DELAY = 500;


class Game{
public:
	Game();

	// General
	bool isLocked() const;

	int getLevel() const;
	int getLives() const;
	int getScore() const;
	int getTotal() const;
	
	void input(int);

	// Draw
	void drawObjects(HDC);
	void update();

	// Gameplay
	void newGame();
	void newLevel();
	
private:
	// Gameplay
	bool _locked;

	// Stats
	int _level;
	int _lives;
	int _score;

	int _total;
	int _operator;

	// GameObjects
	ShipPtr _ship;
	AsteroidList _asteroid;
	ProjectileList _projectile;

	int _astCnt[ASTEROID_TYPES];
	int _astMax[ASTEROID_TYPES];

	// Timer
	size_t _updateTime;
	size_t _shotTime;
};

#endif
