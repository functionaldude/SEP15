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

using namespace std;

enum cmd : char{
  CMD_QUIT = 0,
  CMD_ADDTILE = 1,
  CMD_WRITE = 2,
  CMD_ERROR = 3,
  CMD_BLANK = 4,
};

struct args{
  cmd command;
  string *arg[5];
};

void getCMD(string input, args &arguments){
  if(input == ""){
    arguments.command = CMD_BLANK;
  }
  stringstream iss(input);
  string buf;
  for (char i = 0; iss >> buf; i++) {
    arguments.arg[i] = new string(buf);
  }
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

Game::Game(){
  Activeplayer = COLOR_WHITE;
  Starttile = nullptr;
  Running = false;
}

void Game::setStarttile(Tile *input){
  Starttile = input;
}

void Game::run(){
  Running = true;
  string input;
  struct args arguments;
  while (Running == true) {
    cout << "sep> ";
    //cin >> input;
    getline(cin, input);
    getCMD(input, arguments);

    switch (arguments.command) {
      case CMD_BLANK:
        cout << endl;
        break;
      case CMD_QUIT:
        return;
      case CMD_ADDTILE:
        cout << "Addtile" << endl;
        break;
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