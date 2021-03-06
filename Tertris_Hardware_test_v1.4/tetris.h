/*
  tetris.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/


#ifndef tetris_h
#define tetris_h

#include "score.h"

#include "tetromino.h"
#include "tetrisaudio.h"
#include "gameboard.h"
#include "scoreboard.h"
#include "Arduino.h"


class Tetris
{
  public:
    Tetris();  //Constructor
    Tetromino tetromino;
    Gameboard gameboard;
    Scoreboard scoreboard;
    Audio audio;
    void update_game_state(); //Runs the game

    void reset_game();
    bool start_game();

    bool move_piece_down();
    void move_piece_left();
    void move_piece_right();
    void move_piece_to_floor();
    void rotate_piece();
    
    void init_hardware();

     int game_credits;

    
   private:    
    //Variables
    int lastUpdate;    
    int game_state; // 0 - ready
                    // 1 - running
                    // 2 - game over
    
    int player_location_x;
    int player_location_y; 
        
    int active_piece_tile_coordinates[4][2];    
    
    //Functions
    void create_new_piece();
      void reset_player_location();
      
    void move_player_location(int , int );  
    
    void set_active_piece_coordiantes();
        
};

#endif
