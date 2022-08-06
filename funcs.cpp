#include "funcs.h"
using std::cout;

vector<vector<int>> solver::process_input(){
    // take in input
    std::fstream newFile;
    
    vector<vector<int>> result;
    newFile.open(INPUT, std::ios::in);
    if (newFile.is_open()) {
        string s;
        while(std::getline(newFile, s)) {
            vector<int> subResult;
            for(int i = 0; i < s.length(); i++) {
                if (s[i] != ',') {
                    //subResult.push_back(std::stoi((std::to_string(s[i] - 48)))); other way
                    subResult.push_back(s[i] - 48);
                }
            }
            result.push_back(subResult);
        }
        newFile.close();
    }
   
    return result;
}

void solver::process_output(vector<vector<int>> board) {
    // write to output
    std::freopen(OUTPUT, "w", stdout);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j];
            if (j != 8) {
                cout << ",";
            }
        }
        cout << "\n";
    }
}

void solver::backtrack(unordered_map<int, unordered_set<int>> candidates, vector<vector<int>> board, bool done){
    if(done) return
    

}

