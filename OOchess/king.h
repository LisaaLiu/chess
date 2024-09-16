/**
 * king.h
 *
 * This class represents a chess king piece.
 *
 */

#ifndef KING_H
#define KING_H

#include <iostream>
#include "square.h"
#include "piece.h"

using namespace std;

class King : public Piece
{ 
private:
   
    bool _moved;
    bool _canCastle;

 public:

   
    // Creates a King
    
    King(bool isWhite);
    
    
    // Default destructor
    
    ~King();

    
    // Get the point value of the piece
    
    int value() const override;

    
    // Determines if the piece can legally move to a given square
  
    bool canMoveTo(Square& location) const override;
    
    
    // Display the piece
    
    char getDisplayChar() const override;

    bool hasMoved() const;
    void setMoved();
    bool isKing() const override;
    bool isRook() const override;
    bool isPawn() const override;

}; // King

#endif
