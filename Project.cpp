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

    Game = new GameMechs(14,7); // On heap
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

    // Print the gameboard
    Game->printBoard();

    // Debugging messages go below
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
