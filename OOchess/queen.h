/**
 * queen.h
 *
 * This class represents a chess queen piece.
 *
 */

#ifndef QUEEN_H
#define QUEEN_H

#include <iostream>
#include "square.h"
#include "piece.h"

using namespace std;

class Queen : public Piece
{
 public:
    
    
     //Creates a Queen

    Queen(bool isWhite);
    
    
     //Default destructor
    
    ~Queen();

    
    //Get the point value of the piece

    int value() const override;

    
    //Determines if the piece can legally move to a given square

    bool canMoveTo(Square& location) const override;

    char getDisplayChar() const override;

    bool isKing() const override;
    bool isRook() const override;
    bool isPawn() const override;

}; // Queen

#endif
