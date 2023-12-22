#include "graphDependencies.h"

class InputParser{
    private:
        int n;
        Action* actions;
    public:
        InputParser();
        ~InputParser();
        void parse(std::string line);
        int getNoActions();
        Action getAction(int id);
        void freeMemory();
};

class Matrix{
    private:
        int n;
        float** tab;
    public:
        Matrix();
        Matrix(int n);
        ~Matrix();
        void setValue(int i, int j, float value);
        float getValue(int i, int j);
};




