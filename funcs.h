#ifndef FUNS_H 
#define FUNCS_H
#pragma once

#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define POW_2(a) (((a - 1) & a) == 0) and a != 0

#include <bits/stdc++.h>
using std::vector;
using std::string;
using std::unordered_map;
typedef unsigned long long ll;

//reads input file and returns corresponding board
vector<ll> process_input();
//writes board to output file
void process_output(const vector<ll> &board);

//solves the board and returns it?
vector<vector<int>> solve(vector<vector<int>>);
//generates a dictionary from entries to their candidates
vector<ll> pencil(const vector<ll> &board);
//modifies board in place by solving it via backtracking then writes solution to output file
void backtrack(vector<ll> candidates, vector<ll>& board);
//checks if board is solved
bool done(const vector<ll> &board);
//implements naked singles logic in place
void n_singles(vector<ll> &candidates, vector<ll> &board, int start);
/*
//implements hidden singles logic in place
void h_singles(vector<ll> &candidates, Board& board, int start);
*/
        /*
         * for each group we create a map of all the candidates to their frequency
         * if one of them is 1 then we know it is a hidden single and we can loop to find it
         * if two of them are two then we know it is a hidden/naked pair
         */

        //improve space by replacing set logic with bit checking



#endif