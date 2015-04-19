//
//  Tile.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include "Tile.h"
#include "Position.h"

Tile::Tile(TileType Side, Position *pos, Color player) :
  Side(Side),
  pos(pos),
  player(player)
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

Color Tile::getPlayer(){
  return player;
}

void Tile::setColor(Color input){
  Topcolor = input;
}

Color Tile::getSideColor(short side){
  //0 = up, 1 = down, 2 = left, 3 = right
  if (Side == CROSS) {
    if (Topcolor == COLOR_RED) {
      switch (side) {
        case 0: return COLOR_RED;
        case 1: return COLOR_RED;
        case 2: return COLOR_WHITE;
        case 3: return COLOR_WHITE;
        default: return COLOR_BLANK;
      }
    } else {
      switch (side) {
        case 0: return COLOR_WHITE;
        case 1: return COLOR_WHITE;
        case 2: return COLOR_RED;
        case 3: return COLOR_RED;
        default: return COLOR_BLANK;
      }
    }
  } else if (Side == CURVE_1) {
    if (Topcolor == COLOR_RED) {
      switch (side) {
        case 0: return COLOR_RED;
        case 1: return COLOR_WHITE;
        case 2: return COLOR_RED;
        case 3: return COLOR_WHITE;
        default: return COLOR_BLANK;
      }
    } else {
      switch (side) {
        case 0: return COLOR_WHITE;
        case 1: return COLOR_RED;
        case 2: return COLOR_WHITE;
        case 3: return COLOR_RED;
        default: return COLOR_BLANK;
      }
    }
  } else {
    if (Topcolor == COLOR_RED) {
      switch (side) {
        case 0: return COLOR_RED;
        case 1: return COLOR_WHITE;
        case 2: return COLOR_WHITE;
        case 3: return COLOR_RED;
        default: return COLOR_BLANK;
      }
    } else {
      switch (side) {
        case 0: return COLOR_WHITE;
        case 1: return COLOR_RED;
        case 2: return COLOR_RED;
        case 3: return COLOR_WHITE;
        default: return COLOR_BLANK;
      }
    }
  }
}