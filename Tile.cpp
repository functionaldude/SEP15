//------------------------------------------------------------------------------
// Tile.cpp
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//
// latest change by Amel Hamidovic 23.4.2015
//------------------------------------------------------------------------------
//

#include <vector>
#include "Tile.h"
#include "Position.h"
#include "Game.h"

using std::vector;

Tile::Tile(TileType side, Position *pos, Game *parent) :
  side_(side),
  topcolor_(COLOR_BLANK),
  pos_(pos),
  parent_(parent)
{
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


void Tile::matchSides()
{
  if (unlikely(parent_->getTiles()->size() == 0))
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
      if (neighbours->up)
      {
        if (neighbours->up->getSideColor(DOWN) == COLOR_RED)
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->down)
      {
        if (neighbours->down->getSideColor(UP) == COLOR_RED)
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->left)
      {
        if (neighbours->left->getSideColor(RIGHT) == COLOR_RED)
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->right)
      {
        if (neighbours->right->getSideColor(LEFT) == COLOR_RED)
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
      if (neighbours->up)
      {
        if (neighbours->up->getSideColor(DOWN) == COLOR_RED)
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->down)
      {
        if (neighbours->down->getSideColor(UP) == COLOR_RED)
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->left)
      {
        if (neighbours->left->getSideColor(RIGHT) == COLOR_RED)
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->right)
      {
        if (neighbours->right->getSideColor(LEFT) == COLOR_RED)
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
      if (neighbours->up)
      {
        if (neighbours->up->getSideColor(DOWN) == COLOR_RED)
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
        }
        break;
      }
      if (neighbours->down)
      {
        if (neighbours->down->getSideColor(UP) == COLOR_RED)
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->left)
      {
        if (neighbours->left->getSideColor(RIGHT) == COLOR_RED)
        {
          topcolor_ = COLOR_WHITE;
        } 
        else 
        {
          topcolor_ = COLOR_RED;
        }
        break;
      }
      if (neighbours->right)
      {
        if (neighbours->right->getSideColor(LEFT) == COLOR_RED)
        {
          topcolor_ = COLOR_RED;
        } 
        else 
        {
          topcolor_ = COLOR_WHITE;
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
    Tile *found = parent_->getTile(pos_->getX()+1, pos_->getY());
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos_->getX()+1,
                                                   pos_->getY()), parent_));
    }
    found = parent_->getTile(pos_->getX()-1, pos_->getY());
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos_->getX()-1,
                                                   pos_->getY()), parent_));
    }
    found = parent_->getTile(pos_->getX(), pos_->getY() +1);
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos_->getX(),
                                                   pos_->getY() +1), parent_));
    }
    found = parent_->getTile(pos_->getX(), pos_->getY() -1);
    if (found) 
    {
      edges->push_back(found);
    } 
    else 
    {
      edges->push_back(new Tile(VOID, new Position(pos_->getX(),
                                                   pos_->getY() -1), parent_));
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
  TileNeighbours *neighbours = new TileNeighbours;
  for (auto &iter : *parent_->getTiles()) 
  {
    if (pos_->getY() == iter->pos_->getY()) 
    {
      if (pos_->getX() + 1 == iter->pos_->getX()) 
      {
        neighbours->right = iter;
        continue;
      }
      if (pos_->getX() - 1 == iter->pos_->getX()) 
      {
        neighbours->left = iter;
        continue;
      }
    }
    if (pos_->getX() == iter->pos_->getX()) 
    {
      if (pos_->getY() + 1 == iter->pos_->getY()) 
      {
        neighbours->down = iter;
        continue;
      }
      if (pos_->getY() - 1 == iter->pos_->getY())
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
  if (unlikely(!neighbours->hasNeighbours()))
  {
    delete neighbours;
    return retval;
  }
  if (neighbours->up &&
      this->getSideColor(UP) != neighbours->up->getSideColor(DOWN))
  {
    retval = false;
  }
  if (neighbours->down &&
      this->getSideColor(DOWN) != neighbours->down->getSideColor(UP))
  {
    retval = false;
  }
  if (neighbours->left &&
      this->getSideColor(LEFT) != neighbours->left->getSideColor(RIGHT))
  {
    retval = false;
  }
  if (neighbours->right &&
      this->getSideColor(RIGHT) != neighbours->right->getSideColor(LEFT))
  {
    retval = false;
  }
  delete neighbours;
  return retval;
}

void Tile::setColor(Color farbe){
  this->topcolor_ = farbe;
}
