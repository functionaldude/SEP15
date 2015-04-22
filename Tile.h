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

class Tile 
{
  public:
    Tile(TileType Side, Position *pos, Game *parent);
    ~Tile();
    Position *getPos();
    TileType getType();
    Color getColor();
    Color getSideColor(enum Side side);
    void matchSides();
    Game *getParent();
    std::vector<Tile*> *getEdges();
    tile_neighbours *getNeighbours();
    bool checkSides();
    
  private:
    TileType Side;
    Color Topcolor;
    Position *pos;
    Game *parent;
};

#endif /* defined(__ass1__Tile__) */
