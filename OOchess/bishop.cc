#include "bishop.h"

Bishop::Bishop(bool isWhite) : Piece(isWhite)
{
}

Bishop::~Bishop()
{
}

int Bishop::value() const
{
    return 3;
}

bool Bishop::canMoveTo(Square& location) const
{
    bool validMove = false;
    
    // valid move if moving on a clear diagonal
    if(board->isClearDiagonal(*(this->location()), location))
    {
        validMove = true;
    }
    
    return validMove;
}

char Bishop::getDisplayChar() const
{
    return _isWhite ? 'B' : 'b';
}

bool Bishop::isKing() const{
    return false;
}
bool Bishop::isRook() const{
    return false;
}
bool Bishop::isPawn() const{
    return false;
}
