#ifndef PLAYER_H
#define PLAYER_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Food.h"

class GameMechs;
class objPosArrayList;
class Food;

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos();
        void updatePlayerDir();
        void movePlayer(Food* food);
        bool checkFoodConsumption(Food* food, char &foodType);
        bool checkSelfCollision();
        void turnAround();

    private:
        objPosArrayList* playerPosList;       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif