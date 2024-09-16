#include "levelTwoComputer.h"
#include "move.h"
#include "chessConst.h"
#include <iostream>
#include <vector>
#include <random>
// generate all the capturing and check move for the pieces the player have
void LevelTwoComputer::generateMoves(){
    
    for (auto am :*moves) {
        delete (am);
    }
    moves->erase(moves->begin(), moves->end());
   

    for (set<Piece*>::iterator itr = _myPieces->begin(); itr != _myPieces->end(); ++itr)
    {
        if (*itr) {
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
               
                  pChar = getRandomPawnPomotion();
                    if (!(*itr)->isWhite()) {
                      pChar = tolower(pChar); 
                    } 
                  }
              } 
              
              if ((Piece*)(*itr)->validCaptureCheckMove(*this, *(_board->squareAt(j,i)),pChar)){
           
                moves->emplace_back(new Move(fromSquare, toSquare, pChar));
                   
              }
            }
        }
        
      }
  

    }
 

}
// first get the move from the capturing and check moves,
// if there is no more capturing and check moves,
// call level one and get a valid moves
Move* LevelTwoComputer::getMove() {
    Move *aMove =nullptr;
    generateMoves();
    if (moves->size()>0){
      aMove = getRandomMove(); 

    } else {
      return(component->getMove());
    }
    return aMove;

}
