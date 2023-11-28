#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* Game;
Player* playerPos;



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

    Game = new GameMechs(30,15); // On heap

    playerPos = new Player(Game);
    
    // generate a seed for rand
    srand(time(NULL));

    // Generate food
    Game->generateFood(playerPos); 
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
            case '3':
                Game->generateFood(playerPos);
                break;
                
            // Movement keys
            case 'w':
            case 'W':
                playerPos->updatePlayerDir();
                break;
            case 's':
            case 'S':
                playerPos->updatePlayerDir();
                break;
            case 'd':
            case 'D':
                playerPos->updatePlayerDir();
                break;
            case 'a':
            case 'A':
                playerPos->updatePlayerDir();
            // this is where we will updatePlayerDir()
                break;
            // Invalid key
            default:
                break;
        }
        Game->clearInput(); // reset the input once processed
    }

    // This is where movePlayer() will go
    playerPos->movePlayer();

    // This is where object collision stuff

    // This is where we check win/lose conditions
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    // Print the gameboard
    Game->drawBoard(playerPos);

    Game->printBoard();


    // Print a lose or exit message
    if(Game->getExitFlagStatus() && Game->getLoseFlagStatus())
    {
        MacUILib_printf("\nYou lose!\nScore: %d", Game->getScore());
    }
    else if(Game->getExitFlagStatus() && !(Game->getLoseFlagStatus()))
    {
        MacUILib_printf("\nQuitting...");
    }

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
    delete playerPos;

    MacUILib_uninit();
}
