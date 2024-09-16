/**
 * player.h
 *
 * This class represents a chess player.
 *
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <set>
#include "piece.h"
#include "king.h"
#include "move.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "square.h"

using namespace std;

class Player 
{
public:
     // Creates a Player
    
    Player(string name, bool isWhite, int level);
    
    
     //Default destructor
     
    virtual ~Player();
    
    
     // Make a move
     
    virtual bool makeMove(Move *aMove);
    // get a valid move
    virtual Move* getMove();
    

     // checks if this player is in check
     
    bool inCheck();
    
    
     // Capture another piece

    void capture(Piece *aPiece);
    
  
     //Get the player's name
    string getName() const;
    
    
     // Determines if this is the white player

    bool isWhite() const;
    bool iscomputer() const;
    bool isPawnExchange() const;
    
     
    
     // Get the set of this player's pieces
     
    set<Piece*>* myPieces() const;

    // get the level of computer
    int getLevel()const;
    
    // Get this player's king
     
    King* myKing() const;
    // set player's Opponent
    void setOpponent(Player *player);
    // get player's opponent
    Player* getOpponent() const;

    void setBoard(Board* aboard) ;
    void setKing(King* aKing);
    void setmyPieces(set<Piece*>* myPieces);
    void performPawnPomotion(Piece *aPiece, Square* fromSquare,Square *toSquare, char pChar );
protected:
    
    // Private attributes
    Board *_board;
    string _name;
    bool _isWhite;
    set<Piece*> *_myPieces;
    set<Piece*> *_capturedPieces;
    King *_myKing;
    Player *_opponent;
    int _level;
    
}; // Player

#endif
