#include <iostream>
#include "game.h"
#include "board.h"
#include "chessGameController.h"

/**
 * Main program for playing a chess game.
 */
int main (int argc, char * const argv[]) 
{
    
    GameController g{8, 8};
    g.play();
    return 0;

}
