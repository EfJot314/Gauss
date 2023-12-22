#include <thread>

#include "../HeaderFiles/interfaces.h"



Gauss::Gauss(){
    v = NULL;
    m = NULL;
};

Gauss::Gauss(Matrix* matrix){
    v = NULL;
    m = matrix;
};

Gauss::Gauss(Matrix* matrix, Matrix* vector){
    v = vector;
    //add vector to matrix
    m = matrix->addColumns(v);
};

Gauss::~Gauss(){};

float Gauss::findMultiplicator(int i1, int i2){
    return m->getValue(i1, i1) / m->getValue(i2, i1);
};

void Gauss::classicElimination(){
    int ny = m->getSizeY();
    for(int i1=0;i1<ny;i1++){
        if(m->getValue(i1, i1) == 0)
            continue;
        for(int i2=i1+1;i2<ny;i2++){
            float multiplicator = 1 / findMultiplicator(i1, i2);
            m->subtractRowsWithMultiplicator(i1, i2, multiplicator);
            //if vector is also given
            if(v != NULL){
                v->subtractRowsWithMultiplicator(i1, i2, multiplicator);
            }
            m->setValue(i2, i1, 0);     //to avoid approximation errors
        }
    }
};

void Gauss::threadElimination(){

};

Matrix* Gauss::getMatrix(){
    return m;
};

Matrix* Gauss::getVector(){
    v = m->getLastColumn();
    return v;
};



