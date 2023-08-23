coms327P1: CellularAutomaton.o main.o GraphicsClient.o
	g++ CellularAutomaton.o main.o GraphicsClient.o -o gol
CellularAutomaton.o: CellularAutomaton.h CellularAutomaton.cpp GraphicsClient.h
	g++ -c CellularAutomaton.cpp
GraphicsClient.o: GraphicsClient.h GraphicsClient.cpp
	g++ -c GraphicsClient.cpp
main.o: CellularAutomaton.h GraphicsClient.h main.cpp 
	g++ -c main.cpp