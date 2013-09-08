#include "stdafx.h"
#include "SudokuPuzzle.h"


// Constructors / Destructors
SudokuPuzzle::SudokuPuzzle()
{
	_group = gcnew array<SudokuGroup^, 2>(3, 9);
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 9; ++j){
			_group[i, j] = gcnew SudokuGroup();
		}
	}

	_block = gcnew array<SudokuBlock^, 2>(9, 9);
	for(int row = 0; row < 9; ++row)
	{
		for(int col = 0; col < 9; ++col)
		{
			_block[col, row] = gcnew SudokuBlock();
			
			_group[COL, col]->addBlock(_block[col, row]);
			_group[ROW, row]->addBlock(_block[col, row]);
			_group[BOX, row/3*3 + col/3]->addBlock(_block[col, row]);
		}
	}
	

}

SudokuPuzzle::~SudokuPuzzle()
{

}

	
// Class Methods
SudokuBlock^ SudokuPuzzle::getBlock(int col, int row)
{
	return _block[col, row];
}

void SudokuPuzzle::print()
{
	for(int row = 0; row < 9; ++row)
	{
		for(int col = 0; col < 9; ++col)
		{
			printf("%i ", _block[col, row]->getValue());
			
			if(col % 3 == 2)
				printf(" ");
		}

		if(row % 3 == 2)
			printf("\n");

		printf("\n");
	}
	printf("\n");
	
	///*
	for(int row = 0; row < 9; ++row)
	{
		for(int col = 0; col < 9; ++col)
		{
			_block[col, row]->print();
		}
		printf("\n");
	}
	printf("\n");
	//*/
}


void SudokuPuzzle::step()
{
	for(int row = 0; row < 9; ++row)
	{
		for(int col = 0; col < 9; ++col)
		{
			if(_block[col, row]->isSolved())
			{
				if(_block[col, row]->check())
				{
					int val = _block[col, row]->getValue();
					_group[COL, col]->remove(val);
					_group[ROW, row]->remove(val);
					_group[BOX, row/3*3 + col/3]->remove(val);
				}
			}
		}
	}
}
