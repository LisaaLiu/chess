#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

class HumanPlayer: public Player {
public:
  
  // constructor
  HumanPlayer(string name, bool isWhite, int level);
  // destructor
  virtual ~HumanPlayer();
  
};

#endif  // HUMANPLAYER
