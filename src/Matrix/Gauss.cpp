#include <thread>

#include "../HeaderFiles/interfaces.h"


using namespace std;





int funA(float** valA, float*** valB, int i1, int i2, Matrix* m, thread** A, thread*** B, thread*** C){
    //waiting
    if(i1 > 0){
        while(C[i1-1][i1][i1].joinable()){} 
        while(C[i1-1][i2][i1].joinable()){}
    }
    //doing
    valA[i1][i2] = m->getValue(i2, i1) / m->getValue(i1, i1);
    return 0;
};

int funB(float** valA, float*** valB, int i1, int i2, int j, Matrix* m, thread** A, thread*** B, thread*** C){
    //waiting
    while(A[i1][i2].joinable()){}
    if(j > i1 && i1 > 0){
        while(C[i1-1][i2-1][j].joinable()){}
    }
    //doing
    valB[i1][i2][j] = m->getValue(i1, j) * valA[i1][i2];
    return 0;
};

int funC(float** valA, float*** valB, int i1, int i2, int j, Matrix* m, thread** A, thread*** B, thread*** C){
    //waiting
    while(B[i1][i2][j].joinable()){}
    if(j > i1 && i1 > 0){
        while(C[i1-1][i2][j].joinable()){}
    }
    //doing
    m->setValue(i2, j, m->getValue(i2, j) - valB[i1][i2][j]);
    return 0;
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
    v = NULL;
    //add vector to matrix
    m = matrix->addColumns(vector);
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

    
    //A -> finding multipliers
    thread** A = new thread*[ny];
    for(int i=0;i<ny;i++)
        A[i] = new thread[ny];
    //B -> multiplying elements
    thread*** B = new thread**[ny];
    for(int i=0;i<ny;i++){
        B[i] = new thread*[ny];
        for(int j=0;j<ny;j++)
            B[i][j] = new thread[nx];
    }
    //C -> subtracting elements
    thread*** C = new thread**[ny];
    for(int i=0;i<ny;i++){
        C[i] = new thread*[ny];
        for(int j=0;j<ny;j++)
            C[i][j] = new thread[nx];
    }


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

    

    //creating threads
    for(int i1=0;i1<ny;i1++){
        for(int i2=i1+1;i2<ny;i2++){
            A[i1][i2] = thread(funA, valA, valB, i1, i2, m, A, B, C);
            for(int j=0;j<nx;j++){
                B[i1][i2][j] = thread(funB, valA, valB, i1, i2, j, m, A, B, C);
                C[i1][i2][j] = thread(funC, valA, valB, i1, i2, j, m, A, B, C);
            }
        }
    }

    //waiting all for threads
    for(int i1=0;i1<ny;i1++){
        for(int i2=i1+1;i2<ny;i2++){
            if(A[i1][i2].joinable()){
                A[i1][i2].join();
            }
            for(int j=0;j<nx;j++){
                while(B[i1][i2][j].joinable()){
                    B[i1][i2][j].join();
                }
                while(C[i1][i2][j].joinable()){
                    C[i1][i2][j].join();
                }
            }
        }
    }


};

Matrix* Gauss::getMatrix(){
    if(v == NULL)
        v = m->popLastColumn();
    return m;
};

Matrix* Gauss::getVector(){
    if(v == NULL)
        v = m->popLastColumn();
    return v;
};



