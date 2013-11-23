#include "Data.h"

void Data::save(const MapModelContainer &s, const char * filename){
	cout << "Saving as " << filename << "..." << endl;
    std::ofstream ofs(filename);
    boost::archive::binary_oarchive oa(ofs);
    oa << s;
}

void Data::load(MapModelContainer &s, const char * filename){
	cout << "Loading " << filename << "..." << endl;
    std::ifstream ifs(filename);
    boost::archive::binary_iarchive ia(ifs);
    ia >> s;
    MapModelContainer::load();
}

void Data::save(const LevelMap &s, const char * filename){
	cout << "Saving as " << filename << "..." << endl;
    std::ofstream ofs(filename);
    boost::archive::binary_oarchive oa(ofs);
    oa << s;
}

void Data::load(LevelMap &s, const char * filename){
	cout << "Loading " << filename << "..." << endl;
    std::ifstream ifs(filename);
    boost::archive::binary_iarchive ia(ifs);
    ia >> s;
    s.load();
}
