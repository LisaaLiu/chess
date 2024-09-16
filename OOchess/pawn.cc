/*
 *  pawn.cpp
 *  ChessProject
 *
 */
#include "pawn.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "board.h"

Pawn::Pawn(bool isWhite): Piece(isWhite) ,_moved{false}, _delegate{NULL}, canBeCapturedEnPassant{false}
{
}

Pawn::~Pawn()
{
    if(_delegate)
        delete _delegate;
}

void Pawn::setLocation(Square* location)
{
    if (_delegate) {
        _delegate->setLocation(location);
    }
    Piece::setLocation(location);
}
void Pawn::setMoved() {
    _moved = true;
}

int Pawn::value() const
{
    
    return 1;
}
bool Pawn::validCaptureCheckMove(Player& byPlayer, Square& toSquare,char pChar){
    bool valid = false;
    
    // if the pawn has been promoted
    if(_delegate)
    {
      // use delegate piece's movement rules to determine validity
        valid = _delegate->validAvoidCaptureMove(byPlayer,toSquare,pChar);    
    }
    else 
    {
        // otherwise, attempt to move normally as a pawn
        valid = Piece::validAvoidCaptureMove(byPlayer,toSquare, pChar);    
    }
    
    return valid;
}
bool Pawn::validAvoidCaptureMove(Player& byPlayer, Square& toSquare,char pChar){
    bool valid = false;
    
    // if the pawn has been promoted
    if(_delegate)
    {
      // use delegate piece's movement rules to determine validity
        valid = _delegate->validAvoidCaptureMove(byPlayer,toSquare,pChar);    
    }
    else 
    {
        // otherwise, attempt to move normally as a pawn
        valid = Piece::validAvoidCaptureMove(byPlayer,toSquare, pChar);    
    }
    
    return valid;
}

bool Pawn::validMove(Player& byPlayer, Square& toSquare,char pChar){
     bool valid = false;
    
    // if the pawn has been promoted
    if(_delegate)
    {
      // use delegate piece's movement rules to determine validity
        valid = _delegate->validMove(byPlayer,toSquare,pChar);    
    }
    else 
    {
        // otherwise, attempt to move normally as a pawn
        valid = Piece::validMove(byPlayer,toSquare, pChar);    
    }
    
    return valid;
}
bool Pawn::moveTo(Player& byPlayer,Square& toSquare, char pChar)
{
    bool valid = false;
    // if the pawn has been promoted
    if(_delegate)
    {
        // use delegate piece's movement rules to determine validity
        valid = _delegate->moveTo(byPlayer,toSquare,pChar);
        
        // if the move is valid, move the pawn:
        if(valid)
        {
            // unset the pawn's current square's occupant
            location()->setOccupier(NULL);
            
            // set this pawn's new location
            setLocation(&toSquare);
            
            // set new square's occupant
            location()->setOccupier(this);
        }
    }else {
        // otherwise, attempt to move normally as a pawn
        valid = Piece::moveTo(byPlayer,toSquare, pChar);
        
        // if the move is valid and the pawn has reached the 
        // opponent's edge of the board, promote the pawn to piece of their choice
        /*
        if(valid)
        {
            
            if(board->isEndRow(*location()))
            {
                switch (pChar) {
                    case 'Q':
                    case 'q':
                        _delegate = new Queen(isWhite());
                        break;
                    case 'R':
                    case 'r':
                        _delegate = new Rook(isWhite());
                        break;
                    case 'N':
                    case 'n':
                        _delegate = new Knight(isWhite());
                        break;
                    case 'B':
                    case 'b':
                        _delegate = new Bishop(isWhite());
                        break;
                        default:
                    cout<< "invalid pawn pomotion" << endl;
                        return false;

                }
                
                
                _delegate->setLocation(location());
                _delegate->setBoard(board);
                
            }
            
            _moved = true;
        }*/
    }
    // Set canBeCapturedEnPassant to false for all other pawns except the last moved piece
    if (this != lastMovedPiece && valid)
    {
        for (Piece* piece : *byPlayer.myPieces())
        {
            if (piece->value()==1){
                Pawn* pawn = dynamic_cast<Pawn*>(piece);
                if (pawn && pawn != this)
                {
                    pawn->setEnPassantFlag(false);
                }
            }
        }
    }
    
    return valid;
}

bool Pawn::canMoveTo(Square& location) const
{
    bool validMove = false;
    int translationX = location.getX() - this->location()->getX();
    int translationY = location.getY() - this->location()->getY();
    
    // if pawn has been promoted, use it's delegate's movement rules:
    if(_delegate)
    {
        validMove = _delegate->canMoveTo(location);
    }
    // otherwise, use normal pawn movement rules:
    else 
    {
        // ("forward" is "backwards" relative to the board for black pieces)
        if(!isWhite())
        {
            translationX *= -1;
            translationY *= -1;
        }
        
        // valid move if moving 1 square forward to unoccupied square
        if(!location.occupied() && translationY == 1 && translationX == 0)
        {
            validMove = true;
        }
        
        // valid move if first move and moving 2 squares forward
        // to unoccupied square along a clear vertical
        else if(!hasMoved() && translationY == 2 && translationX == 0 &&
                board->isClearVertical(*(this->location()), location))
        {
            canBeCapturedEnPassant = true;
            validMove = true;
        }
        
        // valid move if capturing a piece on adjacent diagonal
        else if(location.occupied() && translationY == 1 && 
                (translationX == 1 || translationX == -1))
        {
            validMove = true;
        }

        if (translationY == 1 && (translationX == 1 || translationX == -1)) {
                // The move is valid for en passant capture
                if(!isWhite()&& this->location()->getY()== 3 && canEnPassant(location)){
                    validMove = true;
                }else if(isWhite() && this->location()->getY() == 4 && canEnPassant(location)){
                    validMove = true;
                }
        }
    }

    return validMove;
}

bool Pawn::hasMoved() const{
    return _moved;
}

char Pawn::getDisplayChar() const
{
    if (_delegate) return _delegate->getDisplayChar();
    return _isWhite ? 'P' : 'p';
}


bool Pawn::isKing() const{
    return false;
}
bool Pawn::isRook() const{
    return false;
}
bool Pawn::isPawn() const{
    return true;
}
void Pawn::setEnPassantFlag(bool value) const{
    canBeCapturedEnPassant = value;
}
bool Pawn::isEnPassant() const{
    return canBeCapturedEnPassant;
}
bool Pawn::canEnPassant(Square& location) const{
    Square* neighbour = board->squareAt(location.getX(), this->location()->getY());
    Piece* adjacentPiece = neighbour->occupiedBy();
    if (!(_delegate)) {
        if (adjacentPiece && adjacentPiece->isPawn() && adjacentPiece->isWhite() != isWhite()) {
            Pawn* adjacentPawn = dynamic_cast<Pawn*>(adjacentPiece);
            if (adjacentPawn->isEnPassant()) {
                return true;
            }
        }
    }

    return false;
}
