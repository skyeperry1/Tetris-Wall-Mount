/*
  gameboard.h - Library for keeping and updating tetris gameboard state
  Created by Skye Perry, Dec 1, 2018.
  Released into the public domain.
*/


#ifndef gameboard_h
#define gameboard_h

#include "Arduino.h"


#define WIDTH 10 //Game board width
#define HEIGHT 28 //Game board height


class Gameboard
{
  public:
  
  Gameboard();

  int active_state[WIDTH][HEIGHT];

  bool check_for_top_out();  
  bool check_for_collision(int[4][2]);

  void render_tetromino(int[4][2],int);
  void remove_tetromino(int[4][2]);    

  int process_complete_row(int[4][2]);

  int get_drop_height(int, int);

  void debug_print();
  void debug_print_active_state();
  
  private:
  
  bool check_for_complete_row(int);
  
  void remove_row_from_gameboard(int);
    
  void reset_state();
  
  
};
#endif
