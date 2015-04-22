//
//  Game.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
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

using namespace std;

//command parsing
void getCMD(string input, arguments *arguments)
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
    transform(arguments->arg[i]->begin(), arguments->arg[i]->end(), arguments->arg[i]->begin(), ::tolower);
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
Game::Game(string *filename)
{
  Activeplayer = COLOR_WHITE;
  Running = false;
  over = false;
  tile_num = 64;
  if (filename) 
  {
    this->filename = filename;
    constant_write = true;
  } 
  else 
  {
    this->filename = nullptr;
    constant_write = false;
  }
}

//main game function
void Game::run()
{
  Running = true;
  string input;
  Command *cmd = nullptr;
  while (Running == true) 
  {
    if (over) 
    {
      Running = false;
      break;
    }
    arguments *args_cont = nullptr;
    args_cont = new arguments;
    cout << "sep> ";
    //cin >> input;
    getline(cin, input);
    getCMD(input, args_cont);
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
        Running = false;
        return;
      case CMD_ADDTILE:
        try 
        {
          cmd = new cmd_AddTile(this, args_cont);
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
          cmd = new cmd_Write(this, args_cont);
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
  }
}

void Game::togglePlayer()
{
  if (Activeplayer == COLOR_WHITE) 
  {
    Activeplayer = COLOR_RED;
  }
  else 
  {
    Activeplayer = COLOR_WHITE;
  }
}

//adds a tile
int8_t Game::addTile(Tile *input)
{
  if (tile_num == 0) 
  {
    return 4;
  }
  int retval = 0;
  if ((retval = tryTile(input)) == 0) 
  {
    tiles.push_back(input);
    tile_num--;
    addAutomatic(input);

    if (tiles.size() >=5)
    {
      future<bool> fut_win_red_loop;
      future<bool> fut_win_white_loop;
      bool win_red_loop;
      bool win_white_loop;
      try 
      {
        fut_win_red_loop = async(&Game::checkLoopWin, COLOR_RED, input, nullptr, input->getPos());
        fut_win_white_loop = async(&Game::checkLoopWin, COLOR_WHITE, input, nullptr, input->getPos());
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

    if (tiles.size() >= 8)
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
  for (auto &iter : tiles) 
  {
    delete iter;
  }
  if (filename)
  {
    delete filename;
  }
  tiles.clear();
}

//returns the game field dimensions in a dimension struct
dimension *Game::getFieldDimension()
{
  dimension *retval = new dimension;
  for (auto &iter : tiles)
  {
    if (retval->maxX < iter->getPos()->getX())
    {
      retval->maxX = iter->getPos()->getX();
    }
    if (retval->maxY < iter->getPos()->getY())
    {
      retval->maxY = iter->getPos()->getY();
    }
  }
  retval->minX = retval->maxX;
  retval->minY = retval->maxY;
  for (auto &iter : tiles)
  {
    if (retval->minX > iter->getPos()->getX())
    {
      retval->minX = iter->getPos()->getX();
    }
    if (retval->minY > iter->getPos()->getY())
    {
      retval->minY = iter->getPos()->getY();
    }
  }
  return retval;
}

//returns a tile at pos x, y
Tile *Game::getTile(int8_t x, int8_t y)
{
  for (auto &iter :tiles)
  {
    if (iter->getPos()->isPos(x, y))
    {
      return iter;
    }
  }
  return nullptr;
}

//checks shit
int8_t Game::tryTile(Tile *input)
{
  if (tiles.size() == 0 && input->getPos()->getX() != 0 && input->getPos()->getY() != 0)
  {
    return -1;
  }
  for (auto &iter : tiles)
  {
    if (input->getPos()->isPos(iter->getPos()))
    {
      //already exists
      return -2;
    }
  }
  tile_neighbours *neighbours = input->getNeighbours();
  if (!neighbours->hasNeighbours() && tiles.size() != 0)
  {
    //no neigbour found
    delete neighbours;
    return -3;
  }
  input->matchSides();
  if (!input->checkSides())
  {
    //colors mismatch
    delete neighbours;
    return -4;
  }
  delete neighbours;
  return 0;
}

void Game::addAutomatic(Tile * input)
{
  vector<Tile*> *array = nullptr;
  Tile *testtile = nullptr;
  try
  {
    array = input->getEdges();
    if (!array)
    {
      return;
    }
    tile_neighbours *neighbours = nullptr;
    int8_t tests = 0;
    TileType testtype = VOID;
    for (auto &iter : *array)
    {
      if (iter->getType() == VOID)
      {
        neighbours = iter->getNeighbours();
        int8_t cnt_neighbour = neighbours->countNeighbours();
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
        delete neighbours;
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
  return &tiles;
}

void Game::GameOver()
{
  over = true;
}

bool Game::checkLoopWin(Color color, Tile *input, Tile *prev, Position *origin)
{
  if (prev && origin->isPos(input->getPos())) 
  {
    return true;
  }
  Tile *next = nullptr;
  tile_neighbours *neighbours = input->getNeighbours();
  if (neighbours->countNeighbours() < 2) 
  {
    delete neighbours;
    return false;
  }
  if (prev) 
  {
    if (neighbours->UP && !(neighbours->UP->getPos()->isPos(prev->getPos())) && input->getSideColor(UP) == color) 
    {
      next = neighbours->UP;
    } 
    else if (neighbours->LEFT && !(neighbours->LEFT->getPos()->isPos(prev->getPos())) && input->getSideColor(LEFT) == color) 
    {
      next = neighbours->LEFT;
    } 
    else  if (neighbours->DOWN && !(neighbours->DOWN->getPos()->isPos(prev->getPos())) && input->getSideColor(DOWN) == color)
    {
      next = neighbours->DOWN;
    } 
    else if (neighbours->RIGHT && !(neighbours->RIGHT->getPos()->isPos(prev->getPos())) && input->getSideColor(RIGHT) == color)
    {
      next = neighbours->RIGHT;
    }
  } 
  else 
  {
    if (neighbours->UP && input->getSideColor(UP) == color) 
    {
      next = neighbours->UP;
    } 
    else if (neighbours->LEFT && input->getSideColor(LEFT) == color) 
    {
      next = neighbours->LEFT;
    } 
    else  if (neighbours->DOWN && input->getSideColor(DOWN) == color)
    {
      next = neighbours->DOWN;
    } 
    else if (neighbours->RIGHT && input->getSideColor(RIGHT) == color)
    {
      next = neighbours->RIGHT;
    }
  }

  delete neighbours;
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
  static dimension dim;
  static Tile *firstnext;
  static Tile *origin;
  static bool onedirection;
  static int dir_cnt;
  if (!prev) 
  {
    //first init
    origin = input;
    onedirection = false;
    dir_cnt = 0;
    firstnext = nullptr;
  }
  bool retval = false;

  Tile *next = nullptr;
  tile_neighbours *neighbours = input->getNeighbours();

  if (dir_cnt == 2 && onedirection) 
  {
    dir_cnt--;
    onedirection = false;
    input = origin;
    prev = firstnext;
  }

  if (prev) 
  {
    if (neighbours->UP && !(neighbours->UP->getPos()->isPos(prev->getPos())) && input->getSideColor(UP) == color) 
    {
      next = neighbours->UP;
    }
    else if (neighbours->LEFT && !(neighbours->LEFT->getPos()->isPos(prev->getPos())) && input->getSideColor(LEFT) == color) 
    {
      next = neighbours->LEFT;
    }
    else  if (neighbours->DOWN && !(neighbours->DOWN->getPos()->isPos(prev->getPos())) && input->getSideColor(DOWN) == color)
    {
      next = neighbours->DOWN;
    }
    else if (neighbours->RIGHT && !(neighbours->RIGHT->getPos()->isPos(prev->getPos())) && input->getSideColor(RIGHT) == color)
    {
      next = neighbours->RIGHT;
    }
  } 
  else 
  {
    //first
    if (neighbours->UP && input->getSideColor(UP) == color) {dir_cnt++;}
    if (neighbours->LEFT && input->getSideColor(LEFT) == color) {dir_cnt++;}
    if (neighbours->DOWN && input->getSideColor(DOWN) == color){dir_cnt++;}
    if (neighbours->RIGHT && input->getSideColor(RIGHT) == color){dir_cnt++;}

    if (neighbours->UP && input->getSideColor(UP) == color) 
    {
      next = neighbours->UP;
    }
    else if (neighbours->LEFT && input->getSideColor(LEFT) == color) 
    {
      next = neighbours->LEFT;
    }
    else  if (neighbours->DOWN && input->getSideColor(DOWN) == color)
    {
      next = neighbours->DOWN;
    }
    else if (neighbours->RIGHT && input->getSideColor(RIGHT) == color)
    {
      next = neighbours->RIGHT;
    }
    firstnext = next;
  }
  delete neighbours;

  int8_t x = input->getPos()->getX();
  int8_t y = input->getPos()->getY();

  if (x < dim.minX) {dim.minX = x;}
  if (x > dim.maxX) {dim.maxX = x;}
  if (y < dim.minY) {dim.minY = y;}
  if (y > dim.maxY) {dim.maxY = y;}

  if (dir_cnt) 
  {
    if (dim.maxX - dim.minX > 6) 
    {
      return true;
    }
    if (dim.maxY - dim.minY > 6) 
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
