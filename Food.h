#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

class GameMechs;
class objPosArrayList;
class Player;

class Food
{
    public:
        void generateFood();
        void getFoodPos(objPos &returnPos);
        
        Food();
        ~Food();
        Food(Player* player, GameMechs* GM);


    private:
        objPos foodPos;

        Player* myPlayer;
        GameMechs* myGM;

};

#endif