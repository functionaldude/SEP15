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

struct args{
  cmd command;
  std::string *arg[5];
  short arg_count;
};

#endif
