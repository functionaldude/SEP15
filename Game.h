//------------------------------------------------------------------------------
// Game.h
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

#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include <vector>
#include <string>

class Tile;
class Position;

//------------------------------------------------------------------------------
//  Game class for coordinating the game
//

class Game 
{

  //---------------------------------------------------------------------------
  // Friend for Command Class for adding Tiles on the field
  //
  friend class CmdAddTile;
  
  //---------------------------------------------------------------------------
  // Friend for Command Class for writing game output
  //
  friend class CmdWrite;

  friend class CmdSats;

  protected:

  int stats[2];

    //-------------------------------------------------------------------------
    // Color of the active player
    //
    Color activeplayer_;
    
    //-------------------------------------------------------------------------
    // Is set true if game is running
    //
    bool running_;

    //-------------------------------------------------------------------------
    // String with the outputfile name
    //
    std::string *filename_;
    
    //-------------------------------------------------------------------------
    // Is set true if game was launched in graphical mode
    //
    bool constant_write_;

    //-------------------------------------------------------------------------
    // Vector with placed Tiles
    //
    std::vector<Tile*> tiles_;


    //-------------------------------------------------------------------------
    // Bool which is set true if someone wins or game is draw
    //
    bool over_;

    //-------------------------------------------------------------------------
    // Amount of remaining Tiles avaible in the Game
    //
    int tile_num_;
    
    //-------------------------------------------------------------------------
    // Method for placing automatic Tiles
    // @param users input
    // @return Tile at certain position
    //
    void addAutomatic(Tile *input);
    
    //-------------------------------------------------------------------------
    // Method for checking if someone won according to a loop
    // @param color checked color
    // @param input input tile
    // @param prev previous tile
    // @param origin first position
    // @return true if won 
    //
    static bool checkLoopWin(Color color, Tile *input, Tile *prev, 
                            Position *origin);
    
    //-------------------------------------------------------------------------
    // Method for checking if someone won according to a line of 8 Tiles
    // @param color checked color
    // @param input input tile
    // @param prev previous tile
    // @return if won 
    //
    static bool checkLineWin(Color color, Tile *input, Tile *prev);

  public:

    //-------------------------------------------------------------------------
    // Constructor
    //
    Game(std::string *filename);
    
    //-------------------------------------------------------------------------
    // Destructor
    //
    ~Game();
    
    //-------------------------------------------------------------------------
    // Method for adding a Tile
    // @param user input
    // @return Returns 
    int8_t addTile(Tile* input);
    
    //-------------------------------------------------------------------------
    // Method for trying if it's possible to place a Tile at this position
    // @param users input
    // @return 
    int8_t tryTile(Tile *input);
    
    //-------------------------------------------------------------------------
    // Method for running the Game
    //
    void run();
    
    //-------------------------------------------------------------------------
    // Method for toggling the player
    //
    void togglePlayer();
    
    //-------------------------------------------------------------------------
    // Method for ending the game
    //
    void gameOver();

    //-------------------------------------------------------------------------
    // Getter Methods
    //
    Tile *getTile(int8_t x, int8_t y);
    Dimension *getFieldDimension();
    std::vector<Tile*> *getTiles();
};

#endif // GAME_H
