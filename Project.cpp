#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* Game;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(Game->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    Game = new GameMechs(20,10); // On heap
                                // just using default board size currently
}

void GetInput(void)
{
    // Check if there is an new input before returning the input
    if(MacUILib_hasChar())
    {Game->setInput(MacUILib_getChar());}
}

void RunLogic(void)
{
    // If there is an input, then process it
    if(Game->getInput() != 0)
    {
        switch (Game->getInput())
        {
            // exit key
            case ' ': 
                Game->setExitTrue();
                break;
            
            // Debug keys
            case '1':
                Game->incrementScore();
                break;
            case '2':
                Game->setLoseFlag();
                break;

            // Movement keys
            case 'w':
            case 'W':
            case 's':
            case 'S':
            case 'd':
            case 'D':
            case 'a':
            case 'A':
                // this is where we will updatePlayerDir()
                break;

            // Invaid key
            default:
                break;
        }
        Game->clearInput(); // reset the input once processed
    }

    // This is where movePlayer() will go

    // This is where object collision stuff
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    // temporary
    int index;
    char symbol;
    bool printed;
    objPos temp1;
    objPos temp2;

    // Displaying the board
    for(int y=0; y<(Game->getBoardSizeY()); y++) // loop through y coordinates
    {
        for(int x=0; x<(Game->getBoardSizeX()); x++) // for each y coordinate, loop through all x coordinates
        {
            // default space tile
            temp1 = objPos(x, y, ' ');

            // Flag to know when the space has been printed
            printed = false;

            // border of the game board
            if(printed == false)
            {
                index = 0;
                while (Game->getBorderPos(index++, temp2))
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

        // debugging messages
        else if(y==2){MacUILib_printf("\tScore:\t\t%d", Game->getScore());}
        else if(y==3)
        {
            if(Game->getLoseFlagStatus()){MacUILib_printf("\tLoseFlag:\t\tTrue");}
            else{MacUILib_printf("\tLoseFlag:\t\tFalse");}
        }      
        // Next row (y value) prints on a new line
        MacUILib_printf("\n"); 
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //MacUILib_clearScreen();    // commented out so that we can see the screen when program ends
    
    delete Game; // delete Game from heap (GameMechs object)

    MacUILib_uninit();
}
