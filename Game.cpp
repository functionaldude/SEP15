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
#include "Game.h"
#include "Tile.h"
#include "Position.h"
#include "Command.h"

using namespace std;

//command parsing
void getCMD(string input, arguments *arguments){
  if(input == ""){
    arguments->command = CMD_BLANK;
    return;
  }
  stringstream iss(input);
  string buf;
  int8_t i = 0;
  for (; iss >> buf; i++) {
    arguments->arg[i] = new string(buf);
    transform(arguments->arg[i]->begin(), arguments->arg[i]->end(), arguments->arg[i]->begin(), ::tolower);
  }
  arguments->arg_count = i-1;
  if (*arguments->arg[0] == "addtile") {
    arguments->command = CMD_ADDTILE;
  }
  else if (*arguments->arg[0] == "write"){
    arguments->command = CMD_WRITE;
  }
  else if (*arguments->arg[0] == "quit"){
    arguments->command = CMD_QUIT;
  }
  else {
    arguments->command = CMD_ERROR;
  }
}

//constructor
Game::Game(string *filename){
  Activeplayer = COLOR_WHITE;
  Running = false;
  tile_num = 64;
  if (filename) {
    this->filename = filename;
    constant_write = true;
    outputfile = new fstream(*filename, ios::out | ios::binary);
    if (!outputfile->is_open()) {
      //TODO: find out what to do in this case
      cout << "Cannot write file " << *filename << endl;
      delete filename;
      delete outputfile;
      outputfile = nullptr;
      this->filename = nullptr;
      constant_write =false;
    }
  } else {
    this->filename = nullptr;
    constant_write = false;
    outputfile = nullptr;
  }
}

//main game function
void Game::run(){
  Running = true;
  string input;
  Command *cmd = nullptr;
  arguments *args_cont = nullptr;
  while (Running == true) {
    args_cont = new arguments;
    cout << "sep> ";
    //cin >> input;
    getline(cin, input);
    getCMD(input, args_cont);
    switch (args_cont->command) {
      case CMD_BLANK:
        continue;
      case CMD_QUIT:
        cout << "Bye!" << endl;
        if (args_cont) {
          delete args_cont;
          args_cont = nullptr;
        }
        if (cmd) {
          delete cmd;
          cmd = nullptr;
        }
        Running = false;
        return;
      case CMD_ADDTILE:
        cmd = new cmd_AddTile(this, args_cont);
        break;
      case CMD_WRITE:
        cmd = new cmd_Write(this, args_cont);
        break;
      case CMD_ERROR:
        cout << "Error: Unknown command!" << endl;
        continue;
    }
    cmd->execute();
    if (args_cont) {
      delete args_cont;
      args_cont = nullptr;
    }
    if (cmd) {
      delete cmd;
      cmd = nullptr;
    }
  }
}

void Game::setRunning(bool input){
  Running = input;
}

void Game::togglePlayer(){
  if (Activeplayer == COLOR_WHITE) {
    Activeplayer = COLOR_RED;
  } else {
    Activeplayer = COLOR_WHITE;
  }
}

Color Game::getActivePlayer(){
  return Activeplayer;
}

//adds a tile
int8_t Game::addTile(Tile *input){
  if (tiles.size() == 0 && input->getPos()->getX() != 0 && input->getPos()->getY()) {
    delete input;
    return -1;
  }

  tile_neighbours *neighbours = getNeighbours(input);

  if (!neighbours) {
    //already exists
    delete input;
    return -2;
  }
  if (!neighbours->hasNeighbours() && tiles.size() != 0) {
    //no neigbour found
    delete neighbours;
    delete input;
    return -3;
  }

  input->matchSides(neighbours);
  
  if (tiles.size() == 0) {
    input->setColor(COLOR_RED);
  } else if (!checkSides(input, neighbours)) {
    //colors mismatch
    delete neighbours;
    delete input;
    return -4;
  }

  delete neighbours;
  tiles.push_back(input);
  tile_num--;
  addAutomatic(input);
  return 0;
}

//destructor
Game::~Game(){
  for (auto &iter : tiles) {
    delete iter;
  }
  if (outputfile) {
    outputfile->close();
    delete outputfile;
    delete filename;
  }
  tiles.clear();
}

//returns the game field dimensions in a dimension struct
dimension *Game::getFieldDimension(){
  dimension *retval = new dimension;
  for (auto &iter : tiles) {
    if (retval->maxX < iter->getPos()->getX()) {
      retval->maxX = iter->getPos()->getX();
    }
    if (retval->maxY < iter->getPos()->getY()) {
      retval->maxY = iter->getPos()->getY();
    }
  }
  retval->minX = retval->maxX;
  retval->minY = retval->maxY;
  for (auto &iter : tiles) {
    if (retval->minX > iter->getPos()->getX()) {
      retval->minX = iter->getPos()->getX();
    }
    if (retval->minY > iter->getPos()->getY()) {
      retval->minY = iter->getPos()->getY();
    }
  }
  return retval;
}

