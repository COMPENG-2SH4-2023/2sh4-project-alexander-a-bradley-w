#include "GameMechs.h"
#include "MacUILib.h" // added so that we can do print operations in here already

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

// Is this allowed? Probably not?
// Is it good game design?
void GameMechs::printBoard()
{
    // temporary
    int index;
    char symbol;
    bool printed;
    objPos temp1;
    objPos temp2;

    // Displaying the board
    for(int y=0; y<(boardSizeY); y++) // loop through y coordinates
    {
        for(int x=0; x<(boardSizeX); x++) // for each y coordinate, loop through all x coordinates
        {
            // default space tile
            temp1 = objPos(x, y, ' ');

            // Flag to know when the space has been printed
            printed = false;

            // border of the game board
            if(printed == false)
            {
                index = 0;
                while (getBorderPos(index++, temp2))
                {
                    // If the position of the current tile is one that belongs to a border
                    // get the character
                    symbol = temp2.getSymbolIfPosEqual(&temp1);
                    
                    // If the character is not 0, then they were on a border tile
                    // print out the border
                    // If it is 0, then the tiles did not match 
                    if(symbol != 0)
                    {
                        MacUILib_printf("%c", symbol);
                        printed = true;
                        break;
                    }
                }
            }

            // print the player character

            // otherwise, print the default space tile
            if(printed == false){MacUILib_printf("%c", temp1.getSymbol());}
        }

        // Print the controls for good UI design
        if(y==0){MacUILib_printf("\tMovement:\tw-UP, a-LEFT, s-DOWN, d-RIGHT");}
        else if(y==1){MacUILib_printf("\tQuit:\t\tspacebar");}

        // Next row (y value) prints on a new line
        MacUILib_printf("\n"); 
    }
}