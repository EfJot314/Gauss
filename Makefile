main:
	g++ -c ./src/main.cpp ./src/Graph/Graph.cpp ./src/Graph/Visualization/GraphVisualizer.cpp ./src/Graph/Visualization/Vertex.cpp ./src/Graph/Visualization/Edge.cpp ./src/InputLogic/InputParser.cpp ./src/Matrix/SqMatrix.cpp -I$(CURDIR)/src/SFML/sfml/include
	g++ SqMatrix.o -o SqMatrix InputParser.o -o InputParser Edge.o -o Edge Vertex.o -o Vertex GraphVisualizer.o -o GraphVisualizer Graph.o -o Graph main.o -o main -L$(CURDIR)/src/SFML/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
	rm -f SqMatrix.o InputParser.o Edge.o Vertex.o GraphVisualizer.o Graph.o main.o

clean:
	rm -f main

all:
	make clean
	make main



