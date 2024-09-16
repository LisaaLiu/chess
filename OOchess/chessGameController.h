#ifndef CHESS_GAME_CONTROLLER_H
#define CHESS_GAME_CONTROLLER_H
#include "game.h"
class GameController{
private:
    Game game;
    
public:
    // constructor
    GameController(int width, int height);
    // setupGame
    void setupGame();
    // check if valid Coordinate
    bool validCoord(string coord);
    // check if valid piece
    bool validPiece(string pieceS);
    // get the lower case of the string
    std::string toLowercase(const std::string& str);
    // get the level of computer
    int  getLevel(string l);
   // bool gameMove(Move *aMove); 
   // play the game
    void play();
    // valid move location
    bool validMoveLocation(string fromSquare, string toSquare);
    // handle human input of the move
    void handleHumanMove(string parameter);
    // start the game
    void startGame(string parameter);
    // set the game to default state
    void setToDefaultState();
};
#endif
