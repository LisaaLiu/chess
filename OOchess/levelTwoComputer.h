#ifndef LEVEL_TWO_COMPUTER_H
#define LEVEL_TWO_COMPUTER_H

#include "levelDecorator.h"
#include "computerPlayer.h"
// rule two decorator
class LevelTwoComputer : public LevelDecorator {

public:
    LevelTwoComputer(string name, bool isWhite,int level,ComputerPlayer *cPlayer): LevelDecorator(name, isWhite,level,cPlayer){};
    void generateMoves();
    Move* getMove() override;
   
   
};

#endif  // Level_TWO_COMPUTER_H
