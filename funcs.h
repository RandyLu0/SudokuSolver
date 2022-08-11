#ifndef FUNS_H 
#define FUNCS_H
#pragma once

#define INPUT "input.txt"
#define OUTPUT "output.txt"

#include <bits/stdc++.h>
using std::vector;
using std::string;
using std::unordered_map;
using std::unordered_set;
using Board = vector<vector<int>>;
using Candidates = unordered_map<int, unordered_set<int>>;
typedef unsigned long long ll;

//reads input file and returns corresponding board
Board process_input();
//writes board to output file
void process_output(Board board);
//solves the board and returns it?
vector<vector<int>> solve(vector<vector<int>>);
//generates a dictionary from entries to their candidates
Candidates pencil(Board board);
//modifies board in place by solving it via backtracking then writes solution to output file
void backtrack(Candidates candidates, Board& board);
//checks if board is solved
bool done(Board board);
//implements naked singles logic in place
void n_singles(Candidates &candidates, Board& board, int start);
void h_singles(Candidates &candidates, Board& board, int start);
        /*
         * for each group we create a map of all the candidates to their frequency
         * if one of them is 1 then we know it is a hidden single and we can loop to find it
         * if two of them are two then we know it is a hidden/naked pair
         */

        //improve space by replacing set logic with bit checking



#endif