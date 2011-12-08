project6.exe: main.o PQ.o Item.o Grassland.o Animal.o Wolf.o Rabbit.o LList.o
	g++ main.o PQ.o Item.o Grassland.o Animal.o Wolf.o Rabbit.o LList.o -o project6.exe

main.o : main.C
	g++ -c main.C

Item.o : Item.C Item.h
	g++ -c Item.C

Grassland.o : Grassland.C Grassland.h
	g++ -c Grassland.C

PQ.o : PQ.C PQ.h
	g++ -c PQ.C

Animal.o : Animal.C Animal.h
	g++ -c Animal.C

Wolf.o : Wolf.C Wolf.h
	g++ -c Wolf.C

Rabbit.o : Rabbit.C Rabbit.h
	g++ -c Rabbit.C

LList.o : LList.C LList.h
	g++ -c LList.C
