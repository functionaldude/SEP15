//
//  Game.h
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#ifndef __ass1__Game__
#define __ass1__Game__

#include "Color.h"

class Tile;

class Game {

private:
  Color Activeplayer;
  Tile* Starttile;
  bool Running;

public:
  Game();
  void setStarttile(Tile* input);
  void run();
  void setRunning(bool input);
  void togglePlayer();
  Color getActivePlayer();
};

#endif /* defined(__ass1__Game__) */
