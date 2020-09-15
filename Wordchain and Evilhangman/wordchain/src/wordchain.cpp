//Finds the shorthest way from a word to another, by changing one letter at a time.
//Vi diskuterade med handledaren som var här att vi kanske skulle abstraherat koden
// lite bättre, så som vi gjort i evil hangman
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>
#include <set>
#include <chrono>
#include <unistd.h>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

// Method to print the word chain when program has finished
void showstack(stack<string>& words)
{
    while (!words.empty())
    {
        cout << words.top() << " ";
        words.pop();
    }
    cout << endl;
}

//Word chain creating method that creates the chains by creating a que of stacks
// and exploring different chains in each stack untill it finds the shortest correct chain.
void wordChain(const string& w1,const string& w2){
    ifstream myFile;
    queue<stack<string>> wordQueue;
    stack<string> stack1;
    stack<string> tempStack;
    string mainWord;
    set<string> usedWords;
    set<string> dictionary;
    string str;
    auto start = chrono::steady_clock::now();
    myFile.open("dictionary.txt");
    while(getline(myFile, str)){
        dictionary.insert(str);
    }
    myFile.close();
    usedWords.insert(w1);
    stack1.push(w1);
    wordQueue.push(stack1);
    while(!wordQueue.empty()){
        tempStack = wordQueue.front();
        wordQueue.pop();
        mainWord = tempStack.top();
        if(mainWord == w2){
            cout << "Chain from " << w2 << " back to " << w1 << ": " << endl;
            showstack(tempStack);
            wordQueue = {};
            auto end = chrono::steady_clock::now();
            cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << "ms" << endl;
            cout << endl;
        }
        else{
            for(int i=0 ; i < mainWord.size() ; i++){
                string tempWord = mainWord;
                for(int j=0 ; j < ALPHABET.size() ; j++){
                    string letter;
                    letter = ALPHABET[j];
                    tempWord.replace(i, 1, letter);
                    if(dictionary.find(tempWord) != dictionary.end()){
                        if(usedWords.find(tempWord) == usedWords.end()){
                            stack<string> newStack = tempStack;
                            newStack.push(tempWord);
                            wordQueue.push(newStack);
                            usedWords.insert(tempWord);
                        }
                    }

                }
            }

        }

    }
}

int main() {
    string word1, word2;
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";
    cin >> word1 >> word2;
    wordChain(word1, word2);

    // TODO: Finish the program!
    cout << "Have a nice day" << endl;
    return 0;
}
