#ifndef MAPMODELCONTAINER_H_
#define MAPMODELCONTAINER_H_

#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include "../models/Model.h"
#include "../io/Reader.h"

class MapModelContainer{
public:
	MapModelContainer();
	virtual ~MapModelContainer();

	static void add(const char*, const char*, int);
	static void remove(int);	

	// need to add other open methods
	static void init();
	static Model* get(int);
	static Model* getBreakable(int, bool, bool, int);
	static Model* getUnbreakable(int, bool, int);
	static Model* getDoor(bool, bool, bool, int, bool, int);
	static void load();

	static void increment(int);
	static void decrement(int);

	static void toggleMirror();
	static void toggleInvert();
	static void toggleShift();
	static void setRotate(int);
	static void setCondition(int);

	static bool getMirror();
	static bool getInvert();
	static bool getShift();
	static int getAngle();
	static bool getCondition(int);
	static int getIndex(int);

private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		int i;
		for(i = 0; i < 10; i++){
			ar & mainFiles[i];	
			ar & size[i];
		}
		for(i = 0; i < 7; i++)
			ar & otherFiles[i];
	}

	static bool mirror, invert, shift;
	static int angle;
	static bool* condition;

	static Reader reader;
	static int* index;
	static int* size;
	static vector<string>* mainFiles;
	static vector<string>* otherFiles;
	static vector<Model*>** unbreakable;
	static vector<Model*>*** breakable;
	static vector<Model*>***** door;

};

#endif /*MAPMODELCONTAINER_H_*/
