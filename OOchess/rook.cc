/*
 *  rook.cpp
 *  ChessProject
 *
 */
#include "rook.h"

Rook::Rook(bool isWhite) : Piece(isWhite), _canCastle{true}
{
}

Rook::~Rook()
{
}

int Rook::value() const
{
    return 5;
}

void Rook::setMoved() {
    _moved = true;
}
bool Rook::hasMoved() const{
    return _moved;
}
bool Rook::canMoveTo(Square& location) const
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
    }/*else if (canCastle()&& !_moved && _canCastle){
        validMove = true;
    }*/
    
    return validMove;
}

char Rook::getDisplayChar() const
{
    return _isWhite ? 'R' : 'r';
}

bool Rook::isRook() const {
    return true;
}
bool Rook::isKing() const{
    return false;
}
bool Rook::isPawn() const{
    return false;
}
