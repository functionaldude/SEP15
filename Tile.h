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
  Tile(TileType Side, Color Topcolor, Position *pos);
  ~Tile();
  Position *getPos();
  TileType getType();
  Color getColor();
  bool operator<(const Tile& other);
private:
  TileType Side;
  Color Topcolor;
  Position *pos;
};

#endif /* defined(__ass1__Tile__) */
