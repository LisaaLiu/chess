#ifndef BOARD_H
#define BOARD_H

#include <ostream>
#include "square.h"
#include "vector"

using namespace std;


class Board 
{
   private:
    std::vector<std::vector<Square*>> squares;
    
 public:
    const int width;
    const int height;

   Board(int width, int height);
   ~Board();


    
   // Get a specific square on the board
    
   Square* squareAt(int x, int y) const;

    
   // Determine if the path between two squares is a clear vertical
    
   bool isClearVertical(Square& from, Square& to) const;

    
   // Determine if the path between two squares is a clear horizontal
    
   bool isClearHorizontal(Square& from, Square& to) const;

    
   // Determine if the path between two squares is a clear diagonal
    
   bool isClearDiagonal(Square& from, Square& to) const;
    
    
   // Determine if the square is on an ending row of the board
   
    bool isEndRow(Square& location) const;

    
    

}; // Board

#endif
