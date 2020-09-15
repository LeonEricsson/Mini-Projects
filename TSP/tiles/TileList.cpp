/*
 *  This file supplies the implementation of the functions
 * in the tile game by working around a array of Tiles, moving
 * them lower or higher in response to mouse clicks.
 */
//Methods used to play with a window of tiles

#include "TileList.h"
#include <vector>

TileList::TileList(){

}

TileList::~TileList()
{
    delete[] tileList;
}

void TileList::addTile(Tile tile){
    if(listSize == maxSize){
        maxSize = maxSize*2;
        Tile *tempList = new Tile[maxSize];
        copy(tileList, tileList+listSize, tempList);
        delete[] tileList;
        tileList = tempList;

    }
    tileList[listSize] = tile;
    listSize++;

}

void TileList::drawAll(QGraphicsScene* scene) const
{
    for(int i = 0; i < listSize ; i++){
        tileList[i].draw(scene);
    }
}

int TileList::indexOfTopTile(int x, int y) const{
    for(int i = listSize-1 ; i > -1 ; i--){
        if(tileList[i].contains(x, y)){
            return i;
        }
    }
    return -1;
}

void TileList::raise(int x, int y){
    bool found = false;
    int index;
    Tile tempTile = tileList[listSize-1];
    Tile tempTile2;
    for(int i = 0 ; i < listSize ; i++){
        if(tileList[i].contains(x,y)){
            found = true;
            index = i;
        }
    }
    if(found){
        for(int i = listSize-1 ; i > 0 ; i--){
            if(i != index){
              tempTile2 = tempTile;
              tempTile = tileList[i-1];
              tileList[i-1] = tempTile2;
              if(i == 1){
                  tileList[listSize-1] = tempTile;
              }
            }
            else{
                tileList[listSize-1] = tempTile;
                break;
            }
        }
    }
}

void TileList::lower(int x, int y){
    Tile tempTile;
    bool found = false;
    for(int i = listSize-1 ; i >0 ; i--){
        if(tileList[i].contains(x, y)|| found){
            if(!found){
                tempTile = tileList[i];
            }
            found = true;
            tileList[i] = tileList[i-1];
        }
    }
    if(found){
        tileList[0] = tempTile;
    }
  }


void TileList::remove(int x, int y){
    bool found = false;
    int index;
    Tile tempTile = tileList[listSize-1];
    Tile tempTile2;
    for(int i = 0 ; i < listSize ; i++){
        if(tileList[i].contains(x,y)){
            found = true;
            index = i;
        }
    }
    if(found){
        for(int i = listSize-1 ; i > 0 ; i--){
            if (i == index){
                break;
            }
            else{
              tempTile2 = tempTile;
              tempTile = tileList[i-1];
              tileList[i-1] = tempTile2;
            }
        }
        listSize--;
    }
}

void TileList::removeAll(int x, int y){
    for(int i = 0 ; i < listSize ; i++){
        if(tileList[i].contains(x, y)){
            if(i == listSize-1){
                listSize--;
            }
            else if(i == listSize-2){
                tileList[i] = tileList[i+1];
                listSize--;
                i--;
            }
            else{
                tileList[i] = tileList[i+1];
                for(int j = i+1; j < listSize-1 ; j++){
                    tileList[j] = tileList[j+1];
                }
                listSize--;
                i--;
            }
        }
    }
}
