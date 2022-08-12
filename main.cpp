#include "funcs.h"
using std::cout;

int main(){
    vector<ll> input = process_input();
    vector<ll> candidates = pencil(input);
    //n_singles(candidates, input, 0);

/*
    //prints candidates
    for(int i = 0; i < 81;i++)
        cout << i << ": " << candidates[i] << "\n";
*/
    backtrack(pencil(input), input);
    //process_output(input);
    //cout << done(input) << "\n";

    // process_output(input);
    // cout << getSqSet(0, input).size() << "\n";

    


    return 0;
}

