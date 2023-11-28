#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"

using namespace std;

class Player;
class objPosArrayList;

class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;

        bool exitFlag;
        bool loseFlag;
        
        int boardSizeX;
        int boardSizeY;

        int score;

        char** board;

        objPos foodPos;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        
        bool getExitFlagStatus();
        void setExitTrue();

        bool getLoseFlagStatus();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        int getScore();
        void incrementScore();

        // For board display I/O
        void drawBoard(Player *player);
        void printBoard();

        // For the food items
        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);      

};

#endif