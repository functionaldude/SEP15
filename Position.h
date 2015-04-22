//------------------------------------------------------------------------------
// Position.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// <Name> <Matriculum Number>
// <Add one row for every additional group member>
//------------------------------------------------------------------------------
//
#ifndef __ass1__Position__
#define __ass1__Position__

#include <string>

class Position 
{
  private:
    int8_t x_;
    int8_t y_;
  
  public:
    Position(int8_t x, int8_t y);
    Position();
    Position(const Position &obj);
    int getX();
    int getY();
    bool parse(std::string input);
    bool isPos(int8_t x, int8_t y);
    bool isPos(const Position* input);
};

#endif /* defined(__ass1__Position__) */
