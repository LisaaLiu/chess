/**
 * knight.h
 *
 * This class represents a chess knight piece.
 *
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include <iostream>
#include "square.h"
#include "piece.h"

using namespace std;

class Knight : public Piece
{
 public:
    
    
    // Creates a Knight

    Knight(bool isWhite);
    
    
     // Default destructor
    
    ~Knight();

    
    // Get the point value of the piece
    
    int value() const override;

    
    // Determines if the piece can legally move to a given square
    
    bool canMoveTo(Square& location) const override;
    
    
     // Display the piece

    char getDisplayChar() const override;
    bool isKing() const override;
    bool isRook() const override;
    bool isPawn() const override;

}; // Knight

#endif
