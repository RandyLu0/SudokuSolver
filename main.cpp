#include "funcs.h"
using std::cout;

void printSet(unordered_set<int> set) {
        for (auto x : set) {
            cout << x << " "; 
        }
    }

int main(){
    solver slvr;
    vector<vector<int>> input = slvr.process_input();
    slvr.process_output(input);
    
    /* 
    //prints candidates
    unordered_map<int, unordered_set<int>> a = slvr.pencil(input);
    for(auto x : a){
        cout << x.first << ": ";
        printSet(x.second);
        cout << "\n";
    }
    */

    slvr.backtrack(slvr.pencil(input), input);
    //slvr.process_output(input);

    // slvr.process_output(input);
    // cout << slvr.getSqSet(0, input).size() << "\n";

    


    return 0;
}

