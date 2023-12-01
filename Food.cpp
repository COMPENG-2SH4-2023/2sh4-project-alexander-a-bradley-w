#include "Food.h"

Food::Food()
{
    // Initializing empty food buck on heap 
    foodBucket = new objPosArrayList();
    
    myPlayer = NULL;
    myGM = NULL;
    amountToGenerate = 1; // default to generating 1
}

Food::Food(Player* player, GameMechs* GM, int num)
{
    // Initializing empty food buck on heap 
    foodBucket = new objPosArrayList();

    myPlayer = player;
    myGM = GM;
    amountToGenerate = num;
}

Food::~Food()
{
    delete foodBucket;
    foodBucket = NULL;
}


void Food::generateFood()
{
    int xCoord;
    int yCoord;
    bool overlap; // flag for if the generated coordinates overlap the player
    objPos tempPos; // for comparison
    objPos tempPos2; // for proposed coordinates
    objPosArrayList* playerPosList;

    // extract the player position list
    playerPosList = myPlayer->getPlayerPos();

    // Empty the bin
    while(foodBucket->getSize() != 0)
    {
        foodBucket->removeTail();
    }

    // generate number food items
    for(int i=0; i<amountToGenerate; i++)
    {
        // Keep generating new coords until they dont overlap player
        do{
            overlap = false; // defaulting to no overlap

            xCoord = (rand() % (myGM->getBoardSizeX()-2)) + 1; // values from 1 to boardSizeX-2
            // Example
            // boardSizeX = 10
            // All indexes: 0 1 2 3 4 5 6 7 8 9 (10 for null character '\0')
            // Valide indexes for position: 1 2 3 4 5 6 7 8 (i.e., not the border ones)
            
            yCoord = (rand() % (myGM->getBoardSizeY()-2)) + 1;
            // Example
            // boardSizeY = 5
            // All indexes: 0 1 2 3 4
            // Valide indexes for position: 1 2 3 (i.e., not the border ones)

            // Set the food to those coordinates
            tempPos2.setObjPos(xCoord, yCoord, 'o');

            // Loop through the array and add in all the elements
            for(int index=0; index<(playerPosList->getSize()); index++)
            {
                playerPosList->getElement(tempPos,index); // saving the object at the index to a temporary objPos instance

                if(tempPos2.isPosEqual(&tempPos)) // if any part of the snake overlaps, flag it
                {
                    overlap = true;
                    break;
                } 
            }

            // Loop through the food bucket and check if any part of the snake overlaps
            for(int index=0; index<(foodBucket->getSize()); index++)
            {
                foodBucket->getElement(tempPos,index); // saving the object at the index to a temporary objPos instance

                if(tempPos2.isPosEqual(&tempPos)) // if any part of the snake overlaps, flag it
                {
                    overlap = true;
                    break;
                } 
            }

        }while(overlap);
        // Returns true if player and food have equal coordinates, such that loop keeps running until food is generated at unique position

        // Once the generated coordinates do not overlap, then add it to the food bin
        foodBucket->insertHead(tempPos2);
    }
}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}
