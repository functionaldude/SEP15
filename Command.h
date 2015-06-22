//------------------------------------------------------------------------------
// Command.h
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

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "Types.h"

class Game;

class Command
{
  protected:
    
    //-------------------------------------------------------------------------
    // Game object 
    //
    Game *game_;

    //-------------------------------------------------------------------------
    // Arguments object 
    //
    Arguments *args_;
  
  public:
    
    //-------------------------------------------------------------------------
    // Constructor
    //
    Command(Game *game, struct Arguments *args);
    
    //-------------------------------------------------------------------------
    // Destructor
    //
    virtual ~Command();

    //-------------------------------------------------------------------------
    // Executes the command.
    // @param board The board where action should be performed on
    // @param params Possible parameters neede for the execution
    // @return Integer representing the success of the action
    //
    virtual int execute() = 0;

};

class CmdAddTile : public Command 
{
  public:

    //-------------------------------------------------------------------------
    // Method for adding Tiles to the game field
    // @param Game 
    // @param Arguments 
    // @return Tile on field if correct input
    //
    CmdAddTile(Game *game, struct Arguments *args);
    
    //-------------------------------------------------------------------------
    // 
    //
    int execute() override;
};

class CmdWrite : public Command 
{
  public:
    
    //-------------------------------------------------------------------------
    // Method for checking if someone won according to a line of 8 Tiles
    // @param color current color
    // @param input useres input
    // @param prev previous tile
    // @return if won 
    //
    CmdWrite(Game *game, struct Arguments *args);
    
    
    //-------------------------------------------------------------------------
    // 
    //
    int execute() override;
};

class CmdDel : public Command {
public:
  CmdDel(Game *game, struct Arguments *args);

  int execute() override;
};

#endif // COMMAND_H
