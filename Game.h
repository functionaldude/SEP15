//------------------------------------------------------------------------------
// Game.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// <Name> <Matriculum Number>
// <Add one row for every additional group member>
//------------------------------------------------------------------------------
//

#ifndef _GAME_H_
#define _GAME_H_

#include "Types.h"
#include <vector>
#include <string>

class Tile;
class Position;

class Game 
{
  friend class CmdAddTile;
  friend class CmdWrite;

  protected:
    Color activeplayer_;
    bool running_;
    std::string *filename_;
    bool constant_write_;
    std::vector<Tile*> tiles_;
    int tile_num_;
    bool over_;
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
    void gameOver();
    Dimension *getFieldDimension();
    std::vector<Tile*> *getTiles();
};

#endif //GAME_H_INCLUDED
