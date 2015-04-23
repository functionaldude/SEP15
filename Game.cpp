//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//------------------------------------------------------------------------------
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <thread>
#include <future>
#include "Game.h"
#include "Tile.h"
#include "Position.h"
#include "Command.h"

using std::cout;
using std::string;
using std::future;
using std::stringstream;
using std::cin;
using std::endl;
using std::async;
using std::bad_alloc;
using std::vector;
using std::system_error;

//command parsing
void getCmd(string input, Arguments *arguments)
{
  if(input == "")
  {
    arguments->command = CMD_BLANK;
    return;
  }
  stringstream iss(input);
  string buf;
  int8_t i = 0;
  for (; iss >> buf; i++)
  {
    arguments->arg[i] = new string(buf);
    transform(arguments->arg[i]->begin(), arguments->arg[i]->end(),
              arguments->arg[i]->begin(), ::tolower);
  }
  arguments->arg_count = i-1;
  if (*arguments->arg[0] == "addtile") 
  {
    arguments->command = CMD_ADDTILE;
  }
  else if (*arguments->arg[0] == "write")
  {
    arguments->command = CMD_WRITE;
  }
  else if (*arguments->arg[0] == "quit")
  {
    arguments->command = CMD_QUIT;
  }
  else 
  {
    arguments->command = CMD_ERROR;
  }
}

//constructor
Game::Game(string *filename) :
  activeplayer_(COLOR_WHITE),
  running_(false),
  over_(false),
  tile_num_(64)
{
  if (filename) 
  {
    filename_ = filename;
    constant_write_ = true;
  } 
  else 
  {
    filename_ = nullptr;
    constant_write_ = false;
  }
}

//main game function
void Game::run()
{
  running_ = true;
  string input;
  Command *cmd = nullptr;
  while (likely(running_))
  {
    if (unlikely(over_))
    {
      running_ = false;
      break;
    }
    Arguments *args_cont = nullptr;
    args_cont = new Arguments;
    cout << "sep> ";
    //cin >> input;
    getline(cin, input);
    getCmd(input, args_cont);
    switch (args_cont->command) 
    {
      case CMD_BLANK:
        delete args_cont;
        continue;
      case CMD_QUIT:
        cout << "Bye!" << endl;
        if (args_cont) 
        {
          delete args_cont;
          args_cont = nullptr;
        }
        if (cmd) 
        {
          delete cmd;
          cmd = nullptr;
        }
        running_ = false;
        return;
      case CMD_ADDTILE:
        try 
        {
          cmd = new CmdAddTile(this, args_cont);
        } 
        catch (bad_alloc &ba) 
        {
          delete args_cont;
          throw;
        }
        break;
      case CMD_WRITE:
        try 
        {
          cmd = new CmdWrite(this, args_cont);
        } catch (bad_alloc &ba) 
        {
          delete args_cont;
          throw;
        }
        break;
      case CMD_ERROR:
        cout << "Error: Unknown command!" << endl;
        delete args_cont;
        continue;
    }
    cmd->execute();
    if (likely(args_cont))
    {
      delete args_cont;
      args_cont = nullptr;
    }
    if (likely(cmd))
    {
      delete cmd;
      cmd = nullptr;
    }
  }
}

void Game::togglePlayer()
{
  if (activeplayer_ == COLOR_WHITE) 
  {
    activeplayer_ = COLOR_RED;
  }
  else 
  {
    activeplayer_ = COLOR_WHITE;
  }
}

//adds a tile
int8_t Game::addTile(Tile *input)
{
  if (tile_num_ == 0) 
  {
    return 4;
  }
  int retval = 0;
  if ((retval = tryTile(input)) == 0) 
  {
    tiles_.push_back(input);
    tile_num_--;
    addAutomatic(input);

    if (tiles_.size() >=5)
    {
      future<bool> fut_win_red_loop;
      future<bool> fut_win_white_loop;
      bool win_red_loop;
      bool win_white_loop;
      try 
      {
        fut_win_red_loop = async(&Game::checkLoopWin, COLOR_RED, input,
                                 nullptr, input->getPos());
        fut_win_white_loop = async(&Game::checkLoopWin, COLOR_WHITE, input,
                                   nullptr, input->getPos());
        win_red_loop = fut_win_red_loop.get();
        win_white_loop = fut_win_white_loop.get();
      }
      catch (system_error)
      {
        win_red_loop = checkLoopWin(COLOR_RED, input, nullptr, input->getPos());
        win_white_loop = checkLoopWin(COLOR_WHITE, input, nullptr, input->getPos());
      }
      if (win_red_loop && win_white_loop) 
      {
        return 3;
      }
      else if (win_red_loop) 
      {
        return 2;
      } 
      else if (win_white_loop)
      {
        return 1;
      }
    }

    if (tiles_.size() >= 8)
    {
      bool win_red_line = checkLineWin(COLOR_RED, input, nullptr);
      bool win_white_line = checkLineWin(COLOR_WHITE, input, nullptr);
      if (win_red_line && win_white_line)
      {
        return 3;
      } 
      else if (win_red_line)
      {
        return 2;
      } 
      else if (win_white_line) 
      {
        return 1;
      }
    }
  } 
  else 
  {
    delete input;
  }
  return retval;
}

