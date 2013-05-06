// cpp_clr Sudoku.cpp : main project file.

#include "stdafx.h"

using namespace System;

int main(array<System::String ^> ^args)
{
    //Console::WriteLine(L"Hello World");

	/*
	cliext::vector<int> test(9);
	
	printf("before:  %i\n", test.at(0));

	test.at(0) = 99;
	
	printf("after:  %i\n", test.at(0));
	*/

	// Menu
	printf("'q' to exit\n");

	System::String^ line;
	do{
		line = Console::ReadLine();
	}
	while(!line->Equals("q"));


    return 0;
}
