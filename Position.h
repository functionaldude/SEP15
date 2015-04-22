//------------------------------------------------------------------------------
// Position.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//
// latest change by Amel Hamidovic 23.4.2015
//------------------------------------------------------------------------------
//
#ifndef POSITION_H
#define POSITION_H

#include <string>

class Position 
{
  private:

  	//-------------------------------------------------------------------------
    // 8 Bit integer for X coordinates of Tiles
    //
    int8_t x_;
    
    //-------------------------------------------------------------------------
    // 8 Bit integer for Y coordinates of Tiles
    //
    int8_t y_;
  
  public:
    
    //-------------------------------------------------------------------------
    // Constructor
    //
    Position(int8_t x, int8_t y);
    Position();
    
    //-------------------------------------------------------------------------
    // Copy Constructor
    // Makes a copy of another Position Object
    //
    Position(const Position &obj);
    
    //-------------------------------------------------------------------------
    // Method for parsing input string into variables
    // @params input string
    // @returns true if parsing was successful
    //
    bool parse(std::string input);
    
    //-------------------------------------------------------------------------
    // Checks if a position is on x, y
    // @params x coordinate
    // @params y coodinate
    // @returns true if position is on x,y
    //
    bool isPos(int8_t x, int8_t y);
    
    //-------------------------------------------------------------------------
    // Checks if input is on same position
    // @params input of user
    // @returns true if the input pointer is on the same position 
    bool isPos(const Position* input);


    //-------------------------------------------------------------------------
    // Getter Methods
    //
    int getX();
    int getY();
};

#endif // POSITION_H
