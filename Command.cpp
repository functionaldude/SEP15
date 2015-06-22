//------------------------------------------------------------------------------
// Command.cpp
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//------------------------------------------------------------------------------
//
#include <iostream>
#include <fstream>
#include "Command.h"
#include "Position.h"
#include "Tile.h"
#include "Game.h"
#include "Types.h"

using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::ios;
using std::bad_alloc;
using std::streamsize;

Command::Command(Game *game, struct Arguments *args):
  game_(game),
  args_(args)
{
}

Command::~Command()
{
}

CmdAddTile::CmdAddTile(Game *game, struct Arguments *args):Command(game, args){}
int CmdAddTile::execute()
{
  int8_t error = 0;
  if (unlikely(args_->arg_count != 2))
  {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }
  Position *tmp_pos = new Position();
  if (!tmp_pos->parse(*args_->arg[1]))
  {
    cout << "Invalid parameters" << endl;
    delete tmp_pos;
    return -1;
  }
  //TODO: this is ghetto
  TileType tiletype;
  if (*args_->arg[2] == "+")
  {
    tiletype = CROSS;
  } 
  else if (*args_->arg[2] == "/")
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
    tmp_tile = new Tile(tiletype, tmp_pos, game_);
  } 
  catch (std::bad_alloc &ba) 
  {
    delete tmp_pos;
    throw;
  }
  error = game_->addTile(tmp_tile);

  //TODO: rewrite this in switch

  if (error != 0)
  {
    switch (error) {
      case -1:
        cout << "Invalid coordinates - first tile must be set on (0,0)" << endl;
        break;
      case -3:
        cout << "Invalid coordinates - field not connected to tile" << endl;
        break;
      case -2:
        cout << "Invalid coordinates - field not empty" << endl;
        break;
      case -4:
        cout << "Invalid move - connected line colors mismatch" << endl;
        break;
      case 1:
        cout << "Player white wins!" << endl;
        break;
      case 2:
        cout << "Player red wins!" << endl;
        break;
      case 3:
        if (game_->activeplayer_ == COLOR_RED)
        {
          cout << "Player red wins!" << endl;
        }
        else
        {
          cout << "Player white wins!" << endl;
        }
        break;
      case 4:
        cout << "No more tiles left. Game ends in a draw!" << endl;
        break;

      default:
        cout << "Unknown error, fuck" << endl;
        exit(-5);
    }

    if (error < 0)
    {
      return -1;
    }
    else
    {
      game_->gameOver();
    }
  }
  else
  {
    game_->togglePlayer();
  }

  //autosave if -g
  if (game_->constant_write_)
  {
    *args_->arg[0] = "write";
    *args_->arg[1] = "auto";
    args_->arg_count = 1;
    Command *save = new CmdWrite(game_, args_);
    save->execute();
    delete save;
  }
  return 0;
}

CmdWrite::CmdWrite(Game *game, struct Arguments *args): Command(game, args){}
int CmdWrite::execute()
{
  if (args_->arg_count != 1) 
  {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }
  if (game_->tiles_.size() == 0) 
  {
    cout << "Board is empty!" << endl;
    return -1;
  }
  string *filename = args_->arg[1];
  fstream *outputfile;
  if (game_->constant_write_ && *filename == "auto")
  {
    filename = game_->filename_;
  }

  outputfile = new fstream(*filename, ios::out | ios::binary);
  if (unlikely(!outputfile->is_open()))
  {
    cout << "Cannot write file " << *filename << endl;
    return -1;
  }

  FileHeader *header = nullptr;
  Dimension *dimensions = nullptr;
  
  try 
  {
    header = new FileHeader;
    dimensions = game_->getFieldDimension();
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

  header->player = game_->activeplayer_;

  header->min_x = dimensions->min_x;
  header->min_y = dimensions->min_y;
  header->max_x = dimensions->max_x;
  header->max_y = dimensions->max_y;

  outputfile->write((char*)header, sizeof(FileHeader));
  delete header;

  char buffer[2];

  if(game_->tiles_.size() == 1)
  {
    //only 1 tile on (0,0)
    buffer[0] = game_->tiles_[0]->getType();
    buffer[1] = game_->tiles_[0]->getColor();
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
      for (auto &iter : game_->tiles_)
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
        x = dimensions->min_x;
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

CmdLoad::CmdLoad(Game *game, struct Arguments *args): Command(game, args){}
int CmdLoad::execute(){
  if (unlikely(args_->arg_count != 1))
  {
    cout << "Error: Wrong parameter count!" << endl;
    return -1;
  }

  fstream *inputfile = new fstream(*args_->arg[1], ios::in | ios::binary);
  if (unlikely(!inputfile->is_open()))
  {
    cout << "Cannot read file " << *args_->arg[1] << endl;
    return -1;
  }

  //get length of file
  inputfile->seekg(0, inputfile->end);
  streamsize length = (streamsize)inputfile->tellg();
  inputfile->seekg(0, inputfile->beg);

  //create buffer
  char * buffer = new char[1024*1024*4];
  char tile[2];

  //read file
  inputfile->read(buffer, length);

  if (buffer[0] != 'T' || buffer[1] != 'R' || buffer[2] != 'A' || buffer[3] != 'X') {
    cout << "Bad file" << endl;
    delete [] buffer;
    inputfile->close();
    delete inputfile;
    return -1;
  }

  //get header
  Dimension dim;
  game_->activeplayer_ = (Color)buffer[4];
  dim.min_x = (int8_t)buffer[5];
  dim.min_y = (int8_t)buffer[6];
  dim.max_x = (int8_t)buffer[7];
  dim.max_y = (int8_t)buffer[8];

  //clear game vector
  game_->tiles_.clear();

  int8_t counter = 9;
  int8_t x = dim.min_x;
  int8_t y = dim.min_y;

  while (x <= dim.max_x && y <= dim.max_y) {
    tile[0] = buffer[counter++];
    tile[1] = buffer[counter++];
    if (tile[0] != 0 && tile[1] != 0) {
      Tile *newtile = new Tile((TileType)tile[0], new Position(x,y), game_);
      newtile->setColor((Color)tile[1]);
      game_->tiles_.push_back(newtile);
    }
    if (x == dim.max_x)
    {
      x = dim.min_x;
      y++;
    }
    else
    {
      x++;
    }
  }

  //autosave if -g
  if (game_->constant_write_)
  {
    *args_->arg[0] = "write";
    *args_->arg[1] = "auto";
    args_->arg_count = 1;
    Command *save = new CmdWrite(game_, args_);
    save->execute();
    delete save;
  }

  return 0;
}