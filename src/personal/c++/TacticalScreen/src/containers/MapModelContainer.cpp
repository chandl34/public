#include "MapModelContainer.h"

Reader MapModelContainer::reader;
bool MapModelContainer::mirror, MapModelContainer::invert, MapModelContainer::shift;
int MapModelContainer::angle;

int* MapModelContainer::index;
int* MapModelContainer::size;
bool* MapModelContainer::condition;
vector<string>* MapModelContainer::otherFiles;
vector<string>* MapModelContainer::mainFiles;
vector<Model*>** MapModelContainer::unbreakable;
vector<Model*>*** MapModelContainer::breakable;
vector<Model*>***** MapModelContainer::door;

MapModelContainer::MapModelContainer(){
	size_t i, j, k, l;
	index = new int[10];
	size = new int[10];
	for(i = 0; i < 10; i++){
		index[i] = 0;
		size[i] = 0;
	}
	condition = new bool[6];
	for(i = 0; i < 6; i++)
		condition[i] = false;
	otherFiles = new vector<string>[7];
	mainFiles = new vector<string>[10];
	unbreakable = new vector<Model*>*[3];
	for(i = 0; i < 3; i++){
		unbreakable[i] = new vector<Model*>[2];
	}
	breakable = new vector<Model*>**[6];
	for(i = 0; i < 6; i++){
		breakable[i] = new vector<Model*>*[2];
		for(j = 0; j < 2; j++)
			breakable[i][j] = new vector<Model*>[2];
	}
	door = new vector<Model*>****[2];
	for(i = 0; i < 2; i++){
		door[i] = new vector<Model*>***[2];
		for(j = 0; j < 2; j++){
			door[i][j] = new vector<Model*>**[2];
			for(k = 0; k < 2; k++){
				door[i][j][k] = new vector<Model*>*[3];
				for(l = 0; l < 3; l++)
					door[i][j][k][l] = new vector<Model*>[2];
			}
		}
	}
}

MapModelContainer::~MapModelContainer(){
	delete [] index;
	delete [] size;
	delete [] condition;
	delete [] mainFiles;
	delete [] otherFiles;

	size_t i, j, k, l, m, n;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 2; j++){
			for(k = 0; k < unbreakable[i][j].size(); k++)	
				delete unbreakable[i][j].at(k);
		}
		delete [] unbreakable[i];
	}
	delete [] unbreakable;

	for(i = 0; i < 6; i++){
		for(j = 0; j < 2; j++){
			for(k = 0; k < 2; k++){
				for(l = 0; l < breakable[i][j][k].size(); l++)
					delete breakable[i][j][k].at(l);
			}
			delete [] breakable[i][j];
		}
		delete [] breakable[i];
	}
	delete [] breakable;

	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			for(k = 0; k < 2; k++){
				for(l = 0; l < 3; l++){
					for(m = 0; m < 2; m++){
						for(n = 0; n < door[i][j][k][l][m].size(); n++)
							delete door[i][j][k][l][m].at(n);
					}
					delete [] door[i][j][k][l];
				}					
				delete [] door[i][j][k];
			}
			delete [] door[i][j];
		}
		delete [] door[i];
	}
	delete [] door;
}

void MapModelContainer::init(){
	add("obj/Default/ground.obj", "", GROUND);
	add("obj/Default/window.obj", "obj/Default/other/window.obj", WINDOW);
}

void MapModelContainer::toggleMirror(){mirror = !mirror;}
void MapModelContainer::toggleInvert(){invert = !invert;}
void MapModelContainer::toggleShift(){shift = !shift;}
void MapModelContainer::setRotate(int r){angle = r;}
void MapModelContainer::setCondition(int i){
	i-= 4;
	if(i < 0) //Unbreakables are the first four in the enumeration
		return;
	condition[i] = !condition[i];
}

bool MapModelContainer::getMirror(){return mirror;}
bool MapModelContainer::getInvert(){return invert;}
bool MapModelContainer::getShift(){return shift;}
int MapModelContainer::getAngle(){return angle;}
bool MapModelContainer::getCondition(int i){
	i -= 4;
	if(i < 0)  //Unbreakables are the first four in the enumeration
		return UNBROKEN;
	return condition[i];
}
int MapModelContainer::getIndex(int i){return index[i];}

void MapModelContainer::add(const char* filename, const char* o_filename, int type){	
	size[type]++;
	mainFiles[type].push_back(filename);
	Model* temp;
	if(type < DOOR){  // Unbreakables
		for(size_t j = 0; j < 2; j++){
			temp = reader.readOBJ(filename);
			unbreakable[type][j].push_back(temp);
			if(j == 1)
				temp->mirror();
		}
	}
	else{
		otherFiles[type - 3].push_back(o_filename);
		if(type == DOOR){
			for(size_t i = 0; i < 2; i++){
				for(size_t j = 0; j < 2; j++){
					for(size_t k = 0; k < 2; k++){
						for(size_t l = 0; l < 3; l++){
							for(size_t m = 1; m >= 0; m--){
								if(m == 0)
									temp = reader.readOBJ(filename);								
								else
									temp = reader.readOBJ(o_filename);
								door[i][j][k][l][m].push_back(temp);
								if(k == 1)
									temp->invert();	
								if(j == 1)
									temp->shift();	
								if(i == 1)	
									temp->mirror();						
								if(l != 0){
									if(m == 1)
										temp->findCenter();	
									else
										temp->angle(i, j, k, l, 
												door[i][j][k][l][1].at(size[DOOR]-1)->getCenter());
								}
							}
						}
					}
				}
			}
		}
		else{
			int k = type - 4;
			for(size_t i = 0; i < 2; i++){
				for(size_t j = 0; j < 2; j++){
					if(j == 0)
						temp = reader.readOBJ(filename);
					else
						temp = reader.readOBJ(o_filename);
					breakable[k][i][j].push_back(temp);
					if(i == 1)
						temp->mirror();
				}
			}
		}
	}
}

