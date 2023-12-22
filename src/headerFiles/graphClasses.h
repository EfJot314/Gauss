#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <math.h>
#include <sstream>

#include "constants.h"


struct Action{
    char id;
    char variable;
    char* dependencies;
    int nOfDependencies;
};

struct Pair{
    char e1;
    char e2;
};

struct Relations{
    Pair* tab;
    int length;
};


class Graph{
    private:
        int** matrix;
        char* names;
        int nOfVertices;
        int nOfEdges;
    public:
        Graph();
        Graph(int nOfVertices);
        ~Graph();
        int getNoVertices();
        int getNoEdges();
        void addEdge(int v1, int v2);
        void removeEdge(int v1, int v2);
        bool edgeExist(int v1, int v2);
        void setVertexName(int id, char name);
        std::string getName(int id);
        void freeMemory();
};

class Vertex{
    private:
        int x;
        int y;
        std::string id;
        float r;
        sf::CircleShape* circle;
        sf::Font font;
        sf::Text* text;
    public:
        Vertex();
        Vertex(std::string id);
        Vertex(int x, int y, std::string id);
        ~Vertex();
        void addToWindow(sf::RenderWindow* window);
        void setPosition(int x, int y);
        std::string getId();
        int getPositionX();
        int getPositionY();
        bool isOverVertex(int xi, int yi);
};

class Edge{
    private:
        Vertex* v1;
        Vertex* v2;
        sf::VertexArray* line;
    public:
        Edge();
        Edge(Vertex* v1, Vertex* v2);
        ~Edge();
        void addToWindow(sf::RenderWindow* window);
        void updatePosition();
};

class GraphVisualizer{
    private:
        Graph g;
    public:
        GraphVisualizer();
        GraphVisualizer(Graph g);
        ~GraphVisualizer();
        void showGraph();
};
