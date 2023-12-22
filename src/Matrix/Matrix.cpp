#include "./../HeaderFiles/interfaces.h"


Matrix::Matrix(){};

Matrix::Matrix(int n){
    this->n = n;
    tab = (float**)malloc(n*sizeof(float*));
    for(int i=0;i<n;i++)
        tab[i] = (float*)calloc(n, sizeof(float));
};

Matrix::~Matrix(){
    //free memory
    for(int i=0;i<n;i++){
        free(tab[i]);
    }
    free(tab);
};

void Matrix::setValue(int i, int j, float value){
    tab[i][j] = value;
};

float Matrix::getValue(int i, int j){
    return tab[i][j];
};


