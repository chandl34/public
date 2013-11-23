// Jonathan Chandler
// Permutation.C

#include "Permutation.h"

Permutation::Permutation(char * inputFile){
	in.open(inputFile);
	if(in.fail()){
		cout << "Input file not found." << endl;
		exit(-1);
	}		
	CreatePermutationsArray();
	ComputeMatrix();
	PrintMatrix();
	in.close();
}

Permutation::~Permutation(){
	for(int i = 0; i < length; i++){
		delete [] permutation[i];
		delete [] bp[i];
	}
	delete [] permutation;
	delete [] bp;	
}

void Permutation::PrintMatrix(){	
        cout << "Permutations:  " << length << endl;
        cout << "Numbers per permutation:  "  << max << endl;
	int i, j, k;
	for(i = 0; i < length; i++){
		for(j = 0; j < length; j++){  // TEXT FORMATTING BELOW
			if(bp[i][j] != 0)
				k = static_cast<int>(log10(bp[i][j]));
			else
				k = 0;
			while(k < static_cast<int>(log10(max + 1)) + 1){
				cout << " ";
				k++;
			}
			cout << bp[i][j];
		}
		cout << endl;
	} 
}

void Permutation::ComputeMatrix(){
	bp = new int*[length];
	int perm1, perm2, num, count;
	for(perm1 = 0; perm1 < length; perm1++)
		bp[perm1] = new int[length];
	for(perm1 = 0; perm1 < length; perm1++){
		for(perm2 = perm1; perm2 < length; perm2++){  // PERM2 ASSIGNMENT PREVENTS DUPLICATE COUNTS	
			for(num = 0, count = 0; num < max + 1; num++){
				if(permutation[perm1][num] != permutation[perm2][num])
					count++;
			}	
			bp[perm1][perm2] = count;
			bp[perm2][perm1] = count;
		}
	}	
}

void Permutation::CreatePermutationsArray(){
	FindLength();
	FindMax();
	permutation = new int*[length];
	int i, j, prev;
	nString *temp = new nString();
	for(i = 0; i < length; i++){
		in >> nextLine;	
		nextLine.Clear();
		in >> nextLine;	
		permutation[i] = new int[max + 1];
		for(j = 0, prev = 0; nextLine[j] != '\0'; j++){ // FIND SEPERATE NUMBERS
			if(nextLine[j] != ' ')
				temp->Put(nextLine[j]);	
			else{
				permutation[i][prev] = atoi(*temp);
				prev = atoi(*temp);
				temp->Clear();
			}	
		}
		permutation[i][prev] = atoi(*temp);
		permutation[i][atoi(*temp)] = max + 1;
		temp->Clear();
	}
	delete temp;
}

void Permutation::FindLength(){
        length = 0;
        while(!in.eof()){
                in >> nextLine;
                if(nextLine[0] == '>')
                        length++;
                nextLine.Clear();
        }
        Reset();
}

void Permutation::FindMax(){
	max = 1;
	in >> nextLine;
	nextLine.Clear();
	in >> nextLine;

	nString *temp = new nString();
	for(int i = 0; nextLine[i] != '\0'; i++){ // FINDING SEPERATE NUMBERS
		if(nextLine[i] != ' ')
			temp->Put(nextLine[i]);
		else{
			if(atoi(*temp) > max)
				max = atoi(*temp);
			temp->Clear();					
		}	
	}
	if(atoi(*temp) > max)
        	max = atoi(*temp);
        delete temp;
	nextLine.Clear();
	Reset();
}

void Permutation::Reset(){
	in.clear();
        in.seekg(0);
}