//destructor
Game::~Game()
{
  for (auto &iter : tiles_)
  {
    delete iter;
  }
  if (filename_)
  {
    delete filename_;
  }
  tiles_.clear();
}

//returns the game field dimensions in a dimension struct
Dimension *Game::getFieldDimension()
{
  Dimension *retval = new Dimension;
  for (auto &iter : tiles_)
  {
    if (retval->max_x < iter->getPos()->getX())
    {
      retval->max_x = iter->getPos()->getX();
    }
    if (retval->max_y < iter->getPos()->getY())
    {
      retval->max_y = iter->getPos()->getY();
    }
  }
  retval->min_x = retval->max_x;
  retval->min_y = retval->max_y;
  for (auto &iter : tiles_)
  {
    if (retval->min_x > iter->getPos()->getX())
    {
      retval->min_x = iter->getPos()->getX();
    }
    if (retval->min_y > iter->getPos()->getY())
    {
      retval->min_y = iter->getPos()->getY();
    }
  }
  return retval;
}

//returns a tile at pos x, y
Tile *Game::getTile(int8_t x, int8_t y)
{
  for (auto &iter :tiles_)
  {
    if (unlikely(iter->getPos()->isPos(x, y)))
    {
      return iter;
    }
  }
  return nullptr;
}

//checks shit
int8_t Game::tryTile(Tile *input)
{
  if (unlikely(tiles_.size() == 0 && !input->getPos()->isPos(0, 0)))
  {
    return -1;
  }
  for (auto &iter : tiles_)
  {
    if (unlikely(input->getPos()->isPos(iter->getPos())))
    {
      //already exists
      return -2;
    }
  }
  TileNeighbours neighbours = input->getNeighbours();
  if (unlikely(!neighbours.hasNeighbours() && tiles_.size() != 0))
  {
    //no neigbour found
    return -3;
  }
  input->matchSides();
  if (unlikely(!input->checkSides()))
  {
    //colors mismatch
    return -4;
  }
  return 0;
}

void Game::addAutomatic(Tile * input)
{
  vector<Tile*> *array = nullptr;
  Tile *testtile = nullptr;
  try
  {
    array = input->getEdges();
    if (unlikely(!array))
    {
      return;
    }
    TileNeighbours neighbours;
    int8_t tests = 0;
    TileType testtype = VOID;
    for (auto &iter : *array)
    {
      if (iter->getType() == VOID)
      {
        neighbours = iter->getNeighbours();
        int8_t cnt_neighbour = neighbours.countNeighbours();
        if (cnt_neighbour > 1) 
        {
          testtile = new Tile(CROSS, new Position(*iter->getPos()), this);
          if (tryTile(testtile) == 0) 
          {
            tests++;
            testtype = testtile->getType();
          }
          delete testtile;
          testtile = new Tile(CURVE_1, new Position(*iter->getPos()), this);
          if (tryTile(testtile) == 0) 
          {
            tests++;
            testtype = testtile->getType();
          }
          delete testtile;
          testtile = new Tile(CURVE_2, new Position(*iter->getPos()), this);
          if (tryTile(testtile) == 0) 
          {
            tests++;
            testtype = testtile->getType();
          }
          delete testtile;
          if (tests == 1 && testtype != VOID) 
          {
            addTile(new Tile(testtype, new Position(*iter->getPos()), this));
          }
          tests = 0;
          testtype = VOID;
        }
      }
    }

    for (auto &iter : *array)
    {
      if (iter->getType() == VOID) 
      {
        delete iter;
      }
    }
    delete array;
  } 
  catch (bad_alloc &ba) 
  {
    if (array) 
    {
      for (auto &iter : *array)
      {
        if (iter->getType() == VOID) 
        {
          delete iter;
        }
      }
      delete array;
    }
    if (testtile) 
    {
      delete testtile;
    }
    throw;
  }
}

vector<Tile*> *Game::getTiles()
{
  return &tiles_;
}

void Game::gameOver()
{
  over_ = true;
}

