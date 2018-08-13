all: make

make: main.o book.o music.o movie.o
	g++ main.o book.o music.o movie.o -o main 
main.o: main.cpp
	g++ -std=c++14 -c  main.cpp

book.o: book.cpp
	g++ -std=c++14 -c  book.cpp 
music.o:music.cpp
	g++ -std=c++14 -c music.cpp
movie.o:movie.cpp
	g++ -std=c++14 -c movie.cpp
clean:
	rm *.o exe