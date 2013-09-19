// cpp_clr Sudoku.cpp : main project file.

#include "stdafx.h"
#include "SudokuPuzzle.h"

using namespace System;



int main(array<System::String ^> ^args)
{
	// Build puzzle
	SudokuPuzzle^ puzz = gcnew SudokuPuzzle();

	//puzz->setBlockValue(0, 0, 2);
	puzz->getBlock(2, 0)->setValue(3);
	
	puzz->getBlock(2, 1)->setValue(9);
	puzz->getBlock(5, 1)->setValue(1);
	puzz->getBlock(7, 1)->setValue(3);
	
	puzz->getBlock(0, 2)->setValue(1);
	puzz->getBlock(1, 2)->setValue(4);
	puzz->getBlock(4, 2)->setValue(5);
	puzz->getBlock(5, 2)->setValue(7);
	puzz->getBlock(8, 2)->setValue(8);
	
	puzz->getBlock(0, 3)->setValue(6);
	puzz->getBlock(2, 3)->setValue(5);
	puzz->getBlock(5, 3)->setValue(4);
	
	puzz->getBlock(0, 4)->setValue(8);
	puzz->getBlock(3, 4)->setValue(2);
	puzz->getBlock(5, 4)->setValue(5);
	puzz->getBlock(8, 4)->setValue(7);
	
	puzz->getBlock(3, 5)->setValue(1);
	puzz->getBlock(6, 5)->setValue(4);
	puzz->getBlock(8, 5)->setValue(6);
	
	puzz->getBlock(0, 6)->setValue(9);
	puzz->getBlock(3, 6)->setValue(4);
	puzz->getBlock(4, 6)->setValue(1);
	puzz->getBlock(7, 6)->setValue(2);
	puzz->getBlock(8, 6)->setValue(5);
	
	puzz->getBlock(1, 7)->setValue(3);
	puzz->getBlock(3, 7)->setValue(8);
	puzz->getBlock(6, 7)->setValue(6);
	
	puzz->getBlock(6, 8)->setValue(1);

	// Menu
	printf("'1' to show puzzle\n");
	printf("'2' to step puzzle\n");
	printf("'3' to quit\n");

	System::String^ line;
	while(true){
		line = Console::ReadLine();

		if(line->Equals("1"))
		{
			puzz->print();
		}
		else if(line->Equals("2"))
		{
			puzz->step();
		}
		else if(line->Equals("3"))
		{
			break;
		}
	}



    return 0;
}
