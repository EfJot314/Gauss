#include "../headerFiles/interfaces.h"


Edge::Edge(){};

Edge::Edge(Vertex* v1, Vertex* v2){
    this->v1 = v1;
    this->v2 = v2;
    line = new sf::VertexArray(sf::PrimitiveType::Lines, 2);
    (*line)[0].color = sf::Color::Green;
    (*line)[1].color = sf::Color::Red;
    updatePosition();
};

Edge::~Edge(){};

void Edge::updatePosition(){
    (*line)[0].position = sf::Vector2f(v1->getPositionX(), v1->getPositionY());
    (*line)[1].position = sf::Vector2f(v2->getPositionX(), v2->getPositionY());
};

void Edge::addToWindow(sf::RenderWindow* window){
    window->draw(*line);
};