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

void Matrix::subtractRowsWithMultiplicator(int i1, int i2, float value){
    if(i1 < 0 || i1 >= ny || i2 < 0 || i2 >= ny)
        std::cerr<<"Matrix::subtractRowsWithMultiplicator() => Invalid index."<<std::endl;
    else    
        for(int j=0;j<nx;j++)
            tab[i2][j] -= tab[i1][j] * value;
};

float Matrix::getValue(int i, int j){
    return tab[i][j];
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

Matrix* Matrix::addColumns(Matrix* v){
    //validation
    if(v->getSizeY() != ny){
        std::cerr<<"Matrix::subtractRowsWithMultiplicator() => Invalid index."<<std::endl;
        return NULL;
    }

    int dx = v->getSizeX();

    Matrix* nm = new Matrix(nx+dx, ny);
    for(int i=0;i<ny;i++){
        for(int j=0;j<nx;j++){
            nm->setValue(i, j, tab[i][j]);
        }
        for(int j=0;j<dx;j++){
            nm->setValue(i, nx+j, v->getValue(i, j));
        }
    }

    return nm;
};

Matrix* Matrix::getLastColumn(){
    Matrix* v = new Matrix(1, ny);
    for(int i=0;i<ny;i++){
        v->setValue(i, 0, tab[i][ny-1]);
    }
    return v;
};

Matrix* Matrix::getMatrixWithout(int ii, int ij){
    Matrix* matrix = new Matrix(nx-1, ny-1);
    for(int i=0;i<ny;i++){
        int iin = i;
        if(i == ii)
            continue;
        else if(i > ii)
            iin--;
        for(int j=0;j<nx;j++){
            int jin = j;
            if(j == ij)
                continue;
            else if(j > ij)
                jin--;
            
            matrix->setValue(iin, jin, tab[i][j]);
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

    //trivial case
    if(nx == 1)
        return tab[0][0];

    float d = 0;

    //Gauss
    if(method == 'g'){
        d = 1.0f;
        Gauss g(this);
        g.classicElimination();
        for(int i=0;i<nx;i++)
            d *= tab[i][i];

    }

    //definition
    else if(method == 'd'){
        //row -> 0
        for(int j=0;j<nx;j++){
            if(j % 2 == 0)
                d += tab[0][j] * getMatrixWithout(0, j)->getDet('d');
            else
                d -= tab[0][j] * getMatrixWithout(0, j)->getDet('d');
        }
    }
    //error message -> invalid argument
    else{
        std::cerr<<"Matrix::getDet() => Argument method = '"<<method<<"' is invalid, use 'g' or 'd'."<<std::endl;
        return NULL;
    }

    //return value
    return d;
};


