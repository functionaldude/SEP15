//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// <Name> <Matriculum Number>
// <Add one row for every additional group member>
//------------------------------------------------------------------------------
//

#ifndef __ass1__Tile__
#define __ass1__Tile__

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

#endif /* defined(__ass1__Tile__) */
