#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "square.h"

using namespace std;

class Bishop : public Piece
{
 public:
    
    
    // Creates a Bishop
    
    Bishop(bool isWhite);
    
    
    // Default destructor
    
    ~Bishop();

    
    // Get the point value of the piece
    
    int value() const override;

    
    // Determines if the piece can legally move to a given square
    
    bool canMoveTo(Square& location) const override;
    
    
     // Display the piece
    
    char getDisplayChar() const override;
    bool isKing() const override;
    bool isRook() const override;
    bool isPawn() const override;

}; // Bishop

#endif
