project5.exe: main.o Permutation.o nString.o
	g++ main.o Permutation.o nString.o  -o project5.exe

main.o: main.C Permutation.h nString.h
	g++ -c main.C

Permutation.o: Permutation.C Permutation.h
	g++ -c Permutation.C

nString.o: nString.C nString.h
	g++ -c nString.C