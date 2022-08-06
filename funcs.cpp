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

unordered_set<int> solver::getSqSet(int rawIndx, vector<vector<int>> board) {
    unordered_set<int> result = {1,2,3,4,5,6,7,8,9};
    // first get the current square's value
    int row = rawIndx / 9;
    int col = rawIndx % 9;
    int currSqVal = board[row][col];
    if (currSqVal != 0) { return {}; }
    // get the neighboring cells from given the key (raw index)
    for (int i = 0; i < 20; i++) {
        int currRawIndx = neighbors[rawIndx][i];
        int val = board[currRawIndx / 9][currRawIndx % 9];
        if (val != 0 && result.find(val) != result.end()) { // and val exists in result set
            result.erase(val);
        }
    }
    return result;
}

unordered_map<int, unordered_set<int>> solver::pencil(vector<vector<int>> board) {
    unordered_map<int, unordered_set<int>> squares;
    unordered_set<int> candidates;
    for (int row = 0; row < 9; row++){
        for (int col = 0; col < 9; col++){
            int rawIndx = (9 * (row)) + col; 
            squares[rawIndx] = getSqSet(rawIndx, board);
        }
    }
    return squares;
}

void solver::backtrack(unordered_map<int, unordered_set<int>> candidates, vector<vector<int>> board, bool done){
}