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
        void subtractRowsWithMultiplicator(int i1, int i2, float value);
        int getSizeX();
        int getSizeY();
        float getValue(int i, int j);
        Matrix* getTransposedMatrix();
        Matrix* addColumns(Matrix* v);
        Matrix* getLastColumn();
        void show(std::string description);
        float getDet(char method);  //g - Gauss OR d - definition
};



class Gauss{
    private:
        Matrix* m;
        Matrix* v;
        float findMultiplicator(int i1, int i2);
        float multiplicateElement(int i, int j, float value);
        void subtractElements(int i1, int i2, int j);
    public:
        Gauss();
        Gauss(Matrix* matrix);
        Gauss(Matrix* matrix, Matrix* vector);
        ~Gauss();
        void classicElimination();
        void threadElimination();
        Matrix* getMatrix();
        Matrix* getVector();

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




