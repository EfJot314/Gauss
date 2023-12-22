#include "graphDependencies.h"



class Matrix{
    private:
        int nx;
        int ny;
        float** tab;
        Matrix* getMatrixWithout(int ii, int ij);
    public:
        Matrix();
        Matrix(int nx, int ny);
        ~Matrix();
        void setValue(int i, int j, float value);
        int getSizeX();
        int getSizeY();
        float getValue(int i, int j);
        Matrix* getTransposedMatrix();
        void show(std::string description);
        float getDet(char method);  //g - Gauss OR d - definition
};



class InputParser{
    private:
        int nx;
        int ny;
        Matrix* matrix;
    public:
        InputParser();
        ~InputParser();
        void createNewMatrix(int x, int y);
        void setRow(int i, std::string line);
        Matrix* getMatrix();
};







