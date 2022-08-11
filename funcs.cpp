#include "funcs.h"
using std::getline;
using std::ofstream;
using std::ifstream;

Board solver::process_input(){
    ifstream file(INPUT);
    Board board;
    string line = "";
    for(int i = 0; i < 9; i++){
        getline(file, line);
        vector<int> row;
        for(char c : line) if(c != ',') row.push_back(c - 48);
        board.push_back(row);
    }
    file.close();
    return board;
}

void solver::process_output(Board board) {
    ofstream file(OUTPUT);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            file << board[i][j];
            if (j != 8) file << ",";
        }
        file << "\n";
    }
    file.close();
}

Candidates solver::pencil(Board board) {
    Candidates penciled;
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

/*
bool solver::done(Board board){
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

*/
bool solver::done(Board board){
    for(int group = 0; group < 27; group++){
        ll entries = 0;
        for(int i = 0; i < 9; i++){
            int index = groups[group][i];
            int entry = board[index / 9][index % 9];
            if(entry == 0) return false;
            entries += 1 << entry;
        }
        if(entries != (1 << 10) - 2) return false;
    }
    return true;
}

void solver::backtrack(Candidates candidates, Board& board){
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

void solver::h_singles(Candidates &candidates, Board& board, int start) {
    for (int group = 0; group < 27; ++group) {
        unordered_map<int, int> frequencies;
        for (int i = 0; i < 9; ++i) frequencies[i + 1] = 0;
        for (int i = 0; i < 9; ++i)
            for (int candidate : candidates[groups[group][i]]) {
                if(frequencies.count(candidate) == 0) frequencies[candidate] = 1;
                else frequencies[candidate] += 1;
            }
        for (int candidate = 1; candidate <= 9; candidate++) {
            if(frequencies[candidate] == 1){
                for(int i = 0; i < 9; i++){
                    if(candidates[groups[group][i]].count(candidate) == 1){
                        board[i / 9][i % 9] = candidate;
                        candidates[groups[group][i]].clear();
                        for (int j = 0; j < 20; ++j) {
                            candidates[neighbors[i][j]].erase(candidate);
                        }
                    }
                }
            }
        }
    }
}