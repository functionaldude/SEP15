//
//  Game.h
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#ifndef __ass1__Game__
#define __ass1__Game__

#include "types.h"
#include <vector>
#include <string>

class Tile;
class Position;

class Game {
  friend class cmd_AddTile;
  friend class cmd_Write;
protected:
  Color Activeplayer;
  bool Running;
  std::string *filename;
  bool constant_write;
  std::vector<Tile*> tiles;
  std::fstream *outputfile;
  int tile_num;
  bool checkSides(Tile *input, tile_neighbours *neighbours);
  tile_neighbours *getNeighbours(Tile *input);
  std::vector<Tile*> *getEdges(Tile *input);
  void addAutomatic(Tile *input);
  bool tryTile(Tile *input);

public:
  Game(std::string *filename);
  ~Game();
  int8_t addTile(Tile* input);
  void run();
  void togglePlayer();
  void setRunning(bool input);
  Tile *getTile(int8_t x, int8_t y);
  Color getActivePlayer();
  dimension *getFieldDimension();
  std::vector<Tile*> *getTiles();
};

#endif /* defined(__ass1__Game__) */
