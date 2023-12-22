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

class SqMatrix{
    private:
        int n;
        float** tab;
    public:
        SqMatrix();
        SqMatrix(int n);
        ~SqMatrix();
        void setValue(int i, int j, float value);
        float getValue(int i, int j);
};




