/*
  tetris.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/


#ifndef tetris_h
#define tetris_h

#include "score.h"

#include "tetromino.h"

#include "Arduino.h"


#define WIDTH 10 //Game board width
#define HEIGHT 28 //Game board height




class Tetris
{
  public:
    Tetris();  //Constructor
    //void Init();
    void update_game_state(); //Runs the game

    bool move_piece_down();
    void move_piece_left();
    void move_piece_right();
    void move_piece_to_floor();
    void rotate_piece();
    int GameBoard[WIDTH][ HEIGHT];

    void testDisplay();
    void init_hardware();

    Tetromino tetromino;
   private:
    
    //Variables
    int lastUpdate;
    int updateInterval = 500;

    
    int game_state;
    
    int player_location_x;
    int player_location_y; 

    
    int active_piece_tile_coordinates[4][2];

    int y_column_values[WIDTH];
    int x_row_values[HEIGHT];
    
    
    //Functions
    void initialize_gameboard();

    void initialize_counters();

    void update_counters();

    bool check_for_loss();
    
    void serialPrintGameBoard();    

    void create_new_piece();
      void reset_player_location();



    void move_player_location(int , int );    

    void set_active_piece_coordiantes();

    void render_piece_to_gameboard();

    void remove_piece_from_gameboard();

    bool check_for_collision();

    
    bool check_for_complete_row(int );

    void process_complete_row();

    void remove_row_from_gameboard(int);
  


    
};

#endif
