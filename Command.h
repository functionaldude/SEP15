//------------------------------------------------------------------------------
// Filename: Command.h
// Description: Class representing a general command
// Authors: Tutors
// Tutor: Tutors
// Group: 42
// Created: 08.08.2011
// Last change: 02.09.2011
//------------------------------------------------------------------------------

#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>
#include "types.h"

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

#endif //COMMAND_H_INCLUDED
