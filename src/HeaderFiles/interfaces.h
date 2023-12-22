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

class Solver{
    private:
        InputParser ip;
        std::string word;
    public:
        Solver();
        Solver(InputParser ip, std::string word);
        ~Solver();
        Relations* createDependencies();
        Relations* createIndependecies();
        Graph* createGraph(Relations* D);
        std::string createFNF(Graph* g);
};



