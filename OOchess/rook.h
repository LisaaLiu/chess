/**
 * rook.h
 *
 * This class represents a chess rook piece.
 *
 */

#ifndef ROOK_H
#define ROOK_H


#include <iostream>
#include "square.h"
#include "piece.h"


using namespace std;

class Rook : public Piece
{ 
    private:

    bool _moved;
    bool _canCastle;

    public:
    
    
    // Creates a Rook
    
    Rook(bool isWhite);
    
    
     //Default destructor

    ~Rook();


    // return the value
    int value() const override;
    void setMoved();

    bool hasMoved() const;
    
    //Determines if the piece can legally move to a given square

    bool canMoveTo(Square& location) const override;
    
    
     // Display the piece
     
    char getDisplayChar() const override;
    bool isRook() const override;
    bool isKing() const override;
    bool isPawn() const override;


}; // Rook

#endif
