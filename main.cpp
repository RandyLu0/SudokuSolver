#include "funcs.h"
using std::cout;

void printSet(unordered_set<int> set) {
    for (auto x : set) {
        cout << x << " ";
    }
}

int main(){
    Board input = process_input();
    //Candidates candidates = pencil(input);
    //n_singles(candidates, input,0);

/*
    //prints candidates
    for(auto x : candidates){
        cout << x.first << ": ";
        printSet(x.second);
        cout << "\n";
    }
    process_output(input);
*/

    backtrack(pencil(input), input);
    //process_output(input);

    // process_output(input);
    // cout << getSqSet(0, input).size() << "\n";

    


    return 0;
}

