
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "lexicon.h"
#include <set>


/*
 * Plays one game of Boggle using the given boggle game state object.
 */

void printBoard(const Boggle& boggle){
    for(int row = 0; row < boggle.board.numRows(); row++){
            for(int col = 0; col < boggle.board.numCols(); col++){
                cout << boggle.board.get(row, col);
            }
            cout << endl;
        }
}

string getLetters(const Boggle& boggle){
    bool checkFalse = false;
    string letters;
    while(!checkFalse){
    checkFalse = true;
    cout << "Please enter the string for your custom board: " << endl;
    getline(cin, letters);
    boggle.isValidBoard(letters, checkFalse);
  }
  return letters;
}

static void toUpperCaseInPlace(string& str) {
   int nChars = str.length();
   for (int i = 0; i < nChars; i++) {
      str[i] = toupper(str[i]);
   }
}


bool getWord(string& word, const Boggle& boggle){
    bool checkFalse;
    while(!checkFalse){
            cout << "Type a word (or press Enter to end your turn): ";
            getline(cin, word);
            cout << "hello" << endl;
            toUpperCaseInPlace(word);
            if(word.empty()) return false;

            checkFalse = true;
            if(boggle.isValidWordLength(word)) {
                cout << "Please enter a word with atleast 4 letters" << endl;
                checkFalse = false;
            }
            if(!boggle.isValidWord(word)){
                cout << "Word does not exist!" << endl;
                checkFalse = false;
            }
            if(!boggle.isValidUniqueWord(word)){
                cout << "This word has already been found" << endl;
                checkFalse = false;
            }
        }
    return true;



}

void printInfo(const Boggle& boggle){
    cout << "It's your turn!" << endl;
    printBoard(boggle);
    cout << endl;
    cout << "Your words (" << boggle.getUserPoints() << "): {";
    for(string word : boggle.getUsedWords()){
        cout << word + ", ";
    }
    cout << "}" << endl;


}


void userTurn(Boggle& boggle){
    string word;
    boggle.setUserPoints();
    boggle.setUserWords();
    printInfo(boggle);
    while(getWord(word, boggle)){
        clearConsole();
        if(boggle.findUserWord(word)){
            cout << "You found a new word! " << "'" << word << "'" << endl;
        }
        else {
           cout << "This is not a word on the board" << endl;
        }
        printInfo(boggle);
    }

}


void computerTurn(Boggle& boggle){
    set<string> allWords;
    clearConsole();
    cout << endl;
    cout << "It's my turn!" << endl;
    boggle.findAllWords(allWords);
    cout << "My words (" << allWords.size() << "): {";
    for(string word : allWords){
        cout << word + ", ";
    }
    cout << "}" << endl;
    cout << endl;
    cout << "My score: " << boggle.getComputerPoints() << endl;
    if(boggle.getComputerPoints() > boggle.getUserPoints()){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
    else if (boggle.getComputerPoints() == boggle.getUserPoints()) {
       cout << "Wow, you managed to tie! Next time will be your doom human!" << endl;
    }
    else {
       cout << "You managed to beat me, congratulations. You are the superior being!" << endl;
    }

}

void playOneGame(Boggle& boggle) {
    if(yesOrNo("Do you want to generate a random board? ")) boggle.setUpBoard(true);
    else {
       boggle.setUpBoard(false, getLetters(boggle));
    }
    userTurn(boggle);
    computerTurn(boggle);

}





/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