// FIX!
void MapModelContainer::remove(int type){
	if(size[type] == 0 || (type == GROUND && index[type] == 0))
		return;
	if(type < DOOR){
		for(size_t i = 0; i < 2; i++){
			delete unbreakable[type][i].at(index[type]);
			if(size[type] > 1)
				unbreakable[type][i].at(index[type]) = unbreakable[type][i].at(size[type] - 1);
			unbreakable[type][i].pop_back();
		}
		if(size[type] > 1)
			mainFiles[type].at(index[type]) = mainFiles[type].at(size[type] - 1);
		mainFiles[type].pop_back();
	}
	else if(type == DOOR){
		for(size_t i = 0; i < 2; i++){
			for(size_t j = 0; j < 2; j++){
				for(size_t k = 0; k < 2; k++){
					for(size_t l = 0; l < 3; l++){
						for(size_t m = 0; m < 2; m++){
							delete door[i][j][k][l][m].at(index[type]);
							if(size[type] > 1)
								door[i][j][k][l][m].at(index[type]) = door[i][j][k][l][m].at(size[type] - 1);
							door[i][j][k][l][m].pop_back();
						}
					}
				}
			}
		}
		if(size[type] > 1){
			mainFiles[type].at(index[type]) = mainFiles[type].at(size[type] - 1);
			otherFiles[0].at(index[type]) = otherFiles[0].at(size[type] - 1);
		}
		mainFiles[type].pop_back();
		otherFiles[0].pop_back();		
	}
	else{
		int k;
		for(size_t i = 0; i < 2; i++){
			k = type - 4;
			for(size_t j = 0; j < 2; j++){
				delete breakable[k][i][j].at(index[type]);
				if(size[type] > 1)
					breakable[k][i][j].at(index[type]) = breakable[k][i][j].at(size[type] - 1);
				breakable[k][i][j].pop_back();				
			}
		}
		if(size[type] > 1){
			mainFiles[type].at(index[type]) = mainFiles[type].at(size[type] - 1);
			otherFiles[type - 3].at(index[type]) = otherFiles[type - 3].at(size[type] - 1);
		}
		mainFiles[type].pop_back();
		otherFiles[type - 3].pop_back();	
	}
	size[type]--;
}

void MapModelContainer::load(){
	int i, j, k, l, m, n;
	Model* temp;
	for(i = 0; i < DOOR; i++){  						// type
		for(j = 0; j < 2; j++){ 						// mirrored
			for(k = 0; k < size[i]; k++){				// index
				temp = reader.readOBJ(mainFiles[i].at(k).c_str());
				unbreakable[i][j].push_back(temp);
				if(j == 1)
					temp->mirror();
			}				
		}
	}
	for(i = 0; i < 2; i++){								// mirror
		for(j = 0; j < 2; j++){							// shift
			for(k = 0; k < 2; k++){						// invert
				for(l = 0; l < 3; l++){					// angle
					for(m = 1; m >= 0; m--){			// door/hinge
						for(n = 0; n < size[DOOR]; n++){// index
							if(m == 0)
								temp = reader.readOBJ(mainFiles[DOOR].at(n).c_str());								
							else
								temp = reader.readOBJ(otherFiles[0].at(n).c_str());
							door[i][j][k][l][m].push_back(temp);
							if(k == 1)
								temp->invert();	
							if(j == 1)
								temp->shift();	
							if(i == 1)	
								temp->mirror();				
							if(l != 0){
								if(m == 1)
									temp->findCenter();	
								else
									temp->angle(i, j, k, l, 
											door[i][j][k][l][1].at(size[DOOR]-1)->getCenter());
							}
						}
					}
				}
			}
		}
	}
	for(i = 0; i < 6; i++){								// type
		m = i + 4;	n = i + 1;							// adjusted types
		for(j = 0; j < 2; j++){							// mirror
			for(k = 0; k < 2; k++){						// condition
				for(l = 0; l < size[m]; l++){			// index
					if(k == 0)
						temp = reader.readOBJ(mainFiles[m].at(l).c_str());
					else
						temp = reader.readOBJ(otherFiles[n].at(l).c_str());	
					breakable[i][j][k].push_back(temp);
					if(j == 1)
						temp->mirror();
					if(m == WINDOW)
						temp->findCenter();
				}				
			}
		}
	}
}

Model* MapModelContainer::get(int type){
	if(size[type] == 0)
		return NULL;
	if(type == DOOR)
		return door[mirror][shift][invert][angle][0].at(index[type]);
	if(type < DOOR) // unbreakables
		return unbreakable[type][mirror].at(index[type]);
	return breakable[type-4][mirror][condition[type-4]].at(index[type]);
}

Model* MapModelContainer::getBreakable(int t, bool m, bool c, int i){
	return breakable[t-4][m][c].at(i);
}

Model* MapModelContainer::getUnbreakable(int t, bool m, int i){
	return unbreakable[t][m].at(i);
}

Model* MapModelContainer::getDoor(bool m, bool s, bool i, int a, bool h, int index){
	return door[m][s][i][a][h].at(index);
}

void MapModelContainer::increment(int type){
	if(size[type] == 0)
		return;
	if(index[type] >= size[type] - 1)
		index[type] = 0;
	else
		index[type]++;
}

void MapModelContainer::decrement(int type){
	if(size[type] == 0)
		return;
	if(index[type] <= 0)
		index[type] = size[type] - 1;	
	else
		index[type]--;
}
