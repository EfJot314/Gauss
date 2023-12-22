#include "../headerFiles/interfaces.h"


InputParser::InputParser(){
    n = 0;
    actions = (Action*)calloc(maxNoActions, sizeof(Action));
};

InputParser::~InputParser(){};

void InputParser::freeMemory(){
    free(actions);
};

void InputParser::parse(std::string line){
    //remove all what is not a letter
    std::string newLine = "";
    for(char c : line){
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            newLine += c;
        }
    }
    //create new action
    Action a;
    a.id = newLine[0];
    a.variable = newLine[1];
    a.dependencies = (char*)calloc(newLine.length()-2, sizeof(char));
    a.nOfDependencies = newLine.length()-2;
    for(int i=2;i<newLine.length();i++){
        a.dependencies[i-2] = newLine[i];
    }
    //add new action to array and increment n
    actions[n] = a;
    n++;
};

int InputParser::getNoActions(){
    return n;
};

Action InputParser::getAction(int id){
    return actions[id];
}

