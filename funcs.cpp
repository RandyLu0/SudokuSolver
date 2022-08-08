#include "funcs.h"
using std::cout;
using std::fstream;
using std::freopen;

vector<vector<int>> solver::process_input(){
    // take in input
    fstream newFile;
    vector<vector<int>> result;
    newFile.open(INPUT, std::ios::in);
    if (newFile.is_open()) {
        string s;
        while(std::getline(newFile, s)) {
            vector<int> subResult;
            for(int i = 0; i < s.length(); i++)
                if (s[i] != ',') subResult.push_back(s[i] - 48);
            result.push_back(subResult);
        }
        newFile.close();
    }
    return result;
}

void solver::process_output(vector<vector<int>> board) {
    //freopen(OUTPUT, "w", stdout);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j];
            if (j != 8) cout << ",";
        }
        cout << "\n";
    }
}
unordered_map<int, unordered_set<int>> solver::pencil(vector<vector<int>> board) {
    unordered_map<int, unordered_set<int>> penciled;
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            unordered_set<int> candidates = {1,2,3,4,5,6,7,8,9};
            if(board[i][j] != 0) candidates.clear(); 
            else 
                for(int k = 0; k < 20; k++){
                    int neighbor = neighbors[9 * i + j][k];
                    if(candidates.count(board[neighbor / 9][neighbor % 9]) > 0){
                        candidates.erase(board[neighbor / 9][neighbor % 9]);
                    }
                }
            penciled[9 * i + j] = candidates;
        }
    }
    return penciled;
}

bool solver::check(vector<vector<int>> board){
    for(int group = 0; group < 27; group++){
        unordered_set<int> entries;
        for(int i = 0; i < 9; i++){
            int index = groups[group][i];
            int entry = board[index / 9][index % 9];
            if(entries.count(entry) > 0) return false;
            if(entry != 0) entries.insert(entry);
        }
    }
    return true;
}

bool solver::done(const vector<vector<int>>& board) const{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board[i][j] == 0) return false;
    return true;
}


//erasing from idk 
void solver::backtrack(unordered_map<int, unordered_set<int>> candidates, vector<vector<int>>& board){
    if(done(board)) return;
    if(!check(board)) return;
    unordered_map<int, unordered_set<int>> c = candidates;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                cout << 9 * i + j << "\t";
                for(int candidate : c[9 * i + j]){
                    board[i][j] = candidate;
                    unordered_set<int> used;
                    for(int k = 0; k < 20; k++){
                        int index = neighbors[9*i+j][k];
                        int entry = board[index / 9][index % 9];
                        if(entry != 0) used.insert(entry);
                    }
                    if(used.count(candidate) == 0){
                        backtrack(c, board);
                        c[9 * i + j].erase(candidate);
                    }
                }
                board[i][j] = 0;
                return;
            }
        }
    }
}