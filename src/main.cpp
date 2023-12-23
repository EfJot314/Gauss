#include <thread>

#include "./HeaderFiles/interfaces.h"



using namespace std;


int main()
{
    //read data file
    ifstream file(dataFilePath);
    if (!file.is_open()) {
        cerr << "Cannot open file!" << endl;
        return 1;
    }

    //get data
    string line;

    //matrix size
    getline(file, line);
    int n = stof(line);

    //reading matrix
    InputParser ip;
    ip.createNewMatrix(n, n);
    for(int i=0;i<n;i++){
        getline(file, line);
        ip.setRow(i, line);
    }
    Matrix* m = ip.getMatrix();

    m->show("Input matrix:");

    //reading vector
    ip.createNewMatrix(n, 1);
    getline(file, line);
    ip.setRow(0, line);
    Matrix* v = ip.getMatrix();

    v->show("Input vector:");

    //transpose given vector
    v = v->getTransposedMatrix();
    v->show("Transposed vector:");


    float d = m->getDet('d');
    cout << "Definition det: " << d << endl;

    Gauss g(m, v);
    // g.classicElimination();
    g.threadElimination();

    m = g.getMatrix();
    v = g.getVector();

    m->show("Matrix after elimination:");
    v->show("Vector after elimination:");

    d = m->getDet('g');
    cout << "Gauss det: " << d << endl;



    return 0;
}
