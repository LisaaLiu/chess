/*
 *  piece.cpp
 *  ChessProject
 */
#include <string>
#include "piece.h"
#include "player.h"

Piece::Piece(bool isWhite) : _isWhite(isWhite), _square(NULL), _moved{false} {}

Piece::~Piece()
{
}
bool Piece::validAvoidCaptureMove(Player& byPlayer, Square& toSquare,char pChar)
{
    bool validMove = false;
    Piece* toCapture = NULL;
    Square* fromSquare = _square;
    
    
    // check if this is being moved by its player
    if(_isWhite == byPlayer.isWhite())
    {
        
        // check if this is moving according to the correct geometry
        if(canMoveTo(toSquare))
        {
            // check if toSquare is occupied by a piece that could be captured
            if(toSquare.occupied())
            {
                toCapture = toSquare.occupiedBy();
                
                // move only valid if piece to capture is of different color
                if(toCapture->isWhite() != byPlayer.isWhite())
                {
                    validMove = true;
                }
            }
            // if there isn't a capture and we've made it this far, the move is valid
            else 
            {
                validMove = true;
            }

            if(validMove)
            {
                // tentatively make the move:
                // tentatively take opponent's piece off the board, if needed
                if(toCapture)
                {
                    toCapture->setLocation(NULL);
                } 
                
                // unset this piece's current square's occupant
                _square->setOccupier(NULL);
                
                // set this piece's new location
                _square = &toSquare;
                
                // set new square's occupant
                _square->setOccupier(this);
                
                // check if the move leaves byPlayer's king in check
                if(byPlayer.inCheck())
                {
                    // if in check, move is invalid
                    validMove = false;
                } 
                

                // check if I would be captured by the opponent if I make the move
                if (validMove) {
                   // cout << "before check avoid captureing" << endl;
                    set<Piece*> *opPieces = byPlayer.getOpponent()->myPieces();
                    for (set<Piece*>::iterator itr = opPieces->begin(); itr != opPieces->end(); ++itr)
                    {
                        if (*itr) { 
                         
                            if ((*itr)->location()){
                                
                                if ((Piece*)(*itr)->canMoveTo(toSquare)){
                                    validMove = false;
                                }
                            }
                           
                        }
                    }
                   
                }
                // undo the move:
                // reset this piece's location
                _square = fromSquare;
                    
                // update the square's occupant
                _square->setOccupier(this);
                // reset the other square's occupant with opponent's piece or NULL
                toSquare.setOccupier(toCapture);
                    
                // if a piece was tentatively captured, put it back
                if(toCapture)
                {
                    toCapture->setLocation(&toSquare);
                }
                
                
            }
            
        }
    }
    
    return validMove;
}

bool Piece::validCaptureCheckMove(Player& byPlayer, Square& toSquare,char pChar)
{
    bool validMove = false;
    Piece* toCapture = NULL;
    Square* fromSquare = _square;
    bool checkMove = false;
    
    // check if this is being moved by its player
    if(_isWhite == byPlayer.isWhite())
    {
        // check if this is moving according to the correct geometry
        if(canMoveTo(toSquare))
        {
            // check if toSquare is occupied by a piece that could be captured
            if(toSquare.occupied())
            {
                toCapture = toSquare.occupiedBy();
                
                // move only valid if piece to capture is of different color
                if(toCapture->isWhite() != byPlayer.isWhite())
                {
                    validMove = true;
                }
            }
            // if there isn't a capture and we've made it this far, the move is valid
            else 
            {
                validMove = true;
            }

            if(validMove)
            {
                // tentatively make the move:
                // tentatively take opponent's piece off the board, if needed
                if(toCapture)
                {
                    toCapture->setLocation(NULL);
                } 
                
                // unset this piece's current square's occupant
                _square->setOccupier(NULL);
                
                // set this piece's new location
                _square = &toSquare;
                
                // set new square's occupant
                _square->setOccupier(this);
                
                // check if the move leaves byPlayer's king in check
                if(byPlayer.inCheck())
                {
                    // if in check, move is invalid
                    validMove = false;
                } 
                if (byPlayer.getOpponent()->inCheck())  {
                    checkMove = true;
                }
                // undo the move:
                // reset this piece's location
                _square = fromSquare;
                    
                // update the square's occupant
                _square->setOccupier(this);
                    
                // reset the other square's occupant with opponent's piece or NULL
                toSquare.setOccupier(toCapture);
                    
                // if a piece was tentatively captured, put it back
                if(toCapture)
                {
                    toCapture->setLocation(&toSquare);
                }
                
            }
            
        }
    }
    if (validMove && (toCapture||checkMove))
    {
        validMove = true;
    } else {
        validMove = false;
    }
    return validMove;
}
bool Piece::validMove(Player& byPlayer, Square& toSquare,char pChar)
{
    bool validMove = false;
    Piece* toCapture = NULL;
    Square* fromSquare = _square;
   // cout<<  byPlayer.getName() << endl;
    // check if this is being moved by its player
    if(_isWhite == byPlayer.isWhite())
    { 
        if (canCastling(byPlayer, toSquare,pChar)) {
            return true;
        }
        // check if this is moving according to the correct geometry
        if(canMoveTo(toSquare))
        {
            // check if toSquare is occupied by a piece that could be captured
            if(toSquare.occupied())
            {
                toCapture = toSquare.occupiedBy();
                
                // move only valid if piece to capture is of different color
                if(toCapture->isWhite() != byPlayer.isWhite())
                {
                    validMove = true;
                }
            }
            // if there isn't a capture and we've made it this far, the move is valid
            else 
            {
                validMove = true;
            }

            if(validMove)
            {
                // tentatively make the move:
                // tentatively take opponent's piece off the board, if needed
                if(toCapture)
                {
                    toCapture->setLocation(NULL);
                } 
                
                // unset this piece's current square's occupant
                _square->setOccupier(NULL);
                
                // set this piece's new location
                _square = &toSquare;
                
                // set new square's occupant
                _square->setOccupier(this);
                
                // check if the move leaves byPlayer's king in check
                if(byPlayer.inCheck())
                {
                    // if in check, move is invalid
                    validMove = false;
                }    
                // undo the move:
                // reset this piece's location
                _square = fromSquare;
                    
                // update the square's occupant
                _square->setOccupier(this);
                    
                // reset the other square's occupant with opponent's piece or NULL
                toSquare.setOccupier(toCapture);
                    
                // if a piece was tentatively captured, put it back
                if(toCapture)
                {
                    toCapture->setLocation(&toSquare);
                }
                
            }
            
        }
    }
    
    return validMove;
}

