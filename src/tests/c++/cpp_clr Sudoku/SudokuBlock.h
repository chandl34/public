#pragma once

#include "stdafx.h"


ref class SudokuBlock
{
public:
	SudokuBlock();
	~SudokuBlock();

	int getValue();
	bool isSolved();

	void setValue(int);
	void remove(int);
	bool check();

	void print();

private:
	bool _checked;
	cliext::set<int> _poss;
};