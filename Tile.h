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
class Game;

class Tile {
public:
  Tile(TileType Side, Position *pos, Color player, Game *parent);
  ~Tile();
  Position *getPos();
  TileType getType();
  Color getColor();
  void setColor(Color input);
  Color getPlayer();
  Color getSideColor(enum Side side);
  void matchSides(struct tile_neighbours *neighbours);
  Game *getParent();
  std::vector<Tile*> *getEdges();
  tile_neighbours *getNeighbours();
private:
  TileType Side;
  Color Topcolor;
  Position *pos;
  Color player;
  Game *parent;
};

#endif /* defined(__ass1__Tile__) */
