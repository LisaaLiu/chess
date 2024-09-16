
#ifndef RULE_ONE_COMPUTER
#define RULE_ONE_COMPUTER

#include "computerPlayer.h"
// level one  computer decorator
class LevelOneComputer : public ComputerPlayer {

public:
    LevelOneComputer(string name, bool isWhite,int level): ComputerPlayer(name, isWhite,level){};
    void generateMoves();
    Move* getMove() override;
    
};

#endif  // LEVEL_ONE_COMPUTER
