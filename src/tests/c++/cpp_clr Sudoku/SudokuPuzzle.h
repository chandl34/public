#pragma once

#include "stdafx.h"
#include "SudokuBlock.h"
#include "SudokuGroup.h"

	
enum{COL, ROW, BOX};

ref class SudokuPuzzle
{
public:
	SudokuPuzzle();
	~SudokuPuzzle();

	SudokuBlock^ getBlock(int, int);

	void print();

	void step();

private:
	array<SudokuGroup^, 2>^ _group;
	array<SudokuBlock^, 2>^ _block;
};


