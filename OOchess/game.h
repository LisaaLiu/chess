/**
 * game.h
 *
 * This class represents a game of chess.
 *
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "board.h"
#include "piece.h"
#include "player.h"
#include "subject.h"

using namespace std;

struct GameState {
  Board* board;
  Move* currentMove;
  bool setupDone;
  bool gameStart;
  bool defaultSetting;
  bool whiteCheckmate;
  bool blackCheckmate;
  bool staleMate;
  bool whiteKingInCheck;
  bool blackKingInCheck;
  bool whiteResign ;
  bool blackResign ;
  double whiteScore;
  double blackScore;
  string currentPlayerColor;
};

class Game :public Subject{
  private:
    
   
  public:
  Player* playerWhite;
  Player* playerBlack;
  Player* currentPlayer;
  Player* nextPlayer;
  set<Piece*> *whitePieces;
  set<Piece*> *blackPieces;
  King *whiteKing;
  King *blackKing;

  GameState state;


    
     // Destructor
   
  ~Game();

    
     //Construtor
     
  Game(int width, int height);
  // check if white king is in check
  bool whiteKinginCheck();
  // check if the black ing is in check
  bool blackKinginCheck();
  // set white Checkmate if it's white checkmate
  void setWhiteCheckmate();
  // set black Checkmate if it is Black checkmate
  void setBlackCheckmate();
  // set staleMate if it is staleMate
  void setStaleMate();
  // check if it is the right set up of the game
  bool validSetup();
  // update game state after the move
  void updateState();
  // remove pieces from the board
  void removePiece(int X, int Y);
  // set the current player
  void setCurrentPlayer(string color);
  // clean up the current game
  void cleanupCurrentGame();
  // put Pieces on the board
  void putPiece(int X, int Y, char type);
  // configure white player
  void setWhitePlayerConfig(Player * aPlayer);
  // configure black player
  void setBlackPlayerConfig(Player * aPlayer);
  // get the next player
  Player* getNextPlayer(Player* player);
  // put the default pieces on the board
  void initializePieces();
  // create the two players
  void createPlayers(int whitePlayer, int blackPlayer);
  // give the pieces to the player
   void givePiecesToPlayers();
  // get the status of the game
  GameState getState();
  
 

}; // Game

#endif
