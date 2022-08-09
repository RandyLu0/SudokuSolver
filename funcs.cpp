#include "funcs.h"
using std::cout;
using std::freopen;
using std::getline;
using std::cin;

vector<vector<int>> solver::process_input(){
    freopen(INPUT, "r", stdin);
    vector<vector<int>> board;
    for(int i = 0; i < 9; i++){
        string line = "";
        getline(cin, line);
        vector<int> row;
        for(char c : line) if(c != ',') row.push_back(c - 48);
        board.push_back(row);
    }
    return board;
}

void solver::process_output(vector<vector<int>> board) {
    freopen(OUTPUT, "w", stdout);
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

bool solver::done(vector<vector<int>> board){
    for(int group = 0; group < 27; group++){
        unordered_set<int> entries;
        for(int i = 0; i < 9; i++){
            int index = groups[group][i];
            int entry = board[index / 9][index % 9];
            if(entry == 0) return false;
            entries.insert(entry);
        }
        if(entries.size() != 9) return false;
    }
    return true;
}

void solver::backtrack(unordered_map<int, unordered_set<int>> candidates, vector<vector<int>>& board){
    if(done(board)) process_output(board);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                for(int candidate : candidates[9 * i + j]){
                    board[i][j] = candidate;
                    //checks to see if candidate is valid
                    unordered_set<int> used;
                    for(int k = 0; k < 20; k++){
                        int index = neighbors[9*i+j][k];
                        int entry = board[index / 9][index % 9];
                        used.insert(entry);
                    }
                    //if valid then onto next cell
                    if(used.count(candidate) == 0) backtrack(candidates, board);
                }
                board[i][j] = 0;
                return;
            }
        }
    }
}

void solver::n_singles(Candidates &candidates, Board& board, int start){
    for (int index = start; index < 80; index++) {
        if(candidates[index].size() == 1){
            int entry = board[index / 9][index % 9] = *candidates[index].begin();
            candidates[index].clear();
            for (int i = 0; i < 20; ++i) {
                int neighbor = neighbors[index][i];
                candidates[neighbor].erase(entry);
                if(candidates[neighbor].size() == 1) n_singles(candidates, board, neighbor);
            }
        }
    }
}


