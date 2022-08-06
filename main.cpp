#include "funcs.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cout;

void printSet(unordered_set<int> set) {
        for (auto x : set) {
            cout << x << " "; 
        }
    }

int main(){
    solver slvr;
    vector<vector<int>> input = slvr.process_input();
    
    // for( int i =0 ; i < 9; i ++) {
    //     for (int j = 0; j < 9; j++) {
    //         cout << input[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    // slvr.process_output(input);
    // cout << slvr.getSqSet(0, input).size() << "\n";

    

    for (auto elem : slvr.pencil(input)) {
        cout << elem.first << ": ";
        printSet(elem.second);
        cout << "\n";
    }

    return 0;
}

