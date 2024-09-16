#include <string>
#include "move.h"

Move::Move(std::string fromSquare, std::string toSquare,  char promotedPieceType ): 
_fromSquare{fromSquare}, _toSquare{toSquare}, _promotedPieceType{promotedPieceType}{};

Move::~Move() {}
