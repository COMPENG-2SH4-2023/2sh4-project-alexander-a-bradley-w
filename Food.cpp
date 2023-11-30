#include "Food.h"

Food::Food()
{
    // Initializing empty foodPos; an object that doesn't exist in the board 
    foodPos.setObjPos(0, 0, '\0'); // null since no food
    myPlayer = NULL;
    myGM = NULL;
}

Food::Food(Player* player, GameMechs* GM)
{
    foodPos.setObjPos(0, 0, '\0');  // Null object just as before
    myPlayer = player;
    myGM = GM;
}

Food::~Food()
{
    // Nothing on heap right now
}


void Food::generateFood()
{
    int xCoord;
    int yCoord;
    bool overlap; // flag for if the generated coordinates overlap the player
    objPos tempPos;
    objPosArrayList* playerPosList;

    // extract the player position list
    playerPosList = myPlayer->getPlayerPos();

    do{
        overlap = false; // defaulting to no overlap

        xCoord = (rand() % (myGM->getBoardSizeX()-2)) + 1; // values from 1 to boardSizeX-2
        // Example
        // boardSizeX = 10
        // All indexes: 0 1 2 3 4 5 6 7 8 9 (10 for null character '\0')
        // Valide indexes for position: 1 2 3 4 5 6 7 8 (i.e., not the boarder ones)
        
        yCoord = (rand() % (myGM->getBoardSizeY()-2)) + 1;
        // Example
        // boardSizeY = 5
        // All indexes: 0 1 2 3 4
        // Valide indexes for position: 1 2 3 (i.e., not the boarder ones)

        // Set the food to those coordinates
        foodPos.setObjPos(xCoord, yCoord, 'o');

        // Checking if overlapping with player
        // extract the player position list
        playerPosList = myPlayer->getPlayerPos();

        // Loop through the array and add in all the elements
        for(int index=0; index<(playerPosList->getSize()); index++)
        {
            playerPosList->getElement(tempPos,index); // saving the object at the index to a temporary objPos instance

            if(foodPos.isPosEqual(&tempPos)) // if any part of the snake overlaps, flag it
            {
                overlap = true;
                break;
            } 
        }

    }while(overlap);
    // Returns true if player and food have equal coordinates, such that loop keeps running until food is generated at unique position
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}
