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
#include "Game.h"
#include "Tile.h"
#include "Position.h"
#include "Command.h"

using namespace std;

void getCMD(string input, arguments &arguments){
  if(input == ""){
    arguments.command = CMD_BLANK;
    return;
  }
  stringstream iss(input);
  string buf;
  char i = 0;
  for (; iss >> buf; i++) {
    arguments.arg[i] = new string(buf);
  }
  arguments.arg_count = i-1;
  if (*arguments.arg[0] == "AddTile") {
    arguments.command = CMD_ADDTILE;
  }
  else if (*arguments.arg[0] == "write"){
    arguments.command = CMD_WRITE;
  }
  else if (*arguments.arg[0] == "quit"){
    arguments.command = CMD_QUIT;
  }
  else {
    arguments.command = CMD_ERROR;
  }
}

Game::Game(string *filename){
  Activeplayer = COLOR_WHITE;
  Running = false;
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

void Game::run(){
  Running = true;
  string input;
  short error = 0;
  arguments arguments;
  while (Running == true) {
    cout << "sep> ";
    //cin >> input;
    getline(cin, input);
    getCMD(input, arguments);
    Command *cmd = nullptr;
    switch (arguments.command) {
      case CMD_BLANK:
        continue;
      case CMD_QUIT:
        cout << "Bye!" << endl;
        delete cmd;
        delete arguments.arg[0];
        delete arguments.arg[1];
        delete arguments.arg[2];
        Running = false;
        return;
      case CMD_ADDTILE:
        cmd = new cmd_AddTile(this, &arguments);
        break;
      case CMD_WRITE:
        cmd = new cmd_Write(this, &arguments);
        break;
      case CMD_ERROR:
        cout << "Error: Unknown command!" << endl;
        continue;
    }
    error = cmd->execute();
    delete cmd;
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

short Game::addTile(Tile *input){
  if (tiles.size() == 0 && input->getPos()->getX() != 0 && input->getPos()->getY()) {
    delete input;
    return -1;
  }
  bool has_neigbour = false;
  for (auto &iter : tiles){
    if (input->getPos()->getX() == iter->getPos()->getX() && input->getPos()->getY() == iter->getPos()->getY()) {
      //already exists
      delete input;
      return -2;
    }
    if (((input->getPos()->getX() == iter->getPos()->getX() +1 ||
          input->getPos()->getX() == iter->getPos()->getX() -1) &&
         input->getPos()->getY() == iter->getPos()->getY()) ||
        ((input->getPos()->getY() == iter->getPos()->getY() +1 ||
          input->getPos()->getY() == iter->getPos()->getY() -1) &&
         input->getPos()->getX() == iter->getPos()->getX()))
    {
      has_neigbour = true;
    }
  }
  if (!has_neigbour && tiles.size() != 0) {
    //no neigbour found
    delete input;
    return -3;
  }
  tiles.push_back(input);
  return 0;
}

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