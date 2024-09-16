/**
 * piece.h
 *
 * This class represents a game piece.
 *
 */

#ifndef PIECE_H
#define PIECE_H

#include <ostream>
#include "square.h"
#include "board.h"
class Player;

using namespace std;

class Piece 
{
 public:
   
    
    // Creates a Piece
   
    Piece(bool isWhite);
    
    
     // Default destructor
   
    virtual ~Piece();

    
    // Move the piece to the square, making sure that the move
    // is legal
    
    virtual bool moveTo(Player& byPlayer, Square& toSquare,char pChar);

    virtual bool validMove(Player& byPlayer, Square& toSquare,char pChar);
    // Set which square the piece is located on
    bool validCaptureCheckMove(Player& byPlayer, Square& toSquare,char pChar);
    bool validAvoidCaptureMove(Player& byPlayer, Square& toSquare,char pChar);
    virtual void setLocation(Square* location);
   // set which board the piece is located on
    virtual void setBoard(Board* board);

    
    // Get the point value of the piece
   
    virtual int value() const = 0;

    
    //Determine if the piece is white
    
    bool isWhite() const;

    // Get the character that the piece should be displayed as
    // (e.g. K for white king, r for black rook)
    virtual char getDisplayChar() const = 0;

    // Determines if the piece can legally move to a given square
    // based on the geometry of the move
    
    virtual bool canMoveTo(Square& location) const = 0;

    bool canCastling(Player& byPlayer, Square& toSquare,char pChar);
    // Determines if the piece is on a square
    
    bool isOnSquare() const;

    
    //Gets the piece's location
    
    Square* location() const;

    //checks if the piece can Castle
    bool canCastle(Square &toLocation) const;
    virtual bool isKing() const= 0;
    virtual bool isRook() const =0;
    virtual bool isPawn() const = 0;
    bool hasMoved() const;
    void setMoved();
    virtual bool canEnPassant(Square& to) const;


 protected:
    bool _isWhite;
    Board* board;
    static Piece* lastMovedPiece;
    //bool canEnPassant;
    
 private:

    // Private attributes
    Square* _square;
    bool _moved;
    
}; // Piece

#endif
