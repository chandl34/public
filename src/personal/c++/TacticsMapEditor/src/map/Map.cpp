#include "Map.h"

Map::Map(int w, int h){
	width = w;
	height = h;
	block = new Block**[w];
	for(int i = 0; i < w; i++){
		block[i] = new Block*[h];
		for(int j = 0; j < h; j++)
			block[i][j] = new Block(i, j);
	}
}

Map::~Map(){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++)
			delete block[i][j];
		delete [] block[i];
	}
	delete [] block;			
}

void Map::draw(){
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++)
			block[i][j]->draw();
	}
}
