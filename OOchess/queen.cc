/*
 *  queen.cpp
 *  ChessProject
 *
 *
 */
#include "queen.h"

Queen::Queen(bool isWhite) : Piece(isWhite)
{
}

Queen::~Queen()
{
}

int Queen::value() const
{
    return 9;
}

bool Queen::canMoveTo(Square& location) const
{
    bool validMove = false;
    
    // valid move if moving on a clear vertical
    if(board->isClearVertical(*(this->location()), location))
    {
        validMove = true;
    }
    
    // valid move if moving on a clear horizontal
    else if(board->isClearHorizontal(*(this->location()), location))
    {
        validMove = true;
    }
    
    // valid move if moving on a clear diagonal
    else if(board->isClearDiagonal(*(this->location()), location))
    {
        validMove = true;
    }
    
    
    return validMove;
}

char Queen::getDisplayChar() const
{
    return _isWhite ? 'Q' : 'q';
  
}

bool Queen::isKing() const{
    return false;
}
bool Queen::isRook() const{
    return false;
}
bool Queen::isPawn() const{
    return false;
}
