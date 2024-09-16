#ifndef LEVEL_THREE_COMPUTER_H
#define LEVEL_THREE_COMPUTER_H

#include "levelDecorator.h"
#include "computerPlayer.h"

class LevelThreeComputer : public LevelDecorator {

public:
    LevelThreeComputer(string name, bool isWhite,int level,ComputerPlayer *cPlayer): LevelDecorator(name, isWhite,level,cPlayer){};
    bool myPieceIndanger(Piece *myPiece);
    void generateMoves();
    
    Move* getMove() override;
  
};

#endif  // RULE_THREE_COMPUTER_H
