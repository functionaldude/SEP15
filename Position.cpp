//
//  Position.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include <string>
#include <sstream>
#include "Position.h"

Position::Position(int8_t x, int8_t y) : x(x), y(y)
{
}

Position::Position(){}

Position::Position(const Position &obj){
  x = obj.x;
  y = obj.y;
}

int Position::getX(){
  return x;
}

int Position::getY(){
  return y;
}

//position parsing
bool Position::parse(std::string input){
  std::stringstream ss(input);
  int x, y;
  char left_bracket = 0;
  char delimiter = 0;
  char right_bracket = 0;

  if ((ss >> left_bracket >> x >> delimiter >> y >> right_bracket) &&
             (left_bracket == '(') &&
             (right_bracket == ')')
      ){
    this->x = x;
    this->y = y;
    return true;
  }else{
    return false;
  }
}

//converts position to string
std::string Position::toString(){
  std::stringstream ss;
  ss << "(" << x << "," << y << ")";
  return ss.str();
}

//checks if a position is on x, y
bool Position::isPos(int8_t x, int8_t y){
  return (x == this->x && y == this->y);
}

//returns true if the input pointer on the same position is
bool Position::isPos(const Position *input){
  return (input->x == this->x && input->y == this->y);
}