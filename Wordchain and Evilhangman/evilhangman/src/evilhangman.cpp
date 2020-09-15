#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

int main();

// Retrieve amount of guesses remaining
void getGuesses(int& amountOfGuesses){
    cout << "Enter the amount of guesses: ";
    cin >> amountOfGuesses;
    if(amountOfGuesses < 1){
        getGuesses(amountOfGuesses);
    }
}

// Asking user if they want to see remaining words while playing
void seeWordsLeft(bool& seeWords){
    char yesNo;

    cout << "Would you like to see the remaining words (y/n): ";
    cin >> yesNo;
    if(yesNo == 'y'){
        seeWords = true;
    }
    else if (yesNo == 'n'){
        seeWords = false;
    }
    else{
        seeWordsLeft(seeWords);
    }
}

// Main method asking user for initial settings such as wordlength and amount of guesses
void askUser( const unordered_map<string, int>& dictionary, int& amountOfGuesses, bool& seeWords, vector<string>& remainingWords){
        int wordLength = 100;
        bool wordLengthOK = false;
        cout << "Enter word length: ";
        cin >> wordLength;
        for(auto it = dictionary.begin() ; it != dictionary.end() ; it++){
            if(it->second == wordLength){
                wordLengthOK = true;
                remainingWords.push_back(it->first);
            }
    }
        if(!wordLengthOK){
            askUser(dictionary, amountOfGuesses, seeWords, remainingWords);
        }
        getGuesses(amountOfGuesses);
        seeWordsLeft(seeWords);
}

// Method used to print current game info in between guesses
void printInfo(const int& amountOfguesses, const string& word, const bool& seeWord, const vector<string>& remainingWords, const string& guessedLetters){
    cout << "Your word: " << word << endl;
    cout << "Guesses left: " << amountOfguesses << endl;
    cout << "Used letters: " << guessedLetters << endl;
    if(seeWord){
        cout << "Words left: " << remainingWords.size() << endl;
    }


}

/* Method that handles the guessing letter part of the program. First we check if the letter is valid,
 * then we partition the words in the dictionary into different combinations in relation to the guessed letter.
 * We then pick the largets partition as our new remainingWords and continue the game.
 *
 */
void guessLetter(string& guessedLetters, vector<string>& remainingWords, string& word, int& amountOfGuesses){
    string letter;
    string tempWord;

    cout << "Please guess a letter: ";
    cin >> letter;

    if(!(letter.length() == 1) || (ALPHABET.find(letter) == ALPHABET.npos) || (guessedLetters.find(letter) != guessedLetters.npos)){
        guessLetter(guessedLetters, remainingWords, word, amountOfGuesses);
    }
    unordered_map<string, vector<string>> myMap;
    for(string word : remainingWords){
        string key;
        for(auto it = word.begin() ; it != word.end() ; it++){
            if(*it != letter.at(0)){
               key += "-";
            }
            else{
               key += letter;
            }
        }
        if(myMap.count(key) == 0){
           vector<string> str;
           myMap.insert(pair<string, vector<string>>(key,str));
           myMap.find(key)->second.push_back(word);
        }
        else{
          myMap.find(key)->second.push_back(word);
        }
    }
    int max = 0;
    vector<string> largestPartition;
    string newWord;
    for(auto it = myMap.begin() ; it != myMap.end() ; it++){
        if(it->second.size() > max){
            max = it->second.size();
            largestPartition = it->second;
            newWord = it->first;
        }
    }
    remainingWords = largestPartition;
    guessedLetters += letter;
    tempWord = word;
    for(int i = 0 ; i < word.size() ; i++){
        if(word[i] == '-'){
            word[i] = newWord[i];
        }
    }
    if(tempWord == word){
        amountOfGuesses--;
    }
}


// The method that runs the game, it calls all the needed functions and checks if the game is over
int game(vector<string>& remainingWords, int& amountOfGuesses, const bool& seeWords, string& guessedLetters, string& word){
    guessLetter(guessedLetters, remainingWords, word, amountOfGuesses);
    printInfo(amountOfGuesses, word, seeWords, remainingWords, guessedLetters);
    if(amountOfGuesses != 0 ){
        if(word.find("-") != word.npos){
            game(remainingWords, amountOfGuesses, seeWords, guessedLetters, word);
        }
        else{
            cout << "Congratulations, you won!" << endl;
        }

    }
    else {

        cout << "You are out of guesses, game over." << endl;
        cout << "The correct word was:" << remainingWords.at(0) << endl;
    }
    char yesNo;
    cout << "Would you like to play again? (y/n) ";
    cin >> yesNo;
    if(yesNo == 'y'){
        main();
    }
    if(yesNo == 'n'){
        return 0;
    }

}

// This is the pregame method that sets up some necessary info.
void preGame(vector<string>& remainingWords, int& amountOfGuesses, const bool& seeWords){
    string word;
    string guessedLetters;

    for(int i = 0 ; i < remainingWords.at(0).length() ; i++){
        word += "-";
    }

    printInfo(amountOfGuesses, word, seeWords, remainingWords, guessedLetters);
    game(remainingWords, amountOfGuesses, seeWords, guessedLetters, word);
}




int main() {
    int amountOfGuesses;
    bool seeWords;
    vector<string> remainingWords;
    cout << "Welcome to Hangman." << endl;
    ifstream myFile;
    unordered_map<string, int> dictionary;
    string  str;
    myFile.open("di.txt");
    while(getline(myFile, str)){
        dictionary.insert(pair<string, int>(str, str.length()));
    }
    myFile.close();
    askUser(dictionary, amountOfGuesses, seeWords, remainingWords);
    preGame(remainingWords, amountOfGuesses, seeWords);
    return 0;
}
