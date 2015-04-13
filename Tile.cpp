//
//  Tile.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include "Tile.h"
#include "Position.h"

Tile::Tile(Type Side, Color Orientation, Position *pos) :
  Side(Side),
  Topcolor(Orientation),
  pos(pos)
{
}

Tile::~Tile(){
  delete pos;
}

Position *Tile::getPos(){
  return pos;
}