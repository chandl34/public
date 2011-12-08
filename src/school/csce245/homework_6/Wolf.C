// Jonathan Chandler
// Wolf.C

#include "Wolf.h"
#include "Rabbit.h"
#include "LList.h"

Wolf::Wolf(int x1, int y1, int t1, Grassland * g1) \
: Animal(x1, y1, t1, g1){setTime(t1 + 4);}

bool Wolf::doit(int i){
	//cout << "WOLF TURN! -- " << i << " -- STARTING POSITION:  " << x << ", " << y << endl;
	int j, k;
	if(i - born >= 800 && random()%101 <= 1){	// 1% chance of dying at age 800	
		//cout << "WOLF DIES OF OLD AGE!" << endl;
		g->killWolf(this, x, y);
		return false;
	}
	else{	
		/*  RANDOM FUNCTIONALITY
		LList * list = new LList();
		int listSize = 0;
		*/		
		// 4 Possible search directions below
		int choice = random()%4;
		 // Overpopulation control - prevents pile-up
        	if(random()%20 == 0){ // % chance of moving from edge area
                	if(x < 100){ // Near left
                        	if(y < 100) // Near top
                               		choice = 3; // Go bottom right first
                        	else if(y > 411) // Near bottom
                                	choice = 1; // Go top right first
                	}
                	else if(x > 411){ // Near right
                        	if(y < 100) // Near top
                                	choice = 2; // Go bottom left first
                        	else if(y > 411) // Near bottom
                                	choice = 0;
                	}
			else if(x < 200 && random()%2 == 1){ // Near left, % chance
	                        if(y < 200) // Near top
        	                        choice = 3; // Go bottom right first
               	        	else if(y > 311) // Near bottom
                	                choice = 1; // Go top right first
        	        }
        	        else if(x > 311 && random()%2 == 1){ // Near right, % chance
                	        if(y < 200) // Near top
                        	        choice = 2; // Go bottom left first
                 	       else if(y > 311) // Near bottom
                        	        choice = 0;
                	}
        	}		
		// Searching top left
		if(choice == 0){
			for(j = x - 32; j <= x + 32; j++){
				if(j >= 0 && j < 512){
					for(k = y - 32; k <= y + 32; k++){
						if(k >= 0 && k < 512){
							if(!g->available(j, k) && dynamic_cast<Animal*>(g->getAnimal(j, k))->isRabbit()){	
								//cout << "WOLF FOUND FOOD!" << endl;
								if(dynamic_cast<Rabbit*>(g->getAnimal(j, k))->isLazy()) 
									g->killLRabbit(g->getAnimal(j, k), j, k);
								else
									g->killARabbit(g->getAnimal(j, k), j, k);						
								lastEat = i;
								g->setAnimal(x, y, NULL);
								g->setAnimal(j, k, this);
								setTime(i + 4);
								x = j;
								y = k; 
								//cout << "FINAL POSITION:  " << x << ", " << y << endl;
								//list->push(j, k);   RANDOM FUNCTIONALITY
								//listSize++;
								return true;
							}
						}
					}
				}
			}
		}
		// Searching top right
                else if(choice == 1){
                        for(j = x + 32; j >= x - 32; j--){
                                if(j >= 0 && j < 512){
                                        for(k = y - 32; k <= y + 32; k++){
                                                if(k >= 0 && k < 512){
                                                        if(!g->available(j, k) && dynamic_cast<Animal*>(g->getAnimal(j, k))->isRabbit()){ 
                                                                //cout << "WOLF FOUND FOOD!" << endl;
                                                                if(dynamic_cast<Rabbit*>(g->getAnimal(j, k))->isLazy())
                                                                        g->killLRabbit(g->getAnimal(j, k), j, k);
                                                                else
                                                                        g->killARabbit(g->getAnimal(j, k), j, k);                         

                                                                lastEat = i;
                                                                g->setAnimal(x, y, NULL);
                                                                g->setAnimal(j, k, this);
                                                                setTime(i + 4);
                                                                x = j;
                                                                y = k;
                                                                //cout << "FINAL POSITION:  " << x << ", " << y << endl;
                                                                return true;
                                                        }
                                                }
                                        }
                                }
                        }
                }
		// Searching bottom left
                else if(choice == 2){
                        for(j = x - 32; j <= x + 32; j++){
                                if(j >= 0 && j < 512){
                                        for(k = y + 32; k >= y - 32; k--){
                                                if(k >= 0 && k < 512){
                                                        if(!g->available(j, k) && dynamic_cast<Animal*>(g->getAnimal(j, k))->isRabbit()){
                                                                //cout << "WOLF FOUND FOOD!" << endl;
                                                                if(dynamic_cast<Rabbit*>(g->getAnimal(j, k))->isLazy())
                                                                        g->killLRabbit(g->getAnimal(j, k), j, k);
                                                                else
                                                                        g->killARabbit(g->getAnimal(j, k), j, k);

                                                                lastEat = i;
                                                                g->setAnimal(x, y, NULL);
                                                                g->setAnimal(j, k, this);
                                                                setTime(i + 4);
                                                                x = j;
                                                                y = k;
                                                                //cout << "FINAL POSITION:  " << x << ", " << y << endl;
                                                                return true;
                                                        }
                                                }
                                        }
                                }
                        }
                }
		 // Searching bottom right
                else if(choice == 3){
                        for(j = x + 32; j >= x - 32; j--){
                                if(j >= 0 && j < 512){
                                        for(k = y + 32; k >= y - 32; k--){
                                                if(k >= 0 && k < 512){
                                                        if(!g->available(j, k) && dynamic_cast<Animal*>(g->getAnimal(j, k))->isRabbit()){
                                                                //cout << "WOLF FOUND FOOD!" << endl;
                                                                if(dynamic_cast<Rabbit*>(g->getAnimal(j, k))->isLazy())
                                                                        g->killLRabbit(g->getAnimal(j, k), j, k);
                                                                else
                                                                        g->killARabbit(g->getAnimal(j, k), j, k);

                                                                lastEat = i;
                                                                g->setAnimal(x, y, NULL);
                                                                g->setAnimal(j, k, this);
                                                                setTime(i + 4);
                                                                x = j;
                                                                y = k;
                                                                //cout << "FINAL POSITION:  " << x << ", " << y << endl;
                                                                return true;
                                                        }
                                                }
                                        }
                                }
                        }
                }
		/*  RANDOM FUNCTIONALITY
		if(listSize > 0){
			LNode * node = list->get(random()%listSize); 
			j = node->x;
			k = node->y;
			//cout << "WOLF FOUND FOOD!" << endl;
			if(dynamic_cast<Rabbit*>(g->getAnimal(j, k))->isLazy()) 
				g->killLRabbit(g->getAnimal(j, k), j, k);
			else
				g->killARabbit(g->getAnimal(j, k), j, k);						
			lastEat = i;
			g->setAnimal(x, y, NULL);
			g->setAnimal(j, k, this);
			setTime(i + 4);
			x = j;
			y = k; 
			//cout << "FINAL POSITION:  " << x << ", " << y << endl;
			delete list;
			return true;		
		}
		else
			delete list;
		*/
	}
	if(i - lastEat >= 20){		//Wolf failed to find food after 20 turns, dies
		//cout << "WOLF DIES OF HUNGER! - TURN:  " << i << endl;
		g->killWolf(this, x, y);
		return false;
	}
	else{
                do{	//Couldn't find food, moving to random location
			j = (x - 16) + random()%33;
			k = (y - 16) + random()%33;
		}while(j < 0 || j >= 512 || k < 0 || k >= 512 || !g->available(j, k));
		g->setAnimal(x, y, NULL);
		g->setAnimal(j, k, this);
		setTime(i + 4);
		x = j;
		y = k;
		return true;
	} 
	//cout << "FINAL POSITION:  " << x << ", " << y << endl;
}
