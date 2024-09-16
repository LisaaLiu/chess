#ifndef LEVELDECORATOR_H
#define LEVELDECORATOR_H

#include "computerPlayer.h"
// Cell Decorator 
class LevelDecorator : public ComputerPlayer {
protected:
    
    ComputerPlayer* component;
 public:   
    // level decorator constructor
    LevelDecorator(string name, bool isWhite, int level, ComputerPlayer* cPlayer);
   
    // level decorator destructor
    virtual ~LevelDecorator();
    
};

#endif  // LEVEL_DECORATOR_H
