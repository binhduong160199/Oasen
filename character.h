//
// Created by Binh Duong Nguyen on 07.03.23.
//

#ifndef PROJEKT1_CHARACTER_H
#define PROJEKT1_CHARACTER_H
#include "position.h"
#include "stats.h"

class Character {
public:
    Character();
    position position;
    void countRelictAndLife(int array[5][5], int yPosition, int xPosition, Character *Robot, Character *Enemy, stats *stat);
    void printMap(int array[5][5], int yPosition, int xPosition, int yEnemyPosition, int xEnemyPosition);
    void printStat(int live, int point);
    void movePlayer(char a, Character *Robot, int array[5][5], Character *Enemy, stats *stat);
    void moveEnemy(Character *Enemy, int yPosition, int xPosition);

    //get function
    int getNumLives();
    int getNumPoints();
    int getRelict();

    //level 2
    int getGameForDanger();
    int getGameForFountain();
    int getGameForRelict();

private:
    int numLives;
    int numPoints;
    int relictTaken;
};


#endif