/**
 * square.h
 *
 * This class represents a square on a game board.
 *
 */

#ifndef SQUARE_H
#define SQUARE_H

class Piece;

using namespace std;

class Square 
{
 public:
   
    
    // Creates a Square
    Square(int x, int y);
    Square();

   
   // Default destructor
    ~Square();
    
    
    // Set the piece that occupies the square
    
    void setOccupier(Piece* piece);

    
    // Get the X position of the square
    
    
    int getX() const;

    
    //Get the Y position of the square
    
    int getY() const;

    
     //Determine if the square is occupied by a piece
    
    bool occupied() const;   

    
    // Get the Piece that is on the square
    
    Piece* occupiedBy() const;


 private:

    // Private attributes
    int _x;
    int _y;
    Piece* _piece;

}; // Square

#endif
