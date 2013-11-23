#ifndef DATA_H_
#define DATA_H_

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "../containers/MapModelContainer.h"
#include "../map/LevelMap.h"

class Data{
public:
	Data(){}
	virtual ~Data(){}
	
	static void save(const MapModelContainer&, const char*);
	static void load(MapModelContainer&, const char*);
	static void save(const LevelMap&, const char*);
	static void load(LevelMap&, const char*);

};

#endif /*DATA_H_*/
