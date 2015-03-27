//
//  Game.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include <string>
#include <iostream>
#include "Game.h"

using namespace std;

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
  while (Running == true) {
    cout << "sep> ";
    cin >> input;
    if (input == "quit") {
      Running = false;
      return;
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