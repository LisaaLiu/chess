/**
 * pawn.h
 *
 * This class represents a chess pawn piece.
 *
 */

#ifndef PAWN_H
#define PAWN_H


#include <iostream>
#include "square.h"
#include "piece.h"
#include "player.h"

using namespace std;

class Pawn : public Piece
{
 public:
    
    
    //Creates a Pawn

    Pawn(bool isWhite);
    
    
     // Default destructor
   
    ~Pawn();

    
    // Set which square the piece is located on
   
    void setLocation(Square* location);

    
    // Get the point value of the piece
    
    int value() const override;
    
    
     // Move the piece to another square.
     
    bool moveTo(Player& byPlayer,Square& toSquare, char pChar);
    bool validMove(Player& byPlayer, Square& toSquare,char pChar);
    bool validAvoidCaptureMove(Player& byPlayer, Square& toSquare,char pChar);
    bool validCaptureCheckMove(Player& byPlayer, Square& toSquare,char pChar);
    // Determines if the piece can legally move to a given square
    // based on the geometry of the move
    
    bool canMoveTo(Square& location) const;

    char getDisplayChar() const override;

   //Get if the piece has been moved previously

    bool hasMoved() const;
    void setMoved();
    bool isKing() const override;
    bool isRook() const override;
    bool isPawn() const override;

   void setEnPassantFlag(bool value) const;
   bool isEnPassant() const;
   bool canEnPassant(Square & location) const;


 private:
   // for pawn promotion
    // Private attributes
    bool _moved;
    Piece* _delegate;
    mutable bool canBeCapturedEnPassant; // indicate if a pawn is eligible for en passant capture on the next move
}; // Pawn

#endif
