// Jonathan Chandler
// Rabbit.C

#include "Rabbit.h"
#include "LList.h"

Rabbit::Rabbit(int x1, int y1, int t1, Grassland * g1, bool l) \
: Animal(x1, y1, t1, g1){
	lazy = l;
	if(isLazy())
		setTime(t1 + 1);
	else
		setTime(t1 + 2);
}

bool Rabbit::doit(int i){
	//cout << "RABBIT TURN! -- " << i << " -- STARTING POSITION:  " << x << ", " << y << endl;
        int j, k;
	if(isLazy()){			// Lazy rabbit dies at 450
		if(i - born >= 450){
			//cout << "LAZY RABBIT DIES OF OLD AGE! - TURN:  " << i << endl;
			g->killLRabbit(this, x, y);
			return false;
		}
	}
	else{
		if(i - born >= 750 && random()%21 <= 1){  // Active rabbit 5% chance of dying at 750
			//cout << "ACTIVE RABBIT DIES OF OLD AGE! - TURN:  " << i << endl;
			g->killARabbit(this, x, y);
			return false;
		}
	}
	if(g->hasGrass(i, x, y)){ //Checking for grass at its feet
                g->killGrass(i, x, y);
                lastEat = i;
                if(isLazy())
                        setTime(i + 1);
                else
                        setTime(i + 2);
                return true;
        }
        int mobility;
	if(isLazy())
        	mobility = 5;
       	else
               	mobility = 10;
	/* RANDOM FUNCTIONALITY
	LList * list = new LList();
	int listSize = 0;
	*/
	// 4 Search branches below
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
	// Search top left first
	if(choice == 0){
       		for(j = x - mobility; j <= x + mobility; j++){
        		if(j >= 0 && j < 512){
                		for(k = y - mobility; k <= y + mobility; k++){
                        		if(k >= 0 && k < 512){
                               		 	if(g->hasGrass(i, j, k) && g->available(j, k)){
							//cout << "RABBIT FOUND FOOD!" << endl;
							g->killGrass(i, j, k);  
                                        	        lastEat = i;          
  						        g->setAnimal(x, y, NULL);
                                        	        g->setAnimal(j, k, this);
							if(isLazy())
                                        	        	setTime(i + 1);
							else
								setTime(i + 2);
                                        	        x = j;
                                        	        y = k; 
							 //cout << "FINAL POSITION:  " << x << ", " << y << endl;
							 //list->push(j, k);  RANDOM FUNCTIONALITY
							 //listSize++;
                                        	        return true;
                                	        }
                        	        }
                	        }
        	        }
	        }
	}
	// Search top right first
        else if(choice == 1){
                for(j = x + mobility; j >= x - mobility; j--){
                        if(j >= 0 && j < 512){
                                for(k = y - mobility; k <= y + mobility; k++){
                                        if(k >= 0 && k < 512){
                                                if(g->hasGrass(i, j, k) && g->available(j, k)){
                                                        //cout << "RABBIT FOUND FOOD!" << endl;
                                                        g->killGrass(i, j, k);
                                                        lastEat = i;
                                                        g->setAnimal(x, y, NULL);
                                                        g->setAnimal(j, k, this);
                                                        if(isLazy())
                                                                setTime(i + 1);
                                                        else
                                                                setTime(i + 2);
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
	// Search bottom left first
        else if(choice == 2){
                for(j = x - mobility; j <= x + mobility; j++){
                        if(j >= 0 && j < 512){
                                for(k = y + mobility; k >= y - mobility; k--){
                                        if(k >= 0 && k < 512){
                                                if(g->hasGrass(i, j, k) && g->available(j, k)){
                                                        //cout << "RABBIT FOUND FOOD!" << endl;
                                                        g->killGrass(i, j, k);
                                                        lastEat = i;
                                                        g->setAnimal(x, y, NULL);
                                                        g->setAnimal(j, k, this);
                                                        if(isLazy())
                                                                setTime(i + 1);
                                                        else
                                                                setTime(i + 2);
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
	// Search bottom right first
        else if(choice == 3){
                for(j = x + mobility; j >= x - mobility; j--){
                        if(j >= 0 && j < 512){
                                for(k = y + mobility; k >= y - mobility; k--){
                                        if(k >= 0 && k < 512){
                                                if(g->hasGrass(i, j, k) && g->available(j, k)){
                                                        //cout << "RABBIT FOUND FOOD!" << endl;
                                                        g->killGrass(i, j, k);
                                                        lastEat = i;
                                                        g->setAnimal(x, y, NULL);
                                                        g->setAnimal(j, k, this);
                                                        if(isLazy())
                                                                setTime(i + 1);
                                                        else
                                                                setTime(i + 2);
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
		//cout << "RABBIT FOUND FOOD!" << endl;
		g->killGrass(i, j, k);
                lastEat = i;
  		g->setAnimal(x, y, NULL);
                g->setAnimal(j, k, this);
		if(isLazy())
                	setTime(i + 1);
		else
			setTime(i + 2);
                x = j;
                y = k; 
		//cout << "FINAL POSITION:  " << x << ", " << y << endl;
                delete list;
		return true;
	}
	else
		delete list;
	*/
	if(isLazy() && (i - lastEat) >= 5){	//Lazy rabbit hasn't eaten in 5 days, dies
		//cout << "LAZY RABBIT DIES OF HUNGER! - TURN:  " << i << endl;
		g->killLRabbit(this, x, y);
		return false;
	}
	else if(!isLazy() && (i - lastEat) >= (18 + random()%5)){	//Active rabbit hasn't eaten in 18-22 days, dies
		//cout << "ACTIVE RABBIT DIES OF HUNGER! - TURN:  " << i <<  endl;
		g->killARabbit(this, x, y);
		return false;
	}
	if(isLazy())
                setTime(i + 1);
        else
		setTime(i + 2);
	return true; 
	//cout << "FINAL POSITION:  " << x << ", " << y << endl;
}
