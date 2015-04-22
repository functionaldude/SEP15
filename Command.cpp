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

Command::Command(Game *game, struct Arguments *args):
  game_(game),
  args_(args)
{
}

Command::~Command()
{
}

CmdAddTile::cmdAddTile(Game *game, struct Arguments *args): Command(game, args){}
int CmdAddTile::execute()
{
  int8_t error = 0;
  if (args->arg_count != 2) 
  {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }
  Position *tmp_pos = new Position();
  if (!tmp_pos->parse(*args->arg[1])) 
  {
    cout << "Invalid parameters" << endl;
    delete tmp_pos;
    return -1;
  }
  //TODO: this is ghetto
  TileType tiletype;
  if (*args->arg[2] == "+") 
  {
    tiletype = CROSS;
  } 
  else if (*args->arg[2] == "/")
  {
    tiletype = CURVE_1;
  } 
  else 
  {
    tiletype = CURVE_2;
  }
  Tile *tmp_tile;
  
  try 
  {
    tmp_tile = new Tile(tiletype, tmp_pos, game);
  } 
  catch (std::bad_alloc &ba) 
  {
    delete tmp_pos;
    throw;
  }
  error = game->addTile(tmp_tile);

  //TODO: rewrite this in switch
  if (error == -1) {
    cout << "Invalid coordinates - first tile must be set on (0,0)" << endl;
  } 
  else if (error == -3)
  {
    cout << "Invalid coordinates - field not connected to tile" << endl;
  } 
  else if (error == -2)
  {
    cout << "Invalid coordinates - field not empty" << endl;
  }  
  else if (error == -4)
  {
    cout << "Invalid move - connected line colors mismatch" << endl;
  } 
  else if (error == 1)
  {
    cout << "Player white wins!" << endl;
  } 
  else if (error == 2)
  {
    cout << "Player red wins!" << endl;
  } 
  else if (error == 3)
  {
    if (game->Activeplayer == COLOR_RED) 
    {
      cout << "Player red wins!" << endl;
    } 
    else 
    {
      cout << "Player white wins!" << endl;
    }
  } 
  else if (error == 4)
  {
    cout << "No more tiles left. Game ends in a draw!" << endl;
  }
  if (error < 0) 
  {
    return -1;
  } 
  else if (error > 0)
  {
    game->GameOver();
  } 
  else 
  {
    game->togglePlayer();
  }
  //autosave if -g
  if (game->constant_write) 
  {
    *args->arg[0] = "write";
    *args->arg[1] = "auto";
    args->arg_count = 1;
    Command *save = new CmdWrite(game, args);
    save->execute();
    delete save;
  }
  return 0;
}

CmdWrite::cmdWrite(Game *game, struct Arguments *args): Command(game, args){}
int CmdWrite::execute()
{
  if (args->arg_count != 1) 
  {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }
  if (game->tiles.size() == 0) 
  {
    cout << "Board is empty!" << endl;
    return -1;
  }
  string *filename = args->arg[1];
  fstream *outputfile;
  if (game->constant_write && *filename == "auto") 
  {
    filename = game->filename;
  }

  outputfile = new fstream(*filename, ios::out | ios::binary);
  if (!outputfile->is_open()) 
  {
    cout << "Cannot write file " << *filename << endl;
    return -1;
  }

  FileHeader *header = nullptr;
  Dimension *dimensions = nullptr;
  
  try 
  {
    header = new file_header;
    dimensions = game->getFieldDimension();
  } 
  catch (bad_alloc &ba) 
  {
    if (header) 
    {
      delete header;
    }
    outputfile->close();
    delete outputfile;
    throw;
  }

  header->player = game->Activeplayer;

  header->min_x = dimensions->min_x;
  header->min_y = dimensions->min_y;
  header->max_x = dimensions->max_x;
  header->max_y = dimensions->max_y;

  outputfile->write((char*)header, sizeof(FileHeader));
  delete header;

  char buffer[2] ;

  if(game->tiles.size() == 1)
  {
    //only 1 tile on (0,0)
    buffer[0] = game->tiles[0]->getType();
    buffer[1] = game->tiles[0]->getColor();
    outputfile->write(buffer, 2);
  } 
  else 
  {
    //multiple tiles
    int8_t x = dimensions->min_x;
    int8_t y = dimensions->min_y;
    while (x <= dimensions->max_x && y <= dimensions->max_y) 
    {
      buffer[0] = 0;
      buffer[1] = 0;
      for (auto &iter : game->tiles) 
      {
        if (iter->getPos()->isPos(x, y)) 
        {
          buffer[0] = iter->getType();
          buffer[1] = iter->getColor();
          break;
        }
      }
      outputfile->write(buffer, 2);
      if (x == dimensions->max_x) 
      {
        x = dimensions->min_X;
        y++;
      } 
      else 
      {
        x++;
      }
    }
  }

  delete dimensions;
  outputfile->close();
  delete outputfile;
  return 0;
}
