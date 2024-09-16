#include <iostream>
#include "player.h"
#include "board.h"
#include "game.h"
#include "move.h"

#define X_MIN 'a'
#define X_MAX 'h'
#define Y_MIN '1'
#define Y_MAX '8'

Player::Player(string name, bool isWhite,int level):
_name{name}, _isWhite{isWhite},_level{level}
{
    
}

Player::~Player()
{
}
Move* Player::getMove() {
    return nullptr;
}
/*
Player* Player::getOpponent() {
    return _opponent;
}
*/
void Player::performPawnPomotion(Piece *aPiece, Square* fromSquare,Square *toSquare, char pChar  ) {
    Piece *newPiece;
    
    switch (pChar) {
        case 'Q':
        case 'q':
            newPiece = new Queen(isWhite());
            break;
        case 'R':
        case 'r':
            newPiece = new Rook(isWhite());
            break;
        case 'N':
        case 'n':
            newPiece = new Knight(isWhite());
            break;
        case 'B':
        case 'b':
            newPiece = new Bishop(isWhite());
            break;
        default:
            cout<< "invalid pawn pomotion" << endl;
            return;

        }
        // delete the old pieces
        fromSquare->setOccupier(nullptr);
        aPiece->setLocation(nullptr);
        _myPieces->erase(aPiece);
        delete aPiece;

        Piece *toCapture = toSquare->occupiedBy();
        if (toCapture) {
            capture(toCapture);
        }

        newPiece->setLocation(toSquare);
        _myPieces->insert(newPiece);
        toSquare->setOccupier(newPiece);      
        newPiece->setBoard(_board);                       
                
}
bool Player::makeMove(Move *aMove)
{
   
    int fromX;
    int fromY;
    int toX;
    int toY;
    
   
     
    // translate input (algebraic notation) into board coordinates
    fromX = tolower(aMove->_fromSquare.at(0)) - X_MIN;
    fromY = tolower(aMove->_fromSquare.at(1)) - Y_MIN;
    toX = tolower(aMove->_toSquare.at(0)) - X_MIN;
    toY = tolower(aMove->_toSquare.at(1)) - Y_MIN;
    Square *fromSquare = _board->squareAt(fromX, fromY);
    Piece * aPiece = fromSquare->occupiedBy();
    
    Square *toSquare = _board->squareAt(toX, toY);
    char pChar = aMove->_promotedPieceType;
    // perform pawn promotion
    
    if ((aPiece->value() == 1) && (_board->isEndRow(*toSquare)) )
    {
        if (isWhite()){
        if (pChar!='Q' && pChar!='R'&&pChar!='N'&& pChar != 'B')  {
            return false;
        }
        }
        if (!isWhite()) {
        if (pChar!='q' && pChar!='r'&&pChar!='n'&& pChar != 'b')  {
            return false;
        }
        }
       
        if (aPiece->validMove(*this, *toSquare,pChar)) {

           
            performPawnPomotion(aPiece,fromSquare, toSquare, pChar);
            return true;
        }
    }
                
   
    bool valid = aPiece->moveTo(*this,*(toSquare),aMove->_promotedPieceType);
    
    return (valid);
    
  
}

bool Player::inCheck()
{
    bool check = false;
    
    // for each piece in the opponent's set of pieces
    for (set<Piece*>::iterator itr = _opponent->myPieces()->begin(); 
         itr != _opponent->myPieces()->end(); ++itr)
    {
       
        if (*itr) {
          
            if (((Piece*)*itr)->location() && 
                ((Piece*)*itr)->canMoveTo(*(myKing()->location())))
            {
                // I am in check
                check = true;
            }
        }
    }
   
    return check;
}

void Player::setOpponent(Player* player) {
    _opponent = player;
}
void Player::setBoard(Board* aboard) {
    _board = aboard;
}
void Player::setKing(King* aKing) {
    _myKing = aKing;
}
void Player::setmyPieces(set<Piece*>* myPieces) {
    _myPieces = myPieces;
}
void Player::capture(Piece* aPiece)
{
    // unset the piece's location on the board
    aPiece->setLocation(NULL);
    _opponent->myPieces()->erase(aPiece);
    
    delete aPiece;
   
}
int Player:: getLevel() const 
{
    return _level;
}

string Player::getName() const
{
    return _name;
}

bool Player::isWhite() const
{
    return _isWhite;
}

bool Player::iscomputer() const
{
    if (_level==0)return false;
    else return true;
}
/*
int Player::score() const
{
    int score = 0;
    
    // add up the points of all captured pieces
    for (set<Piece*>::iterator itr = _capturedPieces->begin(); itr != _capturedPieces->end(); ++itr)
    {
        score += ((Piece*)*itr)->value();
    }
    
    return score;
}
*/

set<Piece*>* Player::myPieces() const
{
    return _myPieces;
}

King* Player::myKing() const
{
    return _myKing;
}

Player* Player::getOpponent() const{
    return _opponent;
}
