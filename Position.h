//
//  Position.h
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#ifndef __ass1__Position__
#define __ass1__Position__

#include <string>

class Position {
private:
  int8_t x;
  int8_t y;
public:
  Position(int8_t x, int8_t y);
  Position();
  Position(const Position &obj);
  int getX();
  int getY();
  bool parse(std::string input);
  bool isPos(int8_t x, int8_t y);
  bool isPos(const Position* input);
  std::string toString();
};

#endif /* defined(__ass1__Position__) */
