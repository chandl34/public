strTest.exe: Main.o nString.o
	g++ Main.o nString.o -o strTest.exe

Main.o: Main.C nString.h
	g++ -c Main.C

nString.o: nString.C nString.h
	g++ -c nString.C

