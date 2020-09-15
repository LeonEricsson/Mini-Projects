//Game of life
//Adam Hjalmarsson adahj913
//Leon Ericsson leoer843
//This file is a game called "Game of life" where the growth of
//bacterias depends on their neighbours
#include <iostream>
#include <fstream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <vector>

using namespace std;
//Printing out the message in the beginning
void welcomeMessage(){
    cout << "Welcome to the TDDD86 Game of Life, " << endl;
    cout << "a simulation of the lifecycle of a bacteria colony. " << endl;
    cout << "Cells (X) live and die by the following rules: " << endl;
    cout << "- A cell with 1 or fewer neighbours dies. " << endl;
    cout << "- Locations with 2 neighbours remain stable. " << endl;
    cout << "- Locations with 3 neighbours will create life. " << endl;
    cout << "- A cell with 4 or more neighbours dies. " << endl;
    cout << endl;
}

//Creating a grid
void createGrid(int rows, int cols, Grid<char>& myGrid){
    string name;
    ifstream myFile;
    string str;
    cout << "Grid input file name? ";
    cin >> name;
    myFile.open(name);
    myFile >> rows >> cols;
    getline(myFile, str);
    myGrid.resize(rows, cols);
    for(int i=0; i<rows; i++){
       getline(myFile, str);
       for(int j = 0; j<str.size(); j++){
           myGrid.set(i, j, str[j]);
       }
    }
}
//Printing out the grid in it's current state
void printGrid(Grid<char> const & myGrid){
    for(int row = 0; row < myGrid.numRows(); row++){
        for(int col = 0; col < myGrid.numCols(); col++){
            cout << myGrid.get(row, col);
        }
        cout << endl;
    }
}
//Checking how many neighbours every point has
int checkNeigbours(int row, int col, Grid<char>const & myGrid){
    int neighbours = 0;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(myGrid.inBounds(row+i, col+j) && !(j==0 && i==0)){
                if(myGrid.get(row+i, col+j) == 'X'){
                    neighbours += 1;
                }
            }
        }
    }
    return neighbours;

}
//Checking if there are a bacteria or not in every point and, with the help of
// checkNeighbours adding changes to a vector
void checkBacteria(Grid<char>const& myGrid, vector<pair<int, int>>& changes){
    for(int row = 0; row < myGrid.numRows(); row++){
        for(int col = 0; col < myGrid.numCols(); col++){
           if(myGrid.get(row,col) == 'X'){
               if(!(checkNeigbours(row, col, myGrid) == 2) && !(checkNeigbours(row, col, myGrid) == 3)){
                    changes.push_back(make_pair(row, col));

               }
            }
            else{
               if(checkNeigbours(row, col, myGrid) == 3){
                   changes.push_back(make_pair(row, col));
               }
            }
        }
    }
}
//Updating the grid
void updateGrid(Grid<char>& myGrid, vector<pair<int, int>>& changes){
    for(int i = 0; i<changes.size(); i++){
        if((myGrid.get(changes[i].first, changes[i].second)) == 'X'){
            myGrid.set(changes[i].first, changes[i].second, '-');
        }
        else{
            myGrid.set(changes[i].first, changes[i].second, 'X');
        }

    }
    changes.clear();
    printGrid(myGrid);
}


void nextStep(Grid<char>& myGrid, vector<pair<int, int>>& changes);
//Ticks one generation
void tick(Grid<char>& myGrid, vector<pair<int, int>>& changes){
    checkBacteria(myGrid, changes);
    updateGrid(myGrid, changes);
    nextStep(myGrid, changes);
}
//Ticks multiple generations
void animate(Grid<char>& myGrid, vector<pair<int, int>>& changes){
    while(true){
    checkBacteria(myGrid, changes);
    updateGrid(myGrid, changes);
    pause(100);
    }
}
//Gives the user the choice to choose what he wants to do
void nextStep(Grid<char>& myGrid, vector<pair<int, int>>& changes){
    char toDo;
    cout << "a)nimate, t)ick, q)uit ";
    cin >> toDo;
    switch(toDo){
        case 'q' : break;

        case 't' : tick(myGrid, changes);
                 break;
        case 'a' : animate(myGrid, changes);
                 break;
    }




}

int main() {
    vector<pair<int, int>> changes;
    int rows, cols;
    welcomeMessage();
    Grid<char> myGrid;
    createGrid(rows, cols, myGrid);
    printGrid(myGrid);
    nextStep(myGrid, changes);

    std::cout << "Have a nice Life! "  << std::endl;
    return 0;
}
