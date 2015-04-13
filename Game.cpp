//
//  Game.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include <string>
#include <iostream>
#include <sstream>
#include "Game.h"
#include "Tile.h"
#include "Position.h"
#include "Command.h"

using namespace std;

void getCMD(string input, args &arguments){
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
    this->filename = *filename;
    constant_write = true;
  } else {
    constant_write = false;
  }
}

void Game::run(){
  Running = true;
  string input;
  short error = 0;
  args arguments;
  while (Running == true) {
    cout << "sep> ";
    //cin >> input;
    getline(cin, input);
    getCMD(input, arguments);
    Command *cmd;
    switch (arguments.command) {
      case CMD_BLANK:
        break;
      case CMD_QUIT:
        cout << "Bye!" << endl;
        Running = false;
        return;
      case CMD_ADDTILE:{
        cmd = new cmd_AddTile(this, &arguments);
        error = cmd->execute();
        delete cmd;
        break;
      }
      case CMD_WRITE:
        cout << "write" << endl;
        break;
      case CMD_ERROR:
        cout << "Error: Unknown command!" << endl;
        break;
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

short Game::addTile(Tile *input){
  if (tiles.size() == 0 && input->getPos()->getX() != 0 && input->getPos()->getY()) {
    return -1;
  }
  return 0;
}

Game::~Game(){
  tiles.clear();
}