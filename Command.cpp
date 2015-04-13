//------------------------------------------------------------------------------
// Filename: Command.cpp
// Description: Class representing a general command
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 02.09.2011
// Last change: 02.09.2011
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "Command.h"
#include "Position.h"
#include "Tile.h"
#include "Game.h"

using namespace std;

Command::Command(Game *game, struct args *args):
  game(game),
  args(args)
{
}

Command::~Command()
{
}

cmd_AddTile::cmd_AddTile(Game *game, struct args *args): Command(game, args){}
int cmd_AddTile::execute(){
  cout << "Addtile " << (int)args->arg_count << endl;
  short error = 0;
  if (args->arg_count != 2) {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }
  Position *tmp_pos = new Position();
  if (!tmp_pos->parse(*args->arg[1])) {
    cout << "Invalid parameters" << endl;
    delete tmp_pos;
    return -1;
  }
  Tile *tmp_tile = new Tile(Tile::TYPE_CROSS, game->Activeplayer, tmp_pos);
  error = game->addTile(tmp_tile);
  if (error == -1) {
    cout << "Invalid coordinates - first tile must be set on (0,0)" << endl;
    delete tmp_tile;
    return -1;
  }

  //autosave if -g
  if (game->constant_write) {
    Command *save = new cmd_Write(game, args);
    save->execute();
    delete save;
  }
  return 0;
}

cmd_Write::cmd_Write(Game *game, struct args *args): Command(game, args){}
int cmd_Write::execute(){
  cout << "write " << (int)args->arg_count << endl;
  if (!game->constant_write && args->arg_count != 1) {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }
  if (game->tiles.size() == 0) {
    cout << "Board is empty!" << endl;
    return -1;
  }
  string *filename;
  if (game->constant_write) {
    filename = &game->filename;
  } else {
    filename = args->arg[1];
  }
  cout << "file: " << *filename << endl;

  file_header *header = new file_header;
  dimension *dimensions = game->getFieldDimension();

  header->player = game->Activeplayer;

  header->minX = dimensions->minX;
  header->minY = dimensions->minY;
  header->maxX = dimensions->maxX;
  header->maxY = dimensions->maxY;

  fstream file(*filename, ios::out | ios::binary);
  if (!file.is_open()) {
    cout << "Cannot write file " << *filename << endl;
    return -1;
  }
  file.write((char*)header, sizeof(header));

  delete header;

  delete dimensions;
  file.close();
  return 0;
}