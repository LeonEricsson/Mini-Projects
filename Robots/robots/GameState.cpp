/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>

using namespace std;

GameState::GameState(){}

GameState::GameState(int numberOfRobots) {
    //for(size_t i = 0 ; i < robots.size(); i++){
      //  delete robots[i];
    //}
    robots.clear();
    for (int i = 0; i < numberOfRobots; i++) {
        int count = 0;
        Robot robot;
        do
        {
            robot = Robot();
        } while (!isEmpty (robot));
        robots.push_back(new Robot(robot));
    }
    teleportHero();

}

GameState::~GameState(){
    for(size_t i = 0 ; i < robots.size() ; i++){
        delete robots[i];
    }
   robots.clear();
}

GameState::GameState(const GameState& other){
    copyOther(other);
}

GameState& GameState::operator=(const GameState& other){
    if(this != &other){
        for(size_t i = 0 ; i < robots.size() ; i++){
            delete robots[i];
        }
       robots.clear();
       copyOther(other);
    }
    return *this;

}

void GameState::copyOther(const GameState &other){
    hero = other.hero;
    for(int i = 0; i < other.robots.size() ; i++){
        if(other.robots[i]->isJunk()){
            robots.push_back(new Junk(*other.robots[i]));
        }
        else{
            robots.push_back(new Robot(*other.robots[i]));
    }
  }
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    cout << robots.size() << endl;
    for (size_t i = 0; i < robots.size(); ++i)
        robots[i]->draw(scene);
    hero.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for (unsigned int i = 0; i < robots.size(); i++)
        if(!robots[i]->isJunk()){
        robots[i]->moveTowards (hero);
        }
}

int GameState::countCollisions() {
    int numberDestroyed = 0;
    unsigned int i = 0;
    while (i < robots.size()) {
        if(!robots[i]->isJunk()){
           if(countRobotsAt(*robots[i]) > 1){
               Robot* robot = robots[i];
               Junk* junk = new Junk(*robots[i]);
               robots[i] = junk;
               delete robot;
               numberDestroyed++;
           }
        }
        i++;
    }
    return numberDestroyed;
}

bool GameState::anyRobotsLeft() const {
    int robotsAlive = 0;
    for(size_t i = 0 ; i <robots.size() ; i++){
        if(!robots[i]->isJunk()){
            robotsAlive++;
        }
    }
    return(robotsAlive != 0);
}

bool GameState::heroDead() const {
    return !isEmpty(hero);
}

bool GameState::isSafe(const Unit& unit) const {
    for (unsigned int i = 0; i < robots.size(); i++){
        if(!robots[i]->isJunk()){
            if (robots[i]->attacks(unit)) return false;
        }
        else {
            if(robots[i]->at(unit)) return false;
        }
    }
    return true;
}



void GameState::moveHeroTowards(const Unit& dir) {
    hero.moveTowards(dir);
}

Hero GameState::getHero() const {return hero;}

/*
 * Free of robots and junk only
 */
bool GameState::isEmpty(const Unit& unit) const {
    for(size_t i = 0; i < robots.size() ; i++){
        if(robots[i]->at(unit)) return false;
    }
    return true;
}

/*
 * How many robots are there at unit?
 */
int GameState::countRobotsAt(const Unit& unit) const {
    int count = 0;
    for (size_t i = 0; i < robots.size(); ++i) {
        if (robots[i]->at(unit))
            count++;
    }
    return count;
}
