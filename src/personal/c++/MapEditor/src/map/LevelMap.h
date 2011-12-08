#ifndef LEVELMAP_H_
#define LEVELMAP_H_

#include <boost/serialization/utility.hpp>
#include "../io/Reader.h"
#include "../gl/SelectBox.h"

class Block;

class LevelMap{
public:
	LevelMap();
	virtual ~LevelMap();
	void init();
	void load();
	
	void refreshMap();
	static void updateMap(){update = true;}
	bool needsUpdate(){return update;}
	
	static Block* getBlock(int i, int k){return block[i][k];}
	static Block* getSelectedBlock(){return block[SelectBox::get(X)][SelectBox::get(Z)];} 
	int getID(){return id;}	

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		for(int i = 0; i < LEVEL_LENGTH; i++){
			for(int k = 0; k < LEVEL_LENGTH; k++)
				ar & block[i][k];
		}
	}
	
	const static int LEVEL_LENGTH, LEVEL_OFFSET;
	
private:
	friend class boost::serialization::access;

	void drawMap();
	
	static Block*** block;
	static bool update;
	int id;
	
};

#include "Block.h"

#endif /*LEVELMAP_H_*/
