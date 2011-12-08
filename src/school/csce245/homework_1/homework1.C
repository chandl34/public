// Jonathan Chandler
// CSCE 245
// Homework 1


#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int main(){
	srandom(time(0));
	int people[2000];
	int i, j, temp;
	
	// Initializing list of people
	for(i = 0; i < 2000; i++)
		people[i] = i+1;
	for(i = 0; i < 2000; i++){
		// Printing 25 numbers per line
		if(i%25 == 0)
			cout << "\n";

		// Finding a random number 0-1999
		temp = random()%2000;

		// If number has already been removed (-1), find one that hasn't been
		// Removes some of the randomness from the program but speeds up the process of finding numbers
		if(people[temp] == -1){
			
			if(random()%2 == 0){
				for(j = temp; j < 2000 && people[j] == -1; j++);
				if(j == 2000)
					for(j = temp - 1; people[j] == -1; j--);
			}

			else{
				for(j = temp - 1; j > -1 && people[j] == -1; j--);
				if(j == -1)		
					for( j = temp; people[j] == -1; j++);
			}
			
			temp = j;
		}

		// Print out the number found and set it as removed (-1)
		cout << people[temp] << " ";
		people[temp] = -1;
	}
	cout << "\n";
	return 0;
}
