#include "./../HeaderFiles/interfaces.h"


Matrix::Matrix(){};

Matrix::Matrix(int nx, int ny){
    this->nx = nx;
    this->ny = ny;
    tab = (float**)malloc(nx*sizeof(float*));
    for(int i=0;i<nx;i++)
        tab[i] = (float*)calloc(ny, sizeof(float));
};

Matrix::~Matrix(){
    //free memory
    for(int i=0;i<nx;i++){
        free(tab[i]);
    }
    free(tab);
};

void Matrix::setValue(int i, int j, float value){
    if(i >=0 && i < nx && j >= 0 && j < ny)
        tab[i][j] = value;
    else    
        std::cerr<<"Invalid index."<<std::endl;
};

float Matrix::getValue(int i, int j){
    if(i >=0 && i < nx && j >= 0 && j < ny)
        return tab[i][j];
    else    
        std::cerr<<"Invalid index."<<std::endl;
};

int Matrix::getSizeX(){
    return nx;
};

int Matrix::getSizeY(){
    return ny;
};

void Matrix::show(){
    printf("\n");
    for(int i=0;i<nx;i++){
        printf("| ");
        for(int j=0;j<ny;j++){
            printf("%.2f\t", tab[j][i]);
        }
        printf("|\n");
    }
    printf("\n");
};

float Matrix::getDet(char method){
    //validation
    if(nx != ny){
        std::cerr<<"Matrix::getDet() => Matrix size is invalid (nx="<<nx<<", ny="<<ny<<")."<<std::endl;
        return NULL;
    }

    //Gauss
    if(method == 'g'){
        
    }

    //definition
    else if(method == 'd'){

    }
    //error message -> invalid argument
    else{
        std::cerr<<"Matrix::getDet() => Argument method = '"<<method<<"' is invalid, use 'g' or 'd'."<<std::endl;
        return NULL;
    }
    return 1;
};


