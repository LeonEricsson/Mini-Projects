/*
 * TDDD86 TSP
 * This file contains the decleration of the tour class.
 * See tour.cpp for the implementation of the functions.
 */
#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    // The tour constructor initializes the pointer to the first Node
    Tour();

    // The destructor traverses the linked list and deletes the elements
    ~Tour();

     // Prints the points in the order of the linked list
    void show();

    // Draws the points on the scene in the order of the linked list
    void draw(QGraphicsScene* scene);

    // Returns the size of the circular linked list
    int size();

    // Returns the total distance of the tour
    double distance();

    // Nearest insertion heuristic which inserts the points in nearest order
    void insertNearest(Point p);

    // Smallest insertion heuristic which inserts the points in a way that increases
    // the total distance by the smallest amount.
    void insertSmallest(Point p);

private:
    Node* current = nullptr; //Pointer to the current node, nullptr by default
    int size = 0;
};

#endif // TOUR_H
