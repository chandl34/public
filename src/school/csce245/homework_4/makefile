project4.exe: main.o Node.o PriorityQueue.o
	g++ main.o PriorityQueue.o Node.o  -o project4.exe

main.o: main.C PriorityQueue.h Node.h
	g++ -c main.C

PriorityQueue.o: PriorityQueue.C PriorityQueue.h
	g++ -c PriorityQueue.C

Node.o: Node.C Node.h
	g++ -c Node.C