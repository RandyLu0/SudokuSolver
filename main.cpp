#include "funcs.h"
using std::cout;

void printSet(unordered_set<int> set) {
    for (auto x : set) {
        cout << x << " ";
    }
}

int main(){
    solver slvr;
    Board input = slvr.process_input();
    Candidates candidates = slvr.pencil(input);
    //slvr.n_singles(candidates, input,0);

/*
    //prints candidates
    for(auto x : candidates){
        cout << x.first << ": ";
        printSet(x.second);
        cout << "\n";
    }
    slvr.process_output(input);
*/

    //slvr.backtrack(slvr.pencil(input), input);
    slvr.process_output(input);
    cout << slvr.done(input) << "\n";

    // slvr.process_output(input);
    // cout << slvr.getSqSet(0, input).size() << "\n";

    


    return 0;
}

