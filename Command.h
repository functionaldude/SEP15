//------------------------------------------------------------------------------
// Command.h
//
// Group: Group 2, study assistant Christoph Hack
//
// Authors: Alexander Grass 1331106
// Amel Hamidovic 1330013
// Zoltan Sasvari 1330435
//------------------------------------------------------------------------------
//
#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "Types.h"

class Game;

class Command
{
  protected:
    Game *game_;
    Arguments *args_;
  
  public:
    Command(Game *game, struct Arguments *args);
    virtual ~Command();

  //--------------------------------------------------------------------------
  // Executes the command.
  // @param board The board where action should be performed on
  // @param params Possible parameters neede for the execution
  // @return Integer representing the success of the action

    virtual int execute() = 0;
};

class CmdAddTile : public Command 
{
  public:
    CmdAddTile(Game *game, struct Arguments *args);
    int execute() override;
};

class CmdWrite : public Command 
{
  public:
    CmdWrite(Game *game, struct Arguments *args);
    int execute() override;
};

#endif // COMMAND_H
