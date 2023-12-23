main:
	g++ -c ./src/main.cpp  ./src/InputLogic/InputParser.cpp ./src/Matrix/Matrix.cpp ./src/Matrix/Gauss.cpp
	g++ Gauss.o -o Gauss Matrix.o -o Matrix InputParser.o -o InputParser main.o -o main
	rm -f Gauss.o Matrix.o InputParser.o main.o

clean:
	rm -f Gauss.o Matrix.o InputParser.o main.o
	rm -f main

all:
	make clean
	make main



