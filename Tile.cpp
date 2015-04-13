//
//  Tile.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include "Tile.h"
#include "Position.h"

Tile::Tile(TileType Side, Color Orientation, Position *pos) :
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

bool Tile::operator<(const Tile &other){
  if (pos->getX() == other.pos->getX()) {
    return (pos->getY() < other.pos->getY());
  } else {
    return pos->getX() < other.pos->getX();
  }
}

TileType Tile::getType(){
  return Side;
}

Color Tile::getColor(){
  return Topcolor;
}