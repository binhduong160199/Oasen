#include <iostream>
#include "character.h"
#include "generate.h"

using namespace std;

int main() {
    // for Player
    Character Robot;
    Robot.position.y = rand()%4;
    Robot.position.x = rand()%4;

    // for enemy
    Character Enemy;
    Enemy.position.y = rand()%4;
    Enemy.position.x = rand()%4;

    //Stats
    stats stat;

    int array[5][5];
    char a; // u, d, l or r

    // field generate
    cout << "\n****** WELCOME TO MY GAME ******\n" << endl;
    int t = 1;
    // 0 is y, 1 is x
    while(t){
        Robot.position.x = 0;
        Robot.position.y = 0;

        cout << "----------------\n" << endl;

        if(Robot.getNumLives() == 0) {
            cout << "\nTry it next time. You are dead" << endl;
            t = 0;
        }else{
            generateField(array, Robot.position.y, Robot.position.x);
        }

        // in game
        while(Robot.getNumLives() > 0){
            cout << "\nWhere do you want to go (u/l/d/r): \n" << endl;
            cin >> a;
            Robot.movePlayer(a, &Robot, array, &Enemy, &stat);
            // if player took all the point, we would end the game
            if(Robot.getRelict() == c){
                printf("You win!\n");
                stat.printStat(&stat);
                cout << "***********\n" << endl;
                c = 0;
                break;
            }
        }
    }
}