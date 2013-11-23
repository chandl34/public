#include <iostream>
#include <algorithm>
#include "Homework6.h"
#include <math.h>
using namespace std;

int table2Comp, table3Comp;

int n; // Number of projects
int H; // Total hours available
int* g; // Grade maximum per project
int* h; // Hours per project
int* th; // Threshhold
int ** gradeToHours; // Grade to Hour ratio
int ** knapSack;
int ** knapSackMF;

void table1(){
	cout << "Table 1" << endl;
	gradeToHours = new int*[n + 1];
	for(int i = 0; i < n + 1; i++){
		gradeToHours[i] = new int[H + 1];
		for(int j = 0; j < H + 1; j++){
			if(j >= h[i])
				gradeToHours[i][j] = g[i];
			else if(j - th[i] <= 0)
				gradeToHours[i][j] = 0;			
			else
				gradeToHours[i][j] = ceil((float)(j - th[i])/(h[i] - th[i])*g[i]);
			cout << gradeToHours[i][j];

			// Space formatting
			if(gradeToHours[i][j] >= 100)
				cout << " ";
			else if(gradeToHours[i][j] >=10)
				cout << "  ";
			else
				cout << "   ";
		}
		cout << endl;
	}
	cout << endl;
}

void table2(){
	int temp;
	table2Comp = 0;
	cout << "Table 2" << endl;
	knapSack = new int*[n + 1];
	for(int i = 0; i < n + 1; i++){
		knapSack[i] = new int[H + 1];
		for(int j = 0; j < H + 1; j++){
			if(i == 0 || j == 0)
				knapSack[i][j] = 0;
			else{
				table2Comp++;
				if(j - th[i] < 0)  // Value is zero, use above value
					knapSack[i][j] = knapSack[i - 1][j];
				else if(j - h[i] < 0){ // Current row not maxed
					if(knapSack[i - 1][j] >= g[i - 1]){ // Above already maxed out
						for(temp = j; knapSack[i - 1][j] == knapSack[i - 1][temp - 1]; temp--);  // Finding when above maxed
					knapSack[i][j] = max(knapSack[i - 1][j] + gradeToHours[i][j - temp], gradeToHours[i][j]);
					}
					else // Above has not maxed out
						knapSack[i][j] = max(knapSack[i - 1][j], gradeToHours[i][j]);
				}
				else{ // Current row maxed
					if(knapSack[i - 1][j] >= g[i - 1]){ // Above already maxed out
						for(temp = j; knapSack[i - 1][j] == knapSack[i - 1][temp - 1]; temp--);  // Finding when above maxed
						knapSack[i][j] = max(knapSack[i - 1][j] + gradeToHours[i][j - temp], gradeToHours[i][j] + knapSack[i - 1][j - h[i]]);
					}
					else // Above has not maxed out
						knapSack[i][j] = max(knapSack[i - 1][j], gradeToHours[i][j] + knapSack[i - 1][j - h[i]]);
				}
			}
			cout << knapSack[i][j];
			
			// Space formatting
			if(knapSack[i][j] >= 100)
				cout << " ";
			else if(knapSack[i][j] >=10)
				cout << "  ";
			else
				cout << "   ";
		}
		cout << endl;
	}
	cout << endl;
}

int mf(int i, int j){
	if(knapSackMF[i][j] < 0){
		table3Comp++;
		int value, temp;
		if(j < th[i]) // Value never got above zero
			value = mf(i - 1, j);
		else if(j < h[i]){ // Current row not maxed
			// Test if above is maxed
			for(temp = j; mf(i - 1, j) == mf(i - 1, temp - 1); temp--);
			if(temp < j)
				value = max(mf(i - 1, j) + gradeToHours[i][j - temp], gradeToHours[i][j]);
			else
				value = max(mf(i - 1, j), gradeToHours[i][j]);
		}
		else{ // Current row maxed
			// Test if above is maxed
			for(temp = j; mf(i - 1, j) == mf(i - 1, temp - 1); temp--);
			if(temp < j)
				value = max(mf(i - 1, j) + gradeToHours[i][j - temp], gradeToHours[i][j] + mf(i - 1, j - h[i]));
			else
				value = max(mf(i - 1, j), gradeToHours[i][j] + mf(i - 1, j - h[i]));
		}
		knapSackMF[i][j] = value;
	}
	return knapSackMF[i][j];
}

void table3(){
	table3Comp = 0;
	cout << "Table 3" << endl;
	knapSackMF = new int*[n + 1];
	for(int i = 0; i < n + 1; i++){
		knapSackMF[i] = new int[H + 1];
		for(int j = 0; j < H + 1; j++){
			if(i == 0 || j == 0)
				knapSackMF[i][j] = 0;
			else
				knapSackMF[i][j] = -1;
		}
	}
	mf(n, H);

	for(int i = 0; i < n + 1; i++){
		for(int j = 0; j < H + 1; j++){
			cout << knapSackMF[i][j];

			// Space formatting
			if(knapSackMF[i][j] >= 100)
				cout << " ";
			else if(knapSackMF[i][j] >= 10 || knapSackMF[i][j] == -1)
				cout << "  ";
			else
				cout << "   ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	cout << "How many projects need to be done?  ";
	cin >> n;
	while(n < 1 || n > 10){
			cout << "Invalid entry." << endl;
			cout << "How many projects need to be done?  ";
			cin >> n;
	}
	g = new int[n + 1];

	cout << "How many hours do you have?  ";
	cin >> H;
	while(H < 1){
			cout << "Invalid entry." << endl;
			cout << "How many hours do you have?  ";
			cin >> H;
	}
	h = new int[n + 1];
	th = new int[n + 1];

	g[0] = 0; h[0] = 0; th[0] = 0;
	for(int i = 1; i < n + 1; i++){
		cout << "How many points for project " << i << "?  ";
		cin >> g[i];
		while(g[i] < 1){
			cout << "Invalid entry." << endl;
			cout << "How many points for project " << i << "?  ";
			cin >> g[i];
		}
		
		cout << "How many hours to get project " << i << " done?  ";
		cin >> h[i];
		while(h[i] < 1){
			cout << "Invalid entry." << endl;
			cout << "How many hours to get project " << i << " done?  ";
			cin >> h[i];
		}

		cout << "How many hours to get partial credit for project " << i << "?  ";
		cin >> th[i];
		while(th[i] > h[i]){
			cout << "Invalid entry." << endl;
			cout << "How many hours to get partial credit for project " << i << "?  ";
			cin >> th[i];
		}
	}

	cout << endl;
	table1();
	table2();
	table3();
	
	cout << "Knapsack (Table 2) computed " << table2Comp << " values." << endl;
	cout << "KnapsackMF (Table 3) computed " << table3Comp << " values.";

	cin >> n;  // Requires input to stop program

	delete [] h;
	delete [] th;
	delete [] g;
	for(int x = 0; x < n + 1; x++){
		delete [] knapSackMF[x];
		delete [] knapSack[x];
		delete [] gradeToHours[x];		
	}
	delete [] knapSackMF;
	delete [] knapSack;
	delete [] gradeToHours;

	return 0;
}