Piece* Piece::lastMovedPiece = nullptr;

bool Piece::canCastling(Player& byPlayer, Square& toSquare,char pChar)
{
    if (!isKing() || hasMoved() || toSquare.getY() != _square->getY())
    {
        return false;
    }

    if (((_square->getY() != 0) && (_square->getY() != 7 ))|| (_square->getX() != 4))  {
        return false;
    }
    
    
    int translationX = toSquare.getX() - _square->getX();

    if (abs(translationX) != 2 ) {
        return false;
    }
        
    int direction = (translationX > 0) ? 1 : 0;
    //int rookDirection = (direction>0)? -1: 1;
    Square* rookSquare = board->squareAt((direction > 0) ? 7 : 0, _square->getY());
    Piece* rook = rookSquare->occupiedBy();
    if (!rook) {
        return false;
    }
    if (!(rook->isRook()) || hasMoved()) {
        return false;
    }          
                    
    if (direction) {// kingside castling
        Square* next1Square;
        Square* next2Square;
        next1Square = board->squareAt(_square->getX()+1,_square->getY());
        next2Square = board->squareAt(_square->getX()+2,_square->getY());

        if ((next1Square->occupied()) || (next2Square->occupied())) {
            return false;
        }
    } else { // queen side castling
            Square* next1Square;
            Square* next2Square;
            Square* next3Square;
            next1Square = board->squareAt(_square->getX()-1,_square->getY());
            next2Square = board->squareAt(_square->getX()-2,_square->getY());
            next3Square = board->squareAt(_square->getX()-3,_square->getY());
            if ((next1Square->occupied()) || (next2Square->occupied())||(next3Square->occupied())) {
                return false;
             }

    }

    // check if king will be in check in the toSquare and New Rook Square  
    // 
    Square* newRookSquare = nullptr;

    if (direction) {
        newRookSquare = board->squareAt(_square->getX()+1,_square->getY());
    }
    else {
        newRookSquare = board->squareAt(_square->getX()-1,_square->getY());
    }
    // check if king will be in check in the toSquare and New Rook Square  
    // 
    for (set<Piece*>::iterator itr = byPlayer.getOpponent()->myPieces()->begin(); 
    itr != byPlayer.getOpponent()->myPieces()->end(); ++itr)
    {
       
        if (*itr) {
            if ((*itr)->location()) {
                if (((*itr)->canMoveTo(*_square))||((*itr)->canMoveTo(toSquare)) || ((*itr)->canMoveTo(*newRookSquare)))
                {   
                 return false;
                }
            }
        }
                        
        
                    
    }
        
    return true;
}



