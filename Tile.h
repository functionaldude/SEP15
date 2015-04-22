//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//------------------------------------------------------------------------------
//

#ifndef TILE_H
#define TILE_H

#include "Types.h"

class Position;
class Game;

class Tile 
{
  public:
    Tile(TileType side, Position *pos, Game *parent);
    ~Tile();
    Position *getPos();
    TileType getType();
    Color getColor();
    Color getSideColor(enum Side side);
    void matchSides();
    Game *getParent();
    std::vector<Tile*> *getEdges();
    TileNeighbours *getNeighbours();
    bool checkSides();
    
  private:
    TileType side_;
    Color topcolor_;
    Position *pos_;
    Game *parent_;
};

#endif // TILE_H
