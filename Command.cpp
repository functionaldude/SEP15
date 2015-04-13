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
    cout << "Invalid parameters" << endl;
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
  return 0;
}