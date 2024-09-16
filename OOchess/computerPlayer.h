#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"
#include "move.h"
#include <memory> 

class ComputerPlayer: public Player {

protected:
std::vector<Move*> *moves;

public:
  // constructor
  ComputerPlayer(string name, bool isWhite, int level);
  // destructor
  virtual ~ComputerPlayer();
  // get Random Item from vector of type T
  template <typename T>
  T getRandomItem(const std::vector<T> myVector);
  // get random Move from the moves vector
  Move* getRandomMove();
  // get random pawn pomotion letter
  char getRandomPawnPomotion();
  // get Move from moves vector
 virtual Move* getMove();
  
  
  
};

#endif  // COMPUTERPLAYER_H
