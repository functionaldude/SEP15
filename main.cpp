//------------------------------------------------------------------------------
// main.cpp
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//------------------------------------------------------------------------------
//

#include <iostream>
#include <string.h>
#include "Game.h"
#include "Position.h"
#include "Types.h"
#include "Tile.h"

using namespace std;
//------------------------------------------------------------------------------
// main function
// entry point for execution
// @param argc argument count
// @param **argv argument values
// @return return value for the OS
//
int main(int argc, char **argv)
{
  string *filename = nullptr;
  //chack for arguments
  if (unlikely(argc > 3))
  {
    cout << "Usage: <" << string(argv[0]) << ">" << endl;
    return 2;
  }
  if (argc > 1 && !strcmp(argv[1], "-g")) 
  {
    if (argv[2] == nullptr) 
    {
      //error
    } 
    else 
    {
      filename = new std::string(argv[2]);
    }
  }

  Game *trax = new Game(filename);

  try 
  {
    trax->run();
  } 
  catch (std::bad_alloc &ba) 
  {
    delete trax;
    cout << "Error: Out of Memory!" << endl;
    return -1;
  }
  delete trax;
  return 0;
}
