#include "./../HeaderFiles/interfaces.h"


Matrix::Matrix(){};

Matrix::Matrix(int nx, int ny){
    this->nx = nx;
    this->ny = ny;
    tab = (float**)malloc(ny*sizeof(float*));
    for(int i=0;i<ny;i++)
        tab[i] = (float*)calloc(nx, sizeof(float));
};

Matrix::~Matrix(){
    //free memory
    for(int i=0;i<nx;i++){
        free(tab[i]);
    }
    free(tab);
};

void Matrix::setValue(int i, int j, float value){
    if(i >=0 && i < ny && j >= 0 && j < nx)
        tab[i][j] = value;
    else    
        std::cerr<<"Matrix::setValue() => Invalid index."<<std::endl;
};

float Matrix::getValue(int i, int j){
    if(i >=0 && i < ny && j >= 0 && j < nx)
        return tab[i][j];
    else    
        std::cerr<<"Matrix::getValue() => Invalid index."<<std::endl;
};

int Matrix::getSizeX(){
    return nx;
};

int Matrix::getSizeY(){
    return ny;
};

void Matrix::show(std::string description){
    std::cout<<description<<std::endl;
    for(int i=0;i<ny;i++){
        printf("| ");
        for(int j=0;j<nx;j++){
            printf("%.2f\t", tab[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
};

Matrix* Matrix::getTransposedMatrix(){
    Matrix* matrix = new Matrix(ny, nx);
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            matrix->setValue(j, i, tab[i][j]);
        }
    }
    return matrix;
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


