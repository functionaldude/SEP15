//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// <Name> <Matriculum Number>
// <Add one row for every additional group member>
//------------------------------------------------------------------------------
//

#include <vector>
#include "Tile.h"
#include "Position.h"
#include "Game.h"

using namespace std;

Tile::Tile(TileType side, Position *pos, Game *parent) :
  side_(side),
  pos_(pos),
  parent_(parent)
{
  topcolor_ = COLOR_BLANK;
}

Tile::~Tile()
{
  delete pos_;
}

//returns the position pointer
Position *Tile::getPos()
{
  return pos_;
}

//returns the tile type
TileType Tile::getType()
{
  return side_;
}

//returns topcolor
Color Tile::getColor()
{
  return topcolor_;
}

//returns the color of the side of the tile
Color Tile::getSideColor(enum Side side)
{
  if (side == UP) 
  {
    return topcolor_;
  }
  switch (side_) 
  {
    case CROSS:
      if (topcolor_ == COLOR_RED) 
      {
        switch (side) 
        {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_WHITE;
        }
      } 
      else 
      {
        switch (side) 
        {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_RED;
        }
      }
    case CURVE_1:
      if (topcolor_ == COLOR_RED) 
      {
        switch (side) 
        {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_RED;
          case RIGHT: return COLOR_WHITE;
        }
      } 
      else 
      {
        switch (side) 
        {
          case UP: return COLOR_WHITE;
          case DOWN: return COLOR_RED;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_RED;
        }
      }
    case CURVE_2:
      if (topcolor_ == COLOR_RED) 
      {
        switch (side) 
        {
          case UP: return COLOR_RED;
          case DOWN: return COLOR_WHITE;
          case LEFT: return COLOR_WHITE;
          case RIGHT: return COLOR_RED;
          default: return COLOR_BLANK;
        }
      } 
      else 
      {
        switch (side) 
        {
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
void Tile::matchSides()
{
  if (parent->getTiles()->size() == 0) 
  {
    topcolor_ = COLOR_RED;
    return;
  }
  TileNeighbours *neighbours = getNeighbours();
  switch (side_) 
  {
    case VOID: return;

    case CROSS:
    {
      if (neighbours->UP) 
      {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) 
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->DOWN) 
      {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) 
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->LEFT) 
      {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) 
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->RIGHT) 
      {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) 
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      break;
    }

    case CURVE_1:
    {
      if (neighbours->UP) 
      {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) 
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->DOWN) 
      {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) 
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->LEFT) 
      {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) 
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->RIGHT) 
      {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) 
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      break;
    }

    case CURVE_2:
    {
      if (neighbours->UP) 
      {
        if (neighbours->UP->getSideColor(DOWN) == COLOR_RED) 
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->DOWN) 
      {
        if (neighbours->DOWN->getSideColor(UP) == COLOR_RED) 
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->LEFT) 
      {
        if (neighbours->LEFT->getSideColor(RIGHT) == COLOR_RED) 
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->RIGHT) 
      {
        if (neighbours->RIGHT->getSideColor(LEFT) == COLOR_RED) 
        {
          topcolor__ = COLOR_RED;
        } 
        else 
        {
          topcolor__ = COLOR_WHITE;
        }
        break;
      }
      break;
    }
  }
  delete neighbours;
}

vector<Tile*> *Tile::getEdges()
{
  if (parent_->getTiles()->size() < 2) 
  {
    return nullptr;
  }
  vector<Tile*> *edges = nullptr;
  try 
  {
    edges = new std::vector<Tile*>;
    Tile *found = parent_->getTile(pos->getX()+1, pos->getY());
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos->getX()+1, pos->getY()), parent));
    }
    found = parent->getTile(pos->getX()-1, pos->getY());
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos->getX()-1, pos->getY()), parent));
    }
    found = parent->getTile(pos->getX(), pos->getY() +1);
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos->getX(), pos->getY() +1), parent));
    }
    found = parent->getTile(pos->getX(), pos->getY() -1);
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos->getX(), pos->getY() -1), parent));
    }
    return edges;
  } 
  catch (std::bad_alloc &ba) 
  {
    if (edges) 
    {
      for (auto &iter : *edges) 
      {
        delete iter;
      }
      delete edges;
    }
    throw;
  }
  return nullptr;
}

TileNeighbours *Tile::getNeighbours()
{
  tile_neighbours *neighbours = new tile_neighbours;
  for (auto &iter : *parent->getTiles()) 
  {
    if (pos->getY() == iter->pos->getY()) 
    {
      if (pos->getX() + 1 == iter->pos->getX()) 
      {
        neighbours->right = iter;
        continue;
      }
      if (pos->getX() - 1 == iter->pos->getX()) 
      {
        neighbours->left = iter;
        continue;
      }
    }
    if (pos->getX() == iter->pos->getX()) 
    {
      if (pos->getY() + 1 == iter->pos->getY()) 
      {
        neighbours->down = iter;
        continue;
      }
      if (pos->getY() - 1 == iter->pos->getY()) 
      {
        neighbours->up = iter;
        continue;
      }
    }
  }
  return neighbours;
}

bool Tile::checkSides()
{
  TileNeighbours *neighbours = getNeighbours();
  bool retval = true;
  if (!neighbours->hasNeighbours()) 
  {
    delete neighbours;
    return retval;
  }
  if (neighbours->up && this->getSideColor(UP) != neighbours->UP->getSideColor(DOWN)) 
  {
    retval = false;
  }
  if (neighbours->down && this->getSideColor(DOWN) != neighbours->DOWN->getSideColor(UP)) 
  {
    retval = false;
  }
  if (neighbours->left && this->getSideColor(LEFT) != neighbours->LEFT->getSideColor(RIGHT)) 
  {
    retval = false;
  }
  if (neighbours->RIGHT && this->getSideColor(RIGHT) != neighbours->RIGHT->getSideColor(LEFT)) 
  {
    retval = false;
  }
  delete neighbours;
  return retval;
}
