#include "../HeaderFiles/interfaces.h"


using namespace std;


InputParser::InputParser(){};

InputParser::~InputParser(){};

void InputParser::createNewMatrix(int x, int y){
    nx = x;
    ny = y;
    matrix = new Matrix(nx, ny);
};

void InputParser::setRow(int i, string line){
    //validation
    if(i < 0 || i >= ny){
        cerr<<"InputParser::setRow() => Wrong row index."<<endl;
        return;
    }

    istringstream iss(line);
    float value;
    for(int j=0;j<nx;j++){
        iss >> value;
        matrix->setValue(i, j, value);
    }
};

Matrix* InputParser::getMatrix(){
    return matrix;
};
