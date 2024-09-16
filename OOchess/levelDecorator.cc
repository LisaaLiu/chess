#include "levelDecorator.h"

// level Decorator constructor

LevelDecorator::LevelDecorator(string name, bool isWhite, int level,ComputerPlayer* cplayer) : ComputerPlayer(name,isWhite,level),component{cplayer} {}

// level Decorator destructor
LevelDecorator::~LevelDecorator(){delete component;}
