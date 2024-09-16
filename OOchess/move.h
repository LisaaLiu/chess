#ifndef MOVE_H
#define MOVE_H
#include <ostream>
class Move 
{
    public:
        std::string  _fromSquare;
        std::string _toSquare;

        //bool _castling;
        char _promotedPieceType;
        Move(std::string fromSquare, std::string toSquare, char promotedPieceType );
    
    
        // Default destructor
   
        virtual ~Move();   
};
#endif
