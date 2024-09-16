/*
 *  king.cpp
 *  ChessProject
 */
#include "king.h"

King::King(bool isWhite) : Piece(isWhite), _moved{false}, _canCastle{true}
{
}

King::~King()
{
}

int King::value() const
{
    return 0;
}
bool King::hasMoved() const{
    return _moved;
}
void King::setMoved() {
    _moved = true;
}
bool King::canMoveTo(Square& location) const
{
    bool validMove = false;
    int translationX = location.getX() - this->location()->getX();
    int translationY = location.getY() - this->location()->getY();
    
    // valid move if moving 1 square forward/backwards
    if(abs(translationY) == 1 && translationX == 0)
    {
        validMove = true;
    }
    
    // valid move if moving 1 square sideways
    else if(abs(translationX) == 1 && translationY == 0)
    {
        validMove = true;
    }
    
    // valid move if moving 1 square diagonally
    else if(abs(translationX) == 1 && abs(translationY) == 1)
    {
        validMove = true;
    }/*else if(abs(translationX) == 2 && translationY == 0 && !_moved && _canCastle && canCastle()){
        validMove = true;
    }*/
    
    return validMove;
}

char King::getDisplayChar() const
{
    return _isWhite ? 'K' : 'k';
}

bool King::isKing() const{
    return true;
}
bool King::isRook() const{
    return false;
}
bool King::isPawn() const{
    return false;
}
