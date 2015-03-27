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
  int x;
  int y;
public:
  Position(int x, int y);
  int getX();
  int getY();
  bool parse(std::string input);
  std::string toString();
};

#endif /* defined(__ass1__Position__) */
