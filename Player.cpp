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

bool Player::movePlayer()
{
    // Write the position of the snake head into a temporary playerPos object (type objPos)
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    
    // PPA3 Finite State Machine logic
    // Calculating the next position of the snake
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

    // Remove the tail
    if(!checkFoodConsumption()) {playerPosList->removeTail();}
    else
    {
        // Tail "added" by not removing tail during movement
        
        // Now, generate new food!
        // We do this by returning true and generating in the main function (Project.cpp)

        return true;
        
    }
    
    return false;
    
}

