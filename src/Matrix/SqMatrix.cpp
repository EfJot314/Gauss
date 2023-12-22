#include "./../HeaderFiles/interfaces.h"


SqMatrix::SqMatrix(){};

SqMatrix::SqMatrix(int n){
    this->n = n;
    tab = (float**)malloc(n*sizeof(float*));
    for(int i=0;i<n;i++)
        tab[i] = (float*)calloc(n, sizeof(float));
};

SqMatrix::~SqMatrix(){
    //free memory
    for(int i=0;i<n;i++){
        free(tab[i]);
    }
    free(tab);
};

void SqMatrix::setValue(int i, int j, float value){
    tab[i][j] = value;
};

float SqMatrix::getValue(int i, int j){
    return tab[i][j];
};


