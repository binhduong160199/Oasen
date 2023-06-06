//
// Created by Binh Duong Nguyen on 07.03.23.
//

#ifndef PROJEKT1_GENERATE_H
#define PROJEKT1_GENERATE_H
#include <stdio.h>
#include "field.h"
#include <time.h>
#include <stdlib.h>
#include "character.h"

int countRelict(int array[5][5]){
    int sum = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(array[i][j] == relict){
                sum++;
            }
        }
    }
    return sum;
}

//Field
int c;// all relict in  game
void generateField(int array[5][5], int yPosition, int xPosition){
    int chance;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            chance = rand()%100;
            if (chance <= 40) {
                array[i][j] = empty;
            } else if (chance <= 80 ) {
                array[i][j] = danger;
            } else if (chance <= 90 ) {
                array[i][j] = fountain;
            } else {
                array[i][j] = relict;
            }
        }
    }
    for(int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == yPosition && j == xPosition) {
                printf("🤖 ");
            } else if (array[i][j] == empty) {
                printf("☘️ ");
            } else if (array[i][j] == danger) {
                printf("🕸️ ");
            } else if (array[i][j] == fountain) {
                printf("🦋 ");
            } else if (array[i][j] == relict) {
                printf("👑 ");
            }
        }
        printf("\n");
    }
    c = countRelict(array); //all relict in game
}
#endif //PROJEKT1_GENERATE_H
