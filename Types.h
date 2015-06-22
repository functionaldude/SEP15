//------------------------------------------------------------------------------
// Types.h
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

#ifndef TYPES_H 
#define TYPES_H

#include <string>

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif

class Tile;

//-------------------------------------------------------------------------
// Enum for colors
// 
enum Color
{
  COLOR_BLANK = 0,
  COLOR_WHITE = 1,
  COLOR_RED = 2
};

//-------------------------------------------------------------------------
// Enum for Commands
// 
enum Cmd
{
  CMD_QUIT = 0,
  CMD_ADDTILE = 1,
  CMD_WRITE = 2,
  CMD_ERROR = 3,
  CMD_BLANK = 4,
  CMD_STAT = 5
};

//-------------------------------------------------------------------------
// Struct for checking input arguments 
//
struct Arguments
{
  Cmd command;
  std::string *arg[3] = {nullptr, nullptr, nullptr};
  uint8_t arg_count;

  ~Arguments()
  {
    for (uint_fast8_t cnt = 0; cnt < 3; cnt++)
    {
      delete arg[cnt];
    }
  }
};

//-------------------------------------------------------------------------
// Struct for scaling width and height of the game board
//
struct Dimension
{
  int8_t min_x = 0;
  int8_t max_y = 0;
  int8_t min_y = 0;
  int8_t max_x = 0;
};

//-------------------------------------------------------------------------
// Struct for the file header
//
struct FileHeader
{
  unsigned char magicnum[4] = {'T', 'R', 'A', 'X'};
  unsigned char player;
  char min_x;
  char min_y;
  char max_x;
  char max_y;
}__attribute__((packed));


//-----------------------------------------------------------------------------
// Enum for different Tile Types
//
enum TileType 
{
  VOID = 0,
  CROSS = 1,
  CURVE_1 = 2,
  CURVE_2 = 3
};

//-----------------------------------------------------------------------------
// Enum for Topside of Tiles
//
enum Side
{
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3
};

//-------------------------------------------------------------------------
// Struct for initialising, counting and checking neighbours of Tiles
//
struct TileNeighbours 
{
  Tile *up = nullptr;
  Tile *down = nullptr;
  Tile *left = nullptr;
  Tile *right = nullptr;

  uint_fast8_t countNeighbours()
  {
    uint_fast8_t retval = 0;
    if (up){retval++;}
    if (down){retval++;}
    if (left){retval++;}
    if (right){retval++;}
    return retval;
  }
  
  bool hasNeighbours()
  {
    return (up || down || left || right);
  }
};

#endif // TYPES_H
