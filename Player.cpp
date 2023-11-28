#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.x = (mainGameMechsRef->getBoardSizeX()-1) / 2;
    playerPos.y = (mainGameMechsRef->getBoardSizeY()-1) / 2;
    playerPos.symbol = '*';
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list

    returnPos.setObjPos(playerPos);
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

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    switch(myDir)
    {
        case STOP:
            break;
        case LEFT:
            playerPos.y--;
            break;
        case RIGHT:
            playerPos.y++;
            break;
        case UP:
            playerPos.x--;
            break;
        case DOWN:
            playerPos.x++;
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
}

