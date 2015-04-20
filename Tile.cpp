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

//returns the position pointer
Position *Tile::getPos(){
  return pos;
}

//returns the tile type
TileType Tile::getType(){
  return Side;
}

//returns topcolor
Color Tile::getColor(){
  return Topcolor;
}

Color Tile::getPlayer(){
  return player;
}

//sets the topcolor
void Tile::setColor(Color input){
  Topcolor = input;
}

//returns the color of the side of the tile
Color Tile::getSideColor(enum Side side){
  if (side == UP) {
    return Topcolor;
  }
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

//sets the top color according to the neigbours
void Tile::matchSides(struct tile_neighbours *neighbours){
  //TODO: setColor here is ghetto
  switch (Side) {
    case VOID: return;

    case CROSS:{
      if (neighbours->UP) {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) {
          setColor(COLOR_RED);
        } else {
          setColor(COLOR_WHITE);
        }
        break;
      }
      if (neighbours->DOWN) {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) {
          setColor(COLOR_RED);
        } else {
          setColor(COLOR_WHITE);
        }
        break;
      }
      if (neighbours->LEFT) {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) {
          setColor(COLOR_WHITE);
        } else {
          setColor(COLOR_RED);
        }
        break;
      }
      if (neighbours->RIGHT) {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) {
          setColor(COLOR_WHITE);
        } else {
          setColor(COLOR_RED);
        }
        break;
      }
      break;
    }

    case CURVE_1:{
      if (neighbours->UP) {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) {
          setColor(COLOR_RED);
        } else {
          setColor(COLOR_WHITE);
        }
        break;
      }
      if (neighbours->DOWN) {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) {
          setColor(COLOR_WHITE);
        } else {
          setColor(COLOR_RED);
        }
        break;
      }
      if (neighbours->LEFT) {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) {
          setColor(COLOR_RED);
        } else {
          setColor(COLOR_WHITE);
        }
        break;
      }
      if (neighbours->RIGHT) {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) {
          setColor(COLOR_WHITE);
        } else {
          setColor(COLOR_RED);
        }
        break;
      }
      break;
    }

    case CURVE_2:{
      if (neighbours->UP) {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) {
          setColor(COLOR_RED);
        } else {
          setColor(COLOR_WHITE);
        }
        break;
      }
      if (neighbours->DOWN) {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) {
          setColor(COLOR_WHITE);
        } else {
          setColor(COLOR_RED);
        }
        break;
      }
      if (neighbours->LEFT) {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) {
          setColor(COLOR_WHITE);
        } else {
          setColor(COLOR_RED);
        }
        break;
      }
      if (neighbours->RIGHT) {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) {
          setColor(COLOR_RED);
        } else {
          setColor(COLOR_WHITE);
        }
        break;
      }
      break;
    }
  }
}