#include "funcs.h"
#include <iostream>
#include <fstream>
#include <string>
using std::cout;



int main(){
    solver slvr;
    vector<vector<int>> input = slvr.process_input();
    
    // for( int i =0 ; i < 9; i ++) {
    //     for (int j = 0; j < 9; j++) {
    //         cout << input[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    slvr.process_output(input);

    return 0;
}

