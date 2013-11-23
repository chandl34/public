#include "Game.h"

#include <time.h>
#include <iostream>

#include "Digitroid.h"
#include "Mathteroid.h"
#include "Operoid.h"

#include "Math_c34.h"


Game::Game()
{
	_locked = false;

	newGame();
}



// General
bool Game::isLocked() const
{
	return _locked;
}

int Game::getLevel() const
{
	return _level;
}
	
int Game::getLives() const
{
	return _lives;
}

int Game::getScore() const
{
	return _score;
}
	
int Game::getTotal() const
{
	return _total;
}

void Game::input(int in)
{
	if(in == SHOOT){
		// Unlock the game
		if(_locked)
			_locked = false;

		// Shoot when off cooldown
		else{
			size_t _currTime = GetTickCount();
			if(_currTime - _shotTime >= SHOT_DELAY){
				_shotTime = _currTime;

				ProjectilePtr proj = ProjectilePtr(new Projectile(_ship->getCenter(), _ship->getVector()));
				_projectile.push_back(proj);
			}
		}
	}
	else
		_ship->input(in);
}


// Draw
void Game::drawObjects(HDC hdcBackBuffer)
{
	_ship->draw(hdcBackBuffer);
	
	for(AsteroidList::iterator iter = _asteroid.begin(); iter != _asteroid.end(); ++iter)
		(*iter)->draw(hdcBackBuffer);
	
	for(ProjectileList::iterator iter = _projectile.begin(); iter != _projectile.end(); ++iter)
		(*iter)->draw(hdcBackBuffer);
}

void Game::update()
{
	// Check for Level completion
	if(_astCnt[MATHTEROID] == 0)
		newLevel();

	// Update timers
	size_t _currTime = GetTickCount();
	if(_currTime - _updateTime >= UPDATE_DELAY){
		_updateTime = _currTime;
		
		// Randomly add asteroids if below max
		if(_astCnt[DIGITROID] < _astMax[DIGITROID] && roll(10)){
			_asteroid.push_back(AsteroidPtr(new Digitroid(_level)));
			++_astCnt[DIGITROID];
		}
		
		if(_astCnt[OPEROID] < _astMax[OPEROID] && roll(10)){
			_asteroid.push_back(AsteroidPtr(new Operoid(_level)));
			++_astCnt[OPEROID];
		}
	}

	// Update object locations
	_ship->update();
	
	for(AsteroidList::iterator iter = _asteroid.begin(); iter != _asteroid.end(); ++iter)
		(*iter)->update();

	for(ProjectileList::iterator iter = _projectile.begin(); iter != _projectile.end(); ){
		if((*iter)->update())
			 ++iter;
		else
			iter = _projectile.erase(iter);
	}

	// Test for collisions with ship
	if(_ship->canCollide()){
		for(AsteroidList::iterator iter = _asteroid.begin(); iter != _asteroid.end(); ++iter){
			if((*iter)->canCollide() && _ship->detectHit(**iter)){
				_ship = ShipPtr(new Ship());
				--_lives;

				// Check for Game Over
				if(_lives < 0){
					OutputDebugString("Game Over!\n");
					newGame();
				}

				break;
			}
		}
	}
	
	// Test for collisions with projectiles
	for(ProjectileList::iterator piter = _projectile.begin(); piter != _projectile.end(); ){
		bool hit = false;
		for(AsteroidList::iterator aiter = _asteroid.begin(); aiter != _asteroid.end(); ++aiter){
			if((*piter)->detectHit(**aiter)){
				hit = true;
				if((*aiter)->isVulnerable(_total)){
					int type = (*aiter)->getType();
					int value = (*aiter)->getValue();

					// Update total
					if(type == DIGITROID){
						if(!_operator)
							_total = value;
						else{			
							if(_operator == '+')
								_total += value;
							else if(_operator == '-')
								_total -= value;
							else if(_operator == 'x')
								_total *= value;
							else
								_total /= value;

							_operator = 0;
						}
					}
					else if(type == OPEROID){
						_operator = value;
					}
					else if(type == MATHTEROID){
						_score += _total;
						_total = 0;
					}

					--_astCnt[type];
					_asteroid.erase(aiter);
				}
				break;
			}
		}

		if(hit)
			piter = _projectile.erase(piter);
		else
			++piter;
	}

}


// Gameplay
void Game::newGame()
{
	OutputDebugString("New Game\n");

	_level = 0;
	_lives = STARTING_LIVES;
	_score = 0;

	_astCnt[MATHTEROID] = 0;
}

void Game::newLevel()
{
	OutputDebugString("New Level\n");

	++_level;
	_locked = true;

	_total = 0;
	_operator = 0;

	_updateTime = -1;
	_shotTime = -1;

	// Create GameObjects
	_asteroid.clear();
	_projectile.clear();

	//---- Ship
	_ship = ShipPtr(new Ship());
	
	//---- Digitroids
	_astCnt[DIGITROID] = _level * 5;
	_astMax[DIGITROID] = _astCnt[DIGITROID];

	for(int i = 0; i < _astCnt[DIGITROID]; ++i){
		_asteroid.push_back(AsteroidPtr(new Digitroid(_level)));
	}
	
	//---- Operoids
	_astCnt[OPEROID] = _level * 4;
	_astMax[OPEROID] = _astCnt[OPEROID];

	for(int i = 0; i < _astCnt[OPEROID]; ++i)
		_asteroid.push_back(AsteroidPtr(new Operoid(_level)));

	//---- Mathteroids
	_astCnt[MATHTEROID] = _level * 5;
	_astMax[MATHTEROID] = _astCnt[MATHTEROID];
	
	for(int i = 0; i < _astCnt[MATHTEROID]; ++i)
		_asteroid.push_back(AsteroidPtr(new Mathteroid(_level)));
}
