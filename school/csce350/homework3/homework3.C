#include "homework3.h"

ifstream in;
ofstream out;

// Creates an input file
void createInput(char * filename, int size){
	out.open(filename);
	for(int i = 0; i < size; i++)
		out << random() << endl;
	out.close();
}

// SelectionSort on the six input files
void selectionSort(int * data, int size, string filename){	
	// Create copy of data[]
	int * a = new int[size];	
	memcpy(a, data, size * 4);

	int swaps = 0, comparisons = 0;
	int min;
	int temp;
	
	for(int i = 0; i < size - 1; i++){
		min = i;
		for(int j = i + 1; j < size; j++){
			comparisons++;
			if(a[j] < a[min])
				min = j;
		}
		swaps++;
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;		
	}	

	//Creating output file
	filename = "selectionSort" + filename;
	out.open(filename.c_str());			

	for(int i = 0; i < size; i++)
		out << a[i] << endl;

	out << "\nSelectionSort comparisons: " << comparisons;
	out << "\nSelectionSort swaps: " << swaps;

	out.close();

	delete [] a;
}

// BubbleSort on the six input files
void bubbleSort(int * data, int size, string filename){
	// Create copy of data[]
        int * a = new int[size];
        memcpy(a, data, size * 4);

        int swaps = 0, comparisons = 0;
        int min;
        int temp;

	for(int i = 0; i < size - 1; i++){
		for(int j = 0; j < size - 1 - i; j++){
			comparisons++;
			if(a[j+1] < a[j]){
				swaps++;
                		temp = a[j];
               			a[j] = a[j+1];
                		a[j+1] = temp;						
			}
		}
	}

        //Creating output file
        filename = "bubbleSort" + filename;
        out.open(filename.c_str());

        for(int i = 0; i < size; i++)
                out << a[i] << endl;

        out << "\nBubbleSort comparisons: " << comparisons;
        out << "\nBubbleSort swaps: " << swaps;

        out.close();

        delete [] a;

}

int msComparisons = 0;
// MergeSort on the six input files
void mergeSort(int * data, int size, string filename){
        // Create copy of data[]
        int * a = new int[size];
        memcpy(a, data, size * 4);

	mergeSort(a, size);

        //Creating output file
        filename = "mergeSort" + filename;
        out.open(filename.c_str());

        for(int i = 0; i < size; i++)
                out << a[i] << endl;

        out << "\nMergeSort comparisons: " << msComparisons;

        out.close();

        delete [] a;
}

// MergeSort base method 
void mergeSort(int * a, int size){
	if(size > 1){
		// Copy first half
		int * b = new int[size/2];
		for(int i = 0; i < size/2; i++)
			b[i] = a[i];

		// Copy second half
		int cSize = size - size/2;
		int * c = new int[cSize];
		for(int i = 0; i < cSize; i++)
			c[i] = a[i + size/2];

		mergeSort(b, size/2);
		mergeSort(c, cSize);
		merge(b, c, a, size/2, cSize);

		delete [] b;
		delete [] c;
	}
}

// Mergesort sub method
void merge(int * b, int * c, int * a, int bSize, int cSize){
	int i = 0, j = 0, k = 0;
	while(i < bSize && j < cSize){
		msComparisons++;
		if(b[i] <= c[j]){
			a[k] = b[i];
			i++;
		}
		else{
			a[k] = c[j];
			j++;
		}
		k++;
	}
	msComparisons++;
	if(i == bSize){
		while(k < bSize + cSize){
			a[k] = c[j];
			j++;
			k++;
		}
	}
	else{
		while(k < bSize + cSize){
			a[k] = b[i];
			i++;
			k++;
		}
	}
}

int qsComparisons = 0, qsSwaps = 0;
// QuickSort on the six input files
void quickSort(int * data, int size, string filename){
        // Create copy of data[]
        int * a = new int[size];
        memcpy(a, data, size * 4);
	
        quickSort(a, 0, size - 1);

        //Creating output file
        filename = "quickSort" + filename;
        out.open(filename.c_str());

        for(int i = 0; i < size; i++)
                out << a[i] << endl;

        out << "\nQuickSort comparisons: " << qsComparisons;
	out << "\nQuickSort swaps: " << qsSwaps;

        out.close();

        delete [] a;
	
}

// Quicksort base method
void quickSort(int * a, int l, int r){
	if(l < r){
		int s = partition(a, l, r);
		quickSort(a, l, s - 1);
		quickSort(a, s + 1, r);
	}
}


// Quicksort sub method
int partition(int * a, int l, int r){
	int p = a[l];
	int i = l;
	int j = r + 1;
	int temp;	
	
	do{		
		do{
			i++;
			qsComparisons++;
		}while(a[i] < p);
		
		do{
			j--;
			qsComparisons++;
		}while(a[j] > p);
		
		qsSwaps++;
                temp = a[j];
                a[j] = a[i];
                a[i] = temp;  
		
		qsComparisons++;
	}while(i < j);
	
	qsSwaps++;
        temp = a[j];
        a[j] = a[i];
        a[i] = temp;
	
	qsSwaps++;
        temp = a[j];
        a[j] = a[l];
        a[l] = temp;
	
	return j;
}

void sort(string filename){
	in.open(filename.c_str());

	// Determine number of integers in file
	int size = 0;
	while(!in.eof()){
		in.ignore(100, '\n');
		size++;
	}
	size--;
	
	// Return to beginning of file
        in.clear();
        in.seekg(0);

	// Create array of integers from input file
	int * data = new int[size];
	for(int i = 0; i < size; i++)
		in >> data[i];

	in.close();

	// Creating output filename
	filename = "Out" + filename.substr(2);

	// Sorting using each algorithm
	selectionSort(data, size, filename);
	bubbleSort(data, size, filename);
	mergeSort(data, size, filename);
	quickSort(data, size, filename);

	delete [] data;
}

int main(){
        srandom(time(0));  //Setting up randomizer

	// Creating the six input files
        createInput("input256.txt", 256);
        createInput("input512.txt", 512);
        createInput("input1024.txt", 1024);
        createInput("input2048.txt", 2048);
        createInput("input4096.txt", 4096);
        createInput("input8192.txt", 8192);

	sort("input256.txt");
	sort("input512.txt");
	sort("input1024.txt");
	sort("input2048.txt");
	sort("input4096.txt");
	sort("input8192.txt");

}


