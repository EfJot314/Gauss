#include <thread>

#include "../HeaderFiles/interfaces.h"


using namespace std;





void funA(float** valA, float*** valB, float*** valC, int i1, int i2, Matrix* m){
    //waiting
    while(true){
        if(i1 == 0)
            break;
        else if(valC[i1-1][i1][i1] > 10 && valC[i1-1][i2][i2] > 10)
            break;
    }
    //doing
    valA[i1][i2] = m->getValue(i2, i1) / m->getValue(i1, i1);
};

void funB(float** valA, float*** valB, float*** valC, int i1, int i2, int j, Matrix* m){
    //waiting
    while(true){
        if(valA[i1][i2]*valA[i1][i2] > 0.0000001f){
            if(j <= i1)
                break;
            if(i1 == 0)
                break;
            if(valC[i1-1][i1][j] > 10)
                break;
        }
    }
    //doing
    valB[i1][i2][j] = m->getValue(i1, j) * valA[i1][i2];
};

void funC(float** valA, float*** valB, float*** valC, int i1, int i2, int j, Matrix* m){
    //waiting
    while(true){
        if(valB[i1][i2][j]*valB[i1][i2][j] > 0.000000001f){
            if(j <= i1)
                break;
            if(i1 == 0)
                break;
            else if(valC[i1-1][i2][j] > 10)
                break;
        }
    }
    //doing
    //TODO -> not working properly
    m->setValue(i2, j, m->getValue(i2, j) - valB[i1][i2][j]);
    valC[i1][i2][j] = 100;  //for controlling if it is done
};



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
    int nx = m->getSizeX();
    int ny = m->getSizeY();

    cout << nx << " " << ny << endl;

    
    //A -> finding multipliers
    thread* A[ny][ny];
    //B -> multiplying elements
    thread* B[ny][ny][nx];
    //C -> subtracting elements
    thread* C[ny][ny][nx];

    //values from A
    float** valA = (float**)malloc(ny*sizeof(float));
    for(int i=0;i<ny;i++)
        valA[i] = (float*)calloc(ny, sizeof(float));

    //values from B
    float*** valB = (float***)malloc(ny*sizeof(float**));
    for(int i=0;i<ny;i++){
        valB[i] = (float**)malloc(ny*sizeof(float*));
        for(int j=0;j<ny;j++)
            valB[i][j] = (float*)calloc(nx, sizeof(float));
    }

    //values from C -> only for controlling if thread has ended
    float*** valC = (float***)malloc(ny*sizeof(float**));
    for(int i=0;i<ny;i++){
        valC[i] = (float**)malloc(ny*sizeof(float*));
        for(int j=0;j<ny;j++)
            valC[i][j] = (float*)calloc(nx, sizeof(float));
    }

    

    //creating threads
    for(int i1=0;i1<1;i1++){
        for(int i2=i1+1;i2<ny;i2++){
            A[i1][i2] = new thread(funA, valA, valB, valC, i1, i2, m);
            for(int j=0;j<nx;j++){
                B[i1][i2][j] = new thread(funB, valA, valB, valC, i1, i2, j, m);
                C[i1][i2][j] = new thread(funC, valA, valB, valC, i1, i2, j, m);
            }
        }
    }


};

Matrix* Gauss::getMatrix(){
    return m;
};

Matrix* Gauss::getVector(){
    v = m->getLastColumn();
    return v;
};



