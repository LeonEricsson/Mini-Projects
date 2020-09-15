
#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <iostream>


using namespace std;

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


Boggle::Boggle(){
    board.resize(4,4);
    visited.resize(4,4);
    for(int row = 0; row < board.numRows(); row++){
         for(int col = 0; col < board.numCols(); col++){
            visited.set(row, col, 'X');
          }
       }
    userPoints = 0;
}

// Board set-up

void Boggle::setUpBoard(const bool& yesOrNo,const string& letters){
    if(yesOrNo) fillAndShuffleBoard(createCubes());
    else {
        int count = 0;
        for(int i = 0 ; i < letters.size() ; i++){
            board.set(count, i%4, letters[i]);
            if(i % 4 == 3) count++;
        }
    }
}

vector<vector<char>> Boggle::createCubes() const{
    vector<vector<char>> cubes;
    for(int i = 0 ; i < 16 ; i++){
        vector<char> inner;
        for(char c : CUBES[i]){
            inner.push_back(c);
        }
        shuffle(inner);
        cubes.push_back(inner);
    }
    return cubes;
}

void Boggle::fillAndShuffleBoard(const vector<vector<char>>& cubes){
    int count = 0;
    for(int i = 0 ; i < cubes.size() ; i++){
        board.set(count, i%4, cubes[i][0]);
        if(i % 4 == 3) count++;
    }
    shuffle(board);
}

bool Boggle::isValidWordLength(const string& word) const{
    return (word.length() < 4);
}

bool Boggle::isValidWord(const string& word) const {
    return lexicon.contains(word);
}

bool Boggle::isValidUniqueWord(const string& word) const{
    for(string usedWord : usedWords){
        if(usedWord == word){
            return false;
        }
    }
    return true;
}

bool Boggle::isValidBoard(const string& letters, bool& checkFalse) const {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    if(letters.size() != 16 ){
        checkFalse = false;
    }
    for(char c: letters){
        if(alphabet.find(c) == alphabet.npos){
            checkFalse = false;
            break;
        }
    }
}




// Backtracking Algorithm (found word)


bool Boggle::findUserWord(const string& word) {
    for(int row = 0; row < board.numRows(); row++){
         for(int col = 0; col < board.numCols(); col++){
             if(backtrackingUserWord(board.get(row, col), word, row, col)){
                 for(int row = 0; row < visited.numRows(); row++){
                      for(int col = 0; col < visited.numCols(); col++){
                          visited.set(row, col, 'X');
                         }
                      }
                 userPoints += (word.length()- 3);
                 usedWords.insert(word);
                 return true;
                 }
          }
       }
    return false;
}

bool Boggle::backtrackingUserWord(char currentLetter, const string& word, int row, int col,  unsigned int currentPos){
    if(currentLetter == word.back() && currentPos+1 == word.length()){
        return true;
    }

    if(currentLetter == word[currentPos]){
        visited.set(row, col, 'O');
        for(int i = -1 ; i < 2 ; i++){
            for(int j = -1 ; j < 2 ; j++){
                if(!(j == 0 && i == 0)){
                    if(checkInBounds(word, row+i, col+j, currentPos)) return true;
                }
            }
        }
        visited.set(row, col, 'X');
    }
    return false;
}


bool Boggle::checkInBounds(const string& word, int row, int col, unsigned int currentPos){
    if(board.inBounds(row, col) && visited.get(row, col) != 'O'){
        return backtrackingUserWord(board.get(row, col), word, row, col, currentPos+1);
    }
}



// Backtracking algorithm (all words)

void Boggle::findAllWords(set<string>& allWords) {
    computerPoints = 0;
    allWords.clear();
    for(int row = 0; row < board.numRows(); row++){
         for(int col = 0; col < board.numCols(); col++){
             string prefix = "";
             prefix += board.get(row, col);
             backtrackingAllWords(row, col, prefix, allWords);
            }
        }
    }



void Boggle::backtrackingAllWords(int row, int col, string& prefix, set<string>& allWords){

    if(lexicon.containsPrefix(prefix)){
        if(prefix.length() > 3 && lexicon.contains(prefix) && allWords.find(prefix) == allWords.end() && usedWords.find(prefix) == usedWords.end()){
            computerPoints += (prefix.length() - 3);
            allWords.insert(prefix);
        }
        visited.set(row,col,'O');
        for(int i = -1 ; i < 2 ; i++){
            for(int j = -1 ; j < 2 ; j++){
                if(!(j == 0 && i == 0)){
                    (checkInBounds2(row+i, col+j, prefix, allWords));
                }
            }
        }
        visited.set(row, col, 'X');

    }
    prefix.pop_back();
}

void Boggle::checkInBounds2(int row, int col, string& prefix, set<string>& allWords){
    if(board.inBounds(row, col) && visited.get(row, col) != 'O'){

        backtrackingAllWords(row, col, prefix += board.get(row, col), allWords);
    }
}






// Miscellaneous

void Boggle::setUserPoints(){
    userPoints = 0;
}

void Boggle::setUserWords(){
    usedWords.clear();
}


set<string> Boggle::getUsedWords() const{
    return usedWords;
}

int Boggle::getUserPoints() const {
    return userPoints;
}

int Boggle::getComputerPoints() const{
    return computerPoints;
}

