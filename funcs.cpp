#include "funcs.h"
using std::getline;
using std::ofstream;
using std::ifstream;

int groups[27][9] = {{0,1,2,3,4,5,6,7,8},
                     {9,10,11,12,13,14,15,16,17},
                     {18,19,20,21,22,23,24,25,26},
                     {27,28,29,30,31,32,33,34,35},
                     {36,37,38,39,40,41,42,43,44},
                     {45,46,47,48,49,50,51,52,53},
                     {54,55,56,57,58,59,60,61,62},
                     {63,64,65,66,67,68,69,70,71},
                     {72,73,74,75,76,77,78,79,80},
                     {0,9,18,27,36,45,54,63,72},
                     {1,10,19,28,37,46,55,64,73},
                     {2,11,20,29,38,47,56,65,74},
                     {3,12,21,30,39,48,57,66,75},
                     {4,13,22,31,40,49,58,67,76},
                     {5,14,23,32,41,50,59,68,77},
                     {6,15,24,33,42,51,60,69,78},
                     {7,16,25,34,43,52,61,70,79},
                     {8,17,26,35,44,53,62,71,80},
                     {0,1,2,9,10,11,18,19,20},
                     {3,4,5,12,13,14,21,22,23},
                     {6,7,8,15,16,17,24,25,26},
                     {27,28,29,36,37,38,45,46,47},
                     {30,31,32,39,40,41,48,49,50},
                     {33,34,35,42,43,44,51,52,53},
                     {54,55,56,63,64,65,72,73,74},
                     {57,58,59,66,67,68,75,76,77},
                     {60,61,62,69,70,71,78,79,80}};

