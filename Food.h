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
        objPosArrayList* getFoodPos();
        
        Food();
        ~Food();
        Food(Player* player, GameMechs* GM, int num);

        // Getter
        int getAmountToGenerate();

    private:
        objPosArrayList* foodBucket;

        Player* myPlayer;
        GameMechs* myGM;
        int amountToGenerate;

};

#endif