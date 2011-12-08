#include "Data.h"

void Data::load(LevelMap& s, const char* filename){
	cout << "Loading " << filename << "..." << endl;
	reset(); // ID list
    std::ifstream ifs(filename);
    boost::archive::binary_iarchive ia(ifs);
    ia >> s;
	s.load();
}

void Data::load(CharacterModelContainer& s, const char* filename){
	cout << "Loading " << filename << "..." << endl;
    std::ifstream ifs(filename);
    boost::archive::binary_iarchive ia(ifs);
    ia >> s;
    s.load();
}

void Data::load(MapModelContainer &s, const char * filename){
	cout << "Loading " << filename << "..." << endl;
    std::ifstream ifs(filename);
    boost::archive::binary_iarchive ia(ifs);
    ia >> s;
    s.load();
}
