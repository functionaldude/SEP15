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

enum Color{
  COLOR_BLANK = 0,
  COLOR_WHITE = 1,
  COLOR_RED = 2
};

enum cmd : char{
  CMD_QUIT = 0,
  CMD_ADDTILE = 1,
  CMD_WRITE = 2,
  CMD_ERROR = 3,
  CMD_BLANK = 4,
};

struct arguments{
  cmd command;
  std::string *arg[5];
  short arg_count;
};

struct dimension{
  short minX;
  short maxX;
  short minY;
  short maxY;
};

struct file_header{
  unsigned char magic_num[4] = {'T', 'R', 'A', 'X'};
  unsigned char player;
  char minX;
  char minY;
  char maxX;
  char maxY;
}__attribute__((packed));

enum TileType
{
  VOID = 0,
  CROSS = 1,
  CURVE_1 = 2,
  CURVE_2 = 3
};

#endif
