
#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <grid.h>
#include "lexicon.h"
#include <set>


using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    Grid<char> board;


    Boggle();

    // Create the starting board with predetermined letters or randomized cubes
    void setUpBoard(const bool& yesOrNo, const string& letters="");

    // Create the cubes with the listed sides as well as shuffling them
    vector<vector<char>> createCubes() const;

    // Fill the board with the desired shuffled cubes and then shuffle the board
    void fillAndShuffleBoard(const vector<vector<char>>& cubes);

    // Checks if the user entered word is valid length
    bool isValidWordLength(const string& word) const;

    // Checks if the user entered word exists
    bool isValidWord(const string& word) const;

    // Checks if the user entered word has not been entered before
    bool isValidUniqueWord(const string& word) const;

    // Checks if user entered board is valid
    bool isValidBoard(const string& letters, bool& checkFalse) const;

    // Call backtracking algorithm on all valid letters in grid
    bool findUserWord(const string& word);

    // Backtracking algorithm to determine if user entered word can be found
    bool backtrackingUserWord(char currentLetter,const string& word, int row, int col, unsigned int currentPos=0);

    // Helping function #1 to reduce repetitiveness
    bool checkInBounds(const string& word, int row, int col, unsigned int currentPos);

    // Call backtracking algorithm to find all words
    void findAllWords(set<string>& allWords);

    // Backtracking algorithm to find all the words on the board
    void backtrackingAllWords(int row, int col, string& prefix, set<string>& allWords);

    //Helping function #2 to reduce repetitiveness
    void checkInBounds2(int row, int col, string& prefix, set<string>& allWords);

    // User points setter
    void setUserPoints();

    // User words setter
    void setUserWords();

    // User points getter
    int getUserPoints() const;

    // Computer points getter
    int getComputerPoints() const;

    // Used words getter
    set<string> getUsedWords() const;

private:

    Lexicon lexicon = Lexicon("EnglishWords.dat");
    int userPoints;
    int computerPoints;
    set<string> usedWords;
    Grid<char> visited;


};

#endif
