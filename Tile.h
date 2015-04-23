//------------------------------------------------------------------------------
// Tile.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//
// latest change by Amel Hamidovic 23.4.2015
//------------------------------------------------------------------------------
//

#ifndef TILE_H
#define TILE_H

#include "Types.h"

class Position;
class Game;

class Tile 
{
  private:
    
    //-------------------------------------------------------------------------
    // Side of a tile
    //
    TileType side_;
    

    //-------------------------------------------------------------------------
    // Topcolor of a tile
    //
    Color topcolor_;
    

    //-------------------------------------------------------------------------
    // Position of a tile
    //
    Position *pos_;
    

    //-------------------------------------------------------------------------
    // A pointer of every tile on the game
    //
    Game *parent_;

  public:
    
    //-------------------------------------------------------------------------
    // Constructor
    //
    Tile(TileType side, Position *pos, Game *parent);
    
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Tile();
    
    //-------------------------------------------------------------------------
    // Returns color of one side of a tile
    //
    Color getSideColor(enum Side side);

    //-------------------------------------------------------------------------
    // Returns all neighbours of a tile even the empty ones
    //
    std::vector<Tile*> *getEdges();

    //-------------------------------------------------------------------------
    // Returns the four next neighbours of a tile
    //
    TileNeighbours *getNeighbours();

    //-------------------------------------------------------------------------
    // Sets the top color according to the neigbours
    //
    void matchSides();

    //-------------------------------------------------------------------------
    // Checks if input has right connection with neighbours
    bool checkSides();
    
    //-------------------------------------------------------------------------
    // Getter Methods
    //
    Position *getPos();
    TileType getType();
    Color getColor();
    Game *getParent();
     
};

#endif // TILE_H
