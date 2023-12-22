#include "../HeaderFiles/interfaces.h"


Gauss::Gauss(){
    m = NULL;
    v = NULL;
};

Gauss::Gauss(Matrix* matrix){
    m = matrix;
    v = NULL;
};

Gauss::Gauss(Matrix* matrix, Matrix* vector){
    m = matrix;
    v = vector;
};

Gauss::~Gauss(){};

void Gauss::classicElimination(){
    int ny = m->getSizeY();
    for(int i1=0;i1<ny;i1++){
        if(m->getValue(i1, i1) == 0)
            continue;
        for(int i2=i1+1;i2<ny;i2++){
            float multiplicator = m->getValue(i2, i1) / m->getValue(i1, i1);
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
    return v;
};



