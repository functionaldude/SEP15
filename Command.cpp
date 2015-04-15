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

Command::Command(Game *game, struct arguments *args):
  game(game),
  args(args)
{
}

Command::~Command()
{
}

cmd_AddTile::cmd_AddTile(Game *game, struct arguments *args): Command(game, args){}
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
  //TODO: this is ghetto
  TileType tiletype;
  if (*args->arg[2] == "+") {
    tiletype = CROSS;
  } else if (*args->arg[2] == "/"){
    tiletype = CURVE_1;
  } else {
    tiletype = CURVE_2;
  }
  Tile *tmp_tile = new Tile(tiletype, game->Activeplayer, tmp_pos);
  error = game->addTile(tmp_tile);
  if (error == -1) {
    cout << "Invalid coordinates - first tile must be set on (0,0)" << endl;
  } else if (error == -3){
    cout << "Invalid coordinates - field not connected to tile" << endl;
  } else if (error == -2){
    cout << "Invalid coordinates - field not empty" << endl;
  }
  if (error != 0) {
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

cmd_Write::cmd_Write(Game *game, struct arguments *args): Command(game, args){}
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

  file.write((char*)header, sizeof(file_header));
  delete header;

  char buffer[2];

  short x = dimensions->minX;
  short y = dimensions->minY;
  while (x <= dimensions->maxX && y <= dimensions->maxY) {
    buffer[0] = 0;
    buffer[1] = 0;
    for (auto &iter : game->tiles) {
      if (iter->getPos()->getX() == x && iter->getPos()->getY() == y) {
        buffer[0] = iter->getType();
        buffer[1] = iter->getColor();
        break;
      }
    }
    file.write(buffer, 2);
    if (x == dimensions->maxX) {
      x = dimensions->minX;
      y++;
    } else {
      x++;
    }
  }
  //only 1 tile on (0,0)
  if(game->tiles.size() == 1){
    buffer[0] = game->tiles[0]->getType();
    buffer[1] = game->tiles[0]->getColor();
    file.write(buffer, 2);
  }

  delete dimensions;
  file.close();
  return 0;
}