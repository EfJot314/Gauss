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

    //getting word
    string word;
    getline(file, word);

    



    return 0;
}
