/*
  randomizer.h - Library for generating numbers (random tetris pieces).
  Created by Skye Perry, November 22, 2018.
  Library for used in tetris.cpp to create a random sequence of tetris pieces represented as integers 1 - 7.
  This adheres somewhat the Tetris guidline found here: http://tetris.wikia.com/wiki/Random_Generator
  Released into the public domain.
*/


#ifndef randomizer_h
#define randomizer_h

#include "Arduino.h"

#define SEQUENCETOTAL 7

class Randomizer
{
  public:
  
  Randomizer();
  
  void debug_print();
  
  int get_new_piece();
  
  int get_next_piece();
  
  int get_current_piece();
  
  
  
  private:
  int active_sequence,
      inactive_sequence;

  void toggle_active_sequence();
  
  int current_sequence_index;
  
  bool is_already_picked(int,int);
  
  void reset_sequence(int);
  
  void increment_current_sequence_index();
  
  int sequence[2][SEQUENCETOTAL];

  void generate_new_sequence(int);

  
  
};
#endif
