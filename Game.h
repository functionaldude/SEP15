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

class Game 
{
  friend class cmd_AddTile;
  friend class cmd_Write;

  protected:
    Color Activeplayer;
    bool Running;
    std::string *filename;
    bool constant_write;
    std::vector<Tile*> tiles;
    int tile_num;
    bool over;
    void addAutomatic(Tile *input);
    static bool checkLoopWin(Color color, Tile *input, Tile *prev, Position *origin);
    static bool checkLineWin(Color color, Tile *input, Tile *prev);

  public:
    Game(std::string *filename);
    ~Game();
    int8_t addTile(Tile* input);
    int8_t tryTile(Tile *input);
    void run();
    void togglePlayer();
    Tile *getTile(int8_t x, int8_t y);
    void GameOver();
    dimension *getFieldDimension();
    std::vector<Tile*> *getTiles();
};

#endif /* defined(__ass1__Game__) */
