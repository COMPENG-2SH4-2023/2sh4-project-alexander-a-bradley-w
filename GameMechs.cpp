#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = 0; // NULL

    exitFlag = false;
    loseFlag = false;

    boardSizeX = 30; // default board size
    boardSizeY = 15;

    score = 0;


    border = new objPos[(2*boardSizeX + 2*(boardSizeY-2))]; //amount of border obbjects required
    
    // Populate the border
    int index = 0;
    
    // fill in top row
    for(int xCoord=0; xCoord<boardSizeX; xCoord++)
    {
        border[index] = objPos(xCoord, 0, '#');
        ++index;
    }
    
    // fill in bottom row
    for(int xCoord=0; xCoord<boardSizeX; xCoord++)
    {
        border[index] = objPos(xCoord, (boardSizeY-1), '#');
        ++index;
    }

    // fill in left side
    for(int yCoord=1; yCoord<(boardSizeY-1); yCoord++)
    {
        border[index] = objPos(0, yCoord, '#');
        ++index;
    }

    // fill in right side
    for(int yCoord=1; yCoord<(boardSizeY-1); yCoord++)
    {
        border[index] = objPos((boardSizeX-1), yCoord, '#');
        ++index;
    }
}


GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0; // NULL

    exitFlag = false;
    loseFlag = false;

    // Only use the given board sizes when they are valid sizes!
    // Set a minimum board size of 10x5
    // Otherwise use the default ones
    if(boardX>=10){boardSizeX = boardX;}
    else{boardSizeX = 30;}
    
    if(boardY>=5){boardSizeY = boardY;}
    else{boardSizeY = 15;}

    score = 0;

    border = new objPos[(2*boardSizeX + 2*(boardSizeY-2))]; //amount of border obbjects required

    // Populate the border
    int index = 0;
    
    // fill in top row
    for(int xCoord=0; xCoord<boardSizeX; xCoord++)
    {
        border[index] = objPos(xCoord, 0, '#');
        ++index;
    }
    
    // fill in bottom row
    for(int xCoord=0; xCoord<boardSizeX; xCoord++)
    {
        border[index] = objPos(xCoord, (boardSizeY-1), '#');
        ++index;
    }

    // fill in left side
    for(int yCoord=1; yCoord<(boardSizeY-1); yCoord++)
    {
        border[index] = objPos(0, yCoord, '#');
        ++index;
    }

    // fill in right side
    for(int yCoord=1; yCoord<(boardSizeY-1); yCoord++)
    {
        border[index] = objPos((boardSizeX-1), yCoord, '#');
        ++index;
    }
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    delete[] border;
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::incrementScore()
{
    // For now: only increment by 1 at a time
    ++score;
}

bool GameMechs::getBorderPos(int index, objPos &returnPos)
{
    // Return false if the index is valid
    // and true if it is valid (also carry out operation if valid)
    if(index<0 || index>=(2*boardSizeX + 2*(boardSizeY-2))) // less than 0 or >= to the amount of border objects there are
    {return false;}

    else
    {
        returnPos = border[index]; // copy
        return true;
    }
}