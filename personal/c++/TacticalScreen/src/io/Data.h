#ifndef DATA_H_
#define DATA_H_

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "../containers/CharacterModelContainer.h"
#include "../containers/MapModelContainer.h"
#include "../world/map/LevelMap.h"

class Data{
public:
	Data(){}
	virtual ~Data(){}
	
	static void load(LevelMap&, const char*);
	static void load(CharacterModelContainer&, const char*);
	static void load(MapModelContainer&, const char*);

};


#endif /*DATA_H_*/
