//
// Created by Binh Duong Nguyen on 07.03.23.
//

#include <iostream>
#include "character.h"
#include "field.h"
#include "stats.h"
using namespace std;

Character::Character() {
    position = {.x = 0, .y = 0};
    numLives = 5;
    numPoints = 0;
    relictTaken = 0;
}

int Character::getNumLives() {
    return numLives;
}

int Character::getNumPoints() {
    return numPoints;
}

int Character::getRelict() {
    return relictTaken;
}

void Character::printMap(int array[5][5], int yPosition, int xPosition, int yEnemyPosition, int xEnemyPosition) {
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(i == yPosition && j == xPosition){
                array[i][j] = '@';
            }
            if(array[i][j] == '@'){
                if(i != yPosition || j != xPosition ){
                    array[i][j] = empty;
                }
            }

            if(i == yPosition && j == xPosition) {
                printf("🤖 ");
            }else if (i == yEnemyPosition && j == xEnemyPosition){
                printf("🤡 ");
            }else if(array[i][j] == empty){
                printf("☘️ ");
            }else if(array[i][j] == danger){
                printf("🕸️ ");
            }else if(array[i][j] == fountain){
                printf("🦋 ");
            }else if(array[i][j] == relict){
                printf("👑 ");
            }
        }
        printf("\n");
    }
}

void Character::printStat(int live, int point) {
    cout << "\nYour live: " << live <<endl;
    cout << "\nYour point: " << point <<endl;
}

// function for small game

int Character::getGameForDanger() {
    int chance = rand() % 2;
    int number;
    cin >> number;
    if(number == chance){
        return 1;
    }
    return 0;
}

int Character::getGameForFountain() {
    int chance = rand() % 3;
    char answer;
    cin >> answer;
    // rock is 1, paper is 2, scissor is 3
    // rock : r, paper: p, scissor: s
    switch (answer) {
        case 'r':
            if(chance == 1){
                return 1;
            }else if(chance == 3){
                return 1;
            }else{
                return 0;
            }
        case 'p':
            if(chance == 1){
                return 1;
            }else if(chance == 2){
                return 1;
            }else{
                return 0;
            }
        case 's':
            if(chance == 2){
                return 1;
            }else if(chance == 3){
                return 1;
            }else{
                return 0;
            }
    }
    return 0;
}

int Character::getGameForRelict() {
    int chance = rand() % 2;
    int answer;
    cin >> answer;
    if(answer == chance){
        return 1;
    }else{
        return 0;
    }
}

void Character::countRelictAndLife(int array[5][5], int yPosition, int xPosition, Character *Robot, Character *Enemy, stats *stat) {
    if(array[yPosition][xPosition] == danger){
        cout << "\nLet's guess a number 1 or 2" << endl;
        cout << "\nIf your answer is wrong, u lost 1 life" << endl;
        if(!Robot->getGameForDanger()){
            cout << "\nYou lost one life" << endl;
            Robot->numLives--;
            stat->liveLost++;
            printStat(Robot->getNumLives(), Robot->getNumPoints());
        }else{
            cout << "\nYou are lucky" << endl;
            printStat(Robot->getNumLives(), Robot->getNumPoints());
        }
    }else if(array[Robot->position.y][Robot->position.x] == fountain){
        cout << "\nLet's play (Rock:r, Paper:p, Scissor: s)" << endl;
        cout << "\nYou won't get point if you lose: " << endl;
        if(!Robot->getGameForFountain()){
            cout << "\nYou don't get any thing" << endl;
            printStat(Robot->getNumLives(), Robot->getNumPoints());
        }else {
            cout << "\nYou are lucky" << endl;
            Robot->numLives++;
            stat->liveTaken++;
            printStat(Robot->getNumLives(), Robot->getNumPoints());
        }
    }
    else if(array[Robot->position.y][Robot->position.x] == relict){
        cout << "\nYou have a chance to win 2 point" << endl;
        cout << "\n1 is Yes and 2 is No" << endl;
        if(!Robot->getGameForRelict()){
            cout << "\nUnlucky my friend" << endl;
            Robot->numPoints++;
            Robot->relictTaken++;
            stat->relict++;
            printStat(Robot->getNumLives(), Robot->getNumPoints());
        }else{
            cout << "\nYou are lucky this time" << endl;
            Robot->numPoints++;
            Robot->numPoints++;
            Robot->relictTaken++;
            stat->relict++;
            printStat(Robot->getNumLives(), Robot->getNumPoints());
        }
    } else if (Robot->position.y == Enemy->position.y && Robot->position.x == Enemy->position.x) {
        Robot->numLives--;
        stat->interactionEnemy++;
        stat->liveLost++;
    }
    printMap(array, Robot->position.y, Robot->position.x, Enemy->position.y, Enemy->position.x);
}

int checkToMove(int yPosition, int xPosition){
    if(xPosition < 0 || xPosition > 4){
        return 0;
    }else if(yPosition < 0 || yPosition > 4){
        return 0;
    }else{
        return 1;
    }
}

void Character::moveEnemy(Character *Enemy, int yPosition, int xPosition) {
    int dy = yPosition - Enemy->position.y;
    int dx = xPosition - Enemy->position.x;
    if (abs(dy) > abs(dx)) {
        if (dy > 0) {
            Enemy->position.y++;
        } else if (dy < 0) {
            Enemy->position.y--;
        }
    } else {
        if (dx > 0) {
            Enemy->position.x++;
        } else if (dx < 0) {
            Enemy->position.x--;
        }
    }
}

void stats::printStat(stats *stat) {
    printf("\nStats:");
    printf("\nDamaged taken: %d", stat->liveLost);
    printf("\nLives taken: %d", stat->liveTaken);
    printf("\nRelicts found: %d", stat->relict);
    printf("\nInteraction with enemy: %d\n", stat->interactionEnemy);
    stat->relict = 0;
    stat->liveLost = 0;
    stat->liveTaken = 0;
    stat->interactionEnemy = 0;
}

void Character::movePlayer(char a, Character *Robot, int array[5][5], Character *Enemy, stats *stat) {
    switch(a){
        case 'u':
            Robot->position.y--;
            if(!checkToMove(Robot->position.y, Robot->position.x)){
                cout << "\nInvalid move" << endl;
                Robot->position.y++;
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }else{
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }
            moveEnemy(Enemy, Robot->position.y, Robot->position.x);
            break;
        case 'd':
            Robot->position.y++;
            if(!checkToMove(Robot->position.y, Robot->position.x)){
                cout << "\nInvalid move" << endl;
                Robot->position.y--;
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }else{
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }
            moveEnemy(Enemy, Robot->position.y, Robot->position.x);
            break;
        case 'r':
            Robot->position.x++;
            if(!checkToMove(Robot->position.y, Robot->position.x)){
                cout << "\nInvalid move" << endl;
                Robot->position.x--;
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            } else {
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }
            moveEnemy(Enemy, Robot->position.y, Robot->position.x);
            break;
        case 'l':
            Robot->position.x--;
            if(!checkToMove(Robot->position.y, Robot->position.x)){
                cout << "\nInvalid move" << endl;
                Robot->position.x++;
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }else{
                countRelictAndLife(array, Robot->position.y, Robot->position.x, Robot, Enemy, &*stat);
            }
            moveEnemy(Enemy, Robot->position.y, Robot->position.x);
            break;
        default:
            cout << "\nInvalid" << endl;
    }
}