bool Game::checkLoopWin(Color color, Tile *input, Tile *prev, Position *origin)
{
  if (prev && origin->isPos(input->getPos())) 
  {
    return true;
  }
  Tile *next = nullptr;
  TileNeighbours neighbours = input->getNeighbours();
  if (neighbours.countNeighbours() < 2) 
  {
    return false;
  }
  if (likely(prev))
  {
    if (neighbours.up &&
        !(neighbours.up->getPos()->isPos(prev->getPos())) &&
        input->getSideColor(UP) == color)
    {
      next = neighbours.up;
    } 
    else if (neighbours.left &&
             !(neighbours.left->getPos()->isPos(prev->getPos())) &&
             input->getSideColor(LEFT) == color)
    {
      next = neighbours.left;
    } 
    else  if (neighbours.down &&
              !(neighbours.down->getPos()->isPos(prev->getPos())) &&
              input->getSideColor(DOWN) == color)
    {
      next = neighbours.down;
    } 
    else if (neighbours.right &&
             !(neighbours.right->getPos()->isPos(prev->getPos())) &&
             input->getSideColor(RIGHT) == color)
    {
      next = neighbours.right;
    }
  } 
  else 
  {
    if (neighbours.up && input->getSideColor(UP) == color)
    {
      next = neighbours.up;
    } 
    else if (neighbours.left && input->getSideColor(LEFT) == color)
    {
      next = neighbours.left;
    } 
    else  if (neighbours.down && input->getSideColor(DOWN) == color)
    {
      next = neighbours.down;
    } 
    else if (neighbours.right && input->getSideColor(RIGHT) == color)
    {
      next = neighbours.right;
    }
  }

  if (!next)
  {
    return false;
  }
  return checkLoopWin(color, next, input, origin);
}

bool Game::checkLineWin(Color color, Tile *input, Tile *prev)
{
  if (!input) 
  {
    return false;
  }
  static Dimension dim;
  static Tile *firstnext;
  static Tile *origin;
  static bool onedirection;
  static int dir_cnt;
  if (unlikely(!prev))
  {
    //first init
    origin = input;
    onedirection = false;
    dir_cnt = 0;
    firstnext = nullptr;
  }
  bool retval = false;

  Tile *next = nullptr;
  TileNeighbours neighbours = input->getNeighbours();

  if (dir_cnt == 2 && onedirection) 
  {
    dir_cnt--;
    onedirection = false;
    input = origin;
    prev = firstnext;
  }

  if (likely(prev))
  {
    if (neighbours.up &&
        !(neighbours.up->getPos()->isPos(prev->getPos())) &&
        input->getSideColor(UP) == color)
    {
      next = neighbours.up;
    }
    else if (neighbours.left &&
             !(neighbours.left->getPos()->isPos(prev->getPos())) &&
             input->getSideColor(LEFT) == color)
    {
      next = neighbours.left;
    }
    else  if (neighbours.down &&
              !(neighbours.down->getPos()->isPos(prev->getPos())) &&
              input->getSideColor(DOWN) == color)
    {
      next = neighbours.down;
    }
    else if (neighbours.right &&
             !(neighbours.right->getPos()->isPos(prev->getPos())) &&
             input->getSideColor(RIGHT) == color)
    {
      next = neighbours.right;
    }
  } 
  else 
  {
    //first
    if (neighbours.up && input->getSideColor(UP) == color) {dir_cnt++;}
    if (neighbours.left && input->getSideColor(LEFT) == color) {dir_cnt++;}
    if (neighbours.down && input->getSideColor(DOWN) == color){dir_cnt++;}
    if (neighbours.right && input->getSideColor(RIGHT) == color){dir_cnt++;}

    if (neighbours.up && input->getSideColor(UP) == color) 
    {
      next = neighbours.up;
    }
    else if (neighbours.left && input->getSideColor(LEFT) == color) 
    {
      next = neighbours.left;
    }
    else  if (neighbours.down && input->getSideColor(DOWN) == color)
    {
      next = neighbours.down;
    }
    else if (neighbours.right && input->getSideColor(RIGHT) == color)
    {
      next = neighbours.right;
    }
    firstnext = next;
  }

  int8_t x = input->getPos()->getX();
  int8_t y = input->getPos()->getY();

  if (x < dim.min_x) {dim.min_x = x;}
  if (x > dim.max_x) {dim.max_x = x;}
  if (y < dim.min_y) {dim.min_y = y;}
  if (y > dim.max_y) {dim.max_y = y;}

  if (likely(dir_cnt))
  {
    if (dim.max_x - dim.min_x > 6)
    {
      return true;
    }
    if (dim.max_y - dim.min_y > 6)
    {
      return true;
    }
  }


  if (!next && dir_cnt == 2) 
  {
    onedirection = true;
  }
  
  retval = checkLineWin(color, next, input);

  return retval;
}
