//
//  Tile.cpp
//  ass1
//
//  Created by Zoltán Sasvári on 15.03.15.
//  Copyright (c) 2015 G-TEAM. All rights reserved.
//

#include <vector>
#include "Tile.h"
#include "Position.h"
#include "Game.h"

using namespace std;

Tile::Tile(TileType Side, Position *pos, Game *parent) :
  Side(Side),
  pos(pos),
  parent(parent)
{
  Topcolor = COLOR_BLANK;
}

Tile::~Tile(){
  delete pos;
}

//returns the position pointer
Position *Tile::getPos(){
  return pos;
}

//returns the tile type
TileType Tile::getType(){
  return Side;
}

//returns topcolor
Color Tile::getColor(){
  return Topcolor;
}

//returns the color of the side of the tile
Color Tile::getSideColor(enum Side side){
  if (side == UP) {
    return Topcolor;
  }
  switch (Side) {
    case CROSS:
      if (Topcolor == COLOR_RED) {
        switch (side) {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_WHITE;
        }
      } else {
        switch (side) {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_RED;
        }
      }
    case CURVE_1:
      if (Topcolor == COLOR_RED) {
        switch (side) {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_WHITE;
        }
      } else {
        switch (side) {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_RED;
        }
      }
    case CURVE_2:
      if (Topcolor == COLOR_RED) {
        switch (side) {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_RED;
          default: return COLOR_BLANK;
        }
      } else {
        switch (side) {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_WHITE;
        }
      }
    default: return COLOR_BLANK;
  }
}

//sets the top color according to the neigbours
void Tile::matchSides(){
  if (parent->getTiles()->size() == 0) {
    Topcolor = COLOR_RED;
    return;
  }
  tile_neighbours *neighbours = getNeighbours();
  switch (Side) {
    case VOID: return;

    case CROSS:{
      if (neighbours->UP) {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) {
          Topcolor = COLOR_RED;
        } else {
          Topcolor = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->DOWN) {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) {
          Topcolor = COLOR_RED;
        } else {
          Topcolor = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->LEFT) {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) {
          Topcolor = COLOR_WHITE;
        } else {
          Topcolor = COLOR_RED;
        }
        break;
      }
      if (neighbours->RIGHT) {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) {
          Topcolor = COLOR_WHITE;
        } else {
          Topcolor = COLOR_RED;
        }
        break;
      }
      break;
    }

    case CURVE_1:{
      if (neighbours->UP) {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) {
          Topcolor = COLOR_RED;
        } else {
          Topcolor = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->DOWN) {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) {
          Topcolor = COLOR_WHITE;
        } else {
          Topcolor = COLOR_RED;
        }
        break;
      }
      if (neighbours->LEFT) {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) {
          Topcolor = COLOR_RED;
        } else {
          Topcolor = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->RIGHT) {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) {
          Topcolor = COLOR_WHITE;
        } else {
          Topcolor = COLOR_RED;
        }
        break;
      }
      break;
    }

    case CURVE_2:{
      if (neighbours->UP) {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) {
          Topcolor = COLOR_RED;
        } else {
          Topcolor = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->DOWN) {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) {
          Topcolor = COLOR_WHITE;
        } else {
          Topcolor = COLOR_RED;
        }
        break;
      }
      if (neighbours->LEFT) {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) {
          Topcolor = COLOR_WHITE;
        } else {
          Topcolor = COLOR_RED;
        }
        break;
      }
      if (neighbours->RIGHT) {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) {
          Topcolor = COLOR_RED;
        } else {
          Topcolor = COLOR_WHITE;
        }
        break;
      }
      break;
    }
  }
  delete neighbours;
}

vector<Tile*> *Tile::getEdges(){
  if (parent->getTiles()->size() < 2) {
    return nullptr;
  }
  vector<Tile*> *edges = nullptr;
  Tile *found = nullptr;
  try {
    edges = new std::vector<Tile*>;
    found = parent->getTile(pos->getX()+1, pos->getY());
    if (found) {
      edges->push_back(found);
    } else {
      edges->push_back(new Tile(VOID, new Position(pos->getX()+1, pos->getY()), parent));
    }
    found = parent->getTile(pos->getX()-1, pos->getY());
    if (found) {
      edges->push_back(found);
    } else {
      edges->push_back(new Tile(VOID, new Position(pos->getX()-1, pos->getY()), parent));
    }
    found = parent->getTile(pos->getX(), pos->getY() +1);
    if (found) {
      edges->push_back(found);
    } else {
      edges->push_back(new Tile(VOID, new Position(pos->getX(), pos->getY() +1), parent));
    }
    found = parent->getTile(pos->getX(), pos->getY() -1);
    if (found) {
      edges->push_back(found);
    } else {
      edges->push_back(new Tile(VOID, new Position(pos->getX(), pos->getY() -1), parent));
    }
    return edges;
  } catch (std::bad_alloc &ba) {
    if (edges) {
      for (auto &iter : *edges) {
        delete iter;
      }
      delete edges;
    }
    throw;
  }
  return nullptr;
}

tile_neighbours *Tile::getNeighbours(){
  tile_neighbours *neighbours = new tile_neighbours;
  for (auto &iter : *parent->getTiles()) {
    if (pos->getY() == iter->pos->getY()) {
      if (pos->getX() + 1 == iter->pos->getX()) {
        neighbours->RIGHT = iter;
        continue;
      }
      if (pos->getX() - 1 == iter->pos->getX()) {
        neighbours->LEFT = iter;
        continue;
      }
    }
    if (pos->getX() == iter->pos->getX()) {
      if (pos->getY() + 1 == iter->pos->getY()) {
        neighbours->DOWN = iter;
        continue;
      }
      if (pos->getY() - 1 == iter->pos->getY()) {
        neighbours->UP = iter;
        continue;
      }
    }
  }
  return neighbours;
}

bool Tile::checkSides(){
  tile_neighbours *neighbours = getNeighbours();
  bool retval = true;
  if (!neighbours->hasNeighbours()) {
    delete neighbours;
    return retval;
  }
  if (neighbours->UP && this->getSideColor(UP) != neighbours->UP->getSideColor(DOWN)) {
    retval = false;
  }
  if (neighbours->DOWN && this->getSideColor(DOWN) != neighbours->DOWN->getSideColor(UP)) {
    retval = false;
  }
  if (neighbours->LEFT && this->getSideColor(LEFT) != neighbours->LEFT->getSideColor(RIGHT)) {
    retval = false;
  }
  if (neighbours->RIGHT && this->getSideColor(RIGHT) != neighbours->RIGHT->getSideColor(LEFT)) {
    retval = false;
  }
  delete neighbours;
  return retval;
}