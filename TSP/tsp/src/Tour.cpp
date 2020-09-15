/*
 * TDDD86 TSP
 * This file contains the implementation of the Tour class
 * which is an implementation of the circular linked list
 * datatype. This linked list includes nodes with points.
 */

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"
#include <limits>

using namespace std;


Tour::Tour(){}

Tour::~Tour()
{
    int i = 0;
    for(i; i < size ; i++) {
        if(i == size - 1){
            delete current;
        }
        else{
           Node* temp = current;
           current = current->next;
           delete temp;
        }
    }
}


void Tour::show()
{
  for(int i = 0 ; i < size; i++){
      cout << current->point.toString() << endl;

      current = current->next;
  }

}

void Tour::draw(QGraphicsScene *scene)
{
   if(size > 1){
       for(int i = 0; i < size ; i++){
           current->point.drawTo(current->next->point, scene);
           current = current->next;
       }
   }
   else if(size == 1){
       current->point.draw(scene);
   }
}

int Tour::calculateSize()
{  
    int sizeCheck = 0;
    Node* start = current;
    if(current != nullptr){
        while(current->next != start){
            sizeCheck++;
            current = current->next;
        }
        sizeCheck++;

    }
    current = start;
    return sizeCheck;

}

double Tour::distance()
{   double totalDistance = 0;
    if(size > 1){
        for(int i = 0; i < size; i++){
            totalDistance += current->point.distanceTo(current->next->point);
            current = current->next;
         }
    }

    return totalDistance;
}

void Tour::insertNearest(Point p)
{
    double dist;
    double shortestDist = numeric_limits<double>::infinity();
    Node* shortestNode;
    if(size == 0){
       current = new Node(p, nullptr);
       current->next = current;
       size++;

    }
    else{
       for (int i = 0; i < size; i++){
           dist = current->point.distanceTo(p);
           if(dist < shortestDist){
               shortestNode = current;
               shortestDist = dist;
           }
           current = current->next;
       }
    Node* newNode = new Node(p, shortestNode->next);
    shortestNode->next = newNode;
    size++;
    }

}

void Tour::insertSmallest(Point p)
{
    double dist;
    double shortestDist = numeric_limits<double>::infinity();
    Node* shortestNode;
    if(size == 0){
       current = new Node(p, nullptr);
       current->next = current;
       size++;

    }
    else{
       for (int i = 0; i < size ; i++){
           dist = (current->point.distanceTo((p))+p.distanceTo(current->next->point))
                   - current->point.distanceTo(current->next->point);
           if(dist < shortestDist){
               shortestNode = current;
               shortestDist = dist;
           }
           current = current->next;
       }
    Node* newNode = new Node(p, shortestNode->next);
    shortestNode->next = newNode;
    size++;
    }

}
