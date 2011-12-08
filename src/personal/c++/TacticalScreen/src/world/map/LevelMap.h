#ifndef LEVELMAP_H_
#define LEVELMAP_H_

class Block;
class Selection;
class Character;

#include "../../physics/projectiles/Bullet.h"
#include "../../physics/projectiles/Grenade.h"
#include "Block.h"

class LevelMap{
public:
	LevelMap();
	virtual ~LevelMap();
	void load();
	
	void refreshMap();
	void updateMap();
	void updateModels(int);
	bool needsUpdate();
	int getID(int);	
	
	Block* getBlock(int, int);
	Block* getBlock(Coordinate*);
	Selection* getSelection(size_t);
	Character* getCharacter(size_t, size_t);
	size_t getCharacterSize(size_t);

	void addCharacter(Character*, Coordinate*);
	void drawCharacters();
	void clearVision(int, bool);
	
	void addProjectile(Projectile*);
	void drawProjectiles();
		
private:
	friend class boost::serialization::access;		
	
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		for(int i = 0; i < LEVEL_LENGTH; i++){
			for(int k = 0; k < LEVEL_LENGTH; k++)
				ar & block[i][k];
		}
	}

	void refresh(int);
	void draw(int);
	
	map<int, Selection*> select;
	Block*** block;
	vector<Character*>* character;
	list<Projectile*> projectile;
	bool _update;	// Update for any part of the map
	bool* update;	// Update for particular part of the map
	bool doorUpdate; // Counter that ensures doors complete their animation
	int* id;
	
};

#endif /*LEVELMAP_H_*/
