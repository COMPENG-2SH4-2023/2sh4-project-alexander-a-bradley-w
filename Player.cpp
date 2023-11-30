#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // Create the array list for the player
    playerPosList = new objPosArrayList();
    
    // Create a temporary objPos to pass into the insertHead function
    objPos snakeHead;
    snakeHead.setObjPos((mainGameMechsRef->getBoardSizeX()-1) / 2, (mainGameMechsRef->getBoardSizeY()-1) / 2, '*');

    // Insert the snake head
    playerPosList->insertHead(snakeHead);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;

    // Prevent misuse of pointer
    playerPosList = NULL;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   

    char input = mainGameMechsRef->getInput();

    switch(myDir)
    {
        case STOP:
            if(input == 'W' || input == 'w'){
                myDir = UP;
            }
            else if(input == 'S' || input == 's'){
                myDir = DOWN;
            }
            if(input == 'A' || input == 'a'){
                myDir = LEFT;
            }
            else if(input == 'D' || input == 'd'){
                myDir = RIGHT;
            }
            break;
        case LEFT:
            if(input == 'W' || input == 'w'){
                myDir = UP;
            }
            else if(input == 'S' || input == 's'){
                myDir = DOWN;
            }
            break;
        case RIGHT:
            if(input == 'W' || input == 'w'){
                myDir = UP;
            }
            else if(input == 'S' || input == 's'){
                myDir = DOWN;
            }
            break;
        case UP:
            if(input == 'A' || input == 'a'){
                myDir = LEFT;
            }
            else if(input == 'D' || input == 'd'){
                myDir = RIGHT;
            }
            break;
        case DOWN:
            if(input == 'A' || input == 'a'){
                myDir = LEFT;
            }
            else if(input == 'd' || input == 'D'){
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }

    mainGameMechsRef->clearInput();
}

bool Player::checkFoodConsumption()
{
    // Write the position of the snake head into a temporary playerPos object (type objPos)
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);

    // Write the position of a food object into a temporary foodPos object (type objPos)
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);  // Use GameMechs function to get foodPos
    
    return playerPos.isPosEqual(&foodPos);
}

bool Player::checkSelfCollision()
{
    // Note: the tail
    // If the snake less than 5 tiles long there is no need to check this
    if((playerPosList->getSize())<5)
    {
        return false; // no collision is possible if the snake is 4 tiles or less
        // doing this for efficiency
    }

    // Write the position of the snake head into a temporary playerPos object (type objPos)
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);

    // Temporary object for each player body
    objPos playerBody;

    // Loop through all the tiles of the snake body AFTER the head
    // Note: the 5th element (index 4) is the first element that can have a collision with the head
    // Once again, not using index 1 for efficiency sake
    for(int index=4; index<(playerPosList->getSize()); index++)
    {
        // Extract the player body
        playerPosList->getElement(playerBody, index);

        // Check if it overlaps with the head
        if(playerPos.isPosEqual(&playerBody))
        {
            return true; // if it does overlap, return true (exits function)
        }
    }

    // if none of the body pieces overlapped, return false
    return false;
}

void Player::movePlayer()
{
    // Write the position of the snake head into a temporary playerPos object (type objPos)
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    
    // PPA3 Finite State Machine logic
    // Calculating the next position of the snake
    // Incrementing in current direction
    switch(myDir)
    {
        case STOP:
            break;
        case LEFT:
            playerPos.x--;
            break;
        case RIGHT:
            playerPos.x++;
            break;
        case UP:
            playerPos.y--;
            break;
        case DOWN:
            playerPos.y++;
            break;
        default:
            break;
    }

    // Wrap-around
    if( playerPos.y == (mainGameMechsRef->getBoardSizeY()-1)  || playerPos.y == 0 ){
        if( playerPos.y == (mainGameMechsRef->getBoardSizeY()-1) ){
            playerPos.y = 1;
        }else{
            playerPos.y = (mainGameMechsRef->getBoardSizeY()-2);
        }
    }if( playerPos.x == (mainGameMechsRef->getBoardSizeX()-1) || playerPos.x == 0 ){
        if( playerPos.x == (mainGameMechsRef->getBoardSizeX()-1) ){
            playerPos.x = 1;
        }else{
            playerPos.x = (mainGameMechsRef->getBoardSizeX()-2);
        }
    }

    // Add the head at the new location
    playerPosList->insertHead(playerPos);

    // For the tail: need to know if there was food that was consumed
    // Check food collision
    // If yes, dont remove tail to essentially "add" a tail
    // Also, generate a new food and increment the score
    if(!checkFoodConsumption()) {playerPosList->removeTail();}
    else
    {
        // Tail "added" by not removing tail during movement
        // And score will be incremented (tracking score seperately from length for above and beyond features)
        mainGameMechsRef->incrementScore();

        // Now, generate new food!
        mainGameMechsRef->generateFood(this); // note: this is a pointer to an instance of an object itself (i.e., like self in python, but a pointer)
    }

    // Endgame condition: Snake suicide
    // Note: both the food and the self collision cant happen at the same time, so this is all OK
    if(checkSelfCollision()) 
    {
        // Set exit and lose flags to true to quit the game
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
        
        return;
    }

}

