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





    float d = m->getDet('d');



    return 0;
}
