#include "../../HeaderFiles/interfaces.h"

Vertex::Vertex(){};

Vertex::Vertex(std::string id){
    Vertex(0, 0, id);
}

Vertex::Vertex(int x, int y, std::string id){
    this->id = id;
    setPosition(x, y);
    r = 30.0f;

    //creating circle
    circle = new sf::CircleShape(r, 100);
    circle->setFillColor(sf::Color::Black);

    //loading font
    font.loadFromFile(fontFilePath);

    //creating text object
    text = new sf::Text(id, font, 30);
    text->setStyle(sf::Text::Bold);
    text->setFillColor(sf::Color::White);
}

Vertex::~Vertex(){};

void Vertex::addToWindow(sf::RenderWindow* window){
    circle->setPosition(x-r, y-r);
    int w = text->getLocalBounds().width;
    int h = text->getLocalBounds().height;
    text->setPosition(x-w*2/3, y-h);
    window->draw(*circle);
    window->draw(*text);
};

void Vertex::setPosition(int x, int y){
    this->x = x;
    this->y = y;
};

int Vertex::getPositionX(){
    return x;
};

int Vertex::getPositionY(){
    return y;
};

std::string Vertex::getId(){
    return id;
};

bool Vertex::isOverVertex(int xi, int yi){
    int Rsq = (x-xi)*(x-xi) + (y-yi)*(y-yi); 
    return Rsq < r*r;
};