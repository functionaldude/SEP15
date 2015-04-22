//------------------------------------------------------------------------------
// Position.cpp
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

#include <string>
#include <sstream>
#include "Position.h"

using std::string;
using std::stringstream;

Position::Position(int8_t x, int8_t y) : x_(x), y_(y)
{
}

Position::Position(){}

Position::Position(const Position &obj)
{
  x_ = obj.x_;
  y_ = obj.y_;
}

int Position::getX()
{
  return x_;
}

int Position::getY()
{
  return y_;
}


bool Position::parse(string input)
{
  stringstream ss(input);
  int x, y;
  char left_bracket = 0;
  char delimiter = 0;
  char right_bracket = 0;

  if ((ss >> left_bracket >> x >> delimiter >> y >> right_bracket) &&
    (left_bracket == '(') && (right_bracket == ')'))
  {
    x_ = x;
    y_ = y;
    return true;
  }
  else
  {
    return false;
  }
}


bool Position::isPos(int8_t x, int8_t y)
{
  return (x == x_ && y == y_);
}


bool Position::isPos(const Position *input)
{
  return (input->x_ == x_ && input->y_ == y_);
}
