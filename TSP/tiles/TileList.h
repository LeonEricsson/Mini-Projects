/*
 * The TileList class represents the games main functions
 * by storing the games Tiles in an array and manipulating
 * their positions in that array accordingly.
 */

#ifndef TILELIST_H
#define TILELIST_H

#include <QGraphicsScene>
#include "Tile.h"

class TileList {
public:

    // Constructs a TileList which is an array of, to begin with, 10 tiles.
    TileList();

    // Deletes the current array from the heap freeing up space.
    ~TileList();

    /* Adds a new tile to the end of the array, in the
     * case that the array is full the function creates
     * a new array, double the size of the current, and
     * copies the current array onto the new one.
     */
    void addTile(Tile tile);

    /*
     * Draws the tiles in the current array on to the QGraphicsScene
     * object in the correct order from bottom to top.
     */
    void drawAll(QGraphicsScene* scene) const;

    /*
     * Returns the index of the top(end of array) tile at the
     * specific x, y coordinate.
     */
    int indexOfTopTile(int x, int y) const;

    /*
     * If the given coordinates are covered by tile(s) this function
     * moves the top tile to the bottom of all the tiles / beginning of array.
     */
    void lower(int x, int y);

    /*
     * If the given coordinates are covered by tile(s) this function
     * moves the top tile to the top of all the tiles / end of array.
     */
    void raise(int x, int y);

    /*
     * If the given coordinates are covered by tile(s) this function
     * removes the top tile from the array.
     */
    void remove(int x, int y);

    /* If the given coordinates are covered by tile(s) this function
     * removes ALL these tiles from the array.
     */
    void removeAll(int x, int y);


private:

    Tile *tileList = new Tile[10];    //Pointer to the array of tiles
    int listSize = 0;      // Current size of the array
    int maxSize = 10;       // Max size of the array

};

#endif // TILELIST_H
