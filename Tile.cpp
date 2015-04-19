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

Color Tile::getSideColor(enum Side side){
  switch (Side) {
    case CROSS:
      if (Topcolor == COLOR_RED) {
        switch (side) {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_WHITE;
        }
      } else {
        switch (side) {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_RED;
        }
      }
    case CURVE_1:
      if (Topcolor == COLOR_RED) {
        switch (side) {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_WHITE;
        }
      } else {
        switch (side) {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_RED;
        }
      }
    case CURVE_2:
      if (Topcolor == COLOR_RED) {
        switch (side) {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_RED;
          default: return COLOR_BLANK;
        }
      } else {
        switch (side) {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_WHITE;
        }
      }
    case VOID: return COLOR_BLANK;
  }
}