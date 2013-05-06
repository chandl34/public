#pragma once

#include "stdafx.h"


ref class SudokuBlock
{
public:
	SudokuBlock();
	~SudokuBlock();

	void setValue(int);

	bool solved();

private:
	int _val;
	cliext::set<int> _poss;
};