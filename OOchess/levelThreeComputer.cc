#include "levelThreeComputer.h"
#include "move.h"
#include "chessConst.h"
#include <iostream>
#include <vector>
#include <random>
// check if the piece is in danger of being captured.
bool LevelThreeComputer::myPieceIndanger(Piece *myPiece) {
  bool inDanger = false;
    
    // for each piece in the opponent's set of pieces
    for (set<Piece*>::iterator itr = _opponent->myPieces()->begin(); 
         itr != _opponent->myPieces()->end(); ++itr)
    {
       
        if (*itr) {
          
            if (((Piece*)*itr)->location() && 
                ((Piece*)*itr)->canMoveTo(*(myPiece->location())))
            {
                // I am in check
                inDanger = true;
            }
        }
    }
   
    return inDanger;

}

// for the pieces that it is in danger of captures
// generate move that will avoid capture

void LevelThreeComputer::generateMoves(){
    
   
    for (auto am :*moves) {
        delete (am);
    }
    moves->erase(moves->begin(), moves->end());
   // cout << "Start level three Move size" << moves->size() << endl;

    for (set<Piece*>::iterator itr = _myPieces->begin(); itr != _myPieces->end(); ++itr)
    {
        if (*itr) {
          if (myPieceIndanger(*itr)){
              string fromSquare = "  ";
              string toSquare = "  ";
        

              fromSquare.at(0) = char (((*itr)->location()->getX()) + X_MIN);
              fromSquare.at(1) = char(((*itr)->location()->getY()) + Y_MIN);
        

              for (int i = 0; i < _board->height; i++)
              {
                for (int j = 0; j < _board->width; j++)
                {  
                  toSquare.at(0) = char (j + X_MIN);
                  toSquare.at(1) = char (i + Y_MIN);
               
                  char pChar = ' ';
                  if ((*itr)->value() == 1) {
               
                    if (i==0 || i== Y_MIN-1) {
                    // cout << "lastrow" << endl;
                      pChar = getRandomPawnPomotion();
                        if (!(*itr)->isWhite()) {
                          pChar = tolower(pChar); 
                        } 
                    }
                } 
              
             
                if ((Piece*)(*itr)->validAvoidCaptureMove(*this, *(_board->squareAt(j,i)),pChar)){
           
                  moves->emplace_back(new Move(fromSquare, toSquare, pChar));
                   
                }
             
              }
            }
        
          }
        }
  

    }
  
}

// if there is the avoid capture moves, get a random avoid capture move
// else call level two to get the capturing and check moves.
// in level two if there is no more capturing and check moves,
// will call level one to get a valid move
Move* LevelThreeComputer::getMove() {
    Move *aMove = nullptr;
    generateMoves();
    
 
    if (moves->size()>0){
      aMove = getRandomMove(); 

    } else {
      return(component->getMove());
    }
    return aMove;

}
