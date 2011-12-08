// Jonathan Chandler
// Grassland.C

#include "Grassland.h"
#include "Wolf.h"
#include "Rabbit.h"

Grassland::Grassland(int w, int ar, int lr){
	// Setting up random number generator
	srandom(time(0));
	
	// Initializing variables
	wolf = w; 
	aRabbit = ar; 
	lRabbit = lr;
	setTime(350 + random()%101);		//Setting next time 350-450
	//cout << "TIME : " << getTime() << endl;
	
	// Setting up grass and animal locations
	int i, j;
	grass = new int*[512];
	animal = new Item**[512];
	for(i = 0; i < 512; i++){
		grass[i] = new int[512];
		animal[i] = new Item*[512];
		for(j = 0; j < 512; j++){
			grass[i][j] = -10;
			animal[i][j] = NULL;
		}
	}

	// Inserting animals into PQ and into locations
	int tempX, tempY;
	queue = new PQ();
	for(i = 0; i < wolf; i++){
		do{
			tempX = random()%512;
			tempY = random()%512;
		}while(!available(tempX, tempY));	
		animal[tempX][tempY] = new Wolf(tempX, tempY, 0, this);
		queue->insert(animal[tempX][tempY]);
	}
	for(i = 0; i < aRabbit; i++){
                do{
                        tempX = random()%512;
                        tempY = random()%512;
                }while(!available(tempX, tempY));
                animal[tempX][tempY] = new Rabbit(tempX, tempY, 0, this, false);
		queue->insert(animal[tempX][tempY]);
        }
	for(i = 0; i < lRabbit; i++){
                do{
                        tempX = random()%512;
                        tempY = random()%512;
                }while(!available(tempX, tempY));
        	animal[tempX][tempY] = new Rabbit(tempX, tempY, 0, this, true);
        	queue->insert(animal[tempX][tempY]);
	}	
	queue->insert(this);
	
	// Complete all possible turns
	int turn = 0, count = 0, p, q, lastTurn = -1;
	while(wolf != 0){
		turn = queue->get()->getTime();
		if(turn > 10000)
			break;
		/* TRACKING STARVATION PATTERNS
		if(turn%25 == 0 && turn != lastTurn){lastTurn = turn;
			for(p = 100; p < 200; p++){				
				for(q = 0; q < 512; q++)
					if(!hasGrass(turn, p, q)) count++;
			}
			cout << "In range:  " << count << "  -  Turn:  " << turn << endl;
			count = 0;
		}
		*/
		//if(aRabbit == 0) cout << "ACTIVE RABBITS ALL DEAD! -- " << turn << endl;
		//if(lRabbit == 0) cout << "LAZY RABBITS ALL DEAD! -- " << turn << endl;
		if(queue->get()->doit(turn)){
			queue->insert(queue->removeHead());}
	}
	if(turn <= 10000)
		cout << "Failed to finish 10000 turns.  Last turn:  " << turn << endl;
	else
		cout << "Success!" << endl;
	cout << "Starting values:  w = " << w << ", ar = " << ar << ", lr = " << lr  << endl;
	cout << "Remaining wolves:  " << wolf << endl;
	cout << "Remaining active rabbits:  " << aRabbit << endl;
	cout << "Remaining lazy rabbits:  "  << lRabbit << endl;
}

Grassland::~Grassland(){
	int i, j;
	for(i = 0; i < 512; i++){
		delete grass[i];
		for(j = 0; j < 512; j++)
			delete animal[i][j];
		delete [] animal[i];
	}
	delete [] grass;
	delete [] animal;
	delete queue;
}

bool Grassland::doit(int i){
	//cout << "REGROWTH TIME!" << endl;
	setTime(i + 350 + random()%101);	//Setting next time 350-450
	int tempX, tempY, j;
        for(j = 0; j < wolf; j++){
                do{
                        tempX = random()%512;
                        tempY = random()%512;
                }while(!available(tempX, tempY));
                animal[tempX][tempY] = new Wolf(tempX, tempY, i, this);
		queue->insert(animal[tempX][tempY]);
        }
	wolf *= 2;
	int ars, lrs;
	lrs = (aRabbit + lRabbit)/2;
	if((aRabbit + lRabbit)%2 == 1)
		ars = lrs + 1;
	else
		ars = lrs;
	aRabbit += ars;
	lRabbit += lrs;	

	for(j = 0; j < ars; j++){
                do{
                        tempX = random()%512;
                        tempY = random()%512;
                }while(!available(tempX, tempY));
                animal[tempX][tempY] = new Rabbit(tempX, tempY, i, this, false);
		queue->insert(animal[tempX][tempY]);
        }
        for(j = 0; j < lrs; j++){
                do{
                        tempX = random()%512;
                        tempY = random()%512;
                }while(!available(tempX, tempY));
                animal[tempX][tempY] = new Rabbit(tempX, tempY, i, this, true);
		queue->insert(animal[tempX][tempY]);
        }
	return true;	
}

void Grassland::killWolf(Item * dead, int x, int y){
	//cout << "WOLF DYING!" << endl;
	wolf--;
	animal[x][y] = NULL;
	queue->remove(dead);	
	delete dead;
}

void Grassland::killARabbit(Item * dead, int x, int y){
	//cout << "ACTIVE RABBIT DYING!" << endl;
        aRabbit--;
	animal[x][y] = NULL;
        queue->remove(dead);
	delete dead;
}

void Grassland::killLRabbit(Item * dead, int x, int y){
	//cout << "LAZY RABBIT DYING!" << endl;
        lRabbit--;
	animal[x][y] = NULL;
        queue->remove(dead);
	delete dead;
}
