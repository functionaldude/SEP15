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
  int tile_num;
  void addAutomatic(Tile *input);
  bool checkLoopWin(Color color, Tile *input, Tile *prev, Position *origin);

public:
  Game(std::string *filename);
  ~Game();
  int8_t addTile(Tile* input);
  int8_t tryTile(Tile *input);
  void run();
  void togglePlayer();
  void setRunning(bool input);
  Tile *getTile(int8_t x, int8_t y);
  Color getActivePlayer();
  dimension *getFieldDimension();
  std::vector<Tile*> *getTiles();
};

#endif /* defined(__ass1__Game__) */
