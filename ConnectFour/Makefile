all: make

make: main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o
	g++ main.o Cell.o ConnectFourAbstract.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o -o main 

main.o: main.cpp
	g++ -std=c++14 -c  main.cpp

Cell.o: Cell.cpp
	g++ -std=c++14 -c  Cell.cpp 
ConnectFourAbstract.o:ConnectFourAbstract.cpp
	g++ -std=c++14 -c ConnectFourAbstract.cpp
ConnectFourPlus.o:ConnectFourPlus.cpp
	g++ -std=c++14 -c ConnectFourPlus.cpp
ConnectFourDiag.o:ConnectFourDiag.cpp
	g++ -std=c++14 -c ConnectFourDiag.cpp
ConnectFourPlusUndo.o:ConnectFourPlusUndo.cpp
	g++ -std=c++14 -c ConnectFourPlusUndo.cpp
clean:
	rm *.o exe