unordered_map<int, vector<int>> neighbors = {
        {0, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 27, 36, 45, 54, 63, 72}},
        {1,  {0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 28, 37, 46, 55, 64, 73}},
        {2, {0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 19, 20, 29, 38, 47, 56, 65, 74}},
        {3, {0, 1, 2, 4, 5, 6, 7, 8, 12, 13, 14, 21, 22, 23, 30, 39, 48, 57, 66, 75}},
        {4, {0, 1, 2, 3, 5, 6, 7, 8, 12, 13, 14, 21, 22, 23, 31, 40, 49, 58, 67, 76}},
        {5, {0, 1, 2, 3, 4, 6, 7, 8, 12, 13, 14, 21, 22, 23, 32, 41, 50, 59, 68, 77}},
        {6, {0, 1, 2, 3, 4, 5, 7, 8, 15, 16, 17, 24, 25, 26, 33, 42, 51, 60, 69, 78}},
        {7, {0, 1, 2, 3, 4, 5, 6, 8, 15, 16, 17, 24, 25, 26, 34, 43, 52, 61, 70, 79}},
        {8, {0, 1, 2, 3, 4, 5, 6, 7, 15, 16, 17, 24, 25, 26, 35, 44, 53, 62, 71, 80}},
        {9, {0, 1, 2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 27, 36, 45, 54, 63, 72}},
        {10, {0, 1, 2, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 28, 37, 46, 55, 64, 73}},
        {11, {0, 1, 2, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 29, 38, 47, 56, 65, 74}},
        {12, {3, 4, 5, 9, 10, 11, 13, 14, 15, 16, 17, 21, 22, 23, 30, 39, 48, 57, 66, 75}},
        {13, {3, 4, 5, 9, 10, 11, 12, 14, 15, 16, 17, 21, 22, 23, 31, 40, 49, 58, 67, 76}},
        {14, {3, 4, 5, 9, 10, 11, 12, 13, 15, 16, 17, 21, 22, 23, 32, 41, 50, 59, 68, 77}},
        {15, {6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 24, 25, 26, 33, 42, 51, 60, 69, 78}},
        {16, {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17, 24, 25, 26, 34, 43, 52, 61, 70, 79}},
        {17, {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 24, 25, 26, 35, 44, 53, 62, 71, 80}},
        {18, {0, 1, 2, 9, 10, 11, 19, 20, 21, 22, 23, 24, 25, 26, 27, 36, 45, 54, 63, 72}},
        {19, {0, 1, 2, 9, 10, 11, 18, 20, 21, 22, 23, 24, 25, 26, 28, 37, 46, 55, 64, 73}},
        {20, {0, 1, 2, 9, 10, 11, 18, 19, 21, 22, 23, 24, 25, 26, 29, 38, 47, 56, 65, 74}},
        {21, {3, 4, 5, 12, 13, 14, 18, 19, 20, 22, 23, 24, 25, 26, 30, 39, 48, 57, 66, 75}},
        {22, {3, 4, 5, 12, 13, 14, 18, 19, 20, 21, 23, 24, 25, 26, 31, 40, 49, 58, 67, 76}},
        {23, {3, 4, 5, 12, 13, 14, 18, 19, 20, 21, 22, 24, 25, 26, 32, 41, 50, 59, 68, 77}},
        {24, {6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 33, 42, 51, 60, 69, 78}},
        {25, {6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 26, 34, 43, 52, 61, 70, 79}},
        {26, {6, 7, 8, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 35, 44, 53, 62, 71, 80}},
        {27, {0, 9, 18, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 45, 46, 47, 54, 63, 72}},
        {28, {1, 10, 19, 27, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 45, 46, 47, 55, 64, 73}},
        {29, {2, 11, 20, 27, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 45, 46, 47, 56, 65, 74}},
        {30, {3, 12, 21, 27, 28, 29, 31, 32, 33, 34, 35, 39, 40, 41, 48, 49, 50, 57, 66, 75}},
        {31, {4, 13, 22, 27, 28, 29, 30, 32, 33, 34, 35, 39, 40, 41, 48, 49, 50, 58, 67, 76}},
        {32, {5, 14, 23, 27, 28, 29, 30, 31, 33, 34, 35, 39, 40, 41, 48, 49, 50, 59, 68, 77}},
        {33, {6, 15, 24, 27, 28, 29, 30, 31, 32, 34, 35, 42, 43, 44, 51, 52, 53, 60, 69, 78}},
        {34, {7, 16, 25, 27, 28, 29, 30, 31, 32, 33, 35, 42, 43, 44, 51, 52, 53, 61, 70, 79}},
        {35, {8, 17, 26, 27, 28, 29, 30, 31, 32, 33, 34, 42, 43, 44, 51, 52, 53, 62, 71, 80}},
        {36, {0, 9, 18, 27, 28, 29, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 54, 63, 72}},
        {37, {1, 10, 19, 27, 28, 29, 36, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 55, 64, 73}},
        {38, {2, 11, 20, 27, 28, 29, 36, 37, 39, 40, 41, 42, 43, 44, 45, 46, 47, 56, 65, 74}},
        {39, {3, 12, 21, 30, 31, 32, 36, 37, 38, 40, 41, 42, 43, 44, 48, 49, 50, 57, 66, 75}},
        {40, {4, 13, 22, 30, 31, 32, 36, 37, 38, 39, 41, 42, 43, 44, 48, 49, 50, 58, 67, 76}},
        {41, {5, 14, 23, 30, 31, 32, 36, 37, 38, 39, 40, 42, 43, 44, 48, 49, 50, 59, 68, 77}},
        {42, {6, 15, 24, 33, 34, 35, 36, 37, 38, 39, 40, 41, 43, 44, 51, 52, 53, 60, 69, 78}},
        {43, {7, 16, 25, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 51, 52, 53, 61, 70, 79}},
        {44, {8, 17, 26, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 51, 52, 53, 62, 71, 80}},
        {45, {0, 9, 18, 27, 28, 29, 36, 37, 38, 46, 47, 48, 49, 50, 51, 52, 53, 54, 63, 72}},
        {46, {1, 10, 19, 27, 28, 29, 36, 37, 38, 45, 47, 48, 49, 50, 51, 52, 53, 55, 64, 73}},
        {47, {2, 11, 20, 27, 28, 29, 36, 37, 38, 45, 46, 48, 49, 50, 51, 52, 53, 56, 65, 74}},
        {48, {3, 12, 21, 30, 31, 32, 39, 40, 41, 45, 46, 47, 49, 50, 51, 52, 53, 57, 66, 75}},
        {49, {4, 13, 22, 30, 31, 32, 39, 40, 41, 45, 46, 47, 48, 50, 51, 52, 53, 58, 67, 76}},
        {50, {5, 14, 23, 30, 31, 32, 39, 40, 41, 45, 46, 47, 48, 49, 51, 52, 53, 59, 68, 77}},
        {51, {6, 15, 24, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 49, 50, 52, 53, 60, 69, 78}},
        {52, {7, 16, 25, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 53, 61, 70, 79}},
        {53, {8, 17, 26, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 62, 71, 80}},
        {54, {0, 9, 18, 27, 36, 45, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 72, 73, 74}},
        {55, {1, 10, 19, 28, 37, 46, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 72, 73, 74}},
        {56, {2, 11, 20, 29, 38, 47, 54, 55, 57, 58, 59, 60, 61, 62, 63, 64, 65, 72, 73, 74}},
        {57, {3, 12, 21, 30, 39, 48, 54, 55, 56, 58, 59, 60, 61, 62, 66, 67, 68, 75, 76, 77}},
        {58, {4, 13, 22, 31, 40, 49, 54, 55, 56, 57, 59, 60, 61, 62, 66, 67, 68, 75, 76, 77}},
        {59, {5, 14, 23, 32, 41, 50, 54, 55, 56, 57, 58, 60, 61, 62, 66, 67, 68, 75, 76, 77}},
        {60, {6, 15, 24, 33, 42, 51, 54, 55, 56, 57, 58, 59, 61, 62, 69, 70, 71, 78, 79, 80}},
        {61, {7, 16, 25, 34, 43, 52, 54, 55, 56, 57, 58, 59, 60, 62, 69, 70, 71, 78, 79, 80}},
        {62, {8, 17, 26, 35, 44, 53, 54, 55, 56, 57, 58, 59, 60, 61, 69, 70, 71, 78, 79, 80}},
        {63, {0, 9, 18, 27, 36, 45, 54, 55, 56, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74}},
        {64, {1, 10, 19, 28, 37, 46, 54, 55, 56, 63, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74}},
        {65, {2, 11, 20, 29, 38, 47, 54, 55, 56, 63, 64, 66, 67, 68, 69, 70, 71, 72, 73, 74}},
        {66, {3, 12, 21, 30, 39, 48, 57, 58, 59, 63, 64, 65, 67, 68, 69, 70, 71, 75, 76, 77}},
        {67, {4, 13, 22, 31, 40, 49, 57, 58, 59, 63, 64, 65, 66, 68, 69, 70, 71, 75, 76, 77}},
        {68, {5, 14, 23, 32, 41, 50, 57, 58, 59, 63, 64, 65, 66, 67, 69, 70, 71, 75, 76, 77}},
        {69, {6, 15, 24, 33, 42, 51, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 71, 78, 79, 80}},
        {70, {7, 16, 25, 34, 43, 52, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 71, 78, 79, 80}},
        {71, {8, 17, 26, 35, 44, 53, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 78, 79, 80}},
        {72, {0, 9, 18, 27, 36, 45, 54, 55, 56, 63, 64, 65, 73, 74, 75, 76, 77, 78, 79, 80}},
        {73, {1, 10, 19, 28, 37, 46, 54, 55, 56, 63, 64, 65, 72, 74, 75, 76, 77, 78, 79, 80}},
        {74, {2, 11, 20, 29, 38, 47, 54, 55, 56, 63, 64, 65, 72, 73, 75, 76, 77, 78, 79, 80}},
        {75, {3, 12, 21, 30, 39, 48, 57, 58, 59, 66, 67, 68, 72, 73, 74, 76, 77, 78, 79, 80}},
        {76, {4, 13, 22, 31, 40, 49, 57, 58, 59, 66, 67, 68, 72, 73, 74, 75, 77, 78, 79, 80}},
        {77, {5, 14, 23, 32, 41, 50, 57, 58, 59, 66, 67, 68, 72, 73, 74, 75, 76, 78, 79, 80}},
        {78, {6, 15, 24, 33, 42, 51, 60, 61, 62, 69, 70, 71, 72, 73, 74, 75, 76, 77, 79, 80}},
        {79, {7, 16, 25, 34, 43, 52, 60, 61, 62, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 80}},
        {80, {8, 17, 26, 35, 44, 53, 60, 61, 62, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79}}
};

Board process_input(){
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

void process_output(Board board) {
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

Candidates pencil(Board board) {
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

bool done(Board board){
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

void backtrack(Candidates candidates, Board& board){
    if(done(board)) process_output(board);
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                for(int candidate : candidates[9 * i + j]){
                    board[i][j] = candidate;
                    //checks to see if candidate is valid
                    ll used = 0;
                    for(int k = 0; k < 20; k++){
                        int index = neighbors[9*i+j][k];
                        int entry = board[index / 9][index % 9];
                        if((used & 1 << entry) == 0) used += 1 << entry;
                    }
                    //if valid then onto next cell
                    if((used & 1 << candidate) == 0) backtrack(candidates, board);
                }
                //reset and go back one cell
                board[i][j] = 0;
                return;
            }
        }
    }
}

void n_singles(Candidates &candidates, Board& board, int start){
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

void h_singles(Candidates &candidates, Board& board, int start) {
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