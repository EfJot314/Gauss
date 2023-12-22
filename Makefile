main:
	g++ -c ./src/main.cpp ./src/graphLogic/Graph.cpp ./src/Visualization/GraphVisualizer.cpp ./src/Visualization/Vertex.cpp ./src/Visualization/Edge.cpp ./src/inputLogic/InputParser.cpp ./src/graphLogic/Solver.cpp -I$(CURDIR)/src/SFML/sfml/include
	g++ Solver.o -o Solver InputParser.o -o InputParser Edge.o -o Edge Vertex.o -o Vertex GraphVisualizer.o -o GraphVisualizer Graph.o -o Graph main.o -o main -L$(CURDIR)/src/SFML/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
	rm -f Solver.o InputParser.o Edge.o Vertex.o GraphVisualizer.o Graph.o main.o

clean:
	rm -f main

all:
	make clean
	make main



