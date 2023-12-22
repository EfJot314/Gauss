#include "../headerFiles/interfaces.h"




//this function works only on graphs without any cycles
//returns a maximum number of edges which can be used to get from v1 to v2
int dfs(int v1, int v2, int value, Graph* g){
    //end condition
    if(v1 == v2) 
        return value;
    //if edge between v1 and i exist...
    int toReturn = -1;
    for(int i=0;i<g->getNoVertices();i++){
        if(g->edgeExist(v1, i)){
            //...then check if it is longer way to v2, than other ways
            int var = dfs(i, v2, value+1, g);
            if(var > toReturn)
                toReturn = var;
        }
    }
    //return
    return toReturn;
}




Solver::Solver(){};

Solver::Solver(InputParser ip, std::string word){
    this->ip = ip;
    this->word = word;
};

Solver::~Solver(){};

Relations* Solver::createDependencies(){
    int n = ip.getNoActions();
    Relations* D = new Relations;
    D->tab = (Pair*)calloc(n*n, sizeof(Pair));
    D->length = 0;
    //for every action...
    for(int i=0;i<n;i++){
        Action a = ip.getAction(i);
        //...search for another action...
        for(int j=0;j<n;j++){
            bool flag = false;
            Action b = ip.getAction(j);
            //...which has my variable in dependencies...
            for(int z=0;z<b.nOfDependencies;z++){
                if(b.dependencies[z] == a.variable){
                    flag = true;
                    D->tab[D->length] = Pair{a.id, b.id};
                    D->length++;
                    break;
                }
            }
            if(!flag){
                //...or I have its variable in dependencies...
                for(int z=0;z<a.nOfDependencies;z++){
                    if(a.dependencies[z] == b.variable){
                        D->tab[D->length] = Pair{a.id, b.id};
                        D->length++;
                        flag = true;
                        break;
                    }
                }
                if(!flag){
                    //...or if both has the same variable...
                    if(a.variable == b.variable){
                        D->tab[D->length] = Pair{a.id, b.id};
                        D->length++;
                        flag = true;
                    }
                }
            }
        }
    }
    return D;
};

Relations* Solver::createIndependecies(){
    int n = ip.getNoActions();
    Relations* I = new Relations;
    I->tab = (Pair*)calloc(n*n, sizeof(Pair));
    I->length = 0;
    //for every action...
    for(int i=0;i<n;i++){
        Action a = ip.getAction(i);
        //...search for another action...
        for(int j=0;j<n;j++){
            bool flag = false;
            Action b = ip.getAction(j);
            //...which has my variable in dependencies...
            for(int z=0;z<b.nOfDependencies;z++){
                if(b.dependencies[z] == a.variable){
                    flag = true;
                    break;
                }
            }
            if(!flag){
                //...or I have its variable in dependencies...
                for(int z=0;z<a.nOfDependencies;z++){
                    if(a.dependencies[z] == b.variable){
                        flag = true;
                        break;
                    }
                }
                if(!flag){
                    //...or if both has the same variable...
                    if(a.variable == b.variable){
                        flag = true;
                    }
                    //if there is no relation between a and b, then add to I
                    if(!flag){
                        I->tab[I->length] = Pair{a.id, b.id};
                        I->length++;
                    }
                }
            }
        }
    }
    return I;
};


Graph* Solver::createGraph(Relations* D){
    Graph* g = new Graph(word.length());
    //for every letter in word...
    for(int i=0;i<word.length();i++){
        char c = word[i];
        //...search for action which has id equal to c
        for(int j=0;j<ip.getNoActions();j++){
            if(ip.getAction(j).id == c){
                g->setVertexName(i, c);
                //search for edges
                for(int z=0;z<i;z++){
                    //add edge only then, when it is in dependency array
                    for(int x=0;x<D->length;x++){
                        if(D->tab[x].e1 == c && D->tab[x].e2 == word[z]){
                            g->addEdge(z, i);
                            break;
                        }
                    }
                }
            }
        }
    }
    //remove duplicated edges
    for(int i=0;i<word.length();i++){
        for(int j=0;j<word.length();j++){
            //if edge between i and j exist, then check if is duplicated or not
            if(g->edgeExist(i, j)){
                //if exist longer way from i to j, then delete this edge
                if(dfs(i, j, 0, g) > 1){
                    g->removeEdge(i, j);
                }
            }
        }
    }

    //return result
    return g;
};


std::string Solver::createFNF(Graph* g){
    //variable to return
    std::string fnf = "";
    int n = g->getNoVertices();

    int counter = 0;
    int* used = (int*)calloc(n, sizeof(int));

    int newCounter = 0;
    int* newUsed = (int*)calloc(n, sizeof(int));

    while(true){
        fnf += "(";
        for(int i=0;i<n;i++){
            //if haven't used already
            bool flag = true;
            for(int j=0;j<counter;j++){
                if(used[j] == i){
                    flag = false;
                    break;
                }
            }
            if(flag){
                //check if exist edge which connects j to i
                for(int j=0;j<n;j++){
                    if(g->edgeExist(j, i)){
                        //if exist, then check if j was used already
                        flag = false;
                        for(int z=0;z<counter;z++){
                            //if used, then everything is ok, if not, then I cannot add it to fnf in this "turn"
                            if(used[z] == j){
                                flag = true;
                                break;
                            }
                        }
                        if(!flag)
                            break;
                    }
                }
                //if not exist, then add to fnf and to newUsed (used in this "turn")
                if(flag){
                    fnf += g->getName(i);
                    newUsed[newCounter] = i;
                    newCounter++;
                }
            }
            
        }
        //move all used in this () from newUsed to used
        for(int i=0;i<newCounter;i++){
            used[counter] = newUsed[i];
            counter++;
        }
        newCounter = 0;

        fnf += ")";

        //end condition -> nothing added to fnf
        if(fnf[fnf.length()-2] == '('){
            //remove last 2 chars -> ()
            fnf = fnf.substr(0, fnf.length()-2);
            break;
        }        
    }

    //free memory
    free(used);
    free(newUsed);

    //return
    return fnf;
};