//checks if a Tile placement is valid with neighbour colors
bool Game::checkSides(Tile *input, tile_neighbours *neighbours){
  if (!neighbours->hasNeighbours()) {
    return true;
  }
  if (neighbours->UP && input->getSideColor(UP) != neighbours->UP->getSideColor(DOWN)) {
    return false;
  }
  if (neighbours->DOWN && input->getSideColor(DOWN) != neighbours->DOWN->getSideColor(UP)) {
    return false;
  }
  if (neighbours->LEFT && input->getSideColor(LEFT) != neighbours->LEFT->getSideColor(RIGHT)) {
    return false;
  }
  if (neighbours->RIGHT && input->getSideColor(RIGHT) != neighbours->RIGHT->getSideColor(LEFT)) {
    return false;
  }
  return true;
}

//returns a tile at pos x, y
Tile *Game::getTile(int8_t x, int8_t y){
  for (auto &iter :tiles){
    if (iter->getPos()->isPos(x, y)) {
      return iter;
    }
  }
  return nullptr;
}

//returns neighbours of a tile
tile_neighbours *Game::getNeighbours(Tile *input){
  tile_neighbours *neighbours = new tile_neighbours;
  for (auto &iter : tiles) {
    if (input->getPos()->isPos(iter->getPos())) {
      //already exists
      delete neighbours;
      return nullptr;
    }
    if (input->getPos()->getY() == iter->getPos()->getY()) {
      if (input->getPos()->getX() + 1 == iter->getPos()->getX()) {
        neighbours->RIGHT = iter;
        continue;
      }
      if (input->getPos()->getX() - 1 == iter->getPos()->getX()) {
        neighbours->LEFT = iter;
        continue;
      }
    }
    if (input->getPos()->getX() == iter->getPos()->getX()) {
      if (input->getPos()->getY() + 1 == iter->getPos()->getY()) {
        neighbours->DOWN = iter;
        continue;
      }
      if (input->getPos()->getY() - 1 == iter->getPos()->getY()) {
        neighbours->UP = iter;
        continue;
      }
    }
  }
  return neighbours;
}

vector<Tile*> *Game::getEdges(Tile* input){
  if (tiles.size() < 2) {
    return nullptr;
  }
  vector<Tile*> *edges = new std::vector<Tile*>;
  Tile *found = getTile(input->getPos()->getX()+1, input->getPos()->getY());
  if (found) {
    edges->push_back(found);
  } else {
    edges->push_back(new Tile(VOID, new Position(input->getPos()->getX()+1, input->getPos()->getY()), Activeplayer, this));
  }
  found = getTile(input->getPos()->getX()-1, input->getPos()->getY());
  if (found) {
    edges->push_back(found);
  } else {
    edges->push_back(new Tile(VOID, new Position(input->getPos()->getX()-1, input->getPos()->getY()), Activeplayer, this));
  }
  found = getTile(input->getPos()->getX(), input->getPos()->getY() +1);
  if (found) {
    edges->push_back(found);
  } else {
    edges->push_back(new Tile(VOID, new Position(input->getPos()->getX(), input->getPos()->getY() +1), Activeplayer, this));
  }
  found = getTile(input->getPos()->getX(), input->getPos()->getY() -1);
  if (found) {
    edges->push_back(found);
  } else {
    edges->push_back(new Tile(VOID, new Position(input->getPos()->getX(), input->getPos()->getY() -1), Activeplayer, this));
  }
  return edges;
}

bool Game::tryTile(Tile *input){
  if (tiles.size() == 0 && input->getPos()->getX() != 0 && input->getPos()->getY()) {
    return false;
  }
  tile_neighbours *neighbours = getNeighbours(input);
  if (!neighbours) {
    //already exists
    return false;
  }
  if (!neighbours->hasNeighbours() && tiles.size() != 0) {
    //no neigbour found
    delete neighbours;
    return false;
  }
  input->matchSides(neighbours);
  if (!checkSides(input, neighbours)) {
    //colors mismatch
    delete neighbours;
    return false;
  }
  delete neighbours;
  return true;
}

void Game::addAutomatic(Tile * input){
  vector<Tile*> *array = getEdges(input);
  if (!array) {
    return;
  }
  tile_neighbours *neighbours = nullptr;
  int8_t tests = 0;
  TileType testtype = VOID;
  Tile *testtile = nullptr;
  for (auto &iter : *array){
    if (iter->getType() == VOID) {
      neighbours = getNeighbours(iter);
      int8_t cnt_neighbour = neighbours->countNeighbours();
      if (cnt_neighbour > 1) {
        testtile = new Tile(CROSS, new Position(*iter->getPos()), Activeplayer, this);
        if (tryTile(testtile)) {
          tests++;
          testtype = testtile->getType();
        }
        delete testtile;
        testtile = new Tile(CURVE_1, new Position(*iter->getPos()), Activeplayer, this);
        if (tryTile(testtile)) {
          tests++;
          testtype = testtile->getType();
        }
        delete testtile;
        testtile = new Tile(CURVE_2, new Position(*iter->getPos()), Activeplayer, this);
        if (tryTile(testtile)) {
          tests++;
          testtype = testtile->getType();
        }
        delete testtile;
        if (tests == 1 && testtype != VOID) {
          addTile(new Tile(testtype, new Position(*iter->getPos()), Activeplayer, this));
        }
        tests = 0;
        testtype = VOID;
      }
      delete neighbours;
    }
  }

  for (auto &iter : *array){
    if (iter->getType() == VOID) {
      delete iter;
    }
  }
  delete array;
}

vector<Tile*> *Game::getTiles(){
  return &tiles;
}