bool Piece::moveTo(Player& byPlayer, Square& toSquare,char pChar)
{
    bool validMove = false;
    Piece* toCapture = NULL;
    Square* fromSquare = _square;
    
    // check if this is being moved by its player
    if(_isWhite == byPlayer.isWhite())
    {
        /*
        // check if this is moving according to the correct geometry
        if (isKing() && !hasMoved() && toSquare.getY() == _square->getY() && (_square->getY() == 0 || _square->getY() == 7) && _square->getX() == 4) 
        {

            int translationX = toSquare.getX() - _square->getX();

            if (abs(translationX) == 2 )
            {
                int direction = (translationX > 0) ? 1 : -1;
                int rookDirection = (direction>0)? -1: 1;
                Square* rookSquare = board->squareAt((direction > 0) ? 7 : 0, _square->getY());
                Piece* rook = rookSquare->occupiedBy();

                if (rook->isRook() && !hasMoved()){
                    // Check if the squares between the king and the rook are empty
                    Square* betweenKingAndRook = board->squareAt(_square->getX() + direction, _square->getY());
                    Square* beyondRook = board->squareAt(_square->getX() + 2 * direction + rookDirection, _square->getY());

                    if (!betweenKingAndRook->occupied() && !beyondRook->occupied())
                    {
                        // Perform the castling move
                        //toCapture = beyondRook->occupiedBy(); // In case there is a piece on the destination square

                        // Move the king
                        _square->setOccupier(nullptr);
                        toSquare.setOccupier(this);
                        setLocation(&toSquare);

                        // Move the rook
                        rookSquare->setOccupier(nullptr);
                        beyondRook->setOccupier(rook);
                        rook->setLocation(betweenKingAndRook);
                        validMove = true;
                    }
                }
            }
        
        }*/
        if (canCastling(byPlayer, toSquare,pChar)) {
            int translationX = toSquare.getX() - _square->getX();
            int direction = (translationX > 0) ? 1 : 0;

            Square* rookSquare = board->squareAt((direction>0) ? 7 : 0, _square->getY());
            Square* newRookSquare = nullptr;
            Piece* rook = rookSquare->occupiedBy();

            if (direction) {
                newRookSquare = board->squareAt(_square->getX()+1,_square->getY());
            }
            else {
                newRookSquare = board->squareAt(_square->getX()-1,_square->getY());
            }
            // Move the king
             _square->setOccupier(nullptr);
            toSquare.setOccupier(this);
            setLocation(&toSquare);

            // Move the rook
            rookSquare->setOccupier(nullptr);
            newRookSquare->setOccupier(rook);
            rook->setLocation(newRookSquare);
            return true;
        }
        if(canMoveTo(toSquare)){
            // check if toSquare is occupied by a piece that could be captured
            if(toSquare.occupied())
            {
                toCapture = toSquare.occupiedBy();
                
                // move only valid if piece to capture is of different color
                if(toCapture->isWhite() != byPlayer.isWhite())
                {
                    validMove = true;
                }
            }
            // if there isn't a capture and we've made it this far, the move is valid
            else 
            {
                validMove = true;
            }

            if(validMove){
                // tentatively make the move:
                // tentatively take opponent's piece off the board, if needed


                if(canEnPassant(toSquare)){
                    Square* capturedSquare = board->squareAt(toSquare.getX(), _square->getY());
                    Piece* capturedPawn = capturedSquare->occupiedBy();
                    if (capturedPawn)
                    {
                        // Capture the en passant pawn and remove it from the board
                        byPlayer.capture(capturedPawn);
                        capturedSquare->setOccupier(NULL);
                    }
                }

                if(toCapture)
                {
                    toCapture->setLocation(NULL);
                } 
                // unset this piece's current square's occupant
                _square->setOccupier(NULL);
                
                // set this piece's new location
                _square = &toSquare;
                
                // set new square's occupant
                _square->setOccupier(this);
                
                // check if the move leaves byPlayer's king in check
                if(byPlayer.inCheck())
                {
                    // if in check, move is invalid
                    validMove = false;
                    
                    // undo the move:
                    // reset this piece's location
                    _square = fromSquare;
                    
                    // update the square's occupant
                    _square->setOccupier(this);
                    
                    // reset the other square's occupant with opponent's piece or NULL
                    toSquare.setOccupier(toCapture);
                    
                    // if a piece was tentatively captured, put it back
                    if(toCapture)
                    {
                        toCapture->setLocation(&toSquare);
                    }
                }
                else 
                {
                    // if not in check, move is valid, so actually
                    // capture the opponent's piece, if needed
                    if(toCapture)
                    {
                       // cout << " should capture here " << endl;
                        byPlayer.capture(toCapture);
                    } 
                }
            }

        }
    }
    // After successful move, update the lastMovedPiece to the moved piece
    lastMovedPiece = this;
    
    return validMove;
}

void Piece::setLocation(Square* location)
{
    _square = location;
}
void Piece::setBoard(Board* aboard) {
    board = aboard;
}

bool Piece::isWhite() const
{
    return _isWhite;
}


Square* Piece::location() const
{
    return _square;
}

bool Piece::hasMoved() const{
    return _moved;
}

void Piece::setMoved(){
    _moved = true;
}


bool Piece::canEnPassant(Square& to) const
{
    return false;
}
