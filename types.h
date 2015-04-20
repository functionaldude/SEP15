//
//  types.h
//  SEP15
//
//  Created by Zoltán Sasvári on 13.04.15.
//  Copyright (c) 2015 BinaryTrasher. All rights reserved.
//

#ifndef SEP15_types_h
#define SEP15_types_h

#include <string>

class Tile;

enum Color{
  COLOR_BLANK = 0,
  COLOR_WHITE = 1,
  COLOR_RED = 2
};

enum cmd{
  CMD_QUIT = 0,
  CMD_ADDTILE = 1,
  CMD_WRITE = 2,
  CMD_ERROR = 3,
  CMD_BLANK = 4,
};

struct arguments{
  cmd command;
  std::string *arg[3] = {nullptr, nullptr, nullptr};
  uint8_t arg_count;

  ~arguments(){
    for (uint_fast8_t cnt = 0; cnt < 3; cnt++){
      delete arg[cnt];
    }
  }
};

struct dimension{
  int8_t minX;
  int8_t maxX;
  int8_t minY;
  int8_t maxY;
};

struct file_header{
  unsigned char magic_num[4] = {'T', 'R', 'A', 'X'};
  unsigned char player;
  char minX;
  char minY;
  char maxX;
  char maxY;
}__attribute__((packed));

enum TileType{
  VOID = 0,
  CROSS = 1,
  CURVE_1 = 2,
  CURVE_2 = 3
};

enum Side{
  UP = 0,
  DOWN = 1,
  LEFT = 2,
  RIGHT = 3
};

struct tile_neighbours {
  Tile *UP = nullptr;
  Tile *DOWN = nullptr;
  Tile *LEFT = nullptr;
  Tile *RIGHT = nullptr;

  uint_fast8_t countNeighbours(){
    uint_fast8_t retval = 0;
    if (UP){retval++;}
    if (DOWN){retval++;}
    if (LEFT){retval++;}
    if (RIGHT){retval++;}
    return retval;
  }
  bool hasNeighbours(){
    return (UP || DOWN || LEFT || RIGHT);
  }
  bool hasParalellNeighbours(){
    return (UP && DOWN && !LEFT && !RIGHT) || (LEFT && RIGHT && !UP && !DOWN);
  }
};

#endif
