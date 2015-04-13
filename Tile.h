//
//  Tile.h
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#ifndef __ass1__Tile__
#define __ass1__Tile__

#include "types.h"

class Position;

class Tile {
public:
  enum Type
  {
    TYPE_CROSS = 1,
    TYPE_CURVE_1 = 2,
    TYPE_CURVE_2 = 3
  };

  Tile(Type Side, Color Topcolor, Position *pos);
  ~Tile();
  Position *getPos();
private:
  Type Side;
  Color Topcolor;
  Position *pos;
};

#endif /* defined(__ass1__Tile__) */
