#include "funcs.h"

vector<vector<int>> solver::process_input(){
    // take in input
    std::fstream newFile;
    
    vector<vector<int>> result;
    newFile.open("input.txt", std::ios::in);
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
